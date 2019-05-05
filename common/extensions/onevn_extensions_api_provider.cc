/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/common/extensions/onevn_extensions_api_provider.h"

#include "onevn/common/extensions/api/generated_includes.h"
#include "extensions/common/features/json_feature_provider_source.h"
#include "extensions/common/permissions/permissions_info.h"

namespace extensions {

OnevnExtensionsAPIProvider::OnevnExtensionsAPIProvider() {}
OnevnExtensionsAPIProvider::~OnevnExtensionsAPIProvider() = default;

void OnevnExtensionsAPIProvider::AddAPIFeatures(FeatureProvider* provider) {
  AddOnevnAPIFeatures(provider);
}

void OnevnExtensionsAPIProvider::AddManifestFeatures(
    FeatureProvider* provider) {
  AddOnevnManifestFeatures(provider);
}

void OnevnExtensionsAPIProvider::AddPermissionFeatures(
    FeatureProvider* provider) {
  AddOnevnPermissionFeatures(provider);
}

void OnevnExtensionsAPIProvider::AddBehaviorFeatures(
    FeatureProvider* provider) {
  // No onevn-specific behavior features.
}

void OnevnExtensionsAPIProvider::AddAPIJSONSources(
    JSONFeatureProviderSource* json_source) {
  json_source->LoadJSON(IDR_ONEVN_EXTENSION_API_FEATURES);
}

bool OnevnExtensionsAPIProvider::IsAPISchemaGenerated(
    const std::string& name) {
  return api::OnevnGeneratedSchemas::IsGenerated(name);
}

base::StringPiece OnevnExtensionsAPIProvider::GetAPISchema(
    const std::string& name) {
  return api::OnevnGeneratedSchemas::Get(name);
}

void OnevnExtensionsAPIProvider::RegisterPermissions(
    PermissionsInfo* permissions_info) {
  // No onevn-specific permissions.
}

void OnevnExtensionsAPIProvider::RegisterManifestHandlers() {
  // No onevn-specific manifest handlers.
}

}  // namespace extensions
