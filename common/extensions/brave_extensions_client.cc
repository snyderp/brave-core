/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/common/extensions/brave_extensions_client.h"

#include <memory>
#include <set>
#include <string>

/*
#include "extensions/common/features/json_feature_provider_source.h"
#include "base/strings/string_util.h"

#include "chrome/grit/common_resources.h"
#include "extensions/grit/extensions_resources.h"

#include "extensions/common/features/feature_provider.h"
#include "extensions/common/features/json_feature_provider_source.h"
*/

#include "brave/common/extensions/api/generated_schemas.h"
#include "brave/common/extensions/api/grit/brave_api_resources.h"

#include "brave/common/extensions/api/api_features.h"
#include "brave/common/extensions/api/brave_shields.h"
#include "brave/common/extensions/api/manifest_features.h"
#include "brave/common/extensions/api/behavior_features.h"
#include "brave/common/extensions/api/generated_schemas.h"
#include "brave/common/extensions/api/permission_features.h"
/*
#include "brave/common/extensions/api/generated_schemas.h"  // NOLINT: This file is generated
#include "brave/common/extensions/api/api_features.h"
#include "brave/common/extensions/api/behavior_features.h"
#include "brave/common/extensions/api/manifest_features.h"
#include "brave/common/extensions/api/permission_features.h"
*/

#include "base/command_line.h"
#include "base/files/file_path.h"
#include "base/metrics/histogram_macros.h"
#include "base/strings/string_util.h"
#include "base/values.h"
#include "chrome/common/chrome_content_client.h"
#include "chrome/common/chrome_switches.h"
#include "chrome/common/extensions/api/api_features.h"
#include "chrome/common/extensions/api/behavior_features.h"
#include "chrome/common/extensions/api/extension_action/action_info.h"
#include "chrome/common/extensions/api/generated_schemas.h"
#include "chrome/common/extensions/api/manifest_features.h"
#include "chrome/common/extensions/api/permission_features.h"
#include "chrome/common/extensions/chrome_aliases.h"
#include "chrome/common/extensions/chrome_manifest_handlers.h"
#include "chrome/common/extensions/extension_constants.h"
#include "chrome/common/extensions/manifest_handlers/theme_handler.h"
#include "chrome/common/url_constants.h"
#include "chrome/grit/chromium_strings.h"
#include "chrome/grit/common_resources.h"
#include "components/version_info/version_info.h"
#include "content/public/common/url_constants.h"
#include "extensions/common/api/generated_schemas.h"
#include "extensions/common/common_manifest_handlers.h"
#include "extensions/common/constants.h"
#include "extensions/common/extension.h"
#include "extensions/common/extension_api.h"
#include "extensions/common/extension_icon_set.h"
#include "extensions/common/extension_urls.h"
#include "extensions/common/extensions_aliases.h"
#include "extensions/common/features/feature_channel.h"
#include "extensions/common/features/feature_provider.h"
#include "extensions/common/features/json_feature_provider_source.h"
#include "extensions/common/manifest_constants.h"
#include "extensions/common/manifest_handler.h"
#include "extensions/common/manifest_handlers/icons_handler.h"
#include "extensions/common/permissions/api_permission_set.h"
#include "extensions/common/permissions/permissions_info.h"
#include "extensions/common/url_pattern.h"
#include "extensions/common/url_pattern_set.h"
#include "extensions/grit/extensions_resources.h"
#include "ui/base/l10n/l10n_util.h"
#include "url/gurl.h"


namespace extensions {

static base::LazyInstance<BraveExtensionsClient>::Leaky g_client =
    LAZY_INSTANCE_INITIALIZER;

BraveExtensionsClient::BraveExtensionsClient() {
}

BraveExtensionsClient::~BraveExtensionsClient() {
}

std::unique_ptr<FeatureProvider> BraveExtensionsClient::CreateFeatureProvider(
    const std::string& name) const {
  std::unique_ptr<FeatureProvider> provider;
  if (name == "api") {
    provider.reset(new BraveAPIFeatureProvider());
  } else if (name == "manifest") {
    provider.reset(new BraveManifestFeatureProvider());
  } else if (name == "permission") {
    provider.reset(new BravePermissionFeatureProvider());
  } else if (name == "behavior") {
    provider.reset(new BraveBehaviorFeatureProvider());
  } else {
    NOTREACHED();
  }
  return provider;
}

std::unique_ptr<JSONFeatureProviderSource>
BraveExtensionsClient::CreateAPIFeatureSource() const {
  std::unique_ptr<JSONFeatureProviderSource> source(
      new JSONFeatureProviderSource("api"));
  source->LoadJSON(IDR_EXTENSION_API_FEATURES);
  source->LoadJSON(IDR_BRAVE_EXTENSION_API_FEATURES);
  return source;
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
