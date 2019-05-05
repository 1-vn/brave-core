/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/version_info.h"

namespace version_info {

std::string GetOnevnVersionWithoutChromiumMajorVersion() {
  return std::string(ONEVN_BROWSER_VERSION);
}

std::string GetOnevnVersionNumberForDisplay() {
  return std::string(ONEVN_BROWSER_VERSION) +
      "  Chromium: " + ONEVN_CHROMIUM_VERSION;
}

}  // namespace version_info
