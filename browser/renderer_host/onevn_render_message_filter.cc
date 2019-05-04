/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/renderer_host/onevn_render_message_filter.h"

#include "onevn/browser/onevn_browser_process_impl.h"
#include "onevn/components/onevn_shields/browser/onevn_shields_web_contents_observer.h"
#include "onevn/components/onevn_shields/browser/buildflags/buildflags.h"  // For STP
#include "onevn/components/onevn_shields/browser/tracking_protection_service.h"
#include "onevn/components/content_settings/core/browser/onevn_cookie_settings.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/common/render_messages.h"

using base::string16;
using onevn_shields::OneVNShieldsWebContentsObserver;
using content_settings::CookieSettings;

OneVNRenderMessageFilter::OneVNRenderMessageFilter(int render_process_id,
                                                   Profile* profile)
    : ChromeRenderMessageFilter(render_process_id, profile),
      host_content_settings_map_(
          HostContentSettingsMapFactory::GetForProfile(profile)) {}

OneVNRenderMessageFilter::~OneVNRenderMessageFilter() {}

bool OneVNRenderMessageFilter::OnMessageReceived(const IPC::Message& message) {
  bool handled = true;
  IPC_BEGIN_MESSAGE_MAP(OneVNRenderMessageFilter, message)
    IPC_MESSAGE_HANDLER(ChromeViewHostMsg_AllowDatabase, OnAllowDatabase);
    IPC_MESSAGE_HANDLER(ChromeViewHostMsg_AllowDOMStorage, OnAllowDOMStorage);
    IPC_MESSAGE_HANDLER(ChromeViewHostMsg_AllowIndexedDB, OnAllowIndexedDB);
    IPC_MESSAGE_UNHANDLED(handled = false)
  IPC_END_MESSAGE_MAP()

  return ChromeRenderMessageFilter::OnMessageReceived(message);
}

void OneVNRenderMessageFilter::ShouldStoreState(int render_frame_id,
                                                const GURL& origin_url,
                                                const GURL& top_origin_url,
                                                bool* allowed) {
  GURL tab_origin =
      OneVNShieldsWebContentsObserver::GetTabURLFromRenderFrameInfo(
          render_process_id_, render_frame_id, -1)
          .GetOrigin();
  *allowed =
      g_onevn_browser_process->tracking_protection_service()->ShouldStoreState(
          cookie_settings_.get(), host_content_settings_map_,
          render_process_id_, render_frame_id, origin_url, top_origin_url,
          tab_origin);
}

void OneVNRenderMessageFilter::OnAllowDatabase(int render_frame_id,
                                               const GURL& origin_url,
                                               const GURL& top_origin_url,
                                               bool* allowed) {
  ShouldStoreState(render_frame_id, origin_url, top_origin_url, allowed);
  if (*allowed) {
    ChromeRenderMessageFilter::OnAllowDatabase(render_frame_id, origin_url,
                                               top_origin_url, allowed);
  }
}

void OneVNRenderMessageFilter::OnAllowDOMStorage(int render_frame_id,
                                                 const GURL& origin_url,
                                                 const GURL& top_origin_url,
                                                 bool local,
                                                 bool* allowed) {
  ShouldStoreState(render_frame_id, origin_url, top_origin_url, allowed);
  if (*allowed) {
    ChromeRenderMessageFilter::OnAllowDOMStorage(
        render_frame_id, origin_url, top_origin_url, local, allowed);
  }
}

void OneVNRenderMessageFilter::OnAllowIndexedDB(int render_frame_id,
                                                const GURL& origin_url,
                                                const GURL& top_origin_url,
                                                bool* allowed) {
  ShouldStoreState(render_frame_id, origin_url, top_origin_url, allowed);
  if (*allowed) {
    ChromeRenderMessageFilter::OnAllowIndexedDB(render_frame_id, origin_url,
                                                top_origin_url, allowed);
  }
}
