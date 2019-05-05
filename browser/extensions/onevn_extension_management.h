/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_EXTENSIONS_ONEVN_EXTENSION_MANAGEMENT_H_
#define ONEVN_BROWSER_EXTENSIONS_ONEVN_EXTENSION_MANAGEMENT_H_

#include "base/scoped_observer.h"
#include "chrome/browser/extensions/extension_management.h"
#include "extensions/browser/extension_registry_observer.h"

namespace extensions {

class ExtensionRegistry;

class OnevnExtensionManagement : public ExtensionManagement,
                                 public ExtensionRegistryObserver {
 public:
  explicit OnevnExtensionManagement(Profile* profile);
  ~OnevnExtensionManagement() override;

 private:
  void RegisterOnevnExtensions();

  // ExtensionRegistryObserver implementation.
  void OnExtensionLoaded(
      content::BrowserContext* browser_context,
      const Extension* extension) override;
  void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const Extension* extension,
      UnloadedExtensionReason reason) override;

  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver>
    extension_registry_observer_;

  DISALLOW_COPY_AND_ASSIGN(OnevnExtensionManagement);
};

}  // namespace extensions

#endif  // ONEVN_BROWSER_EXTENSIONS_ONEVN_EXTENSION_MANAGEMENT_H_
