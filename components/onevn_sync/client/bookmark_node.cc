#include "onevn/components/onevn_sync/client/bookmark_node.h"

namespace onevn_sync {

OneVNBookmarkPermanentNode::OneVNBookmarkPermanentNode(int64_t id)
    : bookmarks::BookmarkPermanentNode(id) {}

OneVNBookmarkPermanentNode::~OneVNBookmarkPermanentNode() = default;

bool OneVNBookmarkPermanentNode::IsVisible() const {
  return visible_;
}

}  // namespace onevn_sync
