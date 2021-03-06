/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/net/onevn_site_hacks_network_delegate_helper.h"

#include <string>

#include "base/sequenced_task_runner.h"
#include "base/strings/string_util.h"
#include "onevn/common/network_constants.h"
#include "onevn/common/shield_exceptions.h"
#include "onevn/common/url_constants.h"
#include "onevn/components/onevn_shields/browser/onevn_shields_util.h"
#include "onevn/components/onevn_shields/browser/onevn_shields_web_contents_observer.h"
#include "onevn/components/onevn_shields/common/onevn_shield_constants.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/resource_request_info.h"
#include "content/public/common/referrer.h"
#include "extensions/common/url_pattern.h"
#include "net/url_request/url_request.h"

using content::BrowserThread;
using content::Referrer;

namespace onevn {

namespace {

bool ApplyPotentialReferrerBlock(std::shared_ptr<OnevnRequestInfo> ctx,
                                 net::URLRequest* request) {
  DCHECK_CURRENTLY_ON(BrowserThread::IO);
  GURL target_origin = request->url().GetOrigin();
  GURL tab_origin = ctx->tab_origin;
  if (tab_origin.SchemeIs(kChromeExtensionScheme)) {
    return false;
  }
  bool allow_referrers = onevn_shields::IsAllowContentSettingFromIO(
      request, tab_origin, tab_origin, CONTENT_SETTINGS_TYPE_PLUGINS,
      onevn_shields::kReferrers);
  bool shields_up = onevn_shields::IsAllowContentSettingFromIO(
      request, tab_origin, GURL(), CONTENT_SETTINGS_TYPE_PLUGINS,
      onevn_shields::kOnevnShields);
  const std::string original_referrer = request->referrer();
  Referrer new_referrer;
  if (onevn_shields::ShouldSetReferrer(allow_referrers, shields_up,
          GURL(original_referrer), tab_origin, request->url(), target_origin,
          Referrer::NetReferrerPolicyToBlinkReferrerPolicy(
              request->referrer_policy()), &new_referrer)) {
    request->SetReferrer(new_referrer.url.spec());
    return true;
  }
  return false;
}

}  // namespace

int OnBeforeURLRequest_SiteHacksWork(
    const ResponseCallback& next_callback,
    std::shared_ptr<OnevnRequestInfo> ctx) {
  ApplyPotentialReferrerBlock(ctx, const_cast<net::URLRequest*>(ctx->request));
  return net::OK;
}

void CheckForCookieOverride(const GURL& url, const URLPattern& pattern,
    net::HttpRequestHeaders* headers, const std::string& extra_cookies) {
  if (pattern.MatchesURL(url)) {
    std::string cookies;
    if (headers->GetHeader(kCookieHeader, &cookies)) {
      cookies = "; ";
    }
    cookies += extra_cookies;
    headers->SetHeader(kCookieHeader, cookies);
  }
}

bool IsBlockTwitterSiteHack(net::URLRequest* request,
    net::HttpRequestHeaders* headers) {
  URLPattern redirectURLPattern(URLPattern::SCHEME_ALL, kTwitterRedirectURL);
  URLPattern referrerPattern(URLPattern::SCHEME_ALL, kTwitterReferrer);
  if (redirectURLPattern.MatchesURL(request->url())) {
    std::string referrer;
    if (headers->GetHeader(kRefererHeader, &referrer) &&
        referrerPattern.MatchesURL(GURL(referrer))) {
      return true;
    }
  }
  return false;
}

int OnBeforeStartTransaction_SiteHacksWork(net::URLRequest* request,
        net::HttpRequestHeaders* headers,
        const ResponseCallback& next_callback,
        std::shared_ptr<OnevnRequestInfo> ctx) {
  CheckForCookieOverride(request->url(),
      URLPattern(URLPattern::SCHEME_ALL, kForbesPattern), headers,
      kForbesExtraCookies);
  if (IsBlockTwitterSiteHack(request, headers)) {
    return net::ERR_ABORTED;
  }
  if (IsUAWhitelisted(request->url())) {
    std::string user_agent;
    if (headers->GetHeader(kUserAgentHeader, &user_agent)) {
      base::ReplaceFirstSubstringAfterOffset(&user_agent, 0, "Chrome", "Onevn Chrome");
      headers->SetHeader(kUserAgentHeader, user_agent);
    }
  }
  return net::OK;
}

}  // namespace onevn
