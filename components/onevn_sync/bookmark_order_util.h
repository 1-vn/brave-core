/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_SYNC_BOOKMARK_ORDER_UTIL_H_
#define ONEVN_COMPONENTS_ONEVN_SYNC_BOOKMARK_ORDER_UTIL_H_

#include <string>
#include <vector>

namespace onevn_sync {

  std::vector<int> OrderToIntVect(const std::string& s);
  bool CompareOrder(const std::string& left, const std::string& right);

} // namespace onevn_sync

#endif // ONEVN_COMPONENTS_ONEVN_SYNC_BOOKMARK_ORDER_UTIL_H_
