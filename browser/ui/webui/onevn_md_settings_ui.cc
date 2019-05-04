/* Copyright (c) 2019 The OneVN Authors
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/ui/webui/onevn_md_settings_ui.h"

#include <string>
#include "base/command_line.h"
#include "onevn/browser/extensions/onevn_component_loader.h"
#include "onevn/browser/resources/settings/grit/onevn_settings_resources.h"
#include "onevn/browser/resources/settings/grit/onevn_settings_resources_map.h"
#include "onevn/browser/ui/webui/settings/onevn_default_extensions_handler.h"
#include "onevn/browser/ui/webui/settings/onevn_privacy_handler.h"
#include "onevn/browser/ui/webui/settings/default_onevn_shields_handler.h"
#include "onevn/browser/version_info.h"
#include "onevn/common/onevn_switches.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/webui/settings/metrics_reporting_handler.h"
#include "content/public/browser/web_ui_data_source.h"

#if defined(OS_MACOSX)
#include "onevn/browser/ui/webui/settings/onevn_relaunch_handler_mac.h"
#endif

OneVNMdSettingsUI::OneVNMdSettingsUI(content::WebUI* web_ui,
                                     const std::string& host)
    : MdSettingsUI(web_ui) {
  web_ui->AddMessageHandler(
    std::make_unique<settings::MetricsReportingHandler>());
  web_ui->AddMessageHandler(std::make_unique<OneVNPrivacyHandler>());
  web_ui->AddMessageHandler(std::make_unique<DefaultOneVNShieldsHandler>());
  web_ui->AddMessageHandler(std::make_unique<OneVNDefaultExtensionsHandler>());
#if defined(OS_MACOSX)
  // Use sparkle's relaunch api for browser relaunch on update.
  web_ui->AddMessageHandler(std::make_unique<OneVNRelaunchHandler>());
#endif
}

OneVNMdSettingsUI::~OneVNMdSettingsUI() {
}

// static
void OneVNMdSettingsUI::AddResources(content::WebUIDataSource* html_source,
                                Profile* profile) {
  for (size_t i = 0; i < kOneVNSettingsResourcesSize; ++i) {
    html_source->AddResourcePath(kOneVNSettingsResources[i].name,
                                 kOneVNSettingsResources[i].value);
  }

  html_source->AddBoolean("isPdfjsDisabled",
                          extensions::OneVNComponentLoader::IsPdfjsDisabled());
  const base::CommandLine& command_line =
      *base::CommandLine::ForCurrentProcess();
  html_source->AddBoolean("isSyncDisabled",
                          command_line.HasSwitch(switches::kDisableOneVNSync));
  html_source->AddString("onevnProductVersion",
    version_info::GetOneVNVersionWithoutChromiumMajorVersion());
}
