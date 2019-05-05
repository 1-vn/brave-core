/* Copyright 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/extensions/api/onevn_sync_api.h"

#include <memory>
#include <utility>
#include <vector>

#include "onevn/common/extensions/api/onevn_sync.h"
#include "onevn/components/onevn_sync/client/onevn_sync_client.h"
#include "onevn/components/onevn_sync/onevn_sync_service.h"
#include "onevn/components/onevn_sync/onevn_sync_service_factory.h"
#include "onevn/components/onevn_sync/client/client_ext_impl_data.h"
#include "onevn/components/onevn_sync/values_conv.h"
#include "onevn/components/onevn_sync/jslib_messages.h"
#include "chrome/browser/profiles/profile.h"

using ::onevn_sync::OnevnSyncService;
using ::onevn_sync::OnevnSyncServiceFactory;
using content::BrowserContext;

namespace extensions {
namespace api {

namespace {

OnevnSyncService* GetOnevnSyncService(BrowserContext* browser_context) {
  return OnevnSyncServiceFactory::GetForProfile(
      Profile::FromBrowserContext(browser_context));
}

}  // namespace
ExtensionFunction::ResponseAction OnevnSyncGetInitDataFunction::Run() {
  std::unique_ptr<onevn_sync::GetInitData::Params> params(
      onevn_sync::GetInitData::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  OnevnSyncService* sync_service = GetOnevnSyncService(browser_context());
  DCHECK(sync_service);
  sync_service->GetSyncClient()->sync_message_handler()->OnGetInitData(
      params->sync_version);

  return RespondNow(NoArguments());
}

ExtensionFunction::ResponseAction OnevnSyncSyncSetupErrorFunction::Run() {
  std::unique_ptr<onevn_sync::SyncSetupError::Params> params(
      onevn_sync::SyncSetupError::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  OnevnSyncService* sync_service = GetOnevnSyncService(browser_context());
  DCHECK(sync_service);
  sync_service->GetSyncClient()->sync_message_handler()->OnSyncSetupError(
      params->error);

  return RespondNow(NoArguments());
}

ExtensionFunction::ResponseAction OnevnSyncSyncDebugFunction::Run() {
  std::unique_ptr<onevn_sync::SyncDebug::Params> params(
      onevn_sync::SyncDebug::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  OnevnSyncService* sync_service = GetOnevnSyncService(browser_context());
  DCHECK(sync_service);
  sync_service->GetSyncClient()->sync_message_handler()->OnSyncDebug(
      params->message);

  return RespondNow(NoArguments());
}

ExtensionFunction::ResponseAction OnevnSyncSaveInitDataFunction::Run() {
  std::unique_ptr<onevn_sync::SaveInitData::Params> params(
      onevn_sync::SaveInitData::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  OnevnSyncService* sync_service = GetOnevnSyncService(browser_context());
  DCHECK(sync_service);
  sync_service->GetSyncClient()->sync_message_handler()->OnSaveInitData(
      params->seed ? *params->seed : std::vector<uint8_t>(),
      params->device_id ? *params->device_id : std::vector<uint8_t>());

  return RespondNow(NoArguments());
}

ExtensionFunction::ResponseAction OnevnSyncSyncReadyFunction::Run() {
  OnevnSyncService* sync_service = GetOnevnSyncService(browser_context());
  DCHECK(sync_service);
  sync_service->GetSyncClient()->sync_message_handler()->OnSyncReady();

  return RespondNow(NoArguments());
}

ExtensionFunction::ResponseAction OnevnSyncGetExistingObjectsFunction::Run() {
  std::unique_ptr<onevn_sync::GetExistingObjects::Params> params(
      onevn_sync::GetExistingObjects::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  auto records = std::make_unique<std::vector<::onevn_sync::SyncRecordPtr>>();
  ::onevn_sync::ConvertSyncRecords(params->records, *records.get());

  OnevnSyncService* sync_service = GetOnevnSyncService(browser_context());
  DCHECK(sync_service);
  sync_service->GetSyncClient()->sync_message_handler()->OnGetExistingObjects(
    params->category_name,
    std::move(records),
    base::Time::FromJsTime(params->last_record_timestamp),
    params->is_truncated);

  return RespondNow(NoArguments());
}

ExtensionFunction::ResponseAction OnevnSyncResolvedSyncRecordsFunction::Run() {
  std::unique_ptr<onevn_sync::ResolvedSyncRecords::Params> params(
      onevn_sync::ResolvedSyncRecords::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  auto records = std::make_unique<std::vector<::onevn_sync::SyncRecordPtr>>();
  ::onevn_sync::ConvertSyncRecords(params->records, *records.get());

  OnevnSyncService* sync_service = GetOnevnSyncService(browser_context());
  DCHECK(sync_service);
  sync_service->GetSyncClient()->sync_message_handler()->OnResolvedSyncRecords(
    params->category_name,
    std::move(records));

  return RespondNow(NoArguments());
}

ExtensionFunction::ResponseAction
OnevnSyncSaveBookmarksBaseOrderFunction::Run() {
  std::unique_ptr<onevn_sync::SaveBookmarksBaseOrder::Params> params(
      onevn_sync::SaveBookmarksBaseOrder::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  OnevnSyncService* sync_service = GetOnevnSyncService(browser_context());
  DCHECK(sync_service);
  sync_service->GetSyncClient()->sync_message_handler()
    ->OnSaveBookmarksBaseOrder(params->order);

  return RespondNow(NoArguments());
}

ExtensionFunction::ResponseAction OnevnSyncSaveBookmarkOrderFunction::Run() {
  std::unique_ptr<onevn_sync::SaveBookmarkOrder::Params> params(
      onevn_sync::SaveBookmarkOrder::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  OnevnSyncService* sync_service = GetOnevnSyncService(browser_context());
  DCHECK(sync_service);
  sync_service->GetSyncClient()->sync_message_handler()->OnSaveBookmarkOrder(
      params->object_id, params->order);

  return RespondNow(NoArguments());
}

ExtensionFunction::ResponseAction OnevnSyncSyncWordsPreparedFunction::Run() {
  std::unique_ptr<onevn_sync::SyncWordsPrepared::Params> params(
      onevn_sync::SyncWordsPrepared::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  OnevnSyncService* sync_service = GetOnevnSyncService(browser_context());
  DCHECK(sync_service);
  sync_service->GetSyncClient()->sync_message_handler()
    ->OnSyncWordsPrepared(params->words);

  return RespondNow(NoArguments());
}

ExtensionFunction::ResponseAction OnevnSyncExtensionInitializedFunction::Run() {
  // Also inform sync client extension started
  OnevnSyncService* sync_service = GetOnevnSyncService(browser_context());
  DCHECK(sync_service);
  sync_service->GetSyncClient()->OnExtensionInitialized();

  return RespondNow(NoArguments());
}

}  // namespace api
}  // namespace extensions
