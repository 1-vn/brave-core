/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/extensions/onevn_component_loader.h"
#include "onevn/browser/extensions/onevn_extension_functional_test.h"
#include "onevn/common/onevn_switches.h"
#include "onevn/common/pref_names.h"
#include "onevn/common/extensions/extension_constants.h"
#include "chrome/browser/extensions/extension_service.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/common/pref_names.h"
#include "components/prefs/pref_service.h"
#include "content/public/test/browser_test_utils.h"
#include "testing/gtest/include/gtest/gtest.h"

using extensions::OneVNComponentLoader;

class OneVNComponentLoaderTest : public extensions::ExtensionFunctionalTest,
  public OneVNComponentLoader::TestingCallbacks {
 public:
  OneVNComponentLoaderTest() : pdf_extension_action_(TestingCallbacks::NONE) {}
  ~OneVNComponentLoaderTest() override = default;

 protected:
  void SetUpOnMainThread() override {
    extensions::ExtensionService* service =
      extensions::ExtensionSystem::Get(profile())->extension_service();
    DCHECK(service);
    OneVNComponentLoader* loader =
      static_cast<OneVNComponentLoader*>(service->component_loader());
    loader->set_testing_callbacks(this);
  }

  // OneVNComponentLoader::TestingCallbacks
  void OnPdfExtensionAction(
      TestingCallbacks::PdfExtensionAction action) override {
    pdf_extension_action_ = action;
  }

  TestingCallbacks::PdfExtensionAction pdf_extension_action() {
    return pdf_extension_action_;
  }

 private:
  TestingCallbacks::PdfExtensionAction pdf_extension_action_;
};

class OneVNPDFExtensionTest : public OneVNComponentLoaderTest {
 public:
  OneVNPDFExtensionTest() {}
  ~OneVNPDFExtensionTest() override = default;

  void SetDownloadPDFs(bool value) {
    DCHECK(browser());
    profile()->GetPrefs()->SetBoolean(prefs::kPluginsAlwaysOpenPdfExternally,
                                      value);
  }
};

IN_PROC_BROWSER_TEST_F(OneVNPDFExtensionTest, ToggleDownloadPDFs) {
  // Set preference to always download PDFs.
  SetDownloadPDFs(true);
  EXPECT_EQ(TestingCallbacks::WILL_REMOVE, pdf_extension_action());

  // Toggle the preference to view PDFs in the browser.
  SetDownloadPDFs(false);
  EXPECT_EQ(TestingCallbacks::WILL_ADD, pdf_extension_action());
}

class OneVNPDFExtensionDisabledTest : public OneVNPDFExtensionTest {
 public:
  OneVNPDFExtensionDisabledTest() = default;
  ~OneVNPDFExtensionDisabledTest() override = default;

 protected:
  void SetUpCommandLine(base::CommandLine* command_line) override {
    ExtensionFunctionalTest::SetUpCommandLine(command_line);
    // Disable loading of our PDF extension.
    command_line->AppendSwitch(switches::kDisablePDFJSExtension);
  }
};

IN_PROC_BROWSER_TEST_F(OneVNPDFExtensionDisabledTest, ToggleDownloadPDFs) {
  // Set preference to always download PDFs.
  SetDownloadPDFs(true);
  EXPECT_EQ(TestingCallbacks::WILL_REMOVE, pdf_extension_action());

  // Toggle the preference to view PDFs in the browser.
  SetDownloadPDFs(false);
  EXPECT_EQ(TestingCallbacks::WILL_REMOVE, pdf_extension_action());
}
