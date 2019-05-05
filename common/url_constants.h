/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMMON_URL_CONSTANTS_H_
#define ONEVN_COMMON_URL_CONSTANTS_H_

extern const char kChromeExtensionScheme[];
extern const char kOnevnUIScheme[];
extern const char kMagnetScheme[];
extern const char kWidevineMoreInfoURL[];
extern const char kWidevineTOS[];

// This is introduced to replace |kDownloadChromeUrl| in
// outdated_upgrade_bubble_view.cc"
// |kDownloadChromeUrl| couldn't be replaced with char array because array
// should be initialized with initialize list or string literal.
// So, this macro is used.
#define kDownloadOnevnUrl "https://www.1-vn.com/download"

#endif  // ONEVN_COMMON_URL_CONSTANTS_H_
