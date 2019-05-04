/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/devtools/onevn_devtools_ui_bindings.h"

#include "base/values.h"
#include "onevn/browser/themes/onevn_theme_service.h"
#include "chrome/common/pref_names.h"
#include "components/prefs/pref_service.h"

namespace {
std::string GetDevToolsUIThemeValue(Profile* profile) {
  OneVNThemeType theme_type =
      OneVNThemeService::GetActiveOneVNThemeType(profile);
  // In devtools' theme, default is translated to light.
  return theme_type == ONEVN_THEME_TYPE_DARK ? "\"dark\"" : "\"default\"";
}
}

void OneVNDevToolsUIBindings::GetPreferences(const DispatchCallback& callback) {
  const base::DictionaryValue* prefs =
      profile_->GetPrefs()->GetDictionary(prefs::kDevToolsPreferences);

  if (prefs->FindKey("uiTheme"))
    return DevToolsUIBindings::GetPreferences(callback);

  base::Value new_prefs(prefs->Clone());
  new_prefs.SetKey("uiTheme", base::Value(GetDevToolsUIThemeValue(profile())));
  callback.Run(&new_prefs);
}
