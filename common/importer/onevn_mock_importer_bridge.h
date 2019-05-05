/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMMON_IMPORTER_ONEVN_MOCK_IMPORTER_BRIDGE_H_
#define ONEVN_COMMON_IMPORTER_ONEVN_MOCK_IMPORTER_BRIDGE_H_

#include <vector>

#include "onevn/common/importer/onevn_ledger.h"
#include "onevn/common/importer/onevn_stats.h"
#include "onevn/common/importer/imported_browser_window.h"
#include "chrome/common/importer/mock_importer_bridge.h"
#include "net/cookies/canonical_cookie.h"
#include "testing/gmock/include/gmock/gmock.h"

struct OnevnStats;
struct OnevnLedger;

class OnevnMockImporterBridge : public MockImporterBridge {
 public:
  OnevnMockImporterBridge();

  MOCK_METHOD1(SetCookies,
               void(const std::vector<net::CanonicalCookie>&));
  MOCK_METHOD1(UpdateStats,
               void(const OnevnStats&));
  MOCK_METHOD1(UpdateLedger,
               void(const OnevnLedger&));
  MOCK_METHOD1(UpdateWindows,
               void(const ImportedWindowState&));

 private:
  ~OnevnMockImporterBridge() override;
};

#endif  // ONEVN_COMMON_IMPORTER_ONEVN_MOCK_IMPORTER_BRIDGE_H_
