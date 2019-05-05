// Copyright 2018 The Onevn Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/renderer_context_menu/render_view_context_menu.h"
#include "components/spellcheck/spellcheck_buildflags.h"
#if !BUILDFLAG(USE_BROWSER_SPELLCHECKER)
#include "onevn/browser/renderer_context_menu/onevn_spelling_options_submenu_observer.h"
#endif

// Our .h file creates a masquerade for RenderViewContextMenu.  Switch
// back to the Chromium one for the Chromium implementation.
#undef RenderViewContextMenu
#define RenderViewContextMenu RenderViewContextMenu_Chromium

#if !defined(OS_MACOSX)
// Use our subclass to initialize SpellingOptionsSubMenuObserver.
#define SpellingOptionsSubMenuObserver OnevnSpellingOptionsSubMenuObserver
#endif

#include "../../../../chrome/browser/renderer_context_menu/render_view_context_menu.cc"

#if !defined(OS_MACOSX)
#undef SpellingOptionsSubMenuObserver
#endif

// Make it clear which class we mean here.
#undef RenderViewContextMenu

OnevnRenderViewContextMenu::OnevnRenderViewContextMenu(
    content::RenderFrameHost* render_frame_host,
    const content::ContextMenuParams& params)
  : RenderViewContextMenu_Chromium(render_frame_host, params) {
}

void RenderViewContextMenu_Chromium::AppendOnevnLinkItems() {
}

void OnevnRenderViewContextMenu::AppendOnevnLinkItems() {
  if (!params_.link_url.is_empty()) {
    if (base::FeatureList::IsEnabled(features::kDesktopPWAWindowing)) {
      const Browser* browser = GetBrowser();
      const bool is_app = browser && browser->is_app();

      menu_model_.AddItemWithStringId(
          IDC_CONTENT_CONTEXT_OPENLINKTOR,
          is_app ? IDS_CONTENT_CONTEXT_OPENLINKTOR_INAPP
                 : IDS_CONTENT_CONTEXT_OPENLINKTOR);
    } else {
      menu_model_.AddItemWithStringId(IDC_CONTENT_CONTEXT_OPENLINKTOR,
                                      IDS_CONTENT_CONTEXT_OPENLINKTOR);
    }
  }
}

bool OnevnRenderViewContextMenu::IsCommandIdEnabled(int id) const {
  switch (id) {
    case IDC_CONTENT_CONTEXT_OPENLINKTOR:
      return params_.link_url.is_valid() &&
             IsURLAllowedInIncognito(params_.link_url, browser_context_) &&
             !browser_context_->IsTorProfile();
    default:
      return RenderViewContextMenu_Chromium::IsCommandIdEnabled(id);
  }
}

void OnevnRenderViewContextMenu::ExecuteCommand(int id, int event_flags) {
  switch (id) {
    case IDC_CONTENT_CONTEXT_OPENLINKTOR:
      profiles::SwitchToTorProfile(
          base::Bind(
              OnProfileCreated, params_.link_url,
              content::Referrer(GURL(),
                                network::mojom::ReferrerPolicy::kStrictOrigin)));
      break;
    default:
      RenderViewContextMenu_Chromium::ExecuteCommand(id, event_flags);
  }
}

void OnevnRenderViewContextMenu::AddSpellCheckServiceItem(bool is_checked) {
  // Call our implementation, not the one in the base class.
  // Assumption:
  // Use of spelling service is disabled in Onevn profile preferences.
  DCHECK(!GetProfile()->GetPrefs()->GetBoolean(
      spellcheck::prefs::kSpellCheckUseSpellingService));
  AddSpellCheckServiceItem(&menu_model_, is_checked);
}

// static
void OnevnRenderViewContextMenu::AddSpellCheckServiceItem(
    ui::SimpleMenuModel* menu,
    bool is_checked) {
  // Suppress adding "Spellcheck->Ask Onevn for suggestions" item.
}
