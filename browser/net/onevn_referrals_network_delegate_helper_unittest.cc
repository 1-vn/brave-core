/* Copyright 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/net/onevn_referrals_network_delegate_helper.h"

#include <memory>
#include <string>

#include "base/json/json_reader.h"
#include "onevn/browser/net/url_context.h"
#include "onevn/common/network_constants.h"
#include "chrome/test/base/chrome_render_view_host_test_harness.h"
#include "net/traffic_annotation/network_traffic_annotation_test_helper.h"
#include "net/url_request/url_request_test_util.h"
#include "url/gurl.h"
#include "url/url_constants.h"

const char kTestReferralHeaders[] = R"(
  [  
    {  
      "domains": [
         "marketwatch.com",
         "barrons.com"
      ],
      "headers": {
         "X-Onevn-Partner":"dowjones",
         "X-Invalid": "test"
      },
      "cookieNames": [
      ],
      "expiration":31536000000
    },
    {
      "domains": [
         "townsquareblogs.com",
         "tasteofcountry.com",
         "ultimateclassicrock.com",
         "xxlmag.com",
         "popcrush.com"
      ],
      "headers": {
         "X-Onevn-Partner":"townsquare"
      },
      "cookieNames":[
      ],
      "expiration":31536000000
    }
  ])";

namespace {

class OnevnReferralsNetworkDelegateHelperTest : public testing::Test {
 public:
  OnevnReferralsNetworkDelegateHelperTest()
      : thread_bundle_(content::TestBrowserThreadBundle::IO_MAINLOOP),
        context_(new net::TestURLRequestContext(true)) {
  }
  ~OnevnReferralsNetworkDelegateHelperTest() override {}
  void SetUp() override {
    context_->Init();
  }
  net::TestURLRequestContext* context() { return context_.get(); }

 private:
  content::TestBrowserThreadBundle thread_bundle_;
  std::unique_ptr<net::TestURLRequestContext> context_;
};

TEST_F(OnevnReferralsNetworkDelegateHelperTest,
       ReplaceHeadersForMatchingDomain) {
  GURL url("https://www.marketwatch.com");
  net::TestDelegate test_delegate;
  std::unique_ptr<net::URLRequest> request = context()->CreateRequest(
      url, net::IDLE, &test_delegate, TRAFFIC_ANNOTATION_FOR_TESTS);

  base::Optional<base::Value> referral_headers =
      base::JSONReader().ReadToValue(kTestReferralHeaders);
  ASSERT_TRUE(referral_headers);
  ASSERT_TRUE(referral_headers->is_list());

  base::ListValue* referral_headers_list = nullptr;
  referral_headers->GetAsList(&referral_headers_list);

  net::HttpRequestHeaders headers;
  onevn::ResponseCallback callback;
  std::shared_ptr<onevn::OnevnRequestInfo> onevn_request_info(
      new onevn::OnevnRequestInfo());
  onevn_request_info->referral_headers_list = referral_headers_list;
  int ret = onevn::OnBeforeStartTransaction_ReferralsWork(
      request.get(), &headers, callback, onevn_request_info);

  std::string partner_header;
  headers.GetHeader("X-Onevn-Partner", &partner_header);
  EXPECT_EQ(partner_header, "dowjones");

  std::string invalid_partner_header;
  EXPECT_EQ(headers.GetHeader("X-Invalid", &invalid_partner_header), false);
  EXPECT_EQ(invalid_partner_header, "");

  EXPECT_EQ(ret, net::OK);
}

TEST_F(OnevnReferralsNetworkDelegateHelperTest,
       NoReplaceHeadersForNonMatchingDomain) {
  GURL url("https://www.google.com");
  net::TestDelegate test_delegate;
  std::unique_ptr<net::URLRequest> request = context()->CreateRequest(
      url, net::IDLE, &test_delegate, TRAFFIC_ANNOTATION_FOR_TESTS);

  base::Optional<base::Value> referral_headers =
      base::JSONReader().ReadToValue(kTestReferralHeaders);
  ASSERT_TRUE(referral_headers);
  ASSERT_TRUE(referral_headers->is_list());

  base::ListValue* referral_headers_list = nullptr;
  referral_headers->GetAsList(&referral_headers_list);

  net::HttpRequestHeaders headers;
  onevn::ResponseCallback callback;
  std::shared_ptr<onevn::OnevnRequestInfo> onevn_request_info(
      new onevn::OnevnRequestInfo());
  onevn_request_info->referral_headers_list = referral_headers_list;
  int ret = onevn::OnBeforeStartTransaction_ReferralsWork(
      request.get(), &headers, callback, onevn_request_info);

  EXPECT_FALSE(headers.HasHeader("X-Onevn-Partner"));

  EXPECT_EQ(ret, net::OK);
}

}  // namespace
