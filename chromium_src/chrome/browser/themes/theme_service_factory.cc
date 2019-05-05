/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "build/build_config.h"
#include "chrome/browser/themes/theme_service.h"

#if defined(OS_WIN)
#include "onevn/browser/themes/onevn_theme_service_win.h"
#undef ThemeServiceWin
#define ThemeServiceWin OnevnThemeServiceWin
#elif !defined(USE_X11)
#include "onevn/browser/themes/onevn_theme_service.h"
#undef ThemeService
#define ThemeService OnevnThemeService
#endif

#include "../../../../../chrome/browser/themes/theme_service_factory.cc"
