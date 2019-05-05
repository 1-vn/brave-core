/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <cmath>

#include "onevn/browser/onevn_stats_updater_params.h"

#include "base/strings/string_util.h"
#include "base/time/time.h"
#include "onevn/browser/onevn_stats_updater_util.h"
#include "onevn/common/pref_names.h"
#include "components/prefs/pref_service.h"

namespace onevn {

base::Time OnevnStatsUpdaterParams::g_current_time;

OnevnStatsUpdaterParams::OnevnStatsUpdaterParams(PrefService* pref_service)
    : OnevnStatsUpdaterParams(pref_service,
                              GetCurrentDateAsYMD(),
                              GetCurrentISOWeekNumber(),
                              GetCurrentMonth()) {
}

OnevnStatsUpdaterParams::OnevnStatsUpdaterParams(PrefService* pref_service,
                                                 const std::string& ymd,
                                                 int woy,
                                                 int month)
    : pref_service_(pref_service), ymd_(ymd), woy_(woy), month_(month) {
  LoadPrefs();
}

OnevnStatsUpdaterParams::~OnevnStatsUpdaterParams() {
}

std::string OnevnStatsUpdaterParams::GetDailyParam() const {
  return BooleanToString(
      base::CompareCaseInsensitiveASCII(ymd_, last_check_ymd_) == 1);
}

std::string OnevnStatsUpdaterParams::GetWeeklyParam() const {
  return BooleanToString(last_check_woy_ == 0 || woy_ != last_check_woy_);
}

std::string OnevnStatsUpdaterParams::GetMonthlyParam() const {
  return BooleanToString(last_check_month_ == 0 ||
                         month_ != last_check_month_);
}

std::string OnevnStatsUpdaterParams::GetFirstCheckMadeParam() const {
  return BooleanToString(!first_check_made_);
}

std::string OnevnStatsUpdaterParams::GetWeekOfInstallationParam() const {
  return week_of_installation_;
}

std::string OnevnStatsUpdaterParams::GetReferralCodeParam() const {
  return referral_promo_code_.empty() ? "none" : referral_promo_code_;
}

void OnevnStatsUpdaterParams::LoadPrefs() {
  last_check_ymd_ = pref_service_->GetString(kLastCheckYMD);
  last_check_woy_ = pref_service_->GetInteger(kLastCheckWOY);
  last_check_month_ = pref_service_->GetInteger(kLastCheckMonth);
  first_check_made_ = pref_service_->GetBoolean(kFirstCheckMade);
  week_of_installation_ = pref_service_->GetString(kWeekOfInstallation);
  if (week_of_installation_.empty())
    week_of_installation_ = GetLastMondayAsYMD();
  referral_promo_code_ = pref_service_->GetString(kReferralPromoCode);
}

void OnevnStatsUpdaterParams::SavePrefs() {
  pref_service_->SetString(kLastCheckYMD, ymd_);
  pref_service_->SetInteger(kLastCheckWOY, woy_);
  pref_service_->SetInteger(kLastCheckMonth, month_);
  pref_service_->SetBoolean(kFirstCheckMade, true);
  pref_service_->SetString(kWeekOfInstallation, week_of_installation_);
}

std::string OnevnStatsUpdaterParams::BooleanToString(bool bool_value) const {
  return bool_value ? "true" : "false";
}

std::string OnevnStatsUpdaterParams::GetCurrentDateAsYMD() const {
  return onevn::GetDateAsYMD(GetCurrentTimeNow());
}

std::string OnevnStatsUpdaterParams::GetLastMondayAsYMD() const {
  base::Time now = GetCurrentTimeNow();
  base::Time::Exploded exploded;
  now.LocalExplode(&exploded);

  int days_adjusted =
      (exploded.day_of_week == 0) ? 6 : exploded.day_of_week - 1;
  base::Time last_monday = base::Time::FromJsTime(
      now.ToJsTime() - (days_adjusted * base::Time::kMillisecondsPerDay));

  return onevn::GetDateAsYMD(last_monday);
}

int OnevnStatsUpdaterParams::GetCurrentMonth() const {
  base::Time now = GetCurrentTimeNow();
  base::Time::Exploded exploded;
  now.LocalExplode(&exploded);
  return exploded.month;
}

int OnevnStatsUpdaterParams::GetCurrentISOWeekNumber() const {
  base::Time now = GetCurrentTimeNow();
  base::Time::Exploded now_exploded;
  now.LocalExplode(&now_exploded);
  now_exploded.hour = 0;
  now_exploded.minute = 0;
  now_exploded.second = 0;
  now_exploded.millisecond = 0;
  now_exploded.day_of_month =
      now_exploded.day_of_month + 3 - ((now_exploded.day_of_week + 6) % 7);

  base::Time now_adjusted;
  if (!base::Time::FromLocalExploded(now_exploded, &now_adjusted))
    return 0;

  base::Time::Exploded jan4_exploded = {0};
  jan4_exploded.year = now_exploded.year;
  jan4_exploded.month = 1;
  jan4_exploded.day_of_week = 0;
  jan4_exploded.day_of_month = 4;
  jan4_exploded.hour = 0;
  jan4_exploded.minute = 0;
  jan4_exploded.second = 0;
  jan4_exploded.millisecond = 0;

  base::Time jan4_time;
  if (!base::Time::FromLocalExploded(jan4_exploded, &jan4_time))
    return 0;

  return 1 + std::round(
                 ((now_adjusted.ToJsTime() - jan4_time.ToJsTime()) / 86400000 -
                  3 + (jan4_exploded.day_of_week + 6) % 7) /
                 7);
}

base::Time OnevnStatsUpdaterParams::GetCurrentTimeNow() const {
  return g_current_time.is_null() ? base::Time::Now() : g_current_time;
}

// static
void OnevnStatsUpdaterParams::SetCurrentTimeForTest(
    const base::Time& current_time) {
  g_current_time = current_time;
}

}  // namespace onevn
