/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/onevn_browser_main_parts.h"
#include "onevn/browser/browsing_data/onevn_clear_browsing_data.h"

void OnevnBrowserMainParts::PreShutdown() {
  content::OnevnClearBrowsingData::ClearOnExit();
}
