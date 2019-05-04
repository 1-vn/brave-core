/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_BROWSER_UI_VIEWS_ONEVN_LAYOUT_PROVIDER_H_
#define ONEVN_BROWSER_UI_VIEWS_ONEVN_LAYOUT_PROVIDER_H_

#include "base/macros.h"
#include "chrome/browser/ui/views/material_refresh_layout_provider.h"

// Subclasses MaterialRefresh layout though if this class start to override most
// members, then it should directly subclass ChromeLayoutProvider.
class OneVNLayoutProvider : public MaterialRefreshLayoutProvider {
  public:
    OneVNLayoutProvider() = default;
    ~OneVNLayoutProvider() override = default;

    int GetCornerRadiusMetric(views::EmphasisMetric emphasis_metric,
                            const gfx::Size& size = gfx::Size()) const override;
  private:
    DISALLOW_COPY_AND_ASSIGN(OneVNLayoutProvider);
};

#endif
