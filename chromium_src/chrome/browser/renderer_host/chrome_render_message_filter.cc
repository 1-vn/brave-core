/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/renderer_host/chrome_render_message_filter.h"
#include "onevn/browser/content_settings/onevn_cookie_settings_factory.h"

#define CookieSettingsFactory OnevnCookieSettingsFactory
#include "../../../../../../chrome/browser/renderer_host/chrome_render_message_filter.cc"  // NOLINT
#undef CookieSettingsFactory
