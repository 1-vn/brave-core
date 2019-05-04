/* Copyright 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_EXTENSIONS_API_ONEVN_SYNC_API_H_
#define ONEVN_BROWSER_EXTENSIONS_API_ONEVN_SYNC_API_H_

#include "extensions/browser/extension_function.h"

namespace extensions {
namespace api {

class OneVNSyncGetInitDataFunction : public UIThreadExtensionFunction {
  ~OneVNSyncGetInitDataFunction() override {}
  DECLARE_EXTENSION_FUNCTION("onevnSync.getInitData", UNKNOWN)
  ResponseAction Run() override;
};

class OneVNSyncSyncSetupErrorFunction : public UIThreadExtensionFunction {
  ~OneVNSyncSyncSetupErrorFunction() override {}
  DECLARE_EXTENSION_FUNCTION("onevnSync.syncSetupError", UNKNOWN)
  ResponseAction Run() override;
};

class OneVNSyncSyncDebugFunction : public UIThreadExtensionFunction {
  ~OneVNSyncSyncDebugFunction() override {}
  DECLARE_EXTENSION_FUNCTION("onevnSync.syncDebug", UNKNOWN)
  ResponseAction Run() override;
};

class OneVNSyncSaveInitDataFunction : public UIThreadExtensionFunction {
  ~OneVNSyncSaveInitDataFunction() override {}
  DECLARE_EXTENSION_FUNCTION("onevnSync.saveInitData", UNKNOWN)
  ResponseAction Run() override;
};

class OneVNSyncSyncReadyFunction : public UIThreadExtensionFunction {
  ~OneVNSyncSyncReadyFunction() override {}
  DECLARE_EXTENSION_FUNCTION("onevnSync.syncReady", UNKNOWN)
  ResponseAction Run() override;
};

class OneVNSyncGetExistingObjectsFunction : public UIThreadExtensionFunction {
  ~OneVNSyncGetExistingObjectsFunction() override {}
  DECLARE_EXTENSION_FUNCTION("onevnSync.getExistingObjects", UNKNOWN)
  ResponseAction Run() override;
};

class OneVNSyncResolvedSyncRecordsFunction : public UIThreadExtensionFunction {
  ~OneVNSyncResolvedSyncRecordsFunction() override {}
  DECLARE_EXTENSION_FUNCTION("onevnSync.resolvedSyncRecords", UNKNOWN)
  ResponseAction Run() override;
};

class OneVNSyncSaveBookmarksBaseOrderFunction
    : public UIThreadExtensionFunction {
  ~OneVNSyncSaveBookmarksBaseOrderFunction() override {}
  DECLARE_EXTENSION_FUNCTION("onevnSync.saveBookmarksBaseOrder", UNKNOWN)
  ResponseAction Run() override;
};

class OneVNSyncSaveBookmarkOrderFunction : public UIThreadExtensionFunction {
  ~OneVNSyncSaveBookmarkOrderFunction() override {}
  DECLARE_EXTENSION_FUNCTION("onevnSync.saveBookmarkOrder", UNKNOWN)
  ResponseAction Run() override;
};

class OneVNSyncSyncWordsPreparedFunction : public UIThreadExtensionFunction {
  ~OneVNSyncSyncWordsPreparedFunction() override {}
  DECLARE_EXTENSION_FUNCTION("onevnSync.syncWordsPrepared", UNKNOWN)
  ResponseAction Run() override;
};

class OneVNSyncExtensionInitializedFunction
    : public UIThreadExtensionFunction {
  ~OneVNSyncExtensionInitializedFunction() override {}
  DECLARE_EXTENSION_FUNCTION("onevnSync.extensionInitialized", UNKNOWN)
  ResponseAction Run() override;
};

}   // namespace api
}   // namespace extensions

#endif    // ONEVN_BROWSER_EXTENSIONS_API_ONEVN_SYNC_API_H_
