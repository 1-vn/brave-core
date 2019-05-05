/* Copyright 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMMON_ONEVN_CONTENT_CLIENT_H_
#define ONEVN_COMMON_ONEVN_CONTENT_CLIENT_H_

#include "chrome/common/chrome_content_client.h"

class OnevnContentClient : public ChromeContentClient {
 public:
  OnevnContentClient();
  ~OnevnContentClient() override;

  void AddAdditionalSchemes(Schemes* schemes) override;
};

#endif  // ONEVN_COMMON_ONEVN_CONTENT_CLIENT_H_
