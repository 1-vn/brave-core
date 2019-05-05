/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
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

class OnevnRewardsCreateWalletFunction : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.createWallet", UNKNOWN)

 protected:
  ~OnevnRewardsCreateWalletFunction() override;

  ResponseAction Run() override;
};

class OnevnRewardsDonateToSiteFunction : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.donateToSite", UNKNOWN)

 protected:
  ~OnevnRewardsDonateToSiteFunction() override;

  ResponseAction Run() override;
};

class OnevnRewardsGetPublisherDataFunction : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.getPublisherData", UNKNOWN)

 protected:
  ~OnevnRewardsGetPublisherDataFunction() override;

  ResponseAction Run() override;
};

class OnevnRewardsGetWalletPropertiesFunction
    : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.getWalletProperties", UNKNOWN)

 protected:
  ~OnevnRewardsGetWalletPropertiesFunction() override;

  ResponseAction Run() override;
};

class OnevnRewardsGetCurrentReportFunction : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.getCurrentReport", UNKNOWN)

 protected:
  ~OnevnRewardsGetCurrentReportFunction() override;

  ResponseAction Run() override;
};

class OnevnRewardsIncludeInAutoContributionFunction :
  public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.includeInAutoContribution", UNKNOWN)

 protected:
  ~OnevnRewardsIncludeInAutoContributionFunction() override;

  ResponseAction Run() override;
};

class OnevnRewardsGetGrantsFunction : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.getGrants", UNKNOWN)

 protected:
  ~OnevnRewardsGetGrantsFunction() override;

  ResponseAction Run() override;
};

class OnevnRewardsGetGrantCaptchaFunction : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.getGrantCaptcha", UNKNOWN)

 protected:
  ~OnevnRewardsGetGrantCaptchaFunction() override;

  ResponseAction Run() override;
};

class OnevnRewardsSolveGrantCaptchaFunction : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.solveGrantCaptcha", UNKNOWN)

 protected:
  ~OnevnRewardsSolveGrantCaptchaFunction() override;

  ResponseAction Run() override;
};

class OnevnRewardsGetPendingContributionsTotalFunction
    : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION(
      "onevnRewards.getPendingContributionsTotal", UNKNOWN)

 protected:
  ~OnevnRewardsGetPendingContributionsTotalFunction() override;

  ResponseAction Run() override;

 private:
  void OnGetPendingTotal(double amount);
};

class OnevnRewardsGetRewardsMainEnabledFunction
    : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.getRewardsMainEnabled", UNKNOWN)

 protected:
  ~OnevnRewardsGetRewardsMainEnabledFunction() override;

  ResponseAction Run() override;

 private:
  void OnGetRewardsMainEnabled(bool enabled);
};

class OnevnRewardsSaveAdsSettingFunction : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.saveAdsSetting", UNKNOWN)

 protected:
  ~OnevnRewardsSaveAdsSettingFunction() override;

  ResponseAction Run() override;
};

class OnevnRewardsGetACEnabledFunction : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.getACEnabled", UNKNOWN)

 protected:
  ~OnevnRewardsGetACEnabledFunction() override;

  ResponseAction Run() override;

 private:
  void OnGetACEnabled(bool enabled);
};

class OnevnRewardsSaveSettingFunction : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.saveSetting", UNKNOWN)

 protected:
  ~OnevnRewardsSaveSettingFunction() override;

  ResponseAction Run() override;
};

class OnevnRewardsSaveRecurringTipFunction :
  public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.saveRecurringTip", UNKNOWN)

 protected:
  ~OnevnRewardsSaveRecurringTipFunction() override;

  ResponseAction Run() override;
};

class OnevnRewardsRemoveRecurringTipFunction :
  public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.removeRecurringTip", UNKNOWN)

 protected:
  ~OnevnRewardsRemoveRecurringTipFunction() override;

  ResponseAction Run() override;
};

class OnevnRewardsGetRecurringTipsFunction :
  public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.getRecurringTips", UNKNOWN)

 protected:
  ~OnevnRewardsGetRecurringTipsFunction() override;

  ResponseAction Run() override;

 private:
    void OnGetRecurringTips(
        std::unique_ptr<onevn_rewards::ContentSiteList> list);
};

class OnevnRewardsGetPublisherBannerFunction :
public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION(
      "onevnRewards.getPublisherBanner", UNKNOWN)

 protected:
  ~OnevnRewardsGetPublisherBannerFunction() override;

  ResponseAction Run() override;

 private:
  void OnPublisherBanner(
      std::unique_ptr<::onevn_rewards::PublisherBanner> banner);
};

class OnevnRewardsRefreshPublisherFunction : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.refreshPublisher", UNKNOWN)

 protected:
  ~OnevnRewardsRefreshPublisherFunction() override;

  ResponseAction Run() override;

 private:
  void OnRefreshPublisher(bool verified, const std::string& publisher_key);
};

class OnevnRewardsGetAllNotificationsFunction :
    public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnRewards.getAllNotifications", UNKNOWN)

 protected:
  ~OnevnRewardsGetAllNotificationsFunction() override;

  ResponseAction Run() override;
};

}  // namespace api
}  // namespace extensions

#endif  // ONEVN_BROWSER_EXTENSIONS_API_ONEVN_REWARDS_API_H_
