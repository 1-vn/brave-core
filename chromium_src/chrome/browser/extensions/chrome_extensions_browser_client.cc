// Copyright (c) 2019 The Onevn Authors. All rights reserved.

#include "onevn/browser/extensions/updater/onevn_update_client_config.h"
#include "chrome/browser/extensions/chrome_extensions_browser_client.h"
#include "chrome/browser/extensions/updater/chrome_update_client_config.h"

#define ChromeUpdateClientConfig OnevnUpdateClientConfig
#include "../../../../../chrome/browser/extensions/chrome_extensions_browser_client.cc"  // NOLINT
#undef ChromeUpdateClientConfig
