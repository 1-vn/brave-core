/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_NET_ONEVN_SITE_HACKS_NETWORK_DELEGATE_H_
#define ONEVN_BROWSER_NET_ONEVN_SITE_HACKS_NETWORK_DELEGATE_H_

#include "onevn/browser/net/url_context.h"

namespace net {
class URLRequest;
}

namespace onevn {

int OnBeforeURLRequest_SiteHacksWork(
    const ResponseCallback& next_callback,
    std::shared_ptr<OnevnRequestInfo> ctx);

int OnBeforeStartTransaction_SiteHacksWork(net::URLRequest* request,
    net::HttpRequestHeaders* headers,
    const ResponseCallback& next_callback,
    std::shared_ptr<OnevnRequestInfo> ctx);

}  // namespace onevn

#endif  // ONEVN_BROWSER_NET_ONEVN_SITE_HACKS_NETWORK_DELEGATE_H_
