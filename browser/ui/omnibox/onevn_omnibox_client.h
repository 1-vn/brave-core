// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ONEVN_BROWSER_UI_OMNIBOX_ONEVN_OMNIBOX_CLIENT_H_
#define ONEVN_BROWSER_UI_OMNIBOX_ONEVN_OMNIBOX_CLIENT_H_

#include "chrome/browser/ui/omnibox/chrome_omnibox_client.h"
#include "onevn/browser/autocomplete/onevn_autocomplete_scheme_classifier.h"

class OmniboxEditController;
class Profile;

class OnevnOmniboxClient : public ChromeOmniboxClient {
  public:
    OnevnOmniboxClient(OmniboxEditController* controller,
                                         Profile* profile);
    ~OnevnOmniboxClient() override;
    const AutocompleteSchemeClassifier& GetSchemeClassifier() const override;

  private:
    DISALLOW_COPY_AND_ASSIGN(OnevnOmniboxClient);
    OnevnAutocompleteSchemeClassifier scheme_classifier_;
};

#endif
