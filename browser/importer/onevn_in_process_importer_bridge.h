/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_IMPORTER_ONEVN_IN_PROCESS_IMPORTER_BRIDGE_H_
#define ONEVN_BROWSER_IMPORTER_ONEVN_IN_PROCESS_IMPORTER_BRIDGE_H_

#include <string>
#include <vector>

#include "onevn/browser/importer/onevn_profile_writer.h"
#include "chrome/browser/importer/in_process_importer_bridge.h"
#include "net/cookies/canonical_cookie.h"
#include "onevn/browser/importer/onevn_external_process_importer_host.h"

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "build/build_config.h"

class OnevnInProcessImporterBridge : public InProcessImporterBridge {
 public:
  OnevnInProcessImporterBridge(
      ProfileWriter* writer,
      base::WeakPtr<ExternalProcessImporterHost> host);

  void SetCookies(
      const std::vector<net::CanonicalCookie>& cookies) override;
  void UpdateStats(const OnevnStats& stats) override;
  void UpdateLedger(const OnevnLedger& ledger) override;
  void UpdateReferral(const OnevnReferral& referral) override;
  void UpdateWindows(const ImportedWindowState& windowState) override;
  void UpdateSettings(const SessionStoreSettings& settings) override;

  void FinishLedgerImport();
  void Cancel();

 private:
  ~OnevnInProcessImporterBridge() override;

  OnevnProfileWriter* const writer_;  // weak

  DISALLOW_COPY_AND_ASSIGN(OnevnInProcessImporterBridge);
};

#endif  // ONEVN_BROWSER_IMPORTER_ONEVN_IN_PROCESS_IMPORTER_BRIDGE_H_
