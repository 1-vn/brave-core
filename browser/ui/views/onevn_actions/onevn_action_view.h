/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * you can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_UI_VIEWS_ONEVN_ACTIONS_ONEVN_ACTION_VIEW_H_
#define ONEVN_BROWSER_UI_VIEWS_ONEVN_ACTIONS_ONEVN_ACTION_VIEW_H_

#include "chrome/browser/ui/views/toolbar/toolbar_action_view.h"

namespace gfx {
  class Rect;
}

// Subclasses ToolbarActionViewc so that the notification badge can be painted
// outside the highlight bubble.
class OnevnActionView : public ToolbarActionView {
 public:
  using ToolbarActionView::ToolbarActionView;
  // views::MenuButton:
  void OnBoundsChanged(const gfx::Rect& previous_bounds) override;
  DISALLOW_COPY_AND_ASSIGN(OnevnActionView);
};

#endif
