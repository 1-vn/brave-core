/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/ui/webui/onevn_welcome_ui.h"

#include "onevn/browser/onevn_browser_process_impl.h"
#include "onevn/common/pref_names.h"
#include "onevn/common/webui_url_constants.h"
#include "onevn/components/onevn_welcome/resources/grit/onevn_welcome_generated_map.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser_finder.h"
#include "chrome/browser/ui/chrome_pages.h"
#include "chrome/common/pref_names.h"
#include "chrome/common/webui_url_constants.h"
#include "components/grit/onevn_components_resources.h"
#include "components/prefs/pref_change_registrar.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/web_ui_message_handler.h"

using content::WebUIMessageHandler;

namespace {

// The handler for Javascript messages for the chrome://welcome page
class WelcomeDOMHandler : public WebUIMessageHandler {
 public:
  WelcomeDOMHandler() {
  }
  ~WelcomeDOMHandler() override {}

  void Init();

  // WebUIMessageHandler implementation.
  void RegisterMessages() override;

 private:
  void HandleImportNowRequested(const base::ListValue* args);
  void OnWalletInitialized(int result_code);
  Browser* GetBrowser();
  DISALLOW_COPY_AND_ASSIGN(WelcomeDOMHandler);
};

Browser* WelcomeDOMHandler::GetBrowser() {
  return chrome::FindBrowserWithWebContents(web_ui()->GetWebContents());
}

void WelcomeDOMHandler::RegisterMessages() {
  web_ui()->RegisterMessageCallback("importNowRequested",
      base::BindRepeating(&WelcomeDOMHandler::HandleImportNowRequested,
                          base::Unretained(this)));
}

void WelcomeDOMHandler::Init() {
}

void WelcomeDOMHandler::HandleImportNowRequested(const base::ListValue* args) {
  chrome::ShowSettingsSubPageInTabbedBrowser(GetBrowser(), chrome::kImportDataSubPage);
}

}  // namespace

OnevnWelcomeUI::OnevnWelcomeUI(content::WebUI* web_ui, const std::string& name)
    : BasicUI(web_ui, name, kOnevnWelcomeGenerated,
        kOnevnWelcomeGeneratedSize, IDR_ONEVN_WELCOME_HTML) {

  auto handler_owner = std::make_unique<WelcomeDOMHandler>();
  WelcomeDOMHandler* handler = handler_owner.get();
  web_ui->AddMessageHandler(std::move(handler_owner));
  handler->Init();
  Profile* profile = Profile::FromWebUI(web_ui);
  profile->GetPrefs()->SetBoolean(prefs::kHasSeenWelcomePage, true);
#if defined(OS_WIN)
  g_onevn_browser_process->local_state()->SetBoolean(
      prefs::kHasSeenWin10PromoPage,
      true);
#endif
}

OnevnWelcomeUI::~OnevnWelcomeUI() {
}
