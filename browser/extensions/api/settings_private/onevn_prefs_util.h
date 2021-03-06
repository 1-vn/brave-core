/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_EXTENSIONS_API_SETTINGS_PRIVATE_ONEVN_PREFS_UTIL_H
#define ONEVN_BROWSER_EXTENSIONS_API_SETTINGS_PRIVATE_ONEVN_PREFS_UTIL_H

#include "chrome/browser/extensions/api/settings_private/prefs_util.h"
namespace extensions{

class OnevnPrefsUtil : public PrefsUtil {
  public:
    using PrefsUtil::PrefsUtil;
    // Gets the list of whitelisted pref keys -- that is, those which correspond
    // to prefs that clients of the settingsPrivate API may retrieve and
    // manipulate.
    const PrefsUtil::TypedPrefMap& GetWhitelistedKeys() override;
};

}

#endif