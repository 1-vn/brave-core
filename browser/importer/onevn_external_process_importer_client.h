/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_IMPORTER_ONEVN_EXTERNAL_PROCESS_IMPORTER_CLIENT_H_
#define ONEVN_BROWSER_IMPORTER_ONEVN_EXTERNAL_PROCESS_IMPORTER_CLIENT_H_

#include <vector>

#include "onevn/browser/importer/onevn_in_process_importer_bridge.h"
#include "chrome/browser/importer/external_process_importer_client.h"
#include "net/cookies/canonical_cookie.h"

struct OnevnStats;
struct OnevnLedger;
struct ImportedWindowState;

class OnevnExternalProcessImporterClient : public ExternalProcessImporterClient {
 public:
  OnevnExternalProcessImporterClient(
      base::WeakPtr<ExternalProcessImporterHost> importer_host,
      const importer::SourceProfile& source_profile,
      uint16_t items,
      OnevnInProcessImporterBridge* bridge);

  // Called by the ExternalProcessImporterHost on import cancel.
  void Cancel();

  void OnCookiesImportStart(
      uint32_t total_cookies_count) override;
  void OnCookiesImportGroup(
      const std::vector<net::CanonicalCookie>& cookies_group) override;
  void OnStatsImportReady(
       const OnevnStats& stats) override;
  void OnLedgerImportReady(
       const OnevnLedger& ledger) override;
  void OnReferralImportReady(
       const OnevnReferral& referral) override;
  void OnWindowsImportReady(
       const ImportedWindowState& windowState) override;
  void OnSettingsImportReady(const SessionStoreSettings& settings) override;

 private:
  ~OnevnExternalProcessImporterClient() override;

  // Total number of cookies to import.
  size_t total_cookies_count_;

  scoped_refptr<OnevnInProcessImporterBridge> bridge_;

  std::vector<net::CanonicalCookie> cookies_;

  // True if import process has been cancelled.
  bool cancelled_;

  DISALLOW_COPY_AND_ASSIGN(OnevnExternalProcessImporterClient);
};

#endif  // ONEVN_BROWSER_IMPORTER_ONEVN_EXTERNAL_PROCESS_IMPORTER_CLIENT_H_
