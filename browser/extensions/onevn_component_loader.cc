/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/extensions/onevn_component_loader.h"

#include <string>

#include "base/command_line.h"
#include "onevn/browser/onevn_browser_process_impl.h"
#include "onevn/browser/component_updater/onevn_component_installer.h"
#include "onevn/browser/extensions/onevn_component_extension.h"
#include "onevn/common/onevn_switches.h"
#include "onevn/common/extensions/extension_constants.h"
#include "onevn/common/pref_names.h"
#include "onevn/components/onevn_extension/grit/onevn_extension.h"
#include "onevn/components/onevn_rewards/browser/buildflags/buildflags.h"
#include "onevn/components/onevn_rewards/resources/extension/grit/onevn_rewards_extension_resources.h"
#include "onevn/components/onevn_webtorrent/grit/onevn_webtorrent_resources.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/common/pref_names.h"
#include "components/grit/onevn_components_resources.h"
#include "extensions/browser/extension_prefs.h"

namespace extensions {

// static
bool OneVNComponentLoader::IsPdfjsDisabled() {
  const base::CommandLine& command_line =
    *base::CommandLine::ForCurrentProcess();
  return command_line.HasSwitch(switches::kDisablePDFJSExtension);
}

OneVNComponentLoader::OneVNComponentLoader(
    ExtensionServiceInterface* extension_service,
    PrefService* profile_prefs,
    PrefService* local_state,
    Profile* profile)
    : ComponentLoader(extension_service, profile_prefs, local_state, profile),
      profile_(profile),
      profile_prefs_(profile_prefs),
      testing_callbacks_(nullptr) {
  ObserveOpenPdfExternallySetting();
}

OneVNComponentLoader::~OneVNComponentLoader() {
}

void OneVNComponentLoader::OnComponentRegistered(std::string extension_id) {
  ComponentsUI demand_updater;
  // This weird looking call is ok, it is just like this to not need
  // to patch for friend access.
  demand_updater.OnDemandUpdate(g_browser_process->component_updater(),
      extension_id);
}

void OneVNComponentLoader::OnComponentReady(std::string extension_id,
    bool allow_file_access,
    const base::FilePath& install_dir,
    const std::string& manifest) {
  Add(manifest, install_dir);
  if (allow_file_access) {
    ExtensionPrefs::Get((content::BrowserContext *)profile_)->
        SetAllowFileAccess(extension_id, true);
  }
}

void OneVNComponentLoader::AddExtension(const std::string& extension_id,
    const std::string& name, const std::string& public_key) {
  onevn::RegisterComponent(g_browser_process->component_updater(),
    name,
    public_key,
    base::Bind(&OneVNComponentLoader::OnComponentRegistered,
        base::Unretained(this), extension_id),
    base::Bind(&OneVNComponentLoader::OnComponentReady,
        base::Unretained(this), extension_id, true));
}

void OneVNComponentLoader::AddHangoutServicesExtension() {
  if (!profile_prefs_->FindPreference(kHangoutsEnabled) ||
      profile_prefs_->GetBoolean(kHangoutsEnabled)) {
    ForceAddHangoutServicesExtension();
  }
}

void OneVNComponentLoader::ForceAddHangoutServicesExtension() {
  ComponentLoader::AddHangoutServicesExtension();
}

void OneVNComponentLoader::AddDefaultComponentExtensions(
    bool skip_session_components) {
  ComponentLoader::AddDefaultComponentExtensions(skip_session_components);

  const base::CommandLine& command_line =
      *base::CommandLine::ForCurrentProcess();
  if (!command_line.HasSwitch(switches::kDisableOneVNExtension)) {
    base::FilePath onevn_extension_path(FILE_PATH_LITERAL(""));
    onevn_extension_path =
        onevn_extension_path.Append(FILE_PATH_LITERAL("onevn_extension"));
    Add(IDR_ONEVN_EXTENSION, onevn_extension_path);
  }

  if (!profile_prefs_->GetBoolean(prefs::kPluginsAlwaysOpenPdfExternally) &&
      !command_line.HasSwitch(switches::kDisablePDFJSExtension)) {
    AddExtension(pdfjs_extension_id, pdfjs_extension_name,
                 pdfjs_extension_public_key);
  }

#if BUILDFLAG(ONEVN_REWARDS_ENABLED)
  if (!command_line.HasSwitch(switches::kDisableOneVNRewardsExtension)) {
    base::FilePath onevn_rewards_path(FILE_PATH_LITERAL(""));
    onevn_rewards_path =
        onevn_rewards_path.Append(FILE_PATH_LITERAL("onevn_rewards"));
    Add(IDR_ONEVN_REWARDS, onevn_rewards_path);
  }
#endif

  if (!command_line.HasSwitch(switches::kDisableWebTorrentExtension) &&
      (!profile_prefs_->FindPreference(kWebTorrentEnabled) ||
      profile_prefs_->GetBoolean(kWebTorrentEnabled))) {
    base::FilePath onevn_webtorrent_path(FILE_PATH_LITERAL(""));
    onevn_webtorrent_path =
      onevn_webtorrent_path.Append(FILE_PATH_LITERAL("onevn_webtorrent"));
    Add(IDR_ONEVN_WEBTORRENT, onevn_webtorrent_path);
  }
}

void OneVNComponentLoader::ObserveOpenPdfExternallySetting() {
  // Observe the setting change only in regular profiles since the PDF settings
  // page is not available in Guest/Tor profiles.
  DCHECK(profile_ && profile_prefs_);
  if (!profile_->IsGuestSession()) {
    registrar_.Init(profile_prefs_);
    registrar_.Add(prefs::kPluginsAlwaysOpenPdfExternally,
      base::Bind(&OneVNComponentLoader::UpdatePdfExtension,
        base::Unretained(this)));
  }
}

void OneVNComponentLoader::UpdatePdfExtension(const std::string& pref_name) {
  DCHECK(pref_name == prefs::kPluginsAlwaysOpenPdfExternally);
  DCHECK(profile_prefs_);
  if (profile_prefs_->GetBoolean(prefs::kPluginsAlwaysOpenPdfExternally) ||
      IsPdfjsDisabled()) {
    if (testing_callbacks_)
      testing_callbacks_->OnPdfExtensionAction(TestingCallbacks::WILL_REMOVE);
    Remove(pdfjs_extension_id);
  } else if (!Exists(pdfjs_extension_id)) {
    if (testing_callbacks_)
      testing_callbacks_->OnPdfExtensionAction(TestingCallbacks::WILL_ADD);
    AddExtension(pdfjs_extension_id, pdfjs_extension_name,
                 pdfjs_extension_public_key);
  }
}

void OneVNComponentLoader::set_testing_callbacks(
    TestingCallbacks* testing_callbacks) {
  testing_callbacks_ = testing_callbacks;
}

}  // namespace extensions
