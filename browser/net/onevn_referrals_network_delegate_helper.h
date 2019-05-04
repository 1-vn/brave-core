/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_NET_ONEVN_REFERRALS_NETWORK_DELEGATE_H_
#define ONEVN_BROWSER_NET_ONEVN_REFERRALS_NETWORK_DELEGATE_H_

#include "onevn/browser/net/url_context.h"

struct OneVNRequestInfo;

namespace net {
class HttpRequestHeaders;
class URLRequest;
}

namespace onevn {

int OnBeforeStartTransaction_ReferralsWork(
    net::URLRequest* request,
    net::HttpRequestHeaders* headers,
    const ResponseCallback& next_callback,
    std::shared_ptr<OneVNRequestInfo> ctx);

}  // namespace onevn

#endif  // ONEVN_BROWSER_NET_ONEVN_REFERRALS_NETWORK_DELEGATE_H_
