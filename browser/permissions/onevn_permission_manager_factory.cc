/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/permissions/onevn_permission_manager_factory.h"

#include "onevn/browser/permissions/onevn_permission_manager.h"
#include "chrome/browser/permissions/permission_manager.h"
#include "chrome/browser/permissions/permission_manager.h"
#include "chrome/browser/profiles/profile.h"

// static
PermissionManager*
OneVNPermissionManagerFactory::GetForProfile(Profile* profile) {
  return static_cast<PermissionManager*>(
      GetInstance()->GetServiceForBrowserContext(profile, true));
}

// static
OneVNPermissionManagerFactory* OneVNPermissionManagerFactory::GetInstance() {
  return base::Singleton<OneVNPermissionManagerFactory>::get();
}

OneVNPermissionManagerFactory::OneVNPermissionManagerFactory()
    : PermissionManagerFactory() {
}

OneVNPermissionManagerFactory::~OneVNPermissionManagerFactory() {
}

KeyedService* OneVNPermissionManagerFactory::BuildServiceInstanceFor(
    content::BrowserContext* context) const {
  return new OneVNPermissionManager(Profile::FromBrowserContext(context));
}
