/* Copyright 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_SHIELDS_BROWSER_TRACKING_PROTECTION_HELPER_H_
#define ONEVN_COMPONENTS_ONEVN_SHIELDS_BROWSER_TRACKING_PROTECTION_HELPER_H_

#include "base/macros.h"
#include "base/strings/string16.h"
#include "base/synchronization/lock.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"

namespace content {
class WebContents;
class NavigationHandle;
}  // namespace content

namespace onevn_shields {

class TrackingProtectionHelper
    : public content::WebContentsObserver,
      public content::WebContentsUserData<TrackingProtectionHelper> {
 public:
  explicit TrackingProtectionHelper(content::WebContents*);
  ~TrackingProtectionHelper() override;
  void ReadyToCommitNavigation(
      content::NavigationHandle* navigation_handle) override;
  void RenderFrameHostChanged(content::RenderFrameHost* old_host,
                              content::RenderFrameHost* new_host) override;
  void RenderFrameDeleted(content::RenderFrameHost* render_frame_host) override;
  static bool IsSmartTrackingProtectionEnabled();
  WEB_CONTENTS_USER_DATA_KEY_DECL();

 private:
  friend class content::WebContentsUserData<TrackingProtectionHelper>;

  DISALLOW_COPY_AND_ASSIGN(TrackingProtectionHelper);
};

}  // namespace onevn_shields

#endif  // ONEVN_COMPONENTS_ONEVN_SHIELDS_BROWSER_TRACKING_PROTECTION_HELPER_H_
