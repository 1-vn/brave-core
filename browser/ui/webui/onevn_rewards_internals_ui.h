/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_UI_WEBUI_ONEVN_REWARDS_INTERNALS_UI_H_
#define ONEVN_BROWSER_UI_WEBUI_ONEVN_REWARDS_INTERNALS_UI_H_

#include <memory>
#include <string>

#include "base/memory/weak_ptr.h"
#include "onevn/browser/ui/webui/basic_ui.h"

namespace onevn_rewards {
struct RewardsInternalsInfo;
}  // namespace onevn_rewards

class OneVNRewardsInternalsUI : public BasicUI {
 public:
  OneVNRewardsInternalsUI(content::WebUI* web_ui, const std::string& host);
  ~OneVNRewardsInternalsUI() override;

 private:
  DISALLOW_COPY_AND_ASSIGN(OneVNRewardsInternalsUI);
};

#endif  // ONEVN_BROWSER_UI_WEBUI_ONEVN_REWARDS_INTERNALS_UI_H_
