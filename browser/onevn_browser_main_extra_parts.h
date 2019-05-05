/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_ONEVN_BROWSER_MAIN_EXTRA_PARTS_H_
#define ONEVN_BROWSER_ONEVN_BROWSER_MAIN_EXTRA_PARTS_H_

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "chrome/browser/chrome_browser_main.h"
#include "chrome/browser/chrome_browser_main_extra_parts.h"

class OnevnBrowserMainExtraParts : public ChromeBrowserMainExtraParts {
 public:
  explicit OnevnBrowserMainExtraParts();
  ~OnevnBrowserMainExtraParts() override;

  // ChromeBrowserMainExtraParts overrides.
  void PreMainMessageLoopRun() override;

 private:
  DISALLOW_COPY_AND_ASSIGN(OnevnBrowserMainExtraParts);
};

#endif  // ONEVN_BROWSER_ONEVN_BROWSER_MAIN_EXTRA_PARTS_H_
