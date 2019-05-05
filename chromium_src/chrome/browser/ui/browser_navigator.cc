/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/renderer_host/onevn_navigation_ui_data.h"
#include "onevn/common/webui_url_constants.h"
#include "chrome/browser/ui/browser_navigator_params.h"
#include "chrome/common/webui_url_constants.h"
#include "url/gurl.h"

namespace {
void AdjustNavigateParamsForURLOnevnImpl(NavigateParams* params) {
  if (params->url.SchemeIs(content::kOnevnUIScheme)) {
    GURL::Replacements replacements;
    replacements.SetSchemeStr(content::kChromeUIScheme);
    params->url = params->url.ReplaceComponents(replacements);
  }
}

bool IsHostAllowedInIncognitoOnevnImpl(const base::StringPiece& host) {
  if (host == kRewardsHost ||
      host == kOnevnUISyncHost ||
      host == chrome::kChromeUISyncInternalsHost) {
    return false;
  }

  return true;
}
}  // namespace

#define ChromeNavigationUIData OnevnNavigationUIData
#include "../../../../chrome/browser/ui/browser_navigator.cc"  // NOLINT
#undef ChromeNavigationUIData
