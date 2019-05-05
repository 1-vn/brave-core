/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/extensions/api/settings_private/onevn_prefs_util.h"

#include "onevn/common/pref_names.h"
#include "chrome/browser/extensions/api/settings_private/prefs_util.h"
#include "chrome/common/pref_names.h"
#include "chrome/common/extensions/api/settings_private.h"
#include "components/browsing_data/core/pref_names.h"

namespace extensions {

namespace settings_api = api::settings_private;

const PrefsUtil::TypedPrefMap& OnevnPrefsUtil::GetWhitelistedKeys() {
  // Static cache, similar to parent class
  static PrefsUtil::TypedPrefMap* s_onevn_whitelist = nullptr;
  if (s_onevn_whitelist)
    return *s_onevn_whitelist;
  s_onevn_whitelist = new PrefsUtil::TypedPrefMap();
  // Start with parent class whitelist
  const auto chromium_prefs = PrefsUtil::GetWhitelistedKeys();
  s_onevn_whitelist->insert(chromium_prefs.begin(), chromium_prefs.end());
  // Add Onevn values to the whitelist
  // import data
  (*s_onevn_whitelist)[::prefs::kImportDialogCookies] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_onevn_whitelist)[::prefs::kImportDialogStats] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_onevn_whitelist)[::prefs::kImportDialogLedger] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_onevn_whitelist)[::prefs::kImportDialogWindows] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  // Default Onevn shields
  (*s_onevn_whitelist)[kHTTPSEVerywhereControlType] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_onevn_whitelist)[kNoScriptControlType] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_onevn_whitelist)[kGoogleLoginControlType] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_onevn_whitelist)[kFBEmbedControlType] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_onevn_whitelist)[kTwitterEmbedControlType] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_onevn_whitelist)[kLinkedInEmbedControlType] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;

  // appearance prefs
  (*s_onevn_whitelist)[kLocationBarIsWide] =
    settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_onevn_whitelist)[kHideOnevnRewardsButton] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_onevn_whitelist)[kOnevnThemeType] =
      settings_api::PrefType::PREF_TYPE_NUMBER;
  // Clear browsing data on exit prefs.
  (*s_onevn_whitelist)[browsing_data::prefs::kDeleteBrowsingHistoryOnExit] =
    settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_onevn_whitelist)[browsing_data::prefs::kDeleteDownloadHistoryOnExit] =
    settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_onevn_whitelist)[browsing_data::prefs::kDeleteCacheOnExit] =
    settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_onevn_whitelist)[browsing_data::prefs::kDeleteCookiesOnExit] =
    settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_onevn_whitelist)[browsing_data::prefs::kDeletePasswordsOnExit] =
    settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_onevn_whitelist)[browsing_data::prefs::kDeleteFormDataOnExit] =
    settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_onevn_whitelist)[browsing_data::prefs::kDeleteSiteSettingsOnExit] =
    settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_onevn_whitelist)[browsing_data::prefs::kDeleteHostedAppsDataOnExit] =
    settings_api::PrefType::PREF_TYPE_BOOLEAN;
  // WebTorrent pref
  (*s_onevn_whitelist)[kWebTorrentEnabled] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  // Hangouts pref
  (*s_onevn_whitelist)[kHangoutsEnabled] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  // IPFS Companion pref
  (*s_onevn_whitelist)[kIPFSCompanionEnabled] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  return *s_onevn_whitelist;
}

}  // namespace extensions
