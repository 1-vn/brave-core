/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMMON_ONEVN_COOKIE_BLOCKING_H_
#define ONEVN_COMMON_ONEVN_COOKIE_BLOCKING_H_

class GURL;

bool ShouldBlockCookie(bool allow_onevn_shields, bool allow_1p_cookies,
    bool allow_3p_cookies, const GURL& primary_url, const GURL& url,
    bool allow_google_auth);

#endif  // ONEVN_COMMON_ONEVN_COOKIE_BLOCKING_H_
