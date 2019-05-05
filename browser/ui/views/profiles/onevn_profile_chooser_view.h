/* Copyright 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_UI_VIEWS_PROFILES_ONEVN_PROFILE_CHOOSER_VIEW_H_
#define ONEVN_BROWSER_UI_VIEWS_PROFILES_ONEVN_PROFILE_CHOOSER_VIEW_H_

#include "chrome/browser/ui/views/profiles/profile_chooser_view.h"

class OnevnProfileChooserView : public ProfileChooserView {
 private:
  friend class ProfileChooserView;

  OnevnProfileChooserView(views::Button* anchor_button,
                          const gfx::Rect& anchor_rect,
                          gfx::NativeView parent_window,
                          Browser* browser,
                          profiles::BubbleViewMode view_mode,
                          signin::GAIAServiceType service_type,
                          signin_metrics::AccessPoint access_point,
                          bool is_source_keyboard);
  ~OnevnProfileChooserView() override;

  // views::ButtonListener:
  void ButtonPressed(views::Button* sender, const ui::Event& event) override;

  void ResetView() override;

  views::View* OnevnCreateDiceSyncErrorView(
      const AvatarMenu::Item& avatar_item,
      sync_ui_util::AvatarSyncErrorType error,
      int button_string_id);

  void AddTorButton(views::GridLayout* layout);

  views::LabelButton* tor_profile_button_;

  DISALLOW_COPY_AND_ASSIGN(OnevnProfileChooserView);
};

#endif  // ONEVN_BROWSER_UI_VIEWS_PROFILES_ONEVN_PROFILE_CHOOSER_VIEW_H_
