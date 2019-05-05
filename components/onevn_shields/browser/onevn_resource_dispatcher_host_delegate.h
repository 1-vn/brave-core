/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_LOADER_ONEVN_RESOURCE_DISPATCHER_HOST_DELEGATE_H_
#define ONEVN_BROWSER_LOADER_ONEVN_RESOURCE_DISPATCHER_HOST_DELEGATE_H_

#include <memory>
#include <vector>

#include "chrome/browser/loader/chrome_resource_dispatcher_host_delegate.h"


class OnevnResourceDispatcherHostDelegate
    : public ChromeResourceDispatcherHostDelegate {
 public:
  OnevnResourceDispatcherHostDelegate();
  ~OnevnResourceDispatcherHostDelegate() override;

 protected:
  void AppendStandardResourceThrottles(
      net::URLRequest* request,
      content::ResourceContext* resource_context,
      content::ResourceType resource_type,
      std::vector<std::unique_ptr<content::ResourceThrottle>>* throttles)
    override;

  DISALLOW_COPY_AND_ASSIGN(OnevnResourceDispatcherHostDelegate);
};

#endif  // ONEVN_BROWSER_LOADER_ONEVN_RESOURCE_DISPATCHER_HOST_DELEGATE_H_
