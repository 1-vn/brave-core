/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/extensions/api/onevn_theme_api.h"

#include <memory>
#include <string>

#include "base/json/json_writer.h"
#include "base/values.h"
#include "onevn/browser/themes/onevn_theme_service.h"
#include "onevn/common/extensions/api/onevn_theme.h"
#include "chrome/browser/profiles/profile.h"

using BTS = OneVNThemeService;

namespace extensions {
namespace api {

ExtensionFunction::ResponseAction OneVNThemeGetOneVNThemeListFunction::Run() {
  std::string json_string;
  base::JSONWriter::Write(BTS::GetOneVNThemeList(), &json_string);
  return RespondNow(OneArgument(std::make_unique<base::Value>(json_string)));
}

ExtensionFunction::ResponseAction OneVNThemeGetOneVNThemeTypeFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  const std::string theme_type = BTS::GetStringFromOneVNThemeType(
      BTS::GetActiveOneVNThemeType(profile));
  return RespondNow(OneArgument(std::make_unique<base::Value>(theme_type)));
}

}  // namespace api
}  // namespace extensions
