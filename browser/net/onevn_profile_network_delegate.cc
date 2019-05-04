/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/net/onevn_profile_network_delegate.h"

#include "onevn/browser/net/onevn_ad_block_tp_network_delegate_helper.h"
#include "onevn/browser/net/onevn_common_static_redirect_network_delegate_helper.h"
#include "onevn/browser/net/cookie_network_delegate_helper.h"
#include "onevn/browser/net/onevn_httpse_network_delegate_helper.h"
#include "onevn/browser/net/onevn_referrals_network_delegate_helper.h"
#include "onevn/browser/net/onevn_site_hacks_network_delegate_helper.h"
#include "onevn/browser/net/onevn_tor_network_delegate_helper.h"
#include "onevn/browser/net/onevn_translate_redirect_network_delegate_helper.h"
#include "onevn/common/pref_names.h"
#include "onevn/components/onevn_rewards/browser/buildflags/buildflags.h"
#if BUILDFLAG(ONEVN_REWARDS_ENABLED)
#include "onevn/components/onevn_rewards/browser/net/network_delegate_helper.h"
#endif
#include "onevn/components/onevn_webtorrent/browser/net/onevn_torrent_redirect_network_delegate_helper.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "components/prefs/pref_service.h"

OneVNProfileNetworkDelegate::OneVNProfileNetworkDelegate(
    extensions::EventRouterForwarder* event_router) :
    OneVNNetworkDelegateBase(event_router) {
  onevn::OnBeforeURLRequestCallback
  callback =
      base::Bind(onevn::OnBeforeURLRequest_SiteHacksWork);
  before_url_request_callbacks_.push_back(callback);

  callback =
      base::Bind(onevn::OnBeforeURLRequest_AdBlockTPPreWork);
  before_url_request_callbacks_.push_back(callback);

  callback =
      base::Bind(onevn::OnBeforeURLRequest_HttpsePreFileWork);
  before_url_request_callbacks_.push_back(callback);

  callback =
      base::Bind(onevn::OnBeforeURLRequest_CommonStaticRedirectWork);
  before_url_request_callbacks_.push_back(callback);

#if BUILDFLAG(ONEVN_REWARDS_ENABLED)
  callback = base::Bind(onevn_rewards::OnBeforeURLRequest);
  before_url_request_callbacks_.push_back(callback);
#endif

  callback = base::Bind(onevn::OnBeforeURLRequest_TorWork);
  before_url_request_callbacks_.push_back(callback);

  callback = base::BindRepeating(
      onevn::OnBeforeURLRequest_TranslateRedirectWork);
  before_url_request_callbacks_.push_back(callback);

  onevn::OnBeforeStartTransactionCallback start_transaction_callback =
      base::Bind(onevn::OnBeforeStartTransaction_SiteHacksWork);
  before_start_transaction_callbacks_.push_back(start_transaction_callback);

  start_transaction_callback =
      base::Bind(onevn::OnBeforeStartTransaction_ReferralsWork);
  before_start_transaction_callbacks_.push_back(start_transaction_callback);

  onevn::OnHeadersReceivedCallback headers_received_callback =
      base::Bind(
          webtorrent::OnHeadersReceived_TorrentRedirectWork);
  headers_received_callbacks_.push_back(headers_received_callback);

  onevn::OnCanGetCookiesCallback get_cookies_callback =
      base::Bind(onevn::OnCanGetCookiesForOneVNShields);
  can_get_cookies_callbacks_.push_back(get_cookies_callback);

  onevn::OnCanSetCookiesCallback set_cookies_callback =
      base::Bind(onevn::OnCanSetCookiesForOneVNShields);
  can_set_cookies_callbacks_.push_back(set_cookies_callback);
}

OneVNProfileNetworkDelegate::~OneVNProfileNetworkDelegate() {
}
