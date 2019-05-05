// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/installer/mini_installer/mini_installer.h"

#include "testing/gtest/include/gtest/gtest.h"

namespace mini_installer {

class OnevnMiniInstallerTest: public testing::Test {
 public:
  OnevnMiniInstallerTest() {
  }
  ~OnevnMiniInstallerTest() override {}
};


TEST_F(OnevnMiniInstallerTest, HasNoReferralCode) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"OnevnBrowserSetup.exe", referral_code));
}

TEST_F(OnevnMiniInstallerTest, HasStandardReferralCode) {
  ReferralCodeString referral_code;
  EXPECT_TRUE(ParseReferralCode(L"OnevnBrowserSetup-FOO123.exe", referral_code));
  EXPECT_STREQ(referral_code.get(), L"FOO123");
}

TEST_F(OnevnMiniInstallerTest, HasStandardReferralCodeWithPath) {
  ReferralCodeString referral_code;
  EXPECT_TRUE(ParseReferralCode(L"c:/foo/bar/OnevnBrowserSetup-FOO123.exe", referral_code));
  EXPECT_STREQ(referral_code.get(), L"FOO123");
}

TEST_F(OnevnMiniInstallerTest, HasStandardReferralCodeWithDeduplicatingSuffix) {
  ReferralCodeString referral_code;
  EXPECT_TRUE(ParseReferralCode(L"c:/foo/bar/OnevnBrowserSetup-FOO123 (1).exe", referral_code));
  EXPECT_STREQ(referral_code.get(), L"FOO123");
}

TEST_F(OnevnMiniInstallerTest, HasStandardReferralCodeWithDeduplicatingSuffixNoSpaces) {
  ReferralCodeString referral_code;
  EXPECT_TRUE(ParseReferralCode(L"c:/foo/bar/OnevnBrowserSetup-FOO123(1).exe", referral_code));
  EXPECT_STREQ(referral_code.get(), L"FOO123");
}

TEST_F(OnevnMiniInstallerTest, HasStandardReferralCodeWithDeduplicatingSuffixExtraSpaces) {
  ReferralCodeString referral_code;
  EXPECT_TRUE(ParseReferralCode(L"c:/foo/bar/OnevnBrowserSetup-FOO123   (1).exe", referral_code));
  EXPECT_STREQ(referral_code.get(), L"FOO123");
}

TEST_F(OnevnMiniInstallerTest, HasInvalidStandardReferralCodeReversed) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"OnevnBrowserSetup-123FOO.exe", referral_code));
}

TEST_F(OnevnMiniInstallerTest, HasInvalidStandardReferralCodeNoDigits) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"OnevnBrowserSetup-FOO.exe", referral_code));
}

TEST_F(OnevnMiniInstallerTest, HasInvalidStandardReferralCodeNoLetters) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"OnevnBrowserSetup-123.exe", referral_code));
}

TEST_F(OnevnMiniInstallerTest, HasInvalidStandardReferralCodeTooManyDigits) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"OnevnBrowserSetup-FOO1234.exe", referral_code));
}

TEST_F(OnevnMiniInstallerTest, HasInvalidStandardReferralCodeTooFewDigits) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"OnevnBrowserSetup-FOO12.exe", referral_code));
}

TEST_F(OnevnMiniInstallerTest, HasInvalidStandardReferralCodeTooManyLetters) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"OnevnBrowserSetup-FOOO123.exe", referral_code));
}

TEST_F(OnevnMiniInstallerTest, HasInvalidStandardReferralCodeTooFewLetters) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"OnevnBrowserSetup-FO123.exe", referral_code));
}

TEST_F(OnevnMiniInstallerTest, HasExtendedReferralCode) {
  ReferralCodeString referral_code;
  EXPECT_TRUE(ParseReferralCode(L"OnevnBrowserSetup-extended-code.exe", referral_code));
  EXPECT_STREQ(referral_code.get(), L"extended-code");
}

TEST_F(OnevnMiniInstallerTest, HasInvalidExtendedReferralCodeNonAlphabeticCharacters) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"OnevnBrowserSetup-invalid-extended-c0de.exe", referral_code));
}

TEST_F(OnevnMiniInstallerTest, HasInvalidExtendedReferralCodeTooFewWords) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"OnevnBrowserSetup-invalidextendedcode.exe", referral_code));
}

}  // namespace mini_installer
