/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/components/onevn_rewards/common/pref_names.h"

namespace onevn_rewards {
namespace prefs {

const char kOnevnRewardsEnabled[] = "onevn.rewards.enabled";
const char kOnevnRewardsEnabledMigrated[] = "onevn.rewards.enabled_migrated";
const char kRewardsNotifications[] = "onevn.rewards.notifications";
const char kRewardsNotificationTimerInterval[] = "onevn.rewards.notification_timer_interval";
const char kRewardsBackupNotificationFrequency[] =
    "onevn.rewards.backup_notification_frequency";
const char kRewardsBackupNotificationInterval[] =
    "onevn.rewards.backup_notification_interval";
const char kRewardsBackupSucceeded[] = "onevn.rewards.backup_succeeded";
const char kRewardsUserHasFunded[] = "onevn.rewards.user_has_funded";
const char kRewardsAddFundsNotification[] = "onevn.rewards.add_funds_notification";
const char kRewardsNotificationStartupDelay[] = "onevn.rewards.notification_startup_delay";

}  // namespace prefs
}  // namespace onevn_rewards
