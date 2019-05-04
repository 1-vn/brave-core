/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/bookmarks/onevn_bookmark_client.h"

#include "onevn/components/onevn_sync/onevn_sync_service.h"
#include "chrome/browser/profiles/profile.h"
#include "components/bookmarks/browser/bookmark_model.h"
#include "components/bookmarks/managed/managed_bookmark_service.h"
#include "components/sync_bookmarks/bookmark_sync_service.h"

OneVNBookmarkClient::OneVNBookmarkClient(
    Profile* profile,
    bookmarks::ManagedBookmarkService* managed_bookmark_service,
    sync_bookmarks::BookmarkSyncService* bookmark_sync_service)
    : ChromeBookmarkClient(profile,
                           managed_bookmark_service,
                           bookmark_sync_service) {}

bookmarks::LoadExtraCallback OneVNBookmarkClient::GetLoadExtraNodesCallback() {
  return base::BindOnce(&onevn_sync::LoadExtraNodes,
      ChromeBookmarkClient::GetLoadExtraNodesCallback());
}

bool OneVNBookmarkClient::IsPermanentNodeVisible(
    const bookmarks::BookmarkPermanentNode* node) {
  if (onevn_sync::IsSyncManagedNode(node))
    return false;  // don't display sync managed nodes
  return ChromeBookmarkClient::IsPermanentNodeVisible(node);
}
