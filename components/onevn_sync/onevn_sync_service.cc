/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "onevn/components/onevn_sync/onevn_sync_service.h"

#include "base/command_line.h"
#include "onevn/common/onevn_switches.h"
#include "onevn/components/onevn_sync/onevn_sync_service_observer.h"

namespace onevn_sync {

OnevnSyncService::OnevnSyncService() {}
OnevnSyncService::~OnevnSyncService() {}

void OnevnSyncService::AddObserver(OnevnSyncServiceObserver* observer) {
  observers_.AddObserver(observer);
}

void OnevnSyncService::RemoveObserver(OnevnSyncServiceObserver* observer) {
  observers_.RemoveObserver(observer);
}

// static
bool OnevnSyncService::is_enabled() {
  const base::CommandLine& command_line =
      *base::CommandLine::ForCurrentProcess();
  return !command_line.HasSwitch(switches::kDisableOnevnSync);
}

}  // namespace onevn_sync
