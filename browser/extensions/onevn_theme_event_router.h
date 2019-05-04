/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_EXTENSIONS_ONEVN_THEME_EVENT_ROUTER_H_
#define ONEVN_BROWSER_EXTENSIONS_ONEVN_THEME_EVENT_ROUTER_H_

#include "base/gtest_prod_util.h"
#include "base/scoped_observer.h"
#include "ui/native_theme/native_theme_observer.h"

class Profile;

namespace extensions {

class OneVNThemeEventRouter : public ui::NativeThemeObserver {
 public:
  explicit OneVNThemeEventRouter(Profile* profile);
  ~OneVNThemeEventRouter() override;

 private:
  friend class MockOneVNThemeEventRouter;

  // ui::NativeThemeObserver overrides:
  void OnNativeThemeUpdated(ui::NativeTheme* observed_theme) override;

  bool IsDarkModeEnabled() const;
  void ResetThemeObserver();

  // Make virtual for testing.
  virtual void Notify();

  ui::NativeTheme* current_native_theme_for_testing_ = nullptr;
  Profile* profile_;
  bool using_dark_;
  ScopedObserver<ui::NativeTheme, OneVNThemeEventRouter> observer_;

  DISALLOW_COPY_AND_ASSIGN(OneVNThemeEventRouter);
};

}  // namespace extensions

#endif  // ONEVN_BROWSER_EXTENSIONS_ONEVN_THEME_EVENT_ROUTER_H_
