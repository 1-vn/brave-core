/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_CONTENT_SETTINGS_ONEVN_COOKIE_SETTINGS_FACTORY_H_
#define ONEVN_BROWSER_CONTENT_SETTINGS_ONEVN_COOKIE_SETTINGS_FACTORY_H_

#include <string>

#include "chrome/browser/content_settings/cookie_settings_factory.h"

namespace content_settings {
class OnevnCookieSettings;
}

class Profile;

class OnevnCookieSettingsFactory : public CookieSettingsFactory {
 public:
  static scoped_refptr<content_settings::OnevnCookieSettings> GetForProfile(
      Profile* profile);

 private:
  friend struct base::DefaultSingletonTraits<OnevnCookieSettingsFactory>;

  OnevnCookieSettingsFactory();
  ~OnevnCookieSettingsFactory() override;

  DISALLOW_COPY_AND_ASSIGN(OnevnCookieSettingsFactory);
};

#endif  // ONEVN_BROWSER_CONTENT_SETTINGS_ONEVN_COOKIE_SETTINGS_FACTORY_H_
