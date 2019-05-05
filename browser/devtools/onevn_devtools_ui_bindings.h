/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_DEVTOOLS_ONEVN_DEVTOOLS_UI_BINDINGS_H_
#define ONEVN_BROWSER_DEVTOOLS_ONEVN_DEVTOOLS_UI_BINDINGS_H_

#include "chrome/browser/devtools/devtools_ui_bindings.h"

class OnevnDevToolsUIBindings : public DevToolsUIBindings {
 public:
  using DevToolsUIBindings::DevToolsUIBindings;

 private:
  FRIEND_TEST_ALL_PREFIXES(OnevnDevToolsUIBindingsBrowserTest, ThemeTest);

  // DevToolsUIBindings overrides:
  void GetPreferences(const DispatchCallback& callback) override;

  DISALLOW_COPY_AND_ASSIGN(OnevnDevToolsUIBindings);
};

#endif  // ONEVN_BROWSER_DEVTOOLS_ONEVN_DEVTOOLS_UI_BINDINGS_H_
