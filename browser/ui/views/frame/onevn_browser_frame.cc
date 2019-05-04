/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/ui/views/frame/onevn_browser_frame.h"

#include "onevn/browser/themes/onevn_theme_service.h"
#include "chrome/browser/ui/views/frame/browser_view.h"
#include "ui/native_theme/native_theme_dark_aura.h"
#include "ui/views/widget/native_widget.h"

OneVNBrowserFrame::OneVNBrowserFrame(BrowserView* browser_view)
    : BrowserFrame(browser_view),
      browser_view_(browser_view) {
}

OneVNBrowserFrame::~OneVNBrowserFrame() {
}

const ui::NativeTheme* OneVNBrowserFrame::GetNativeTheme() const {
  // Gets the platform-specific override for NativeTheme,
  // unless we're in dark mode in which case get cross-platform
  // dark theme.
  // TODO: Have platform-specific version of dark theme too.
#if defined(OS_WIN) || defined(OS_MACOSX) || defined(OS_CHROMEOS)
  OneVNThemeType active_builtin_theme =
            OneVNThemeService::GetActiveOneVNThemeType(
                              browser_view_->browser()->profile());
  if (active_builtin_theme == OneVNThemeType::ONEVN_THEME_TYPE_DARK ||
      browser_view_->browser()->profile()->GetProfileType() ==
          Profile::INCOGNITO_PROFILE ||
      browser_view_->browser()->profile()->IsTorProfile()) {
    return ui::NativeThemeDarkAura::instance();
  }
#endif
  // Each platform will implement ui::NativeTheme::GetInstanceForNativeUi
  // separately, which Widget::GetNativeTheme calls.
  return views::Widget::GetNativeTheme();
}