/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_SYNC_CLIENT_BOOKMARK_NODE_H_
#define ONEVN_COMPONENTS_ONEVN_SYNC_CLIENT_BOOKMARK_NODE_H_

#include "components/bookmarks/browser/bookmark_node.h"

namespace onevn_sync {

// Sync Managed PerrmanentNode
class OnevnBookmarkPermanentNode : public bookmarks::BookmarkPermanentNode {
 public:
  explicit OnevnBookmarkPermanentNode(int64_t id);
  ~OnevnBookmarkPermanentNode() override;

  void set_visible(bool value) { visible_ = value; }

  // BookmarkNode overrides:
  bool IsVisible() const override;

 private:
  bool visible_ = false;

  DISALLOW_COPY_AND_ASSIGN(OnevnBookmarkPermanentNode);
};

}  // namespace onevn_sync

#endif  // ONEVN_COMPONENTS_ONEVN_SYNC_CLIENT_BOOKMARK_NODE_H_
