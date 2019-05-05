/* Copyright 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/common/onevn_content_client.h"

#include "content/public/common/url_constants.h"

OnevnContentClient::OnevnContentClient() {}

OnevnContentClient::~OnevnContentClient() {}

void OnevnContentClient::AddAdditionalSchemes(Schemes* schemes) {
  ChromeContentClient::AddAdditionalSchemes(schemes);
  schemes->standard_schemes.push_back(content::kOnevnUIScheme);
  schemes->secure_schemes.push_back(content::kOnevnUIScheme);
  schemes->cors_enabled_schemes.push_back(content::kOnevnUIScheme);
  schemes->savable_schemes.push_back(content::kOnevnUIScheme);
}
