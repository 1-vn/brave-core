/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/devtools/onevn_devtools_ui_bindings.h"

#include <string>

#include "base/bind.h"
#include "base/values.h"
#include "onevn/browser/themes/onevn_theme_service.h"
#include "onevn/common/pref_names.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/tabs/tab_strip_model.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "content/public/browser/web_contents.h"
#include "components/prefs/pref_service.h"

using BTS = OnevnThemeService;

namespace {
void SetOnevnThemeType(Profile* profile, OnevnThemeType type) {
  profile->GetPrefs()->SetInteger(kOnevnThemeType, type);
}
}  // namespace

class OnevnDevToolsUIBindingsBrowserTest : public InProcessBrowserTest {
 public:
  void GetPreferenceCallback(const base::Value* value) {
    ui_theme_ = value->FindKey("uiTheme")->GetString();
  }

  std::string ui_theme_;
};

IN_PROC_BROWSER_TEST_F(OnevnDevToolsUIBindingsBrowserTest, ThemeTest) {
  auto* profile = browser()->profile();
  auto* tab_strip_model = browser()->tab_strip_model();
  content::WebContents* web_contents = tab_strip_model->GetActiveWebContents();
  DCHECK(web_contents);

  SetOnevnThemeType(profile, OnevnThemeType::ONEVN_THEME_TYPE_DARK);
  auto* devtools_ui_bindings = new OnevnDevToolsUIBindings(web_contents);
  DCHECK(devtools_ui_bindings);
  devtools_ui_bindings->GetPreferences(
      base::Bind(&OnevnDevToolsUIBindingsBrowserTest::GetPreferenceCallback,
                 base::Unretained(this)));
  // Check current devtools' theme is same as native theme when user doesn't
  // change devtools' theme explicitely.
  EXPECT_EQ(ui_theme_, "\"dark\"");

  SetOnevnThemeType(profile, OnevnThemeType::ONEVN_THEME_TYPE_LIGHT);
  devtools_ui_bindings->GetPreferences(
      base::Bind(&OnevnDevToolsUIBindingsBrowserTest::GetPreferenceCallback,
                 base::Unretained(this)));
  // In devtools, default is used as light.
  EXPECT_EQ(ui_theme_, "\"default\"");

  // When user sets devtools' theme explicitely, respect user's setting.
  devtools_ui_bindings->SetPreference("uiTheme", "\"dark\"");
  devtools_ui_bindings->GetPreferences(
      base::Bind(&OnevnDevToolsUIBindingsBrowserTest::GetPreferenceCallback,
                 base::Unretained(this)));
  EXPECT_EQ(ui_theme_, "\"dark\"");
}
