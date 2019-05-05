/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_ONEVN_BROWSER_PROCESS_IMPL_H_
#define ONEVN_BROWSER_ONEVN_BROWSER_PROCESS_IMPL_H_

#include <memory>

#include "chrome/browser/browser_process_impl.h"
#include "third_party/widevine/cdm/buildflags.h"

namespace onevn {
class OnevnReferralsService;
class OnevnStatsUpdater;
}

#if BUILDFLAG(BUNDLE_WIDEVINE_CDM)
class OnevnWidevineBundleManager;
#endif

namespace onevn_shields {
class AdBlockService;
class AdBlockCustomFiltersService;
class AdBlockRegionalServiceManager;
class AutoplayWhitelistService;
class ExtensionWhitelistService;
class HTTPSEverywhereService;
class LocalDataFilesService;
class ReferrerWhitelistService;
class TrackingProtectionService;
}  // namespace onevn_shields

namespace extensions {
class OnevnTorClientUpdater;
}

class OnevnBrowserProcessImpl : public BrowserProcessImpl {
 public:
  OnevnBrowserProcessImpl(
      ChromeFeatureListCreator* chrome_feature_list_creator);
  ~OnevnBrowserProcessImpl() override;

  // BrowserProcess implementation.
  component_updater::ComponentUpdateService* component_updater() override;

  ProfileManager* profile_manager() override;

  onevn_shields::AdBlockService* ad_block_service();
  onevn_shields::AdBlockCustomFiltersService* ad_block_custom_filters_service();
  onevn_shields::AdBlockRegionalServiceManager*
  ad_block_regional_service_manager();
  onevn_shields::AutoplayWhitelistService* autoplay_whitelist_service();
  onevn_shields::ExtensionWhitelistService* extension_whitelist_service();
  onevn_shields::ReferrerWhitelistService* referrer_whitelist_service();
  onevn_shields::TrackingProtectionService* tracking_protection_service();
  onevn_shields::HTTPSEverywhereService* https_everywhere_service();
  onevn_shields::LocalDataFilesService* local_data_files_service();
  extensions::OnevnTorClientUpdater* tor_client_updater();
#if BUILDFLAG(BUNDLE_WIDEVINE_CDM)
  OnevnWidevineBundleManager* onevn_widevine_bundle_manager();
#endif

 private:
  void CreateProfileManager();

  std::unique_ptr<onevn_shields::AdBlockService> ad_block_service_;
  std::unique_ptr<onevn_shields::AdBlockCustomFiltersService>
      ad_block_custom_filters_service_;
  std::unique_ptr<onevn_shields::AdBlockRegionalServiceManager>
      ad_block_regional_service_manager_;
  std::unique_ptr<onevn_shields::AutoplayWhitelistService>
      autoplay_whitelist_service_;
  std::unique_ptr<onevn_shields::ExtensionWhitelistService>
      extension_whitelist_service_;
  std::unique_ptr<onevn_shields::ReferrerWhitelistService>
      referrer_whitelist_service_;
  std::unique_ptr<onevn_shields::TrackingProtectionService>
      tracking_protection_service_;
  std::unique_ptr<onevn_shields::HTTPSEverywhereService>
      https_everywhere_service_;
  std::unique_ptr<onevn_shields::LocalDataFilesService>
      local_data_files_service_;
  std::unique_ptr<onevn::OnevnStatsUpdater> onevn_stats_updater_;
  std::unique_ptr<onevn::OnevnReferralsService> onevn_referrals_service_;
  std::unique_ptr<extensions::OnevnTorClientUpdater> tor_client_updater_;
#if BUILDFLAG(BUNDLE_WIDEVINE_CDM)
  std::unique_ptr<OnevnWidevineBundleManager> onevn_widevine_bundle_manager_;
#endif

  SEQUENCE_CHECKER(sequence_checker_);

  DISALLOW_COPY_AND_ASSIGN(OnevnBrowserProcessImpl);
};

extern OnevnBrowserProcessImpl* g_onevn_browser_process;

#endif  // ONEVN_BROWSER_ONEVN_BROWSER_PROCESS_IMPL_H_
