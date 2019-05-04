/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/ui/webui/settings/onevn_privacy_handler.h"

#include <string>

#include "base/bind.h"
#include "base/values.h"
#include "chrome/common/pref_names.h"
#include "chrome/browser/profiles/profile.h"
#include "components/prefs/pref_service.h"
#include "content/public/common/webrtc_ip_handling_policy.h"
#include "content/public/browser/web_ui.h"

void OneVNPrivacyHandler::RegisterMessages() {
  profile_ = Profile::FromWebUI(web_ui());

  web_ui()->RegisterMessageCallback(
      "getWebRTCPolicy",
      base::BindRepeating(&OneVNPrivacyHandler::GetWebRTCPolicy,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "setWebRTCPolicy",
      base::BindRepeating(&OneVNPrivacyHandler::SetWebRTCPolicy,
                          base::Unretained(this)));
}

void OneVNPrivacyHandler::SetWebRTCPolicy(const base::ListValue* args) {
  CHECK_EQ(args->GetSize(), 1U);
  CHECK(profile_);

  std::string policy;
  args->GetString(0, &policy);
  profile_->GetPrefs()->SetString(prefs::kWebRTCIPHandlingPolicy, policy);
}

void OneVNPrivacyHandler::GetWebRTCPolicy(const base::ListValue* args) {
  CHECK_EQ(args->GetSize(), 1U);
  CHECK(profile_);

  std::string policy =
    profile_->GetPrefs()->GetString(prefs::kWebRTCIPHandlingPolicy);

  AllowJavascript();
  ResolveJavascriptCallback(
      args->GetList()[0].Clone(),
      base::Value(policy));
}
