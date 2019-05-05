/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_PERMISSION_ONEVN_PERMISSION_MANAGER_H_
#define ONEVN_BROWSER_PERMISSION_ONEVN_PERMISSION_MANAGER_H_

#include "chrome/browser/permissions/permission_manager.h"

class OnevnPermissionManager : public PermissionManager {
 public:
  explicit OnevnPermissionManager(Profile* profile);

 private:
  DISALLOW_COPY_AND_ASSIGN(OnevnPermissionManager);
};

#endif // ONEVN_BROWSER_PERMISSION_ONEVN_PERMISSION_MANAGER_H_
