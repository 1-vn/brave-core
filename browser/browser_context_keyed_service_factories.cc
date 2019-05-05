/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/browser_context_keyed_service_factories.h"

#include "onevn/browser/search_engines/search_engine_provider_service_factory.h"
#include "onevn/browser/tor/tor_profile_service_factory.h"
#include "onevn/components/onevn_ads/browser/ads_service_factory.h"
#include "onevn/components/onevn_rewards/browser/rewards_service_factory.h"
#include "onevn/components/onevn_sync/onevn_sync_service_factory.h"

namespace onevn {

void EnsureBrowserContextKeyedServiceFactoriesBuilt() {
  onevn_ads::AdsServiceFactory::GetInstance();
  onevn_rewards::RewardsServiceFactory::GetInstance();
  onevn_sync::OnevnSyncServiceFactory::GetInstance();
  TorProfileServiceFactory::GetInstance();
  SearchEngineProviderServiceFactory::GetInstance();
}

}  // namespace onevn
