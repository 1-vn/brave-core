/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/autocomplete/onevn_autocomplete_provider_client.h"

#include "base/strings/utf_string_conversions.h"
#include "onevn/common/webui_url_constants.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/search_engines/template_url_service_factory.h"
#include "chrome/common/webui_url_constants.h"

OneVNAutocompleteProviderClient::OneVNAutocompleteProviderClient(
    Profile* profile)
    : ChromeAutocompleteProviderClient(profile->GetOriginalProfile()),
      profile_(profile) {
}

OneVNAutocompleteProviderClient::~OneVNAutocompleteProviderClient() {
}

TemplateURLService* OneVNAutocompleteProviderClient::GetTemplateURLService() {
  return TemplateURLServiceFactory::GetForProfile(profile_);
}

const TemplateURLService*
OneVNAutocompleteProviderClient::GetTemplateURLService() const {
  return TemplateURLServiceFactory::GetForProfile(profile_);
}

std::vector<base::string16> OneVNAutocompleteProviderClient::GetBuiltinURLs() {
  std::vector<base::string16> v =
      ChromeAutocompleteProviderClient::GetBuiltinURLs();
  auto it = std::find(v.begin(), v.end(),
      base::ASCIIToUTF16(chrome::kChromeUISyncInternalsHost));
  DCHECK(it != v.end());
  if (it != v.end()) {
    *it = base::ASCIIToUTF16(kOneVNUISyncHost);
  }
  return v;
}
