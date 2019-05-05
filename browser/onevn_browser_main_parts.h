/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_ONEVN_BROWSER_MAIN_PARTS_H_
#define ONEVN_BROWSER_ONEVN_BROWSER_MAIN_PARTS_H_

#include "base/macros.h"
#include "chrome/browser/chrome_browser_main.h"

class OnevnBrowserMainParts : public ChromeBrowserMainParts {
 public:
  using ChromeBrowserMainParts::ChromeBrowserMainParts;
  ~OnevnBrowserMainParts() override = default;

  void PreShutdown() override;

 private:
  DISALLOW_COPY_AND_ASSIGN(OnevnBrowserMainParts);
};

#endif  // ONEVN_BROWSER_ONEVN_BROWSER_MAIN_PARTS_H_
