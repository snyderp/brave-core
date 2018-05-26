/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_BROWSER_EXTENSIONS_BRAVE_COMPONENT_LOADER_API_H_
#define BRAVE_BROWSER_EXTENSIONS_BRAVE_COMPONENT_LOADER_API_H_

#include "base/files/file_path.h"
#include "components/component_updater/component_updater_service.h"
#include "content/public/common/resource_type.h"
#include "url/gurl.h"

using ReadyCallback = base::Callback<void(const base::FilePath&)>;

// Just used to give access to OnDemandUpdater since it's private.
// Chromium has ComponentsUI which is a friend class, so we just
// do this hack here to gain access.
class ComponentsUI {
 public:
  static void OnDemandUpdate(
      component_updater::ComponentUpdateService* cus,
      const std::string& component_id);
};

namespace extensions {

// For registering, loading, and unloading component extensions.
class BraveComponentLoaderAPI : public ComponentsUI {
 public:
  BraveComponentLoaderAPI();
  ~BraveComponentLoaderAPI();

  static void RegisterExtension(
    const std::string& component_id,
    const std::string& component_name,
    const std::string& public_key,
    const ReadyCallback& ready_callback);

 protected:
  static void OnComponentRegistered(const std::string& component_id);

  DISALLOW_COPY_AND_ASSIGN(BraveComponentLoaderAPI);
};

}  // namespace extensions

#endif  // BRAVE_BROWSER_EXTENSIONS_BRAVE_COMPONENT_LOADER_API_H_
