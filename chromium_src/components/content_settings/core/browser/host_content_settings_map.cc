/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/components/content_settings/core/browser/onevn_content_settings_ephemeral_provider.h"
#include "onevn/components/content_settings/core/browser/onevn_content_settings_pref_provider.h"

#define EphemeralProvider OnevnEphemeralProvider
#define PrefProvider OnevnPrefProvider
#include "../../../../../../components/content_settings/core/browser/host_content_settings_map.cc"
#undef EphemeralProvider
#undef PrefProvider
