/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_NET_COOKIE_NETWORK_DELEGATE_H_
#define ONEVN_BROWSER_NET_COOKIE_NETWORK_DELEGATE_H_

#include "onevn/browser/net/url_context.h"

namespace onevn {

bool OnCanGetCookiesForOnevnShields(std::shared_ptr<OnevnRequestInfo> ctx);
bool OnCanSetCookiesForOnevnShields(std::shared_ptr<OnevnRequestInfo> ctx);

}  // namespace onevn

#endif  // ONEVN_BROWSER_NET_COOKIE_NETWORK_DELEGATE_H_
