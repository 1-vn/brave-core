/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_EXTENSIONS_ONEVN_EXTENSION_PROVIDER_H_
#define ONEVN_BROWSER_EXTENSIONS_ONEVN_EXTENSION_PROVIDER_H_

#include <string>

#include "extensions/browser/management_policy.h"

namespace extensions {

class OneVNExtensionProvider : public ManagementPolicy::Provider {
 public:
  OneVNExtensionProvider();
  ~OneVNExtensionProvider() override;
  std::string GetDebugPolicyProviderName() const override;
  bool UserMayLoad(const Extension* extension,
                   base::string16* error) const override;
  bool MustRemainInstalled(const Extension* extension,
                           base::string16* error) const override;
  static bool IsVetted(const extensions::Extension* extension);
  static bool IsVetted(const std::string id);
 private:
  DISALLOW_COPY_AND_ASSIGN(OneVNExtensionProvider);
};

}  // namespace extensions

#endif  // ONEVN_BROWSER_EXTENSIONS_ONEVN_EXTENSION_PROVIDER_H_
