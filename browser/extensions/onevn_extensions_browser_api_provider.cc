/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/extensions/onevn_extensions_browser_api_provider.h"

#include "onevn/common/extensions/api/generated_api_registration.h"
#include "extensions/browser/extension_function_registry.h"

// TOOD: I don't know why this isn't automatically linked in
#include "../gen/onevn/common/extensions/api/generated_api_registration.cc"

namespace extensions {

OnevnExtensionsBrowserAPIProvider::OnevnExtensionsBrowserAPIProvider() =
    default;
OnevnExtensionsBrowserAPIProvider::~OnevnExtensionsBrowserAPIProvider() =
    default;

void OnevnExtensionsBrowserAPIProvider::RegisterExtensionFunctions(
    ExtensionFunctionRegistry* registry) {
  // Generated APIs from Onevn.
  api::OnevnGeneratedFunctionRegistry::RegisterAll(registry);
}

}  // namespace extensions
