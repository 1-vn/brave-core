/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_AUTOCOMPLETE_ONEVN_AUTOCOMPLETE_SCHEME_CLASSIFIER_H_
#define ONEVN_BROWSER_AUTOCOMPLETE_ONEVN_AUTOCOMPLETE_SCHEME_CLASSIFIER_H_

#include "chrome/browser/autocomplete/chrome_autocomplete_scheme_classifier.h"

class OneVNAutocompleteSchemeClassifier : public ChromeAutocompleteSchemeClassifier {
 public:
  explicit OneVNAutocompleteSchemeClassifier(Profile* profile);
  ~OneVNAutocompleteSchemeClassifier() override;

  metrics::OmniboxInputType GetInputTypeForScheme(
      const std::string& scheme) const override;

 private:
  Profile* profile_;

  DISALLOW_COPY_AND_ASSIGN(OneVNAutocompleteSchemeClassifier);
};

#endif  // ONEVN_BROWSER_AUTOCOMPLETE_ONEVN_AUTOCOMPLETE_SCHEME_CLASSIFIER_H_

