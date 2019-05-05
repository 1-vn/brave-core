/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/components/onevn_ads/common/pref_names.h"

namespace onevn_ads {

namespace prefs {

const char kOnevnAdsEnabled[] = "onevn.onevn_ads.enabled";

const char kOnevnAdsPerHour[] = "onevn.onevn_ads.ads_per_hour";
const char kOnevnAdsPerDay[] = "onevn.onevn_ads.ads_per_day";
const char kOnevnAdsIdleThreshold[] = "onevn.onevn_ads.idle_threshold";

const char kOnevnAdShouldShowFirstLaunchNotification[] =
    "onevn.onevn_ads.should_show_first_launch_notification";
const char kOnevnAdsLaunchNotificationTimestamp[] =
    "onevn.onevn_ads.launch_notification_timestamp";

const int kOnevnAdsPrefsDefaultVersion = 1;
const int kOnevnAdsPrefsCurrentVersion = 2;
const char kOnevnAdsPrefsVersion[] = "onevn.onevn_ads.prefs.version";
const char kOnevnAdsPrefsMigratedFrom62[] =
    "onevn.onevn_ads.prefs.migrated.from_0_62.x";

}  // namespace prefs

}  // namespace onevn_ads
