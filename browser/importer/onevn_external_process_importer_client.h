/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_IMPORTER_ONEVN_EXTERNAL_PROCESS_IMPORTER_CLIENT_H_
#define ONEVN_BROWSER_IMPORTER_ONEVN_EXTERNAL_PROCESS_IMPORTER_CLIENT_H_

#include <vector>

#include "onevn/browser/importer/onevn_in_process_importer_bridge.h"
#include "chrome/browser/importer/external_process_importer_client.h"
#include "net/cookies/canonical_cookie.h"

struct OneVNStats;
struct OneVNLedger;
struct ImportedWindowState;

class OneVNExternalProcessImporterClient : public ExternalProcessImporterClient {
 public:
  OneVNExternalProcessImporterClient(
      base::WeakPtr<ExternalProcessImporterHost> importer_host,
      const importer::SourceProfile& source_profile,
      uint16_t items,
      OneVNInProcessImporterBridge* bridge);

  // Called by the ExternalProcessImporterHost on import cancel.
  void Cancel();

  void OnCookiesImportStart(
      uint32_t total_cookies_count) override;
  void OnCookiesImportGroup(
      const std::vector<net::CanonicalCookie>& cookies_group) override;
  void OnStatsImportReady(
       const OneVNStats& stats) override;
  void OnLedgerImportReady(
       const OneVNLedger& ledger) override;
  void OnReferralImportReady(
       const OneVNReferral& referral) override;
  void OnWindowsImportReady(
       const ImportedWindowState& windowState) override;
  void OnSettingsImportReady(const SessionStoreSettings& settings) override;

 private:
  ~OneVNExternalProcessImporterClient() override;

  // Total number of cookies to import.
  size_t total_cookies_count_;

  scoped_refptr<OneVNInProcessImporterBridge> bridge_;

  std::vector<net::CanonicalCookie> cookies_;

  // True if import process has been cancelled.
  bool cancelled_;

  DISALLOW_COPY_AND_ASSIGN(OneVNExternalProcessImporterClient);
};

#endif  // ONEVN_BROWSER_IMPORTER_ONEVN_EXTERNAL_PROCESS_IMPORTER_CLIENT_H_
