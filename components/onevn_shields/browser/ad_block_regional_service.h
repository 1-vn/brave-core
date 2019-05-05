/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_SHIELDS_BROWSER_AD_BLOCK_REGIONAL_SERVICE_H_
#define ONEVN_COMPONENTS_ONEVN_SHIELDS_BROWSER_AD_BLOCK_REGIONAL_SERVICE_H_

#include <stdint.h>

#include <memory>
#include <string>
#include <vector>

#include "base/files/file_path.h"
#include "onevn/components/onevn_shields/browser/ad_block_base_service.h"
#include "content/public/common/resource_type.h"

class AdBlockServiceTest;

namespace onevn_shields {

// The onevn shields service in charge of ad-block checking and init
// for a specific region.
class AdBlockRegionalService : public AdBlockBaseService {
 public:
  explicit AdBlockRegionalService(const std::string& uuid);
  ~AdBlockRegionalService() override;

  std::string GetUUID() const { return uuid_; }
  std::string GetTitle() const { return title_; }
  scoped_refptr<base::SequencedTaskRunner> GetTaskRunner() override;

 protected:
  bool Init() override;
  void OnComponentReady(const std::string& component_id,
                        const base::FilePath& install_dir,
                        const std::string& manifest) override;

 private:
  friend class ::AdBlockServiceTest;
  static std::string g_ad_block_regional_component_id_;
  static std::string g_ad_block_regional_component_base64_public_key_;
  static std::string g_ad_block_regional_dat_file_version_;
  static void SetComponentIdAndBase64PublicKeyForTest(
      const std::string& component_id,
      const std::string& component_base64_public_key);
  static void SetDATFileVersionForTest(const std::string& dat_file_version);

  std::string uuid_;
  std::string title_;

  DISALLOW_COPY_AND_ASSIGN(AdBlockRegionalService);
};

// Creates the AdBlockRegionalService
std::unique_ptr<AdBlockRegionalService> AdBlockRegionalServiceFactory(
    const std::string& uuid);

}  // namespace onevn_shields

#endif  // ONEVN_COMPONENTS_ONEVN_SHIELDS_BROWSER_AD_BLOCK_REGIONAL_SERVICE_H_
