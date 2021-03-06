/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_NET_ONEVN_AD_BLOCK_TP_NETWORK_DELEGATE_H_
#define ONEVN_BROWSER_NET_ONEVN_AD_BLOCK_TP_NETWORK_DELEGATE_H_

#include "onevn/browser/net/url_context.h"

namespace onevn {

int OnBeforeURLRequest_AdBlockTPPreWork(
    const ResponseCallback& next_callback,
    std::shared_ptr<OnevnRequestInfo> ctx);

bool GetPolyfillForAdBlock(bool allow_onevn_shields, bool allow_ads,
    const GURL& tab_origin, const GURL& gurl, std::string* new_url_spec);

}  // namespace onevn

#endif  // ONEVN_BROWSER_NET_ONEVN_AD_BLOCK_TP_NETWORK_DELEGATE_H_
