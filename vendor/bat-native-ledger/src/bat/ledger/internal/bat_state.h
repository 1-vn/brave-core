/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVNLEDGER_BAT_CLIENT_STATE_H_
#define ONEVNLEDGER_BAT_CLIENT_STATE_H_

#include <map>
#include <memory>
#include <string>

#include "bat/ledger/ledger.h"
#include "bat/ledger/internal/bat_helper.h"

namespace bat_ledger {
class LedgerImpl;
}

namespace onevnledger_bat_state {

class BatState {
 public:
  explicit BatState(bat_ledger::LedgerImpl* ledger);
  ~BatState();

  bool LoadState(const std::string& data);

  void AddReconcile(
      const std::string& viewing_id,
      const onevnledger_bat_helper::CURRENT_RECONCILE& reconcile);

  bool UpdateReconcile(
      const onevnledger_bat_helper::CURRENT_RECONCILE& reconcile);

  onevnledger_bat_helper::CURRENT_RECONCILE GetReconcileById(
      const std::string& viewingId) const;

  void RemoveReconcileById(const std::string& viewingId);

  bool ReconcileExists(const std::string& viewingId) const;

  void SetRewardsMainEnabled(bool enabled);

  bool GetRewardsMainEnabled() const;

  void SetContributionAmount(double amount);

  double GetContributionAmount() const;

  void SetUserChangedContribution();

  bool GetUserChangedContribution() const;

  void SetAutoContribute(bool enabled);

  bool GetAutoContribute() const;

  const std::string& GetBATAddress() const;

  const std::string& GetBTCAddress() const;

  const std::string& GetETHAddress() const;

  const std::string& GetLTCAddress() const;

  uint64_t GetReconcileStamp() const;

  void ResetReconcileStamp();

  uint64_t GetLastGrantLoadTimestamp() const;

  void SetLastGrantLoadTimestamp(uint64_t stamp);

  bool IsWalletCreated() const;

  double GetBalance() const;

  const std::string& GetPaymentId() const;

  void SetPaymentId(const std::string& payment_id);

  const onevnledger_bat_helper::Grants& GetGrants() const;

  void SetGrants(onevnledger_bat_helper::Grants grants);

  const std::string& GetPersonaId() const;

  void SetPersonaId(const std::string& persona_id);

  const std::string& GetUserId() const;

  void SetUserId(const std::string& user_id);

  const std::string& GetRegistrarVK() const;

  void SetRegistrarVK(const std::string& registrar_vk);

  const std::string& GetPreFlight() const;

  void SetPreFlight(const std::string& pre_flight);

  const onevnledger_bat_helper::WALLET_INFO_ST& GetWalletInfo() const;

  void SetWalletInfo(const onevnledger_bat_helper::WALLET_INFO_ST& info);

  const onevnledger_bat_helper::WALLET_PROPERTIES_ST&
  GetWalletProperties() const;

  void SetWalletProperties(
      onevnledger_bat_helper::WALLET_PROPERTIES_ST* properties);

  unsigned int GetDays() const;

  void SetDays(unsigned int days);

  const onevnledger_bat_helper::Transactions& GetTransactions() const;

  void SetTransactions(
      const onevnledger_bat_helper::Transactions& transactions);

  const onevnledger_bat_helper::Ballots& GetBallots() const;

  void SetBallots(const onevnledger_bat_helper::Ballots& ballots);

  const onevnledger_bat_helper::BatchVotes& GetBatch() const;

  void SetBatch(const onevnledger_bat_helper::BatchVotes& votes);

  const std::string& GetCurrency() const;

  void SetCurrency(const std::string& currency);

  uint64_t GetBootStamp() const;

  void SetBootStamp(uint64_t stamp);

  const std::string& GetMasterUserToken() const;

  void SetMasterUserToken(const std::string& token);

  bool AddReconcileStep(const std::string& viewing_id,
                        ledger::ContributionRetry step,
                        int level);

  const onevnledger_bat_helper::CurrentReconciles& GetCurrentReconciles() const;

  double GetDefaultContributionAmount();

  void SetAddress(std::map<std::string, std::string> addresses);

 private:
  void SaveState();

  bat_ledger::LedgerImpl* ledger_;  // NOT OWNED
  std::unique_ptr<onevnledger_bat_helper::CLIENT_STATE_ST> state_;
};

}  // namespace onevnledger_bat_state

#endif  // ONEVNLEDGER_BAT_CLIENT_STATE_H_
