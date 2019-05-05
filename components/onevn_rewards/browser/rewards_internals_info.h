/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_REWARDS_BROWSER_REWARDS_INTERNALS_INFO_H_
#define ONEVN_COMPONENTS_ONEVN_REWARDS_BROWSER_REWARDS_INTERNALS_INFO_H_

#include <map>
#include <string>

#include "onevn/components/onevn_rewards/browser/reconcile_info.h"

namespace onevn_rewards {

struct RewardsInternalsInfo {
  RewardsInternalsInfo();
  ~RewardsInternalsInfo();
  RewardsInternalsInfo(const RewardsInternalsInfo& info);

  std::string payment_id;
  bool is_key_info_seed_valid;
  std::string persona_id;
  std::string user_id;
  uint64_t boot_stamp;

  std::map<std::string, ReconcileInfo> current_reconciles;
};

}  // namespace onevn_rewards

#endif  // ONEVN_COMPONENTS_ONEVN_REWARDS_BROWSER_REWARDS_INTERNALS_INFO_H_
