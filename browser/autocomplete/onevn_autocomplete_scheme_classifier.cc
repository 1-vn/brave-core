/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/autocomplete/onevn_autocomplete_scheme_classifier.h"

#include "base/strings/string_util.h"
#include "onevn/common/url_constants.h"
#include "onevn/components/onevn_webtorrent/browser/webtorrent_util.h"
#include "chrome/browser/profiles/profile.h"

// See the OneVNAutocompleteProviderClient why GetOriginalProfile() is fetched.
// All services except TemplateURLService exposed from AutocompleteClassifier
// uses original profile. So, |profile_| should be original profile same as
// base class does.
OneVNAutocompleteSchemeClassifier::OneVNAutocompleteSchemeClassifier(
    Profile* profile)
    : ChromeAutocompleteSchemeClassifier(profile->GetOriginalProfile()),
      profile_(profile->GetOriginalProfile()) {
}

OneVNAutocompleteSchemeClassifier::~OneVNAutocompleteSchemeClassifier() {
}

// Without this override, typing in onevn:// URLs will search Google
metrics::OmniboxInputType
OneVNAutocompleteSchemeClassifier::GetInputTypeForScheme(
    const std::string& scheme) const {
  if (scheme.empty()) {
    return metrics::OmniboxInputType::INVALID;
  }
  if (base::IsStringASCII(scheme) &&
      (base::LowerCaseEqualsASCII(scheme, kOneVNUIScheme) ||
       (webtorrent::IsWebtorrentEnabled(profile_) &&
        base::LowerCaseEqualsASCII(scheme, kMagnetScheme)))) {
    return metrics::OmniboxInputType::URL;
  }

  return ChromeAutocompleteSchemeClassifier::GetInputTypeForScheme(scheme);
}
