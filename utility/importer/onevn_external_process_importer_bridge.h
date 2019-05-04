/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_UTILITY_IMPORTER_ONEVN_EXTERNAL_PROCESS_IMPORTER_BRIDGE_H_
#define ONEVN_UTILITY_IMPORTER_ONEVN_EXTERNAL_PROCESS_IMPORTER_BRIDGE_H_

#include <vector>

#include "chrome/utility/importer/external_process_importer_bridge.h"
#include "net/cookies/canonical_cookie.h"

class OneVNExternalProcessImporterBridge :
                                      public ExternalProcessImporterBridge {
 public:
  // |observer| must outlive this object.
  OneVNExternalProcessImporterBridge(
      const base::flat_map<uint32_t, std::string>& localized_strings,
      scoped_refptr<chrome::mojom::ThreadSafeProfileImportObserverPtr>
          observer);

  void SetCookies(const std::vector<net::CanonicalCookie>& cookies) override;
  void UpdateStats(const OneVNStats& stats) override;
  void UpdateLedger(const OneVNLedger& ledger) override;
  void UpdateReferral(const OneVNReferral& referral) override;
  void UpdateWindows(const ImportedWindowState& windowState) override;
  void UpdateSettings(const SessionStoreSettings& settings) override;


 private:
  ~OneVNExternalProcessImporterBridge() override;

  DISALLOW_COPY_AND_ASSIGN(OneVNExternalProcessImporterBridge);
};

#endif  // ONEVN_UTILITY_IMPORTER_ONEVN_EXTERNAL_PROCESS_IMPORTER_BRIDGE_H_
