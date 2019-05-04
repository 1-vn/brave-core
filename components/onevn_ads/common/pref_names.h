/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_ADS_COMMON_PREF_NAMES_H_
#define ONEVN_COMPONENTS_ONEVN_ADS_COMMON_PREF_NAMES_H_

namespace onevn_ads {

namespace prefs {

extern const char kOneVNAdsEnabled[];
extern const char kOneVNAdsPerHour[];
extern const char kOneVNAdsPerDay[];
extern const char kOneVNAdsIdleThreshold[];

extern const char kOneVNAdShouldShowFirstLaunchNotification[];
extern const char kOneVNAdsLaunchNotificationTimestamp[];

extern const int kOneVNAdsPrefsDefaultVersion;
extern const int kOneVNAdsPrefsCurrentVersion;
extern const char kOneVNAdsPrefsVersion[];
extern const char kOneVNAdsPrefsMigratedFrom62[];

}  // namespace prefs

}  // namespace onevn_ads

#endif  // ONEVN_COMPONENTS_ONEVN_ADS_COMMON_PREF_NAMES_H_
