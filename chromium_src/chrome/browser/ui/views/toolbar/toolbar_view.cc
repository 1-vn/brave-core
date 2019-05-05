/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/ui/views/location_bar/location_bar_view.h"
#include "onevn/browser/ui/views/location_bar/onevn_location_bar_view.h"
#include "chrome/browser/ui/views/profiles/avatar_toolbar_button.h"
#include "onevn/browser/ui/views/profiles/onevn_avatar_toolbar_button.h"

#define LocationBarView OnevnLocationBarView
#define AvatarToolbarButton OnevnAvatarToolbarButton
#include "../../../../../../../chrome/browser/ui/views/toolbar/toolbar_view.cc" // NOLINT
#undef LocationBarView
#undef AvatarToolbarButton
