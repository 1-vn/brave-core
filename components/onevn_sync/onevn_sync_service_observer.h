/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_SYNC_ONEVN_SYNC_SERVICE_OBSERVER_H_
#define ONEVN_COMPONENTS_ONEVN_SYNC_ONEVN_SYNC_SERVICE_OBSERVER_H_

namespace onevn_sync {

class OnevnSyncService;

class OnevnSyncServiceObserver : public base::CheckedObserver {
 public:
  ~OnevnSyncServiceObserver() override {}

  virtual void OnSyncSetupError(OnevnSyncService* sync_service,
                                const std::string& error) {}
  virtual void OnSyncStateChanged(OnevnSyncService* sync_service) {}
  virtual void OnHaveSyncWords(OnevnSyncService* sync_service,
                               const std::string& sync_words) {}
};

} // namespace onevn_sync

#endif // ONEVN_COMPONENTS_ONEVN_SYNC_ONEVN_SYNC_SERVICE_OBSERVER_H_
