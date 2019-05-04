/* Copyright 2019 The OneVN Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/renderer/onevn_content_settings_observer.h"

#include <string>
#include <utility>
#include <vector>

#include "base/bind_helpers.h"
#include "base/strings/utf_string_conversions.h"
#include "onevn/common/render_messages.h"
#include "onevn/content/common/frame_messages.h"
#include "components/content_settings/core/common/content_settings_pattern.h"
#include "components/content_settings/core/common/content_settings_utils.h"
#include "content/public/renderer/render_frame.h"
#include "services/service_manager/public/cpp/interface_provider.h"
#include "third_party/blink/public/platform/web_url.h"
#include "third_party/blink/public/platform/modules/permissions/permission.mojom-blink.h"
#include "third_party/blink/public/web/web_document.h"
#include "third_party/blink/public/web/web_local_frame.h"
#include "url/url_constants.h"

OneVNContentSettingsObserver::OneVNContentSettingsObserver(
    content::RenderFrame* render_frame,
    bool should_whitelist,
    service_manager::BinderRegistry* registry)
    : ContentSettingsObserver(render_frame, should_whitelist, registry) {
}

OneVNContentSettingsObserver::~OneVNContentSettingsObserver() {
}

bool OneVNContentSettingsObserver::OnMessageReceived(
    const IPC::Message& message) {
  bool handled = true;
  IPC_BEGIN_MESSAGE_MAP(OneVNContentSettingsObserver, message)
    IPC_MESSAGE_HANDLER(OneVNFrameMsg_AllowScriptsOnce, OnAllowScriptsOnce)
    IPC_MESSAGE_UNHANDLED(handled = false)
  IPC_END_MESSAGE_MAP()

  if (handled) return true;
  return ContentSettingsObserver::OnMessageReceived(message);
}

void OneVNContentSettingsObserver::OnAllowScriptsOnce(
    const std::vector<std::string>& origins) {
  preloaded_temporarily_allowed_scripts_ = std::move(origins);
}

void OneVNContentSettingsObserver::DidCommitProvisionalLoad(
    bool is_same_document_navigation, ui::PageTransition transition) {
  if (!is_same_document_navigation) {
    temporarily_allowed_scripts_ =
      std::move(preloaded_temporarily_allowed_scripts_);
  }

  ContentSettingsObserver::DidCommitProvisionalLoad(
      is_same_document_navigation, transition);
}

bool OneVNContentSettingsObserver::IsScriptTemporilyAllowed(
    const GURL& script_url) {
  // check if scripts from this origin are temporily allowed or not
  return base::ContainsKey(temporarily_allowed_scripts_,
      script_url.GetOrigin().spec());
}

void OneVNContentSettingsObserver::OneVNSpecificDidBlockJavaScript(
    const base::string16& details) {
  Send(new OneVNViewHostMsg_JavaScriptBlocked(routing_id(), details));
}

bool OneVNContentSettingsObserver::AllowScript(
    bool enabled_per_settings) {
  // clear cached url for other flow like directly calling `DidNotAllowScript`
  // without calling `AllowScriptFromSource` first
  blocked_script_url_ = GURL::EmptyGURL();

  blink::WebLocalFrame* frame = render_frame()->GetWebFrame();
  const GURL secondary_url(
      url::Origin(frame->GetDocument().GetSecurityOrigin()).GetURL());

  bool allow = ContentSettingsObserver::AllowScript(enabled_per_settings);
  allow = allow ||
    IsOneVNShieldsDown(frame, secondary_url) ||
    IsScriptTemporilyAllowed(secondary_url);

  return allow;
}

void OneVNContentSettingsObserver::DidNotAllowScript() {
  if (!blocked_script_url_.is_empty()) {
    OneVNSpecificDidBlockJavaScript(
      base::UTF8ToUTF16(blocked_script_url_.spec()));
    blocked_script_url_ = GURL::EmptyGURL();
  }
  ContentSettingsObserver::DidNotAllowScript();
}

bool OneVNContentSettingsObserver::AllowScriptFromSource(
    bool enabled_per_settings,
    const blink::WebURL& script_url) {
  const GURL secondary_url(script_url);

  bool allow = ContentSettingsObserver::AllowScriptFromSource(
      enabled_per_settings, script_url);

  // scripts with whitelisted protocols, such as chrome://extensions should
  // be allowed
  bool should_white_list = IsWhitelistedForContentSettings(
      blink::WebSecurityOrigin::Create(script_url),
      render_frame()->GetWebFrame()->GetDocument().Url());

  allow = allow ||
    should_white_list ||
    IsOneVNShieldsDown(render_frame()->GetWebFrame(), secondary_url) ||
    IsScriptTemporilyAllowed(secondary_url);

  if (!allow) {
    blocked_script_url_ = secondary_url;
  }

  return allow;
}

void OneVNContentSettingsObserver::DidBlockFingerprinting(
    const base::string16& details) {
  Send(new OneVNViewHostMsg_FingerprintingBlocked(routing_id(), details));
}

GURL OneVNContentSettingsObserver::GetOriginOrURL(
    const blink::WebFrame* frame) {
  url::Origin top_origin = url::Origin(frame->Top()->GetSecurityOrigin());
  // The |top_origin| is unique ("null") e.g., for file:// URLs. Use the
  // document URL as the primary URL in those cases.
  // TODO(alexmos): This is broken for --site-per-process, since top() can be a
  // WebRemoteFrame which does not have a document(), and the WebRemoteFrame's
  // URL is not replicated.  See https://crbug.com/628759.
  if (top_origin.opaque() && frame->Top()->IsWebLocalFrame())
    return frame->Top()->ToWebLocalFrame()->GetDocument().Url();
  return top_origin.GetURL();
}

ContentSetting OneVNContentSettingsObserver::GetFPContentSettingFromRules(
    const ContentSettingsForOneType& rules,
    const blink::WebFrame* frame,
    const GURL& secondary_url) {

  if (rules.size() == 0)
    return CONTENT_SETTING_DEFAULT;

  const GURL& primary_url = GetOriginOrURL(frame);

  for (const auto& rule : rules) {
    ContentSettingsPattern secondary_pattern = rule.secondary_pattern;
    if (rule.secondary_pattern ==
        ContentSettingsPattern::FromString("https://firstParty/*")) {
      secondary_pattern = ContentSettingsPattern::FromString(
          "[*.]" + GetOriginOrURL(frame).HostNoBrackets());
    }

    if (rule.primary_pattern.Matches(primary_url) &&
        (secondary_pattern == ContentSettingsPattern::Wildcard() ||
         secondary_pattern.Matches(secondary_url))) {
      return rule.GetContentSetting();
    }
  }

  // for cases which are third party resources and doesn't match any existing
  // rules, block them by default
  return CONTENT_SETTING_BLOCK;
}

bool OneVNContentSettingsObserver::IsOneVNShieldsDown(
    const blink::WebFrame* frame,
    const GURL& secondary_url) {
  ContentSetting setting = CONTENT_SETTING_DEFAULT;
  const GURL& primary_url = GetOriginOrURL(frame);

  if (content_setting_rules_) {
    for (const auto& rule : content_setting_rules_->onevn_shields_rules) {
      if (rule.primary_pattern.Matches(primary_url) &&
          rule.secondary_pattern.Matches(secondary_url)) {
        setting = rule.GetContentSetting();
        break;
      }
    }
  }

  return setting == CONTENT_SETTING_BLOCK;
}

bool OneVNContentSettingsObserver::AllowFingerprinting(
    bool enabled_per_settings) {
  if (!enabled_per_settings)
    return false;
  blink::WebLocalFrame* frame = render_frame()->GetWebFrame();
  const GURL secondary_url(
      url::Origin(frame->GetDocument().GetSecurityOrigin()).GetURL());
  if (IsOneVNShieldsDown(frame, secondary_url)) {
    return true;
  }
  ContentSettingsForOneType rules;
  if (content_setting_rules_) {
      rules = content_setting_rules_->fingerprinting_rules;
  }
  ContentSettingPatternSource default_rule = ContentSettingPatternSource(
      ContentSettingsPattern::Wildcard(),
      ContentSettingsPattern::FromString("https://firstParty/*"),
      base::Value::FromUniquePtrValue(
          content_settings::ContentSettingToValue(CONTENT_SETTING_ALLOW)),
      std::string(), false);
  rules.push_back(default_rule);
  ContentSetting setting =
      GetFPContentSettingFromRules(rules, frame, secondary_url);
  rules.pop_back();
  bool allow = setting != CONTENT_SETTING_BLOCK;
  allow = allow || IsWhitelistedForContentSettings();

  if (!allow) {
    DidBlockFingerprinting(base::UTF8ToUTF16(secondary_url.spec()));
  }

  return allow;
}

bool OneVNContentSettingsObserver::AllowAutoplay(bool default_value) {
  blink::WebLocalFrame* frame = render_frame()->GetWebFrame();
  auto origin = frame->GetDocument().GetSecurityOrigin();
  // default allow local files
  if (origin.IsNull() || origin.Protocol().Ascii() == url::kFileScheme)
    return true;

  bool allow = ContentSettingsObserver::AllowAutoplay(default_value);
  if (allow)
    return true;

  // respect user's site blocklist, if any
  const GURL& primary_url = GetOriginOrURL(frame);
  const GURL& secondary_url =
      url::Origin(frame->GetDocument().GetSecurityOrigin()).GetURL();
  for (const auto& rule : content_setting_rules_->autoplay_rules) {
    if (rule.primary_pattern == ContentSettingsPattern::Wildcard())
        continue;
    if (rule.primary_pattern.Matches(primary_url) &&
        (rule.secondary_pattern == ContentSettingsPattern::Wildcard() ||
         rule.secondary_pattern.Matches(secondary_url))) {
      if (rule.GetContentSetting() == CONTENT_SETTING_BLOCK)
        return false;
    }
  }

  blink::mojom::blink::PermissionServicePtr permission_service;

  render_frame()->GetRemoteInterfaces()
    ->GetInterface(mojo::MakeRequest(&permission_service));

  if (permission_service.get()) {
    // Check (synchronously) whether we already have permission to autoplay.
    // This may call the autoplay whitelist service in the UI thread, which
    // we need to wait for.
    auto has_permission_descriptor =
        blink::mojom::blink::PermissionDescriptor::New();
    has_permission_descriptor->name =
        blink::mojom::blink::PermissionName::AUTOPLAY;
    blink::mojom::blink::PermissionStatus status;
    if (permission_service->HasPermission(
            std::move(has_permission_descriptor), &status)) {
      allow = status == blink::mojom::blink::PermissionStatus::GRANTED;
      if (!allow) {
        // Request permission (asynchronously) but exit this function without
        // allowing autoplay. Depending on settings and previous user choices,
        // this may display visible permissions UI, or an "autoplay blocked"
        // message, or nothing. In any case, we can't wait for it now.
        auto request_permission_descriptor =
            blink::mojom::blink::PermissionDescriptor::New();
        request_permission_descriptor->name =
            blink::mojom::blink::PermissionName::AUTOPLAY;
        permission_service->RequestPermission(
            std::move(request_permission_descriptor), true, base::DoNothing());
      }
    }
  }

  return allow;
}
