/* Copyright 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_UI_ONEVN_BROWSER_COMMAND_CONTROLLER_H_
#define ONEVN_BROWSER_UI_ONEVN_BROWSER_COMMAND_CONTROLLER_H_

#include "chrome/browser/ui/browser_command_controller.h"

// This namespace is needed for a chromium_src override
namespace chrome {

class OnevnBrowserCommandController : public chrome::BrowserCommandController {
 public:
  explicit OnevnBrowserCommandController(Browser* browser);

 private:
  // Overriden from CommandUpdater:
  bool SupportsCommand(int id) const override;
  bool IsCommandEnabled(int id) const override;
  bool ExecuteCommandWithDisposition(
      int id,
      WindowOpenDisposition disposition,
      base::TimeTicks time_stamp = base::TimeTicks::Now()) override;
  void AddCommandObserver(int id, CommandObserver* observer) override;
  void RemoveCommandObserver(int id, CommandObserver* observer) override;
  void RemoveCommandObserver(CommandObserver* observer) override;
  bool UpdateCommandEnabled(int id, bool state) override;

  void InitOnevnCommandState();
  void UpdateCommandForOnevnRewards();
  void UpdateCommandForOnevnAdblock();
  void UpdateCommandForTor();
  void UpdateCommandForOnevnSync();

  bool ExecuteOnevnCommandWithDisposition(int id,
                                          WindowOpenDisposition disposition);

  Browser* const browser_;

  CommandUpdaterImpl onevn_command_updater_;

  DISALLOW_COPY_AND_ASSIGN(OnevnBrowserCommandController);
};

}   // namespace chrome

#endif  // ONEVN_BROWSER_UI_ONEVN_BROWSER_COMMAND_CONTROLLER_H_
