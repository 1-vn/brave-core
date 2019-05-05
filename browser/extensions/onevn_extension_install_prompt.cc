/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/extensions/onevn_extension_install_prompt.h"

#include "base/strings/utf_string_conversions.h"
#include "onevn/browser/extensions/onevn_extension_provider.h"
#include "onevn/grit/onevn_generated_resources.h"
#include "extensions/common/extension_id.h"
#include "ui/base/l10n/l10n_util.h"

OnevnPrompt::OnevnPrompt(ExtensionInstallPrompt::PromptType type) :
    ExtensionInstallPrompt::Prompt(type) {
}

OnevnPrompt::~OnevnPrompt() {
}

base::string16 OnevnPrompt::GetDialogTitle() const {
  if (!extensions::OnevnExtensionProvider::IsVetted(extension())) {
    if (type_ == ExtensionInstallPrompt::INSTALL_PROMPT ||
        type_ == ExtensionInstallPrompt::WEBSTORE_WIDGET_PROMPT) {
      return l10n_util::GetStringFUTF16(IDS_UNVETTED_EXTENSION_INSTALL_PROMPT_TITLE,
          base::UTF8ToUTF16(extension_->name()));
    }
  }
  return ExtensionInstallPrompt::Prompt::GetDialogTitle();
}
