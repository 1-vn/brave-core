/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/ui/views/onevn_actions/onevn_actions_container.h"
#include "onevn/browser/ui/views/location_bar/onevn_location_bar_view.h"
#include "onevn/common/extensions/extension_constants.h"
#include "onevn/common/pref_names.h"
#include "onevn/components/onevn_rewards/common/pref_names.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/chrome_notification_types.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "chrome/browser/profiles/profile_window.h"
#include "chrome/browser/search_engines/template_url_service_factory.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_finder.h"
#include "chrome/browser/ui/browser_list.h"
#include "chrome/browser/ui/views/frame/browser_view.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/test/base/search_test_utils.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/notification_service.h"
#include "content/public/test/test_utils.h"

class OnevnActionsContainerTest : public InProcessBrowserTest {
 public:
  OnevnActionsContainerTest() = default;
  ~OnevnActionsContainerTest() override = default;

  void SetUpOnMainThread() override {
    Init(browser());
  }

  void Init(Browser* browser) {
    BrowserView* browser_view =
        BrowserView::GetBrowserViewForBrowser(browser);
    ASSERT_NE(browser_view, nullptr);
    OnevnLocationBarView* onevn_location_bar_view =
        static_cast<OnevnLocationBarView*>(browser_view->GetLocationBarView());
    ASSERT_NE(onevn_location_bar_view, nullptr);
    onevn_actions_ = onevn_location_bar_view->onevn_actions_;
    ASSERT_NE(onevn_actions_, nullptr);
    prefs_ = browser->profile()->GetPrefs();
  }

  void CheckOnevnRewardsActionShown(bool expected_shown) {
    const bool shown =
        onevn_actions_->IsActionShown(onevn_rewards_extension_id);
    ASSERT_EQ(shown, expected_shown);
  }

 protected:
  OnevnActionsContainer* onevn_actions_;
  PrefService* prefs_;
  DISALLOW_COPY_AND_ASSIGN(OnevnActionsContainerTest);
};

IN_PROC_BROWSER_TEST_F(OnevnActionsContainerTest, HideOnevnRewardsAction) {
  // By default the action should be shown.
  EXPECT_FALSE(prefs_->GetBoolean(onevn_rewards::prefs::kOnevnRewardsEnabled));
  EXPECT_FALSE(prefs_->GetBoolean(kHideOnevnRewardsButton));
  CheckOnevnRewardsActionShown(true);

  // Set to hide.
  prefs_->SetBoolean(kHideOnevnRewardsButton, true);
  CheckOnevnRewardsActionShown(false);

  // Set to show.
  prefs_->SetBoolean(kHideOnevnRewardsButton, false);
  CheckOnevnRewardsActionShown(true);

  // Set to hide.
  prefs_->SetBoolean(kHideOnevnRewardsButton, true);
  CheckOnevnRewardsActionShown(false);

  // Enable Onevn Rewards.
  prefs_->SetBoolean(onevn_rewards::prefs::kOnevnRewardsEnabled, true);
  CheckOnevnRewardsActionShown(true);

  // Toggle to show and back to hide.
  prefs_->SetBoolean(kHideOnevnRewardsButton, false);
  prefs_->SetBoolean(kHideOnevnRewardsButton, true);
  CheckOnevnRewardsActionShown(true);

  // Disable Onevn Rewards.
  prefs_->SetBoolean(onevn_rewards::prefs::kOnevnRewardsEnabled, false);
  CheckOnevnRewardsActionShown(false);
}

IN_PROC_BROWSER_TEST_F(OnevnActionsContainerTest,
                       OnevnRewadsActionHiddenInGuestSession) {
    // By default the action should be shown.
  EXPECT_FALSE(prefs_->GetBoolean(onevn_rewards::prefs::kOnevnRewardsEnabled));
  EXPECT_FALSE(prefs_->GetBoolean(kHideOnevnRewardsButton));
  CheckOnevnRewardsActionShown(true);

  // Open a Guest window.
  EXPECT_EQ(1U, BrowserList::GetInstance()->size());
  content::WindowedNotificationObserver browser_creation_observer(
      chrome::NOTIFICATION_BROWSER_OPENED,
      content::NotificationService::AllSources());
  profiles::SwitchToGuestProfile(ProfileManager::CreateCallback());
  base::RunLoop().RunUntilIdle();
  browser_creation_observer.Wait();
  EXPECT_EQ(2U, BrowserList::GetInstance()->size());

  // Retrieve the new Guest profile.
  Profile* guest = g_browser_process->profile_manager()->GetProfileByPath(
      ProfileManager::GetGuestProfilePath());
  // The BrowsingDataRemover needs a loaded TemplateUrlService or else it hangs
  // on to a CallbackList::Subscription forever.
  search_test_utils::WaitForTemplateURLServiceToLoad(
        TemplateURLServiceFactory::GetForProfile(guest));

  // Access the browser with the Guest profile and re-init test for it.
  Browser* browser = chrome::FindAnyBrowser(guest, true);
  EXPECT_TRUE(browser);
  Init(browser);
  CheckOnevnRewardsActionShown(false);
}
