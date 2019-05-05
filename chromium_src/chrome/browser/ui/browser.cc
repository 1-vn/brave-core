/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/ui/browser_command_controller.h"
#include "chrome/browser/ui/browser_content_setting_bubble_model_delegate.h"
#include "onevn/browser/ui/onevn_browser_content_setting_bubble_model_delegate.h"
#include "onevn/browser/ui/onevn_browser_command_controller.h"
#include "onevn/browser/ui/toolbar/onevn_location_bar_model_delegate.h"

#define BrowserContentSettingBubbleModelDelegate \
  OnevnBrowserContentSettingBubbleModelDelegate
#define BrowserCommandController OnevnBrowserCommandController
#define BrowserLocationBarModelDelegate OnevnLocationBarModelDelegate
#include "../../../../../chrome/browser/ui/browser.cc"  // NOLINT
#undef BrowserLocationBarModelDelegate
#undef BrowserContentSettingBubbleModelDelegate
#undef BrowserCommandController
