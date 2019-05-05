/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_VERSION_INFO_VALUES_H_
#define ONEVN_BROWSER_VERSION_INFO_VALUES_H_

#include <string>

namespace version_info {
std::string GetOnevnVersionWithoutChromiumMajorVersion();
std::string GetOnevnVersionNumberForDisplay();
}  // namespace version_info

#endif  // ONEVN_BROWSER_VERSION_INFO_VALUES_H_
