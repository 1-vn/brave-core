/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/extensions/api/onevn_sync_event_router.h"

#include "onevn/common/extensions/api/onevn_sync.h"
#include "chrome/browser/profiles/profile.h"
#include "extensions/browser/extension_event_histogram_value.h"

using extensions::api::onevn_sync::RecordAndExistingObject;

namespace extensions {

OneVNSyncEventRouter::OneVNSyncEventRouter(Profile* profile) :
    event_router_(EventRouter::Get(profile)) {
}

OneVNSyncEventRouter::~OneVNSyncEventRouter() {}

void OneVNSyncEventRouter::GotInitData(
    const onevn_sync::Uint8Array& seed,
    const onevn_sync::Uint8Array& device_id,
    const extensions::api::onevn_sync::Config& config,
    const std::string& sync_words) {
  const std::vector<int> arg_seed(seed.begin(), seed.end());
  const std::vector<int> arg_device_id(device_id.begin(), device_id.end());

  std::unique_ptr<base::ListValue> args(
     extensions::api::onevn_sync::OnGotInitData::Create(arg_seed,
                                                        arg_device_id,
                                                        config,
                                                        sync_words)
       .release());
  std::unique_ptr<Event> event(
     new Event(extensions::events::FOR_TEST,
       extensions::api::onevn_sync::OnGotInitData::kEventName,
       std::move(args)));
  event_router_->BroadcastEvent(std::move(event));
}

void OneVNSyncEventRouter::FetchSyncRecords(
    const std::vector<std::string>& category_names,
    const base::Time& startAt,
    const int max_records) {
  std::unique_ptr<base::ListValue> args(
     extensions::api::onevn_sync::OnFetchSyncRecords::Create(category_names,
       startAt.ToJsTime(), static_cast<double>(max_records))
       .release());
  std::unique_ptr<Event> event(
     new Event(extensions::events::FOR_TEST,
       extensions::api::onevn_sync::OnFetchSyncRecords::kEventName,
       std::move(args)));
  event_router_->BroadcastEvent(std::move(event));
}

void OneVNSyncEventRouter::FetchSyncDevices() {
  std::unique_ptr<base::ListValue> args(
     extensions::api::onevn_sync::OnFetchSyncDevices::Create()
       .release());

  std::unique_ptr<Event> event(
     new Event(extensions::events::FOR_TEST,
       extensions::api::onevn_sync::OnFetchSyncDevices::kEventName,
       std::move(args)));
  event_router_->BroadcastEvent(std::move(event));
}

void OneVNSyncEventRouter::ResolveSyncRecords(
    const std::string& category_name,
    const std::vector<RecordAndExistingObject>& records_and_existing_objects) {
  for (const auto & entry : records_and_existing_objects) {
    DCHECK(!entry.server_record.object_data.empty());
    DCHECK(!entry.local_record ||
        (entry.local_record->object_data == "bookmark" ||
        entry.local_record->object_data == "device" ||
        entry.local_record->object_data == "historySite" ||
        entry.local_record->object_data == "siteSetting"));
  }

  std::unique_ptr<base::ListValue> args(
     extensions::api::onevn_sync::OnResolveSyncRecords::Create(
          category_name,
          records_and_existing_objects).release());
  std::unique_ptr<Event> event(
     new Event(extensions::events::FOR_TEST,
       extensions::api::onevn_sync::OnResolveSyncRecords::kEventName,
       std::move(args)));

  event_router_->BroadcastEvent(std::move(event));
}

void OneVNSyncEventRouter::SendSyncRecords(
    const std::string& category_name,
    const std::vector<api::onevn_sync::SyncRecord>& records) {
  std::unique_ptr<base::ListValue> args(
     extensions::api::onevn_sync::OnSendSyncRecords::Create(
          category_name,
          records).release());
  std::unique_ptr<Event> event(
     new Event(extensions::events::FOR_TEST,
       extensions::api::onevn_sync::OnSendSyncRecords::kEventName,
       std::move(args)));

  event_router_->BroadcastEvent(std::move(event));
}

void OneVNSyncEventRouter::SendGetBookmarksBaseOrder(
    const std::string& device_id,
    const std::string& platform) {
  std::unique_ptr<base::ListValue> args(
     extensions::api::onevn_sync::OnSendGetBookmarksBaseOrder::Create(
        device_id, platform).release());
  std::unique_ptr<Event> event(
     new Event(extensions::events::FOR_TEST,
       extensions::api::onevn_sync::OnSendGetBookmarksBaseOrder::kEventName,
       std::move(args)));

  event_router_->BroadcastEvent(std::move(event));
}

void OneVNSyncEventRouter::NeedSyncWords(const std::string& seed) {
  std::unique_ptr<base::ListValue> args(
     extensions::api::onevn_sync::OnNeedSyncWords::Create(seed)
       .release());
  std::unique_ptr<Event> event(
     new Event(extensions::events::FOR_TEST,
       extensions::api::onevn_sync::OnNeedSyncWords::kEventName,
       std::move(args)));
  event_router_->BroadcastEvent(std::move(event));
}

void OneVNSyncEventRouter::LoadClient() {
  std::unique_ptr<base::ListValue> args(
     extensions::api::onevn_sync::OnLoadClient::Create()
       .release());

  std::unique_ptr<Event> event(
     new Event(extensions::events::FOR_TEST,
       extensions::api::onevn_sync::OnLoadClient::kEventName,
       std::move(args)));
  event_router_->BroadcastEvent(std::move(event));
}

void OneVNSyncEventRouter::ClearOrderMap() {
  auto args = std::make_unique<base::ListValue>();
  std::unique_ptr<Event> event(
     new Event(extensions::events::FOR_TEST,
       extensions::api::onevn_sync::OnClearOrderMap::kEventName,
       std::move(args)));
  event_router_->BroadcastEvent(std::move(event));
}

} // namespace extensions
