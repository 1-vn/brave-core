/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/resources/md_extensions/grit/onevn_extensions_resources.h"
#include "onevn/browser/resources/md_extensions/grit/onevn_extensions_resources_map.h"
#include "onevn/grit/onevn_generated_resources.h"
#include "chrome/common/buildflags.h"
#include "chrome/grit/generated_resources.h"
#include "content/public/browser/web_ui_data_source.h"

namespace extensions {

namespace {

// Called from the original extension_ui.cc's CreateMdExtensionsSource via a
// patch.
void OnevnAddExtensionsResources(content::WebUIDataSource* source) {
#if !BUILDFLAG(OPTIMIZE_WEBUI)
  for (size_t i = 0; i < kOnevnExtensionsResourcesSize; ++i) {
    source->AddResourcePath(kOnevnExtensionsResources[i].name,
                            kOnevnExtensionsResources[i].value);
  }
#endif
}

}  // namespace

}  // namespace extensions

// These are defined in generated_resources.h, but since we are including it
// here the original extensions_ui.cc shouldn't include it again and the
// redefined values will be used.
#undef IDS_MD_EXTENSIONS_ITEM_CHROME_WEB_STORE
#define IDS_MD_EXTENSIONS_ITEM_CHROME_WEB_STORE \
  IDS_MD_EXTENSIONS_ONEVN_ITEM_CHROME_WEB_STORE
#undef IDS_MD_EXTENSIONS_ITEM_SOURCE_WEBSTORE
#define IDS_MD_EXTENSIONS_ITEM_SOURCE_WEBSTORE \
  IDS_MD_EXTENSIONS_ONEVN_ITEM_SOURCE_WEBSTORE

#include "../../../../../../chrome/browser/ui/webui/extensions/extensions_ui.cc"  // NOLINT
