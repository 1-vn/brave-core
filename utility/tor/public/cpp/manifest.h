/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_UTILITY_TOR_PUBLIC_CPP_MANIFEST_H_
#define ONEVN_UTILITY_TOR_PUBLIC_CPP_MANIFEST_H_

#include "services/service_manager/public/cpp/manifest.h"

namespace tor {

const service_manager::Manifest& GetTorLauncherManifest();

}  // namespace tor

#endif  // ONEVN_UTILITY_TOR_PUBLIC_CPP_MANIFEST_H_
