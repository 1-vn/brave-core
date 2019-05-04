/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/components/onevn_shields/common/onevn_shield_constants.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "components/content_settings/core/common/content_settings_pattern.h"

const GURL kOneVNURL("https://www.1-vn.com");

class OneVNContentSettingsRegistryBrowserTest : public InProcessBrowserTest {
 public:
  using InProcessBrowserTest::InProcessBrowserTest;

  HostContentSettingsMap* content_settings() {
    return HostContentSettingsMapFactory::GetForProfile(browser()->profile());
  }

  HostContentSettingsMap* private_content_settings() {
    return HostContentSettingsMapFactory::GetForProfile(
        browser()->profile()->GetOffTheRecordProfile());
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(OneVNContentSettingsRegistryBrowserTest);
};

IN_PROC_BROWSER_TEST_F(OneVNContentSettingsRegistryBrowserTest,
                       WithWildcardContentSetting) {
  content_settings()->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(),
      ContentSettingsPattern::Wildcard(),
      CONTENT_SETTINGS_TYPE_PLUGINS,
      onevn_shields::kOneVNShields,
      CONTENT_SETTING_ALLOW);

  ContentSetting onevn_url_shields_setting =
      content_settings()->GetContentSetting(
          kOneVNURL, kOneVNURL, CONTENT_SETTINGS_TYPE_PLUGINS,
          onevn_shields::kOneVNShields);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, onevn_url_shields_setting);

  ContentSetting onevn_url_shields_setting_private =
      private_content_settings()->GetContentSetting(
          kOneVNURL, kOneVNURL, CONTENT_SETTINGS_TYPE_PLUGINS,
          onevn_shields::kOneVNShields);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, onevn_url_shields_setting_private);
}

IN_PROC_BROWSER_TEST_F(OneVNContentSettingsRegistryBrowserTest,
                       WithoutWildcardContentSetting) {
  ContentSetting onevn_url_shields_setting =
      content_settings()->GetContentSetting(
          kOneVNURL, kOneVNURL, CONTENT_SETTINGS_TYPE_PLUGINS,
          onevn_shields::kOneVNShields);
  EXPECT_EQ(CONTENT_SETTING_DEFAULT, onevn_url_shields_setting);

  ContentSetting onevn_url_shields_setting_private =
      private_content_settings()->GetContentSetting(
          kOneVNURL, kOneVNURL, CONTENT_SETTINGS_TYPE_PLUGINS,
          onevn_shields::kOneVNShields);
  EXPECT_EQ(CONTENT_SETTING_DEFAULT, onevn_url_shields_setting_private);
}

IN_PROC_BROWSER_TEST_F(OneVNContentSettingsRegistryBrowserTest,
                       WithOneVNShieldsContentSetting) {
  ContentSettingsPattern onevn_url_pattern =
      ContentSettingsPattern::FromURL(kOneVNURL);

  content_settings()->SetContentSettingCustomScope(
      onevn_url_pattern,
      onevn_url_pattern,
      CONTENT_SETTINGS_TYPE_PLUGINS,
      onevn_shields::kOneVNShields,
      CONTENT_SETTING_ALLOW);

  ContentSetting onevn_url_shields_setting =
      content_settings()->GetContentSetting(
          kOneVNURL, kOneVNURL, CONTENT_SETTINGS_TYPE_PLUGINS,
          onevn_shields::kOneVNShields);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, onevn_url_shields_setting);

  ContentSetting onevn_url_shields_setting_private =
      private_content_settings()->GetContentSetting(
          kOneVNURL, kOneVNURL, CONTENT_SETTINGS_TYPE_PLUGINS,
          onevn_shields::kOneVNShields);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, onevn_url_shields_setting_private);
}
