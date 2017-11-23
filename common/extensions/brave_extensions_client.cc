/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/common/extensions/brave_extensions_client.h"

#include <memory>
#include <set>
#include <string>

#include "brave/common/extensions/api/generated_schemas.h"
#include "base/strings/string_util.h"

namespace extensions {

static base::LazyInstance<BraveExtensionsClient>::Leaky g_client =
    LAZY_INSTANCE_INITIALIZER;

BraveExtensionsClient::BraveExtensionsClient() {
}

BraveExtensionsClient::~BraveExtensionsClient() {
}

bool BraveExtensionsClient::IsAPISchemaGenerated(
    const std::string& name) const {
  return ChromeExtensionsClient::IsAPISchemaGenerated(name) ||
    api::BraveGeneratedSchemas::IsGenerated(name);
}

base::StringPiece BraveExtensionsClient::GetAPISchema(
    const std::string& name) const {
  if (api::BraveGeneratedSchemas::IsGenerated(name))
    return api::BraveGeneratedSchemas::Get(name);

  return ChromeExtensionsClient::GetAPISchema(name);
}

// static
ChromeExtensionsClient* BraveExtensionsClient::GetInstance() {
  return g_client.Pointer();
}

}  // namespace extensions
