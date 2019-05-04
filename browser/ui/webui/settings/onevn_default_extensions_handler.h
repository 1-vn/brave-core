/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_UI_WEBUI_SETTINGS_ONEVN_DEFAULT_EXTENSIONS_HANDLER_H_
#define ONEVN_BROWSER_UI_WEBUI_SETTINGS_ONEVN_DEFAULT_EXTENSIONS_HANDLER_H_

#include <string>
#include "base/memory/weak_ptr.h"
#include "chrome/browser/ui/webui/settings/settings_page_ui_handler.h"
#include "chrome/common/extensions/webstore_install_result.h"

class Profile;

class OneVNDefaultExtensionsHandler : public settings::SettingsPageUIHandler {
 public:
  OneVNDefaultExtensionsHandler();
  ~OneVNDefaultExtensionsHandler() override;

 private:
  // SettingsPageUIHandler overrides:
  void RegisterMessages() override;
  void OnJavascriptAllowed() override {}
  void OnJavascriptDisallowed() override {}

  void SetWebTorrentEnabled(const base::ListValue* args);
  void SetHangoutsEnabled(const base::ListValue* args);
  void SetIPFSCompanionEnabled(const base::ListValue* args);

  bool IsExtensionInstalled(const std::string& extension_id) const;
  void OnInstallResult(const std::string& pref_name,
      bool success, const std::string& error,
      extensions::webstore_install::Result result);

  Profile* profile_ = nullptr;
  base::WeakPtrFactory<OneVNDefaultExtensionsHandler> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(OneVNDefaultExtensionsHandler);
};

#endif  // ONEVN_BROWSER_UI_WEBUI_SETTINGS_ONEVN_DEFAULT_EXTENSIONS_HANDLER_H_
