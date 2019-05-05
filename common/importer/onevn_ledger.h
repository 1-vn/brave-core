/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMMON_IMPORTER_ONEVN_LEDGER_H_
#define ONEVN_COMMON_IMPORTER_ONEVN_LEDGER_H_

#include <string>
#include <vector>

struct OnevnPublisher {
  std::string key;
  bool verified;
  std::string name;
  std::string url;
  std::string provider;
  int pin_percentage;

  OnevnPublisher();
  OnevnPublisher(const OnevnPublisher& other);
  ~OnevnPublisher();
};

// NOTE: if we need to read more data from session-store-1,
// we may consider moving this to onevn_importer.h (or similar)
struct SessionStoreSettings {
  struct PaymentSettings {
    bool allow_media_publishers;
    bool allow_non_verified;
    bool enabled;
    double contribution_amount;
    uint64_t min_visit_time;
    unsigned int min_visits;
  } payments;
  std::string default_search_engine;
  bool use_alternate_private_search_engine;
  bool use_alternate_private_search_engine_tor;
};

struct OnevnLedger {
  OnevnLedger();
  OnevnLedger(const OnevnLedger& other);
  ~OnevnLedger();

  std::string passphrase;
  std::vector<std::string> excluded_publishers;
  std::vector<OnevnPublisher> pinned_publishers;
  SessionStoreSettings settings;
};

#endif  // ONEVN_COMMON_IMPORTER_ONEVN_LEDGER_H_
