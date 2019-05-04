/* Copyright 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/components/onevn_sync/client/onevn_sync_client_impl.h"

#include <memory>
#include <string>
#include <vector>

#include "base/logging.h"
#include "onevn/browser/extensions/api/onevn_sync_event_router.h"
#include "onevn/components/onevn_sync/client/client_ext_impl_data.h"
#include "onevn/components/onevn_sync/grit/onevn_sync_resources.h"
#include "onevn/components/onevn_sync/onevn_sync_prefs.h"
#include "onevn/common/extensions/api/onevn_sync.h"
#include "onevn/common/extensions/extension_constants.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/extensions/component_loader.h"
#include "chrome/browser/extensions/extension_service.h"
#include "content/public/browser/browser_thread.h"
#include "extensions/browser/extension_registry.h"
#include "extensions/browser/extension_system.h"
#include "extensions/common/one_shot_event.h"

namespace onevn_sync {

OneVNSyncClient* onevn_sync_client_for_testing_;

// static
void OneVNSyncClientImpl::set_for_testing(OneVNSyncClient* sync_client) {
  onevn_sync_client_for_testing_ = sync_client;
}

// static
OneVNSyncClient* OneVNSyncClient::Create(
    SyncMessageHandler* handler,
    Profile* profile) {
  if (onevn_sync_client_for_testing_)
    return onevn_sync_client_for_testing_;

  return new OneVNSyncClientImpl(handler, profile);
}

OneVNSyncClientImpl::OneVNSyncClientImpl(SyncMessageHandler* handler,
                                         Profile* profile) :
    handler_(handler),
    profile_(profile),
    sync_prefs_(new onevn_sync::prefs::Prefs(profile->GetPrefs())),
    extension_loaded_(false),
    onevn_sync_event_router_(new extensions::OneVNSyncEventRouter(profile)),
    extension_registry_observer_(this) {
  // Handle when the extension system is ready
  extensions::ExtensionSystem::Get(profile)->ready().Post(
      FROM_HERE, base::Bind(&OneVNSyncClientImpl::OnExtensionSystemReady,
          base::Unretained(this)));
}

OneVNSyncClientImpl::~OneVNSyncClientImpl() {}

SyncMessageHandler* OneVNSyncClientImpl::sync_message_handler() {
  return handler_;
}

void OneVNSyncClientImpl::SendGotInitData(const Uint8Array& seed,
                                          const Uint8Array& device_id,
                                          const client_data::Config& config,
                                          const std::string& sync_words) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  extensions::api::onevn_sync::Config config_extension;
  ConvertConfig(config, config_extension);
  onevn_sync_event_router_->GotInitData(seed, device_id, config_extension,
                                        sync_words);
}

void OneVNSyncClientImpl::SendFetchSyncRecords(
    const std::vector<std::string> &category_names,
    const base::Time &startAt,
    const int max_records) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  onevn_sync_event_router_->FetchSyncRecords(category_names, startAt,
                                             max_records);
}

void OneVNSyncClientImpl::SendFetchSyncDevices() {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  onevn_sync_event_router_->FetchSyncDevices();
}

void OneVNSyncClientImpl::SendResolveSyncRecords(
    const std::string &category_name,
    std::unique_ptr<SyncRecordAndExistingList> records_and_existing_objects) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  std::vector<extensions::api::onevn_sync::RecordAndExistingObject>
      records_and_existing_objects_ext;

  ConvertResolvedPairs(*records_and_existing_objects,
                       records_and_existing_objects_ext);

  onevn_sync_event_router_->ResolveSyncRecords(category_name,
    records_and_existing_objects_ext);
}

void OneVNSyncClientImpl::SendSyncRecords(const std::string &category_name,
                                          const RecordsList &records) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  std::vector<extensions::api::onevn_sync::SyncRecord> records_ext;
  ConvertSyncRecordsFromLibToExt(records, records_ext);

  onevn_sync_event_router_->SendSyncRecords(category_name, records_ext);
}

void OneVNSyncClientImpl::SendDeleteSyncUser()  {
  NOTIMPLEMENTED();
}

void OneVNSyncClientImpl::SendDeleteSyncCategory(
    const std::string& category_name) {
  NOTIMPLEMENTED();
}

void OneVNSyncClientImpl::SendGetBookmarksBaseOrder(
    const std::string& device_id,
    const std::string& platform) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  onevn_sync_event_router_->SendGetBookmarksBaseOrder(device_id, platform);
}

void OneVNSyncClientImpl::NeedSyncWords(const std::string &seed) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  onevn_sync_event_router_->NeedSyncWords(seed);
}

void OneVNSyncClientImpl::OnExtensionInitialized() {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  DCHECK(extension_loaded_);
  if (extension_loaded_)
    onevn_sync_event_router_->LoadClient();
}

void OneVNSyncClientImpl::OnSyncEnabledChanged() {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  if (sync_prefs_->GetSyncEnabled()) {
    LoadOrUnloadExtension(true);
  } else {
    LoadOrUnloadExtension(false);
  }
}

void OneVNSyncClientImpl::OnExtensionReady(
    content::BrowserContext* browser_context,
    const extensions::Extension* extension) {
  if (extension->id() == onevn_sync_extension_id)
    handler_->BackgroundSyncStarted(true);
}

void OneVNSyncClientImpl::OnExtensionLoaded(
    content::BrowserContext* browser_context,
    const extensions::Extension* extension) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  if (extension->id() == onevn_sync_extension_id) {
    extension_loaded_ = true;
  }
}

void OneVNSyncClientImpl::OnExtensionUnloaded(
    content::BrowserContext* browser_context,
    const extensions::Extension* extension,
    extensions::UnloadedExtensionReason reason) {
  if (extension->id() == onevn_sync_extension_id) {
    extension_loaded_ = false;
    handler_->BackgroundSyncStopped(true);
  }
}

void OneVNSyncClientImpl::LoadOrUnloadExtension(bool load) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  base::FilePath onevn_sync_extension_path(FILE_PATH_LITERAL(""));
  onevn_sync_extension_path =
      onevn_sync_extension_path.Append(FILE_PATH_LITERAL("onevn_sync"));
  extensions::ExtensionSystem* system =
    extensions::ExtensionSystem::Get(profile_);
  extensions::ComponentLoader* component_loader =
    system->extension_service()->component_loader();
  if (load) {
    component_loader->Add(IDR_ONEVN_SYNC_EXTENSION, onevn_sync_extension_path);
  } else {
    // Remove by root path doesn't have effect, using extension id instead
    // component_loader->Remove(onevn_sync_extension_path);
    component_loader->Remove(onevn_sync_extension_id);
  }
}

void OneVNSyncClientImpl::OnExtensionSystemReady() {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  // observe changes in extension system
  extension_registry_observer_.Add(ExtensionRegistry::Get(profile_));
  DCHECK(!extension_loaded_);
  if (sync_prefs_->GetSyncEnabled()) {
    LoadOrUnloadExtension(true);
  }
}

void OneVNSyncClientImpl::ClearOrderMap() {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  onevn_sync_event_router_->ClearOrderMap();
}

}  // namespace onevn_sync
