/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "onevn/components/onevn_sync/onevn_sync_service.h"

#include "base/command_line.h"
#include "onevn/common/onevn_switches.h"
#include "onevn/components/onevn_sync/onevn_sync_service_observer.h"

namespace onevn_sync {

OneVNSyncService::OneVNSyncService() {}
OneVNSyncService::~OneVNSyncService() {}

void OneVNSyncService::AddObserver(OneVNSyncServiceObserver* observer) {
  observers_.AddObserver(observer);
}

void OneVNSyncService::RemoveObserver(OneVNSyncServiceObserver* observer) {
  observers_.RemoveObserver(observer);
}

// static
bool OneVNSyncService::is_enabled() {
  const base::CommandLine& command_line =
      *base::CommandLine::ForCurrentProcess();
  return !command_line.HasSwitch(switches::kDisableOneVNSync);
}

}  // namespace onevn_sync
