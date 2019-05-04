/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_IMPORTER_ONEVN_IMPORTER_LOCK_DIALOG_H_
#define ONEVN_BROWSER_IMPORTER_ONEVN_IMPORTER_LOCK_DIALOG_H_

#include "base/callback_forward.h"
#include "chrome/common/importer/importer_data_types.h"
#include "ui/gfx/native_widget_types.h"

namespace onevn {
namespace importer {

// This function is called by an ImporterHost, and presents the Chrome profile
// warning dialog. After closing the dialog, the ImportHost receives a callback
// with the message either to skip the import, or to continue the process.
void ShowImportLockDialog(gfx::NativeWindow parent,
                          ::importer::SourceProfile source_profile,
                          const base::Callback<void(bool)>& callback);

}  // namespace importer
}  // namespace onevn

#endif  // ONEVN_BROWSER_IMPORTER_ONEVN_IMPORTER_LOCK_DIALOG_H_
