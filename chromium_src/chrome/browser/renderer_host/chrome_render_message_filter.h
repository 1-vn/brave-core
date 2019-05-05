/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_CHROMIUM_SRC_CHROME_BROWSER_RENDERER_HOST_CHROME_RENDER_MESSAGE_FILTER_H_
#define ONEVN_CHROMIUM_SRC_CHROME_BROWSER_RENDERER_HOST_CHROME_RENDER_MESSAGE_FILTER_H_

#include "onevn/components/content_settings/core/browser/onevn_cookie_settings.h"

#define CookieSettings OnevnCookieSettings
#include "../../../../../../chrome/browser/renderer_host/chrome_render_message_filter.h"
#undef CookieSettings

#endif  // ONEVN_CHROMIUM_SRC_CHROME_BROWSER_RENDERER_HOST_CHROME_RENDER_MESSAGE_FILTER_H_
