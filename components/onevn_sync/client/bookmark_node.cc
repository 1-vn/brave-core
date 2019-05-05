#include "onevn/components/onevn_sync/client/bookmark_node.h"

namespace onevn_sync {

OnevnBookmarkPermanentNode::OnevnBookmarkPermanentNode(int64_t id)
    : bookmarks::BookmarkPermanentNode(id) {}

OnevnBookmarkPermanentNode::~OnevnBookmarkPermanentNode() = default;

bool OnevnBookmarkPermanentNode::IsVisible() const {
  return visible_;
}

}  // namespace onevn_sync
