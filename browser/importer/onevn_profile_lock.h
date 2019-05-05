/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_IMPORTER_ONEVN_PROFILE_LOCK_H__
#define ONEVN_BROWSER_IMPORTER_ONEVN_PROFILE_LOCK_H__

#include "base/files/file_path.h"
#include "onevn/browser/importer/chrome_profile_lock.h"

class OnevnProfileLock : public ChromeProfileLock {
 public:
  explicit OnevnProfileLock(const base::FilePath& user_data_dir);
  ~OnevnProfileLock() override;

  void Lock() override;
};

#endif  // ONEVN_BROWSER_IMPORTER_ONEVN_PROFILE_LOCK_H__
