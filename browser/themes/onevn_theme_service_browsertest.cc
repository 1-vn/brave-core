/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/themes/onevn_theme_service.h"
#include "onevn/browser/themes/theme_properties.h"
#include "onevn/common/pref_names.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/themes/theme_properties.h"
#include "chrome/browser/themes/theme_service.h"
#include "chrome/browser/themes/theme_service_factory.h"
#include "chrome/browser/ui/browser.h"
#include "components/prefs/pref_service.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "ui/native_theme/native_theme.h"
#include "ui/native_theme/native_theme_dark_aura.h"
#include "ui/native_theme/native_theme_observer.h"

using OnevnThemeServiceTest = InProcessBrowserTest;
using BTS = OnevnThemeService;

namespace {

void SetOnevnThemeType(Profile* profile, OnevnThemeType type) {
  profile->GetPrefs()->SetInteger(kOnevnThemeType, type);
}

bool IsDefaultThemeOverridden(Profile* profile) {
  return profile->GetPrefs()->GetBoolean(kUseOverriddenOnevnThemeType);
}

class TestNativeThemeObserver : public ui::NativeThemeObserver {
 public:
  TestNativeThemeObserver() {}
  ~TestNativeThemeObserver() override {}

  MOCK_METHOD1(OnNativeThemeUpdated, void(ui::NativeTheme*));
};

}  // namespace

class OnevnThemeServiceTestWithoutSystemTheme : public InProcessBrowserTest {
 public:
  OnevnThemeServiceTestWithoutSystemTheme() {
    OnevnThemeService::is_test_ = true;
    OnevnThemeService::use_system_theme_mode_in_test_ = false;
  }
};

IN_PROC_BROWSER_TEST_F(OnevnThemeServiceTestWithoutSystemTheme,
                       OnevnThemeChangeTest) {
  Profile* profile = browser()->profile();
  Profile* profile_private = profile->GetOffTheRecordProfile();

  const ui::ThemeProvider& tp =
      ThemeService::GetThemeProviderForProfile(profile);
  const ui::ThemeProvider& tp_private =
      ThemeService::GetThemeProviderForProfile(profile_private);

  auto test_theme_property = OnevnThemeProperties::COLOR_FOR_TEST;

  // Check default type is set initially.
  EXPECT_TRUE(IsDefaultThemeOverridden(profile));
  EXPECT_TRUE(IsDefaultThemeOverridden(profile_private));

  // Test light theme
  SetOnevnThemeType(profile, OnevnThemeType::ONEVN_THEME_TYPE_LIGHT);
  EXPECT_EQ(OnevnThemeType::ONEVN_THEME_TYPE_LIGHT,
            BTS::GetActiveOnevnThemeType(profile));
  EXPECT_EQ(OnevnThemeProperties::kLightColorForTest,
            tp.GetColor(test_theme_property));

  // Test light theme private
  SetOnevnThemeType(profile_private, OnevnThemeType::ONEVN_THEME_TYPE_LIGHT);
  EXPECT_EQ(OnevnThemeType::ONEVN_THEME_TYPE_LIGHT,
            BTS::GetActiveOnevnThemeType(profile_private));
  EXPECT_EQ(OnevnThemeProperties::kPrivateColorForTest,
            tp_private.GetColor(test_theme_property));

  // Test dark theme
  SetOnevnThemeType(profile, OnevnThemeType::ONEVN_THEME_TYPE_DARK);
  EXPECT_EQ(OnevnThemeType::ONEVN_THEME_TYPE_DARK,
            BTS::GetActiveOnevnThemeType(profile));
  EXPECT_EQ(OnevnThemeProperties::kDarkColorForTest,
            tp.GetColor(test_theme_property));

  // Test dark theme private
  SetOnevnThemeType(profile_private, OnevnThemeType::ONEVN_THEME_TYPE_DARK);
  EXPECT_EQ(OnevnThemeType::ONEVN_THEME_TYPE_DARK,
            BTS::GetActiveOnevnThemeType(profile_private));
  EXPECT_EQ(OnevnThemeProperties::kPrivateColorForTest,
            tp_private.GetColor(test_theme_property));
}

// Test whether appropriate native theme observer is called when onevn theme is
// changed.
IN_PROC_BROWSER_TEST_F(OnevnThemeServiceTest, NativeThemeObserverTest) {
  Profile* profile = browser()->profile();
  // Initially set to light.
  SetOnevnThemeType(profile, OnevnThemeType::ONEVN_THEME_TYPE_LIGHT);

  // Check native theme and dark theme oberver is called once by changing theme
  // to dark and light.
  TestNativeThemeObserver native_theme_observer;
  EXPECT_CALL(
      native_theme_observer,
      OnNativeThemeUpdated(ui::NativeTheme::GetInstanceForNativeUi())).Times(1);
  TestNativeThemeObserver native_dark_theme_observer;
  EXPECT_CALL(
      native_dark_theme_observer,
      OnNativeThemeUpdated(ui::NativeThemeDarkAura::instance())).Times(1);

  ui::NativeThemeDarkAura::instance()->AddObserver(
      &native_dark_theme_observer);
  ui::NativeTheme::GetInstanceForNativeUi()->AddObserver(
      &native_theme_observer);

  SetOnevnThemeType(profile, OnevnThemeType::ONEVN_THEME_TYPE_DARK);
  SetOnevnThemeType(profile, OnevnThemeType::ONEVN_THEME_TYPE_LIGHT);
}

#if defined(OS_MACOSX)
IN_PROC_BROWSER_TEST_F(OnevnThemeServiceTest, SystemThemeChangeTest) {
  // TODO(simonhong): Delete this when we gets dark mode enabled branch on
  // MacOS.
  if (!OnevnThemeService::SystemThemeModeEnabled())
    return;

  const bool initial_mode =
      ui::NativeTheme::GetInstanceForNativeUi()->SystemDarkModeEnabled();
  Profile* profile = browser()->profile();

  // Change to light.
  SetOnevnThemeType(profile, OnevnThemeType::ONEVN_THEME_TYPE_LIGHT);
  EXPECT_FALSE(
      ui::NativeTheme::GetInstanceForNativeUi()->SystemDarkModeEnabled());

  SetOnevnThemeType(profile, OnevnThemeType::ONEVN_THEME_TYPE_DARK);
  EXPECT_TRUE(
      ui::NativeTheme::GetInstanceForNativeUi()->SystemDarkModeEnabled());

  SetOnevnThemeType(profile, OnevnThemeType::ONEVN_THEME_TYPE_LIGHT);
  EXPECT_FALSE(
      ui::NativeTheme::GetInstanceForNativeUi()->SystemDarkModeEnabled());

  SetOnevnThemeType(profile, OnevnThemeType::ONEVN_THEME_TYPE_DEFAULT);
  EXPECT_EQ(initial_mode,
            ui::NativeTheme::GetInstanceForNativeUi()->SystemDarkModeEnabled());
}
#endif
