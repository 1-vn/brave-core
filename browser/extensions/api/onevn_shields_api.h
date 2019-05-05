/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_EXTENSIONS_API_ONEVN_SHIELDS_API_H_
#define ONEVN_BROWSER_EXTENSIONS_API_ONEVN_SHIELDS_API_H_

#include "extensions/browser/extension_function.h"

namespace extensions {
namespace api {

class OnevnShieldsAllowScriptsOnceFunction : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnShields.allowScriptsOnce", UNKNOWN)

 protected:
  ~OnevnShieldsAllowScriptsOnceFunction() override;

  ResponseAction Run() override;
};

class OnevnShieldsContentSettingGetFunction
    : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnShields.get", UNKNOWN)

 protected:
  ~OnevnShieldsContentSettingGetFunction() override {}

  // ExtensionFunction:
  ResponseAction Run() override;
};

class OnevnShieldsContentSettingSetFunction
    : public UIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("onevnShields.set", UNKNOWN)

 protected:
  ~OnevnShieldsContentSettingSetFunction() override {}

  // ExtensionFunction:
  ResponseAction Run() override;
};

}  // namespace api
}  // namespace extensions

#endif  // ONEVN_BROWSER_EXTENSIONS_API_ONEVN_SHIELDS_API_H_
