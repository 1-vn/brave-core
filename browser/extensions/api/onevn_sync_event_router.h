/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_EXTENSIONS_API_ONEVN_SYNC_EVENT_ROUTER_H_
#define ONEVN_BROWSER_EXTENSIONS_API_ONEVN_SYNC_EVENT_ROUTER_H_

#include <string>
#include "extensions/browser/event_router.h"

class Profile;

namespace extensions {
namespace api {
namespace onevn_sync {
struct SyncRecord;
struct Config;
struct RecordAndExistingObject;
} // namespace onevn_sync
} // namespace api
} // namespace extensions

using extensions::api::onevn_sync::RecordAndExistingObject;

namespace onevn_sync {
using Uint8Array = std::vector<unsigned char>;
}

namespace extensions {

class OneVNSyncEventRouter {
 public:
  OneVNSyncEventRouter(Profile* profile);
  ~OneVNSyncEventRouter();

  void GotInitData(
    const onevn_sync::Uint8Array& seed,
    const onevn_sync::Uint8Array& device_id,
    const extensions::api::onevn_sync::Config& config,
    const std::string& sync_words);

  void FetchSyncRecords(
    const std::vector<std::string>& category_names,
    const base::Time& startAt,
    const int max_records);

  void FetchSyncDevices();

  void ResolveSyncRecords(const std::string &category_name,
    const std::vector<RecordAndExistingObject>& records_and_existing_objects);

  void SendSyncRecords(const std::string& category_name,
                       const std::vector<api::onevn_sync::SyncRecord>& records);

  void SendGetBookmarksBaseOrder(const std::string& device_id,
                                 const std::string& platform);

  void NeedSyncWords(const std::string& seed);

  void ClearOrderMap();

  void LoadClient();

private:
  EventRouter* event_router_;
};

} // namespace extensions

#endif // ONEVN_BROWSER_EXTENSIONS_API_ONEVN_SYNC_EVENT_ROUTER_H_
