/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_REWARDS_BROWSER_NET_NETWORK_HELPER_DELEGATE_H_
#define ONEVN_COMPONENTS_ONEVN_REWARDS_BROWSER_NET_NETWORK_HELPER_DELEGATE_H_

#include "onevn/browser/net/url_context.h"

namespace onevn_rewards {

int OnBeforeURLRequest(
    const onevn::ResponseCallback& next_callback,
    std::shared_ptr<onevn::OnevnRequestInfo> ctx);

}  // namespace onevn_rewards

#endif  // ONEVN_COMPONENTS_ONEVN_REWARDS_BROWSER_NET_NETWORK_HELPER_DELEGATE_H_
