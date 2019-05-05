/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_THEMES_ONEVN_THEME_SERVICE_H_
#define ONEVN_BROWSER_THEMES_ONEVN_THEME_SERVICE_H_

#include <memory>
#include <string>

#include "chrome/browser/themes/theme_service.h"
#include "components/prefs/pref_member.h"

namespace extensions {
class OnevnThemeEventRouter;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

enum OnevnThemeType {
  // DEFAULT type acts as two ways depends on system theme mode.
  // If system theme mode is disabled, we override it with channel based
  // policy. See GetThemeTypeBasedOnChannel(). In this case, user can see
  // two options in theme settings(dark and light).
  // Otherwise, it acts like system theme mode. In this case, user can see
  // three options in theme settings(os theme, dark and light).
  ONEVN_THEME_TYPE_DEFAULT,
  ONEVN_THEME_TYPE_DARK,
  ONEVN_THEME_TYPE_LIGHT,
};

class OnevnThemeService : public ThemeService {
 public:
  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);
  static OnevnThemeType GetActiveOnevnThemeType(Profile* profile);
  static base::Value GetOnevnThemeList();
  static std::string GetStringFromOnevnThemeType(OnevnThemeType type);

  OnevnThemeService();
  ~OnevnThemeService() override;

  // ThemeService overrides:
  void Init(Profile* profile) override;

 protected:
  // ThemeService overrides:
  SkColor GetDefaultColor(int id, bool incognito) const override;

 private:
  friend class OnevnThemeServiceTestWithoutSystemTheme;
  FRIEND_TEST_ALL_PREFIXES(OnevnThemeEventRouterBrowserTest,
                           ThemeChangeTest);
  FRIEND_TEST_ALL_PREFIXES(OnevnThemeServiceTest, GetOnevnThemeListTest);
  FRIEND_TEST_ALL_PREFIXES(OnevnThemeServiceTest, SystemThemeChangeTest);

  // Own |mock_router|.
  void SetOnevnThemeEventRouterForTesting(
      extensions::OnevnThemeEventRouter* mock_router);

  void OnPreferenceChanged(const std::string& pref_name);

  void RecoverPrefStates(Profile* profile);
  void OverrideDefaultThemeIfNeeded(Profile* profile);

  static bool SystemThemeModeEnabled();

  static bool is_test_;
  static bool use_system_theme_mode_in_test_;

  IntegerPrefMember onevn_theme_type_pref_;

  // Make OnevnThemeService own OnevnThemeEventRouter.
  // OnevnThemeEventRouter does its job independently with OnevnThemeService.
  // However, both are related with onevn theme and have similar life cycle.
  // So, Owning OnevnThemeEventRouter by OnevnThemeService seems fine.
  // Use smart ptr for testing by SetOnevnThemeEventRouterForTesting.
  std::unique_ptr<extensions::OnevnThemeEventRouter> onevn_theme_event_router_;

  DISALLOW_COPY_AND_ASSIGN(OnevnThemeService);
};

#endif  // ONEVN_BROWSER_THEMES_ONEVN_THEME_SERVICE_H_
