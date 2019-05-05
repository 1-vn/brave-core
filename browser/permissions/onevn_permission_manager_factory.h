/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_PERMISSION_ONEVN_PERMISSION_MANAGER_FACTORR_H_
#define ONEVN_BROWSER_PERMISSION_ONEVN_PERMISSION_MANAGER_FACTORR_H_

#include "chrome/browser/permissions/permission_manager_factory.h"

class OnevnPermissionManagerFactory : public PermissionManagerFactory {
 public:
  static PermissionManager* GetForProfile(Profile* profile);
  static OnevnPermissionManagerFactory* GetInstance();

 private:
  friend struct base::DefaultSingletonTraits<OnevnPermissionManagerFactory>;

  OnevnPermissionManagerFactory();
  ~OnevnPermissionManagerFactory() override;

  // BrowserContextKeyedBaseFactory methods:
  KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* profile) const override;

  DISALLOW_COPY_AND_ASSIGN(OnevnPermissionManagerFactory);
};

#endif // ONEVN_BROWSER_PERMISSION_ONEVN_PERMISSION_MANAGER_FACTORR_H_
