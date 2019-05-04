// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/installer/mini_installer/mini_installer.h"

#include "testing/gtest/include/gtest/gtest.h"

namespace mini_installer {

class OneVNMiniInstallerTest: public testing::Test {
 public:
  OneVNMiniInstallerTest() {
  }
  ~OneVNMiniInstallerTest() override {}
};


TEST_F(OneVNMiniInstallerTest, HasNoReferralCode) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"OneVNBrowserSetup.exe", referral_code));
}

TEST_F(OneVNMiniInstallerTest, HasStandardReferralCode) {
  ReferralCodeString referral_code;
  EXPECT_TRUE(ParseReferralCode(L"OneVNBrowserSetup-FOO123.exe", referral_code));
  EXPECT_STREQ(referral_code.get(), L"FOO123");
}

TEST_F(OneVNMiniInstallerTest, HasStandardReferralCodeWithPath) {
  ReferralCodeString referral_code;
  EXPECT_TRUE(ParseReferralCode(L"c:/foo/bar/OneVNBrowserSetup-FOO123.exe", referral_code));
  EXPECT_STREQ(referral_code.get(), L"FOO123");
}

TEST_F(OneVNMiniInstallerTest, HasStandardReferralCodeWithDeduplicatingSuffix) {
  ReferralCodeString referral_code;
  EXPECT_TRUE(ParseReferralCode(L"c:/foo/bar/OneVNBrowserSetup-FOO123 (1).exe", referral_code));
  EXPECT_STREQ(referral_code.get(), L"FOO123");
}

TEST_F(OneVNMiniInstallerTest, HasStandardReferralCodeWithDeduplicatingSuffixNoSpaces) {
  ReferralCodeString referral_code;
  EXPECT_TRUE(ParseReferralCode(L"c:/foo/bar/OneVNBrowserSetup-FOO123(1).exe", referral_code));
  EXPECT_STREQ(referral_code.get(), L"FOO123");
}

TEST_F(OneVNMiniInstallerTest, HasStandardReferralCodeWithDeduplicatingSuffixExtraSpaces) {
  ReferralCodeString referral_code;
  EXPECT_TRUE(ParseReferralCode(L"c:/foo/bar/OneVNBrowserSetup-FOO123   (1).exe", referral_code));
  EXPECT_STREQ(referral_code.get(), L"FOO123");
}

TEST_F(OneVNMiniInstallerTest, HasInvalidStandardReferralCodeReversed) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"OneVNBrowserSetup-123FOO.exe", referral_code));
}

TEST_F(OneVNMiniInstallerTest, HasInvalidStandardReferralCodeNoDigits) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"OneVNBrowserSetup-FOO.exe", referral_code));
}

TEST_F(OneVNMiniInstallerTest, HasInvalidStandardReferralCodeNoLetters) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"OneVNBrowserSetup-123.exe", referral_code));
}

TEST_F(OneVNMiniInstallerTest, HasInvalidStandardReferralCodeTooManyDigits) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"OneVNBrowserSetup-FOO1234.exe", referral_code));
}

TEST_F(OneVNMiniInstallerTest, HasInvalidStandardReferralCodeTooFewDigits) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"OneVNBrowserSetup-FOO12.exe", referral_code));
}

TEST_F(OneVNMiniInstallerTest, HasInvalidStandardReferralCodeTooManyLetters) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"OneVNBrowserSetup-FOOO123.exe", referral_code));
}

TEST_F(OneVNMiniInstallerTest, HasInvalidStandardReferralCodeTooFewLetters) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"OneVNBrowserSetup-FO123.exe", referral_code));
}

TEST_F(OneVNMiniInstallerTest, HasExtendedReferralCode) {
  ReferralCodeString referral_code;
  EXPECT_TRUE(ParseReferralCode(L"OneVNBrowserSetup-extended-code.exe", referral_code));
  EXPECT_STREQ(referral_code.get(), L"extended-code");
}

TEST_F(OneVNMiniInstallerTest, HasInvalidExtendedReferralCodeNonAlphabeticCharacters) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"OneVNBrowserSetup-invalid-extended-c0de.exe", referral_code));
}

TEST_F(OneVNMiniInstallerTest, HasInvalidExtendedReferralCodeTooFewWords) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"OneVNBrowserSetup-invalidextendedcode.exe", referral_code));
}

}  // namespace mini_installer
