/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/renderer_host/onevn_navigation_ui_data.h"

#include <memory>

#include "base/memory/ptr_util.h"
#include "onevn/browser/tor/tor_profile_service_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "content/public/browser/web_contents.h"

OneVNNavigationUIData::OneVNNavigationUIData()
    : ChromeNavigationUIData(), tor_profile_service_(nullptr) {}

OneVNNavigationUIData::OneVNNavigationUIData(
    NavigationHandle* navigation_handle)
    : ChromeNavigationUIData(navigation_handle),
      tor_profile_service_(nullptr) {}

OneVNNavigationUIData::~OneVNNavigationUIData() {}

// static
std::unique_ptr<ChromeNavigationUIData>
OneVNNavigationUIData::CreateForMainFrameNavigation(
    content::WebContents* web_contents,
    WindowOpenDisposition disposition,
    int64_t data_reduction_proxy_page_id) {
  auto navigation_ui_data =
      ChromeNavigationUIData::CreateForMainFrameNavigation(
          web_contents, disposition, data_reduction_proxy_page_id);
  OneVNNavigationUIData* ui_data =
      static_cast<OneVNNavigationUIData*>(navigation_ui_data.get());

  Profile* profile =
      Profile::FromBrowserContext(web_contents->GetBrowserContext());
  TorProfileServiceFactory::SetTorNavigationUIData(profile, ui_data);

  return navigation_ui_data;
}

std::unique_ptr<content::NavigationUIData> OneVNNavigationUIData::Clone()
    const {
  content::NavigationUIData* chrome_copy =
      (ChromeNavigationUIData::Clone().release());
  OneVNNavigationUIData* copy =
      static_cast<OneVNNavigationUIData*>(chrome_copy);

  copy->tor_profile_service_ = tor_profile_service_;

  return base::WrapUnique(copy);
}

void OneVNNavigationUIData::SetTorProfileService(
    TorProfileService* tor_profile_service) {
  tor_profile_service_ = tor_profile_service;
}

TorProfileService* OneVNNavigationUIData::GetTorProfileService() const {
  return tor_profile_service_;
}
