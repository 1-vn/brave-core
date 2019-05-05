/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/importer/onevn_external_process_importer_client.h"
#include "onevn/browser/importer/onevn_external_process_importer_host.h"
#include "onevn/browser/importer/onevn_profile_lock.h"
#include "onevn/browser/importer/chrome_profile_lock.h"
#include "onevn/browser/importer/onevn_in_process_importer_bridge.h"

#include "onevn/browser/importer/onevn_importer_lock_dialog.h"

OnevnExternalProcessImporterHost::OnevnExternalProcessImporterHost()
  : ExternalProcessImporterHost(),
    weak_ptr_factory_(this) {}

OnevnExternalProcessImporterHost::~OnevnExternalProcessImporterHost() {}

void OnevnExternalProcessImporterHost::StartImportSettings(
    const importer::SourceProfile& source_profile,
    Profile* target_profile,
    uint16_t items,
    ProfileWriter* writer) {
  // We really only support importing from one host at a time.
  DCHECK(!profile_);
  DCHECK(target_profile);

  profile_ = target_profile;
  writer_ = writer;
  source_profile_ = source_profile;
  items_ = items;

  if (!ExternalProcessImporterHost::CheckForFirefoxLock(source_profile)) {
    Cancel();
    return;
  }

  if (!CheckForChromeOrOnevnLock()) {
    Cancel();
    return;
  }

  ExternalProcessImporterHost::CheckForLoadedModels(items);

  LaunchImportIfReady();
}

void OnevnExternalProcessImporterHost::LaunchImportIfReady() {
  if (waiting_for_bookmarkbar_model_ || template_service_subscription_.get() ||
      !is_source_readable_ || cancelled_)
    return;

  // This is the in-process half of the bridge, which catches data from the IPC
  // pipe and feeds it to the ProfileWriter. The external process half of the
  // bridge lives in the external process (see ProfileImportThread).
  // The ExternalProcessImporterClient created in the next line owns the bridge,
  // and will delete it.
  OnevnInProcessImporterBridge* bridge =
      new OnevnInProcessImporterBridge(writer_.get(),
                                       weak_ptr_factory_.GetWeakPtr());
  client_ = new OnevnExternalProcessImporterClient(
      weak_ptr_factory_.GetWeakPtr(), source_profile_, items_, bridge);
  client_->Start();
}

void OnevnExternalProcessImporterHost::ShowWarningDialog() {
  DCHECK(!headless_);
  onevn::importer::ShowImportLockDialog(
      parent_window_,
      source_profile_,
      base::Bind(&OnevnExternalProcessImporterHost::OnImportLockDialogEnd,
                 weak_ptr_factory_.GetWeakPtr()));
}

void OnevnExternalProcessImporterHost::OnImportLockDialogEnd(bool is_continue) {
  if (is_continue) {
    // User chose to continue, then we check the lock again to make sure that
    // the other browser has been closed. Try to import the settings if
    // successful. Otherwise, show a warning dialog.
    browser_lock_->Lock();
    if (browser_lock_->HasAcquired()) {
      is_source_readable_ = true;
      LaunchImportIfReady();
    } else {
      ShowWarningDialog();
    }
  } else {
    NotifyImportEnded();
  }
}

bool OnevnExternalProcessImporterHost::CheckForChromeOrOnevnLock() {
  if (!(source_profile_.importer_type == importer::TYPE_CHROME ||
        source_profile_.importer_type == importer::TYPE_ONEVN))
    return true;

  DCHECK(!browser_lock_.get());

  if (source_profile_.importer_type == importer::TYPE_CHROME) {
    // Extract the user data directory from the path of the profile to be
    // imported, because we can only lock/unlock the entire user directory with
    // ProcessSingleton.
    base::FilePath user_data_dir = source_profile_.source_path.DirName();
    browser_lock_.reset(new ChromeProfileLock(user_data_dir));
  } else {  // source_profile_.importer_type == importer::TYPE_ONEVN
    browser_lock_.reset(new OnevnProfileLock(source_profile_.source_path));
  }

  browser_lock_->Lock();
  if (browser_lock_->HasAcquired())
    return true;

  // If fail to acquire the lock, we set the source unreadable and
  // show a warning dialog, unless running without UI (in which case the import
  // must be aborted).
  is_source_readable_ = false;
  if (headless_)
    return false;

  ShowWarningDialog();
  return true;
}
