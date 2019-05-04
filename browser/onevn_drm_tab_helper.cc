/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/onevn_drm_tab_helper.h"

#include "onevn/common/pref_names.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/navigation_handle.h"

#if BUILDFLAG(ENABLE_WIDEVINE_CDM_COMPONENT) || BUILDFLAG(BUNDLE_WIDEVINE_CDM)
#include "onevn/browser/widevine/widevine_utils.h"
#endif

OneVNDrmTabHelper::OneVNDrmTabHelper(content::WebContents* contents)
    : WebContentsObserver(contents), bindings_(contents, this) {}

OneVNDrmTabHelper::~OneVNDrmTabHelper() {}

bool OneVNDrmTabHelper::ShouldShowWidevineOptIn() const {
  // If the user already opted in, don't offer it.
  PrefService* prefs = ProfileManager::GetActiveUserProfile()->GetPrefs();
  if (prefs->GetBoolean(kWidevineOptedIn)) {
    return false;
  }

  return is_widevine_requested_;
}

void OneVNDrmTabHelper::DidStartNavigation(
    content::NavigationHandle* navigation_handle) {
  if (!navigation_handle->IsInMainFrame() ||
      navigation_handle->IsSameDocument()) {
    return;
  }
  is_widevine_requested_ = false;
#if BUILDFLAG(ENABLE_WIDEVINE_CDM_COMPONENT) || BUILDFLAG(BUNDLE_WIDEVINE_CDM)
  is_permission_requested_ = false;
#endif
}

void OneVNDrmTabHelper::OnWidevineKeySystemAccessRequest() {
  is_widevine_requested_ = true;

#if BUILDFLAG(ENABLE_WIDEVINE_CDM_COMPONENT) || BUILDFLAG(BUNDLE_WIDEVINE_CDM)
  if (ShouldShowWidevineOptIn() && !is_permission_requested_) {
    is_permission_requested_ = true;
    RequestWidevinePermission(web_contents());
  }
#endif
}

WEB_CONTENTS_USER_DATA_KEY_IMPL(OneVNDrmTabHelper)
