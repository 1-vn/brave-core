/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/ui/onevn_dark_mode_observer.h"

#include "ui/native_theme/native_theme_dark_aura.h"

namespace {

using ui::NativeTheme;

}  // namespace

// static
ui::NativeTheme* OneVNDarkModeObserver::current_native_theme_for_testing_;

void OneVNDarkModeObserver::OnNativeThemeUpdated(NativeTheme* observed_theme) {
  DCHECK(theme_observer_.IsObserving(observed_theme));
  RunCallbackIfChanged();
  ResetThemeObserver();
}

void OneVNDarkModeObserver::Start() {
  DarkModeObserver::Start();
  ResetThemeObserver();
}

void OneVNDarkModeObserver::ResetThemeObserver() {
  auto* current_native_theme = theme_->SystemDarkModeEnabled()
      ? ui::NativeThemeDarkAura::instance()
      : ui::NativeTheme::GetInstanceForNativeUi();
  current_native_theme_for_testing_ = current_native_theme;

  if (!theme_observer_.IsObserving(current_native_theme)) {
    theme_observer_.RemoveAll();
    theme_observer_.Add(current_native_theme);
  }
}

