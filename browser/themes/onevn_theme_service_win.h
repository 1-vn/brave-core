/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_THEMES_ONEVN_THEME_SERVICE_WIN_H_
#define ONEVN_BROWSER_THEMES_ONEVN_THEME_SERVICE_WIN_H_

#include "chrome/browser/themes/theme_service_win.h"

class OneVNThemeServiceWin : public ThemeServiceWin {
 public:
  OneVNThemeServiceWin() = default;
  ~OneVNThemeServiceWin() override = default;

 private:
  // ThemeServiceWin overrides:
  SkColor GetDefaultColor(int id, bool incognito) const override;

  DISALLOW_COPY_AND_ASSIGN(OneVNThemeServiceWin);
};

#endif  // ONEVN_BROWSER_THEMES_ONEVN_THEME_SERVICE_WIN_H_
