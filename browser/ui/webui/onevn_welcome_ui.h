/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_UI_WEBUI_ONEVN_WELCOME_UI_H_
#define ONEVN_BROWSER_UI_WEBUI_ONEVN_WELCOME_UI_H_

#include "onevn/browser/ui/webui/basic_ui.h"

class OneVNWelcomeUI : public BasicUI {
 public:
  OneVNWelcomeUI(content::WebUI* web_ui, const std::string& host);
  ~OneVNWelcomeUI() override;

 private:
  DISALLOW_COPY_AND_ASSIGN(OneVNWelcomeUI);
};

#endif  // ONEVN_BROWSER_UI_WEBUI_ONEVN_WELCOME_UI_H_
