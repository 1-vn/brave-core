/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/extensions/onevn_theme_event_router.h"

#include <memory>
#include <string>
#include <utility>

#include "onevn/browser/themes/onevn_theme_service.h"
#include "onevn/common/extensions/api/onevn_theme.h"
#include "chrome/browser/profiles/profile.h"
#include "extensions/browser/event_router.h"
#include "ui/native_theme/native_theme_dark_aura.h"

namespace extensions {

OneVNThemeEventRouter::OneVNThemeEventRouter(Profile* profile)
    : profile_(profile),
      using_dark_(IsDarkModeEnabled()),
      observer_(this) {
  ResetThemeObserver();
}

OneVNThemeEventRouter::~OneVNThemeEventRouter() {}

void OneVNThemeEventRouter::OnNativeThemeUpdated(
    ui::NativeTheme* observed_theme) {
  DCHECK(observer_.IsObserving(observed_theme));
  ResetThemeObserver();

  bool use_dark = IsDarkModeEnabled();
  if (use_dark == using_dark_)
    return;

  using_dark_ = use_dark;
  Notify();
}

void OneVNThemeEventRouter::Notify() {
  EventRouter* event_router = EventRouter::Get(profile_);
  const std::string theme_type =
      OneVNThemeService::GetStringFromOneVNThemeType(
          OneVNThemeService::GetActiveOneVNThemeType(profile_));

  auto event = std::make_unique<extensions::Event>(
      extensions::events::ONEVN_ON_ONEVN_THEME_TYPE_CHANGED,
      api::onevn_theme::OnOneVNThemeTypeChanged::kEventName,
      api::onevn_theme::OnOneVNThemeTypeChanged::Create(theme_type),
      profile_);

  event_router->BroadcastEvent(std::move(event));
}

bool OneVNThemeEventRouter::IsDarkModeEnabled() const {
  return OneVNThemeService::GetActiveOneVNThemeType(profile_) ==
      ONEVN_THEME_TYPE_DARK;
}

void OneVNThemeEventRouter::ResetThemeObserver() {
  auto* current_native_theme =
      IsDarkModeEnabled() ? ui::NativeThemeDarkAura::instance()
                          : ui::NativeTheme::GetInstanceForNativeUi();
  if (!observer_.IsObserving(current_native_theme)) {
    observer_.RemoveAll();
    observer_.Add(current_native_theme);
    current_native_theme_for_testing_ = current_native_theme;
  }
}

}  // namespace extensions
