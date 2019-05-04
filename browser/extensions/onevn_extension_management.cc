/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/extensions/onevn_extension_management.h"

#include <memory>

#include "base/command_line.h"
#include "onevn/browser/onevn_browser_process_impl.h"
#include "onevn/common/onevn_switches.h"
#include "onevn/common/extensions/extension_constants.h"
#include "onevn/common/pref_names.h"
#include "onevn/browser/extensions/onevn_extension_provider.h"
#include "onevn/browser/extensions/onevn_tor_client_updater.h"
#include "chrome/browser/extensions/external_policy_loader.h"
#include "chrome/browser/profiles/profile.h"
#include "components/prefs/pref_service.h"
#include "extensions/browser/extension_registry.h"
#include "extensions/common/extension.h"
#include "extensions/common/extension_urls.h"

namespace extensions {

OneVNExtensionManagement::OneVNExtensionManagement(Profile* profile)
    : ExtensionManagement(profile),
      extension_registry_observer_(this) {
  extension_registry_observer_.Add(ExtensionRegistry::Get(
        static_cast<content::BrowserContext*>(profile)));
  providers_.push_back(
      std::make_unique<OneVNExtensionProvider>());
  RegisterOneVNExtensions();
}

OneVNExtensionManagement::~OneVNExtensionManagement() {
}

void OneVNExtensionManagement::RegisterOneVNExtensions() {
  const base::CommandLine& command_line =
      *base::CommandLine::ForCurrentProcess();
  if (!command_line.HasSwitch(switches::kDisableTorClientUpdaterExtension))
    g_onevn_browser_process->tor_client_updater()->Register();
}

void OneVNExtensionManagement::OnExtensionLoaded(
    content::BrowserContext* browser_context,
    const Extension* extension) {
  if (extension->id() == ipfs_companion_extension_id)
    pref_service_->SetBoolean(kIPFSCompanionEnabled, true);
}

void OneVNExtensionManagement::OnExtensionUnloaded(
    content::BrowserContext* browser_context,
    const Extension* extension,
    UnloadedExtensionReason reason) {
  if (extension->id() == ipfs_companion_extension_id)
    pref_service_->SetBoolean(kIPFSCompanionEnabled, false);
}

}  // namespace extensions
