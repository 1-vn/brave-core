/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_UI_TOOLBAR_ONEVN_LOCATION_BAR_MODEL_DELEGATE_H_
#define ONEVN_BROWSER_UI_TOOLBAR_ONEVN_LOCATION_BAR_MODEL_DELEGATE_H_

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "chrome/browser/ui/browser_location_bar_model_delegate.h"

class Browser;

class OnevnLocationBarModelDelegate : public BrowserLocationBarModelDelegate {
 public:
  explicit OnevnLocationBarModelDelegate(Browser* browser);
  ~OnevnLocationBarModelDelegate() override;

 private:
  base::string16 FormattedStringWithEquivalentMeaning(
      const GURL& url,
      const base::string16& formatted_url) const override;

  DISALLOW_COPY_AND_ASSIGN(OnevnLocationBarModelDelegate);
};

#endif  // ONEVN_BROWSER_UI_TOOLBAR_ONEVN_LOCATION_BAR_MODEL_DELEGATE_H_
