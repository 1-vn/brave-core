/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMMON_SHIELD_EXCEPTIONS_H_
#define ONEVN_COMMON_SHIELD_EXCEPTIONS_H_

class GURL;

namespace onevn {

bool IsUAWhitelisted(const GURL& gurl);
bool IsBlockedResource(const GURL& gurl);
bool IsWhitelistedCookieException(const GURL& firstPartyOrigin,
                                  const GURL& subresourceUrl,
                                  bool allow_google_auth);

}  // namespace onevn

#endif  // ONEVN_COMMON_SHIELD_EXCEPTIONS_H_
