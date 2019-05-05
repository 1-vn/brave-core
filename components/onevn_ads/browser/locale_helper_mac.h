/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_BROWSER_ONEVN_ADS_LOCALE_HELPER_MAC_H_
#define ONEVN_COMPONENTS_BROWSER_ONEVN_ADS_LOCALE_HELPER_MAC_H_

#include <string>

#include "onevn/components/onevn_ads/browser/locale_helper.h"

namespace onevn_ads {

class LocaleHelperMac : public LocaleHelper {
 public:
  LocaleHelperMac();
  ~LocaleHelperMac() override;

  static LocaleHelperMac* GetInstance();

 private:
  friend struct base::DefaultSingletonTraits<LocaleHelperMac>;

  // LocaleHelperMac impl
  std::string GetLocale() const override;

  DISALLOW_COPY_AND_ASSIGN(LocaleHelperMac);
};

}  // namespace onevn_ads

#endif  // ONEVN_COMPONENTS_BROWSER_ONEVN_ADS_LOCALE_HELPER_MAC_H_
