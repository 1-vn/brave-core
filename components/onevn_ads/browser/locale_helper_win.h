/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_BROWSER_ONEVN_ADS_LOCALE_HELPER_WIN_H_
#define ONEVN_COMPONENTS_BROWSER_ONEVN_ADS_LOCALE_HELPER_WIN_H_

#include <windows.h>
#include <string>

#include "onevn/components/onevn_ads/browser/locale_helper.h"

namespace onevn_ads {

class LocaleHelperWin : public LocaleHelper {
 public:
  LocaleHelperWin();
  ~LocaleHelperWin() override;

  static LocaleHelperWin* GetInstance();

 private:
  friend struct base::DefaultSingletonTraits<LocaleHelperWin>;

  // LocaleHelper impl
  std::string GetLocale() const override;

  DISALLOW_COPY_AND_ASSIGN(LocaleHelperWin);
};

}  // namespace onevn_ads

#endif  // ONEVN_COMPONENTS_BROWSER_ONEVN_ADS_LOCALE_HELPER_WIN_H_
