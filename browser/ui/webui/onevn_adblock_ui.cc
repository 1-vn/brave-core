/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/ui/webui/onevn_adblock_ui.h"

#include "onevn/browser/onevn_browser_process_impl.h"
#include "onevn/common/pref_names.h"
#include "onevn/common/webui_url_constants.h"
#include "onevn/components/onevn_adblock/resources/grit/onevn_adblock_generated_map.h"
#include "onevn/components/onevn_shields/browser/ad_block_custom_filters_service.h"
#include "onevn/components/onevn_shields/browser/ad_block_regional_service_manager.h"
#include "chrome/browser/profiles/profile.h"
#include "components/grit/onevn_components_resources.h"
#include "components/prefs/pref_change_registrar.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/render_frame_host.h"
#include "content/public/browser/render_view_host.h"
#include "content/public/browser/web_ui_data_source.h"
#include "content/public/browser/web_ui_message_handler.h"

namespace {

class AdblockDOMHandler : public content::WebUIMessageHandler {
 public:
  AdblockDOMHandler();
  ~AdblockDOMHandler() override;

  // WebUIMessageHandler implementation.
  void RegisterMessages() override;

 private:
  void HandleEnableFilterList(const base::ListValue* args);
  void HandleGetCustomFilters(const base::ListValue* args);
  void HandleGetRegionalLists(const base::ListValue* args);
  void HandleUpdateCustomFilters(const base::ListValue* args);

  DISALLOW_COPY_AND_ASSIGN(AdblockDOMHandler);
};

AdblockDOMHandler::AdblockDOMHandler() {}

AdblockDOMHandler::~AdblockDOMHandler() {}

void AdblockDOMHandler::RegisterMessages() {
  web_ui()->RegisterMessageCallback(
      "onevn_adblock.enableFilterList",
      base::BindRepeating(&AdblockDOMHandler::HandleEnableFilterList,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "onevn_adblock.getCustomFilters",
      base::BindRepeating(&AdblockDOMHandler::HandleGetCustomFilters,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "onevn_adblock.getRegionalLists",
      base::BindRepeating(&AdblockDOMHandler::HandleGetRegionalLists,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "onevn_adblock.updateCustomFilters",
      base::BindRepeating(&AdblockDOMHandler::HandleUpdateCustomFilters,
                          base::Unretained(this)));
}

void AdblockDOMHandler::HandleEnableFilterList(const base::ListValue* args) {
  DCHECK_EQ(args->GetSize(), 2U);
  std::string uuid;
  if (!args->GetString(0, &uuid))
    return;
  bool enabled;
  if (!args->GetBoolean(1, &enabled))
    return;
  g_onevn_browser_process->ad_block_regional_service_manager()
      ->EnableFilterList(uuid, enabled);
}

void AdblockDOMHandler::HandleGetCustomFilters(const base::ListValue* args) {
  DCHECK_EQ(args->GetSize(), 0U);
  const std::string custom_filters =
      g_onevn_browser_process->ad_block_custom_filters_service()
          ->GetCustomFilters();
  if (!web_ui()->CanCallJavascript())
    return;
  web_ui()->CallJavascriptFunctionUnsafe("onevn_adblock.onGetCustomFilters",
                                         base::Value(custom_filters));
}

void AdblockDOMHandler::HandleGetRegionalLists(const base::ListValue* args) {
  DCHECK_EQ(args->GetSize(), 0U);
  if (!web_ui()->CanCallJavascript())
    return;
  std::unique_ptr<base::ListValue> regional_lists =
      g_onevn_browser_process->ad_block_regional_service_manager()
          ->GetRegionalLists();
  web_ui()->CallJavascriptFunctionUnsafe("onevn_adblock.onGetRegionalLists",
                                         *regional_lists);
}

void AdblockDOMHandler::HandleUpdateCustomFilters(const base::ListValue* args) {
  DCHECK_EQ(args->GetSize(), 1U);
  std::string custom_filters;
  if (!args->GetString(0, &custom_filters))
    return;

  g_onevn_browser_process->ad_block_custom_filters_service()
      ->UpdateCustomFilters(custom_filters);
}

}  // namespace

OneVNAdblockUI::OneVNAdblockUI(content::WebUI* web_ui, const std::string& name)
    : BasicUI(web_ui, name, kOneVNAdblockGenerated,
        kOneVNAdblockGeneratedSize, IDR_ONEVN_ADBLOCK_HTML) {
  Profile* profile = Profile::FromWebUI(web_ui);
  PrefService* prefs = profile->GetPrefs();
  pref_change_registrar_ = std::make_unique<PrefChangeRegistrar>();
  pref_change_registrar_->Init(prefs);
  pref_change_registrar_->Add(kAdsBlocked,
    base::Bind(&OneVNAdblockUI::OnPreferenceChanged, base::Unretained(this)));
  web_ui->AddMessageHandler(std::make_unique<AdblockDOMHandler>());
}

OneVNAdblockUI::~OneVNAdblockUI() {
}

void OneVNAdblockUI::CustomizeWebUIProperties(
    content::RenderViewHost* render_view_host) {
  DCHECK(IsSafeToSetWebUIProperties());
  Profile* profile = Profile::FromWebUI(web_ui());
  PrefService* prefs = profile->GetPrefs();
  if (render_view_host) {
    render_view_host->SetWebUIProperty(
        "adsBlockedStat", std::to_string(prefs->GetUint64(kAdsBlocked)));
  }
}

void OneVNAdblockUI::UpdateWebUIProperties() {
  if (IsSafeToSetWebUIProperties()) {
    CustomizeWebUIProperties(GetRenderViewHost());
    web_ui()->CallJavascriptFunctionUnsafe("onevn_adblock.statsUpdated");
  }
}

void OneVNAdblockUI::OnPreferenceChanged() {
  UpdateWebUIProperties();
}
