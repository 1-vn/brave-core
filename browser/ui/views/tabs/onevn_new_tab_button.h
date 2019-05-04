/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * you can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_UI_VIEWS_TABS_ONEVN_NEW_TAB_BUTTON_H_
#define ONEVN_BROWSER_UI_VIEWS_TABS_ONEVN_NEW_TAB_BUTTON_H_

#include "chrome/browser/ui/views/tabs/new_tab_button.h"
#include "third_party/skia/include/core/SkPath.h"

class TabStrip;
namespace views {
class ButtonListener;
}

class OneVNNewTabButton : public NewTabButton {
 public:
  static const gfx::Size kButtonSize;
  using NewTabButton::NewTabButton;

 private:
  gfx::Size CalculatePreferredSize() const override;
  SkPath GetBorderPath(const gfx::Point& origin,
                       float scale,
                       bool extend_to_top) const override;
  void PaintPlusIcon(gfx::Canvas* canvas) const override;
  DISALLOW_COPY_AND_ASSIGN(OneVNNewTabButton);
};

#endif  // ONEVN_BROWSER_UI_VIEWS_TABS_ONEVN_NEW_TAB_BUTTON_H_
