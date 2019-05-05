/* Copyright 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_EXTENSIONS_API_ONEVN_SYNC_API_H_
#define ONEVN_BROWSER_EXTENSIONS_API_ONEVN_SYNC_API_H_

#include "extensions/browser/extension_function.h"

namespace extensions {
namespace api {

class OnevnSyncGetInitDataFunction : public UIThreadExtensionFunction {
  ~OnevnSyncGetInitDataFunction() override {}
  DECLARE_EXTENSION_FUNCTION("onevnSync.getInitData", UNKNOWN)
  ResponseAction Run() override;
};

class OnevnSyncSyncSetupErrorFunction : public UIThreadExtensionFunction {
  ~OnevnSyncSyncSetupErrorFunction() override {}
  DECLARE_EXTENSION_FUNCTION("onevnSync.syncSetupError", UNKNOWN)
  ResponseAction Run() override;
};

class OnevnSyncSyncDebugFunction : public UIThreadExtensionFunction {
  ~OnevnSyncSyncDebugFunction() override {}
  DECLARE_EXTENSION_FUNCTION("onevnSync.syncDebug", UNKNOWN)
  ResponseAction Run() override;
};

class OnevnSyncSaveInitDataFunction : public UIThreadExtensionFunction {
  ~OnevnSyncSaveInitDataFunction() override {}
  DECLARE_EXTENSION_FUNCTION("onevnSync.saveInitData", UNKNOWN)
  ResponseAction Run() override;
};

class OnevnSyncSyncReadyFunction : public UIThreadExtensionFunction {
  ~OnevnSyncSyncReadyFunction() override {}
  DECLARE_EXTENSION_FUNCTION("onevnSync.syncReady", UNKNOWN)
  ResponseAction Run() override;
};

class OnevnSyncGetExistingObjectsFunction : public UIThreadExtensionFunction {
  ~OnevnSyncGetExistingObjectsFunction() override {}
  DECLARE_EXTENSION_FUNCTION("onevnSync.getExistingObjects", UNKNOWN)
  ResponseAction Run() override;
};

class OnevnSyncResolvedSyncRecordsFunction : public UIThreadExtensionFunction {
  ~OnevnSyncResolvedSyncRecordsFunction() override {}
  DECLARE_EXTENSION_FUNCTION("onevnSync.resolvedSyncRecords", UNKNOWN)
  ResponseAction Run() override;
};

class OnevnSyncSaveBookmarksBaseOrderFunction
    : public UIThreadExtensionFunction {
  ~OnevnSyncSaveBookmarksBaseOrderFunction() override {}
  DECLARE_EXTENSION_FUNCTION("onevnSync.saveBookmarksBaseOrder", UNKNOWN)
  ResponseAction Run() override;
};

class OnevnSyncSaveBookmarkOrderFunction : public UIThreadExtensionFunction {
  ~OnevnSyncSaveBookmarkOrderFunction() override {}
  DECLARE_EXTENSION_FUNCTION("onevnSync.saveBookmarkOrder", UNKNOWN)
  ResponseAction Run() override;
};

class OnevnSyncSyncWordsPreparedFunction : public UIThreadExtensionFunction {
  ~OnevnSyncSyncWordsPreparedFunction() override {}
  DECLARE_EXTENSION_FUNCTION("onevnSync.syncWordsPrepared", UNKNOWN)
  ResponseAction Run() override;
};

class OnevnSyncExtensionInitializedFunction
    : public UIThreadExtensionFunction {
  ~OnevnSyncExtensionInitializedFunction() override {}
  DECLARE_EXTENSION_FUNCTION("onevnSync.extensionInitialized", UNKNOWN)
  ResponseAction Run() override;
};

}   // namespace api
}   // namespace extensions

#endif    // ONEVN_BROWSER_EXTENSIONS_API_ONEVN_SYNC_API_H_
