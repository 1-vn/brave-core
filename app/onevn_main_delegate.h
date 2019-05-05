/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_APP_ONEVN_MAIN_DELEGATE_H_
#define ONEVN_APP_ONEVN_MAIN_DELEGATE_H_

#include "chrome/app/chrome_main_delegate.h"

// Chrome implementation of ContentMainDelegate.
class OnevnMainDelegate : public ChromeMainDelegate {
 public:
  OnevnMainDelegate();

  // |exe_entry_point_ticks| is the time at which the main function of the
  // executable was entered, or null if not available.
  explicit OnevnMainDelegate(base::TimeTicks exe_entry_point_ticks);
  ~OnevnMainDelegate() override;

 protected:
  // content::ContentMainDelegate implementation:
  bool BasicStartupComplete(int* exit_code) override;

  content::ContentBrowserClient* CreateContentBrowserClient() override;
  content::ContentRendererClient* CreateContentRendererClient() override;
  content::ContentUtilityClient* CreateContentUtilityClient() override;
  void PreSandboxStartup() override;

  DISALLOW_COPY_AND_ASSIGN(OnevnMainDelegate);
};

#endif  // ONEVN_APP_ONEVN_MAIN_DELEGATE_H_
