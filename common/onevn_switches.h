/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMMON_ONEVN_SWITCHES_H_
#define ONEVN_COMMON_ONEVN_SWITCHES_H_

namespace switches {

// All switches in alphabetical order. The switches should be documented
// alongside the definition of their values in the .cc file.
extern const char kDisableOnevnExtension[];

extern const char kDisableOnevnRewardsExtension[];

extern const char kDisableOnevnUpdate[];

extern const char kDisableChromeGoogleURLTrackingClient[];

extern const char kDisablePDFJSExtension[];

extern const char kDisableTorClientUpdaterExtension[];

extern const char kDisableWebTorrentExtension[];

extern const char kDisableOnevnSync[];

extern const char kRewards[];

extern const char kUiMode[];

extern const char kUpgradeFromMuon[];

extern const char kDisableMachineId[];

extern const char kDisableEncryptionWin[];

extern const char kEnableSmartTrackingProtection[];

}  // namespace switches

#endif  // ONEVN_COMMON_ONEVN_SWITCHES_H_
