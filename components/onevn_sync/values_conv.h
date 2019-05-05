/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_SYNC_VALUES_CONV_H_
#define ONEVN_COMPONENTS_ONEVN_SYNC_VALUES_CONV_H_

#include <memory>
#include <vector>
#include <string>

#include <base/time/time.h>
#include "onevn/components/onevn_sync/jslib_messages_fwd.h"

namespace base {
  class Value;
}

namespace onevn_sync {

class Settings;

std::unique_ptr<base::Value> OnevnSyncSettingsToValue(onevn_sync::Settings *onevn_sync_settings);

template <typename TEnum>
TEnum ExtractEnum(const base::Value *val, const std::string &fileld_name,
  TEnum min, TEnum max, TEnum def);

template <typename TEnum>
TEnum ConvertEnum(const int val, TEnum min, TEnum max, TEnum def);

std::string StrFromUint8Array(const Uint8Array &arr);
std::string StrFromUnsignedCharArray(const std::vector<unsigned char> &vec);
Uint8Array Uint8ArrayFromString(const std::string &data_string);
std::vector<unsigned char> UCharVecFromString(const std::string &data_string);

} // namespace onevn_sync

#endif //ONEVN_COMPONENTS_ONEVN_SYNC_VALUES_CONV_H_
