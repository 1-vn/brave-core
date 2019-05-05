/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_SHIELDS_BROWSER_BASE_ONEVN_SHIELDS_SERVICE_H_
#define ONEVN_COMPONENTS_ONEVN_SHIELDS_BROWSER_BASE_ONEVN_SHIELDS_SERVICE_H_

#include <stdint.h>

#include <memory>
#include <string>
#include <vector>
// TODO(onevn): <mutex> is an unapproved C++11 header
#include <mutex>  // NOLINT

#include "base/files/file_path.h"
#include "base/sequenced_task_runner.h"
#include "onevn/browser/extensions/onevn_component_extension.h"
#include "content/public/common/resource_type.h"
#include "url/gurl.h"

namespace onevn_shields {

// The onevn shields service in charge of checking onevn shields like ad-block,
// tracking protection, etc.
class BaseOnevnShieldsService : public OnevnComponentExtension {
 public:
  BaseOnevnShieldsService();
  ~BaseOnevnShieldsService() override;
  bool Start();
  void Stop();
  bool IsInitialized() const;
  virtual bool ShouldStartRequest(const GURL& url,
      content::ResourceType resource_type,
      const std::string& tab_host,
      bool* did_match_exception,
      bool* cancel_request_explicitly);
  virtual scoped_refptr<base::SequencedTaskRunner> GetTaskRunner();

 protected:
  virtual bool Init() = 0;
  virtual void Cleanup() = 0;

 private:
  void InitShields();

  bool initialized_;
  std::mutex initialized_mutex_;
  scoped_refptr<base::SequencedTaskRunner> task_runner_;
};

}  // namespace onevn_shields

#endif  // ONEVN_COMPONENTS_ONEVN_SHIELDS_BROWSER_BASE_ONEVN_SHIELDS_SERVICE_H_
