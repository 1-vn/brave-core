/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/autocomplete/onevn_autocomplete_provider_client.h"
#include "onevn/browser/autocomplete/onevn_autocomplete_scheme_classifier.h"
#include "onevn/components/omnibox/browser/onevn_autocomplete_controller.h"
#include "components/omnibox/browser/autocomplete_classifier.h"
#include "components/omnibox/browser/autocomplete_controller.h"

#define AutocompleteController OnevnAutocompleteController
#define ChromeAutocompleteProviderClient OnevnAutocompleteProviderClient
#define ChromeAutocompleteSchemeClassifier OnevnAutocompleteSchemeClassifier
#include "../../../../../chrome/browser/autocomplete/autocomplete_classifier_factory.cc"
#undef ChromeAutocompleteSchemeClassifier
#undef ChromeAutocompleteProviderClient
#undef AutocompleteController
