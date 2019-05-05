/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
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
bool IsOnevnCommands(int id) {
  return id >= IDC_ONEVN_COMMANDS_START && id <= IDC_ONEVN_COMMANDS_LAST;
}
}

namespace chrome {

OnevnBrowserCommandController::OnevnBrowserCommandController(Browser* browser)
    : BrowserCommandController(browser),
      browser_(browser),
      onevn_command_updater_(nullptr) {
  InitOnevnCommandState();
}

bool OnevnBrowserCommandController::SupportsCommand(int id) const {
  return IsOnevnCommands(id)
      ? onevn_command_updater_.SupportsCommand(id)
      : BrowserCommandController::SupportsCommand(id);
}

bool OnevnBrowserCommandController::IsCommandEnabled(int id) const {
  return IsOnevnCommands(id)
      ? onevn_command_updater_.IsCommandEnabled(id)
      : BrowserCommandController::IsCommandEnabled(id);
}

bool OnevnBrowserCommandController::ExecuteCommandWithDisposition(
    int id,
    WindowOpenDisposition disposition,
    base::TimeTicks time_stamp) {
  return IsOnevnCommands(id)
             ? ExecuteOnevnCommandWithDisposition(id, disposition)
             : BrowserCommandController::ExecuteCommandWithDisposition(
                   id, disposition, time_stamp);
}

void OnevnBrowserCommandController::AddCommandObserver(
    int id, CommandObserver* observer) {
  IsOnevnCommands(id)
      ? onevn_command_updater_.AddCommandObserver(id, observer)
      : BrowserCommandController::AddCommandObserver(id, observer);
}

void OnevnBrowserCommandController::RemoveCommandObserver(
    int id, CommandObserver* observer) {
  IsOnevnCommands(id)
      ? onevn_command_updater_.RemoveCommandObserver(id, observer)
      : BrowserCommandController::RemoveCommandObserver(id, observer);
}

void OnevnBrowserCommandController::RemoveCommandObserver(
    CommandObserver* observer) {
  onevn_command_updater_.RemoveCommandObserver(observer);
  BrowserCommandController::RemoveCommandObserver(observer);
}

bool OnevnBrowserCommandController::UpdateCommandEnabled(int id, bool state) {
  return IsOnevnCommands(id)
      ? onevn_command_updater_.UpdateCommandEnabled(id, state)
      : BrowserCommandController::UpdateCommandEnabled(id, state);
}

void OnevnBrowserCommandController::InitOnevnCommandState() {
  // Sync & Rewards pages doesn't work on tor(guest) session.
  // They also doesn't work on private window but they are redirected
  // to normal window in this case.
  if (!browser_->profile()->IsGuestSession()) {
#if BUILDFLAG(ONEVN_REWARDS_ENABLED)
    UpdateCommandForOnevnRewards();
#endif
    if (onevn_sync::OnevnSyncService::is_enabled())
      UpdateCommandForOnevnSync();
  }
  UpdateCommandForOnevnAdblock();
  UpdateCommandForTor();
}

void OnevnBrowserCommandController::UpdateCommandForOnevnRewards() {
  UpdateCommandEnabled(IDC_SHOW_ONEVN_REWARDS, true);
}

void OnevnBrowserCommandController::UpdateCommandForOnevnAdblock() {
  UpdateCommandEnabled(IDC_SHOW_ONEVN_ADBLOCK, true);
}

void OnevnBrowserCommandController::UpdateCommandForTor() {
  UpdateCommandEnabled(IDC_NEW_TOR_IDENTITY, true);
  UpdateCommandEnabled(IDC_NEW_OFFTHERECORD_WINDOW_TOR, true);
}

void OnevnBrowserCommandController::UpdateCommandForOnevnSync() {
  UpdateCommandEnabled(IDC_SHOW_ONEVN_SYNC, true);
}

bool OnevnBrowserCommandController::ExecuteOnevnCommandWithDisposition(
    int id, WindowOpenDisposition disposition) {
  if (!SupportsCommand(id) || !IsCommandEnabled(id))
    return false;

  if (browser_->tab_strip_model()->active_index() == TabStripModel::kNoTab)
    return true;

  DCHECK(onevn_command_updater_.IsCommandEnabled(id))
      << "Invalid/disabled command " << id;

  switch (id) {
    case IDC_SHOW_ONEVN_REWARDS:
      onevn::ShowOnevnRewards(browser_);
      break;
    case IDC_SHOW_ONEVN_ADBLOCK:
      onevn::ShowOnevnAdblock(browser_);
      break;
    case IDC_NEW_OFFTHERECORD_WINDOW_TOR:
      onevn::NewOffTheRecordWindowTor(browser_);
      break;
    case IDC_NEW_TOR_IDENTITY:
      onevn::NewTorIdentity(browser_);
      break;
    case IDC_SHOW_ONEVN_SYNC:
      onevn::ShowOnevnSync(browser_);
      break;

    default:
      LOG(WARNING) << "Received Unimplemented Command: " << id;
      break;
  }

  return true;
}

}  // namespace chrome
