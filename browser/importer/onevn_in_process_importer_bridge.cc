/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/importer/onevn_in_process_importer_bridge.h"
#include "chrome/browser/importer/external_process_importer_host.h"

OneVNInProcessImporterBridge::OneVNInProcessImporterBridge(
    ProfileWriter* writer,
    base::WeakPtr<ExternalProcessImporterHost> host) :
  InProcessImporterBridge(writer, host),
  writer_(static_cast<OneVNProfileWriter*>(writer)) {
}

void OneVNInProcessImporterBridge::SetCookies(
    const std::vector<net::CanonicalCookie>& cookies) {
  writer_->AddCookies(cookies);
}

void OneVNInProcessImporterBridge::UpdateStats(const OneVNStats& stats) {
  writer_->UpdateStats(stats);
}

void OneVNInProcessImporterBridge::UpdateLedger(
    const OneVNLedger& ledger) {
  writer_->SetBridge(this);
  writer_->UpdateLedger(ledger);
}

void OneVNInProcessImporterBridge::FinishLedgerImport () {
  NotifyItemEnded(importer::LEDGER);
  NotifyEnded();
}

void OneVNInProcessImporterBridge::Cancel () {
  host_->Cancel();
}

void OneVNInProcessImporterBridge::UpdateReferral(const OneVNReferral& referral) {
  writer_->UpdateReferral(referral);
}

void OneVNInProcessImporterBridge::UpdateWindows(
    const ImportedWindowState& windowState) {
  // TODO: Can we just restore windows/tabs here? Do we even need to do anything with the ProfileWriter?
  writer_->UpdateWindows(windowState);
}

void OneVNInProcessImporterBridge::UpdateSettings(
      const SessionStoreSettings& settings) {
  writer_->UpdateSettings(settings);
}

OneVNInProcessImporterBridge::~OneVNInProcessImporterBridge() {}
