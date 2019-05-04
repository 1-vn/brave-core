/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/onevn_tab_helpers.h"

#include "onevn/browser/onevn_drm_tab_helper.h"
#include "onevn/components/onevn_ads/browser/ads_tab_helper.h"
#include "onevn/components/onevn_rewards/browser/buildflags/buildflags.h"
#include "onevn/components/onevn_shields/browser/buildflags/buildflags.h"  // For STP
#include "content/public/browser/web_contents.h"

#if !defined(OS_ANDROID)
#include "onevn/components/onevn_shields/browser/onevn_shields_web_contents_observer.h"
#if BUILDFLAG(ONEVN_REWARDS_ENABLED)
#include "onevn/components/onevn_rewards/browser/rewards_helper.h"
#endif
#if BUILDFLAG(ONEVN_STP_ENABLED)
#include "onevn/components/onevn_shields/browser/tracking_protection_helper.h"

using onevn_shields::TrackingProtectionHelper;
#endif
// Add tab helpers here unless they are intended for android too
#endif

namespace onevn {

void AttachTabHelpers(content::WebContents* web_contents) {
#if !defined(OS_ANDROID)
  onevn_shields::OneVNShieldsWebContentsObserver::CreateForWebContents(
      web_contents);
#if BUILDFLAG(ONEVN_REWARDS_ENABLED)
  onevn_rewards::RewardsHelper::CreateForWebContents(web_contents);
#endif
  // Add tab helpers here unless they are intended for android too
  OneVNDrmTabHelper::CreateForWebContents(web_contents);
#if BUILDFLAG(ONEVN_STP_ENABLED)
  if (TrackingProtectionHelper::IsSmartTrackingProtectionEnabled()) {
    onevn_shields::TrackingProtectionHelper::CreateForWebContents(web_contents);
  }
#endif
#endif

  onevn_ads::AdsTabHelper::CreateForWebContents(web_contents);
}

}  // namespace onevn
