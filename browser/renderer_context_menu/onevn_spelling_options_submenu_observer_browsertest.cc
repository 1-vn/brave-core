/* Copyright 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/renderer_context_menu/onevn_spelling_options_submenu_observer.h"

#include <memory>

#include "base/values.h"
#include "onevn/browser/renderer_context_menu/onevn_mock_render_view_context_menu.h"
#include "onevn/common/pref_names.h"
#include "chrome/app/chrome_command_ids.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "components/language/core/browser/pref_names.h"
#include "components/prefs/pref_service.h"
#include "components/spellcheck/browser/pref_names.h"
#include "content/public/common/context_menu_params.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace {

// A test class used in this file. This test should be a browser test because it
// accesses resources.
class OnevnSpellingOptionsSubMenuObserverTest : public InProcessBrowserTest {
 public:
  OnevnSpellingOptionsSubMenuObserverTest() {}
  ~OnevnSpellingOptionsSubMenuObserverTest() override {}

  void Clear() {
    if (menu_)
      menu_->SetObserver(nullptr);
    observer_.reset();
    menu_.reset();
  }

  void Reset(bool incognito = false,
             OnevnSpellingOptionsSubMenuObserver::GtestMode gtest_mode =
                 OnevnSpellingOptionsSubMenuObserver::GTEST_MODE_NORMAL) {
    Clear();
    menu_.reset(new OnevnMockRenderViewContextMenu(
        incognito ? browser()->profile()->GetOffTheRecordProfile()
                  : browser()->profile()));
    std::unique_ptr<OnevnSpellingOptionsSubMenuObserver> observer =
        std::make_unique<OnevnSpellingOptionsSubMenuObserver>(menu_.get(),
                                                              menu_.get(), 1);
    observer->SetGtestMode(gtest_mode);
    observer_ = std::move(observer);
    menu_->SetObserver(observer_.get());
    // Uncomment to print the menu to standard output for each test.
    // menu_->EnablePrintMenu();
  }

  void SetUpOnMainThread() override {
    InProcessBrowserTest::SetUpOnMainThread();
  }

  void TearDownOnMainThread() override {
    Clear();
  }

  void InitMenu(bool enable_spellcheck,
                const std::string& accept_languages,
                const std::vector<std::string>& dictionaries) {
    menu()->GetPrefs()->SetBoolean(spellcheck::prefs::kSpellCheckEnable,
                                   enable_spellcheck);
    menu()->GetPrefs()->SetString(language::prefs::kAcceptLanguages,
                                  accept_languages);
    base::ListValue dictionaries_value;
    dictionaries_value.AppendStrings(dictionaries);
    menu()->GetPrefs()->Set(spellcheck::prefs::kSpellCheckDictionaries,
                            dictionaries_value);
    observer()->InitMenu(content::ContextMenuParams());
  }

  void CheckExpected() {
    for (size_t i = 0; i < menu()->GetMenuSize(); ++i) {
      OnevnMockRenderViewContextMenu::MockMenuItem item;
      menu()->GetMenuItem(i, &item);
      EXPECT_NE(IDC_CONTENT_CONTEXT_SPELLING_TOGGLE, item.command_id);
    }
    // Check that the menu doesn't end with a separator.
    OnevnMockRenderViewContextMenu::MockMenuItem item;
    menu()->GetMenuItem(menu()->GetMenuSize() - 1, &item);
    EXPECT_NE(-1, item.command_id);  // -1 == separator
  }

  OnevnMockRenderViewContextMenu* menu() { return menu_.get(); }
  SpellingOptionsSubMenuObserver* observer() { return observer_.get(); }

 private:
  std::unique_ptr<OnevnMockRenderViewContextMenu> menu_;
  std::unique_ptr<SpellingOptionsSubMenuObserver> observer_;

  DISALLOW_COPY_AND_ASSIGN(OnevnSpellingOptionsSubMenuObserverTest);
};

// Tests that "Ask Onevn for suggestions" isn't shown in the menu and the menu
// doesn't end with a separator.

IN_PROC_BROWSER_TEST_F(OnevnSpellingOptionsSubMenuObserverTest,
                       CheckAskOnevnNotShown) {
  // Test with spellcheck enabled.
  Reset();
  InitMenu(true, "en-US", std::vector<std::string>(1, "en-US"));
  menu()->PrintMenu("Test with spellcheck enabled.");
  CheckExpected();

  // Test with spellcheck disabled.
  Reset();
  InitMenu(false, "en-US", std::vector<std::string>(1, "en-US"));
  menu()->PrintMenu("Test with spellcheck disabled.");
  CheckExpected();

  // Test with no dictionaries.
  Reset();
  InitMenu(false, "en-US", std::vector<std::string>());
  menu()->PrintMenu("Test with no dictionaries.");
  CheckExpected();

  // Test empty submenu.
  Reset(false, OnevnSpellingOptionsSubMenuObserver::GTEST_MODE_EMPTY_SUBMENU);
  InitMenu(false, "en-US", std::vector<std::string>());
  menu()->PrintMenu("Test empty submenu.");
  EXPECT_EQ(1U, menu()->GetMenuSize());
  OnevnMockRenderViewContextMenu::MockMenuItem item;
  menu()->GetMenuItem(0, &item);
  EXPECT_EQ(IDC_SPELLCHECK_MENU, item.command_id);
  EXPECT_FALSE(item.enabled);
}

IN_PROC_BROWSER_TEST_F(OnevnSpellingOptionsSubMenuObserverTest,
                       CheckAskOnevnNotShownIncognito) {
  // Test with spellcheck enabled.
  Reset(true);
  InitMenu(true, "en-US", std::vector<std::string>(1, "en-US"));
  menu()->PrintMenu("Test incognito profile with spellcheck enabled.");
  CheckExpected();

  // Test with spellcheck disabled.
  Reset(true);
  InitMenu(false, "en-US", std::vector<std::string>(1, "en-US"));
  menu()->PrintMenu("Test incognito profile with spellcheck disabled.");
  CheckExpected();

  // Test with no dictionaries.
  Reset(true);
  InitMenu(false, "en-US", std::vector<std::string>());
  menu()->PrintMenu("Test incognito profile with no dictionaries.");
  CheckExpected();
}

}  // namespace