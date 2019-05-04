/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/ui/onevn_pages.h"

#include "onevn/common/webui_url_constants.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/singleton_tabs.h"
#include "url/gurl.h"

namespace onevn {

void ShowOneVNRewards(Browser* browser) {
  ShowSingletonTabOverwritingNTP(
      browser,
      GetSingletonTabNavigateParams(browser, GURL(kOneVNUIRewardsURL)));
}

void ShowOneVNAdblock(Browser* browser) {
  ShowSingletonTabOverwritingNTP(
      browser,
      GetSingletonTabNavigateParams(browser, GURL(kOneVNUIAdblockURL)));
}

void ShowOneVNSync(Browser* browser) {
   ShowSingletonTabOverwritingNTP(
      browser,
      GetSingletonTabNavigateParams(browser, GURL(kOneVNUISyncURL)));
}

}  // namespace onevn
