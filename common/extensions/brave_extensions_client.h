/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMMON_EXTENSIONS_BRAVE_EXTENSIONS_CLIENT_H_
#define BRAVE_COMMON_EXTENSIONS_BRAVE_EXTENSIONS_CLIENT_H_

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "chrome/common/extensions/chrome_extensions_client.h"

namespace extensions {

// The implementation of ExtensionsClient for Brave, which encapsulates the
// global knowledge of features, permissions, and manifest fields.
class BraveExtensionsClient : public ChromeExtensionsClient {
 public:
  BraveExtensionsClient();
  ~BraveExtensionsClient() override;

  bool IsAPISchemaGenerated(const std::string& name) const override;
  base::StringPiece GetAPISchema(const std::string& name) const override;

  // Get the LazyInstance for ChromeExtensionsClient.
  static ChromeExtensionsClient* GetInstance();

 private:
  DISALLOW_COPY_AND_ASSIGN(BraveExtensionsClient);
};

}  // namespace extensions

#endif  // BRAVE_COMMON_EXTENSIONS_BRAVE_EXTENSIONS_CLIENT_H_
