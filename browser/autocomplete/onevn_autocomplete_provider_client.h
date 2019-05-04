/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_AUTOCOMPLETE_ONEVN_AUTOCOMPLETE_PROVIDER_CLIENT_H_
#define ONEVN_BROWSER_AUTOCOMPLETE_ONEVN_AUTOCOMPLETE_PROVIDER_CLIENT_H_

#include "chrome/browser/autocomplete/chrome_autocomplete_provider_client.h"

// In onevn, different AutocompleteClassifiers are created for normal and
// incognito profile by changing
// AutocompleteClassifierFactory::GetBrowserContextToUse().
// This changes are needed to use different search engine used by web search in
// web page context menu.
// When context menu handles web search it gets search engine url from
// ChromeAutocompleteProviderClient via AutocompleteClassifiers.
// Because of this, private window will use same search engine url of normal
// window if same AutocompleteClassifiers are used on normal and incognito.
// So, we made this change.
// However, ChromeAutocompleteProviderClient exposes many other services based
// on profiles.
// We don't want to change other services. Only wanted to get proper
// TemplateURLService. To achieve this, OneVNAutocompleteProviderClient is
// introduced. It initializes ChromeAutocompleteProviderClient with original
// profile and only overrided TemplateURLService getter.
// OneVNAutocompleteSchemeClassifier also initialize
// ChromeAutocompleteSchemeClassifier with original profile for same reason.
class OneVNAutocompleteProviderClient
    : public ChromeAutocompleteProviderClient {
 public:
  explicit OneVNAutocompleteProviderClient(Profile* profile);
  ~OneVNAutocompleteProviderClient() override;

  TemplateURLService* GetTemplateURLService() override;
  const TemplateURLService* GetTemplateURLService() const override;
  std::vector<base::string16> GetBuiltinURLs() override;

 private:
  Profile* profile_;

  DISALLOW_COPY_AND_ASSIGN(OneVNAutocompleteProviderClient);
};

#endif  // ONEVN_BROWSER_AUTOCOMPLETE_ONEVN_AUTOCOMPLETE_PROVIDER_CLIENT_H_
