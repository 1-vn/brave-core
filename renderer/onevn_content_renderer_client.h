/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_RENDERER_ONEVN_CONTENT_RENDERER_CLIENT_H_
#define ONEVN_RENDERER_ONEVN_CONTENT_RENDERER_CLIENT_H_

#include "chrome/renderer/chrome_content_renderer_client.h"

class OneVNContentRendererClient : public ChromeContentRendererClient {
 public:
  OneVNContentRendererClient();
  ~OneVNContentRendererClient() override;
  void SetRuntimeFeaturesDefaultsBeforeBlinkInitialization() override;

 private:
  DISALLOW_COPY_AND_ASSIGN(OneVNContentRendererClient);
};

#endif  // ONEVN_RENDERER_ONEVN_CONTENT_RENDERER_CLIENT_H_
