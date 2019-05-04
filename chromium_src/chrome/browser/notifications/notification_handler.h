/* Copyright 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_CHROMIUM_SRC_CHROME_BROWSER_NOTIFICATIONS_NOTIFICATION_HANDLER_H_
#define ONEVN_CHROMIUM_SRC_CHROME_BROWSER_NOTIFICATIONS_NOTIFICATION_HANDLER_H_

#define NotificationHandler NotificationHandler_ChromiumImpl
#include "../../../../../../chrome/browser/notifications/notification_handler.h"
#undef NotificationHandler

class NotificationHandler : public NotificationHandler_ChromiumImpl {
 public:
  enum class Type {
    WEB_PERSISTENT = 0,
    WEB_NON_PERSISTENT = 1,
    EXTENSION = 2,
    SEND_TAB_TO_SELF = 3,
    TRANSIENT = 4,
    ONEVN_ADS = 5,
    MAX = ONEVN_ADS,
  };
};

#endif  // ONEVN_CHROMIUM_SRC_CHROME_BROWSER_NOTIFICATIONS_NOTIFICATION_HANDLER_H_
