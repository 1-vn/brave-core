/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_UI_WEBUI_ONEVN_NEW_TAB_UI_H_
#define ONEVN_BROWSER_UI_WEBUI_ONEVN_NEW_TAB_UI_H_

#include <memory>

#include "onevn/browser/ui/webui/basic_ui.h"

class PrefChangeRegistrar;

class OnevnNewTabUI : public BasicUI {
 public:
  OnevnNewTabUI(content::WebUI* web_ui, const std::string& host);
  ~OnevnNewTabUI() override;

 private:
  // BasicUI overrides
  void UpdateWebUIProperties() override;

  void CustomizeNewTabWebUIProperties(content::RenderViewHost* render_view_host);
  void OnPreferenceChanged();

  std::unique_ptr<PrefChangeRegistrar> pref_change_registrar_;

  DISALLOW_COPY_AND_ASSIGN(OnevnNewTabUI);
};

#endif  // ONEVN_BROWSER_UI_WEBUI_ONEVN_NEW_TAB_UI_H_
