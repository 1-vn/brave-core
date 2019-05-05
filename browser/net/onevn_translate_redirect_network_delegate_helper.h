/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_NET_ONEVN_TRANSLATE_REDIRECT_NETWORK_DELEGATE_HELPER_H_
#define ONEVN_BROWSER_NET_ONEVN_TRANSLATE_REDIRECT_NETWORK_DELEGATE_HELPER_H_

#include <memory>
#include "onevn/browser/net/url_context.h"

namespace onevn {

int OnBeforeURLRequest_TranslateRedirectWork(
    const ResponseCallback& next_callback,
    std::shared_ptr<OnevnRequestInfo> ctx);

}  // namespace onevn

#endif  // ONEVN_BROWSER_NET_ONEVN_TRANSLATE_REDIRECT_NETWORK_DELEGATE_HELPER_H_
