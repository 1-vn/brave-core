/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_THEMES_THEME_PROPERTIES_H_
#define ONEVN_BROWSER_THEMES_THEME_PROPERTIES_H_

#include "base/optional.h"
#include "third_party/skia/include/core/SkColor.h"
#include "onevn/browser/themes/onevn_theme_service.h"

namespace OneVNThemeProperties {

  const SkColor kPrivateColorForTest = SkColorSetRGB(0xFF, 0x00, 0x00);
  const SkColor kLightColorForTest = SkColorSetRGB(0xFF, 0xFF, 0xFF);
  const SkColor kDarkColorForTest = SkColorSetRGB(0x00, 0x00, 0x00);

  enum TestProperty {
    COLOR_FOR_TEST = 9000
  };

}

base::Optional<SkColor> MaybeGetDefaultColorForOneVNUi(int id, bool incognito, OneVNThemeType theme);

#endif  // ONEVN_BROWSER_THEMES_THEME_PROPERTIES_H_
