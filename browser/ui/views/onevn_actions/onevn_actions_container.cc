/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/ui/views/onevn_actions/onevn_actions_container.h"

#include <memory>
#include <string>
#include <utility>

#include "onevn/browser/ui/onevn_actions/onevn_action_view_controller.h"
#include "onevn/browser/ui/views/onevn_actions/onevn_action_view.h"
#include "onevn/browser/ui/views/rounded_separator.h"
#include "onevn/common/extensions/extension_constants.h"
#include "onevn/common/pref_names.h"
#include "onevn/components/onevn_rewards/common/pref_names.h"
#include "chrome/browser/extensions/extension_action_manager.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/layout_constants.h"
#include "chrome/browser/ui/toolbar/toolbar_action_view_controller.h"
#include "chrome/browser/ui/views/toolbar/toolbar_action_view.h"
#include "components/prefs/pref_service.h"
#include "extensions/browser/extension_registry.h"
#include "extensions/browser/extension_registry_observer.h"
#include "extensions/browser/extension_system.h"
#include "extensions/common/one_shot_event.h"
#include "ui/views/layout/box_layout.h"
#include "ui/views/layout/grid_layout.h"
#include "ui/views/view.h"

OnevnActionsContainer::OnevnActionInfo::OnevnActionInfo()
    : position_(ACTION_ANY_POSITION) {}

OnevnActionsContainer::OnevnActionInfo::~OnevnActionInfo() {
  Reset();
}

void OnevnActionsContainer::OnevnActionInfo::Reset() {
  // Destroy view before view_controller.
  // Destructor for |ToolbarActionView| tries to access controller instance.
  view_.reset();
  view_controller_.reset();
}

OnevnActionsContainer::OnevnActionsContainer(Browser* browser, Profile* profile)
    : views::View(),
      browser_(browser),
      extension_action_api_(extensions::ExtensionActionAPI::Get(profile)),
      extension_registry_(extensions::ExtensionRegistry::Get(profile)),
      extension_action_manager_(
          extensions::ExtensionActionManager::Get(profile)),
      extension_registry_observer_(this),
      extension_action_observer_(this),
      weak_ptr_factory_(this) {
  // Handle when the extension system is ready
  extensions::ExtensionSystem::Get(profile)->ready().Post(
      FROM_HERE, base::Bind(&OnevnActionsContainer::OnExtensionSystemReady,
                            weak_ptr_factory_.GetWeakPtr()));
}

OnevnActionsContainer::~OnevnActionsContainer() {
  actions_.clear();
}

void OnevnActionsContainer::Init() {
  // automatic layout
  auto vertical_container_layout = std::make_unique<views::BoxLayout>(
                                                views::BoxLayout::kHorizontal);
  vertical_container_layout->set_main_axis_alignment(
                                  views::BoxLayout::MAIN_AXIS_ALIGNMENT_CENTER);
  vertical_container_layout->set_cross_axis_alignment(
      views::BoxLayout::CROSS_AXIS_ALIGNMENT_CENTER);
  SetLayoutManager(std::move(vertical_container_layout));

  // children
  RoundedSeparator* onevn_button_separator_ = new RoundedSeparator();
  // TODO(petemill): theme color
  onevn_button_separator_->SetColor(SkColorSetRGB(0xb2, 0xb5, 0xb7));
  constexpr int kSeparatorRightMargin = 2;
  constexpr int kSeparatorWidth = 1;
  onevn_button_separator_->SetPreferredSize(gfx::Size(
                                    kSeparatorWidth + kSeparatorRightMargin,
                                    GetLayoutConstant(LOCATION_BAR_ICON_SIZE)));
  // separator right margin
  onevn_button_separator_->SetBorder(
      views::CreateEmptyBorder(0, 0, 0, kSeparatorRightMargin));
  // Just in case the extensions load before this function does (not likely!)
  // make sure separator is at index 0
  AddChildViewAt(onevn_button_separator_, 0);
  // Populate actions
  actions_[onevn_extension_id].position_ = 1;
  actions_[onevn_rewards_extension_id].position_ = ACTION_ANY_POSITION;

  // React to Onevn Rewards preferences changes.
  onevn_rewards_enabled_.Init(
      onevn_rewards::prefs::kOnevnRewardsEnabled,
      browser_->profile()->GetPrefs(),
      base::Bind(&OnevnActionsContainer::OnOnevnRewardsPreferencesChanged,
                 base::Unretained(this)));
  hide_onevn_rewards_button_.Init(
      kHideOnevnRewardsButton, browser_->profile()->GetPrefs(),
      base::Bind(&OnevnActionsContainer::OnOnevnRewardsPreferencesChanged,
                 base::Unretained(this)));
}

bool OnevnActionsContainer::IsContainerAction(const std::string& id) const {
  return (actions_.find(id) != actions_.end());
}

bool OnevnActionsContainer::ShouldAddAction(const std::string& id) const {
  if (!IsContainerAction(id))
    return false;
  if (id == onevn_rewards_extension_id)
    return ShouldAddOnevnRewardsAction();
  return true;
}

bool OnevnActionsContainer::ShouldAddOnevnRewardsAction() const {
  // Guest (and Tor for now) should not show the action.
  if (browser_->profile()->IsGuestSession())
    return false;
  const PrefService* prefs = browser_->profile()->GetPrefs();
  return prefs->GetBoolean(onevn_rewards::prefs::kOnevnRewardsEnabled) ||
         !prefs->GetBoolean(kHideOnevnRewardsButton);
}

void OnevnActionsContainer::AddAction(const extensions::Extension* extension,
                                      int pos) {
  DCHECK(extension);
  if (!ShouldAddAction(extension->id()))
    return;
  VLOG(1) << "AddAction (" << extension->id() << "), was already loaded: "
          << static_cast<bool>(actions_[extension->id()].view_);
  if (!actions_[extension->id()].view_) {
    const auto& id = extension->id();
    // Create a ExtensionActionViewController for the extension
    // Passing |nullptr| instead of ToolbarActionsBar since we
    // do not require that logic.
    // If we do require notifications when popups are open or closed,
    // then we should inherit and pass |this| through.
    actions_[id].view_controller_ =
        std::make_unique<OnevnActionViewController>(
        extension, browser_,
        extension_action_manager_->GetExtensionAction(*extension), nullptr);
    // The button view
    actions_[id].view_ = std::make_unique<OnevnActionView>(
        actions_[id].view_controller_.get(), this);
    // Add extension view after separator view
    // `AddChildView` should be called first, so that changes that modify
    // layout (e.g. preferred size) are forwarded to its parent
    if (actions_[id].position_ != ACTION_ANY_POSITION) {
      DCHECK_GT(actions_[id].position_, 0);
      AddChildViewAt(actions_[id].view_.get(), actions_[id].position_);
    } else {
      AddChildView(actions_[id].view_.get());
    }
    // we control destruction
    actions_[id].view_->set_owned_by_client();
    // Sets overall size of button but not image graphic. We set a large width
    // in order to give space for the bubble.
    actions_[id].view_->SetPreferredSize(gfx::Size(34, 24));
    Update();
  }
}

void OnevnActionsContainer::AddAction(const std::string& id, int pos) {
  DCHECK(extension_registry_);
  const extensions::Extension* extension =
      extension_registry_->enabled_extensions().GetByID(id);
  if (extension)
    AddAction(extension, pos);
}

void OnevnActionsContainer::RemoveAction(const std::string& id) {
  DCHECK(IsContainerAction(id));
  VLOG(1) << "RemoveAction (" << id << "), was loaded: "
          << static_cast<bool>(actions_[id].view_);
  // This will reset references and automatically remove the child from the
  // parent (us)
  actions_[id].Reset();
  // layout
  Update();
  PreferredSizeChanged();
}

// Adds or removes action
void OnevnActionsContainer::ShowAction(const std::string& id, bool show) {
  if (show != IsActionShown(id))
    show ? AddAction(id) : RemoveAction(id);
}

// Checks if action for the given |id| has been added
bool OnevnActionsContainer::IsActionShown(const std::string& id) const {
  DCHECK(IsContainerAction(id));
  return(actions_.at(id).view_ != nullptr);
}

void OnevnActionsContainer::UpdateActionState(const std::string& id) {
  if (actions_[id].view_controller_)
    actions_[id].view_controller_->UpdateState();
}

void OnevnActionsContainer::Update() {
  // Update state of each action and also determine if there are any buttons to
  // show
  bool can_show = false;
  for (auto const& pair : actions_) {
    if (pair.second.view_controller_)
      pair.second.view_controller_->UpdateState();
    if (!can_show && pair.second.view_)
      can_show = true;
  }
  // only show separator if we're showing any buttons
  const bool visible = !should_hide_ && can_show;
  SetVisible(visible);
  Layout();
}

void OnevnActionsContainer::SetShouldHide(bool should_hide) {
  should_hide_ = should_hide;
  Update();
}

content::WebContents* OnevnActionsContainer::GetCurrentWebContents() {
  return browser_->tab_strip_model()->GetActiveWebContents();
}

bool OnevnActionsContainer::ShownInsideMenu() const {
  return false;
}

void OnevnActionsContainer::OnToolbarActionViewDragDone() {
}

views::MenuButton* OnevnActionsContainer::GetOverflowReferenceView() {
  // Our action views should always be visible,
  // so we should not need another view.
  NOTREACHED();
  return nullptr;
}

// ToolbarActionView::Delegate members
gfx::Size OnevnActionsContainer::GetToolbarActionSize() {
  // Shields icon should be square, and full-height
  gfx::Rect rect(gfx::Size(height(), height()));
  rect.Inset(-GetLayoutInsets(LOCATION_BAR_ICON_INTERIOR_PADDING));
  return rect.size();
}

void OnevnActionsContainer::WriteDragDataForView(View* sender,
                                                   const gfx::Point& press_pt,
                                                   OSExchangeData* data) {
  // Not supporting drag for action buttons inside this container
}

int OnevnActionsContainer::GetDragOperationsForView(View* sender,
                                                      const gfx::Point& p) {
  return ui::DragDropTypes::DRAG_NONE;
}

bool OnevnActionsContainer::CanStartDragForView(View* sender,
                                                  const gfx::Point& press_pt,
                                                  const gfx::Point& p) {
  return false;
}
// end ToolbarActionView::Delegate members

void OnevnActionsContainer::OnExtensionSystemReady() {
  // observe changes in extension system
  extension_registry_observer_.Add(extension_registry_);
  extension_action_observer_.Add(extension_action_api_);
  // Check if onevn extension already loaded
  const extensions::Extension* extension =
          extension_registry_->enabled_extensions().GetByID(onevn_extension_id);
  if (extension)
    AddAction(extension);
  // Check if onevn rewards extension already loaded
  extension = extension_registry_->enabled_extensions().GetByID(
      onevn_rewards_extension_id);
  if (extension)
    AddAction(extension);
}

// ExtensionRegistry::Observer
void OnevnActionsContainer::OnExtensionLoaded(
    content::BrowserContext* browser_context,
    const extensions::Extension* extension) {
  if (IsContainerAction(extension->id()))
    AddAction(extension);
}

void OnevnActionsContainer::OnExtensionUnloaded(
    content::BrowserContext* browser_context,
    const extensions::Extension* extension,
    extensions::UnloadedExtensionReason reason) {
  if (IsContainerAction(extension->id()))
    RemoveAction(extension->id());
}
// end ExtensionRegistry::Observer

// ExtensionActionAPI::Observer
void OnevnActionsContainer::OnExtensionActionUpdated(
    ExtensionAction* extension_action,
    content::WebContents* web_contents,
    content::BrowserContext* browser_context) {
  if (IsContainerAction(extension_action->extension_id()))
    UpdateActionState(extension_action->extension_id());
}
// end ExtensionActionAPI::Observer

void OnevnActionsContainer::ChildPreferredSizeChanged(views::View* child) {
  PreferredSizeChanged();
}

// Onevn Rewards preferences change observers callback
void OnevnActionsContainer::OnOnevnRewardsPreferencesChanged() {
  ShowAction(onevn_rewards_extension_id, ShouldAddOnevnRewardsAction());
}
