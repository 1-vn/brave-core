#define AddProfilesExtraParts AddProfilesExtraParts_ChromiumImpl
#include "../../../../chrome/browser/profiles/chrome_browser_main_extra_parts_profiles.cc"
#undef AddProfilesExtraParts

#include "onevn/browser/browser_context_keyed_service_factories.h"

namespace {

class OnevnBrowserMainExtraPartsProfiles : public ChromeBrowserMainExtraPartsProfiles {
 public:
  OnevnBrowserMainExtraPartsProfiles() : ChromeBrowserMainExtraPartsProfiles() {}

  void PreProfileInit() override {
    ChromeBrowserMainExtraPartsProfiles::PreProfileInit();
    onevn::EnsureBrowserContextKeyedServiceFactoriesBuilt();
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(OnevnBrowserMainExtraPartsProfiles);
};

}  // namespace

namespace chrome {

void AddProfilesExtraParts(ChromeBrowserMainParts* main_parts) {
  main_parts->AddParts(new OnevnBrowserMainExtraPartsProfiles());
}

}  // namespace chrome
