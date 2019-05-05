/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ONEVN_EXTENSIONS_RENDERER_ONEVN_NATIVE_EXTENSION_BINDINGS_SYSTEM_H_
#define ONEVN_EXTENSIONS_RENDERER_ONEVN_NATIVE_EXTENSION_BINDINGS_SYSTEM_H_

#include "extensions/renderer/native_extension_bindings_system.h"

namespace extensions {

class OnevnNativeExtensionBindingsSystem : public NativeExtensionBindingsSystem {
 public:
  explicit OnevnNativeExtensionBindingsSystem(
      std::unique_ptr<IPCMessageSender> ipc_message_sender);
  ~OnevnNativeExtensionBindingsSystem() override {}

 private:
  DISALLOW_COPY_AND_ASSIGN(OnevnNativeExtensionBindingsSystem);
};

}  // namespace extensions

#endif  // ONEVN_EXTENSIONS_RENDERER_ONEVN_NATIVE_EXTENSION_BINDINGS_SYSTEM_H_
