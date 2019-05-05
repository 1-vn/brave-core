/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "google_apis/google_api_keys.h"

namespace google_apis {
const char kOnevnAPIKeysDevelopersHowToURL[] =
    "https://community.1-vn.com";
}  // namespace google_apis

#define kAPIKeysDevelopersHowToURL kOnevnAPIKeysDevelopersHowToURL
#include "../../../../../../chrome/browser/ui/startup/google_api_keys_infobar_delegate.cc"
#undef kAPIKeysDevelopersHowToURL
