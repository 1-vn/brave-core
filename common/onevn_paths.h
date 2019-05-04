/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_COMMON_ONEVN_PATHS_H
#define ONEVN_COMMON_ONEVN_PATHS_H

#include "build/build_config.h"

// This file declares path keys for the onevn module.  These can be used
// with the PathService to access various special directories and files.

namespace onevn {

enum {
  PATH_START = 12000,

  DIR_TEST_DATA,                // Directory where unit test data resides.
  PATH_END
};

// Call once to register the provider for the path keys defined above.
void RegisterPathProvider();

// Call once to override chrome's path with onevn's new path.
void OverridePath();

}  // namespace onevn

#endif  // ONEVN_COMMON_ONEVN_PATHS_H
