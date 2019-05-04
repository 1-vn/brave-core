/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/ui/toolbar/onevn_toolbar_actions_model.h"

#include "onevn/common/extensions/extension_constants.h"
#include "chrome/browser/ui/toolbar/toolbar_actions_model.h"
#include "extensions/common/extension.h"

bool OneVNToolbarActionsModel::ShouldAddExtension(const extensions::Extension* extension) {
  // Don't show the OneVN and Rewards 'extensions' in the ToolbarActions
  // extensions area. They will instead be shown in the OneVNActions area.
  if (extension->id() == onevn_extension_id || 
      extension->id() == onevn_rewards_extension_id) {
    return false;
  }
  return ToolbarActionsModel::ShouldAddExtension(extension);
}
