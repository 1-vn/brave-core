/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/components/services/onevn_content_browser_overlay_manifest.h"

#include "base/no_destructor.h"
#include "onevn/common/tor/tor_launcher.mojom.h"
#include "onevn/components/services/bat_ads/public/interfaces/bat_ads.mojom.h"
#include "onevn/components/services/bat_ledger/public/interfaces/bat_ledger.mojom.h"
#include "services/service_manager/public/cpp/manifest_builder.h"

const service_manager::Manifest& GetOnevnContentBrowserOverlayManifest() {
  static base::NoDestructor<service_manager::Manifest> manifest{
      service_manager::ManifestBuilder()
          .WithServiceName("content_browser")
          .WithDisplayName("Onevn")
          .RequireCapability("bat_ads", "bat_ads")
          .RequireCapability("bat_ledger", "bat_ledger")
          .RequireCapability("tor_launcher", "tor_launcher")
          .Build()};
  return *manifest;
}
