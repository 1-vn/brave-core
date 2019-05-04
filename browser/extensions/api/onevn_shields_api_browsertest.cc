/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/path_service.h"
#include "onevn/browser/extensions/api/onevn_shields_api.h"
#include "onevn/common/onevn_paths.h"
#include "onevn/common/extensions/extension_constants.h"
#include "onevn/components/onevn_shields/common/onevn_shield_constants.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/extensions/api/content_settings/content_settings_api.h"
#include "chrome/browser/extensions/api/content_settings/content_settings_api_constants.h"
#include "chrome/browser/extensions/api/content_settings/content_settings_helpers.h"
#include "chrome/browser/extensions/api/content_settings/content_settings_service.h"
#include "chrome/browser/extensions/api/content_settings/content_settings_store.h"
#include "chrome/browser/extensions/extension_function_test_utils.h"
#include "chrome/browser/extensions/extension_tab_util.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/test/base/ui_test_utils.h"
#include "content/public/test/browser_test_utils.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "components/content_settings/core/common/content_settings.h"
#include "components/content_settings/core/common/content_settings_types.h"
#include "extensions/common/extension_builder.h"
#include "net/dns/mock_host_resolver.h"

namespace extensions {

using api::OneVNShieldsContentSettingGetFunction;
using api::OneVNShieldsContentSettingSetFunction;
using extensions::api::OneVNShieldsAllowScriptsOnceFunction;
using extension_function_test_utils::RunFunctionAndReturnError;
using extension_function_test_utils::RunFunctionAndReturnSingleResult;

class OneVNShieldsAPIBrowserTest : public InProcessBrowserTest {
  public:
    void SetUpOnMainThread() override {
      InProcessBrowserTest::SetUpOnMainThread();
      host_resolver()->AddRule("*", "127.0.0.1");
      content::SetupCrossSiteRedirector(embedded_test_server());

      onevn::RegisterPathProvider();
      base::FilePath test_data_dir;
      base::PathService::Get(onevn::DIR_TEST_DATA, &test_data_dir);
      embedded_test_server()->ServeFilesFromDirectory(test_data_dir);

      ASSERT_TRUE(embedded_test_server()->Start());
      extension_ = extensions::ExtensionBuilder("Test").Build();
      content_settings_ =
          HostContentSettingsMapFactory::GetForProfile(browser()->profile());
    }

    content::WebContents* active_contents() {
      return browser()->tab_strip_model()->GetActiveWebContents();
    }

    scoped_refptr<const extensions::Extension> extension() {
      return extension_;
    }

    HostContentSettingsMap* content_settings() const {
      return content_settings_;
    }

    void BlockScripts() {
      content_settings_->SetContentSettingCustomScope(
          ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
          CONTENT_SETTINGS_TYPE_JAVASCRIPT, "", CONTENT_SETTING_BLOCK);
    }

    bool NavigateToURLUntilLoadStop(
        const std::string& origin, const std::string& path) {
      ui_test_utils::NavigateToURL(
          browser(),
          embedded_test_server()->GetURL(origin, path));

      return WaitForLoadStop(active_contents());
    }

    void AllowScriptOriginOnce(const std::string& origin) {
      // run extension function to temporarily allow origin
      scoped_refptr<OneVNShieldsAllowScriptsOnceFunction> function(
          new OneVNShieldsAllowScriptsOnceFunction());
      function->set_extension(extension().get());
      function->set_has_callback(true);

      const GURL url(embedded_test_server()->GetURL(origin, "/simple.js"));
      const std::string allow_origin = url.GetOrigin().spec();
      int tabId = extensions::ExtensionTabUtil::GetTabId(active_contents());

      RunFunctionAndReturnSingleResult(
          function.get(),
          "[[\"" + allow_origin + "\"], " + std::to_string(tabId) + "]",
          browser());

      // reload page with a.com temporarily allowed
      active_contents()->GetController().Reload(content::ReloadType::NORMAL,
          true);
    }

  private:
    HostContentSettingsMap* content_settings_;
    scoped_refptr<const extensions::Extension> extension_;
};

IN_PROC_BROWSER_TEST_F(OneVNShieldsAPIBrowserTest, AllowScriptsOnce) {
  BlockScripts();

  EXPECT_TRUE(
      NavigateToURLUntilLoadStop("a.com", "/load_js_from_origins.html"));
  EXPECT_EQ(active_contents()->GetAllFrames().size(), 1u) <<
    "All script loadings should be blocked.";

  AllowScriptOriginOnce("a.com");

  EXPECT_TRUE(WaitForLoadStop(active_contents()));
  EXPECT_EQ(active_contents()->GetAllFrames().size(), 2u) <<
    "Scripts from a.com should be temporarily allowed.";

  // reload page again
  active_contents()->GetController().Reload(content::ReloadType::NORMAL,
                                            true);
  EXPECT_TRUE(WaitForLoadStop(active_contents()));
  EXPECT_EQ(active_contents()->GetAllFrames().size(), 2u) <<
    "Scripts from a.com should be temporarily allowed after reload.";

  // same doc navigation
  ui_test_utils::NavigateToURL(
      browser(),
      embedded_test_server()->GetURL("a.com", "/load_js_from_origins.html#foo"));
  EXPECT_TRUE(WaitForLoadStop(active_contents()));
  EXPECT_EQ(active_contents()->GetAllFrames().size(), 2u) <<
    "Scripts from a.com should be temporarily allowed for same doc navigation.";

  // navigate to a different origin
  ui_test_utils::NavigateToURL(
      browser(),
      embedded_test_server()->GetURL("b.com", "/load_js_from_origins.html"));
  EXPECT_TRUE(WaitForLoadStop(active_contents()));
  EXPECT_EQ(active_contents()->GetAllFrames().size(), 1u) <<
    "All script loadings should be blocked after navigating away.";
}

IN_PROC_BROWSER_TEST_F(OneVNShieldsAPIBrowserTest, AllowScriptsOnceIframe) {
  BlockScripts();

  EXPECT_TRUE(
      NavigateToURLUntilLoadStop("a.com", "/remote_iframe.html"));
  EXPECT_EQ(active_contents()->GetAllFrames().size(), 2u) <<
    "All script loadings should be blocked.";

  AllowScriptOriginOnce("b.com");

  EXPECT_TRUE(WaitForLoadStop(active_contents()));
  EXPECT_EQ(active_contents()->GetAllFrames().size(), 3u) <<
    "Scripts from b.com should be temporarily allowed.";
}

constexpr char kJavascriptSetParams[] =
    "[\"javascript\", {\"primaryPattern\": \"https://www.1-vn.com/*\","
    "\"setting\": \"block\"}]";
constexpr char kJavascriptGetParams[] =
    "[\"javascript\", {\"primaryUrl\": \"https://www.1-vn.com/*\"}]";
constexpr char kOneVNURLPattern[] = "https://www.1-vn.com/*";
const GURL kOneVNURL("https://www.1-vn.com");

// Test javascript content setting works properly via onevnShields api.
IN_PROC_BROWSER_TEST_F(OneVNShieldsAPIBrowserTest,
                       ContentSettingJavascriptAPI) {
  // Default content settings for javascript is allow.
  scoped_refptr<OneVNShieldsContentSettingGetFunction> get_function(
      new OneVNShieldsContentSettingGetFunction());
  get_function->set_extension(extension().get());
  std::unique_ptr<base::Value> value;
  value.reset(RunFunctionAndReturnSingleResult(get_function.get(),
                                               kJavascriptGetParams,
                                               browser()));
  EXPECT_EQ(value->FindKey(
      content_settings_api_constants::kContentSettingKey)->GetString(),
      std::string("allow"));

  // Block javascript.
  scoped_refptr<OneVNShieldsContentSettingSetFunction> set_function(
      new OneVNShieldsContentSettingSetFunction());
  set_function->set_extension(extension().get());
  RunFunctionAndReturnSingleResult(set_function.get(),
                                   kJavascriptSetParams,
                                   browser());

  // Check Block is set.
  get_function = base::MakeRefCounted<OneVNShieldsContentSettingGetFunction>();
  get_function->set_extension(extension().get());
  value.reset(RunFunctionAndReturnSingleResult(get_function.get(),
                                               kJavascriptGetParams,
                                               browser()));
  EXPECT_EQ(value->FindKey(
      content_settings_api_constants::kContentSettingKey)->GetString(),
      std::string("block"));
}

// Test previous settings set by extension is deleted when setting is newly
// modifed.
IN_PROC_BROWSER_TEST_F(OneVNShieldsAPIBrowserTest,
                       ContentSettingValueFromExtensionDelete) {
  // Set javascript content setting via ContentSettingsStore and check this
  // settings comes from extension. chrome.contentSettings.javascript.set()
  // sets settings into ContentSettingsStore.
  std::string primary_error;
  ContentSettingsPattern primary_pattern =
      content_settings_helpers::ParseExtensionPattern(kOneVNURLPattern,
                                                      &primary_error);
  scoped_refptr<ContentSettingsStore> store =
      ContentSettingsService::Get(browser()->profile())->
          content_settings_store();
  store->SetExtensionContentSetting(onevn_extension_id,
                                    primary_pattern,
                                    ContentSettingsPattern::Wildcard(),
                                    CONTENT_SETTINGS_TYPE_JAVASCRIPT,
                                    std::string(),
                                    CONTENT_SETTING_ALLOW,
                                    kExtensionPrefsScopeRegular);
  DCHECK(primary_pattern.IsValid());

  content_settings::SettingInfo info;
  content_settings()->GetWebsiteSetting(
      kOneVNURL, kOneVNURL,
      CONTENT_SETTINGS_TYPE_JAVASCRIPT, std::string(), &info);
  // Check source is extension.
  EXPECT_EQ(info.source,
            content_settings::SettingSource::SETTING_SOURCE_EXTENSION);

  // Check this value via onevnShields api.
  scoped_refptr<OneVNShieldsContentSettingGetFunction> get_function(
      new OneVNShieldsContentSettingGetFunction());
  get_function->set_extension(extension().get());
  std::unique_ptr<base::Value> value;
  value.reset(RunFunctionAndReturnSingleResult(get_function.get(),
                                               kJavascriptGetParams,
                                               browser()));
  EXPECT_EQ(value->FindKey(
      content_settings_api_constants::kContentSettingKey)->GetString(),
      std::string("allow"));

  // Block via shields api.
  scoped_refptr<OneVNShieldsContentSettingSetFunction> set_function(
      new OneVNShieldsContentSettingSetFunction());
  set_function->set_extension(extension().get());
  RunFunctionAndReturnSingleResult(set_function.get(),
                                   kJavascriptSetParams,
                                   browser());

  // Check Block is set.
  get_function = base::MakeRefCounted<OneVNShieldsContentSettingGetFunction>();
  get_function->set_extension(extension().get());
  value.reset(RunFunctionAndReturnSingleResult(get_function.get(),
                                               kJavascriptGetParams,
                                               browser()));
  EXPECT_EQ(value->FindKey(
      content_settings_api_constants::kContentSettingKey)->GetString(),
      std::string("block"));

  content_settings()->GetWebsiteSetting(
      kOneVNURL, kOneVNURL,
      CONTENT_SETTINGS_TYPE_JAVASCRIPT, std::string(), &info);
  // Check source is user.
  EXPECT_EQ(info.source,
            content_settings::SettingSource::SETTING_SOURCE_USER);
}

// Checks shields configuration is persisted across the sessions.
IN_PROC_BROWSER_TEST_F(OneVNShieldsAPIBrowserTest,
                       PRE_ShieldSettingsPersistTest) {
  HostContentSettingsMapFactory::GetForProfile(browser()->profile())->
      SetContentSettingDefaultScope(
        kOneVNURL, kOneVNURL,
        CONTENT_SETTINGS_TYPE_PLUGINS,
        onevn_shields::kHTTPUpgradableResources,
        CONTENT_SETTING_ALLOW);

  ContentSetting setting =
      HostContentSettingsMapFactory::GetForProfile(browser()->profile())->
          GetContentSetting(kOneVNURL, kOneVNURL, CONTENT_SETTINGS_TYPE_PLUGINS,
                            onevn_shields::kHTTPUpgradableResources);
  EXPECT_EQ(setting, CONTENT_SETTING_ALLOW);
}

IN_PROC_BROWSER_TEST_F(OneVNShieldsAPIBrowserTest,
                       ShieldSettingsPersistTest) {
  ContentSetting setting =
      HostContentSettingsMapFactory::GetForProfile(browser()->profile())->
          GetContentSetting(kOneVNURL, kOneVNURL, CONTENT_SETTINGS_TYPE_PLUGINS,
                            onevn_shields::kHTTPUpgradableResources);
  EXPECT_EQ(setting, CONTENT_SETTING_ALLOW);
}

// Checks flash configuration isn't persisted across the sessions.
IN_PROC_BROWSER_TEST_F(OneVNShieldsAPIBrowserTest,
                       PRE_FlashPersistTest) {
  HostContentSettingsMapFactory::GetForProfile(browser()->profile())->
      SetContentSettingDefaultScope(
        kOneVNURL, kOneVNURL,
        CONTENT_SETTINGS_TYPE_PLUGINS,
        std::string(),
        CONTENT_SETTING_ALLOW);

  ContentSetting setting =
      HostContentSettingsMapFactory::GetForProfile(browser()->profile())->
          GetContentSetting(kOneVNURL, kOneVNURL, CONTENT_SETTINGS_TYPE_PLUGINS,
                            std::string());
  EXPECT_EQ(setting, CONTENT_SETTING_ALLOW);
}

IN_PROC_BROWSER_TEST_F(OneVNShieldsAPIBrowserTest,
                       FlashPersistTest) {
  ContentSetting setting =
      HostContentSettingsMapFactory::GetForProfile(browser()->profile())->
          GetContentSetting(kOneVNURL, kOneVNURL, CONTENT_SETTINGS_TYPE_PLUGINS,
                            std::string());
  EXPECT_EQ(setting, CONTENT_SETTING_BLOCK);
}

}  // namespace extensions
