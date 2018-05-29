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


void BraveComponentLoaderAPI::Load(const base::FilePath& path, base::DictionaryValue manifest) {
  extensions::Manifest::Location manifest_location =
      extensions::Manifest::Location::UNPACKED;
  args->GetNext(&manifest_location);

  int flags = 0;
  std::unique_ptr<base::DictionaryValue> manifest_copy =
      manifest.CreateDeepCopy();

  file_task_runner_->PostTask(
      FROM_HERE,
      base::Bind(&Extension::LoadOnFILEThread, base::Unretained(this), path,
                 Passed(&manifest_copy), manifest_location, flags));
}

void BraveComponentLoaderAPI::NotifyErrorOnUIThread(const std::string& error) {
  LOG(ERROR) << "Error loading extension: " << error;
}

void BraveComponentLoaderAPI::NotifyLoadOnUIThread(
    scoped_refptr<extensions::Extension> extension) {
  LOG(ERROR) << "====notify loadon ui thread ";
  /*
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  extensions::ExtensionSystem::Get(browser_context_)->ready().Post(
        FROM_HERE,
        base::Bind(&Extension::AddExtension,
          // GetWeakPtr()
          base::Unretained(this), base::Passed(&extension)));
          */
}
  
void BraveComponentLoaderAPI::LoadOnFILEThread(const base::FilePath path,
    std::unique_ptr<base::DictionaryValue> manifest,
    extensions::Manifest::Location manifest_location,
    int flags) {
  base::AssertBlockingAllowed();

  std::string error;
  if (manifest->empty()) {
    manifest = extensions::file_util::LoadManifest(path, &error)
  }

  if (!manifest || !error.empty()) {
    content::BrowserThread::PostTask(
          content::BrowserThread::UI, FROM_HERE,
          base::Bind(&BraveComponentLoaderAPI::NotifyErrorOnUIThread,
              base::Unretained(this), error));
  } else {
    scoped_refptr<extensions::Extension> extension = LoadExtension(path,
                              *manifest,
                              manifest_location,
                              flags,
                              &error);

    if (!extension || !error.empty()) {
      content::BrowserThread::PostTask(
          content::BrowserThread::UI, FROM_HERE,
          base::Bind(&BraveComponentLoaderAPI::NotifyErrorOnUIThread,
              base::Unretained(this), error));
    } else {
      content::BrowserThread::PostTask(
          content::BrowserThread::UI, FROM_HERE,
          base::Bind(&BraveComponentLoaderAPI::NotifyLoadOnUIThread,
              base::Unretained(this), base::Passed(&extension)));
    }
  }
}

void BraveComponentLoaderAPI::OnComponentRegistered(const std::string& component_id) {
  LOG(ERROR) << "Component registered!!!! (but not ready): " << component_id;
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
