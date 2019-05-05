/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/renderer_host/onevn_navigation_ui_data.h"

#include <memory>

#include "base/memory/ptr_util.h"
#include "onevn/browser/tor/tor_profile_service_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "content/public/browser/web_contents.h"

OnevnNavigationUIData::OnevnNavigationUIData()
    : ChromeNavigationUIData(), tor_profile_service_(nullptr) {}

OnevnNavigationUIData::OnevnNavigationUIData(
    NavigationHandle* navigation_handle)
    : ChromeNavigationUIData(navigation_handle),
      tor_profile_service_(nullptr) {}

OnevnNavigationUIData::~OnevnNavigationUIData() {}

// static
std::unique_ptr<ChromeNavigationUIData>
OnevnNavigationUIData::CreateForMainFrameNavigation(
    content::WebContents* web_contents,
    WindowOpenDisposition disposition,
    int64_t data_reduction_proxy_page_id) {
  auto navigation_ui_data =
      ChromeNavigationUIData::CreateForMainFrameNavigation(
          web_contents, disposition, data_reduction_proxy_page_id);
  OnevnNavigationUIData* ui_data =
      static_cast<OnevnNavigationUIData*>(navigation_ui_data.get());

  Profile* profile =
      Profile::FromBrowserContext(web_contents->GetBrowserContext());
  TorProfileServiceFactory::SetTorNavigationUIData(profile, ui_data);

  return navigation_ui_data;
}

std::unique_ptr<content::NavigationUIData> OnevnNavigationUIData::Clone()
    const {
  content::NavigationUIData* chrome_copy =
      (ChromeNavigationUIData::Clone().release());
  OnevnNavigationUIData* copy =
      static_cast<OnevnNavigationUIData*>(chrome_copy);

  copy->tor_profile_service_ = tor_profile_service_;

  return base::WrapUnique(copy);
}

void OnevnNavigationUIData::SetTorProfileService(
    TorProfileService* tor_profile_service) {
  tor_profile_service_ = tor_profile_service;
}

TorProfileService* OnevnNavigationUIData::GetTorProfileService() const {
  return tor_profile_service_;
}
