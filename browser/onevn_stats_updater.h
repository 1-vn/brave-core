/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_ONEVN_STATS_UPDATER_H_
#define ONEVN_BROWSER_ONEVN_STATS_UPDATER_H_

#include <memory>

#include "base/callback.h"
#include "base/macros.h"
#include "base/memory/scoped_refptr.h"
#include "url/gurl.h"

class OneVNStatsUpdaterBrowserTest;
class PrefChangeRegistrar;
class PrefRegistrySimple;
class PrefService;

namespace base {
class OneShotTimer;
class RepeatingTimer;
}

namespace net {
class HttpResponseHeaders;
}

namespace network {
class SimpleURLLoader;
}

namespace onevn {

class OneVNStatsUpdaterParams;

class OneVNStatsUpdater {
 public:
  OneVNStatsUpdater(PrefService* pref_service);
  ~OneVNStatsUpdater();

  void Start();
  void Stop();

  using StatsUpdatedCallback =
      base::RepeatingCallback<void(const std::string& url)>;

  void SetStatsUpdatedCallback(StatsUpdatedCallback stats_updated_callback);

 private:
  // Invoked from SimpleURLLoader after download is complete.
  void OnSimpleLoaderComplete(
      std::unique_ptr<onevn::OneVNStatsUpdaterParams> stats_updater_params,
      scoped_refptr<net::HttpResponseHeaders> headers);

  // Invoked when server ping timer fires.
  void OnServerPingTimerFired();

  // Invoked when the specified referral preference changes.
  void OnReferralCheckedForPromoCodeFileChanged();

  void StartServerPingStartupTimer();
  void SendServerPing();

  friend class ::OneVNStatsUpdaterBrowserTest;
  static void SetBaseUpdateURLForTest(const GURL& base_update_url);
  static GURL g_base_update_url_;

  PrefService* pref_service_;
  StatsUpdatedCallback stats_updated_callback_;
  std::unique_ptr<network::SimpleURLLoader> simple_url_loader_;
  std::unique_ptr<base::OneShotTimer> server_ping_startup_timer_;
  std::unique_ptr<base::RepeatingTimer> server_ping_periodic_timer_;
  std::unique_ptr<PrefChangeRegistrar> pref_change_registrar_;

  DISALLOW_COPY_AND_ASSIGN(OneVNStatsUpdater);
};

// Creates the OneVNStatsUpdater
std::unique_ptr<OneVNStatsUpdater> OneVNStatsUpdaterFactory(
    PrefService* pref_service);

// Registers the preferences used by OneVNStatsUpdater
void RegisterPrefsForOneVNStatsUpdater(PrefRegistrySimple* registry);

}  // namespace onevn

#endif  // ONEVN_BROWSER_ONEVN_STATS_UPDATER_H_
