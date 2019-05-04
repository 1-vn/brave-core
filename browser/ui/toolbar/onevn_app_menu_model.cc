/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/ui/toolbar/onevn_app_menu_model.h"

#include "onevn/app/onevn_command_ids.h"
#include "onevn/components/onevn_sync/onevn_sync_service.h"
#include "onevn/grit/onevn_generated_resources.h"
#include "chrome/app/chrome_command_ids.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"

OneVNAppMenuModel::OneVNAppMenuModel(
    ui::AcceleratorProvider* provider,
    Browser* browser,
    AppMenuIconController* app_menu_icon_controller)
    : AppMenuModel(provider, browser, app_menu_icon_controller),
      browser_(browser) {}

OneVNAppMenuModel::~OneVNAppMenuModel() {}

void OneVNAppMenuModel::Build() {
  // Insert onevn items after build chromium items.
  AppMenuModel::Build();
  InsertOneVNMenuItems();
}

void OneVNAppMenuModel::InsertOneVNMenuItems() {
  // Sync & Rewards pages are redirected to normal window when it is loaded in
  // private window. So, only hide them in guest(tor) window.
  if (!browser_->profile()->IsGuestSession()) {
    InsertItemWithStringIdAt(
        GetIndexOfCommandId(IDC_SHOW_DOWNLOADS),
        IDC_SHOW_ONEVN_REWARDS,
        IDS_SHOW_ONEVN_REWARDS);
    if (onevn_sync::OneVNSyncService::is_enabled()) {
      InsertItemWithStringIdAt(
          GetIndexOfCommandId(IDC_SHOW_ONEVN_REWARDS),
          IDC_SHOW_ONEVN_SYNC,
          IDS_SHOW_ONEVN_SYNC);
    }
  }
  InsertItemWithStringIdAt(
      GetIndexOfCommandId(IDC_SHOW_DOWNLOADS),
      IDC_SHOW_ONEVN_ADBLOCK,
      IDS_SHOW_ONEVN_ADBLOCK);
  if (browser_->profile()->IsTorProfile()) {
    InsertItemWithStringIdAt(
        GetIndexOfCommandId(IDC_NEW_WINDOW),
        IDC_NEW_TOR_IDENTITY,
        IDS_NEW_TOR_IDENTITY);
  } else {
    InsertItemWithStringIdAt(
        GetIndexOfCommandId(IDC_NEW_INCOGNITO_WINDOW) + 1,
        IDC_NEW_OFFTHERECORD_WINDOW_TOR,
        IDS_NEW_OFFTHERECORD_WINDOW_TOR);
  }
}
