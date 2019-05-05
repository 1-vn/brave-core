/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_IMPORTER_ONEVN_PROFILE_WRITER_H_
#define ONEVN_BROWSER_IMPORTER_ONEVN_PROFILE_WRITER_H_

#include <memory>
#include <string>
#include <vector>

#include "base/macros.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/importer/profile_writer.h"
#include "net/cookies/canonical_cookie.h"
#include "onevn/components/onevn_rewards/browser/rewards_service_observer.h"
#include "onevn/common/importer/onevn_ledger.h"

struct OnevnStats;
struct OnevnReferral;
class OnevnInProcessImporterBridge;
struct ImportedWindowState;

class OnevnProfileWriter : public ProfileWriter,
                           public onevn_rewards::RewardsServiceObserver,
                           public base::SupportsWeakPtr<OnevnProfileWriter>{
 public:
  explicit OnevnProfileWriter(Profile* profile);

  virtual void AddCookies(const std::vector<net::CanonicalCookie>& cookies);
  virtual void UpdateStats(const OnevnStats& stats);
  virtual void UpdateLedger(const OnevnLedger& ledger);
  virtual void UpdateReferral(const OnevnReferral& referral);
  virtual void UpdateWindows(const ImportedWindowState& windowState);
  virtual void UpdateSettings(const SessionStoreSettings& settings);

  void SetBridge(OnevnInProcessImporterBridge* bridge);

  void OnIsWalletCreated(bool created);

  // onevn_rewards::RewardsServiceObserver:
  void OnWalletInitialized(onevn_rewards::RewardsService* rewards_service,
                           uint32_t result) override;
  void OnRecoverWallet(onevn_rewards::RewardsService* rewards_service,
                       unsigned int result,
                       double balance,
                       std::vector<onevn_rewards::Grant> grants) override;
  void OnWalletProperties(
      onevn_rewards::RewardsService* rewards_service,
      int error_code,
      std::unique_ptr<onevn_rewards::WalletProperties> properties) override;

 protected:
  friend class base::RefCountedThreadSafe<OnevnProfileWriter>;
  const scoped_refptr<base::SequencedTaskRunner> task_runner_;
  void CancelWalletImport(std::string msg);
  void SetWalletProperties(onevn_rewards::RewardsService* rewards_service);
  void BackupWallet();
  void OnWalletBackupComplete(bool result);
  ~OnevnProfileWriter() override;

 private:
  onevn_rewards::RewardsService* rewards_service_;
  OnevnInProcessImporterBridge* bridge_ptr_;
  double new_contribution_amount_;
  unsigned int pinned_item_count_;
  OnevnLedger ledger_;
  // Only used when wallet exists and first action is guaranteed
  // to be FetchWalletProperties(). See notes in onevn_profile_writer.cc
  bool consider_for_backup_;
};

#endif  // ONEVN_BROWSER_IMPORTER_ONEVN_PROFILE_WRITER_H_
