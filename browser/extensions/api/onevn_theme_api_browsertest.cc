/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/extensions/api/onevn_theme_api.h"
#include "onevn/browser/themes/onevn_theme_service.h"
#include "onevn/common/pref_names.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/browser/extensions/extension_function_test_utils.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "components/prefs/pref_service.h"
#include "extensions/common/extension_builder.h"

using BTS = OnevnThemeService;
using extensions::api::OnevnThemeGetOnevnThemeTypeFunction;
using extension_function_test_utils::RunFunctionAndReturnSingleResult;

namespace {
void SetOnevnThemeType(Profile* profile, OnevnThemeType type) {
  profile->GetPrefs()->SetInteger(kOnevnThemeType, type);
}
}  // namespace
class OnevnThemeAPIBrowserTest : public InProcessBrowserTest {
 public:
  void SetUpOnMainThread() override {
    InProcessBrowserTest::SetUpOnMainThread();
    extension_ = extensions::ExtensionBuilder("Test").Build();
  }

  scoped_refptr<const extensions::Extension> extension() {
    return extension_;
  }

 private:
  scoped_refptr<const extensions::Extension> extension_;
};

IN_PROC_BROWSER_TEST_F(OnevnThemeAPIBrowserTest,
                       OnevnThemeGetOnevnThemeTypeTest) {
  Profile* profile = browser()->profile();

  // Change to Light type and check it from api.
  SetOnevnThemeType(profile, OnevnThemeType::ONEVN_THEME_TYPE_LIGHT);
  EXPECT_EQ(OnevnThemeType::ONEVN_THEME_TYPE_LIGHT,
            BTS::GetActiveOnevnThemeType(profile));

  scoped_refptr<OnevnThemeGetOnevnThemeTypeFunction> get_function(
      new OnevnThemeGetOnevnThemeTypeFunction());
  get_function->set_extension(extension().get());
  std::unique_ptr<base::Value> value;
  value.reset(RunFunctionAndReturnSingleResult(get_function.get(),
                                               std::string("[]"),
                                               browser()));
  EXPECT_EQ(value->GetString(), "Light");
}
