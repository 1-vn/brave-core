/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_RENDERER_HOST_ONEVN_RENDER_MESSAGE_FILTER_H_
#define ONEVN_BROWSER_RENDERER_HOST_ONEVN_RENDER_MESSAGE_FILTER_H_

#include "chrome/browser/renderer_host/chrome_render_message_filter.h"
#include "content/public/browser/browser_message_filter.h"

class HostContentSettingsMap;

class OneVNRenderMessageFilter : public ChromeRenderMessageFilter {
 public:
  using ChromeRenderMessageFilter::ChromeRenderMessageFilter;
  OneVNRenderMessageFilter(int render_process_id, Profile* profile);
  bool OnMessageReceived(const IPC::Message& message) override;

 private:
  friend class base::DeleteHelper<OneVNRenderMessageFilter>;

  ~OneVNRenderMessageFilter() override;

  void OnAllowDatabase(int render_frame_id,
                       const GURL& origin_url,
                       const GURL& top_origin_url,
                       bool* allowed);

  void OnAllowDOMStorage(int render_frame_id,
                         const GURL& origin_url,
                         const GURL& top_origin_url,
                         bool local,
                         bool* allowed);

  void OnAllowIndexedDB(int render_frame_id,
                        const GURL& origin_url,
                        const GURL& top_origin_url,
                        bool* allowed);

  void ShouldStoreState(int render_frame_id,
                        const GURL& origin_url,
                        const GURL& top_origin_url,
                        bool* allowed);

  HostContentSettingsMap* host_content_settings_map_;
  DISALLOW_COPY_AND_ASSIGN(OneVNRenderMessageFilter);
};

#endif  // ONEVN_BROWSER_RENDERER_HOST_ONEVN_RENDER_MESSAGE_FILTER_H_
