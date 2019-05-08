/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_UI_WEBUI_ONEVN_REWARDS_SOURCE_H_
#define ONEVN_BROWSER_UI_WEBUI_ONEVN_REWARDS_SOURCE_H_

#include <string>
#include <vector>

#include "base/macros.h"
#include "chrome/browser/bitmap_fetcher/bitmap_fetcher_service.h"
#include "content/public/browser/url_data_source.h"

class GURL;
class Profile;
class SkBitmap;

class OnevnRewardsSource : public content::URLDataSource {
 public:
  explicit OnevnRewardsSource(Profile* profile);

  ~OnevnRewardsSource() override;

  // content::URLDataSource implementation.
  std::string GetSource() const override;
  void StartDataRequest(
      const std::string& path,
      const content::ResourceRequestInfo::WebContentsGetter& wc_getter,
      const content::URLDataSource::GotDataCallback& got_data_callback)
      override;
  std::string GetMimeType(const std::string&) const override;
  bool AllowCaching() const override;
  bool ShouldReplaceExistingSource() const override;
  bool ShouldServiceRequest(const GURL& url,
                            content::ResourceContext* resource_context,
                            int render_process_id) const override;

 private:
  void OnBitmapFetched(
      const content::URLDataSource::GotDataCallback& got_data_callback,
      BitmapFetcherService::RequestId request_id,
      const GURL& url,
      const SkBitmap& bitmap);

  Profile* profile_;
  std::vector<std::string> resource_fetchers_;
  std::vector<BitmapFetcherService::RequestId> request_ids_;

  DISALLOW_COPY_AND_ASSIGN(OnevnRewardsSource);
};

#endif  // ONEVN_BROWSER_UI_WEBUI_ONEVN_REWARDS_SOURCE_H_