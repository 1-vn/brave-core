/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_SHIELDS_BROWSER_AUTOPLAY_WHITELIST_SERVICE_H_
#define ONEVN_COMPONENTS_ONEVN_SHIELDS_BROWSER_AUTOPLAY_WHITELIST_SERVICE_H_

#include <stdint.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "base/files/file_path.h"
#include "base/memory/weak_ptr.h"
#include "base/sequence_checker.h"
#include "base/sequenced_task_runner.h"
#include "onevn/components/onevn_shields/browser/base_local_data_files_observer.h"
#include "onevn/components/onevn_shields/browser/dat_file_util.h"
#include "content/public/common/resource_type.h"
#include "url/gurl.h"

class AutoplayWhitelistParser;
class OneVNContentSettingsObserverAutoplayTest;

namespace onevn_shields {

// The onevn shields service in charge of autoplay whitelist
class AutoplayWhitelistService : public BaseLocalDataFilesObserver {
 public:
  AutoplayWhitelistService();
  ~AutoplayWhitelistService() override;

  bool ShouldAllowAutoplay(const GURL& url);
  scoped_refptr<base::SequencedTaskRunner> GetTaskRunner();

  // implementation of BaseLocalDataFilesObserver
  void OnComponentReady(const std::string& component_id,
                        const base::FilePath& install_dir,
                        const std::string& manifest) override;

 private:
  friend class ::OneVNContentSettingsObserverAutoplayTest;

  void OnDATFileDataReady();

  onevn_shields::DATFileDataBuffer buffer_;

  std::unique_ptr<AutoplayWhitelistParser> autoplay_whitelist_client_;

  SEQUENCE_CHECKER(sequence_checker_);
  base::WeakPtrFactory<AutoplayWhitelistService> weak_factory_;
  DISALLOW_COPY_AND_ASSIGN(AutoplayWhitelistService);
};

// Creates the AutoplayWhitelistService
std::unique_ptr<AutoplayWhitelistService> AutoplayWhitelistServiceFactory();

}  // namespace onevn_shields

#endif  // ONEVN_COMPONENTS_ONEVN_SHIELDS_BROWSER_AUTOPLAY_WHITELIST_SERVICE_H_
