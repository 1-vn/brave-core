/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_IMPORTER_ONEVN_EXTERNAL_PROCESS_IMPORTER_HOST_H_
#define ONEVN_BROWSER_IMPORTER_ONEVN_EXTERNAL_PROCESS_IMPORTER_HOST_H_

#include "base/memory/weak_ptr.h"
#include "onevn/browser/importer/browser_profile_lock.h"
#include "chrome/browser/importer/external_process_importer_host.h"

class OneVNExternalProcessImporterHost : public ExternalProcessImporterHost {
 public:
  OneVNExternalProcessImporterHost();

  void StartImportSettings(
      const importer::SourceProfile& source_profile,
      Profile* target_profile,
      uint16_t items,
      ProfileWriter* writer) override;

 private:
  ~OneVNExternalProcessImporterHost() override;

  // Launches the utility process that starts the import task, unless bookmark
  // or template model are not yet loaded. If load is not detected, this method
  // will be called when the loading observer sees that model loading is
  // complete.
  void LaunchImportIfReady() override;

  // Make sure that Chrome or OneVN isn't running, if import browser is Chrome
  // or OneVN. Show to the user a dialog that notifies that is necessary to
  // close Chrome or OneVN prior to continuing the import. Returns false iff
  // import should be aborted.
  bool CheckForChromeOrOneVNLock();

  // ShowWarningDialog() asks user to close the application that is owning the
  // lock. They can retry or skip the importing process.
  // This method should not be called if the importer is in headless mode.
  void ShowWarningDialog();

  // This is called when when user ends the lock dialog by clicking on either
  // the "Skip" or "Continue" buttons. |is_continue| is true when user clicked
  // the "Continue" button.
  void OnImportLockDialogEnd(bool is_continue);

  // Chrome or OneVN profile lock.
  std::unique_ptr<BrowserProfileLock> browser_lock_;

  // Vends weak pointers for the importer to call us back.
  base::WeakPtrFactory<OneVNExternalProcessImporterHost> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(OneVNExternalProcessImporterHost);
};

#endif  // ONEVN_BROWSER_IMPORTER_ONEVN_EXTERNAL_PROCESS_IMPORTER_HOST_H_
