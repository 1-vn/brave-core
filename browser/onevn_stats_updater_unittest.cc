/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/onevn_stats_updater.h"

#include "base/time/time.h"
#include "onevn/browser/onevn_stats_updater_params.h"
#include "onevn/common/pref_names.h"
#include "onevn/components/onevn_referrals/browser/onevn_referrals_service.h"
#include "chrome/browser/browser_process.h"
#include "components/prefs/testing_pref_service.h"
#include "testing/gtest/include/gtest/gtest.h"

const char kYesterday[] = "2018-06-21";
const char kToday[] = "2018-06-22";
const char kTomorrow[] = "2018-06-23";

const int kLastWeek = 24;
const int kThisWeek = 25;
const int kNextWeek = 26;

const int kLastMonth = 5;
const int kThisMonth = 6;
const int kNextMonth = 7;

class OnevnStatsUpdaterTest: public testing::Test {
 public:
  OnevnStatsUpdaterTest() {
  }
  ~OnevnStatsUpdaterTest() override {}

  void SetUp() override {
    onevn::RegisterPrefsForOnevnStatsUpdater(testing_local_state_.registry());
    onevn::RegisterPrefsForOnevnReferralsService(
        testing_local_state_.registry());
  }

  PrefService* GetLocalState() { return &testing_local_state_; }

  void SetCurrentTimeForTest(const base::Time& current_time) {
    onevn::OnevnStatsUpdaterParams::SetCurrentTimeForTest(current_time);
  }

 private:
  TestingPrefServiceSimple testing_local_state_;
};


TEST_F(OnevnStatsUpdaterTest, IsDailyUpdateNeededLastCheckedYesterday) {
  GetLocalState()->SetString(kLastCheckYMD, kYesterday);

  onevn::OnevnStatsUpdaterParams onevn_stats_updater_params(
      GetLocalState(), kToday, kThisWeek, kThisMonth);
  ASSERT_EQ(onevn_stats_updater_params.GetDailyParam(), "true");
  onevn_stats_updater_params.SavePrefs();

  ASSERT_EQ(GetLocalState()->GetString(kLastCheckYMD), kToday);
}

TEST_F(OnevnStatsUpdaterTest, IsDailyUpdateNeededLastCheckedToday) {
  GetLocalState()->SetString(kLastCheckYMD, kToday);

  onevn::OnevnStatsUpdaterParams onevn_stats_updater_params(
      GetLocalState(), kToday, kThisWeek, kThisMonth);
  ASSERT_EQ(onevn_stats_updater_params.GetDailyParam(), "false");
  onevn_stats_updater_params.SavePrefs();

  ASSERT_EQ(GetLocalState()->GetString(kLastCheckYMD), kToday);
}

TEST_F(OnevnStatsUpdaterTest, IsDailyUpdateNeededLastCheckedTomorrow) {
  GetLocalState()->SetString(kLastCheckYMD, kTomorrow);

  onevn::OnevnStatsUpdaterParams onevn_stats_updater_params(
      GetLocalState(), kToday, kThisWeek, kThisMonth);
  ASSERT_EQ(onevn_stats_updater_params.GetDailyParam(), "false");
  onevn_stats_updater_params.SavePrefs();

  ASSERT_EQ(GetLocalState()->GetString(kLastCheckYMD), kToday);
}

TEST_F(OnevnStatsUpdaterTest, IsWeeklyUpdateNeededLastCheckedLastWeek) {
  GetLocalState()->SetInteger(kLastCheckWOY, kLastWeek);

  onevn::OnevnStatsUpdaterParams onevn_stats_updater_params(
      GetLocalState(), kToday, kThisWeek, kThisMonth);
  ASSERT_EQ(onevn_stats_updater_params.GetWeeklyParam(), "true");
  onevn_stats_updater_params.SavePrefs();

  ASSERT_EQ(GetLocalState()->GetInteger(kLastCheckWOY), kThisWeek);
}

TEST_F(OnevnStatsUpdaterTest, IsWeeklyUpdateNeededLastCheckedThisWeek) {
  GetLocalState()->SetInteger(kLastCheckWOY, kThisWeek);

  onevn::OnevnStatsUpdaterParams onevn_stats_updater_params(
      GetLocalState(), kToday, kThisWeek, kThisMonth);
  ASSERT_EQ(onevn_stats_updater_params.GetWeeklyParam(), "false");
  onevn_stats_updater_params.SavePrefs();

  ASSERT_EQ(GetLocalState()->GetInteger(kLastCheckWOY), kThisWeek);
}

TEST_F(OnevnStatsUpdaterTest, IsWeeklyUpdateNeededLastCheckedNextWeek) {
  GetLocalState()->SetInteger(kLastCheckWOY, kNextWeek);

  onevn::OnevnStatsUpdaterParams onevn_stats_updater_params(
      GetLocalState(), kToday, kThisWeek, kThisMonth);
  ASSERT_EQ(onevn_stats_updater_params.GetWeeklyParam(), "true");
  onevn_stats_updater_params.SavePrefs();

  ASSERT_EQ(GetLocalState()->GetInteger(kLastCheckWOY), kThisWeek);
}

TEST_F(OnevnStatsUpdaterTest, IsMonthlyUpdateNeededLastCheckedLastMonth) {
  GetLocalState()->SetInteger(kLastCheckMonth, kLastMonth);

  onevn::OnevnStatsUpdaterParams onevn_stats_updater_params(
      GetLocalState(), kToday, kThisWeek, kThisMonth);
  ASSERT_EQ(onevn_stats_updater_params.GetMonthlyParam(), "true");
  onevn_stats_updater_params.SavePrefs();

  ASSERT_EQ(GetLocalState()->GetInteger(kLastCheckMonth), kThisMonth);
}

TEST_F(OnevnStatsUpdaterTest, IsMonthlyUpdateNeededLastCheckedThisMonth) {
  GetLocalState()->SetInteger(kLastCheckMonth, kThisMonth);

  onevn::OnevnStatsUpdaterParams onevn_stats_updater_params(
      GetLocalState(), kToday, kThisWeek, kThisMonth);
  ASSERT_EQ(onevn_stats_updater_params.GetMonthlyParam(), "false");
  onevn_stats_updater_params.SavePrefs();

  ASSERT_EQ(GetLocalState()->GetInteger(kLastCheckMonth), kThisMonth);
}

TEST_F(OnevnStatsUpdaterTest, IsMonthlyUpdateNeededLastCheckedNextMonth) {
  GetLocalState()->SetInteger(kLastCheckMonth, kNextMonth);

  onevn::OnevnStatsUpdaterParams onevn_stats_updater_params(
      GetLocalState(), kToday, kThisWeek, kThisMonth);
  ASSERT_EQ(onevn_stats_updater_params.GetMonthlyParam(), "true");
  onevn_stats_updater_params.SavePrefs();

  ASSERT_EQ(GetLocalState()->GetInteger(kLastCheckMonth), kThisMonth);
}

// This test ensures that our weekly stats cut over on Monday
TEST_F(OnevnStatsUpdaterTest, IsWeeklyUpdateNeededOnMondayLastCheckedOnSunday) {
  base::Time::Exploded exploded;
  base::Time current_time;

  {
    // Set our local state to indicate that the last weekly check was
    // performed during ISO week #43
    GetLocalState()->SetInteger(kLastCheckWOY, 43);

    // Set date to 2018-11-04 (ISO week #44)
    exploded.hour = 0;
    exploded.minute = 0;
    exploded.second = 0;
    exploded.millisecond = 0;
    exploded.day_of_week = 0;
    exploded.year = 2018;
    exploded.month = 11;
    exploded.day_of_month = 4;

    ASSERT_TRUE(base::Time::FromLocalExploded(exploded, &current_time));

    SetCurrentTimeForTest(current_time);
    onevn::OnevnStatsUpdaterParams onevn_stats_updater_params(GetLocalState());

    // Make sure that the weekly param was set to true, since this is
    // a new ISO week (#44)
    ASSERT_EQ(onevn_stats_updater_params.GetWeeklyParam(), "true");
    onevn_stats_updater_params.SavePrefs();

    // Make sure that local state was updated to reflect this as well
    ASSERT_EQ(GetLocalState()->GetInteger(kLastCheckWOY), 44);
  }

  {
    // Now it's the next day (Monday)
    exploded.day_of_week = 1;
    exploded.day_of_month = 5;

    ASSERT_TRUE(base::Time::FromLocalExploded(exploded, &current_time));

    SetCurrentTimeForTest(current_time);
    onevn::OnevnStatsUpdaterParams onevn_stats_updater_params(GetLocalState());

    // Make sure that the weekly param was set to true, since this is
    // a new ISO week (#45)
    ASSERT_EQ(onevn_stats_updater_params.GetWeeklyParam(), "true");
    onevn_stats_updater_params.SavePrefs();

    // Make sure that local state was updated to reflect this as well
    ASSERT_EQ(GetLocalState()->GetInteger(kLastCheckWOY), 45);
  }

  {
    // Now it's the next day (Tuesday)
    exploded.day_of_week = 2;
    exploded.day_of_month = 6;

    ASSERT_TRUE(base::Time::FromLocalExploded(exploded, &current_time));

    SetCurrentTimeForTest(current_time);
    onevn::OnevnStatsUpdaterParams onevn_stats_updater_params(GetLocalState());

    // Make sure that the weekly param was set to false, since this is
    // still the same ISO week (#45)
    ASSERT_EQ(onevn_stats_updater_params.GetWeeklyParam(), "false");
    onevn_stats_updater_params.SavePrefs();

    // Make sure that local state also didn't change
    ASSERT_EQ(GetLocalState()->GetInteger(kLastCheckWOY), 45);
  }
}

TEST_F(OnevnStatsUpdaterTest, HasCorrectWeekOfInstallation) {
  base::Time::Exploded exploded;
  base::Time current_time;

  {
    // Set date to 2019-03-24 (Sunday)
    exploded.hour = 0;
    exploded.minute = 0;
    exploded.second = 0;
    exploded.millisecond = 0;
    exploded.day_of_week = 0;
    exploded.year = 2019;
    exploded.month = 3;
    exploded.day_of_month = 24;

    ASSERT_TRUE(base::Time::FromLocalExploded(exploded, &current_time));
    SetCurrentTimeForTest(current_time);

    // Make sure that week of installation is previous Monday
    onevn::OnevnStatsUpdaterParams onevn_stats_updater_params(GetLocalState());
    ASSERT_EQ(onevn_stats_updater_params.GetWeekOfInstallationParam(),
              "2019-03-18");
  }

  {
    // Set date to 2019-03-25 (Monday)
    exploded.hour = 0;
    exploded.minute = 0;
    exploded.second = 0;
    exploded.millisecond = 0;
    exploded.day_of_week = 0;
    exploded.year = 2019;
    exploded.month = 3;
    exploded.day_of_month = 25;

    ASSERT_TRUE(base::Time::FromLocalExploded(exploded, &current_time));
    SetCurrentTimeForTest(current_time);

    // Make sure that week of installation is today, since today is a
    // Monday
    onevn::OnevnStatsUpdaterParams onevn_stats_updater_params(GetLocalState());
    ASSERT_EQ(onevn_stats_updater_params.GetWeekOfInstallationParam(),
              "2019-03-25");
  }

  {
    // Set date to 2019-03-30 (Saturday)
    exploded.hour = 0;
    exploded.minute = 0;
    exploded.second = 0;
    exploded.millisecond = 0;
    exploded.day_of_week = 0;
    exploded.year = 2019;
    exploded.month = 3;
    exploded.day_of_month = 30;

    ASSERT_TRUE(base::Time::FromLocalExploded(exploded, &current_time));
    SetCurrentTimeForTest(current_time);

    // Make sure that week of installation is previous Monday
    onevn::OnevnStatsUpdaterParams onevn_stats_updater_params(GetLocalState());
    ASSERT_EQ(onevn_stats_updater_params.GetWeekOfInstallationParam(),
              "2019-03-25");
  }
}
