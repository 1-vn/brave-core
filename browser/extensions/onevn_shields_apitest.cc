/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/path_service.h"
#include "onevn/common/onevn_paths.h"
#include "chrome/browser/extensions/extension_apitest.h"
#include "extensions/test/result_catcher.h"

namespace extensions {
namespace {

class OnevnShieldsExtensionApiTest : public ExtensionApiTest {
 public:
  void SetUp() override {
    onevn::RegisterPathProvider();
    base::PathService::Get(onevn::DIR_TEST_DATA, &extension_dir_);
    extension_dir_ = extension_dir_.AppendASCII("extensions/api_test");
    ExtensionApiTest::SetUp();
  }
  void TearDown() override {
    ExtensionApiTest::TearDown();
  }
  base::FilePath extension_dir_;
};

IN_PROC_BROWSER_TEST_F(OnevnShieldsExtensionApiTest, OnevnExtensionHasAccess) {
  ResultCatcher catcher;
  const Extension* extension =
    LoadExtension(extension_dir_.AppendASCII("onevnShields"));
  ASSERT_TRUE(extension);
  ASSERT_TRUE(catcher.GetNextResult()) << message_;
}

IN_PROC_BROWSER_TEST_F(OnevnShieldsExtensionApiTest, NotOnevnExtensionHasNoAccess) {
  LOG(ERROR) << "======= This is an intentional fail:";
  ResultCatcher catcher;
  const Extension* extension =
    LoadExtension(extension_dir_.AppendASCII("notOnevnShields"));
  ASSERT_TRUE(extension);
  ASSERT_FALSE(catcher.GetNextResult()) << message_;
}

}  // namespace
}  // extensions
