/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/components/onevn_shields/browser/buildflags/buildflags.h"  // For STP
#include "build/build_config.h"  // For OS_MACOSX
#include "chrome/browser/search/search.h"
#include "content/public/browser/browser_url_handler.h"

#if BUILDFLAG(ONEVN_STP_ENABLED)
#include "onevn/browser/renderer_host/onevn_render_message_filter.h"
#undef ChromeRenderMessageFilter
#define ChromeRenderMessageFilter OnevnRenderMessageFilter
#endif

#if defined(OS_MACOSX)
#include "onevn/browser/onevn_browser_main_parts_mac.h"
#undef ChromeBrowserMainPartsMac
#define ChromeBrowserMainPartsMac OnevnBrowserMainPartsMac
#endif

#if defined(OS_LINUX)
#include "onevn/browser/ui/views/onevn_browser_main_extra_parts_views_linux.h"
#define ChromeBrowserMainExtraPartsViewsLinux OnevnBrowserMainExtraPartsViewsLinux // NOLINT
#endif

#define HandleNewTabURLRewrite HandleNewTabURLRewrite_ChromiumImpl
#define HandleNewTabURLReverseRewrite HandleNewTabURLReverseRewrite_ChromiumImpl

namespace search {
  bool HandleNewTabURLRewrite(GURL * url, content::BrowserContext * bc) {
    return false;
  }
  bool HandleNewTabURLReverseRewrite(GURL * url, content::BrowserContext * bc) {
    return false;
  }
}  // namespace search

#include "../../../../chrome/browser/chrome_content_browser_client.cc"  // NOLINT

#undef HandleNewTabURLRewrite
#undef HandleNewTabURLReverseRewrite_ChromiumImpl

#if defined(OS_LINUX)
#undef ChromeBrowserMainExtraPartsViewsLinux
#endif
