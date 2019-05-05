/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/extensions/onevn_theme_event_router.h"
#include "onevn/browser/themes/onevn_theme_service.h"
#include "onevn/common/pref_names.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/browser/themes/theme_service_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "components/prefs/pref_service.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "ui/native_theme/native_theme_dark_aura.h"

using OnevnThemeEventRouterBrowserTest = InProcessBrowserTest;

namespace {

void SetOnevnThemeType(Profile* profile, OnevnThemeType type) {
  profile->GetPrefs()->SetInteger(kOnevnThemeType, type);
}

}  // namespace

namespace extensions {

class MockOnevnThemeEventRouter : public OnevnThemeEventRouter {
 public:
  using OnevnThemeEventRouter::OnevnThemeEventRouter;
  ~MockOnevnThemeEventRouter() override {}

  ui::NativeTheme* current_native_theme_for_testing() const {
    return current_native_theme_for_testing_;
  }

  MOCK_METHOD0(Notify, void());
};

}  // namespace extensions


IN_PROC_BROWSER_TEST_F(OnevnThemeEventRouterBrowserTest,
                       ThemeChangeTest) {
  Profile* profile = browser()->profile();
  SetOnevnThemeType(profile, OnevnThemeType::ONEVN_THEME_TYPE_DARK);

  extensions::MockOnevnThemeEventRouter* mock_router =
      new extensions::MockOnevnThemeEventRouter(profile);
  OnevnThemeService* service = static_cast<OnevnThemeService*>(
      ThemeServiceFactory::GetForProfile(browser()->profile()));
  service->SetOnevnThemeEventRouterForTesting(mock_router);

  EXPECT_CALL(*mock_router, Notify()).Times(1);
  SetOnevnThemeType(profile, OnevnThemeType::ONEVN_THEME_TYPE_LIGHT);
  EXPECT_EQ(
      ui::NativeTheme::GetInstanceForNativeUi(),
      mock_router->current_native_theme_for_testing());

  EXPECT_CALL(*mock_router, Notify()).Times(1);
  SetOnevnThemeType(profile, OnevnThemeType::ONEVN_THEME_TYPE_DARK);
  EXPECT_EQ(
      ui::NativeThemeDarkAura::instance(),
      mock_router->current_native_theme_for_testing());

  EXPECT_CALL(*mock_router, Notify()).Times(0);
  SetOnevnThemeType(profile, OnevnThemeType::ONEVN_THEME_TYPE_DARK);
}
