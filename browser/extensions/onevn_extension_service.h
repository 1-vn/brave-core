/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_EXTENSIONS_ONEVN_EXTENSION_SERVICE_H_
#define ONEVN_BROWSER_EXTENSIONS_ONEVN_EXTENSION_SERVICE_H_

#include "chrome/browser/extensions/extension_service.h"

namespace extensions {

class OnevnExtensionService : public ExtensionService {
 public:
  // Constructor stores pointers to |profile| and |extension_prefs| but
  // ownership remains at caller.
  OnevnExtensionService(Profile* profile,
                        const base::CommandLine* command_line,
                        const base::FilePath& install_directory,
                        ExtensionPrefs* extension_prefs,
                        Blacklist* blacklist,
                        bool autoupdate_enabled,
                        bool extensions_enabled,
                        OneShotEvent* ready);
  ~OnevnExtensionService() override;

  void AddComponentExtension(const Extension* extension) override;

  DISALLOW_COPY_AND_ASSIGN(OnevnExtensionService);
};

}  // namespace extensions

#endif  // ONEVN_BROWSER_EXTENSIONS_ONEVN_EXTENSION_SERVICE_H_
