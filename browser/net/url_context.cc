/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */


#include "onevn/browser/net/url_context.h"

#include <memory>
#include <string>

#include "onevn/common/pref_names.h"
#include "onevn/common/url_constants.h"
#include "onevn/components/onevn_shields/browser/onevn_shields_util.h"
#include "onevn/components/onevn_shields/browser/onevn_shields_web_contents_observer.h"
#include "onevn/components/onevn_shields/common/onevn_shield_constants.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "components/prefs/testing_pref_service.h"
#include "content/public/browser/resource_request_info.h"

namespace onevn {

OnevnRequestInfo::OnevnRequestInfo() {
}

OnevnRequestInfo::~OnevnRequestInfo() {
}

void OnevnRequestInfo::FillCTXFromRequest(const net::URLRequest* request,
    std::shared_ptr<onevn::OnevnRequestInfo> ctx) {
  ctx->request_identifier = request->identifier();
  ctx->request_url = request->url();
  if (request->initiator().has_value()) {
    ctx->initiator_url = request->initiator()->GetURL();
  }
  auto* request_info = content::ResourceRequestInfo::ForRequest(request);
  if (request_info) {
    ctx->resource_type = request_info->GetResourceType();
  }
  onevn_shields::GetRenderFrameInfo(request,
                                    &ctx->render_frame_id,
                                    &ctx->render_process_id,
                                    &ctx->frame_tree_node_id);
  if (!request->site_for_cookies().is_empty()) {
    ctx->tab_url = request->site_for_cookies();
  } else {
    // We can not always use site_for_cookies since it can be empty in certain
    // cases. See the comments in url_request.h
    ctx->tab_url = onevn_shields::OnevnShieldsWebContentsObserver::
        GetTabURLFromRenderFrameInfo(ctx->render_process_id,
                                     ctx->render_frame_id,
                                     ctx->frame_tree_node_id).GetOrigin();
  }
  ctx->tab_origin = ctx->tab_url.GetOrigin();
  ctx->allow_onevn_shields = onevn_shields::IsAllowContentSettingFromIO(
      request, ctx->tab_origin, ctx->tab_origin, CONTENT_SETTINGS_TYPE_PLUGINS,
      onevn_shields::kOnevnShields) &&
    !request->site_for_cookies().SchemeIs(kChromeExtensionScheme);
  ctx->allow_ads = onevn_shields::IsAllowContentSettingFromIO(
      request, ctx->tab_origin, ctx->tab_origin, CONTENT_SETTINGS_TYPE_PLUGINS,
      onevn_shields::kAds);
  ctx->allow_http_upgradable_resource =
      onevn_shields::IsAllowContentSettingFromIO(request, ctx->tab_origin,
          ctx->tab_origin, CONTENT_SETTINGS_TYPE_PLUGINS,
      onevn_shields::kHTTPUpgradableResources);
  ctx->allow_1p_cookies = onevn_shields::IsAllowContentSettingFromIO(
      request, ctx->tab_origin, GURL("https://firstParty/"),
      CONTENT_SETTINGS_TYPE_PLUGINS, onevn_shields::kCookies);
  ctx->allow_3p_cookies = onevn_shields::IsAllowContentSettingFromIO(
      request, ctx->tab_origin, GURL(), CONTENT_SETTINGS_TYPE_PLUGINS,
      onevn_shields::kCookies);
  ctx->request = request;
}

}  // namespace onevn
