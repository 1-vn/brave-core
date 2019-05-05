/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_AUTOCOMPLETE_ONEVN_GEOLOCATION_PERMISSION_CONTEXT_H_
#define ONEVN_BROWSER_AUTOCOMPLETE_ONEVN_GEOLOCATION_PERMISSION_CONTEXT_H_

#include "chrome/browser/geolocation/geolocation_permission_context.h"

class OnevnGeolocationPermissionContext : public GeolocationPermissionContext {
 public:
  explicit OnevnGeolocationPermissionContext(Profile* profile);
  ~OnevnGeolocationPermissionContext() override;

  void DecidePermission(content::WebContents* web_contents,
                        const PermissionRequestID& id,
                        const GURL& requesting_origin,
                        const GURL& embedding_origin,
                        bool user_gesture,
                        const BrowserPermissionCallback& callback) override;

 private:
  DISALLOW_COPY_AND_ASSIGN(OnevnGeolocationPermissionContext);
};

#endif  // ONEVN_BROWSER_AUTOCOMPLETE_ONEVN_GEOLOCATION_PERMISSION_CONTEXT_H_
