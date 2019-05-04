/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/extensions/onevn_component_extension.h"

#include <string>

#include "base/bind.h"
#include "base/bind_helpers.h"
#include "base/callback.h"
#include "onevn/browser/component_updater/onevn_component_installer.h"
#include "chrome/browser/browser_process.h"

void ComponentsUI::OnDemandUpdate(
    component_updater::ComponentUpdateService* cus,
    const std::string& component_id) {
  cus->GetOnDemandUpdater().OnDemandUpdate(
      component_id, component_updater::OnDemandUpdater::Priority::FOREGROUND,
      component_updater::Callback());
}

OneVNComponentExtension::OneVNComponentExtension() {
}

OneVNComponentExtension::~OneVNComponentExtension() {
}

void OneVNComponentExtension::Register(
    const std::string& component_name,
    const std::string& component_id,
    const std::string& component_base64_public_key) {
  component_name_ = component_name;
  component_id_ = component_id;
  component_base64_public_key_ = component_base64_public_key;

  base::Closure registered_callback =
      base::Bind(&OneVNComponentExtension::OnComponentRegistered,
                 base::Unretained(this), component_id_);
  ReadyCallback ready_callback =
      base::Bind(&OneVNComponentExtension::OnComponentReady,
                 base::Unretained(this), component_id_);
  onevn::RegisterComponent(g_browser_process->component_updater(),
                           component_name_, component_base64_public_key_,
                           registered_callback, ready_callback);
}

// static
bool OneVNComponentExtension::Unregister(const std::string& component_id) {
  return g_browser_process->component_updater()->UnregisterComponent(
      component_id);
}

void OneVNComponentExtension::OnComponentRegistered(const std::string& component_id) {
  OnDemandUpdate(g_browser_process->component_updater(), component_id);
}

void OneVNComponentExtension::OnComponentReady(
    const std::string& component_id,
    const base::FilePath& install_dir,
    const std::string& manifest) {
}
