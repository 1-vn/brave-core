/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_SHIELDS_BROWSER_AD_BLOCK_CUSTOM_FILTERS_SERVICE_H_
#define ONEVN_COMPONENTS_ONEVN_SHIELDS_BROWSER_AD_BLOCK_CUSTOM_FILTERS_SERVICE_H_

#include <memory>
#include <string>

#include "onevn/components/onevn_shields/browser/ad_block_base_service.h"

class AdBlockServiceTest;

namespace onevn_shields {

// The onevn shields service in charge of custom filter ad-block
// checking and init.
class AdBlockCustomFiltersService : public AdBlockBaseService {
 public:
  AdBlockCustomFiltersService();
  ~AdBlockCustomFiltersService() override;

  std::string GetCustomFilters();
  bool UpdateCustomFilters(const std::string& custom_filters);
  scoped_refptr<base::SequencedTaskRunner> GetTaskRunner() override;

 protected:
  bool Init() override;

 private:
  friend class ::AdBlockServiceTest;
  void UpdateCustomFiltersOnFileTaskRunner(const std::string& custom_filters);

  DISALLOW_COPY_AND_ASSIGN(AdBlockCustomFiltersService);
};

// Creates the AdBlockCustomFiltersService
std::unique_ptr<AdBlockCustomFiltersService>
AdBlockCustomFiltersServiceFactory();

}  // namespace onevn_shields

#endif  // ONEVN_COMPONENTS_ONEVN_SHIELDS_BROWSER_AD_BLOCK_CUSTOM_FILTERS_SERVICE_H_
