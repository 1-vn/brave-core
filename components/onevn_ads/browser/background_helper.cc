/* Copyright 2019 The Onevn Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "onevn/components/onevn_ads/browser/background_helper.h"

namespace onevn_ads {

BackgroundHelper::BackgroundHelper() {}

BackgroundHelper::~BackgroundHelper() {}

bool BackgroundHelper::IsForeground() const {
  return true;
}

void BackgroundHelper::TriggerOnBackground() {
  for (auto& observer : observers_)
    observer.OnBackground();
}

void BackgroundHelper::TriggerOnForeground() {
  for (auto& observer : observers_)
    observer.OnForeground();
}

void BackgroundHelper::AddObserver(Observer* observer) {
  observers_.AddObserver(observer);
}

void BackgroundHelper::RemoveObserver(Observer* observer) {
  observers_.RemoveObserver(observer);
}

#if !defined(OS_MACOSX) && !defined(OS_WIN) && !defined(OS_LINUX)
BackgroundHelper* BackgroundHelper::GetInstance() {
  // just return a dummy background helper for all other platforms
  return base::Singleton<BackgroundHelper>::get();
}
#endif

}  // namespace onevn_ads
