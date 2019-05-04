#include "../../../../../../chrome/browser/profiles/profile.cc"

#include "onevn/common/tor/pref_names.h"

bool Profile::IsTorProfile() const {
  return GetPrefs()->GetBoolean(tor::prefs::kProfileUsingTor);
}
