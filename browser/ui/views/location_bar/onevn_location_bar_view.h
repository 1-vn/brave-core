/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_UI_VIEWS_LOCATION_BAR_ONEVN_LOCATION_BAR_VIEW_H_
#define ONEVN_BROWSER_UI_VIEWS_LOCATION_BAR_ONEVN_LOCATION_BAR_VIEW_H_

#include "chrome/browser/ui/views/location_bar/location_bar_view.h"

class OneVNActionsContainer;
class OneVNActionsContainerTest;
class OneVNRewardsBrowserTest;
enum class OmniboxTint;

// The purposes of this subclass are to:
// - Add the OneVNActionsContainer to the location bar
class OneVNLocationBarView : public LocationBarView {
 public:
  using LocationBarView::LocationBarView;
  void Init() override;
  void Layout() override;
  void Update(const content::WebContents* contents) override;
  void OnChanged() override;

  // views::View:
  gfx::Size CalculatePreferredSize() const override;
  void OnThemeChanged() override;
  void ChildPreferredSizeChanged(views::View* child) override;

  ContentSettingImageView* GetContentSettingsImageViewForTesting(size_t idx);

 private:
  friend class ::OneVNActionsContainerTest;
  friend class ::OneVNRewardsBrowserTest;
  void UpdateBookmarkStarVisibility() override;
  OmniboxTint GetTint() override;
  OneVNActionsContainer* onevn_actions_ = nullptr;

  DISALLOW_COPY_AND_ASSIGN(OneVNLocationBarView);
};

#endif  // ONEVN_BROWSER_UI_VIEWS_LOCATION_BAR_ONEVN_LOCATION_BAR_VIEW_H_
