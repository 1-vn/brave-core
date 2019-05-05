/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/components/content_settings/core/browser/onevn_cookie_settings.h"

#include "base/bind.h"
#include "onevn/common/onevn_cookie_blocking.h"
#include "onevn/common/pref_names.h"
#include "onevn/components/onevn_shields/common/onevn_shield_constants.h"
#include "components/content_settings/core/common/cookie_settings_base.h"
#include "components/prefs/pref_service.h"
#include "extensions/buildflags/buildflags.h"
#include "net/base/registry_controlled_domains/registry_controlled_domain.h"
#include "url/gurl.h"

namespace content_settings {

using namespace net::registry_controlled_domains;  // NOLINT

OnevnCookieSettings::OnevnCookieSettings(
    HostContentSettingsMap* host_content_settings_map,
    PrefService* prefs,
    const char* extension_scheme)
    : CookieSettings(host_content_settings_map, prefs, extension_scheme),
      allow_google_auth_(prefs->GetBoolean(kGoogleLoginControlType)) {
  pref_change_registrar_.Init(prefs);
  pref_change_registrar_.Add(
      kGoogleLoginControlType,
      base::BindRepeating(&OnevnCookieSettings::OnAllowGoogleAuthChanged,
                          base::Unretained(this)));
}

OnevnCookieSettings::~OnevnCookieSettings() {}

void OnevnCookieSettings::GetCookieSetting(
    const GURL& url,
    const GURL& first_party_url,
    content_settings::SettingSource* source,
    ContentSetting* cookie_setting) const {
  GetCookieSetting(url, first_party_url, first_party_url, source,
                   cookie_setting);
}

void OnevnCookieSettings::GetCookieSetting(
    const GURL& url,
    const GURL& first_party_url,
    const GURL& tab_url,
    content_settings::SettingSource* source,
    ContentSetting* cookie_setting) const {
  DCHECK(cookie_setting);

  // Auto-allow in extensions or for WebUI embedded in a secure origin.
  // This matches an early return case in CookieSettings::GetCookieSetting
  if (first_party_url.SchemeIs(kChromeUIScheme) &&
      url.SchemeIsCryptographic()) {
    *cookie_setting = CONTENT_SETTING_ALLOW;
    return;
  }

  // This matches an early return case in CookieSettings::GetCookieSetting
#if BUILDFLAG(ENABLE_EXTENSIONS)
  if (url.SchemeIs(extension_scheme_) &&
      first_party_url.SchemeIs(extension_scheme_)) {
    *cookie_setting = CONTENT_SETTING_ALLOW;
    return;
  }
#endif

  CookieSettings::GetCookieSetting(url, first_party_url, source,
                                   cookie_setting);
  if (*cookie_setting == CONTENT_SETTING_BLOCK) {
    return;
  }

  GURL primary_url =
      (tab_url == GURL("about:blank") || tab_url.is_empty() ? first_party_url
                                                            : tab_url);

  ContentSetting onevn_shields_setting =
      host_content_settings_map_->GetContentSetting(
          primary_url, GURL(), CONTENT_SETTINGS_TYPE_PLUGINS,
          onevn_shields::kOnevnShields);
  ContentSetting onevn_1p_setting =
      host_content_settings_map_->GetContentSetting(
          primary_url, GURL("https://firstParty/"),
          CONTENT_SETTINGS_TYPE_PLUGINS, onevn_shields::kCookies);
  ContentSetting onevn_3p_setting =
      host_content_settings_map_->GetContentSetting(
          primary_url, GURL(), CONTENT_SETTINGS_TYPE_PLUGINS,
          onevn_shields::kCookies);

  bool allow_onevn_shields = onevn_shields_setting == CONTENT_SETTING_ALLOW ||
                             onevn_shields_setting == CONTENT_SETTING_DEFAULT;
  bool allow_1p_cookies = onevn_1p_setting == CONTENT_SETTING_ALLOW ||
                          onevn_1p_setting == CONTENT_SETTING_DEFAULT;
  bool allow_3p_cookies = onevn_3p_setting == CONTENT_SETTING_ALLOW;
  if (ShouldBlockCookie(allow_onevn_shields, allow_1p_cookies, allow_3p_cookies,
                        first_party_url, url, allow_google_auth_)) {
    *cookie_setting = CONTENT_SETTING_BLOCK;
  }
}

bool OnevnCookieSettings::IsCookieAccessAllowed(const GURL& url,
                                                const GURL& first_party_url,
                                                const GURL& tab_url) const {
  ContentSetting setting;
  GetCookieSetting(url, first_party_url, tab_url, nullptr, &setting);
  DCHECK(setting == CONTENT_SETTING_ALLOW ||
         setting == CONTENT_SETTING_SESSION_ONLY ||
         setting == CONTENT_SETTING_DEFAULT ||
         setting == CONTENT_SETTING_BLOCK);
  return setting == CONTENT_SETTING_ALLOW ||
         setting == CONTENT_SETTING_SESSION_ONLY;
}

void OnevnCookieSettings::OnAllowGoogleAuthChanged() {
  DCHECK(thread_checker_.CalledOnValidThread());
  base::AutoLock auto_lock(lock_);
  allow_google_auth_ =
      pref_change_registrar_.prefs()->GetBoolean(kGoogleLoginControlType);
}

}  // namespace content_settings
