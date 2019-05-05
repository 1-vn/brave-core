/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_UTILITY_ONEVN_CONTENT_UTILITY_CLIENT_H_
#define ONEVN_UTILITY_ONEVN_CONTENT_UTILITY_CLIENT_H_

#include <string>

#include "chrome/utility/chrome_content_utility_client.h"

class OnevnContentUtilityClient : public ChromeContentUtilityClient {
 public:
  OnevnContentUtilityClient();
  ~OnevnContentUtilityClient() override;

  bool HandleServiceRequest(
      const std::string& service_name,
      service_manager::mojom::ServiceRequest request) override;

 private:
  DISALLOW_COPY_AND_ASSIGN(OnevnContentUtilityClient);
};

#endif  // ONEVN_UTILITY_ONEVN_CONTENT_UTILITY_CLIENT_H_
