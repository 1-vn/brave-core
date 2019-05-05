/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_REWARDS_BROWSER_RECURRING_DONATION_H_
#define ONEVN_COMPONENTS_ONEVN_REWARDS_BROWSER_RECURRING_DONATION_H_

#include <string>

// TODO(nejczdovc): Rename to RecurringTip

namespace onevn_rewards {

struct RecurringDonation {
  RecurringDonation();
  ~RecurringDonation();
  RecurringDonation(const RecurringDonation& data);

  std::string publisher_key;
  double amount = 0;
  uint32_t added_date = 0;
};

}  // namespace onevn_rewards

#endif  // ONEVN_COMPONENTS_ONEVN_REWARDS_BROWSER_RECURRING_DONATION_H_
