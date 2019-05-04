/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/test/base/onevn_test_launcher_delegate.h"

#include "onevn/app/onevn_main_delegate.h"

OneVNTestLauncherDelegate::OneVNTestLauncherDelegate(
    ChromeTestSuiteRunner* runner)
    : ChromeTestLauncherDelegate(runner) {}

OneVNTestLauncherDelegate::~OneVNTestLauncherDelegate() = default;

content::ContentMainDelegate*
OneVNTestLauncherDelegate::CreateContentMainDelegate() {
  return new OneVNMainDelegate();
}
