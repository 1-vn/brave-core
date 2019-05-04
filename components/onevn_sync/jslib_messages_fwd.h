/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_SYNC_JSLIB_MESSAGES_FWD_H_
#define ONEVN_COMPONENTS_ONEVN_SYNC_JSLIB_MESSAGES_FWD_H_

#include "build/build_config.h"

// TODO(darkdh): forward declaration with unique_ptr on Windows
#if defined(OS_WIN)
#include "onevn/components/onevn_sync/jslib_messages.h"
#else
namespace onevn_sync {
namespace jslib {
class SyncRecord;
}
}
#endif

namespace onevn_sync {

typedef std::unique_ptr<jslib::SyncRecord> SyncRecordPtr;
typedef std::vector<SyncRecordPtr> RecordsList;
typedef std::unique_ptr<RecordsList> RecordsListPtr;
typedef std::pair<SyncRecordPtr, SyncRecordPtr> SyncRecordAndExisting;
typedef std::unique_ptr<SyncRecordAndExisting> SyncRecordAndExistingPtr;
typedef std::vector<SyncRecordAndExistingPtr> SyncRecordAndExistingList;

using Uint8Array = std::vector<unsigned char>;

}  // namespace onevn_sync

#endif  // ONEVN_COMPONENTS_ONEVN_SYNC_JSLIB_MESSAGES_FWD_H_
