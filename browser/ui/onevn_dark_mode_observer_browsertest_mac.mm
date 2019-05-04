/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/test/scoped_feature_list.h"
#include "onevn/browser/themes/onevn_theme_service.h"
#include "onevn/browser/ui/onevn_dark_mode_observer.h"
#include "onevn/common/pref_names.h"
#include "chrome/browser/browser_features.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "components/prefs/pref_service.h"
#include "ui/native_theme/native_theme_dark_aura.h"

using OneVNDarkModeObserverTest = InProcessBrowserTest;

namespace {

void SetOneVNThemeType(Profile* profile, OneVNThemeType type) {
  profile->GetPrefs()->SetInteger(kOneVNThemeType, type);
}

}  // namespace

// Test whether DarkModeObserver observes proper NativeTheme.
IN_PROC_BROWSER_TEST_F(OneVNDarkModeObserverTest,
                       ObserveProperNativeThemeTest) {
  if (@available(macOS 10.14, *)) {
    base::test::ScopedFeatureList features;
    features.InitAndEnableFeature(features::kWebUIDarkMode);

    Profile* profile = browser()->profile();

    // Load webui to instantiate OneVNDarkModeObserver.
    AddTabAtIndexToBrowser(
        browser(), 0, GURL("onevn://history"), ui::PAGE_TRANSITION_TYPED, true);

    // Initially set to light.
    SetOneVNThemeType(profile, OneVNThemeType::ONEVN_THEME_TYPE_LIGHT);
    EXPECT_EQ(
        ui::NativeTheme::GetInstanceForNativeUi(),
        OneVNDarkModeObserver::current_native_theme_for_testing_);

    SetOneVNThemeType(profile, OneVNThemeType::ONEVN_THEME_TYPE_DARK);
    EXPECT_EQ(
        ui::NativeThemeDarkAura::instance(),
        OneVNDarkModeObserver::current_native_theme_for_testing_);
  }
}
