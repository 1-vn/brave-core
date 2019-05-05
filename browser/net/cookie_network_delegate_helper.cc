/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/net/cookie_network_delegate_helper.h"

#include <memory>

#include "onevn/common/onevn_cookie_blocking.h"

namespace onevn {

bool OnCanGetCookiesForOnevnShields(std::shared_ptr<OnevnRequestInfo> ctx) {
  return !ShouldBlockCookie(ctx->allow_onevn_shields, ctx->allow_1p_cookies,
    ctx->allow_3p_cookies, ctx->tab_origin, ctx->request_url,
    ctx->allow_google_auth);
}

bool OnCanSetCookiesForOnevnShields(std::shared_ptr<OnevnRequestInfo> ctx) {
  return !ShouldBlockCookie(ctx->allow_onevn_shields, ctx->allow_1p_cookies,
    ctx->allow_3p_cookies, ctx->tab_origin, ctx->request_url,
    ctx->allow_google_auth);
}

}  // namespace onevn
