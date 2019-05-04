/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "onevn/components/onevn_rewards/browser/rewards_service.h"

#include "base/logging.h"
#include "base/time/time.h"
#include "onevn/components/onevn_rewards/common/pref_names.h"
#include "onevn/components/onevn_rewards/browser/buildflags/buildflags.h"
#include "onevn/components/onevn_rewards/browser/rewards_notification_service_impl.h"
#include "onevn/components/onevn_rewards/browser/rewards_service_observer.h"
#include "components/prefs/pref_registry_simple.h"

#if !BUILDFLAG(ONEVN_REWARDS_ENABLED)
#include "content/public/common/referrer.h"
#endif

namespace onevn_rewards {

#if !BUILDFLAG(ONEVN_REWARDS_ENABLED)
bool IsMediaLink(const GURL& url,
                 const GURL& first_party_url,
                 const content::Referrer& referrer) {
  return false;
}
#endif

RewardsService::RewardsService() {
}

RewardsService::~RewardsService() {
}

void RewardsService::AddObserver(RewardsServiceObserver* observer) {
  observers_.AddObserver(observer);
}

void RewardsService::RemoveObserver(RewardsServiceObserver* observer) {
  observers_.RemoveObserver(observer);
}

// static
void RewardsService::RegisterProfilePrefs(PrefRegistrySimple* registry) {
  registry->RegisterStringPref(prefs::kRewardsNotifications, "");
  registry->RegisterTimeDeltaPref(prefs::kRewardsNotificationTimerInterval,
                                  base::TimeDelta::FromDays(1));
  registry->RegisterTimeDeltaPref(prefs::kRewardsBackupNotificationFrequency,
                                  base::TimeDelta::FromDays(7));
  registry->RegisterTimeDeltaPref(prefs::kRewardsBackupNotificationInterval,
                                  base::TimeDelta::FromDays(7));
  registry->RegisterTimeDeltaPref(prefs::kRewardsNotificationStartupDelay,
                                  base::TimeDelta::FromSeconds(30));
  registry->RegisterBooleanPref(prefs::kRewardsBackupSucceeded, false);
  registry->RegisterBooleanPref(prefs::kRewardsUserHasFunded, false);
  registry->RegisterTimePref(prefs::kRewardsAddFundsNotification, base::Time());
  registry->RegisterBooleanPref(prefs::kOneVNRewardsEnabled, false);
  registry->RegisterBooleanPref(prefs::kOneVNRewardsEnabledMigrated, false);
}

}  // namespace onevn_rewards
