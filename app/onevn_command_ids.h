/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_APP_ONEVN_COMMAND_IDS_H_
#define ONEVN_APP_ONEVN_COMMAND_IDS_H_

// First onevn id must be higher than last chrome command.
// Check chrome/app/chrome_command_ids.h when rebase.
// ID of IDC_ONEVN_COMANDS_START and first onevn command should be same.
#define IDC_ONEVN_COMMANDS_START 56000
#define IDC_SHOW_ONEVN_REWARDS   56000
#define IDC_SHOW_ONEVN_ADBLOCK   56001
#define IDC_NEW_TOR_IDENTITY     56002
#define IDC_NEW_OFFTHERECORD_WINDOW_TOR 56003
#define IDC_CONTENT_CONTEXT_OPENLINKTOR 56004
#define IDC_SHOW_ONEVN_SYNC      56005

#define IDC_ONEVN_COMMANDS_LAST  57000

#endif  // ONEVN_APP_ONEVN_COMMAND_IDS_H_
