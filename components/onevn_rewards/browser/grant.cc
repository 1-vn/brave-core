/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/components/onevn_rewards/browser/grant.h"

namespace onevn_rewards {

Grant::Grant() : expiryTime(0) {}

Grant::~Grant() {}

Grant::Grant(const Grant &properties) {
  altcurrency = properties.altcurrency;
  probi = properties.probi;
  promotionId = properties.promotionId;
  expiryTime = properties.expiryTime;
  type = properties.type;
}

}  // namespace onevn_rewards
