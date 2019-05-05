/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_NET_ONEVN_PROFILE_NETWORK_DELEGATE_H_
#define ONEVN_BROWSER_NET_ONEVN_PROFILE_NETWORK_DELEGATE_H_

#include "onevn/browser/net/onevn_network_delegate_base.h"

class OnevnProfileNetworkDelegate : public OnevnNetworkDelegateBase {
 public:
  OnevnProfileNetworkDelegate(extensions::EventRouterForwarder* event_router);
  ~OnevnProfileNetworkDelegate() override;

  DISALLOW_COPY_AND_ASSIGN(OnevnProfileNetworkDelegate);
};

#endif  // ONEVN_BROWSER_NET_ONEVN_PROFILE_NETWORK_DELEGATE_H_
