/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/extensions/api/onevn_rewards_api.h"

#include <memory>
#include <string>
#include <utility>

#include "base/bind.h"
#include "onevn/browser/onevn_rewards/donations_dialog.h"
#include "onevn/common/extensions/api/onevn_rewards.h"
#include "onevn/components/onevn_rewards/browser/rewards_service.h"
#include "onevn/components/onevn_rewards/browser/rewards_service_factory.h"
#include "onevn/components/onevn_ads/browser/ads_service.h"
#include "onevn/components/onevn_ads/browser/ads_service_factory.h"
#include "content/public/browser/web_contents.h"
#include "chrome/browser/extensions/api/tabs/tabs_constants.h"
#include "chrome/browser/extensions/extension_tab_util.h"
#include "chrome/browser/profiles/profile.h"

using onevn_rewards::RewardsService;
using onevn_rewards::RewardsServiceFactory;
using onevn_ads::AdsService;
using onevn_ads::AdsServiceFactory;

namespace extensions {
namespace api {

OnevnRewardsCreateWalletFunction::~OnevnRewardsCreateWalletFunction() {
}

ExtensionFunction::ResponseAction OnevnRewardsCreateWalletFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  auto* rewards_service = RewardsServiceFactory::GetForProfile(profile);
  if (rewards_service) {
    rewards_service->CreateWallet();
  }
  return RespondNow(NoArguments());
}

OnevnRewardsDonateToSiteFunction::~OnevnRewardsDonateToSiteFunction() {
}

ExtensionFunction::ResponseAction OnevnRewardsDonateToSiteFunction::Run() {
  std::unique_ptr<onevn_rewards::DonateToSite::Params> params(
      onevn_rewards::DonateToSite::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  // Sanity check: don't allow donations in private / tor contexts,
  // although the command should not have been enabled in the first place.
  Profile* profile = Profile::FromBrowserContext(browser_context());
  if (profile->IsOffTheRecord()) {
    return RespondNow(Error("Cannot donate to site in a private context"));
  }

  // Get web contents for this tab
  content::WebContents* contents = nullptr;
  if (!ExtensionTabUtil::GetTabById(
        params->tab_id,
        profile,
        include_incognito_information(),
        nullptr,
        nullptr,
        &contents,
        nullptr)) {
    return RespondNow(Error(tabs_constants::kTabNotFoundError,
                            base::IntToString(params->tab_id)));
  }
  ::onevn_rewards::OpenDonationDialog(contents, params->publisher_key);

  return RespondNow(NoArguments());
}

OnevnRewardsGetPublisherDataFunction::~OnevnRewardsGetPublisherDataFunction() {
}

OnevnRewardsIncludeInAutoContributionFunction::
  ~OnevnRewardsIncludeInAutoContributionFunction() {
}

ExtensionFunction::ResponseAction
  OnevnRewardsIncludeInAutoContributionFunction::Run() {
  std::unique_ptr<onevn_rewards::IncludeInAutoContribution::Params> params(
    onevn_rewards::IncludeInAutoContribution::Params::Create(*args_));
  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);
  if (rewards_service) {
    rewards_service->SetContributionAutoInclude(
      params->publisher_key, params->excluded);
  }
  return RespondNow(NoArguments());
}

ExtensionFunction::ResponseAction OnevnRewardsGetPublisherDataFunction::Run() {
  std::unique_ptr<onevn_rewards::GetPublisherData::Params> params(
      onevn_rewards::GetPublisherData::Params::Create(*args_));
  Profile* profile = Profile::FromBrowserContext(browser_context());
  auto* rewards_service = RewardsServiceFactory::GetForProfile(profile);
  if (rewards_service) {
    rewards_service->GetPublisherActivityFromUrl(params->window_id,
                                                  params->url,
                                                  params->favicon_url,
                                                  params->publisher_blob);
  }
  return RespondNow(NoArguments());
}

OnevnRewardsGetWalletPropertiesFunction::
~OnevnRewardsGetWalletPropertiesFunction() {
}

ExtensionFunction::ResponseAction
OnevnRewardsGetWalletPropertiesFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  auto* rewards_service = RewardsServiceFactory::GetForProfile(profile);
  if (rewards_service) {
    rewards_service->FetchWalletProperties();
  }
  return RespondNow(NoArguments());
}

OnevnRewardsGetCurrentReportFunction::~OnevnRewardsGetCurrentReportFunction() {
}

ExtensionFunction::ResponseAction OnevnRewardsGetCurrentReportFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  auto* rewards_service = RewardsServiceFactory::GetForProfile(profile);
  if (rewards_service) {
    rewards_service->GetCurrentBalanceReport();
  }
  return RespondNow(NoArguments());
}

OnevnRewardsGetGrantsFunction::~OnevnRewardsGetGrantsFunction() {
}

ExtensionFunction::ResponseAction OnevnRewardsGetGrantsFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);
  if (rewards_service) {
    rewards_service->FetchGrants(std::string(), std::string());
  }
  return RespondNow(NoArguments());
}

OnevnRewardsGetGrantCaptchaFunction::~OnevnRewardsGetGrantCaptchaFunction() {
}

ExtensionFunction::ResponseAction OnevnRewardsGetGrantCaptchaFunction::Run() {
  std::unique_ptr<onevn_rewards::GetGrantCaptcha::Params> params(
      onevn_rewards::GetGrantCaptcha::Params::Create(*args_));
  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);
  if (rewards_service) {
    rewards_service->GetGrantCaptcha(params->promotion_id,
                                     params->type);
  }
  return RespondNow(NoArguments());
}

OnevnRewardsSolveGrantCaptchaFunction::
~OnevnRewardsSolveGrantCaptchaFunction() {
}

ExtensionFunction::ResponseAction OnevnRewardsSolveGrantCaptchaFunction::Run() {
  std::unique_ptr<onevn_rewards::SolveGrantCaptcha::Params> params(
      onevn_rewards::SolveGrantCaptcha::Params::Create(*args_));
  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);
  if (rewards_service) {
    rewards_service->SolveGrantCaptcha(params->solution, params->promotion_id);
  }
  return RespondNow(NoArguments());
}

OnevnRewardsGetPendingContributionsTotalFunction::
~OnevnRewardsGetPendingContributionsTotalFunction() {
}

ExtensionFunction::ResponseAction
OnevnRewardsGetPendingContributionsTotalFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);

  if (!rewards_service) {
    return RespondNow(OneArgument(
          std::make_unique<base::Value>(0.0)));
  }

  rewards_service->GetPendingContributionsTotal(base::Bind(
        &OnevnRewardsGetPendingContributionsTotalFunction::OnGetPendingTotal,
        this));
  return RespondLater();
}

void OnevnRewardsGetPendingContributionsTotalFunction::OnGetPendingTotal(
    double amount) {
  Respond(OneArgument(std::make_unique<base::Value>(amount)));
}

OnevnRewardsGetRewardsMainEnabledFunction::
~OnevnRewardsGetRewardsMainEnabledFunction() {
}

ExtensionFunction::ResponseAction
OnevnRewardsGetRewardsMainEnabledFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);

  if (!rewards_service) {
    return RespondNow(Error("Rewards service is not initialized"));
  }

  rewards_service->GetRewardsMainEnabled(base::Bind(
        &OnevnRewardsGetRewardsMainEnabledFunction::OnGetRewardsMainEnabled,
        this));
  return RespondLater();
}

void OnevnRewardsGetRewardsMainEnabledFunction::OnGetRewardsMainEnabled(
    bool enabled) {
  Respond(OneArgument(std::make_unique<base::Value>(enabled)));
}

OnevnRewardsSaveAdsSettingFunction::~OnevnRewardsSaveAdsSettingFunction() {
}

ExtensionFunction::ResponseAction OnevnRewardsSaveAdsSettingFunction::Run() {
  std::unique_ptr<onevn_rewards::SaveAdsSetting::Params> params(
      onevn_rewards::SaveAdsSetting::Params::Create(*args_));
  Profile* profile = Profile::FromBrowserContext(browser_context());
  AdsService* ads_service_ = AdsServiceFactory::GetForProfile(profile);
  if (ads_service_) {
    if (params->key == "adsEnabled") {
      ads_service_->SetAdsEnabled(params->value == "true");
    }
  }
  return RespondNow(NoArguments());
}

OnevnRewardsGetACEnabledFunction::
~OnevnRewardsGetACEnabledFunction() {
}

ExtensionFunction::ResponseAction
OnevnRewardsGetACEnabledFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);

  if (!rewards_service) {
    return RespondNow(Error("Rewards service is not initialized"));
  }

  rewards_service->GetAutoContribute(base::BindOnce(
        &OnevnRewardsGetACEnabledFunction::OnGetACEnabled,
        this));
  return RespondLater();
}

void OnevnRewardsGetACEnabledFunction::OnGetACEnabled(bool enabled) {
  Respond(OneArgument(std::make_unique<base::Value>(enabled)));
}

OnevnRewardsSaveSettingFunction::~OnevnRewardsSaveSettingFunction() {
}

ExtensionFunction::ResponseAction OnevnRewardsSaveSettingFunction::Run() {
  std::unique_ptr<onevn_rewards::SaveSetting::Params> params(
      onevn_rewards::SaveSetting::Params::Create(*args_));

  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);

  if (rewards_service) {
    if (params->key == "enabledMain") {
      rewards_service->SetRewardsMainEnabled(
          std::stoi(params->value.c_str()));
    }
  }

  return RespondNow(NoArguments());
}

OnevnRewardsSaveRecurringTipFunction::
~OnevnRewardsSaveRecurringTipFunction() {
}

ExtensionFunction::ResponseAction
OnevnRewardsSaveRecurringTipFunction::Run() {
  std::unique_ptr<onevn_rewards::SaveRecurringTip::Params> params(
    onevn_rewards::SaveRecurringTip::Params::Create(*args_));

  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service_ =
    RewardsServiceFactory::GetForProfile(profile);

  if (rewards_service_) {
    rewards_service_->SaveRecurringTip(params->publisher_key,
                                       params->new_amount);
  }

  return RespondNow(NoArguments());
}

OnevnRewardsRemoveRecurringTipFunction::
~OnevnRewardsRemoveRecurringTipFunction() {
}

ExtensionFunction::ResponseAction
OnevnRewardsRemoveRecurringTipFunction::Run() {
  std::unique_ptr<onevn_rewards::RemoveRecurringTip::Params> params(
    onevn_rewards::RemoveRecurringTip::Params::Create(*args_));

  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service_ =
    RewardsServiceFactory::GetForProfile(profile);

  if (rewards_service_) {
    rewards_service_->RemoveRecurringTip(params->publisher_key);
  }

  return RespondNow(NoArguments());
}

OnevnRewardsGetRecurringTipsFunction::
~OnevnRewardsGetRecurringTipsFunction() {
}

ExtensionFunction::ResponseAction
OnevnRewardsGetRecurringTipsFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);

  if (!rewards_service) {
    return RespondNow(Error("Rewards service is not initialized"));
  }

  rewards_service->GetRecurringTipsUI(base::Bind(
        &OnevnRewardsGetRecurringTipsFunction::OnGetRecurringTips,
        this));
  return RespondLater();
}

void OnevnRewardsGetRecurringTipsFunction::OnGetRecurringTips(
    std::unique_ptr<::onevn_rewards::ContentSiteList> list) {
  std::unique_ptr<base::DictionaryValue> result(new base::DictionaryValue());
  auto recurringTips = std::make_unique<base::ListValue>();

  if (!list->empty()) {
    for (auto const& item : *list) {
      auto tip = std::make_unique<base::DictionaryValue>();
      tip->SetString("publisherKey", item.id);
      tip->SetInteger("amount", item.weight);
      recurringTips->Append(std::move(tip));
    }
  }

  result->SetList("recurringTips", std::move(recurringTips));
  Respond(OneArgument(std::move(result)));
}

OnevnRewardsGetPublisherBannerFunction::
~OnevnRewardsGetPublisherBannerFunction() {
}

ExtensionFunction::ResponseAction
OnevnRewardsGetPublisherBannerFunction::Run() {
  std::unique_ptr<onevn_rewards::GetPublisherBanner::Params> params(
    onevn_rewards::GetPublisherBanner::Params::Create(*args_));

  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);

  if (!rewards_service) {
    return RespondNow(Error("Rewards service is not initialized"));
  }

  rewards_service->GetPublisherBanner(
      params->publisher_key,
      base::BindOnce(
        &OnevnRewardsGetPublisherBannerFunction::OnPublisherBanner,
        this));
  return RespondLater();
}

void OnevnRewardsGetPublisherBannerFunction::OnPublisherBanner(
    std::unique_ptr<::onevn_rewards::PublisherBanner> banner) {
  std::unique_ptr<base::DictionaryValue> result(new base::DictionaryValue());

  if (banner) {
    result->SetString("publisherKey", banner->publisher_key);
    result->SetString("title", banner->title);
    result->SetString("name", banner->name);
    result->SetString("description", banner->description);
    result->SetString("background", banner->background);
    result->SetString("logo", banner->logo);
    result->SetString("provider", banner->provider);
    result->SetBoolean("verified", banner->verified);

    auto amounts = std::make_unique<base::ListValue>();
    for (int const& value : banner->amounts) {
      amounts->AppendInteger(value);
    }
    result->SetList("amounts", std::move(amounts));

    auto social = std::make_unique<base::DictionaryValue>();
    for (auto const& item : banner->social) {
      social->SetString(item.first, item.second);
    }
    result->SetDictionary("social", std::move(social));
  }

  Respond(OneArgument(std::move(result)));
}

OnevnRewardsRefreshPublisherFunction::~OnevnRewardsRefreshPublisherFunction() {
}

ExtensionFunction::ResponseAction OnevnRewardsRefreshPublisherFunction::Run() {
  std::unique_ptr<onevn_rewards::RefreshPublisher::Params> params(
      onevn_rewards::RefreshPublisher::Params::Create(*args_));

  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);
  if (!rewards_service) {
    return RespondNow(TwoArguments(
        std::make_unique<base::Value>(false),
        std::make_unique<base::Value>(std::string())));
  }
  rewards_service->RefreshPublisher(
      params->publisher_key,
      base::BindOnce(
        &OnevnRewardsRefreshPublisherFunction::OnRefreshPublisher,
        this));
  return RespondLater();
}

void OnevnRewardsRefreshPublisherFunction::OnRefreshPublisher(
    bool verified, const std::string& publisher_key) {
  Respond(TwoArguments(std::make_unique<base::Value>(verified),
                       std::make_unique<base::Value>(publisher_key)));
}

OnevnRewardsGetAllNotificationsFunction::
~OnevnRewardsGetAllNotificationsFunction() {
}

ExtensionFunction::ResponseAction
OnevnRewardsGetAllNotificationsFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);

  auto list = std::make_unique<base::ListValue>();

  if (!rewards_service) {
    return RespondNow(OneArgument(std::move(list)));
  }

  auto notifications = rewards_service->GetAllNotifications();

  for (auto const& notification : notifications) {
    auto item = std::make_unique<base::DictionaryValue>();
    item->SetString("id", notification.second.id_);
    item->SetInteger("type", notification.second.type_);
    item->SetInteger("timestamp", notification.second.timestamp_);

    auto args = std::make_unique<base::ListValue>();
    for (auto const& arg : notification.second.args_) {
      args->AppendString(arg);
    }

    item->SetList("args", std::move(args));
    list->Append(std::move(item));
  }

  return RespondNow(OneArgument(std::move(list)));
}

}  // namespace api
}  // namespace extensions
