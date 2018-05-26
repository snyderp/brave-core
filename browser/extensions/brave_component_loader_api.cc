/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/extensions/brave_component_loader_api.h"

#include "base/command_line.h"
#include "brave/browser/component_updater/brave_component_installer.h"
#include "brave/common/brave_switches.h"
#include "chrome/browser/browser_process.h"
#include "components/grit/brave_components_resources.h"

void ComponentsUI::OnDemandUpdate(
    component_updater::ComponentUpdateService* cus,
    const std::string& component_id) {
  cus->GetOnDemandUpdater().OnDemandUpdate(component_id,
      component_updater::Callback());
}

namespace extensions {

void BraveComponentLoaderAPI::OnComponentRegistered(const std::string& component_id) {
  OnDemandUpdate(g_browser_process->component_updater(), component_id);
}

void BraveComponentLoaderAPI::RegisterExtension(
    const std::string& component_id,
    const std::string& component_name,
    const std::string& public_key,
    const ReadyCallback& ready_callback) {
  base::Closure registered_callback =
      base::Bind(&BraveComponentLoaderAPI::OnComponentRegistered, component_id);
  brave::RegisterComponent(g_browser_process->component_updater(),
      component_name, public_key,
      registered_callback, ready_callback);
}

}  // namespace extensions
