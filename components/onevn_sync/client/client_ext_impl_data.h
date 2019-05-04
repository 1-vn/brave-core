/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_SYNC_CLIENT_CLIENT_EXT_IMPL_DATA_H
#define ONEVN_COMPONENTS_ONEVN_SYNC_CLIENT_CLIENT_EXT_IMPL_DATA_H

#include <memory>
#include <vector>

#include "onevn/components/onevn_sync/jslib_messages_fwd.h"

namespace extensions {
namespace api {
namespace onevn_sync {
  struct Config;
  struct SyncRecord;
  struct RecordAndExistingObject;
}
}
}

namespace onevn_sync {
namespace client_data {
  class Config;
}
}

namespace onevn_sync {

void ConvertConfig(const onevn_sync::client_data::Config &config,
  extensions::api::onevn_sync::Config &config_extension);

void ConvertSyncRecords(const std::vector<extensions::api::onevn_sync::SyncRecord> &records_extension,
  std::vector<onevn_sync::SyncRecordPtr> &records);

void ConvertResolvedPairs(const SyncRecordAndExistingList &records_and_existing_objects,
  std::vector<extensions::api::onevn_sync::RecordAndExistingObject> &records_and_existing_objects_ext);

void ConvertSyncRecordsFromLibToExt(const std::vector<onevn_sync::SyncRecordPtr> &records,
  std::vector<extensions::api::onevn_sync::SyncRecord> &records_extension);

} // namespace onevn_sync

#endif // ONEVN_COMPONENTS_ONEVN_SYNC_CLIENT_CLIENT_EXT_IMPL_DATA_H
