/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <vector>

#include "onevn/browser/importer/onevn_external_process_importer_client.h"

OneVNExternalProcessImporterClient::OneVNExternalProcessImporterClient(
    base::WeakPtr<ExternalProcessImporterHost> importer_host,
    const importer::SourceProfile& source_profile,
    uint16_t items,
    OneVNInProcessImporterBridge* bridge)
    : ExternalProcessImporterClient(
          importer_host, source_profile, items, bridge),
      total_cookies_count_(0),
      bridge_(bridge),
      cancelled_(false) {}

void OneVNExternalProcessImporterClient::Cancel() {
  if (cancelled_)
    return;

  cancelled_ = true;
  ExternalProcessImporterClient::Cancel();
}

void OneVNExternalProcessImporterClient::OnCookiesImportStart(
    uint32_t total_cookies_count) {
  if (cancelled_)
    return;

  total_cookies_count_ = total_cookies_count;
  cookies_.reserve(total_cookies_count);
}

void OneVNExternalProcessImporterClient::OnCookiesImportGroup(
    const std::vector<net::CanonicalCookie>& cookies_group) {
  if (cancelled_)
    return;

  cookies_.insert(cookies_.end(), cookies_group.begin(),
                  cookies_group.end());
  if (cookies_.size() >= total_cookies_count_)
    bridge_->SetCookies(cookies_);
}

void OneVNExternalProcessImporterClient::OnStatsImportReady(
    const OneVNStats& stats) {
  if (cancelled_)
    return;

  bridge_->UpdateStats(stats);
}

void OneVNExternalProcessImporterClient::OnLedgerImportReady(
    const OneVNLedger& ledger) {
  if (cancelled_)
    return;

  bridge_->UpdateLedger(ledger);
}

void OneVNExternalProcessImporterClient::OnReferralImportReady(
    const OneVNReferral& referral) {
  if (cancelled_)
    return;

  bridge_->UpdateReferral(referral);
}

void OneVNExternalProcessImporterClient::OnWindowsImportReady(
    const ImportedWindowState& windowState) {
  if (cancelled_)
    return;

  bridge_->UpdateWindows(windowState);
}

void OneVNExternalProcessImporterClient::OnSettingsImportReady(
    const SessionStoreSettings& settings) {
  if (cancelled_)
    return;

  bridge_->UpdateSettings(settings);
}

OneVNExternalProcessImporterClient::~OneVNExternalProcessImporterClient() {}
