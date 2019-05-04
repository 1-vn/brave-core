/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_REWARDS_BROWSER_REWARDS_SERVICE_OBSERVER_H_
#define ONEVN_COMPONENTS_ONEVN_REWARDS_BROWSER_REWARDS_SERVICE_OBSERVER_H_

#include <memory>
#include <string>
#include <vector>

#include "base/observer_list_types.h"
#include "onevn/components/onevn_rewards/browser/balance_report.h"
#include "onevn/components/onevn_rewards/browser/content_site.h"
#include "onevn/components/onevn_rewards/browser/grant.h"
#include "onevn/components/onevn_rewards/browser/publisher_banner.h"
#include "onevn/components/onevn_rewards/browser/wallet_properties.h"

namespace onevn_rewards {

class RewardsService;

class RewardsServiceObserver : public base::CheckedObserver {
 public:
  ~RewardsServiceObserver() override {}

  virtual void OnWalletInitialized(
      RewardsService* rewards_service,
      uint32_t error_code) {}
  virtual void OnWalletProperties(
      RewardsService* rewards_service,
      int error_code,
      std::unique_ptr<onevn_rewards::WalletProperties> properties) {}
  virtual void OnGrant(
      RewardsService* rewards_service,
      unsigned int error_code,
      onevn_rewards::Grant properties) {}
  virtual void OnGrantCaptcha(
      RewardsService* rewards_service,
      std::string image,
      std::string hint) {}
  virtual void OnRecoverWallet(
      RewardsService* rewards_service,
      unsigned int result,
      double balance,
      std::vector<onevn_rewards::Grant> grants) {}
  virtual void OnGrantFinish(
      RewardsService* rewards_service,
      unsigned int result,
      onevn_rewards::Grant grant) {}
  virtual void OnContentSiteUpdated(
      RewardsService* rewards_service) {}
  virtual void OnExcludedSitesChanged(
      RewardsService* rewards_service,
      std::string publisher_id,
      bool excluded) {}
  virtual void OnReconcileComplete(
      RewardsService* rewards_service,
      unsigned int result,
      const std::string& viewing_id,
      const std::string& category,
      const std::string& probi) {}
  virtual void OnRewardsMainEnabled(
      onevn_rewards::RewardsService* rewards_service,
      bool rewards_main_enabled) {}
  virtual void OnPendingContributionSaved(
      onevn_rewards::RewardsService* rewards_service,
      int result) {}
  virtual void OnPublisherListNormalized(
      RewardsService* rewards_service,
      const onevn_rewards::ContentSiteList& list) {}
  virtual void OnTransactionHistoryForThisCycleChanged(
      onevn_rewards::RewardsService* rewards_service) {}
  virtual void OnRecurringTipSaved(
      onevn_rewards::RewardsService* rewards_service,
      bool success) {}
  virtual void OnRecurringTipRemoved(
      onevn_rewards::RewardsService* rewards_service,
      bool success) {}
  virtual void OnContributionSaved(
      onevn_rewards::RewardsService* rewards_service,
      bool success,
      int category) {}
  // DO NOT ADD ANY MORE METHODS HERE UNLESS IT IS A BROADCAST NOTIFICATION
  // RewardsServiceObserver should not be used to return responses to the
  // caller. Method calls on RewardsService should use callbacks to return
  // responses. The observer is primarily for broadcast notifications of events
  // from the the rewards service. OnWalletInitialized, OnContentSiteUpdated,
  // etc... are examples of events that all observers will be interested in.
};

}  // namespace onevn_rewards

#endif  // ONEVN_COMPONENTS_ONEVN_REWARDS_BROWSER_REWARDS_SERVICE_OBSERVER_H_
