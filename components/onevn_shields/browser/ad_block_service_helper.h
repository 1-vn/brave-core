/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_SHIELDS_BROWSER_AD_BLOCK_SERVICE_HELPER_H_
#define ONEVN_COMPONENTS_ONEVN_SHIELDS_BROWSER_AD_BLOCK_SERVICE_HELPER_H_

#include <string>
#include <vector>

#include "onevn/vendor/ad-block/filter_list.h"

namespace onevn_shields {

std::vector<FilterList>::const_iterator FindAdBlockFilterListByUUID(
    const std::vector<FilterList>& region_lists,
    const std::string& uuid);
std::vector<FilterList>::const_iterator FindAdBlockFilterListByLocale(
    const std::vector<FilterList>& region_lists,
    const std::string& locale);

}  // namespace onevn_shields

#endif  // ONEVN_COMPONENTS_ONEVN_SHIELDS_BROWSER_AD_BLOCK_SERVICE_HELPER_H_
