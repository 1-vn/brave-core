/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_NET_COOKIE_NETWORK_DELEGATE_H_
#define ONEVN_BROWSER_NET_COOKIE_NETWORK_DELEGATE_H_

#include "onevn/browser/net/url_context.h"

namespace onevn {

bool OnCanGetCookiesForOneVNShields(std::shared_ptr<OneVNRequestInfo> ctx);
bool OnCanSetCookiesForOneVNShields(std::shared_ptr<OneVNRequestInfo> ctx);

}  // namespace onevn

#endif  // ONEVN_BROWSER_NET_COOKIE_NETWORK_DELEGATE_H_
