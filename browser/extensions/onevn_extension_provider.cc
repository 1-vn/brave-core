/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/extensions/onevn_extension_provider.h"

#include <algorithm>
#include <string>
#include <vector>

#include "base/strings/utf_string_conversions.h"
#include "onevn/browser/onevn_browser_process_impl.h"
#include "onevn/common/extensions/extension_constants.h"
#include "onevn/components/onevn_shields/browser/extension_whitelist_service.h"
#include "onevn/components/onevn_shields/browser/local_data_files_service.h"
#include "onevn/grit/onevn_generated_resources.h"
#include "ui/base/l10n/l10n_util.h"

namespace {

bool IsBlacklisted(const extensions::Extension* extension) {
  // This is a hardcoded list of extensions to block.
  // Don't add new extensions to this list. Add them to
  // the files managed by the extension whitelist service.
  static std::vector<std::string> blacklisted_extensions(
      {// Used for tests, corresponds to
       // onevn/test/data/should-be-blocked-extension.
       "mlklomjnahgiddgfdgjhibinlfibfffc",
       // Chromium PDF Viewer.
       "mhjfbmdgcfjbbpaeojofohoefgiehjai"});

  if (std::find(blacklisted_extensions.begin(), blacklisted_extensions.end(),
                extension->id()) != blacklisted_extensions.end())
    return true;

  return g_onevn_browser_process->extension_whitelist_service()->IsBlacklisted(
      extension->id());
}

}  // namespace

namespace extensions {

bool OnevnExtensionProvider::IsVetted(const Extension* extension) {
  // This is a hardcoded list of vetted extensions, mostly
  // the built-in ones that ship with Onevn or are used for
  // unit tests.
  // Don't add new extensions to this list. Add them to
  // the files managed by the extension whitelist service.
  return OnevnExtensionProvider::IsVetted(extension->id());
}

bool OnevnExtensionProvider::IsVetted(const std::string id) {
  static std::vector<std::string> vetted_extensions({
      onevn_extension_id,
      onevn_rewards_extension_id,
      onevn_sync_extension_id,
      onevn_webtorrent_extension_id,
      crl_set_extension_id,
      pdfjs_extension_id,
      hangouts_extension_id,
      widevine_extension_id,
      onevn_shields::kLocalDataFilesComponentId,
      // Web Store
      "ahfgeienlihckogmohjhadlkjgocpleb",
      // Onevn Automation Extension
      "aapnijgdinlhnhlmodcfapnahmbfebeb",
      // Test ID: Onevn Default Ad Block Updater
      "naccapggpomhlhoifnlebfoocegenbol",
      // Test ID: Onevn Regional Ad Block Updater
      // (9852EFC4-99E4-4F2D-A915-9C3196C7A1DE)
      "dlpmaigjliompnelofkljgcmlenklieh",
      // Test ID: Onevn Tracking Protection Updater
      "eclbkhjphkhalklhipiicaldjbnhdfkc",
      // Test ID: PDFJS
      "kpbdcmcgkedhpbcpfndimofjnefgjidd",
      // Test ID: Onevn HTTPS Everywhere Updater
      "bhlmpjhncoojbkemjkeppfahkglffilp",
      // Test ID: Onevn Tor Client Updater
      "ngicbhhaldfdgmjhilmnleppfpmkgbbk",
  });
  if (std::find(vetted_extensions.begin(), vetted_extensions.end(), id) !=
      vetted_extensions.end())
    return true;

  return g_onevn_browser_process->extension_whitelist_service()->IsWhitelisted(
      id);
}

OnevnExtensionProvider::OnevnExtensionProvider() {}

OnevnExtensionProvider::~OnevnExtensionProvider() {}

std::string OnevnExtensionProvider::GetDebugPolicyProviderName() const {
#if defined(NDEBUG)
  NOTREACHED();
  return std::string();
#else
  return "Onevn Extension Provider";
#endif
}

bool OnevnExtensionProvider::UserMayLoad(const Extension* extension,
                                         base::string16* error) const {
  if (IsBlacklisted(extension)) {
    if (error) {
      *error = l10n_util::GetStringFUTF16(IDS_EXTENSION_CANT_INSTALL_ON_ONEVN,
                                          base::UTF8ToUTF16(extension->name()),
                                          base::UTF8ToUTF16(extension->id()));
    }
    DVLOG(1) << "Extension will not install "
             << " ID: " << base::UTF8ToUTF16(extension->id()) << ", "
             << " Name: " << base::UTF8ToUTF16(extension->name());
    return false;
  }
  return true;
}

bool OnevnExtensionProvider::MustRemainInstalled(const Extension* extension,
                                                 base::string16* error) const {
  return extension->id() == onevn_extension_id ||
         extension->id() == onevn_rewards_extension_id ||
         extension->id() == onevn_sync_extension_id;
}

}  // namespace extensions
