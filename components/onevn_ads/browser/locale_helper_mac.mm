/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/components/onevn_ads/browser/locale_helper_mac.h"

#import <Cocoa/Cocoa.h>

namespace onevn_ads {

LocaleHelperMac::LocaleHelperMac() = default;

LocaleHelperMac::~LocaleHelperMac() = default;

std::string LocaleHelperMac::GetLocale() const {
  NSString *locale = [[NSLocale preferredLanguages] firstObject];
  return std::string([locale UTF8String]);
}

LocaleHelperMac* LocaleHelperMac::GetInstance() {
  return base::Singleton<LocaleHelperMac>::get();
}

LocaleHelper* LocaleHelper::GetInstance() {
  return LocaleHelperMac::GetInstance();
}

}  // namespace onevn_ads
