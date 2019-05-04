/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_TEST_BASE_ONEVN_TEST_LAUNCHER_H_
#define ONEVN_TEST_BASE_ONEVN_TEST_LAUNCHER_H_

#include "chrome/test/base/chrome_test_launcher.h"
#include "base/macros.h"

class OneVNTestLauncherDelegate : public ChromeTestLauncherDelegate {
 public:
  // Does not take ownership of ChromeTestSuiteRunner.
  explicit OneVNTestLauncherDelegate(ChromeTestSuiteRunner* runner);
  ~OneVNTestLauncherDelegate() override;

 private:
  // ChromeLauncherDelegate:
  content::ContentMainDelegate* CreateContentMainDelegate() override;

  DISALLOW_COPY_AND_ASSIGN(OneVNTestLauncherDelegate);
};

#endif  // ONEVN_TEST_BASE_ONEVN_TEST_LAUNCHER_H_
