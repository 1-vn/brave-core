/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_UI_VIEWS_FRAME_ONEVN_BROWSER_FRAME_H_
#define ONEVN_BROWSER_UI_VIEWS_FRAME_ONEVN_BROWSER_FRAME_H_

#include "chrome/browser/ui/views/frame/browser_frame.h"

class BrowserView;

class OnevnBrowserFrame : public BrowserFrame {
  public:
    explicit OnevnBrowserFrame(BrowserView* browser_view);
    ~OnevnBrowserFrame() override;
    const ui::NativeTheme* GetNativeTheme() const override;

  private:
    // The BrowserView is our ClientView. This is a pointer to it.
    BrowserView* browser_view_;

    DISALLOW_COPY_AND_ASSIGN(OnevnBrowserFrame);
};

#endif
