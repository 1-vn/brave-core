/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_THEMES_ONEVN_THEME_UTILS_H_
#define ONEVN_BROWSER_THEMES_ONEVN_THEME_UTILS_H_

#include "onevn/browser/themes/onevn_theme_service.h"

bool SystemThemeSupportDarkMode();

// Override system theme with |type|. With this, browser gets this theme type
// regardless of OS preference when it queries system theme type.
// If |type| is ONEVN_THEME_TYPE_DEFAULT, clear overridden theme and follow
// the theme in OS preference.
// Note: This is only implemented on MacOS for now.
void SetSystemTheme(OnevnThemeType type);

#endif  // ONEVN_BROWSER_THEMES_ONEVN_THEME_UTILS_H_
