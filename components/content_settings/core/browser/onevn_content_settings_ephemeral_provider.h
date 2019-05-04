/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_CONTENT_SETTINGS_CORE_BROWSER_CONTENT_SETTINGS_EPHEMERAL_PROVIDER_H_
#define ONEVN_COMPONENTS_CONTENT_SETTINGS_CORE_BROWSER_CONTENT_SETTINGS_EPHEMERAL_PROVIDER_H_

#include "components/content_settings/core/browser/content_settings_ephemeral_provider.h"

namespace content_settings {

// See the comments of OneVNPrefProvider.
class OneVNEphemeralProvider : public EphemeralProvider {
 public:
  using EphemeralProvider::EphemeralProvider;
  ~OneVNEphemeralProvider() override {}

 private:
  // EphemeralProvider overrides:
  bool SetWebsiteSetting(const ContentSettingsPattern& primary_pattern,
                         const ContentSettingsPattern& secondary_pattern,
                         ContentSettingsType content_type,
                         const ResourceIdentifier& resource_identifier,
                         base::Value* value) override;

  DISALLOW_COPY_AND_ASSIGN(OneVNEphemeralProvider);
};

}  // namespace content_settings

#endif  // ONEVN_COMPONENTS_CONTENT_SETTINGS_CORE_BROWSER_CONTENT_SETTINGS_EPHEMERAL_PROVIDER_H_
