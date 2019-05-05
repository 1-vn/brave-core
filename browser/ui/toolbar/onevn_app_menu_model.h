/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_UI_TOOLBAR_ONEVN_APP_MENU_MODEL_H_
#define ONEVN_BROWSER_UI_TOOLBAR_ONEVN_APP_MENU_MODEL_H_

#include "chrome/browser/ui/toolbar/app_menu_model.h"

class OnevnAppMenuModel : public AppMenuModel {
 public:
  OnevnAppMenuModel(ui::AcceleratorProvider* provider,
      Browser* browser,
      AppMenuIconController* app_menu_icon_controller = nullptr);
  ~OnevnAppMenuModel() override;

 private:
  // AppMenuModel overrides:
  void Build() override;

  void InsertOnevnMenuItems();

  Browser* const browser_;  // weak

  DISALLOW_COPY_AND_ASSIGN(OnevnAppMenuModel);
};

#endif  // ONEVN_BROWSER_UI_TOOLBAR_ONEVN_APP_MENU_MODEL_H_
