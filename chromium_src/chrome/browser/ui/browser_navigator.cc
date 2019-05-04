/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/renderer_host/onevn_navigation_ui_data.h"
#include "onevn/common/webui_url_constants.h"
#include "chrome/browser/ui/browser_navigator_params.h"
#include "chrome/common/webui_url_constants.h"
#include "url/gurl.h"

namespace {
void AdjustNavigateParamsForURLOneVNImpl(NavigateParams* params) {
  if (params->url.SchemeIs(content::kOneVNUIScheme)) {
    GURL::Replacements replacements;
    replacements.SetSchemeStr(content::kChromeUIScheme);
    params->url = params->url.ReplaceComponents(replacements);
  }
}

bool IsHostAllowedInIncognitoOneVNImpl(const base::StringPiece& host) {
  if (host == kRewardsHost ||
      host == kOneVNUISyncHost ||
      host == chrome::kChromeUISyncInternalsHost) {
    return false;
  }

  return true;
}
}  // namespace

#define ChromeNavigationUIData OneVNNavigationUIData
#include "../../../../chrome/browser/ui/browser_navigator.cc"  // NOLINT
#undef ChromeNavigationUIData
