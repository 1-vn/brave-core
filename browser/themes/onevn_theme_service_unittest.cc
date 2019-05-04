/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/themes/onevn_theme_service.h"

#include "testing/gtest/include/gtest/gtest.h"

TEST(OneVNThemeServiceTest, GetOneVNThemeListTest) {
  OneVNThemeService::is_test_ = true;

  OneVNThemeService::use_system_theme_mode_in_test_ = true;

  base::Value list = OneVNThemeService::GetOneVNThemeList();
  EXPECT_EQ(3UL, list.GetList().size());

  OneVNThemeService::use_system_theme_mode_in_test_ = false;
  list = OneVNThemeService::GetOneVNThemeList();
  EXPECT_EQ(2UL, list.GetList().size());
}
