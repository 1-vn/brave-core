/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/net/onevn_tor_network_delegate_helper.h"

#include <memory>

#include "onevn/browser/renderer_host/onevn_navigation_ui_data.h"
#include "onevn/browser/tor/tor_profile_service.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/resource_request_info.h"
#include "content/public/common/url_constants.h"
#include "extensions/common/constants.h"
#include "net/url_request/url_request_context.h"

using content::BrowserThread;
using content::ResourceRequestInfo;

namespace onevn {

int OnBeforeURLRequest_TorWork(
    const ResponseCallback& next_callback,
    std::shared_ptr<OneVNRequestInfo> ctx) {
  DCHECK_CURRENTLY_ON(BrowserThread::IO);

  ResourceRequestInfo* resource_info =
    ResourceRequestInfo::ForRequest(ctx->request);
  if (!resource_info) {
    return net::OK;
  }

  const OneVNNavigationUIData* ui_data =
    static_cast<const OneVNNavigationUIData*>(
        resource_info->GetNavigationUIData());
  if (!ui_data) {
    return net::OK;
  }

  auto* tor_profile_service = ui_data->GetTorProfileService();
  if (!tor_profile_service) {
    return net::OK;
  }

  auto& request_url = ctx->request_url;
  if (request_url.SchemeIsHTTPOrHTTPS()) {
    auto* proxy_service = ctx->request->context()->proxy_resolution_service();
    return tor_profile_service->SetProxy(proxy_service, request_url, false);
  } else if (request_url.SchemeIs(content::kChromeUIScheme) ||
             request_url.SchemeIs(extensions::kExtensionScheme) ||
             request_url.SchemeIs(content::kChromeDevToolsScheme)) {
    // No proxy for internal schemes.
    return net::OK;
  } else {
    return net::ERR_DISALLOWED_URL_SCHEME;
  }
}

}  // namespace onevn
