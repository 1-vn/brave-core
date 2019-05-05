/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_REWARDS_BROWSER_RECONCILE_INFO_H_
#define ONEVN_COMPONENTS_ONEVN_REWARDS_BROWSER_RECONCILE_INFO_H_

#include <map>
#include <string>

namespace onevn_rewards {

enum ContributionRetry {
  STEP_NO = 0,
  STEP_RECONCILE = 1,  // Phase 1
  STEP_CURRENT = 2,    // Phase 1
  STEP_PAYLOAD = 3,    // Phase 1
  STEP_REGISTER = 4,   // Phase 1
  STEP_VIEWING = 5,    // Phase 1
  STEP_WINNERS = 6,    // Phase 1
  STEP_PREPARE = 7,    // Phase 2
  STEP_PROOF = 8,      // Phase 2
  STEP_VOTE = 9,       // Phase 2
  STEP_FINAL = 10      // Phase 2
};

struct ReconcileInfo {
  ReconcileInfo();
  ~ReconcileInfo();
  ReconcileInfo(const ReconcileInfo& info);

  std::string viewing_id_;
  std::string amount_;
  ContributionRetry retry_step_;
  int retry_level_;
};

}  // namespace onevn_rewards

#endif  // ONEVN_COMPONENTS_ONEVN_REWARDS_BROWSER_RECONCILE_INFO_H_
