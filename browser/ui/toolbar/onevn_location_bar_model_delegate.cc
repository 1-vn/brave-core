/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/ui/toolbar/onevn_location_bar_model_delegate.h"

#include "base/strings/utf_string_conversions.h"

OneVNLocationBarModelDelegate::OneVNLocationBarModelDelegate(
    Browser* browser) : BrowserLocationBarModelDelegate(browser) {}

OneVNLocationBarModelDelegate::~OneVNLocationBarModelDelegate() {}

base::string16
OneVNLocationBarModelDelegate::FormattedStringWithEquivalentMeaning(
    const GURL& url,
    const base::string16& formatted_url) const {
  base::string16 new_formatted_url =
      BrowserLocationBarModelDelegate::FormattedStringWithEquivalentMeaning(
          url, formatted_url);

  if (url.SchemeIs("chrome")) {
    base::ReplaceFirstSubstringAfterOffset(
        &new_formatted_url,
        0,
        base::UTF8ToUTF16("chrome://"),
        base::UTF8ToUTF16("onevn://"));
  }

  return new_formatted_url;
}
