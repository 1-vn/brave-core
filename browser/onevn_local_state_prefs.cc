/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/onevn_local_state_prefs.h"

#include "base/values.h"
#include "onevn/browser/onevn_stats_updater.h"
#include "onevn/browser/metrics/metrics_reporting_util.h"
#include "onevn/browser/tor/tor_profile_service.h"
#include "onevn/components/onevn_referrals/browser/onevn_referrals_service.h"
#include "onevn/components/onevn_shields/browser/ad_block_service.h"
#include "chrome/browser/first_run/first_run.h"
#include "chrome/common/pref_names.h"
#include "components/metrics/metrics_pref_names.h"
#include "components/prefs/pref_registry_simple.h"

namespace onevn {

void RegisterLocalStatePrefs(PrefRegistrySimple* registry) {
  onevn_shields::RegisterPrefsForAdBlockService(registry);
  RegisterPrefsForOneVNStatsUpdater(registry);
  RegisterPrefsForOneVNReferralsService(registry);
#if defined(OS_MACOSX)
  // Turn off super annoying 'Hold to quit'
  registry->SetDefaultPrefValue(prefs::kConfirmToQuitEnabled,
      base::Value(false));
#endif
  tor::TorProfileService::RegisterLocalStatePrefs(registry);
  RegisterPrefsForMuonMigration(registry);

  registry->SetDefaultPrefValue(
      metrics::prefs::kMetricsReportingEnabled,
      base::Value(GetDefaultPrefValueForMetricsReporting()));
}

}  // namespace onevn
