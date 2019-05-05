/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_SYNC_ONEVN_SYNC_CLIENT_IMPL_H
#define ONEVN_COMPONENTS_ONEVN_SYNC_ONEVN_SYNC_CLIENT_IMPL_H

#include "onevn/components/onevn_sync/client/onevn_sync_client.h"
#include "base/macros.h"
#include "base/scoped_observer.h"
#include "extensions/browser/extension_registry_observer.h"
#include "base/gtest_prod_util.h"

class OnevnSyncServiceTest;
class Profile;

namespace extensions {
class OnevnSyncEventRouter;
}

namespace onevn_sync {

namespace prefs {
  class Prefs;
}

using extensions::Extension;
using extensions::ExtensionRegistry;
using extensions::ExtensionRegistryObserver;
using extensions::UnloadedExtensionReason;

class OnevnSyncClientImpl : public OnevnSyncClient,
                            public ExtensionRegistryObserver {
 public:
  ~OnevnSyncClientImpl() override;

  // OnevnSyncClient overrides

  // OnevnSync to Browser messages
  SyncMessageHandler* sync_message_handler() override;

  // Browser to OnevnSync messages
  void SendGotInitData(const Uint8Array& seed, const Uint8Array& device_id,
    const client_data::Config& config, const std::string& sync_words) override;
  void SendFetchSyncRecords(
    const std::vector<std::string> &category_names, const base::Time &startAt,
    const int max_records) override;
  void SendFetchSyncDevices() override ;
  void SendResolveSyncRecords(
      const std::string& category_name,
      std::unique_ptr<SyncRecordAndExistingList> records) override;
  void SendSyncRecords(const std::string& category_name,
    const RecordsList &records) override;
  void SendDeleteSyncUser() override;
  void SendDeleteSyncCategory(const std::string& category_name) override;
  void SendGetBookmarksBaseOrder(const std::string& device_id,
                                 const std::string& platform) override;
  void NeedSyncWords(const std::string& seed) override;

 private:
  friend class OnevnSyncClient;
  friend class ::OnevnSyncServiceTest;
  static void set_for_testing(OnevnSyncClient* sync_client);

  OnevnSyncClientImpl(SyncMessageHandler* handler, Profile* profile);

  void OnExtensionInitialized() override;
  void OnSyncEnabledChanged() override;

  // ExtensionRegistryObserver:
  void OnExtensionReady(content::BrowserContext* browser_context,
                        const extensions::Extension* extension) override;
  void OnExtensionLoaded(content::BrowserContext* browser_context,
                         const Extension* extension) override;
  void OnExtensionUnloaded(content::BrowserContext* browser_context,
                           const Extension* extension,
                           UnloadedExtensionReason reason) override;
  void LoadOrUnloadExtension(bool load);
  void OnExtensionSystemReady();

  void ClearOrderMap() override;

  SyncMessageHandler* handler_;  // not owned
  Profile* profile_;  // not owned
  std::unique_ptr<onevn_sync::prefs::Prefs> sync_prefs_;
  bool extension_loaded_;

  std::unique_ptr<extensions::OnevnSyncEventRouter> onevn_sync_event_router_;

  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver>
    extension_registry_observer_;

  DISALLOW_COPY_AND_ASSIGN(OnevnSyncClientImpl);
};

} // namespace onevn_sync

#endif // ONEVN_COMPONENTS_ONEVN_SYNC_ONEVN_SYNC_CLIENT_IMPL_H
