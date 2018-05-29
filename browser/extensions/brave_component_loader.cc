/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/extensions/brave_component_loader.h"

#include "base/command_line.h"
#include "brave/common/brave_switches.h"
#include "components/grit/brave_components_resources.h"
#include "brave/browser/extensions/brave_component_loader_api.h"
#include "chrome/browser/browser_process_impl.h"

namespace {

void OnComponentReady(const std::string& component_id,
    const base::FilePath& install_dir) {
  LOG(ERROR) << "OnCOMPONENT READY !!!! " << component_id;
  extensions::BraveComponentLoaderAPI::LoadExtension(base::FilePath("/Users/bbondy/Library/Application\ Support/Brave-Browser-Development/oemmndcbldboiebfnladdacbdfmadadm/1.6.293/"), 
      base::DictionaryValue());
}

}

namespace extensions {

BraveComponentLoader::BraveComponentLoader(
    ExtensionServiceInterface* extension_service,
    PrefService* profile_prefs,
    PrefService* local_state,
    Profile* profile)
    : ComponentLoader(extension_service, profile_prefs, local_state, profile),
      profile_(profile){
}

BraveComponentLoader::~BraveComponentLoader() {
}

void BraveComponentLoader::AddDefaultComponentExtensions(
    bool skip_session_components) {
  ComponentLoader::AddDefaultComponentExtensions(skip_session_components);

  const base::CommandLine& command_line =
      *base::CommandLine::ForCurrentProcess();
  if (!command_line.HasSwitch(switches::kDisableBraveExtension)) {
    base::FilePath brave_extension_path(FILE_PATH_LITERAL(""));
    brave_extension_path =
        brave_extension_path.Append(FILE_PATH_LITERAL("brave_extension"));
    Add(IDR_BRAVE_EXTENSON, brave_extension_path);
  }

  extensions::BraveComponentLoaderAPI::RegisterExtension("oemmndcbldboiebfnladdacbdfmadadm",
      "PDFJS",
      "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDb5PIb8ayK6vHvEIY1nJKRSCDE8iJ1T43qFN+5dvCVQrmyEkgqB9ZuZNT24Lwot96HV51VoITHKRNIVKI2Nrbfn0M49t7qtaP34g/GXJ7mAIbSzsY4+i+Wsz8EL2SNEIw6uH8RmXG7nZ29NJ7sk7jn17QmMsO2UJ01UT8hfOOOEQIDAQAB",
      base::Bind(OnComponentReady, "oemmndcbldboiebfnladdacbdfmadadm"));
}

}  // namespace extensions
