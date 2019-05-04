/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/permissions/onevn_permission_manager.h"

#include "onevn/browser/autoplay/autoplay_permission_context.h"

OneVNPermissionManager::OneVNPermissionManager(Profile* profile)
  : PermissionManager(profile) {
  permission_contexts_[CONTENT_SETTINGS_TYPE_AUTOPLAY] =
      std::make_unique<AutoplayPermissionContext>(profile);
}
