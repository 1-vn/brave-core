/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/ui/views/location_bar/onevn_location_bar_view.h"

#include "onevn/browser/themes/onevn_theme_service.h"
#include "chrome/browser/profiles/profile.h"
#include "onevn/browser/ui/views/onevn_actions/onevn_actions_container.h"
#include "chrome/browser/ui/layout_constants.h"
#include "chrome/browser/ui/omnibox/omnibox_theme.h"
#include "chrome/browser/ui/views/location_bar/location_bar_view.h"
#include "chrome/browser/ui/views/location_bar/star_view.h"
#include "components/version_info/channel.h"

void OnevnLocationBarView::Init() {
  // LocationBarView (original) GetTint is called from ctor,
  // which will not use our overriden function, so call it again here.
  tint_ = GetTint();
  // base method calls Update and Layout
  LocationBarView::Init();
  // onevn action buttons
  onevn_actions_ = new OnevnActionsContainer(browser_, profile());
  onevn_actions_->Init();
  AddChildView(onevn_actions_);
  // Call Update again to cause a Layout
  Update(nullptr);
}

void OnevnLocationBarView::Layout() {
  LocationBarView::Layout(onevn_actions_ ? onevn_actions_ : nullptr);
}

void OnevnLocationBarView::Update(const content::WebContents* contents) {
  // base Init calls update before our Init is run, so our children
  // may not be initialized yet
  if (onevn_actions_) {
    onevn_actions_->Update();
  }
  LocationBarView::Update(contents);
}

void OnevnLocationBarView::UpdateBookmarkStarVisibility() {
  if (star_view_) {
    star_view_->SetVisible(false);
  }
}

void OnevnLocationBarView::OnChanged() {
  if (onevn_actions_) {
    // Do not show actions whilst omnibar is open or url is being edited
    const bool should_hide = GetLocationBarModel()->input_in_progress() &&
                      !omnibox_view_->text().empty();
    onevn_actions_->SetShouldHide(should_hide);
  }

  // OnChanged calls Layout
  LocationBarView::OnChanged();
}

gfx::Size OnevnLocationBarView::CalculatePreferredSize() const {
  gfx::Size min_size = LocationBarView::CalculatePreferredSize();
  if (onevn_actions_ && onevn_actions_->visible()){
    const int onevn_actions_min = onevn_actions_->GetMinimumSize().width();
    const int extra_width = onevn_actions_min +
                              GetLayoutConstant(LOCATION_BAR_ELEMENT_PADDING);
    min_size.Enlarge(extra_width, 0);
  }
  return min_size;
}

OmniboxTint OnevnLocationBarView::GetTint() {
  // Match the user-selectable onevn theme, even if there is a theme extension
  // installed, allowing non-extension-themeable elements to fit in better with
  // a theme extension.
  if (profile()->GetProfileType() == Profile::INCOGNITO_PROFILE ||
      profile()->IsTorProfile()) {
    return OmniboxTint::PRIVATE; // special extra enum value
  }
  // TODO: OnevnThemeService can have a simpler get dark / light function
  switch (OnevnThemeService::GetActiveOnevnThemeType(profile())) {
    case OnevnThemeType::ONEVN_THEME_TYPE_LIGHT:
      return OmniboxTint::LIGHT;
    case OnevnThemeType::ONEVN_THEME_TYPE_DARK:
      return OmniboxTint::DARK;
    default:
      NOTREACHED();
      return OmniboxTint::LIGHT;
  }
}


void OnevnLocationBarView::OnThemeChanged() {
  LocationBarView::OnThemeChanged();

  if (!IsInitialized())
    return;

  Update(nullptr);
  RefreshBackground();
}

void OnevnLocationBarView::ChildPreferredSizeChanged(views::View* child) {
  LocationBarView::ChildPreferredSizeChanged(child);

  if (child != onevn_actions_)
    return;

  Layout();
}

ContentSettingImageView*
OnevnLocationBarView::GetContentSettingsImageViewForTesting(size_t idx) {
  DCHECK(idx < content_setting_views_.size());
  return content_setting_views_[idx];
}

// Provide base class implementation for Update override that has been added to
// header via a patch. This should never be called as the only instantiated
// implementation should be our |OnevnLocationBarView|.
void LocationBarView::Layout() {
  Layout(nullptr);
}

