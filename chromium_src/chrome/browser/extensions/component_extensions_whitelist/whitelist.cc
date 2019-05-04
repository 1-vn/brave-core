/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#define IsComponentExtensionWhitelisted IsComponentExtensionWhitelisted_ChromiumImpl  // NOLINT
#include "../../../../../../chrome/browser/extensions/component_extensions_whitelist/whitelist.cc"  // NOLINT
#undef IsComponentExtensionWhitelisted

#include "base/stl_util.h"
#include "onevn/common/extensions/extension_constants.h"
#include "onevn/components/onevn_extension/grit/onevn_extension.h"
#include "components/grit/onevn_components_resources.h"
#include "onevn/components/onevn_rewards/resources/extension/grit/onevn_rewards_extension_resources.h"
#include "onevn/components/onevn_sync/grit/onevn_sync_resources.h"
#include "onevn/components/onevn_webtorrent/grit/onevn_webtorrent_resources.h"

namespace extensions {

  bool IsComponentExtensionWhitelisted(const std::string& extension_id) {
    const char* const kAllowed[] = {
      onevn_extension_id,
      pdfjs_extension_id,
      onevn_rewards_extension_id,
      onevn_sync_extension_id,
      onevn_webtorrent_extension_id
    };

    for (size_t i = 0; i < base::size(kAllowed); ++i) {
      if (extension_id == kAllowed[i])
        return true;
    }

    return IsComponentExtensionWhitelisted_ChromiumImpl(extension_id);
  }

  bool IsComponentExtensionWhitelisted(int manifest_resource_id) {
    switch (manifest_resource_id) {
      // Please keep the list in alphabetical order.
      case IDR_ONEVN_EXTENSION:
      case IDR_ONEVN_REWARDS:
      case IDR_ONEVN_SYNC_EXTENSION:
      case IDR_ONEVN_WEBTORRENT:
        return true;
    }

    return IsComponentExtensionWhitelisted_ChromiumImpl(manifest_resource_id);
  }

}  // namespace extensions
