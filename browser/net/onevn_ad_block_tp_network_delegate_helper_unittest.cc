/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/net/onevn_ad_block_tp_network_delegate_helper.h"

#include "onevn/browser/net/url_context.h"
#include "onevn/common/network_constants.h"
#include "chrome/test/base/chrome_render_view_host_test_harness.h"
#include "net/traffic_annotation/network_traffic_annotation_test_helper.h"
#include "net/url_request/url_request_test_util.h"

using onevn::GetPolyfillForAdBlock;

namespace {

class OneVNAdBlockTPNetworkDelegateHelperTest: public testing::Test {
 public:
  OneVNAdBlockTPNetworkDelegateHelperTest()
      : thread_bundle_(content::TestBrowserThreadBundle::IO_MAINLOOP),
        context_(new net::TestURLRequestContext(true)) {
  }
  ~OneVNAdBlockTPNetworkDelegateHelperTest() override {}
  void SetUp() override {
    context_->Init();
  }
  net::TestURLRequestContext* context() { return context_.get(); }

 private:
  content::TestBrowserThreadBundle thread_bundle_;
  std::unique_ptr<net::TestURLRequestContext> context_;
};


TEST_F(OneVNAdBlockTPNetworkDelegateHelperTest, NoChangeURL) {
  net::TestDelegate test_delegate;
  GURL url("https://bradhatesprimes.1-vn.com/composite_numbers_ftw");
  std::unique_ptr<net::URLRequest> request =
      context()->CreateRequest(url, net::IDLE, &test_delegate,
                               TRAFFIC_ANNOTATION_FOR_TESTS);
  std::shared_ptr<onevn::OneVNRequestInfo>
      onevn_request_info(new onevn::OneVNRequestInfo());
  onevn::OneVNRequestInfo::FillCTXFromRequest(request.get(), onevn_request_info);
  onevn::ResponseCallback callback;
  int ret =
    OnBeforeURLRequest_AdBlockTPPreWork(callback,
        onevn_request_info);
  onevn::OneVNRequestInfo::FillCTXFromRequest(request.get(), onevn_request_info);
  EXPECT_TRUE(onevn_request_info->new_url_spec.empty());
  EXPECT_EQ(ret, net::OK);
}

TEST_F(OneVNAdBlockTPNetworkDelegateHelperTest, EmptyRequestURL) {
  net::TestDelegate test_delegate;
  std::unique_ptr<net::URLRequest> request =
      context()->CreateRequest(GURL(), net::IDLE, &test_delegate,
                               TRAFFIC_ANNOTATION_FOR_TESTS);
  std::shared_ptr<onevn::OneVNRequestInfo>
      onevn_request_info(new onevn::OneVNRequestInfo());
  onevn::OneVNRequestInfo::FillCTXFromRequest(request.get(), onevn_request_info);
  onevn::ResponseCallback callback;
  int ret =
    OnBeforeURLRequest_AdBlockTPPreWork(callback,
        onevn_request_info);
  onevn::OneVNRequestInfo::FillCTXFromRequest(request.get(), onevn_request_info);
  EXPECT_TRUE(onevn_request_info->new_url_spec.empty());
  EXPECT_EQ(ret, net::OK);
}


TEST_F(OneVNAdBlockTPNetworkDelegateHelperTest, RedirectsToStubs) {
  std::vector<GURL> urls({
    GURL(kGoogleTagManagerPattern),
    GURL(kGoogleTagServicesPattern)
  });
  std::for_each(urls.begin(), urls.end(),
      [this](GURL url){
    net::TestDelegate test_delegate;
    std::unique_ptr<net::URLRequest> request =
        context()->CreateRequest(url, net::IDLE, &test_delegate,
                                 TRAFFIC_ANNOTATION_FOR_TESTS);
    std::shared_ptr<onevn::OneVNRequestInfo>
        onevn_request_info(new onevn::OneVNRequestInfo());
    onevn::OneVNRequestInfo::FillCTXFromRequest(request.get(), onevn_request_info);
    onevn::ResponseCallback callback;
    int ret =
      OnBeforeURLRequest_AdBlockTPPreWork(callback,
          onevn_request_info);
    onevn::OneVNRequestInfo::FillCTXFromRequest(request.get(), onevn_request_info);
    EXPECT_EQ(ret, net::OK);
    EXPECT_TRUE(GURL(onevn_request_info->new_url_spec).SchemeIs("data"));
  });
}

TEST_F(OneVNAdBlockTPNetworkDelegateHelperTest, Blocking) {
  std::vector<GURL> urls({
      GURL("https://pdfjs.robwu.nl/ping"),
    });
  std::for_each(urls.begin(), urls.end(), [this](GURL url){
    net::TestDelegate test_delegate;
    std::unique_ptr<net::URLRequest> request =
      context()->CreateRequest(url, net::IDLE, &test_delegate,
                               TRAFFIC_ANNOTATION_FOR_TESTS);
    std::shared_ptr<onevn::OneVNRequestInfo>
      onevn_request_info(new onevn::OneVNRequestInfo());
    onevn::OneVNRequestInfo::FillCTXFromRequest(request.get(), onevn_request_info);
    onevn::ResponseCallback callback;
    int ret =
      OnBeforeURLRequest_AdBlockTPPreWork(callback,
                                          onevn_request_info);
    onevn::OneVNRequestInfo::FillCTXFromRequest(request.get(), onevn_request_info);
    EXPECT_STREQ(onevn_request_info->new_url_spec.c_str(), kEmptyDataURI);
    EXPECT_EQ(ret, net::OK);
  });
}

TEST_F(OneVNAdBlockTPNetworkDelegateHelperTest, GetPolyfill) {
  GURL tab_origin("https://test.com");
  GURL tag_manager_url(kGoogleTagManagerPattern);
  GURL tag_services_url(kGoogleTagServicesPattern);
  GURL normal_url("https://a.com");
  std::string out_url_spec;
  // Shields up, block ads, tag manager should get polyfill
  ASSERT_TRUE(GetPolyfillForAdBlock(true, false, tab_origin, tag_manager_url, &out_url_spec));
  // Shields up, block ads, tag services should get polyfill
  ASSERT_TRUE(GetPolyfillForAdBlock(true, false, tab_origin, tag_services_url, &out_url_spec));
  // Shields up, block ads, normal URL should NOT get polyfill
  ASSERT_FALSE(GetPolyfillForAdBlock(true, false, tab_origin, normal_url, &out_url_spec));

  // Shields up, allow ads, tag manager should NOT get polyfill
  ASSERT_FALSE(GetPolyfillForAdBlock(true, true, tab_origin, tag_manager_url, &out_url_spec));
  // Shields up, allow ads, tag services should NOT get polyfill
  ASSERT_FALSE(GetPolyfillForAdBlock(true, true, tab_origin, tag_services_url, &out_url_spec));
  // Shields up, allow ads, normal URL should NOT get polyfill
  ASSERT_FALSE(GetPolyfillForAdBlock(true, true, tab_origin, normal_url, &out_url_spec));

  // Shields down, allow ads, tag manager should NOT get polyfill
  ASSERT_FALSE(GetPolyfillForAdBlock(false, true, tab_origin, tag_manager_url, &out_url_spec));
  // Shields down, allow ads, tag services should NOT get polyfill
  ASSERT_FALSE(GetPolyfillForAdBlock(false, true, tab_origin, tag_services_url, &out_url_spec));
  // Shields down, allow ads, normal URL should NOT get polyfill
  ASSERT_FALSE(GetPolyfillForAdBlock(false, true, tab_origin, normal_url, &out_url_spec));

  // Shields down, block ads, tag manager should NOT get polyfill
  ASSERT_FALSE(GetPolyfillForAdBlock(false, false, tab_origin, tag_manager_url, &out_url_spec));
  // Shields down, block ads, tag services should NOT get polyfill
  ASSERT_FALSE(GetPolyfillForAdBlock(false, false, tab_origin, tag_services_url, &out_url_spec));
  // Shields down, block ads, normal URL should NOT get polyfill
  ASSERT_FALSE(GetPolyfillForAdBlock(false, false, tab_origin, normal_url, &out_url_spec));
}

}  // namespace
