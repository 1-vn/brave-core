#define AddProfilesExtraParts AddProfilesExtraParts_ChromiumImpl
#include "../../../../chrome/browser/profiles/chrome_browser_main_extra_parts_profiles.cc"
#undef AddProfilesExtraParts

#include "onevn/browser/browser_context_keyed_service_factories.h"

namespace {

class OneVNBrowserMainExtraPartsProfiles : public ChromeBrowserMainExtraPartsProfiles {
 public:
  OneVNBrowserMainExtraPartsProfiles() : ChromeBrowserMainExtraPartsProfiles() {}

  void PreProfileInit() override {
    ChromeBrowserMainExtraPartsProfiles::PreProfileInit();
    onevn::EnsureBrowserContextKeyedServiceFactoriesBuilt();
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(OneVNBrowserMainExtraPartsProfiles);
};

}  // namespace

namespace chrome {

void AddProfilesExtraParts(ChromeBrowserMainParts* main_parts) {
  main_parts->AddParts(new OneVNBrowserMainExtraPartsProfiles());
}

}  // namespace chrome
