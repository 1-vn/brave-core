/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/onevn_browser_main_extra_parts.h"

#include "onevn/browser/onevn_browser_process_impl.h"
#include "chrome/browser/first_run/first_run.h"
#include "third_party/widevine/cdm/buildflags.h"

#if BUILDFLAG(BUNDLE_WIDEVINE_CDM)
#include "onevn/browser/widevine/onevn_widevine_bundle_manager.h"
#endif

OneVNBrowserMainExtraParts::OneVNBrowserMainExtraParts() {
}

OneVNBrowserMainExtraParts::~OneVNBrowserMainExtraParts() {
}

void OneVNBrowserMainExtraParts::PreMainMessageLoopRun() {
  onevn::AutoImportMuon();
#if BUILDFLAG(BUNDLE_WIDEVINE_CDM)
  // Want to check as early as possible because |StartupCheck()| has some
  // fixup handling for abnormal status and run it on UI thread.
  // However, OneVNBrowserProcessImpl that the owner of bundle manager is
  // created before browser thread creation.
  // So, call it after browser threads are created.
  g_onevn_browser_process->onevn_widevine_bundle_manager()->StartupCheck();
#endif
}
