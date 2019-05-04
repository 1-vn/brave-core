/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/common/importer/onevn_importer_utils.h"

#include "base/base_paths.h"
#include "base/files/file_path.h"
#include "base/files/file_util.h"
#include "base/path_service.h"

base::FilePath GetOneVNUserDataFolder() {
  base::FilePath home;
  if (!base::PathService::Get(base::DIR_HOME, &home))
    return base::FilePath();

  base::FilePath result = home;

  // If OneVN is installed via Snap, use the sandboxed home directory.
  if (base::PathExists(base::FilePath("/snap/bin/onevn"))) {
    result = result.Append("snap").Append("onevn").Append("current");
  }

  return result.Append(".config").Append("onevn");
}
