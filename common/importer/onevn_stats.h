/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMMON_IMPORTER_ONEVN_STATS_H_
#define ONEVN_COMMON_IMPORTER_ONEVN_STATS_H_

struct OneVNStats {
  int adblock_count;
  int trackingProtection_count;
  int httpsEverywhere_count;

  OneVNStats()
    : adblock_count(0),
      trackingProtection_count(0),
      httpsEverywhere_count(0) {}
};

#endif  // ONEVN_COMMON_IMPORTER_ONEVN_STATS_H_
