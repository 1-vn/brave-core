/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_CHROMIUM_SRC_CHROME_BROWSER_UI_WEBUI_DARK_MODE_HANDLER_H_
#define ONEVN_CHROMIUM_SRC_CHROME_BROWSER_UI_WEBUI_DARK_MODE_HANDLER_H_

#include "onevn/browser/ui/onevn_dark_mode_observer.h"

#define DarkModeObserver OnevnDarkModeObserver
#include "../../../../../../chrome/browser/ui/webui/dark_mode_handler.h"  // NOLINT
#undef DarkModeObserver

#endif  // ONEVN_CHROMIUM_SRC_CHROME_BROWSER_UI_WEBUI_DARK_MODE_HANDLER_H_
