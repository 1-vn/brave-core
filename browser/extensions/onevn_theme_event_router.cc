/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
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

OnevnThemeEventRouter::OnevnThemeEventRouter(Profile* profile)
    : profile_(profile),
      using_dark_(IsDarkModeEnabled()),
      observer_(this) {
  ResetThemeObserver();
}

OnevnThemeEventRouter::~OnevnThemeEventRouter() {}

void OnevnThemeEventRouter::OnNativeThemeUpdated(
    ui::NativeTheme* observed_theme) {
  DCHECK(observer_.IsObserving(observed_theme));
  ResetThemeObserver();

  bool use_dark = IsDarkModeEnabled();
  if (use_dark == using_dark_)
    return;

  using_dark_ = use_dark;
  Notify();
}

void OnevnThemeEventRouter::Notify() {
  EventRouter* event_router = EventRouter::Get(profile_);
  const std::string theme_type =
      OnevnThemeService::GetStringFromOnevnThemeType(
          OnevnThemeService::GetActiveOnevnThemeType(profile_));

  auto event = std::make_unique<extensions::Event>(
      extensions::events::ONEVN_ON_ONEVN_THEME_TYPE_CHANGED,
      api::onevn_theme::OnOnevnThemeTypeChanged::kEventName,
      api::onevn_theme::OnOnevnThemeTypeChanged::Create(theme_type),
      profile_);

  event_router->BroadcastEvent(std::move(event));
}

bool OnevnThemeEventRouter::IsDarkModeEnabled() const {
  return OnevnThemeService::GetActiveOnevnThemeType(profile_) ==
      ONEVN_THEME_TYPE_DARK;
}

void OnevnThemeEventRouter::ResetThemeObserver() {
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
