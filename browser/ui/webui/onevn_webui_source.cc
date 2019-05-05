/* Copyright (c) 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/ui/webui/onevn_webui_source.h"

#include <map>
#include <vector>

#include "components/grit/onevn_components_strings.h"
#include "content/public/browser/web_ui_data_source.h"

#if !defined(OS_ANDROID)
#include "onevn/components/onevn_rewards/resources/grit/onevn_rewards_resources.h"
#include "components/grit/onevn_components_resources.h"
#else
#include "components/grit/components_resources.h"
#endif

namespace {

struct WebUISimpleItem {
  const char* name;
  int id;
};

void AddLocalizedStringsBulk(content::WebUIDataSource* html_source,
                             const std::vector<WebUISimpleItem>& simple_items) {
  for (size_t i = 0; i < simple_items.size(); i++) {
    html_source->AddLocalizedString(simple_items[i].name,
                                    simple_items[i].id);
  }
}

void AddResourcePaths(content::WebUIDataSource* html_source,
                      const std::vector<WebUISimpleItem>& simple_items) {
  for (size_t i = 0; i < simple_items.size(); i++) {
    html_source->AddResourcePath(simple_items[i].name,
                                 simple_items[i].id);
  }
}

}  // namespace

void CustomizeWebUIHTMLSource(const std::string &name,
    content::WebUIDataSource* source) {
  static std::map<std::string, std::vector<WebUISimpleItem> > resources = {
    {
      std::string("newtab"), {
        { "img/toolbar/menu_btn.svg", IDR_ONEVN_COMMON_TOOLBAR_IMG },
        // Hash path is the MD5 of the file contents,
        // webpack image loader does this
        { "fd85070af5114d6ac462c466e78448e4.svg", IDR_ONEVN_NEW_TAB_IMG1 },
        { "314e7529efec41c8867019815f4d8dad.svg", IDR_ONEVN_NEW_TAB_IMG4 },
        { "6c337c63662ee0ba4e57f6f8156d69ce.svg", IDR_ONEVN_NEW_TAB_IMG2 },
        // New tab Backgrounds
        { "ntp-1.webp", IDR_ONEVN_NEW_TAB_BACKGROUND1 },
        { "ntp-2.webp", IDR_ONEVN_NEW_TAB_BACKGROUND2 },
        { "ntp-3.webp", IDR_ONEVN_NEW_TAB_BACKGROUND3 },
        { "ntp-4.webp", IDR_ONEVN_NEW_TAB_BACKGROUND4 },
        { "ntp-5.webp", IDR_ONEVN_NEW_TAB_BACKGROUND5 },
        { "ntp-6.webp", IDR_ONEVN_NEW_TAB_BACKGROUND6 },
        { "ntp-7.webp", IDR_ONEVN_NEW_TAB_BACKGROUND7 },
        { "ntp-8.webp", IDR_ONEVN_NEW_TAB_BACKGROUND8 },
        { "ntp-9.webp", IDR_ONEVN_NEW_TAB_BACKGROUND9 },
        { "ntp-10.webp", IDR_ONEVN_NEW_TAB_BACKGROUND10 },
        { "ntp-11.webp", IDR_ONEVN_NEW_TAB_BACKGROUND11 },
        { "ntp-12.webp", IDR_ONEVN_NEW_TAB_BACKGROUND12 },
        { "ntp-13.webp", IDR_ONEVN_NEW_TAB_BACKGROUND13 },
        { "ntp-14.webp", IDR_ONEVN_NEW_TAB_BACKGROUND14 },
        { "ntp-15.webp", IDR_ONEVN_NEW_TAB_BACKGROUND15 },
        { "ntp-16.webp", IDR_ONEVN_NEW_TAB_BACKGROUND16 },

        // private tab
        { "c168145d6bf1abf2c0322636366f7dbe.svg", IDR_ONEVN_PRIVATE_TAB_TOR_IMG },               // NOLINT
        { "dbdc336ccc651b8a7c925b3482d6e65a.svg", IDR_ONEVN_PRIVATE_TAB_IMG }
      }
    }, {
      std::string("rewards"), {
        { "favicon.ico", IDR_ONEVN_REWARDS_FAVICON },
        { "4fcfa7f92c5fc22c2b6f34701bfdcd0a.jpeg", IDR_ONEVN_REWARDS_IMG_BART_TEMP },            // NOLINT
        { "6dd79d472f9c73429b26dae4ef14575e.svg", IDR_ONEVN_REWARDS_IMG_WALLET_BG },             // NOLINT
        { "c9255cc2aa3d81ca6328e82d25a95766.png", IDR_ONEVN_REWARDS_IMG_CAPTCHA_BAT },           // NOLINT
        { "1bb9aa85741c6d1c077f043324aae835.svg", IDR_ONEVN_REWARDS_IMG_WELCOME_BG },            // NOLINT
        { "88eeadb981d67d5e096afb9b8fe26df7.svg", IDR_ONEVN_REWARDS_IMG_BAT },
        { "87186eec176189163ce037bcc7676f2a.svg", IDR_ONEVN_REWARDS_IMG_BTC },
        { "7d9f0ededf215a4702ae5c457f7779ae.svg", IDR_ONEVN_REWARDS_IMG_ETH },
        { "2c6f798a519beabb327149c349912f5f.svg", IDR_ONEVN_REWARDS_IMG_LTC },
      }
    }, {
      std::string("welcome"), {
        { "favicon.ico", IDR_ONEVN_WELCOME_PAGE_FAVICON }
      }
    }, {
      std::string("adblock"), {
      }
    }, {
      std::string("donate"), {
        { "2e7994eaf768ee4a99272ea96cb39849.svg", IDR_ONEVN_DONATE_BG_1 },
        { "4364e454dba7ea966b117f643832e871.svg", IDR_ONEVN_DONATE_BG_2 },
      }
    }
  };
  AddResourcePaths(source, resources[name]);

  static std::map<std::string, std::vector<WebUISimpleItem> >
                                                           localized_strings = {
    {
      std::string("newtab"), {
        { "adsBlocked", IDS_ONEVN_NEW_TAB_TOTAL_ADS_BLOCKED },
        { "trackersBlocked", IDS_ONEVN_NEW_TAB_TOTAL_TRACKERS_BLOCKED },
        { "httpsUpgraded", IDS_ONEVN_NEW_TAB_TOTAL_HTTPS_UPGRADES },
        { "estimatedTimeSaved", IDS_ONEVN_NEW_TAB_TOTAL_TIME_SAVED },
        { "thumbRemoved", IDS_ONEVN_NEW_TAB_THUMB_REMOVED },
        { "undoRemoved", IDS_ONEVN_NEW_TAB_UNDO_REMOVED },
        { "close", IDS_ONEVN_NEW_TAB_CLOSE },
        { "restoreAll", IDS_ONEVN_NEW_TAB_RESTORE_ALL },
        { "second", IDS_ONEVN_NEW_TAB_SECOND },
        { "seconds", IDS_ONEVN_NEW_TAB_SECONDS },
        { "minute", IDS_ONEVN_NEW_TAB_MINUTE },
        { "minutes", IDS_ONEVN_NEW_TAB_MINUTES },
        { "hour", IDS_ONEVN_NEW_TAB_HOUR },
        { "hours", IDS_ONEVN_NEW_TAB_HOURS },
        { "day", IDS_ONEVN_NEW_TAB_DAY },
        { "days", IDS_ONEVN_NEW_TAB_DAYS },
        { "photoBy", IDS_ONEVN_NEW_TAB_PHOTO_BY },
        { "preferencesPageTitle", IDS_ONEVN_NEW_TAB_PREFERENCES_PAGE_TITLE },
        { "bookmarksPageTitle", IDS_ONEVN_NEW_TAB_BOOKMARKS_PAGE_TITLE },
        { "historyPageTitle", IDS_ONEVN_NEW_TAB_HISTORY_PAGE_TITLE },

        // Private Tab - General
        { "learnMore", IDS_ONEVN_PRIVATE_NEW_TAB_LEARN_MORE },
        { "done", IDS_ONEVN_PRIVATE_NEW_TAB_DONE },
        { "searchSettings", IDS_ONEVN_PRIVATE_NEW_TAB_SEARCH_SETTINGS },
        { "headerLabel", IDS_ONEVN_PRIVATE_NEW_TAB_THIS_IS_A },

        // Private Tab - Header Private Window
        { "headerTitle", IDS_ONEVN_PRIVATE_NEW_TAB_PRIVATE_WINDOW },
        { "headerText", IDS_ONEVN_PRIVATE_NEW_TAB_PRIVATE_WINDOW_DESC },
        { "headerButton", IDS_ONEVN_PRIVATE_NEW_TAB_PRIVATE_WINDOW_BUTTON },

        // Private Tab - Header Private Window with Tor
        { "headerTorTitle", IDS_ONEVN_PRIVATE_NEW_TAB_PRIVATE_WINDOW_TOR },
        { "headerTorText", IDS_ONEVN_PRIVATE_NEW_TAB_PRIVATE_WINDOW_TOR_DESC },
        { "headerTorButton", IDS_ONEVN_PRIVATE_NEW_TAB_PRIVATE_WIONDOW_TOR_BUTTON },             // NOLINT

        // Private Tab - Box for DDG
        { "boxDdgLabel", IDS_ONEVN_PRIVATE_NEW_TAB_BOX_DDG_LABEL },
        { "boxDdgTitle", IDS_ONEVN_PRIVATE_NEW_TAB_BOX_DDG_TITLE },
        { "boxDdgText", IDS_ONEVN_PRIVATE_NEW_TAB_BOX_DDG_TEXT_1 },
        { "boxDdgText2", IDS_ONEVN_PRIVATE_NEW_TAB_BOX_DDG_TEXT_2 },
        { "boxDdgButton", IDS_ONEVN_PRIVATE_NEW_TAB_BOX_DDG_BUTTON },

        // Private Tab - Box for Tor
        { "boxTorLabel", IDS_ONEVN_PRIVATE_NEW_TAB_BOX_TOR_LABEL },
        { "boxTorLabel2", IDS_ONEVN_PRIVATE_NEW_TAB_BOX_TOR_LABEL_2 },
        { "boxTorTitle", IDS_ONEVN_PRIVATE_NEW_TAB_BOX_TOR_TITLE },

        // Private Tab - Private Window with Tor - Tor Box
        { "boxTorText", IDS_ONEVN_PRIVATE_NEW_TAB_BOX_TOR_TEXT_1 },

        // Private Tab - Private Window - Tor Box
        { "boxTorText2", IDS_ONEVN_PRIVATE_NEW_TAB_BOX_TOR_TEXT_2 },
        { "boxTorButton", IDS_ONEVN_PRIVATE_NEW_TAB_BOX_TOR_BUTTON }
      }
    }, {
      std::string("welcome"), {
        { "welcome", IDS_ONEVN_WELCOME_PAGE_MAIN_TITLE },
        { "whatIsOnevn", IDS_ONEVN_WELCOME_PAGE_MAIN_DESC },
        { "letsGo", IDS_ONEVN_WELCOME_PAGE_MAIN_BUTTON },
        { "enableOnevnRewards", IDS_ONEVN_WELCOME_PAGE_REWARDS_TITLE },
        { "setupOnevnRewards", IDS_ONEVN_WELCOME_PAGE_REWARDS_DESC },
        { "enableRewards", IDS_ONEVN_WELCOME_PAGE_REWARDS_BUTTON },
        { "importFromAnotherBrowser", IDS_ONEVN_WELCOME_PAGE_IMPORT_TITLE },
        { "setupImport", IDS_ONEVN_WELCOME_PAGE_IMPORT_DESC },
        { "import", IDS_ONEVN_WELCOME_PAGE_IMPORT_BUTTON },
        { "manageShields", IDS_ONEVN_WELCOME_PAGE_SHIELDS_TITLE },
        { "adjustProtectionLevel", IDS_ONEVN_WELCOME_PAGE_SHIELDS_DESC },
        { "shieldSettings", IDS_ONEVN_WELCOME_PAGE_SHIELDS_BUTTON },
        { "setDefaultSearchEngine", IDS_ONEVN_WELCOME_PAGE_SEARCH_TITLE },
        { "chooseSearchEngine", IDS_ONEVN_WELCOME_PAGE_SEARCH_DESC },
        { "search", IDS_ONEVN_WELCOME_PAGE_SEARCH_BUTTON },
        { "findToolbarTheme", IDS_ONEVN_WELCOME_PAGE_THEME_TITLE },
        { "chooseTheme", IDS_ONEVN_WELCOME_PAGE_THEME_DESC },
        { "theme", IDS_ONEVN_WELCOME_PAGE_THEME_BUTTON },
        { "skipWelcomeTour", IDS_ONEVN_WELCOME_PAGE_SKIP_BUTTON },
        { "next", IDS_ONEVN_WELCOME_PAGE_NEXT_BUTTON },
        { "done", IDS_ONEVN_WELCOME_PAGE_DONE_BUTTON },
      }
    }, {
      std::string("rewards"), {
        { "adsCurrentEarnings",  IDS_ONEVN_REWARDS_LOCAL_ADS_CURRENT_EARNINGS },
        { "adsDesc",  IDS_ONEVN_REWARDS_LOCAL_ADS_DESC },
        { "adsDisabledTextOne",  IDS_ONEVN_REWARDS_LOCAL_ADS_DISABLED_TEXT_ONE },                // NOLINT
        { "adsDisabledTextTwo",  IDS_ONEVN_REWARDS_LOCAL_ADS_DISABLED_TEXT_TWO },                // NOLINT
        { "adsNotificationsReceived",  IDS_ONEVN_REWARDS_LOCAL_ADS_NOTIFICATIONS_RECEIVED },     // NOLINT
        { "adsNotSupported", IDS_ONEVN_REWARDS_LOCAL_ADS_NOT_SUPPORTED },
        { "adsPaymentDate",  IDS_ONEVN_REWARDS_LOCAL_ADS_PAYMENT_DATE },
        { "adsPagesViewed",  IDS_ONEVN_REWARDS_LOCAL_ADS_PAGES_VIEWED },
        { "adsPerHour",  IDS_ONEVN_REWARDS_LOCAL_ADS_PER_HOUR },
        { "adsPerHour1",  IDS_ONEVN_REWARDS_LOCAL_ADS_PER_HOUR_1 },
        { "adsPerHour2",  IDS_ONEVN_REWARDS_LOCAL_ADS_PER_HOUR_2 },
        { "adsPerHour3",  IDS_ONEVN_REWARDS_LOCAL_ADS_PER_HOUR_3 },
        { "adsPerHour4",  IDS_ONEVN_REWARDS_LOCAL_ADS_PER_HOUR_4 },
        { "adsPerHour5",  IDS_ONEVN_REWARDS_LOCAL_ADS_PER_HOUR_5 },
        { "adsTitle",  IDS_ONEVN_REWARDS_LOCAL_ADS_TITLE },

        { "bat", IDS_ONEVN_UI_BAT_REWARDS_TEXT },
        { "contributionTitle",  IDS_ONEVN_REWARDS_LOCAL_CONTR_TITLE },
        { "contributionDesc",  IDS_ONEVN_REWARDS_LOCAL_CONTR_DESC },
        { "contributionMonthly",  IDS_ONEVN_REWARDS_LOCAL_CONTR_MONTHLY },
        { "contributionNextDate",  IDS_ONEVN_REWARDS_LOCAL_CONTR_NEXT_DATE },
        { "contributionSites",  IDS_ONEVN_REWARDS_LOCAL_CONTR_SITES },
        { "contributionDisabledText1",  IDS_ONEVN_REWARDS_LOCAL_CONTR_DISABLED_TEXT1 },          // NOLINT
        { "contributionDisabledText2",  IDS_ONEVN_REWARDS_LOCAL_CONTR_DISABLED_TEXT2 },          // NOLINT
        { "contributionVisitSome",  IDS_ONEVN_REWARDS_LOCAL_CONTR_VISIT_SOME },
        { "contributionMinTime",  IDS_ONEVN_REWARDS_LOCAL_CONTR_MIN_TIME },
        { "contributionMinVisits",  IDS_ONEVN_REWARDS_LOCAL_CONTR_MIN_VISITS },
        { "contributionAllowed",  IDS_ONEVN_REWARDS_LOCAL_CONTR_ALLOWED },
        { "contributionNonVerified",  IDS_ONEVN_REWARDS_LOCAL_CONTR_ALLOW_NON_VERIFIED },        // NOLINT
        { "contributionVideos",  IDS_ONEVN_REWARDS_LOCAL_CONTR_ALLOW_VIDEOS },
        { "contributionVisit1",  IDS_ONEVN_REWARDS_LOCAL_CONTR_VISIT_1 },
        { "contributionVisit5",  IDS_ONEVN_REWARDS_LOCAL_CONTR_VISIT_5 },
        { "contributionVisit10",  IDS_ONEVN_REWARDS_LOCAL_CONTR_VISIT_10 },
        { "contributionTime5",  IDS_ONEVN_REWARDS_LOCAL_CONTR_TIME_5 },
        { "contributionTime8",  IDS_ONEVN_REWARDS_LOCAL_CONTR_TIME_8 },
        { "contributionTime60",  IDS_ONEVN_REWARDS_LOCAL_CONTR_TIME_60 },

        { "deviceOffline", IDS_ONEVN_REWARDS_LOCAL_DEVICE_OFFLINE },
        { "donationTitle",  IDS_ONEVN_REWARDS_LOCAL_DONAT_TITLE },
        { "donationDesc",  IDS_ONEVN_REWARDS_LOCAL_DONAT_DESC },
        { "donationTotalDonations",  IDS_ONEVN_REWARDS_LOCAL_DONAT_TOTAL_DONATIONS },            // NOLINT
        { "donationVisitSome",  IDS_ONEVN_REWARDS_LOCAL_DONAT_VISIT_SOME },
        { "donationAbility",  IDS_ONEVN_REWARDS_LOCAL_DONAT_ABILITY },
        { "donationAbilityYT",  IDS_ONEVN_REWARDS_LOCAL_DONAT_ABILITY_YT },
        { "donationAbilityTwitter",  IDS_ONEVN_REWARDS_LOCAL_DONAT_ABILITY_TW },
        { "donationDisabledText1",  IDS_ONEVN_REWARDS_LOCAL_DONAT_DISABLED_TEXT1 },              // NOLINT
        { "donationDisabledText2",  IDS_ONEVN_REWARDS_LOCAL_DONAT_DISABLED_TEXT2 },              // NOLINT
        { "donationNextDate",  IDS_ONEVN_REWARDS_LOCAL_DONAT_NEXT_DATE },

        { "panelAddFunds",  IDS_ONEVN_REWARDS_LOCAL_PANEL_ADD_FUNDS },
        { "panelWithdrawFunds",  IDS_ONEVN_REWARDS_LOCAL_PANEL_WITHDRAW_FUNDS },
        { "tokens",  IDS_ONEVN_REWARDS_LOCAL_TOKENS },
        { "walletRecoverySuccess",  IDS_ONEVN_REWARDS_LOCAL_WALLET_RECOVERY_SUCCESS },           // NOLINT
        { "walletRestored",  IDS_ONEVN_REWARDS_LOCAL_WALLET_RESTORED },
        { "walletRecoveryFail",  IDS_ONEVN_REWARDS_LOCAL_WALLET_RECOVERY_FAIL },                 // NOLINT
        { "almostThere",  IDS_ONEVN_REWARDS_LOCAL_ALMOST_THERE },
        { "notQuite",  IDS_ONEVN_REWARDS_LOCAL_NOT_QUITE },
        { "proveHuman",  IDS_ONEVN_REWARDS_LOCAL_PROVE_HUMAN },
        { "serverNotResponding",  IDS_ONEVN_REWARDS_LOCAL_SERVER_NOT_RESPONDING },               // NOLINT
        { "uhOh",  IDS_ONEVN_REWARDS_LOCAL_UH_OH },
        { "grantGoneTitle",  IDS_ONEVN_REWARDS_LOCAL_GRANT_GONE_TITLE },
        { "grantGoneButton",  IDS_ONEVN_REWARDS_LOCAL_GRANT_GONE_BUTTON },
        { "grantGoneText",  IDS_ONEVN_REWARDS_LOCAL_GRANT_GONE_TEXT },
        { "grantGeneralErrorTitle",  IDS_ONEVN_REWARDS_LOCAL_GENERAL_GRANT_ERROR_TITLE },        // NOLINT
        { "grantGeneralErrorButton",  IDS_ONEVN_REWARDS_LOCAL_GENERAL_GRANT_ERROR_BUTTON },      // NOLINT
        { "grantGeneralErrorText",  IDS_ONEVN_REWARDS_LOCAL_GENERAL_GRANT_ERROR_TEXT },          // NOLINT
        { "walletCorrupted",  IDS_ONEVN_REWARDS_LOCAL_WALLET_CORRUPTED },
        { "walletCorruptedNow",  IDS_ONEVN_REWARDS_LOCAL_WALLET_CORRUPTED_NOW },
        { "grantAlreadyClaimedText", IDS_ONEVN_REWARDS_LOCAL_GRANT_ALREADY_CLAIMED_TEXT },       // NOLINT

        { "about", IDS_ONEVN_UI_ABOUT },
        { "accept", IDS_ONEVN_UI_ACCEPT },
        { "activityCopy", IDS_ONEVN_UI_ACTIVITY_COPY },
        { "activityNote", IDS_ONEVN_UI_ACTIVITY_NOTE },
        { "addFunds", IDS_ONEVN_UI_ADD_FUNDS },
        { "addFundsFAQ", IDS_ONEVN_UI_ADD_FUNDS_FAQ},
        { "addFundsNote", IDS_ONEVN_UI_ADD_FUNDS_NOTE},
        { "addFundsQR", IDS_ONEVN_UI_ADD_FUNDS_QR},
        { "addFundsText", IDS_ONEVN_UI_ADD_FUNDS_TEXT},
        { "addFundsTitle", IDS_ONEVN_UI_ADD_FUNDS_TITLE},
        { "adsEarnings", IDS_ONEVN_UI_ADS_EARNINGS },
        { "allowTip", IDS_ONEVN_UI_ALLOW_TIP },
        { "amount", IDS_ONEVN_UI_AMOUNT },
        { "backup", IDS_ONEVN_UI_BACKUP },
        { "onevnAdsDesc", IDS_ONEVN_UI_ONEVN_ADS_DESC },
        { "onevnAdsLaunchMsg", IDS_ONEVN_UI_ONEVN_ADS_LAUNCH_MSG },
        { "onevnAdsLaunchTitle", IDS_ONEVN_UI_ONEVN_ADS_LAUNCH_TITLE },
        { "onevnAdsTitle", IDS_ONEVN_UI_ONEVN_ADS_TITLE },
        { "onevnContributeDesc", IDS_ONEVN_UI_ONEVN_CONTRIBUTE_DESC },
        { "onevnContributeTitle", IDS_ONEVN_UI_ONEVN_CONTRIBUTE_TITLE },
        { "onevnRewards", IDS_ONEVN_UI_ONEVN_REWARDS },
        { "onevnRewardsCreatingText", IDS_ONEVN_UI_ONEVN_REWARDS_CREATING_TEXT },                // NOLINT
        { "onevnRewardsDesc", IDS_ONEVN_UI_ONEVN_REWARDS_DESC },
        { "onevnRewardsOptInText", IDS_ONEVN_UI_ONEVN_REWARDS_OPT_IN_TEXT },
        { "onevnRewardsSubTitle", IDS_ONEVN_UI_ONEVN_REWARDS_SUB_TITLE },
        { "onevnRewardsTeaser", IDS_ONEVN_UI_ONEVN_REWARDS_TEASER },
        { "onevnRewardsTitle", IDS_ONEVN_UI_ONEVN_REWARDS_TITLE },
        { "onevnVerified", IDS_ONEVN_UI_ONEVN_VERIFIED },
        { "cancel", IDS_ONEVN_UI_CANCEL },
        { "captchaDrag", IDS_ONEVN_UI_CAPTCHA_DRAG },
        { "captchaLuckyDay", IDS_ONEVN_UI_CAPTCHA_LUCKY_DAY },
        { "captchaOnTheWay", IDS_ONEVN_UI_CAPTCHA_ON_THE_WAY },
        { "captchaProveHuman", IDS_ONEVN_UI_CAPTCHA_PROVE_HUMAN },
        { "captchaTarget", IDS_ONEVN_UI_CAPTCHA_TARGET },
        { "captchaMissedTarget", IDS_ONEVN_UI_CAPTCHA_MISSED_TARGET },
        { "claim", IDS_ONEVN_UI_CLAIM },
        { "closeBalance", IDS_ONEVN_UI_CLOSE_BALANCE },
        { "contribute", IDS_ONEVN_UI_CONTRIBUTE },
        { "contributeAllocation", IDS_ONEVN_UI_CONTRIBUTE_ALLOCATION },
        { "copy", IDS_ONEVN_UI_COPY },
        { "currentDonation", IDS_ONEVN_UI_CURRENT_DONATION },
        { "date", IDS_ONEVN_UI_DATE },
        { "deposit", IDS_ONEVN_UI_DEPOSIT },
        { "deposits", IDS_ONEVN_UI_DEPOSITS },
        { "description", IDS_ONEVN_UI_DESCRIPTION },
        { "disabledPanelOff", IDS_ONEVN_UI_DISABLED_PANEL_OFF },
        { "disabledPanelSettings", IDS_ONEVN_UI_DISABLED_PANEL_SETTINGS },
        { "disabledPanelText", IDS_ONEVN_UI_DISABLED_PANEL_TEXT },
        { "disabledPanelTitle", IDS_ONEVN_UI_DISABLED_PANEL_TITLE },
        { "dndCaptchaText1", IDS_ONEVN_UI_DND_CAPTCHA_TEXT_1 },
        { "dndCaptchaText2", IDS_ONEVN_UI_DND_CAPTCHA_TEXT_2 },
        { "donation", IDS_ONEVN_UI_DONATION },
        { "donationAmount", IDS_ONEVN_UI_DONATION_AMOUNT },
        { "donationTips", IDS_ONEVN_REWARDS_LOCAL_DONAT_TITLE },
        { "donateMonthly", IDS_ONEVN_UI_DONATE_MONTHLY },
        { "donateNow", IDS_ONEVN_UI_DONATE_NOW },
        { "done", IDS_ONEVN_UI_DONE },
        { "downloadPDF", IDS_ONEVN_UI_DOWNLOAD_PDF },
        { "earningsAds", IDS_ONEVN_UI_EARNINGS_ADS },
        { "earningsClaimDefault", IDS_ONEVN_UI_EARNINGS_CLAIM_DEFAULT },
        { "enableTips", IDS_ONEVN_UI_ENABLE_TIPS },
        { "excludeSite", IDS_ONEVN_UI_EXCLUDE_SITE },
        { "excludedSitesText", IDS_ONEVN_UI_EXCLUDED_SITES },
        { "expiresOn", IDS_ONEVN_UI_EXPIRES_ON },
        { "for", IDS_ONEVN_UI_FOR },
        { "grantDisclaimer", IDS_ONEVN_UI_GRANT_DISCLAIMER },
        { "grantExpire", IDS_ONEVN_UI_GRANT_EXPIRE },
        { "grants", IDS_ONEVN_UI_GRANTS },
        { "import", IDS_ONEVN_UI_IMPORT },
        { "includeInAuto", IDS_ONEVN_UI_INCLUDE_IN_AUTO },
        { "learnMore", IDS_ONEVN_UI_LEARN_MORE },
        { "makeMonthly", IDS_ONEVN_UI_MAKE_MONTHLY },
        { "manageWallet", IDS_ONEVN_UI_MANAGE_WALLET },
        { "monthApr", IDS_ONEVN_UI_MONTH_APR },
        { "monthAug", IDS_ONEVN_UI_MONTH_AUG },
        { "monthDec", IDS_ONEVN_UI_MONTH_DEC },
        { "monthFeb", IDS_ONEVN_UI_MONTH_FEB },
        { "monthJan", IDS_ONEVN_UI_MONTH_JAN },
        { "monthJul", IDS_ONEVN_UI_MONTH_JUL },
        { "monthJun", IDS_ONEVN_UI_MONTH_JUN },
        { "monthMar", IDS_ONEVN_UI_MONTH_MAR },
        { "monthMay", IDS_ONEVN_UI_MONTH_MAY },
        { "monthNov", IDS_ONEVN_UI_MONTH_NOV },
        { "monthOct", IDS_ONEVN_UI_MONTH_OCT },
        { "monthSep", IDS_ONEVN_UI_MONTH_SEP },
        { "monthlyTips", IDS_ONEVN_UI_MONTHLY_TIPS },
        { "newGrant", IDS_ONEVN_UI_NEW_GRANT },
        { "newTokenGrant", IDS_ONEVN_UI_NEW_TOKEN_GRANT },
        { "noActivity", IDS_ONEVN_UI_NO_ACTIVITY },
        { "noGrants", IDS_ONEVN_UI_NO_GRANTS },
        { "notEnoughTokens", IDS_ONEVN_UI_NOT_ENOUGH_TOKENS },
        { "noThankYou", IDS_ONEVN_UI_NO_THANK_YOU },
        { "off", IDS_ONEVN_UI_OFF },
        { "ok", IDS_ONEVN_UI_OK },
        { "on", IDS_ONEVN_UI_ON },
        { "oneTime", IDS_ONEVN_UI_ONE_TIME },
        { "oneTimeDonation", IDS_ONEVN_UI_ONE_TIME_DONATION },
        { "openBalance", IDS_ONEVN_UI_OPEN_BALANCE },
        { "payment", IDS_ONEVN_UI_PAYMENT },
        { "paymentMonthly", IDS_ONEVN_UI_PAYMENT_MONTHLY },
        { "paymentNotMade", IDS_ONEVN_UI_PAYMENT_NOT_MADE },
        { "paymentWarning", IDS_ONEVN_UI_PAYMENT_WARNING },
        { "pinnedSitesHeader", IDS_ONEVN_UI_PAYMENT_PINNED_SITES_HEADER },
        { "pinnedSitesMsg", IDS_ONEVN_UI_PAYMENT_PINNED_SITES_MSG },
        { "pinnedSitesOne", IDS_ONEVN_UI_PAYMENT_PINNED_SITES_ONE },
        { "pinnedSitesTwo", IDS_ONEVN_UI_PAYMENT_PINNED_SITES_TWO },
        { "pinnedSitesThree", IDS_ONEVN_UI_PAYMENT_PINNED_SITES_THREE },
        { "pinnedSitesFour", IDS_ONEVN_UI_PAYMENT_PINNED_SITES_FOUR },
        { "pleaseNote", IDS_ONEVN_UI_PLEASE_NOTE },
        { "print", IDS_ONEVN_UI_PRINT },
        { "readyToTakePart", IDS_ONEVN_UI_READY_TO_TAKE_PART },
        { "readyToTakePartOptInText", IDS_ONEVN_UI_READY_TO_TAKE_PART_OPT_IN_TEXT },             // NOLINT
        { "readyToTakePartStart", IDS_ONEVN_UI_READY_TO_TAKE_PART_START },
        { "recoveryKeys", IDS_ONEVN_UI_RECOVERY_KEYS },
        { "recurring", IDS_ONEVN_UI_RECURRING },
        { "recurringDonation", IDS_ONEVN_UI_RECURRING_DONATION },
        { "recurringDonations", IDS_ONEVN_UI_RECURRING_DONATIONS },
        { "remove", IDS_ONEVN_UI_REMOVE },
        { "reservedAmountText", IDS_ONEVN_UI_RESERVED_AMOUNT_TEXT },
        { "reservedMoreLink", IDS_ONEVN_UI_RESERVED_MORE_LINK },
        { "restore", IDS_ONEVN_UI_RESTORE },
        { "restoreAll", IDS_ONEVN_UI_RESTORE_ALL },
        { "reviewSitesMsg", IDS_ONEVN_UI_REVIEW_SITE_MSG },
        { "rewardsBackupText1", IDS_ONEVN_UI_REWARDS_BACKUP_TEXT1 },
        { "rewardsBackupText2", IDS_ONEVN_UI_REWARDS_BACKUP_TEXT2 },
        { "rewardsBackupText3", IDS_ONEVN_UI_REWARDS_BACKUP_TEXT3 },
        { "rewardsBannerText1", IDS_ONEVN_UI_REWARDS_BANNER_TEXT1 },
        { "rewardsBannerText2", IDS_ONEVN_UI_REWARDS_BANNER_TEXT2 },
        { "rewardsContribute", IDS_ONEVN_UI_REWARDS_CONTRIBUTE },
        { "rewardsContributeAttention", IDS_ONEVN_UI_REWARDS_CONTRIBUTE_ATTENTION },             // NOLINT
        { "rewardsContributeAttentionScore", IDS_ONEVN_UI_REWARDS_CONTRIBUTE_ATTENTION_SCORE },  // NOLINT
        { "rewardsContributeText1", IDS_ONEVN_UI_REWARDS_CONTRIBUTE_TEXT1 },
        { "rewardsOffText2", IDS_ONEVN_UI_REWARDS_OFF_TEXT2 },
        { "rewardsOffText3", IDS_ONEVN_UI_REWARDS_OFF_TEXT3 },
        { "rewardsOffText4", IDS_ONEVN_UI_REWARDS_OFF_TEXT4 },
        { "rewardsPanelEmptyText1", IDS_ONEVN_UI_REWARDS_PANEL_EMPTY_TEXT1 },
        { "rewardsPanelEmptyText2", IDS_ONEVN_UI_REWARDS_PANEL_EMPTY_TEXT2 },
        { "rewardsPanelEmptyText3", IDS_ONEVN_UI_REWARDS_PANEL_EMPTY_TEXT3 },
        { "rewardsPanelEmptyText4", IDS_ONEVN_UI_REWARDS_PANEL_EMPTY_TEXT4 },
        { "rewardsPanelEmptyText5", IDS_ONEVN_UI_REWARDS_PANEL_EMPTY_TEXT5 },
        { "rewardsPanelOffText1", IDS_ONEVN_UI_REWARDS_PANEL_OFF_TEXT1 },
        { "rewardsPanelOffText2", IDS_ONEVN_UI_REWARDS_PANEL_OFF_TEXT2 },
        { "rewardsPanelText1", IDS_ONEVN_UI_REWARDS_PANEL_TEXT1 },
        { "rewardsPanelText2", IDS_ONEVN_UI_REWARDS_PANEL_TEXT2 },
        { "rewardsPanelText3", IDS_ONEVN_UI_REWARDS_PANEL_TEXT3 },
        { "rewardsPanelText4", IDS_ONEVN_UI_REWARDS_PANEL_TEXT4 },
        { "rewardsRestoreText1", IDS_ONEVN_UI_REWARDS_RESTORE_TEXT1 },
        { "rewardsRestoreText2", IDS_ONEVN_UI_REWARDS_RESTORE_TEXT2 },
        { "rewardsRestoreText3", IDS_ONEVN_UI_REWARDS_RESTORE_TEXT3 },
        { "rewardsRestoreText4", IDS_ONEVN_UI_REWARDS_RESTORE_TEXT4 },
        { "rewardsSummary", IDS_ONEVN_UI_REWARDS_SUMMARY },
        { "rewardsWhy", IDS_ONEVN_UI_REWARDS_WHY },
        { "saveAsFile", IDS_ONEVN_UI_SAVE_AS_FILE },
        { "seeAllItems", IDS_ONEVN_UI_SEE_ALL_ITEMS },
        { "seeAllSites", IDS_ONEVN_UI_SEE_ALL_SITES },
        { "sendDonation", IDS_ONEVN_UI_SEND_DONATION },
        { "sendTip", IDS_ONEVN_UI_SEND_TIP },
        { "settings", IDS_ONEVN_UI_SETTINGS },
        { "site", IDS_ONEVN_UI_SITE },
        { "sites", IDS_ONEVN_UI_SITES },
        { "tipOnLike", IDS_ONEVN_UI_TIP_ON_LIKE },
        { "titleBAT", IDS_ONEVN_UI_TITLE_BAT},
        { "titleBTC", IDS_ONEVN_UI_TITLE_BTC},
        { "titleETH", IDS_ONEVN_UI_TITLE_ETH},
        { "titleLTC", IDS_ONEVN_UI_TITLE_LTC},
        { "tokenGrantClaimed", IDS_ONEVN_UI_TOKEN_GRANT_CLAIMED },
        { "tokens", IDS_ONEVN_UI_TOKENS },
        { "total", IDS_ONEVN_UI_TOTAL },
        { "transactions", IDS_ONEVN_UI_TRANSACTIONS },
        { "turnOnAds", IDS_ONEVN_UI_TURN_ON_ADS },
        { "turnOnRewardsDesc", IDS_ONEVN_UI_TURN_ON_REWARDS_DESC },
        { "turnOnRewardsTitle", IDS_ONEVN_UI_TURN_ON_REWARDS_TITLE },
        { "type", IDS_ONEVN_UI_TYPE },
        { "verifiedPublisher", IDS_ONEVN_UI_VERIFIED_PUBLISHER },
        { "viewMonthly", IDS_ONEVN_UI_VIEW_MONTHLY },
        { "walletActivity", IDS_ONEVN_UI_WALLET_ACTIVITY },
        { "walletAddress", IDS_ONEVN_UI_WALLET_ADDRESS },
        { "walletBalance", IDS_ONEVN_UI_WALLET_BALANCE },
        { "walletFailedButton", IDS_ONEVN_UI_WALLET_FAILED_BUTTON },
        { "walletFailedTitle", IDS_ONEVN_UI_WALLET_FAILED_TITLE },
        { "walletFailedText", IDS_ONEVN_UI_WALLET_FAILED_TEXT },
        { "welcome", IDS_ONEVN_UI_WELCOME },
        { "welcomeButtonTextOne", IDS_ONEVN_UI_WELCOME_BUTTON_TEXT_ONE},
        { "welcomeButtonTextTwo", IDS_ONEVN_UI_WELCOME_BUTTON_TEXT_TWO},
        { "welcomeDescOne", IDS_ONEVN_UI_WELCOME_DESC_ONE},
        { "welcomeDescTwo", IDS_ONEVN_UI_WELCOME_DESC_TWO},
        { "welcomeFooterTextOne", IDS_ONEVN_UI_WELCOME_FOOTER_TEXT_ONE},
        { "welcomeFooterTextTwo", IDS_ONEVN_UI_WELCOME_FOOTER_TEXT_TWO},
        { "welcomeHeaderOne", IDS_ONEVN_UI_WELCOME_HEADER_ONE},
        { "welcomeHeaderTwo", IDS_ONEVN_UI_WELCOME_HEADER_TWO},
        { "whyOnevnRewards", IDS_ONEVN_UI_WHY_ONEVN_REWARDS },
        { "whyOnevnRewardsDesc1", IDS_ONEVN_UI_WHY_ONEVN_REWARDS_DESC_1 },
        { "whyOnevnRewardsDesc2", IDS_ONEVN_UI_WHY_ONEVN_REWARDS_DESC_2 },
        { "yourWallet", IDS_ONEVN_UI_YOUR_WALLET },

        { "and", IDS_ONEVN_UI_AND },
        { "privacyPolicy", IDS_ONEVN_UI_PRIVACY_POLICY },
        { "rewardsOffText5", IDS_ONEVN_UI_REWARDS_OFF_TEXT5 },
        { "serviceTextToggle", IDS_ONEVN_UI_SERVICE_TEXT_TOGGLE },
        { "serviceTextWelcome", IDS_ONEVN_UI_SERVICE_TEXT_WELCOME },
        { "termsOfService", IDS_ONEVN_UI_TERMS_OF_SERVICE }
      }
    }, {
      std::string("sync"), {
        // Shared strings
        { "remove", IDS_ONEVN_SYNC_SHARED_REMOVE_PARTIAL },
        { "copied", IDS_ONEVN_SYNC_SHARED_COPIED_TEXT },
        { "wordCount",  IDS_ONEVN_SYNC_SHARED_WORD_COUNT_TEXT },
        { "ok", IDS_ONEVN_SYNC_SHARED_OK_BUTTON },
        { "cancel", IDS_ONEVN_SYNC_SHARED_CANCEL_BUTTON },
        { "cancelDeviceSyncing", IDS_ONEVN_SYNC_SHARED_CANCEL_SYNCING_TITLE },
        { "cancelDeviceSyncingButton", IDS_ONEVN_SYNC_SHARED_CANCEL_SYNCING_BUTTON },            // NOLINT
        { "thisSyncChain", IDS_ONEVN_SYNC_SHARED_FROM_THIS_CHAIN_PARTIAL },
        { "lookingForDevice", IDS_ONEVN_SYNC_SCAN_CODE_LOOKING_FOR_DEVICE_BUTTON },              // NOLINT
        { "viewSyncCode", IDS_ONEVN_SYNC_ENABLED_VIEW_CODE_BUTTON },
        // Enabled Content
        { "onevnSync", IDS_ONEVN_SYNC_ENABLED_ONEVN_TITLE },
        { "syncChainDevices", IDS_ONEVN_SYNC_ENABLED_DEVICES_CHAIN_TITLE },
        { "deviceName", IDS_ONEVN_SYNC_ENABLED_TABLE_DEVICE_NAME_TITLE },
        { "thisDevice", IDS_ONEVN_SYNC_ENABLED_TABLE_THIS_DEVICE_TEXT },
        { "addedOn", IDS_ONEVN_SYNC_ENABLED_TABLE_ADDED_ON_TITLE },
        { "addDevice", IDS_ONEVN_SYNC_ENABLED_ADD_DEVICE_BUTTON },
        { "settingsTitle", IDS_ONEVN_SYNC_ENABLED_SETTINGS_TITLE },
        { "settingsDescription", IDS_ONEVN_SYNC_ENABLED_SETTINGS_DESCRIPTION },
        { "settings", IDS_ONEVN_SYNC_ENABLED_TABLE_SETTINGS },
        { "bookmarks", IDS_ONEVN_SYNC_ENABLED_BOOKMARKS_LABEL },
        { "savedSiteSettings", IDS_ONEVN_SYNC_ENABLED_SITE_SETTINGS_LABEL },
        { "browsingHistory", IDS_ONEVN_SYNC_ENABLED_HISTORY_LABEL },
        { "leaveSyncChain", IDS_ONEVN_SYNC_ENABLED_LEAVE_CHAIN_BUTTON },
        // Disabled Content
        { "syncTitle", IDS_ONEVN_SYNC_DISABLED_DESCRIPTION },
        { "syncDescription", IDS_ONEVN_SYNC_DISABLED_NEW_CHAIN_DESCRIPTION },
        { "startSyncChain", IDS_ONEVN_SYNC_DISABLED_START_NEW_CHAIN_BUTTON },
        { "enterSyncChainCode", IDS_ONEVN_SYNC_DISABLED_ENTER_CODE_BUTTON },
        // [modal] Enter Sync Code
        { "enterSyncCode", IDS_ONEVN_SYNC_ENTER_CODE_TITLE },
        { "enterSyncCodeDescription", IDS_ONEVN_SYNC_ENTER_CODE_DESCRIPTION },
        { "confirmCode", IDS_ONEVN_SYNC_ENTER_CODE_CONFIRM_CODE_BUTTON },
        // [modal] Remove Main Device
        { "thisDeviceRemovalDescription", IDS_ONEVN_SYNC_REMOVE_THIS_DEVICE_DESCRIPTION },       // NOLINT
        { "joinSyncChain", IDS_ONEVN_SYNC_REMOVE_THIS_DEVICE_JOIN_CHAIN_INSTRUCTIONS },          // NOLINT
        // [modal] Remove Other Device
        { "otherDeviceRemovalDescription", IDS_ONEVN_SYNC_REMOVE_OTHER_DEVICE_DESCRIPTION },     // NOLINT
        // [modal] Reset Sync
        { "warning", IDS_ONEVN_SYNC_RESET_WARNING_TITLE },
        { "removing", IDS_ONEVN_SYNC_RESET_REMOVING_PARTIAL },
        { "deleteSyncChain", IDS_ONEVN_SYNC_RESET_DELETE_CHAIN_PARTIAL },
        { "deleteSyncDescription", IDS_ONEVN_SYNC_RESET_REMOVAL_INSTRUCTIONS },
        { "startSyncChainHowTo", IDS_ONEVN_SYNC_RESET_START_NEW_INSTRUCTIONS },
        { "areYouSure", IDS_ONEVN_SYNC_RESET_ARE_YOU_SURE_TITLE },
        // [modal] Scan Code
        { "scanThisCode", IDS_ONEVN_SYNC_SCAN_CODE_TITLE },
        { "scanThisCodeHowToPartial1", IDS_ONEVN_SYNC_SCAN_CODE_DESCRIPTION_PARTIAL_1 },         // NOLINT
        { "scanThisCodeHowToPartial2", IDS_ONEVN_SYNC_SCAN_CODE_DESCRIPTION_PARTIAL_2 },         // NOLINT
        { "scanThisCodeHowToPartial3", IDS_ONEVN_SYNC_SCAN_CODE_DESCRIPTION_PARTIAL_3 },         // NOLINT
        // [modal] View Code
        { "chainCode", IDS_ONEVN_SYNC_VIEW_CODE_TITLE },
        { "chainCodeDescriptionPartial1", IDS_ONEVN_SYNC_VIEW_CODE_DESCRIPTION_PARTIAL_1 },      // NOLINT
        { "chainCodeDescriptionPartial2", IDS_ONEVN_SYNC_VIEW_CODE_DESCRIPTION_PARTIAL_2 },      // NOLINT
        { "chainCodeDescriptionPartial3", IDS_ONEVN_SYNC_VIEW_CODE_DESCRIPTION_PARTIAL_3 },      // NOLINT
        { "useCameraInstead", IDS_ONEVN_SYNC_VIEW_CODE_USE_CAMERA_BUTTON },
        { "qrCode", IDS_ONEVN_SYNC_VIEW_CODE_QR_CODE },
        // [modal] Choose Device Type
        { "letsSync", IDS_ONEVN_SYNC_CHOOSE_DEVICE_TITLE },
        { "chooseDeviceType", IDS_ONEVN_SYNC_CHOOSE_DEVICE_DESCRIPTION },
        { "phoneTablet", IDS_ONEVN_SYNC_CHOOSE_DEVICE_MOBILE_TITLE },
        { "computer", IDS_ONEVN_SYNC_CHOOSE_DEVICE_COMPUTER_TITLE },
        // errors
        { "errorWrongCodeTitle", IDS_ONEVN_SYNC_ERROR_WRONG_CODE_TITLE },
        { "errorWrongCodeDescription", IDS_ONEVN_SYNC_ERROR_WRONG_CODE_DESCRIPTION },            // NOLINT
        { "errorMissingDeviceNameTitle", IDS_ONEVN_SYNC_ERROR_MISSING_DEVICE_NAME_TITLE },       // NOLINT
        { "errorMissingCodeTitle", IDS_ONEVN_SYNC_ERROR_MISSING_SYNC_CODE_TITLE },               // NOLINT
        { "errorSyncInitFailedTitle", IDS_ONEVN_SYNC_ERROR_INIT_FAILED_TITLE },
        { "errorSyncInitFailedDescription", IDS_ONEVN_SYNC_ERROR_INIT_FAILED_DESCRIPTION },      // NOLINT
        { "errorSyncRequiresCorrectTimeTitle", IDS_ONEVN_SYNC_REQUIRES_CORRECT_TIME_TITLE },     // NOLINT
        { "errorSyncRequiresCorrectTimeDescription", IDS_ONEVN_SYNC_REQUIRES_CORRECT_TIME_DESCRIPTION }, // NOLINT
      }
    }, {
      std::string("adblock"), {
        { "additionalFiltersTitle", IDS_ADBLOCK_ADDITIONAL_FILTERS_TITLE },
        { "additionalFiltersWarning", IDS_ADBLOCK_ADDITIONAL_FILTERS_WARNING },                  // NOLINT
        { "adsBlocked", IDS_ADBLOCK_TOTAL_ADS_BLOCKED },
        { "customFiltersTitle", IDS_ADBLOCK_CUSTOM_FILTERS_TITLE },
        { "customFiltersInstructions", IDS_ADBLOCK_CUSTOM_FILTERS_INSTRUCTIONS },                // NOLINT
      }
    }, {
      std::string("donate"), {
        { "about", IDS_ONEVN_UI_ABOUT },
        { "addFunds", IDS_ONEVN_UI_ADD_FUNDS },
        { "autoTipText", IDS_ONEVN_UI_AUTO_TIP_TEXT },
        { "bat", IDS_ONEVN_UI_BAT_TEXT },
        { "donationAmount", IDS_ONEVN_UI_DONATION_AMOUNT },
        { "doMonthly", IDS_ONEVN_UI_DO_MONTHLY },
        { "firstTipDateText", IDS_ONEVN_UI_FIRST_TIP_TEXT },
        { "makeMonthly", IDS_ONEVN_UI_MAKE_MONTHLY },
        { "notEnoughTokens", IDS_ONEVN_UI_NOT_ENOUGH_TOKENS },
        { "on", IDS_ONEVN_UI_ON },
        { "monthlyText", IDS_ONEVN_UI_MONTHLY_TEXT },
        { "rewardsBannerText1", IDS_ONEVN_UI_REWARDS_BANNER_TEXT1 },
        { "rewardsBannerText2", IDS_ONEVN_UI_REWARDS_BANNER_TEXT2 },
        { "sendDonation", IDS_ONEVN_UI_SEND_DONATION },
        { "siteBannerNoticeNote", IDS_ONEVN_UI_SITE_BANNER_NOTICE_NOTE },
        { "siteBannerNoticeText", IDS_ONEVN_UI_SITE_BANNER_NOTICE_TEXT },
        { "thankYou", IDS_ONEVN_UI_THANK_YOU },
        { "tipText", IDS_ONEVN_UI_TIP_TEXT },
        { "tokens", IDS_ONEVN_UI_TOKENS },
        { "unVerifiedTextMore", IDS_ONEVN_UI_SITE_UNVERIFIED_TEXT_MORE },
        { "walletBalance", IDS_ONEVN_UI_WALLET_BALANCE },
        { "welcome", IDS_ONEVN_UI_WELCOME },
      }
    }, {
      std::string("rewards-internals"), {
        { "amount", IDS_ONEVN_REWARDS_INTERNALS_AMOUNT },
        { "bootStamp", IDS_ONEVN_REWARDS_INTERNALS_BOOT_STAMP },
        { "currentReconcile", IDS_ONEVN_REWARDS_INTERNALS_CURRENT_RECONCILE },
        { "invalid", IDS_ONEVN_REWARDS_INTERNALS_INVALID },
        { "keyInfoSeed", IDS_ONEVN_REWARDS_INTERNALS_KEY_INFO_SEED },
        { "personaId", IDS_ONEVN_REWARDS_INTERNALS_PERSONA_ID },
        { "refreshButton", IDS_ONEVN_REWARDS_INTERNALS_REFRESH_BUTTON },
        { "retryLevel", IDS_ONEVN_REWARDS_INTERNALS_RETRY_LEVEL },
        { "retryStep", IDS_ONEVN_REWARDS_INTERNALS_RETRY_STEP },
        { "retryStepCurrent", IDS_ONEVN_REWARDS_INTERNALS_RETRY_STEP_CURRENT },
        { "retryStepFinal", IDS_ONEVN_REWARDS_INTERNALS_RETRY_STEP_FINAL },
        { "retryStepPayload", IDS_ONEVN_REWARDS_INTERNALS_RETRY_STEP_PAYLOAD },
        { "retryStepPrepare", IDS_ONEVN_REWARDS_INTERNALS_RETRY_STEP_PREPARE },
        { "retryStepProof", IDS_ONEVN_REWARDS_INTERNALS_RETRY_STEP_PROOF },
        { "retryStepReconcile", IDS_ONEVN_REWARDS_INTERNALS_RETRY_STEP_RECONCILE },              // NOLINT
        { "retryStepRegister", IDS_ONEVN_REWARDS_INTERNALS_RETRY_STEP_REGISTER },                // NOLINT
        { "retryStepUnknown", IDS_ONEVN_REWARDS_INTERNALS_RETRY_STEP_UNKNOWN },
        { "retryStepViewing", IDS_ONEVN_REWARDS_INTERNALS_RETRY_STEP_VIEWING },
        { "retryStepVote", IDS_ONEVN_REWARDS_INTERNALS_RETRY_STEP_VOTE },
        { "retryStepWinners", IDS_ONEVN_REWARDS_INTERNALS_RETRY_STEP_WINNERS },
        { "rewardsNotEnabled", IDS_ONEVN_REWARDS_INTERNALS_REWARDS_NOT_ENABLED },                // NOLINT
        { "userId", IDS_ONEVN_REWARDS_INTERNALS_USER_ID },
        { "valid", IDS_ONEVN_REWARDS_INTERNALS_VALID },
        { "viewingId", IDS_ONEVN_REWARDS_INTERNALS_VIEWING_ID },
        { "walletPaymentId", IDS_ONEVN_REWARDS_INTERNALS_WALLET_PAYMENT_ID },
      }
    }
  };
  AddLocalizedStringsBulk(source, localized_strings[name]);
}  // NOLINT(readability/fn_size)
