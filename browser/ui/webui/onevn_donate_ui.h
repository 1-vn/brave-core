// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ONEVN_BROWSER_UI_WEBUI_ONEVN_DONATE_UI_H_
#define ONEVN_BROWSER_UI_WEBUI_ONEVN_DONATE_UI_H_

#include "base/macros.h"
#include "chrome/browser/ui/webui/constrained_web_dialog_ui.h"

class OnevnDonateUI : public ConstrainedWebDialogUI {
 public:
  OnevnDonateUI(content::WebUI* web_ui, const std::string& host);
  ~OnevnDonateUI() override;

 private:
  DISALLOW_COPY_AND_ASSIGN(OnevnDonateUI);
};

#endif
