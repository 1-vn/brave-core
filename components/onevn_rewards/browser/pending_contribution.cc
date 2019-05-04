/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "onevn/components/onevn_rewards/browser/pending_contribution.h"

namespace onevn_rewards {

PendingContribution::PendingContribution() :
  amount(0),
  added_date(0),
  reconcile_date(0) {
}

PendingContribution::~PendingContribution() { }

}  // namespace onevn_rewards
