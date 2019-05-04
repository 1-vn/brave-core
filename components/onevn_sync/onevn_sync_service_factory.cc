/* Copyright 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/components/onevn_sync/onevn_sync_service_factory.h"

#include <memory>
#include <string>

#include "base/memory/singleton.h"
#include "onevn/components/onevn_sync/onevn_sync_prefs.h"
#include "onevn/components/onevn_sync/onevn_sync_service.h"
#include "onevn/components/onevn_sync/onevn_sync_service_impl.h"
#include "chrome/browser/bookmarks/bookmark_model_factory.h"
#include "chrome/browser/profiles/incognito_helpers.h"
#include "chrome/browser/profiles/profile.h"
#include "components/keyed_service/content/browser_context_dependency_manager.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/pref_registry/pref_registry_syncable.h"

namespace onevn_sync {

// static
OneVNSyncService* OneVNSyncServiceFactory::GetForProfile(Profile* profile) {
  if (profile->IsOffTheRecord())
    return NULL;

  return static_cast<OneVNSyncService*>(
      GetInstance()->GetServiceForBrowserContext(profile, true));
}

// static
OneVNSyncServiceFactory* OneVNSyncServiceFactory::GetInstance() {
  return base::Singleton<OneVNSyncServiceFactory>::get();
}

OneVNSyncServiceFactory::OneVNSyncServiceFactory()
    : BrowserContextKeyedServiceFactory(
        "OneVNSyncService",
        BrowserContextDependencyManager::GetInstance()) {
  DependsOn(BookmarkModelFactory::GetInstance());
}

OneVNSyncServiceFactory::~OneVNSyncServiceFactory() = default;

KeyedService* OneVNSyncServiceFactory::BuildServiceInstanceFor(
    content::BrowserContext* context) const {
  std::unique_ptr<OneVNSyncServiceImpl> onevn_sync_service(
      new OneVNSyncServiceImpl(Profile::FromBrowserContext(context)));
  return onevn_sync_service.release();
}

void OneVNSyncServiceFactory::RegisterProfilePrefs(
    user_prefs::PrefRegistrySyncable* registry) {
  registry->RegisterStringPref(prefs::kSyncDeviceId, std::string());
  registry->RegisterStringPref(prefs::kSyncSeed, std::string());
  registry->RegisterStringPref(prefs::kSyncPrevSeed, std::string());
  registry->RegisterStringPref(prefs::kSyncDeviceName, std::string());
  registry->RegisterStringPref(prefs::kSyncBookmarksBaseOrder, std::string());

  registry->RegisterBooleanPref(prefs::kSyncEnabled, false);
  registry->RegisterBooleanPref(prefs::kSyncBookmarksEnabled, false);
  registry->RegisterBooleanPref(prefs::kSyncSiteSettingsEnabled, false);
  registry->RegisterBooleanPref(prefs::kSyncHistoryEnabled, false);

  registry->RegisterTimePref(prefs::kSyncLatestRecordTime, base::Time());
  registry->RegisterTimePref(prefs::kSyncLastFetchTime, base::Time());

  registry->RegisterStringPref(prefs::kSyncDeviceList, std::string());
  registry->RegisterStringPref(prefs::kSyncApiVersion, std::string("0"));
  registry->RegisterIntegerPref(prefs::kSyncMigrateBookmarksVersion, 0);
}

content::BrowserContext* OneVNSyncServiceFactory::GetBrowserContextToUse(
    content::BrowserContext* context) const {
  return chrome::GetBrowserContextRedirectedInIncognito(context);
}

bool OneVNSyncServiceFactory::ServiceIsNULLWhileTesting() const {
  return false;
}

}  // namespace onevn_sync
