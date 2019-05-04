/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef COMPONENTS_ONEVN_SHIELDS_BROWSER_ADBLOCK_INTERCEPTOR_H_
#define COMPONENTS_ONEVN_SHIELDS_BROWSER_ADBLOCK_INTERCEPTOR_H_

#include "net/url_request/url_request_interceptor.h"

namespace onevn_shields {

// Intercepts certain requests and blocks them by silently returning 200 OK
// and not allowing them to hit the network.
class AdBlockInterceptor : public net::URLRequestInterceptor {
 public:
  AdBlockInterceptor();
  ~AdBlockInterceptor() override;

 protected:
  // net::URLRequestInterceptor:
  net::URLRequestJob* MaybeInterceptRequest(
      net::URLRequest* request,
      net::NetworkDelegate* network_delegate) const override;
 private:
  DISALLOW_COPY_AND_ASSIGN(AdBlockInterceptor);
};

}  // namespace onevn_shields

#endif  // COMPONENTS_ONEVN_SHIELDS_BROWSER_ADBLOCK_INTERCEPTOR_H_
