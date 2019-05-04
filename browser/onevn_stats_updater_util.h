/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_ONEVN_STATS_UPDATER_UTIL_H_
#define ONEVN_BROWSER_ONEVN_STATS_UPDATER_UTIL_H_

#include <string>

#include "base/time/time.h"

namespace onevn {

std::string GetDateAsYMD(const base::Time& time);

}  // namespace onevn

#endif  // ONEVN_BROWSER_ONEVN_STATS_UPDATER_UTIL_H_
