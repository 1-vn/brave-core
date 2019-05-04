/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/common/extensions/onevn_extensions_api_provider.h"

#include "onevn/common/extensions/api/generated_includes.h"
#include "extensions/common/features/json_feature_provider_source.h"
#include "extensions/common/permissions/permissions_info.h"

namespace extensions {

OneVNExtensionsAPIProvider::OneVNExtensionsAPIProvider() {}
OneVNExtensionsAPIProvider::~OneVNExtensionsAPIProvider() = default;

void OneVNExtensionsAPIProvider::AddAPIFeatures(FeatureProvider* provider) {
  AddOneVNAPIFeatures(provider);
}

void OneVNExtensionsAPIProvider::AddManifestFeatures(
    FeatureProvider* provider) {
  AddOneVNManifestFeatures(provider);
}

void OneVNExtensionsAPIProvider::AddPermissionFeatures(
    FeatureProvider* provider) {
  AddOneVNPermissionFeatures(provider);
}

void OneVNExtensionsAPIProvider::AddBehaviorFeatures(
    FeatureProvider* provider) {
  // No onevn-specific behavior features.
}

void OneVNExtensionsAPIProvider::AddAPIJSONSources(
    JSONFeatureProviderSource* json_source) {
  json_source->LoadJSON(IDR_ONEVN_EXTENSION_API_FEATURES);
}

bool OneVNExtensionsAPIProvider::IsAPISchemaGenerated(
    const std::string& name) {
  return api::OneVNGeneratedSchemas::IsGenerated(name);
}

base::StringPiece OneVNExtensionsAPIProvider::GetAPISchema(
    const std::string& name) {
  return api::OneVNGeneratedSchemas::Get(name);
}

void OneVNExtensionsAPIProvider::RegisterPermissions(
    PermissionsInfo* permissions_info) {
  // No onevn-specific permissions.
}

void OneVNExtensionsAPIProvider::RegisterManifestHandlers() {
  // No onevn-specific manifest handlers.
}

}  // namespace extensions
