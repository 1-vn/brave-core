/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMMON_IMPORTER_ONEVN_IMPORTER_UTILS_H_
#define ONEVN_COMMON_IMPORTER_ONEVN_IMPORTER_UTILS_H_

#include <stdint.h>

#include <vector>

namespace base {
class DictionaryValue;
class FilePath;
class ListValue;
}

base::FilePath GetOnevnUserDataFolder();

base::ListValue* GetOnevnSourceProfiles(
    const base::FilePath& user_data_folder);

bool OnevnImporterCanImport(const base::FilePath& profile,
			    uint16_t* services_supported);

#endif  // ONEVN_COMMON_IMPORTER_ONEVN_IMPORTER_UTILS_H_
