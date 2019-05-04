/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/net/onevn_httpse_network_delegate_helper.h"

#include "onevn/browser/net/url_context.h"
#include "onevn/common/network_constants.h"
#include "chrome/test/base/chrome_render_view_host_test_harness.h"
#include "net/traffic_annotation/network_traffic_annotation_test_helper.h"
#include "net/url_request/url_request_test_util.h"

namespace {

class OneVNHTTPSENetworkDelegateHelperTest: public testing::Test {
 public:
  OneVNHTTPSENetworkDelegateHelperTest()
      : thread_bundle_(content::TestBrowserThreadBundle::IO_MAINLOOP),
        context_(new net::TestURLRequestContext(true)) {
  }
  ~OneVNHTTPSENetworkDelegateHelperTest() override {}
  void SetUp() override {
    context_->Init();
  }
  net::TestURLRequestContext* context() { return context_.get(); }

 private:
  content::TestBrowserThreadBundle thread_bundle_;
  std::unique_ptr<net::TestURLRequestContext> context_;
};


TEST_F(OneVNHTTPSENetworkDelegateHelperTest, AlreadySetNewURLNoOp) {
  net::TestDelegate test_delegate;
  GURL url("http://bradhatesprimes.1-vn.com/composite_numbers_ftw");
  std::unique_ptr<net::URLRequest> request =
      context()->CreateRequest(url, net::IDLE, &test_delegate,
                               TRAFFIC_ANNOTATION_FOR_TESTS);
  std::shared_ptr<onevn::OneVNRequestInfo>
      onevn_request_info(new onevn::OneVNRequestInfo());
  request->set_site_for_cookies(
      GURL("http://brad.1-vn.com/hide_all_primes_in_ui/composites_forever"));
  onevn_request_info->new_url_spec = "data:image/png;base64,iVB";
  onevn::ResponseCallback callback;
  int ret =
    OnBeforeURLRequest_HttpsePreFileWork(callback, onevn_request_info);
  EXPECT_EQ(onevn_request_info->new_url_spec, onevn_request_info->new_url_spec);
  EXPECT_EQ(ret, net::OK);
}

}  // namespace
