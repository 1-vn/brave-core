// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/common/channel_info.h"

#include "base/strings/string_util.h"
#include "onevn/common/onevn_channel_info_posix.h"
#include "build/build_config.h"
#include "components/version_info/version_info.h"

namespace chrome {

std::string GetChannelName() {
  std::string modifier;
  onevn::GetChannelImpl(&modifier, nullptr);
  return modifier;
}

version_info::Channel GetChannel() {
  return onevn::GetChannelImpl(nullptr, nullptr);
}

}  // namespace chrome

