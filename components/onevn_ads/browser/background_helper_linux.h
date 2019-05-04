/* Copyright 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_ADS_BROWSER_BACKGROUND_HELPER_LINUX_H_
#define ONEVN_COMPONENTS_ONEVN_ADS_BROWSER_BACKGROUND_HELPER_LINUX_H_

#include "base/macros.h"
#include "base/memory/singleton.h"
#include "base/memory/weak_ptr.h"
#include "onevn/components/onevn_ads/browser/background_helper.h"
#include "chrome/browser/ui/browser_list_observer.h"

namespace onevn_ads {

class BackgroundHelperLinux :
    public BackgroundHelper,
    public base::SupportsWeakPtr<BackgroundHelperLinux>,
    public BrowserListObserver {
 public:
  BackgroundHelperLinux();
  ~BackgroundHelperLinux() override;

  static BackgroundHelperLinux* GetInstance();

 private:
  friend struct base::DefaultSingletonTraits<BackgroundHelperLinux>;

  // BackgroundHelper impl
  bool IsForeground() const override;

  // BrowserListObserver overrides
  void OnBrowserSetLastActive(Browser* browser) override;
  void OnBrowserNoLongerActive(Browser* browser) override;

  void CheckState();

  DISALLOW_COPY_AND_ASSIGN(BackgroundHelperLinux);
};

}  // namespace onevn_ads

#endif  // ONEVN_COMPONENTS_ONEVN_ADS_BROWSER_BACKGROUND_HELPER_LINUX_H_
