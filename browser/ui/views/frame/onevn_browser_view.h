/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_UI_VIEWS_FRAME_ONEVN_BROWSER_VIEW_H_
#define ONEVN_BROWSER_UI_VIEWS_FRAME_ONEVN_BROWSER_VIEW_H_

#include "chrome/browser/ui/views/frame/browser_view.h"

class OneVNBrowserView : public BrowserView {
 public:
  using BrowserView::BrowserView;

  void SetStarredState(bool is_starred) override;
  void ShowUpdateChromeDialog() override;

 private:
  DISALLOW_COPY_AND_ASSIGN(OneVNBrowserView);
};

#endif  // ONEVN_BROWSER_UI_VIEWS_FRAME_ONEVN_BROWSER_VIEW_H_
