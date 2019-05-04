/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_ADS_BROWSER_TEST_UTIL_H_
#define ONEVN_COMPONENTS_ONEVN_ADS_BROWSER_TEST_UTIL_H_

#include <memory>

#include "base/files/file_path.h"

class KeyedService;
class Profile;

namespace onevn_ads {

std::unique_ptr<Profile> CreateOneVNAdsProfile(const base::FilePath& path);

}  // namespace onevn_ads

#endif  // ONEVN_COMPONENTS_ONEVN_ADS_BROWSER_TEST_UTIL_H_
