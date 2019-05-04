/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_WEBTORRENT_BROWSER_NET_ONEVN_TORRENT_REDIRECT_NETWORK_DELEGATE_HELPER_H_
#define ONEVN_COMPONENTS_ONEVN_WEBTORRENT_BROWSER_NET_ONEVN_TORRENT_REDIRECT_NETWORK_DELEGATE_HELPER_H_

#include "chrome/browser/net/chrome_network_delegate.h"
#include "onevn/browser/net/url_context.h"

namespace onevn {
struct OneVNRequestInfo;
}

namespace net {
class URLRequest;
}

namespace webtorrent {

int OnHeadersReceived_TorrentRedirectWork(
    net::URLRequest* request,
    const net::HttpResponseHeaders* original_response_headers,
    scoped_refptr<net::HttpResponseHeaders>* override_response_headers,
    GURL* allowed_unsafe_redirect_url,
    const onevn::ResponseCallback& next_callback,
    std::shared_ptr<onevn::OneVNRequestInfo> ctx);

}  // namespace webtorrent

#endif  // ONEVN_COMPONENTS_ONEVN_WEBTORRENT_BROWSER_NET_ONEVN_TORRENT_REDIRECT_NETWORK_DELEGATE_HELPER_H_
