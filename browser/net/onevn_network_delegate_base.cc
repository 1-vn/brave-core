/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/net/onevn_network_delegate_base.h"

#include <algorithm>
#include <utility>

#include "base/task/post_task.h"
#include "onevn/browser/onevn_browser_process_impl.h"
#include "onevn/common/pref_names.h"
#include "onevn/components/onevn_shields/browser/ad_block_custom_filters_service.h"
#include "onevn/components/onevn_shields/browser/ad_block_regional_service_manager.h"
#include "onevn/components/onevn_shields/browser/ad_block_service.h"
#include "onevn/components/onevn_shields/browser/onevn_shields_util.h"
#include "onevn/components/onevn_shields/browser/onevn_shields_web_contents_observer.h"
#include "onevn/components/onevn_shields/common/onevn_shield_constants.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/content_settings/tab_specific_content_settings.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "components/prefs/pref_change_registrar.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/browser_task_traits.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/render_frame_host.h"
#include "content/public/browser/web_contents.h"
#include "net/base/registry_controlled_domains/registry_controlled_domain.h"
#include "net/url_request/url_request.h"

using content::BrowserThread;
using net::HttpResponseHeaders;
using net::URLRequest;

namespace {

content::WebContents* GetWebContentsFromProcessAndFrameId(int render_process_id,
                                                          int render_frame_id) {
  if (render_process_id) {
    content::RenderFrameHost* rfh =
        content::RenderFrameHost::FromID(render_process_id, render_frame_id);
    return content::WebContents::FromRenderFrameHost(rfh);
  }
  // TODO(iefremov): Seems like a typo?
  // issues/2263
  return content::WebContents::FromFrameTreeNodeId(render_frame_id);
}

std::string GetTagFromPrefName(const std::string& pref_name) {
  if (pref_name == kFBEmbedControlType) {
    return onevn_shields::kFacebookEmbeds;
  }
  if (pref_name == kTwitterEmbedControlType) {
    return onevn_shields::kTwitterEmbeds;
  }
  if (pref_name == kLinkedInEmbedControlType) {
    return onevn_shields::kLinkedInEmbeds;
  }
  return "";
}

}  // namespace

base::flat_set<base::StringPiece>* TrackableSecurityHeaders() {
  static base::NoDestructor<base::flat_set<base::StringPiece>>
      kTrackableSecurityHeaders(base::flat_set<base::StringPiece>{
          "Strict-Transport-Security", "Expect-CT", "Public-Key-Pins",
          "Public-Key-Pins-Report-Only"});
  return kTrackableSecurityHeaders.get();
}

void RemoveTrackableSecurityHeadersForThirdParty(
    URLRequest* request,
    const net::HttpResponseHeaders* original_response_headers,
    scoped_refptr<net::HttpResponseHeaders>* override_response_headers) {
  if (!request || !request->top_frame_origin().has_value() ||
      (!original_response_headers && !override_response_headers->get())) {
    return;
  }

  auto top_frame_origin = request->top_frame_origin().value();
  auto request_url = request->url();

  if (net::registry_controlled_domains::SameDomainOrHost(
          request_url, top_frame_origin,
          net::registry_controlled_domains::INCLUDE_PRIVATE_REGISTRIES)) {
    return;
  }

  if (!override_response_headers->get()) {
    *override_response_headers =
        new net::HttpResponseHeaders(original_response_headers->raw_headers());
  }
  for (auto header : *TrackableSecurityHeaders()) {
    (*override_response_headers)->RemoveHeader(header.as_string());
  }
}

OneVNNetworkDelegateBase::OneVNNetworkDelegateBase(
    extensions::EventRouterForwarder* event_router)
    : ChromeNetworkDelegate(event_router), referral_headers_list_(nullptr),
      allow_google_auth_(true) {
  // Initialize the preference change registrar.
  base::PostTaskWithTraits(
      FROM_HERE, {BrowserThread::UI},
      base::Bind(&OneVNNetworkDelegateBase::InitPrefChangeRegistrarOnUI,
                 base::Unretained(this)));
}

OneVNNetworkDelegateBase::~OneVNNetworkDelegateBase() {}

void OneVNNetworkDelegateBase::InitPrefChangeRegistrarOnUI() {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  PrefService* prefs = g_browser_process->local_state();
  pref_change_registrar_.reset(new PrefChangeRegistrar());
  pref_change_registrar_->Init(prefs);
  pref_change_registrar_->Add(
      kReferralHeaders,
      base::Bind(&OneVNNetworkDelegateBase::OnReferralHeadersChanged,
                 base::Unretained(this)));
  // Retrieve current referral headers, if any.
  OnReferralHeadersChanged();

  PrefService* user_prefs = ProfileManager::GetActiveUserProfile()->GetPrefs();
  user_pref_change_registrar_.reset(new PrefChangeRegistrar());
  user_pref_change_registrar_->Init(user_prefs);
  user_pref_change_registrar_->Add(
      kGoogleLoginControlType,
      base::BindRepeating(&OneVNNetworkDelegateBase::OnPreferenceChanged,
                          base::Unretained(this), kGoogleLoginControlType));
  user_pref_change_registrar_->Add(
      kFBEmbedControlType,
      base::BindRepeating(&OneVNNetworkDelegateBase::OnPreferenceChanged,
                          base::Unretained(this), kFBEmbedControlType));
  user_pref_change_registrar_->Add(
      kTwitterEmbedControlType,
      base::BindRepeating(&OneVNNetworkDelegateBase::OnPreferenceChanged,
                          base::Unretained(this), kTwitterEmbedControlType));
  user_pref_change_registrar_->Add(
      kLinkedInEmbedControlType,
      base::BindRepeating(&OneVNNetworkDelegateBase::OnPreferenceChanged,
                          base::Unretained(this), kLinkedInEmbedControlType));
  UpdateAdBlockFromPref(kFBEmbedControlType);
  UpdateAdBlockFromPref(kTwitterEmbedControlType);
  UpdateAdBlockFromPref(kLinkedInEmbedControlType);
  allow_google_auth_ = user_prefs->GetBoolean(kGoogleLoginControlType);
}

void OneVNNetworkDelegateBase::OnReferralHeadersChanged() {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  if (const base::ListValue* referral_headers =
          g_browser_process->local_state()->GetList(kReferralHeaders)) {
    base::PostTaskWithTraits(
        FROM_HERE, {BrowserThread::IO},
        base::Bind(&OneVNNetworkDelegateBase::SetReferralHeaders,
                   base::Unretained(this), referral_headers->DeepCopy()));
  }
}

void OneVNNetworkDelegateBase::SetReferralHeaders(
    base::ListValue* referral_headers) {
  DCHECK_CURRENTLY_ON(BrowserThread::IO);
  referral_headers_list_.reset(referral_headers);
}

int OneVNNetworkDelegateBase::OnBeforeURLRequest(
    URLRequest* request,
    net::CompletionOnceCallback callback,
    GURL* new_url) {
  if (before_url_request_callbacks_.empty() || !request) {
    return ChromeNetworkDelegate::OnBeforeURLRequest(
        request, std::move(callback), new_url);
  }
  std::shared_ptr<onevn::OneVNRequestInfo> ctx(new onevn::OneVNRequestInfo());
  onevn::OneVNRequestInfo::FillCTXFromRequest(request, ctx);
  ctx->new_url = new_url;
  ctx->event_type = onevn::kOnBeforeRequest;
  callbacks_[request->identifier()] = std::move(callback);
  RunNextCallback(request, ctx);
  return net::ERR_IO_PENDING;
}

int OneVNNetworkDelegateBase::OnBeforeStartTransaction(
    URLRequest* request,
    net::CompletionOnceCallback callback,
    net::HttpRequestHeaders* headers) {
  if (before_start_transaction_callbacks_.empty() || !request) {
    return ChromeNetworkDelegate::OnBeforeStartTransaction(
        request, std::move(callback), headers);
  }
  std::shared_ptr<onevn::OneVNRequestInfo> ctx(new onevn::OneVNRequestInfo());
  onevn::OneVNRequestInfo::FillCTXFromRequest(request, ctx);
  ctx->event_type = onevn::kOnBeforeStartTransaction;
  ctx->headers = headers;
  ctx->referral_headers_list = referral_headers_list_.get();
  callbacks_[request->identifier()] = std::move(callback);
  RunNextCallback(request, ctx);
  return net::ERR_IO_PENDING;
}

int OneVNNetworkDelegateBase::OnHeadersReceived(
    URLRequest* request,
    net::CompletionOnceCallback callback,
    const net::HttpResponseHeaders* original_response_headers,
    scoped_refptr<net::HttpResponseHeaders>* override_response_headers,
    GURL* allowed_unsafe_redirect_url) {
  RemoveTrackableSecurityHeadersForThirdParty(
      request, original_response_headers, override_response_headers);

  if (headers_received_callbacks_.empty() || !request) {
    return ChromeNetworkDelegate::OnHeadersReceived(
        request, std::move(callback), original_response_headers,
        override_response_headers, allowed_unsafe_redirect_url);
  }

  std::shared_ptr<onevn::OneVNRequestInfo> ctx(new onevn::OneVNRequestInfo());
  callbacks_[request->identifier()] = std::move(callback);
  onevn::OneVNRequestInfo::FillCTXFromRequest(request, ctx);
  ctx->event_type = onevn::kOnHeadersReceived;
  ctx->original_response_headers = original_response_headers;
  ctx->override_response_headers = override_response_headers;
  ctx->allowed_unsafe_redirect_url = allowed_unsafe_redirect_url;

  // Return ERR_IO_PENDING and run callbacks later by posting a task.
  // URLRequestHttpJob::awaiting_callback_ will be set to true after we
  // return net::ERR_IO_PENDING here, callbacks need to be run later than this
  // to set awaiting_callback_ back to false.
  base::PostTaskWithTraits(
      FROM_HERE, {BrowserThread::IO},
      base::Bind(&OneVNNetworkDelegateBase::RunNextCallback,
                 base::Unretained(this), request, ctx));
  return net::ERR_IO_PENDING;
}

bool OneVNNetworkDelegateBase::OnCanGetCookies(
    const URLRequest& request,
    const net::CookieList& cookie_list,
    bool allowed_from_caller) {
  std::shared_ptr<onevn::OneVNRequestInfo> ctx(new onevn::OneVNRequestInfo());
  ctx->allow_google_auth = allow_google_auth_;
  onevn::OneVNRequestInfo::FillCTXFromRequest(&request, ctx);
  ctx->event_type = onevn::kOnCanGetCookies;
  bool allow = std::all_of(can_get_cookies_callbacks_.begin(),
                           can_get_cookies_callbacks_.end(),
                           [&ctx](onevn::OnCanGetCookiesCallback callback) {
                             return callback.Run(ctx);
                           });

  base::RepeatingCallback<content::WebContents*(void)> wc_getter =
      base::BindRepeating(&GetWebContentsFromProcessAndFrameId,
                          ctx->render_process_id, ctx->render_frame_id);
  base::PostTaskWithTraits(
      FROM_HERE, {BrowserThread::UI},
      base::BindOnce(&TabSpecificContentSettings::CookiesRead, wc_getter,
                     request.url(), request.site_for_cookies(), cookie_list,
                     !allow));

  return allow;
}

bool OneVNNetworkDelegateBase::OnCanSetCookie(
    const URLRequest& request,
    const net::CanonicalCookie& cookie,
    net::CookieOptions* options,
    bool allowed_from_caller) {
  std::shared_ptr<onevn::OneVNRequestInfo> ctx(new onevn::OneVNRequestInfo());
  ctx->allow_google_auth = allow_google_auth_;
  onevn::OneVNRequestInfo::FillCTXFromRequest(&request, ctx);
  ctx->event_type = onevn::kOnCanSetCookies;

  bool allow = std::all_of(can_set_cookies_callbacks_.begin(),
                           can_set_cookies_callbacks_.end(),
                           [&ctx](onevn::OnCanSetCookiesCallback callback) {
                             return callback.Run(ctx);
                           });

  base::RepeatingCallback<content::WebContents*(void)> wc_getter =
      base::BindRepeating(&GetWebContentsFromProcessAndFrameId,
                          ctx->render_process_id, ctx->render_frame_id);
  base::PostTaskWithTraits(
      FROM_HERE, {BrowserThread::UI},
      base::BindOnce(&TabSpecificContentSettings::CookieChanged, wc_getter,
                     request.url(), request.site_for_cookies(), cookie,
                     !allow));

  return allow;
}

void OneVNNetworkDelegateBase::RunCallbackForRequestIdentifier(
    uint64_t request_identifier,
    int rv) {
  std::map<uint64_t, net::CompletionOnceCallback>::iterator it =
      callbacks_.find(request_identifier);
  std::move(it->second).Run(rv);
}

void OneVNNetworkDelegateBase::RunNextCallback(
    URLRequest* request,
    std::shared_ptr<onevn::OneVNRequestInfo> ctx) {
  DCHECK_CURRENTLY_ON(BrowserThread::IO);

  if (!ContainsKey(callbacks_, ctx->request_identifier)) {
    return;
  }

  if (request->status().status() == net::URLRequestStatus::CANCELED) {
    return;
  }

  // Continue processing callbacks until we hit one that returns PENDING
  int rv = net::OK;

  if (ctx->event_type == onevn::kOnBeforeRequest) {
    while (before_url_request_callbacks_.size() !=
           ctx->next_url_request_index) {
      onevn::OnBeforeURLRequestCallback callback =
          before_url_request_callbacks_[ctx->next_url_request_index++];
      onevn::ResponseCallback next_callback =
          base::Bind(&OneVNNetworkDelegateBase::RunNextCallback,
                     base::Unretained(this), request, ctx);
      rv = callback.Run(next_callback, ctx);
      if (rv == net::ERR_IO_PENDING) {
        return;
      }
      if (rv != net::OK) {
        break;
      }
    }
  } else if (ctx->event_type == onevn::kOnBeforeStartTransaction) {
    while (before_start_transaction_callbacks_.size() !=
           ctx->next_url_request_index) {
      onevn::OnBeforeStartTransactionCallback callback =
          before_start_transaction_callbacks_[ctx->next_url_request_index++];
      onevn::ResponseCallback next_callback =
          base::Bind(&OneVNNetworkDelegateBase::RunNextCallback,
                     base::Unretained(this), request, ctx);
      rv = callback.Run(request, ctx->headers, next_callback, ctx);
      if (rv == net::ERR_IO_PENDING) {
        return;
      }
      if (rv != net::OK) {
        break;
      }
    }
  } else if (ctx->event_type == onevn::kOnHeadersReceived) {
    while (headers_received_callbacks_.size() != ctx->next_url_request_index) {
      onevn::OnHeadersReceivedCallback callback =
          headers_received_callbacks_[ctx->next_url_request_index++];
      onevn::ResponseCallback next_callback =
          base::Bind(&OneVNNetworkDelegateBase::RunNextCallback,
                     base::Unretained(this), request, ctx);
      rv = callback.Run(request, ctx->original_response_headers,
                        ctx->override_response_headers,
                        ctx->allowed_unsafe_redirect_url, next_callback, ctx);
      if (rv == net::ERR_IO_PENDING) {
        return;
      }
      if (rv != net::OK) {
        break;
      }
    }
  }

  if (rv != net::OK) {
    RunCallbackForRequestIdentifier(ctx->request_identifier, rv);
    return;
  }

  net::CompletionOnceCallback wrapped_callback =
      base::BindOnce(&OneVNNetworkDelegateBase::RunCallbackForRequestIdentifier,
                     base::Unretained(this), ctx->request_identifier);

  if (ctx->event_type == onevn::kOnBeforeRequest) {
    if (!ctx->new_url_spec.empty() &&
        (ctx->new_url_spec != ctx->request_url.spec()) &&
        IsRequestIdentifierValid(ctx->request_identifier)) {
      *ctx->new_url = GURL(ctx->new_url_spec);
    }
    if (ctx->blocked_by == onevn::kAdBlocked ||
        ctx->blocked_by == onevn::kTrackerBlocked) {
      // We are going to intercept this request and block it later in the
      // network stack.
      if (ctx->cancel_request_explicitly) {
        RunCallbackForRequestIdentifier(ctx->request_identifier,
            net::ERR_ABORTED);
        return;
      }
      request->SetExtraRequestHeaderByName("X-OneVN-Block", "", true);
    }
    rv = ChromeNetworkDelegate::OnBeforeURLRequest(
        request, std::move(wrapped_callback), ctx->new_url);
  } else if (ctx->event_type == onevn::kOnBeforeStartTransaction) {
    rv = ChromeNetworkDelegate::OnBeforeStartTransaction(
        request, std::move(wrapped_callback), ctx->headers);
  } else if (ctx->event_type == onevn::kOnHeadersReceived) {
    rv = ChromeNetworkDelegate::OnHeadersReceived(
        request, std::move(wrapped_callback), ctx->original_response_headers,
        ctx->override_response_headers, ctx->allowed_unsafe_redirect_url);
  }

  // ChromeNetworkDelegate returns net::ERR_IO_PENDING if an extension is
  // intercepting the request and OK if the request should proceed normally.
  if (rv != net::ERR_IO_PENDING) {
    RunCallbackForRequestIdentifier(ctx->request_identifier, rv);
  }
}

void OneVNNetworkDelegateBase::OnURLRequestDestroyed(URLRequest* request) {
  if (ContainsKey(callbacks_, request->identifier())) {
    callbacks_.erase(request->identifier());
  }
  ChromeNetworkDelegate::OnURLRequestDestroyed(request);
}

bool OneVNNetworkDelegateBase::IsRequestIdentifierValid(
    uint64_t request_identifier) {
  return ContainsKey(callbacks_, request_identifier);
}

void OneVNNetworkDelegateBase::OnPreferenceChanged(
    const std::string& pref_name) {
  UpdateAdBlockFromPref(pref_name);
}

void OneVNNetworkDelegateBase::UpdateAdBlockFromPref(
    const std::string& pref_name) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  PrefService* user_prefs = ProfileManager::GetActiveUserProfile()->GetPrefs();
  allow_google_auth_ = user_prefs->GetBoolean(kGoogleLoginControlType);
  std::string tag = GetTagFromPrefName(pref_name);
  if (tag.length() == 0) {
    return;
  }
  bool enabled = user_prefs->GetBoolean(pref_name);
  g_onevn_browser_process->ad_block_service()->EnableTag(tag, enabled);
  g_onevn_browser_process->ad_block_regional_service_manager()->EnableTag(
      tag, enabled);
  g_onevn_browser_process->ad_block_custom_filters_service()->EnableTag(
      tag, enabled);
}
