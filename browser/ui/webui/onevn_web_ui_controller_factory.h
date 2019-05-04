/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_UI_WEBUI_CHROME_WEB_UI_CONTROLLER_FACTORY_H_
#define ONEVN_BROWSER_UI_WEBUI_CHROME_WEB_UI_CONTROLLER_FACTORY_H_

#include "chrome/browser/ui/webui/chrome_web_ui_controller_factory.h"

namespace base {
class RefCountedMemory;
}

class OneVNWebUIControllerFactory : public ChromeWebUIControllerFactory {
 public:
  content::WebUI::TypeID GetWebUIType(content::BrowserContext* browser_context,
                                      const GURL& url) const override;
  std::unique_ptr<content::WebUIController> CreateWebUIControllerForURL(
      content::WebUI* web_ui,
      const GURL& url) const override;

  static OneVNWebUIControllerFactory* GetInstance();

 protected:
  friend struct base::DefaultSingletonTraits<OneVNWebUIControllerFactory>;

  OneVNWebUIControllerFactory();
  ~OneVNWebUIControllerFactory() override;

 private:
  DISALLOW_COPY_AND_ASSIGN(OneVNWebUIControllerFactory);
};

#endif  // ONEVN_BROWSER_UI_WEBUI_CHROME_WEB_UI_CONTROLLER_FACTORY_H_
