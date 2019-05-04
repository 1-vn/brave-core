/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_REWARDS_COMMON_PREF_NAMES_H_
#define ONEVN_COMPONENTS_ONEVN_REWARDS_COMMON_PREF_NAMES_H_

namespace onevn_rewards {
namespace prefs {

extern const char kOneVNRewardsEnabled[];
extern const char kOneVNRewardsEnabledMigrated[];
extern const char kRewardsNotifications[];
extern const char kRewardsNotificationTimerInterval[];
extern const char kRewardsBackupNotificationFrequency[];
extern const char kRewardsBackupNotificationInterval[];
extern const char kRewardsBackupSucceeded[];
extern const char kRewardsUserHasFunded[];
extern const char kRewardsAddFundsNotification[];
extern const char kRewardsNotificationStartupDelay[];

}  // namespace prefs
}  // namespace onevn_rewards

#endif  // ONEVN_COMPONENTS_ONEVN_REWARDS_COMMON_PREF_NAMES_H_
