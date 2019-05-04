/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/components/onevn_webtorrent/browser/webtorrent_util.h"

#include "onevn/common/extensions/extension_constants.h"
#include "chrome/browser/profiles/profile.h"
#include "extensions/browser/extension_registry.h"

namespace webtorrent {

bool IsWebtorrentEnabled(content::BrowserContext* browser_context) {
  bool isTorProfile =
    Profile::FromBrowserContext(browser_context)->IsTorProfile();
  extensions::ExtensionRegistry* registry =
    extensions::ExtensionRegistry::Get(browser_context);
  return !isTorProfile &&
    registry->enabled_extensions().Contains(onevn_webtorrent_extension_id);
}

}  // webtorrent

