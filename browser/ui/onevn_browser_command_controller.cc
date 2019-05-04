/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/ui/onevn_browser_command_controller.h"

#include "onevn/app/onevn_command_ids.h"
#include "onevn/browser/ui/onevn_pages.h"
#include "onevn/components/onevn_rewards/browser/buildflags/buildflags.h"
#include "onevn/components/onevn_sync/onevn_sync_service.h"
#include "onevn/browser/ui/browser_commands.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/tabs/tab_strip_model.h"

namespace {
bool IsOneVNCommands(int id) {
  return id >= IDC_ONEVN_COMMANDS_START && id <= IDC_ONEVN_COMMANDS_LAST;
}
}

namespace chrome {

OneVNBrowserCommandController::OneVNBrowserCommandController(Browser* browser)
    : BrowserCommandController(browser),
      browser_(browser),
      onevn_command_updater_(nullptr) {
  InitOneVNCommandState();
}

bool OneVNBrowserCommandController::SupportsCommand(int id) const {
  return IsOneVNCommands(id)
      ? onevn_command_updater_.SupportsCommand(id)
      : BrowserCommandController::SupportsCommand(id);
}

bool OneVNBrowserCommandController::IsCommandEnabled(int id) const {
  return IsOneVNCommands(id)
      ? onevn_command_updater_.IsCommandEnabled(id)
      : BrowserCommandController::IsCommandEnabled(id);
}

bool OneVNBrowserCommandController::ExecuteCommandWithDisposition(
    int id,
    WindowOpenDisposition disposition,
    base::TimeTicks time_stamp) {
  return IsOneVNCommands(id)
             ? ExecuteOneVNCommandWithDisposition(id, disposition)
             : BrowserCommandController::ExecuteCommandWithDisposition(
                   id, disposition, time_stamp);
}

void OneVNBrowserCommandController::AddCommandObserver(
    int id, CommandObserver* observer) {
  IsOneVNCommands(id)
      ? onevn_command_updater_.AddCommandObserver(id, observer)
      : BrowserCommandController::AddCommandObserver(id, observer);
}

void OneVNBrowserCommandController::RemoveCommandObserver(
    int id, CommandObserver* observer) {
  IsOneVNCommands(id)
      ? onevn_command_updater_.RemoveCommandObserver(id, observer)
      : BrowserCommandController::RemoveCommandObserver(id, observer);
}

void OneVNBrowserCommandController::RemoveCommandObserver(
    CommandObserver* observer) {
  onevn_command_updater_.RemoveCommandObserver(observer);
  BrowserCommandController::RemoveCommandObserver(observer);
}

bool OneVNBrowserCommandController::UpdateCommandEnabled(int id, bool state) {
  return IsOneVNCommands(id)
      ? onevn_command_updater_.UpdateCommandEnabled(id, state)
      : BrowserCommandController::UpdateCommandEnabled(id, state);
}

void OneVNBrowserCommandController::InitOneVNCommandState() {
  // Sync & Rewards pages doesn't work on tor(guest) session.
  // They also doesn't work on private window but they are redirected
  // to normal window in this case.
  if (!browser_->profile()->IsGuestSession()) {
#if BUILDFLAG(ONEVN_REWARDS_ENABLED)
    UpdateCommandForOneVNRewards();
#endif
    if (onevn_sync::OneVNSyncService::is_enabled())
      UpdateCommandForOneVNSync();
  }
  UpdateCommandForOneVNAdblock();
  UpdateCommandForTor();
}

void OneVNBrowserCommandController::UpdateCommandForOneVNRewards() {
  UpdateCommandEnabled(IDC_SHOW_ONEVN_REWARDS, true);
}

void OneVNBrowserCommandController::UpdateCommandForOneVNAdblock() {
  UpdateCommandEnabled(IDC_SHOW_ONEVN_ADBLOCK, true);
}

void OneVNBrowserCommandController::UpdateCommandForTor() {
  UpdateCommandEnabled(IDC_NEW_TOR_IDENTITY, true);
  UpdateCommandEnabled(IDC_NEW_OFFTHERECORD_WINDOW_TOR, true);
}

void OneVNBrowserCommandController::UpdateCommandForOneVNSync() {
  UpdateCommandEnabled(IDC_SHOW_ONEVN_SYNC, true);
}

bool OneVNBrowserCommandController::ExecuteOneVNCommandWithDisposition(
    int id, WindowOpenDisposition disposition) {
  if (!SupportsCommand(id) || !IsCommandEnabled(id))
    return false;

  if (browser_->tab_strip_model()->active_index() == TabStripModel::kNoTab)
    return true;

  DCHECK(onevn_command_updater_.IsCommandEnabled(id))
      << "Invalid/disabled command " << id;

  switch (id) {
    case IDC_SHOW_ONEVN_REWARDS:
      onevn::ShowOneVNRewards(browser_);
      break;
    case IDC_SHOW_ONEVN_ADBLOCK:
      onevn::ShowOneVNAdblock(browser_);
      break;
    case IDC_NEW_OFFTHERECORD_WINDOW_TOR:
      onevn::NewOffTheRecordWindowTor(browser_);
      break;
    case IDC_NEW_TOR_IDENTITY:
      onevn::NewTorIdentity(browser_);
      break;
    case IDC_SHOW_ONEVN_SYNC:
      onevn::ShowOneVNSync(browser_);
      break;

    default:
      LOG(WARNING) << "Received Unimplemented Command: " << id;
      break;
  }

  return true;
}

}  // namespace chrome
