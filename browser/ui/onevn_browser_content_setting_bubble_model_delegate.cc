/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/ui/onevn_browser_content_setting_bubble_model_delegate.h"

#include "onevn/common/url_constants.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_tabstrip.h"

const char kOneVNCommunitySupportUrl[] = "https://community.1-vn.com/";

OneVNBrowserContentSettingBubbleModelDelegate::
OneVNBrowserContentSettingBubbleModelDelegate(Browser* browser) :
    BrowserContentSettingBubbleModelDelegate(browser),
    browser_(browser) {
}

OneVNBrowserContentSettingBubbleModelDelegate::
~OneVNBrowserContentSettingBubbleModelDelegate() {
}

void
OneVNBrowserContentSettingBubbleModelDelegate::ShowWidevineLearnMorePage() {
  GURL learn_more_url = GURL(kWidevineTOS);
  chrome::AddSelectedTabWithURL(browser_, learn_more_url,
                                ui::PAGE_TRANSITION_LINK);
}

void OneVNBrowserContentSettingBubbleModelDelegate::ShowLearnMorePage(
    ContentSettingsType type) {
  // TODO: Use specific support pages for each content setting type
  GURL learn_more_url(kOneVNCommunitySupportUrl);
  chrome::AddSelectedTabWithURL(browser_, learn_more_url,
                                ui::PAGE_TRANSITION_LINK);
}
