/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/browser/ui/content_settings/onevn_content_setting_image_models.h"

#include "onevn/browser/ui/content_settings/onevn_autoplay_blocked_image_model.h"
#include "third_party/widevine/cdm/buildflags.h"

void OnevnGenerateContentSettingImageModels(
    std::vector<std::unique_ptr<ContentSettingImageModel>>& result) {
  // Remove the cookies content setting image model
  // https://github.com/1-vn/onevn-browser/issues/1197
  // TODO(iefremov): This changes break internal image models ordering which is
  // based on enum values. This breaks tests and probably should be fixed
  // (by adding more diff of course).
  for (size_t i = 0; i < result.size(); i++) {
    if (result[i]->image_type() ==
        ContentSettingImageModel::ImageType::COOKIES) {
      result.erase(result.begin() + i);
      break;
    }
  }

  result.push_back(std::make_unique<OnevnAutoplayBlockedImageModel>());
}
