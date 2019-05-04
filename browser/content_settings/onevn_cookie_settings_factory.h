/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_CONTENT_SETTINGS_ONEVN_COOKIE_SETTINGS_FACTORY_H_
#define ONEVN_BROWSER_CONTENT_SETTINGS_ONEVN_COOKIE_SETTINGS_FACTORY_H_

#include <string>

#include "chrome/browser/content_settings/cookie_settings_factory.h"

namespace content_settings {
class OneVNCookieSettings;
}

class Profile;

class OneVNCookieSettingsFactory : public CookieSettingsFactory {
 public:
  static scoped_refptr<content_settings::OneVNCookieSettings> GetForProfile(
      Profile* profile);

 private:
  friend struct base::DefaultSingletonTraits<OneVNCookieSettingsFactory>;

  OneVNCookieSettingsFactory();
  ~OneVNCookieSettingsFactory() override;

  DISALLOW_COPY_AND_ASSIGN(OneVNCookieSettingsFactory);
};

#endif  // ONEVN_BROWSER_CONTENT_SETTINGS_ONEVN_COOKIE_SETTINGS_FACTORY_H_
