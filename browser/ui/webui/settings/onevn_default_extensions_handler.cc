/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/ui/webui/settings/onevn_default_extensions_handler.h"

#include <string>

#include "base/bind.h"
#include "base/values.h"
#include "onevn/browser/extensions/onevn_component_loader.h"
#include "onevn/common/extensions/extension_constants.h"
#include "onevn/common/pref_names.h"
#include "onevn/components/onevn_webtorrent/grit/onevn_webtorrent_resources.h"
#include "chrome/browser/extensions/component_loader.h"
#include "chrome/browser/extensions/extension_service.h"
#include "chrome/browser/extensions/webstore_install_with_prompt.h"
#include "chrome/browser/profiles/profile.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/web_ui.h"
#include "extensions/browser/extension_registry.h"
#include "extensions/browser/extension_system.h"

OneVNDefaultExtensionsHandler::OneVNDefaultExtensionsHandler()
  : weak_ptr_factory_(this) {
}

OneVNDefaultExtensionsHandler::~OneVNDefaultExtensionsHandler() {
}

void OneVNDefaultExtensionsHandler::RegisterMessages() {
  profile_ = Profile::FromWebUI(web_ui());
  web_ui()->RegisterMessageCallback(
      "setWebTorrentEnabled",
      base::BindRepeating(&OneVNDefaultExtensionsHandler::SetWebTorrentEnabled,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "setHangoutsEnabled",
      base::BindRepeating(&OneVNDefaultExtensionsHandler::SetHangoutsEnabled,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "setIPFSCompanionEnabled",
      base::BindRepeating(
        &OneVNDefaultExtensionsHandler::SetIPFSCompanionEnabled,
        base::Unretained(this)));
}

void OneVNDefaultExtensionsHandler::SetWebTorrentEnabled(
    const base::ListValue* args) {
  CHECK_EQ(args->GetSize(), 1U);
  CHECK(profile_);
  bool enabled;
  args->GetBoolean(0, &enabled);

  extensions::ExtensionService* service =
    extensions::ExtensionSystem::Get(profile_)->extension_service();
  extensions::ComponentLoader* loader = service->component_loader();

  if (enabled) {
    if (!loader->Exists(onevn_webtorrent_extension_id)) {
      base::FilePath onevn_webtorrent_path(FILE_PATH_LITERAL(""));
      onevn_webtorrent_path =
        onevn_webtorrent_path.Append(FILE_PATH_LITERAL("onevn_webtorrent"));
      loader->Add(IDR_ONEVN_WEBTORRENT, onevn_webtorrent_path);
    }
    service->EnableExtension(onevn_webtorrent_extension_id);
  } else {
    service->DisableExtension(onevn_webtorrent_extension_id,
        extensions::disable_reason::DisableReason::DISABLE_BLOCKED_BY_POLICY);
  }
}

void OneVNDefaultExtensionsHandler::SetHangoutsEnabled(
    const base::ListValue* args) {
  CHECK_EQ(args->GetSize(), 1U);
  CHECK(profile_);
  bool enabled;
  args->GetBoolean(0, &enabled);

  extensions::ExtensionService* service =
    extensions::ExtensionSystem::Get(profile_)->extension_service();

  if (enabled) {
    extensions::ComponentLoader* loader = service->component_loader();
    if (!loader->Exists(hangouts_extension_id)) {
      static_cast<extensions::OneVNComponentLoader*>(loader)->
          ForceAddHangoutServicesExtension();
    }
    service->EnableExtension(hangouts_extension_id);
  } else {
    service->DisableExtension(hangouts_extension_id,
        extensions::disable_reason::DisableReason::DISABLE_BLOCKED_BY_POLICY);
  }
}

bool OneVNDefaultExtensionsHandler::IsExtensionInstalled(
    const std::string& extension_id) const {
  extensions::ExtensionRegistry* registry =
    extensions::ExtensionRegistry::Get(
        static_cast<content::BrowserContext*>(profile_));
  return registry && registry->GetInstalledExtension(extension_id);
}

void OneVNDefaultExtensionsHandler::OnInstallResult(
    const std::string& pref_name,
    bool success, const std::string& error,
    extensions::webstore_install::Result result) {
  if (result != extensions::webstore_install::Result::SUCCESS &&
      result != extensions::webstore_install::Result::LAUNCH_IN_PROGRESS) {
    profile_->GetPrefs()->SetBoolean(pref_name, false);
  }
}

void OneVNDefaultExtensionsHandler::SetIPFSCompanionEnabled(
    const base::ListValue* args) {
  CHECK_EQ(args->GetSize(), 1U);
  CHECK(profile_);
  bool enabled;
  args->GetBoolean(0, &enabled);

  extensions::ExtensionService* service =
  extensions::ExtensionSystem::Get(profile_)->extension_service();
  if (enabled) {
    if (!IsExtensionInstalled(ipfs_companion_extension_id)) {
      scoped_refptr<extensions::WebstoreInstallWithPrompt> installer =
        new extensions::WebstoreInstallWithPrompt(
            ipfs_companion_extension_id, profile_,
            base::BindOnce(&OneVNDefaultExtensionsHandler::OnInstallResult,
              weak_ptr_factory_.GetWeakPtr(), kIPFSCompanionEnabled));
      installer->BeginInstall();
    }
    service->EnableExtension(ipfs_companion_extension_id);
  } else {
    service->DisableExtension(ipfs_companion_extension_id,
        extensions::disable_reason::DisableReason::DISABLE_USER_ACTION);
  }
}
