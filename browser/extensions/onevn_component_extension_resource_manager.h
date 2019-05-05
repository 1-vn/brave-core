/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_EXTENSIONS_ONEVN_COMPONENT_EXTENSION_RESOURCE_MANAGER_H_
#define ONEVN_BROWSER_EXTENSIONS_ONEVN_COMPONENT_EXTENSION_RESOURCE_MANAGER_H_

#include "chrome/browser/extensions/chrome_component_extension_resource_manager.h"

namespace extensions {

class OnevnComponentExtensionResourceManager
    : public ChromeComponentExtensionResourceManager {
 public:
  OnevnComponentExtensionResourceManager();
  ~OnevnComponentExtensionResourceManager() override;

  DISALLOW_COPY_AND_ASSIGN(OnevnComponentExtensionResourceManager);
};

}  // namespace extensions

#endif  // ONEVN_BROWSER_EXTENSIONS_ONEVN_COMPONENT_EXTENSION_RESOURCE_MANAGER_H_
