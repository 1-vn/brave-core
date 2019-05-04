/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/extensions/onevn_component_extension_resource_manager.h"

#include "onevn/components/onevn_extension/grit/onevn_extension_generated_map.h"
#include "onevn/components/onevn_extension/grit/onevn_extension_resources_map.h"
#include "onevn/components/onevn_rewards/resources/extension/grit/onevn_rewards_extension_resources_map.h"
#include "onevn/components/onevn_rewards/resources/extension/grit/onevn_rewards_panel_generated_map.h"
#include "onevn/components/onevn_sync/grit/onevn_sync_generated_map.h"
#include "onevn/components/onevn_sync/grit/onevn_sync_resources_map.h"
#include "onevn/components/onevn_webtorrent/grit/onevn_webtorrent_resources_map.h"
#include "onevn/components/onevn_webtorrent/grit/onevn_webtorrent_generated_map.h"

namespace extensions {

OneVNComponentExtensionResourceManager::
OneVNComponentExtensionResourceManager() {
  AddComponentResourceEntries(
      kOneVNExtension,
      kOneVNExtensionSize);

  AddComponentResourceEntries(
      kOneVNExtensionGenerated,
      kOneVNExtensionGeneratedSize);

  AddComponentResourceEntries(
      kOneVNRewardsExtensionResources,
      kOneVNRewardsExtensionResourcesSize);

  AddComponentResourceEntries(
      kOneVNRewardsPanelGenerated,
      kOneVNRewardsPanelGeneratedSize);

  AddComponentResourceEntries(
      kOneVNSyncResources,
      kOneVNSyncResourcesSize);

  AddComponentResourceEntries(
      kOneVNSyncGenerated,
      kOneVNSyncGeneratedSize);

  AddComponentResourceEntries(
      kOneVNWebtorrentResources,
      kOneVNWebtorrentResourcesSize);

  AddComponentResourceEntries(
      kOneVNWebtorrentGenerated,
      kOneVNWebtorrentGeneratedSize);
}

OneVNComponentExtensionResourceManager::
~OneVNComponentExtensionResourceManager() {}

}  // namespace extensions
