/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/net/onevn_referrals_network_delegate_helper.h"

#include "base/values.h"
#include "onevn/components/onevn_referrals/browser/onevn_referrals_service.h"
#include "onevn/common/network_constants.h"
#include "chrome/browser/browser_process.h"
#include "content/public/browser/browser_thread.h"
#include "extensions/common/url_pattern.h"
#include "net/url_request/url_request.h"

namespace onevn {

int OnBeforeStartTransaction_ReferralsWork(
    net::URLRequest* request,
    net::HttpRequestHeaders* headers,
    const ResponseCallback& next_callback,
    std::shared_ptr<OneVNRequestInfo> ctx) {
  if (!ctx->referral_headers_list)
    return net::OK;
  // If the domain for this request matches one of our target domains,
  // set the associated custom headers.
  const base::DictionaryValue* request_headers_dict = nullptr;
  if (!OneVNReferralsService::GetMatchingReferralHeaders(
          *ctx->referral_headers_list, &request_headers_dict, request->url()))
    return net::OK;
  for (const auto& it : request_headers_dict->DictItems()) {
    if (it.first == kOneVNPartnerHeader) {
      headers->SetHeader(it.first, it.second.GetString());
    }
  }
  return net::OK;
}

}  // namespace onevn
