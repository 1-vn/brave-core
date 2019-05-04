/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import rewardsPanelActions from '../actions/rewardsPanelActions'

chrome.onevnRewards.getAllNotifications((list: RewardsExtension.Notification[]) => {
  rewardsPanelActions.onAllNotifications(list)
})

chrome.onevnRewards.onWalletInitialized.addListener((result: RewardsExtension.Result) => {
  rewardsPanelActions.onWalletInitialized(result)
})

chrome.onevnRewards.onPublisherData.addListener((windowId: number, publisher: RewardsExtension.Publisher) => {
  rewardsPanelActions.onPublisherData(windowId, publisher)

  // Get publisher amounts
  if (publisher && publisher.publisher_key) {
    chrome.onevnRewards.getPublisherBanner(publisher.publisher_key, ((banner: RewardsExtension.PublisherBanner) => {
      rewardsPanelActions.onPublisherBanner(banner)
    }))
  }
})

chrome.onevnRewards.onWalletProperties.addListener((properties: RewardsExtension.WalletProperties) => {
  rewardsPanelActions.onWalletProperties(properties)
})

chrome.onevnRewards.onCurrentReport.addListener((properties: RewardsExtension.Report) => {
  rewardsPanelActions.onCurrentReport(properties)
})

chrome.onevnRewards.onGrant.addListener((properties: RewardsExtension.GrantResponse) => {
  rewardsPanelActions.onGrant(properties)
})

chrome.onevnRewards.onGrantCaptcha.addListener((captcha: RewardsExtension.Captcha) => {
  rewardsPanelActions.onGrantCaptcha(captcha)
})

chrome.onevnRewards.onGrantFinish.addListener((properties: RewardsExtension.GrantFinish) => {
  rewardsPanelActions.onGrantFinish(properties)
})

chrome.rewardsNotifications.onNotificationAdded.addListener((id: string, type: number, timestamp: number, args: string[]) => {
  rewardsPanelActions.onNotificationAdded(id, type, timestamp, args)
})

chrome.rewardsNotifications.onNotificationDeleted.addListener((id: string, type: number, timestamp: number) => {
  rewardsPanelActions.onNotificationDeleted(id, type, timestamp)
})

chrome.onevnRewards.onEnabledMain.addListener((enabledMain: boolean) => {
  rewardsPanelActions.onEnabledMain(enabledMain)
})

chrome.onevnRewards.onPendingContributionSaved.addListener((result: number) => {
  if (result === 0) {
    chrome.onevnRewards.getPendingContributionsTotal(((amount: number) => {
      rewardsPanelActions.OnPendingContributionsTotal(amount)
    }))
  }
})

chrome.onevnRewards.onPublisherListNormalized.addListener((properties: RewardsExtension.PublisherNormalized[]) => {
  rewardsPanelActions.onPublisherListNormalized(properties)
})

chrome.onevnRewards.onExcludedSitesChanged.addListener((properties: RewardsExtension.ExcludedSitesChanged) => {
  rewardsPanelActions.onExcludedSitesChanged(properties)
})

chrome.onevnRewards.onRecurringTipSaved.addListener((success: boolean) => {
  if (success) {
    chrome.onevnRewards.getRecurringTips((tips: RewardsExtension.RecurringTips) => {
      rewardsPanelActions.onRecurringTips(tips)
    })
  }
})

chrome.onevnRewards.onRecurringTipRemoved.addListener((success: boolean) => {
  if (success) {
    chrome.onevnRewards.getRecurringTips((tips: RewardsExtension.RecurringTips) => {
      rewardsPanelActions.onRecurringTips(tips)
    })
  }
})
