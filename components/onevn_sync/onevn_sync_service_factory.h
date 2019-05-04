/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_SYNC_ONEVN_SYNC_SERVICE_FACTORY_H_
#define ONEVN_COMPONENTS_ONEVN_SYNC_ONEVN_SYNC_SERVICE_FACTORY_H_

#include "base/macros.h"
#include "base/memory/singleton.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

class Profile;

namespace onevn_sync {

class OneVNSyncService;

class OneVNSyncServiceFactory : public BrowserContextKeyedServiceFactory {
 public:
  static OneVNSyncService* GetForProfile(Profile* profile);
  static OneVNSyncService* GetForBrowserContext(
      content::BrowserContext* context);

  static OneVNSyncServiceFactory* GetInstance();

 private:
  friend struct base::DefaultSingletonTraits<OneVNSyncServiceFactory>;

  OneVNSyncServiceFactory();
  ~OneVNSyncServiceFactory() override;

  // BrowserContextKeyedServiceFactory:
  KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* context) const override;
  void RegisterProfilePrefs(
      user_prefs::PrefRegistrySyncable* registry) override;
  content::BrowserContext* GetBrowserContextToUse(
      content::BrowserContext* context) const override;
  bool ServiceIsNULLWhileTesting() const override;

  DISALLOW_COPY_AND_ASSIGN(OneVNSyncServiceFactory);
};

} // namespace onevn_sync

#endif // ONEVN_COMPONENTS_ONEVN_SYNC_ONEVN_SYNC_SERVICE_FACTORY_H_
