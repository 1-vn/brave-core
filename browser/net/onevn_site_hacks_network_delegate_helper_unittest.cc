/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/net/onevn_site_hacks_network_delegate_helper.h"

#include "onevn/browser/net/url_context.h"
#include "onevn/common/network_constants.h"
#include "chrome/test/base/chrome_render_view_host_test_harness.h"
#include "net/traffic_annotation/network_traffic_annotation_test_helper.h"
#include "net/url_request/url_request_test_util.h"

namespace {

class OneVNSiteHacksNetworkDelegateHelperTest: public testing::Test {
 public:
  OneVNSiteHacksNetworkDelegateHelperTest()
      : thread_bundle_(content::TestBrowserThreadBundle::IO_MAINLOOP),
        context_(new net::TestURLRequestContext(true)) {
  }
  ~OneVNSiteHacksNetworkDelegateHelperTest() override {}
  void SetUp() override {
    context_->Init();
  }
  net::TestURLRequestContext* context() { return context_.get(); }

 private:
  content::TestBrowserThreadBundle thread_bundle_;
  std::unique_ptr<net::TestURLRequestContext> context_;
};

TEST_F(OneVNSiteHacksNetworkDelegateHelperTest, ForbesWithCookieHeader) {
  GURL url("https://www.forbes.com");
  net::TestDelegate test_delegate;
  std::unique_ptr<net::URLRequest> request =
      context()->CreateRequest(url, net::IDLE, &test_delegate,
                               TRAFFIC_ANNOTATION_FOR_TESTS);
  net::HttpRequestHeaders headers;
  headers.SetHeader(kCookieHeader, "name=value; name2=value2; name3=value3");
  std::shared_ptr<onevn::OneVNRequestInfo>
      onevn_request_info(new onevn::OneVNRequestInfo());
  onevn::OneVNRequestInfo::FillCTXFromRequest(request.get(), onevn_request_info);
  onevn::ResponseCallback callback;
  int ret = onevn::OnBeforeStartTransaction_SiteHacksWork(request.get(), &headers,
      callback, onevn_request_info);
  std::string cookies;
  headers.GetHeader(kCookieHeader, &cookies);
  EXPECT_TRUE(cookies.find(std::string("; ") + kForbesExtraCookies) != std::string::npos);
  EXPECT_EQ(ret, net::OK);
}

TEST_F(OneVNSiteHacksNetworkDelegateHelperTest, ForbesWithoutCookieHeader) {
  GURL url("https://www.forbes.com/prime_numbers/573259391");
  net::TestDelegate test_delegate;
  std::unique_ptr<net::URLRequest> request =
      context()->CreateRequest(url, net::IDLE, &test_delegate,
                               TRAFFIC_ANNOTATION_FOR_TESTS);
  net::HttpRequestHeaders headers;
  std::shared_ptr<onevn::OneVNRequestInfo>
      onevn_request_info(new onevn::OneVNRequestInfo());
  onevn::OneVNRequestInfo::FillCTXFromRequest(request.get(), onevn_request_info);
  onevn::ResponseCallback callback;
  int ret = onevn::OnBeforeStartTransaction_SiteHacksWork(request.get(), &headers,
      callback, onevn_request_info);
  std::string cookies;
  headers.GetHeader(kCookieHeader, &cookies);
  EXPECT_TRUE(cookies.find(kForbesExtraCookies) != std::string::npos);
  EXPECT_EQ(ret, net::OK);
}

TEST_F(OneVNSiteHacksNetworkDelegateHelperTest, NotForbesNoCookieChange) {
  GURL url("https://www.1-vn.com/prime_numbers/573259391");
  net::TestDelegate test_delegate;
  std::unique_ptr<net::URLRequest> request =
      context()->CreateRequest(url, net::IDLE, &test_delegate,
                               TRAFFIC_ANNOTATION_FOR_TESTS);
  net::HttpRequestHeaders headers;
  std::string expected_cookies = "name=value; name2=value2; name3=value3";
  headers.SetHeader(kCookieHeader, "name=value; name2=value2; name3=value3");
  std::shared_ptr<onevn::OneVNRequestInfo>
      onevn_request_info(new onevn::OneVNRequestInfo());
  onevn::OneVNRequestInfo::FillCTXFromRequest(request.get(), onevn_request_info);
  onevn::ResponseCallback callback;
  int ret = onevn::OnBeforeStartTransaction_SiteHacksWork(request.get(), &headers,
      callback, onevn_request_info);
  std::string cookies;
  headers.GetHeader(kCookieHeader, &cookies);
  EXPECT_STREQ(cookies.c_str(), expected_cookies.c_str());
  EXPECT_EQ(ret, net::OK);
}

TEST_F(OneVNSiteHacksNetworkDelegateHelperTest, NoScriptTwitterMobileRedirect) {
  GURL url("https://mobile.twitter.com/i/nojs_router?path=%2F");
  net::TestDelegate test_delegate;
  std::unique_ptr<net::URLRequest> request =
      context()->CreateRequest(url, net::IDLE, &test_delegate,
                               TRAFFIC_ANNOTATION_FOR_TESTS);
  net::HttpRequestHeaders headers;
  headers.SetHeader(kRefererHeader, "https://twitter.com/");
  std::shared_ptr<onevn::OneVNRequestInfo>
      onevn_request_info(new onevn::OneVNRequestInfo());
  onevn::OneVNRequestInfo::FillCTXFromRequest(request.get(), onevn_request_info);
  onevn::ResponseCallback callback;
  int ret = onevn::OnBeforeStartTransaction_SiteHacksWork(request.get(), &headers,
      callback, onevn_request_info);
  EXPECT_EQ(ret, net::ERR_ABORTED);
}

TEST_F(OneVNSiteHacksNetworkDelegateHelperTest, AllowTwitterMobileRedirectFromDiffSite) {
  GURL url("https://mobile.twitter.com/i/nojs_router?path=%2F");
  net::TestDelegate test_delegate;
  std::unique_ptr<net::URLRequest> request =
      context()->CreateRequest(url, net::IDLE, &test_delegate,
                               TRAFFIC_ANNOTATION_FOR_TESTS);
  net::HttpRequestHeaders headers;
  headers.SetHeader(kRefererHeader, "https://brianbondy.com/");
  std::shared_ptr<onevn::OneVNRequestInfo>
      onevn_request_info(new onevn::OneVNRequestInfo());
  onevn::OneVNRequestInfo::FillCTXFromRequest(request.get(), onevn_request_info);
  onevn::ResponseCallback callback;
  int ret = onevn::OnBeforeStartTransaction_SiteHacksWork(request.get(), &headers,
      callback, onevn_request_info);
  EXPECT_EQ(ret, net::OK);
}

TEST_F(OneVNSiteHacksNetworkDelegateHelperTest, TwitterNoCancelWithReferer) {
  GURL url("https://twitter.com/brianbondy");
  net::TestDelegate test_delegate;
  std::unique_ptr<net::URLRequest> request =
      context()->CreateRequest(url, net::IDLE, &test_delegate,
                               TRAFFIC_ANNOTATION_FOR_TESTS);
  net::HttpRequestHeaders headers;
  headers.SetHeader(kRefererHeader, "https://twitter.com/");
  std::shared_ptr<onevn::OneVNRequestInfo>
      onevn_request_info(new onevn::OneVNRequestInfo());
  onevn::OneVNRequestInfo::FillCTXFromRequest(request.get(), onevn_request_info);
  onevn::ResponseCallback callback;
  int ret = onevn::OnBeforeStartTransaction_SiteHacksWork(request.get(), &headers,
      callback, onevn_request_info);
  EXPECT_EQ(ret, net::OK);
}

TEST_F(OneVNSiteHacksNetworkDelegateHelperTest, UAWhitelistedTest) {
  std::vector<GURL> urls({
    GURL("https://adobe.com"),
    GURL("https://adobe.com/something"),
    GURL("https://duckduckgo.com"),
    GURL("https://duckduckgo.com/something"),
    GURL("https://1-vn.com"),
    GURL("https://1-vn.com/something"),
    GURL("https://netflix.com"),
    GURL("https://netflix.com/something"),
    GURL("https://a.adobe.com"),
    GURL("https://a.duckduckgo.com"),
    GURL("https://a.1-vn.com"),
    GURL("https://a.netflix.com"),
    GURL("https://a.adobe.com/something"),
    GURL("https://a.duckduckgo.com/something"),
    GURL("https://a.1-vn.com/something"),
    GURL("https://a.netflix.com/something")
  });
  std::for_each(urls.begin(), urls.end(),
      [this](GURL url){
    net::TestDelegate test_delegate;
    std::unique_ptr<net::URLRequest> request =
        context()->CreateRequest(url, net::IDLE, &test_delegate,
                                 TRAFFIC_ANNOTATION_FOR_TESTS);
    net::HttpRequestHeaders headers;
    headers.SetHeader(kUserAgentHeader,
        "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 "
        "(KHTML, like Gecko) Chrome/33.0.1750.117 Safari/537.36");
    std::shared_ptr<onevn::OneVNRequestInfo>
        onevn_request_info(new onevn::OneVNRequestInfo());
    onevn::OneVNRequestInfo::FillCTXFromRequest(request.get(), onevn_request_info);
    onevn::ResponseCallback callback;
    int ret = onevn::OnBeforeStartTransaction_SiteHacksWork(request.get(), &headers,
        callback, onevn_request_info);
    std::string user_agent;
    headers.GetHeader(kUserAgentHeader, &user_agent);
    EXPECT_EQ(ret, net::OK);
    EXPECT_STREQ(user_agent.c_str(),
        "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 "
        "(KHTML, like Gecko) OneVN Chrome/33.0.1750.117 Safari/537.36");
  });
}

TEST_F(OneVNSiteHacksNetworkDelegateHelperTest, NOTUAWhitelistedTest) {
  std::vector<GURL> urls({
    GURL("https://brianbondy.com"),
    GURL("https://onevncombo.com"),
    GURL("https://onevn.example.com")
  });
  std::for_each(urls.begin(), urls.end(),
      [this](GURL url){
    net::TestDelegate test_delegate;
    std::unique_ptr<net::URLRequest> request =
        context()->CreateRequest(url, net::IDLE, &test_delegate,
                                 TRAFFIC_ANNOTATION_FOR_TESTS);
    net::HttpRequestHeaders headers;
    headers.SetHeader(kUserAgentHeader,
        "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 "
        "(KHTML, like Gecko) Chrome/33.0.1750.117 Safari/537.36");
    std::shared_ptr<onevn::OneVNRequestInfo>
        onevn_request_info(new onevn::OneVNRequestInfo());
    onevn::OneVNRequestInfo::FillCTXFromRequest(request.get(), onevn_request_info);
    onevn::ResponseCallback callback;
    int ret = onevn::OnBeforeStartTransaction_SiteHacksWork(request.get(), &headers,
        callback, onevn_request_info);
    std::string user_agent;
    headers.GetHeader(kUserAgentHeader, &user_agent);
    EXPECT_EQ(ret, net::OK);
    EXPECT_STREQ(user_agent.c_str(),
        "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 "
        "(KHTML, like Gecko) Chrome/33.0.1750.117 Safari/537.36");
  });
}

TEST_F(OneVNSiteHacksNetworkDelegateHelperTest, ReferrerPreserved) {
  std::vector<GURL> urls({
    GURL("https://brianbondy.com/7"),
    GURL("https://www.brianbondy.com/5"),
    GURL("https://brian.bondy.brianbondy.com")
  });
  std::for_each(urls.begin(), urls.end(),
      [this](GURL url){
    net::TestDelegate test_delegate;
    std::unique_ptr<net::URLRequest> request =
        context()->CreateRequest(url, net::IDLE, &test_delegate,
                                 TRAFFIC_ANNOTATION_FOR_TESTS);
    net::HttpRequestHeaders headers;
    std::string original_referrer = "https://hello.brianbondy.com/about";
    request->SetReferrer(original_referrer);

    std::shared_ptr<onevn::OneVNRequestInfo>
        onevn_request_info(new onevn::OneVNRequestInfo());
    onevn::OneVNRequestInfo::FillCTXFromRequest(request.get(), onevn_request_info);
    onevn::ResponseCallback callback;
    int ret = onevn::OnBeforeURLRequest_SiteHacksWork(callback, onevn_request_info);
    EXPECT_EQ(ret, net::OK);
    // new_url should not be set
    EXPECT_TRUE(onevn_request_info->new_url_spec.empty());
    EXPECT_STREQ(request->referrer().c_str(), original_referrer.c_str());
  });
}

TEST_F(OneVNSiteHacksNetworkDelegateHelperTest, ReferrerCleared) {
  std::vector<GURL> urls({
    GURL("https://digg.com/7"),
    GURL("https://slashdot.org/5"),
    GURL("https://bondy.brian.org")
  });
  std::for_each(urls.begin(), urls.end(),
      [this](GURL url){
    net::TestDelegate test_delegate;
    std::unique_ptr<net::URLRequest> request =
        context()->CreateRequest(url, net::IDLE, &test_delegate,
                                 TRAFFIC_ANNOTATION_FOR_TESTS);

    std::string original_referrer = "https://hello.brianbondy.com/about";
    request->SetReferrer(original_referrer);

    std::shared_ptr<onevn::OneVNRequestInfo>
        onevn_request_info(new onevn::OneVNRequestInfo());
    onevn::OneVNRequestInfo::FillCTXFromRequest(request.get(), onevn_request_info);
    onevn::ResponseCallback callback;
    int ret = onevn::OnBeforeURLRequest_SiteHacksWork(callback, onevn_request_info);
    EXPECT_EQ(ret, net::OK);
    // new_url should not be set
    EXPECT_TRUE(onevn_request_info->new_url_spec.empty());
    EXPECT_STREQ(request->referrer().c_str(), url.GetOrigin().spec().c_str());
  });
}

TEST_F(OneVNSiteHacksNetworkDelegateHelperTest, ReferrerWouldBeClearedButExtensionSite) {
  std::vector<GURL> urls({
    GURL("https://digg.com/7"),
    GURL("https://slashdot.org/5"),
    GURL("https://bondy.brian.org")
  });
  std::for_each(urls.begin(), urls.end(),
      [this](GURL url){
    net::TestDelegate test_delegate;
    std::unique_ptr<net::URLRequest> request =
        context()->CreateRequest(url, net::IDLE, &test_delegate,
                                 TRAFFIC_ANNOTATION_FOR_TESTS);
    request->set_site_for_cookies(GURL("chrome-extension://aemmndcbldboiebfnladdacbdfmadadm/test.html"));
    std::string original_referrer = "https://hello.brianbondy.com/about";
    request->SetReferrer(original_referrer);

    std::shared_ptr<onevn::OneVNRequestInfo>
        onevn_request_info(new onevn::OneVNRequestInfo());
    onevn::OneVNRequestInfo::FillCTXFromRequest(request.get(), onevn_request_info);
    onevn::ResponseCallback callback;
    int ret = onevn::OnBeforeURLRequest_SiteHacksWork(callback, onevn_request_info);
    EXPECT_EQ(ret, net::OK);
    // new_url should not be set
    EXPECT_TRUE(onevn_request_info->new_url_spec.empty());
    EXPECT_STREQ(request->referrer().c_str(), original_referrer.c_str());
  });
}

}  // namespace
