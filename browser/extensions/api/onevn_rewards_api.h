/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_EXTENSIONS_API_ONEVN_REWARDS_API_H_
#define ONEVN_BROWSER_EXTENSIONS_API_ONEVN_REWARDS_API_H_

#include <memory>
#include <string>

#include "extensions/browser/extension_function.h"
#include "onevn/components/onevn_rewards/browser/content_site.h"
#include "onevn/components/onevn_rewards/browser/publisher_banner.h"

namespace extensions {
namespace api {

class OneVNRewardsCreateWalletFunction : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.createWallet", UNKNOWN)

 protected:
  ~OneVNRewardsCreateWalletFunction() override;

  ResponseAction Run() override;
};

class OneVNRewardsDonateToSiteFunction : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.donateToSite", UNKNOWN)

 protected:
  ~OneVNRewardsDonateToSiteFunction() override;

  ResponseAction Run() override;
};

class OneVNRewardsGetPublisherDataFunction : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.getPublisherData", UNKNOWN)

 protected:
  ~OneVNRewardsGetPublisherDataFunction() override;

  ResponseAction Run() override;
};

class OneVNRewardsGetWalletPropertiesFunction
    : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.getWalletProperties", UNKNOWN)

 protected:
  ~OneVNRewardsGetWalletPropertiesFunction() override;

  ResponseAction Run() override;
};

class OneVNRewardsGetCurrentReportFunction : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.getCurrentReport", UNKNOWN)

 protected:
  ~OneVNRewardsGetCurrentReportFunction() override;

  ResponseAction Run() override;
};

class OneVNRewardsIncludeInAutoContributionFunction :
  public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.includeInAutoContribution", UNKNOWN)

 protected:
  ~OneVNRewardsIncludeInAutoContributionFunction() override;

  ResponseAction Run() override;
};

class OneVNRewardsGetGrantsFunction : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.getGrants", UNKNOWN)

 protected:
  ~OneVNRewardsGetGrantsFunction() override;

  ResponseAction Run() override;
};

class OneVNRewardsGetGrantCaptchaFunction : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.getGrantCaptcha", UNKNOWN)

 protected:
  ~OneVNRewardsGetGrantCaptchaFunction() override;

  ResponseAction Run() override;
};

class OneVNRewardsSolveGrantCaptchaFunction : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.solveGrantCaptcha", UNKNOWN)

 protected:
  ~OneVNRewardsSolveGrantCaptchaFunction() override;

  ResponseAction Run() override;
};

class OneVNRewardsGetPendingContributionsTotalFunction
    : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION(
      "onevnRewards.getPendingContributionsTotal", UNKNOWN)

 protected:
  ~OneVNRewardsGetPendingContributionsTotalFunction() override;

  ResponseAction Run() override;

 private:
  void OnGetPendingTotal(double amount);
};

class OneVNRewardsGetRewardsMainEnabledFunction
    : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.getRewardsMainEnabled", UNKNOWN)

 protected:
  ~OneVNRewardsGetRewardsMainEnabledFunction() override;

  ResponseAction Run() override;

 private:
  void OnGetRewardsMainEnabled(bool enabled);
};

class OneVNRewardsSaveAdsSettingFunction : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.saveAdsSetting", UNKNOWN)

 protected:
  ~OneVNRewardsSaveAdsSettingFunction() override;

  ResponseAction Run() override;
};

class OneVNRewardsGetACEnabledFunction : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.getACEnabled", UNKNOWN)

 protected:
  ~OneVNRewardsGetACEnabledFunction() override;

  ResponseAction Run() override;

 private:
  void OnGetACEnabled(bool enabled);
};

class OneVNRewardsSaveSettingFunction : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.saveSetting", UNKNOWN)

 protected:
  ~OneVNRewardsSaveSettingFunction() override;

  ResponseAction Run() override;
};

class OneVNRewardsSaveRecurringTipFunction :
  public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.saveRecurringTip", UNKNOWN)

 protected:
  ~OneVNRewardsSaveRecurringTipFunction() override;

  ResponseAction Run() override;
};

class OneVNRewardsRemoveRecurringTipFunction :
  public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.removeRecurringTip", UNKNOWN)

 protected:
  ~OneVNRewardsRemoveRecurringTipFunction() override;

  ResponseAction Run() override;
};

class OneVNRewardsGetRecurringTipsFunction :
  public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.getRecurringTips", UNKNOWN)

 protected:
  ~OneVNRewardsGetRecurringTipsFunction() override;

  ResponseAction Run() override;

 private:
    void OnGetRecurringTips(
        std::unique_ptr<onevn_rewards::ContentSiteList> list);
};

class OneVNRewardsGetPublisherBannerFunction :
public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION(
      "onevnRewards.getPublisherBanner", UNKNOWN)

 protected:
  ~OneVNRewardsGetPublisherBannerFunction() override;

  ResponseAction Run() override;

 private:
  void OnPublisherBanner(
      std::unique_ptr<::onevn_rewards::PublisherBanner> banner);
};

class OneVNRewardsRefreshPublisherFunction : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.refreshPublisher", UNKNOWN)

 protected:
  ~OneVNRewardsRefreshPublisherFunction() override;

  ResponseAction Run() override;

 private:
  void OnRefreshPublisher(bool verified, const std::string& publisher_key);
};

class OneVNRewardsGetAllNotificationsFunction :
    public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.getAllNotifications", UNKNOWN)

 protected:
  ~OneVNRewardsGetAllNotificationsFunction() override;

  ResponseAction Run() override;
};

}  // namespace api
}  // namespace extensions

#endif  // ONEVN_BROWSER_EXTENSIONS_API_ONEVN_REWARDS_API_H_
