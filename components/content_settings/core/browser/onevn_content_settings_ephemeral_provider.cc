/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/components/content_settings/core/browser/onevn_content_settings_ephemeral_provider.h"

#include "onevn/components/onevn_shields/common/onevn_shield_constants.h"

namespace {

bool IsShieldsResourceID(
    const content_settings::ResourceIdentifier& resource_identifier) {
  if (resource_identifier == onevn_shields::kAds ||
      resource_identifier == onevn_shields::kTrackers ||
      resource_identifier == onevn_shields::kHTTPUpgradableResources ||
      resource_identifier == onevn_shields::kJavaScript ||
      resource_identifier == onevn_shields::kFingerprinting ||
      resource_identifier == onevn_shields::kOneVNShields ||
      resource_identifier == onevn_shields::kReferrers ||
      resource_identifier == onevn_shields::kCookies) {
    return true;
  } else {
    return false;
  }
}

}

namespace content_settings {

bool OneVNEphemeralProvider::SetWebsiteSetting(
    const ContentSettingsPattern& primary_pattern,
    const ContentSettingsPattern& secondary_pattern,
    ContentSettingsType content_type,
    const ResourceIdentifier& resource_identifier,
    base::Value* in_value) {
  // Prevent this handle shields configuration.
  if (content_type == CONTENT_SETTINGS_TYPE_PLUGINS &&
      IsShieldsResourceID(resource_identifier)) {
    return false;
  }

  // Only flash plugin setting can be reached here.
  DCHECK(resource_identifier.empty());

  return EphemeralProvider::SetWebsiteSetting(
      primary_pattern, secondary_pattern,
      content_type, resource_identifier, in_value);
}

}  // namespace content_settings
