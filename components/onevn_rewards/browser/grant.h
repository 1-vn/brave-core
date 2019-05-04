/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_REWARDS_BROWSER_GRANT_H_
#define ONEVN_COMPONENTS_ONEVN_REWARDS_BROWSER_GRANT_H_

#include <string>

namespace onevn_rewards {

struct Grant {
  Grant();
  ~Grant();
  Grant(const Grant& properties);

  std::string altcurrency;
  std::string probi;
  std::string promotionId;
  uint64_t expiryTime;
  std::string type;
};

}  // namespace onevn_rewards

#endif  // ONEVN_COMPONENTS_ONEVN_REWARDS_BROWSER_GRANT_H_
