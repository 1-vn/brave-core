/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/onevn_browser_process_impl.h"

#include <utility>

#include "base/bind.h"
#include "base/path_service.h"
#include "base/task/post_task.h"
#include "base/threading/sequenced_task_runner_handle.h"
#include "onevn/browser/onevn_stats_updater.h"
#include "onevn/browser/component_updater/onevn_component_updater_configurator.h"
#include "onevn/browser/extensions/onevn_tor_client_updater.h"
#include "onevn/browser/profiles/onevn_profile_manager.h"
#include "onevn/components/onevn_referrals/browser/onevn_referrals_service.h"
#include "onevn/components/onevn_shields/browser/ad_block_custom_filters_service.h"
#include "onevn/components/onevn_shields/browser/ad_block_regional_service_manager.h"
#include "onevn/components/onevn_shields/browser/ad_block_service.h"
#include "onevn/components/onevn_shields/browser/autoplay_whitelist_service.h"
#include "onevn/components/onevn_shields/browser/extension_whitelist_service.h"
#include "onevn/components/onevn_shields/browser/https_everywhere_service.h"
#include "onevn/components/onevn_shields/browser/local_data_files_service.h"
#include "onevn/components/onevn_shields/browser/referrer_whitelist_service.h"
#include "onevn/components/onevn_shields/browser/tracking_protection_service.h"
#include "chrome/browser/io_thread.h"
#include "chrome/common/chrome_paths.h"
#include "components/component_updater/component_updater_service.h"
#include "components/component_updater/timer_update_scheduler.h"
#include "content/public/browser/browser_thread.h"

#if BUILDFLAG(BUNDLE_WIDEVINE_CDM)
#include "onevn/browser/widevine/onevn_widevine_bundle_manager.h"
#endif

OnevnBrowserProcessImpl* g_onevn_browser_process = nullptr;

using content::BrowserThread;

OnevnBrowserProcessImpl::~OnevnBrowserProcessImpl() {
}

OnevnBrowserProcessImpl::OnevnBrowserProcessImpl(
    ChromeFeatureListCreator* chrome_feature_list_creator)
    : BrowserProcessImpl(chrome_feature_list_creator) {
  g_browser_process = this;
  g_onevn_browser_process = this;

  onevn_referrals_service_ = onevn::OnevnReferralsServiceFactory(local_state());
  base::SequencedTaskRunnerHandle::Get()->PostDelayedTask(
      FROM_HERE,
      base::BindOnce(
          [](onevn::OnevnReferralsService* referrals_service) {
            referrals_service->Start();
          },
          base::Unretained(onevn_referrals_service_.get())),
      base::TimeDelta::FromSeconds(3));

  onevn_stats_updater_ = onevn::OnevnStatsUpdaterFactory(local_state());
  base::SequencedTaskRunnerHandle::Get()->PostTask(
      FROM_HERE, base::BindOnce(
                     [](onevn::OnevnStatsUpdater* stats_updater) {
                       stats_updater->Start();
                     },
                     base::Unretained(onevn_stats_updater_.get())));
}

component_updater::ComponentUpdateService*
OnevnBrowserProcessImpl::component_updater() {
  if (component_updater_)
    return component_updater_.get();

  if (!BrowserThread::CurrentlyOn(BrowserThread::UI))
    return nullptr;

  std::unique_ptr<component_updater::UpdateScheduler> scheduler;
#if defined(OS_ANDROID)
  if (base::FeatureList::IsEnabled(
          chrome::android::kBackgroundTaskComponentUpdate) &&
      component_updater::BackgroundTaskUpdateScheduler::IsAvailable()) {
    scheduler =
        std::make_unique<component_updater::BackgroundTaskUpdateScheduler>();
  }
#endif
  if (!scheduler)
    scheduler = std::make_unique<component_updater::TimerUpdateScheduler>();

  component_updater_ = component_updater::ComponentUpdateServiceFactory(
      component_updater::MakeOnevnComponentUpdaterConfigurator(
          base::CommandLine::ForCurrentProcess(),
          g_browser_process->local_state()),
      std::move(scheduler));

  return component_updater_.get();
}

ProfileManager* OnevnBrowserProcessImpl::profile_manager() {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  if (!created_profile_manager_)
    CreateProfileManager();
  return profile_manager_.get();
}

onevn_shields::AdBlockService*
OnevnBrowserProcessImpl::ad_block_service() {
  if (ad_block_service_)
    return ad_block_service_.get();

  ad_block_service_ = onevn_shields::AdBlockServiceFactory();
  return ad_block_service_.get();
}

onevn_shields::AdBlockCustomFiltersService*
OnevnBrowserProcessImpl::ad_block_custom_filters_service() {
  if (!ad_block_custom_filters_service_)
    ad_block_custom_filters_service_ =
        onevn_shields::AdBlockCustomFiltersServiceFactory();
  return ad_block_custom_filters_service_.get();
}

onevn_shields::AdBlockRegionalServiceManager*
OnevnBrowserProcessImpl::ad_block_regional_service_manager() {
  if (!ad_block_regional_service_manager_)
    ad_block_regional_service_manager_ =
        onevn_shields::AdBlockRegionalServiceManagerFactory();
  return ad_block_regional_service_manager_.get();
}

onevn_shields::AutoplayWhitelistService*
OnevnBrowserProcessImpl::autoplay_whitelist_service() {
  if (!autoplay_whitelist_service_) {
    autoplay_whitelist_service_ =
        onevn_shields::AutoplayWhitelistServiceFactory();
  }
  return autoplay_whitelist_service_.get();
}

onevn_shields::ExtensionWhitelistService*
OnevnBrowserProcessImpl::extension_whitelist_service() {
  if (!extension_whitelist_service_) {
    extension_whitelist_service_ =
        onevn_shields::ExtensionWhitelistServiceFactory();
  }
  return extension_whitelist_service_.get();
}

onevn_shields::ReferrerWhitelistService*
OnevnBrowserProcessImpl::referrer_whitelist_service() {
  if (!referrer_whitelist_service_) {
    referrer_whitelist_service_ =
      onevn_shields::ReferrerWhitelistServiceFactory();
  }
  return referrer_whitelist_service_.get();
}

onevn_shields::TrackingProtectionService*
OnevnBrowserProcessImpl::tracking_protection_service() {
  if (!tracking_protection_service_) {
    tracking_protection_service_ =
        onevn_shields::TrackingProtectionServiceFactory();
  }
  return tracking_protection_service_.get();
}

onevn_shields::HTTPSEverywhereService*
OnevnBrowserProcessImpl::https_everywhere_service() {
  if (!https_everywhere_service_)
    https_everywhere_service_ =
        onevn_shields::HTTPSEverywhereServiceFactory();
  return https_everywhere_service_.get();
}

onevn_shields::LocalDataFilesService*
OnevnBrowserProcessImpl::local_data_files_service() {
  if (!local_data_files_service_)
    local_data_files_service_ =
        onevn_shields::LocalDataFilesServiceFactory();
  return local_data_files_service_.get();
}

extensions::OnevnTorClientUpdater*
OnevnBrowserProcessImpl::tor_client_updater() {
  if (tor_client_updater_)
    return tor_client_updater_.get();

  tor_client_updater_ = extensions::OnevnTorClientUpdaterFactory();
  return tor_client_updater_.get();
}

void OnevnBrowserProcessImpl::CreateProfileManager() {
  DCHECK(!created_profile_manager_ && !profile_manager_);
  created_profile_manager_ = true;

  base::FilePath user_data_dir;
  base::PathService::Get(chrome::DIR_USER_DATA, &user_data_dir);
  profile_manager_ = std::make_unique<OnevnProfileManager>(user_data_dir);
}

#if BUILDFLAG(BUNDLE_WIDEVINE_CDM)
OnevnWidevineBundleManager*
OnevnBrowserProcessImpl::onevn_widevine_bundle_manager() {
  if (!onevn_widevine_bundle_manager_)
    onevn_widevine_bundle_manager_.reset(new OnevnWidevineBundleManager);
  return onevn_widevine_bundle_manager_.get();
}
#endif
