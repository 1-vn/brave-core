/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_NET_ONEVN_PROFILE_NETWORK_DELEGATE_H_
#define ONEVN_BROWSER_NET_ONEVN_PROFILE_NETWORK_DELEGATE_H_

#include "onevn/browser/net/onevn_network_delegate_base.h"

class OneVNProfileNetworkDelegate : public OneVNNetworkDelegateBase {
 public:
  OneVNProfileNetworkDelegate(extensions::EventRouterForwarder* event_router);
  ~OneVNProfileNetworkDelegate() override;

  DISALLOW_COPY_AND_ASSIGN(OneVNProfileNetworkDelegate);
};

#endif  // ONEVN_BROWSER_NET_ONEVN_PROFILE_NETWORK_DELEGATE_H_
