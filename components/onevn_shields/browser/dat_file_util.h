/* Copyright (c) 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMPONENTS_ONEVN_SHIELDS_BROWSER_DAT_FILE_UTIL_H_
#define ONEVN_COMPONENTS_ONEVN_SHIELDS_BROWSER_DAT_FILE_UTIL_H_

#include <string>
#include <vector>

#include "base/callback_forward.h"

namespace base {
class FilePath;
}

namespace onevn_shields {

using DATFileDataBuffer = std::vector<unsigned char>;

void GetDATFileData(const base::FilePath& file_path,
                    DATFileDataBuffer* buffer);
void GetDATFileAsString(const base::FilePath& file_path,
                        std::string* contents);

}  // namespace onevn_shields

#endif  // ONEVN_COMPONENTS_ONEVN_SHIELDS_BROWSER_DAT_FILE_UTIL_H_
