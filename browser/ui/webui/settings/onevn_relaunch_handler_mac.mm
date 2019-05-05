/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/ui/webui/settings/onevn_relaunch_handler_mac.h"

#include "base/bind.h"
#import "onevn/browser/mac/sparkle_glue.h"

void OnevnRelaunchHandler::RegisterMessages() {
  web_ui()->RegisterMessageCallback(
      "relaunchOnMac",
      base::BindRepeating(&OnevnRelaunchHandler::Relaunch,
                          base::Unretained(this)));
}

void OnevnRelaunchHandler::Relaunch(const base::ListValue* args) {
  [[SparkleGlue sharedSparkleGlue] relaunch];
}
