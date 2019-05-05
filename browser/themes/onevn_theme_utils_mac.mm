/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/themes/onevn_theme_utils.h"

#import <Cocoa/Cocoa.h>

#include "base/mac/sdk_forward_declarations.h"

bool SystemThemeSupportDarkMode() {
  // Dark mode is supported since Mojave.
  if (@available(macOS 10.14, *))
    return true;
  return false;
}

void SetSystemTheme(OnevnThemeType type) {
  if (type == ONEVN_THEME_TYPE_DEFAULT) {
    [NSApp setAppearance:nil];
    return;
  }

  if (@available(macOS 10.14, *)) {
    NSAppearanceName new_appearance_name =
        type == ONEVN_THEME_TYPE_DARK ? NSAppearanceNameDarkAqua
                                      : NSAppearanceNameAqua;
    [NSApp setAppearance:[NSAppearance appearanceNamed:new_appearance_name]];
  }
}
