/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_UI_WEBUI_ONEVN_WEBUI_SOURCE_H_
#define ONEVN_BROWSER_UI_WEBUI_ONEVN_WEBUI_SOURCE_H_

#include <string>

namespace content {
class WebUIDataSource;
class WebUI;
}

void CustomizeWebUIHTMLSource(const std::string &name, content::WebUIDataSource* source);

#endif  // ONEVN_BROWSER_UI_WEBUI_ONEVN_WEBUI_SOURCE_H_
