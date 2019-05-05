/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_ADS_COMMON_PREF_NAMES_H_
#define ONEVN_COMPONENTS_ONEVN_ADS_COMMON_PREF_NAMES_H_

namespace onevn_ads {

namespace prefs {

extern const char kOnevnAdsEnabled[];
extern const char kOnevnAdsPerHour[];
extern const char kOnevnAdsPerDay[];
extern const char kOnevnAdsIdleThreshold[];

extern const char kOnevnAdShouldShowFirstLaunchNotification[];
extern const char kOnevnAdsLaunchNotificationTimestamp[];

extern const int kOnevnAdsPrefsDefaultVersion;
extern const int kOnevnAdsPrefsCurrentVersion;
extern const char kOnevnAdsPrefsVersion[];
extern const char kOnevnAdsPrefsMigratedFrom62[];

}  // namespace prefs

}  // namespace onevn_ads

#endif  // ONEVN_COMPONENTS_ONEVN_ADS_COMMON_PREF_NAMES_H_
