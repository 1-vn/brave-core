/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_UI_WEBUI_ONEVN_REWARDS_UI_H_
#define ONEVN_BROWSER_UI_WEBUI_ONEVN_REWARDS_UI_H_

#include "onevn/browser/ui/webui/basic_ui.h"

class OnevnRewardsUI : public BasicUI {
 public:
  OnevnRewardsUI(content::WebUI* web_ui, const std::string& host);
  ~OnevnRewardsUI() override;

 private:
  DISALLOW_COPY_AND_ASSIGN(OnevnRewardsUI);
};

#endif  // ONEVN_BROWSER_UI_WEBUI_ONEVN_REWARDS_UI_H_
