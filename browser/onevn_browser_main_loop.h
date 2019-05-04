/* Copyright 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_ONEVN_BROWSER_MAIN_LOOP_H_
#define ONEVN_BROWSER_ONEVN_BROWSER_MAIN_LOOP_H_

#include "base/macros.h"
#include "content/browser/browser_main_loop.h"

namespace onevn {

class OneVNBrowserMainLoop : public content::BrowserMainLoop {
 public:
  using BrowserMainLoop::BrowserMainLoop;
  ~OneVNBrowserMainLoop() override = default;

  void PreShutdown() override;

 private:
  DISALLOW_COPY_AND_ASSIGN(OneVNBrowserMainLoop);
};

}  // namespace onevn

#endif  // ONEVN_BROWSER_ONEVN_BROWSER_MAIN_LOOP_H_
