/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/brave_browser_main_extra_parts.h"

#include "brave/browser/component_updater/brave_component_installer.h"
#include "brave/common/resource_bundle_helper.h"

BraveBrowserMainExtraParts::BraveBrowserMainExtraParts() {
}

BraveBrowserMainExtraParts::~BraveBrowserMainExtraParts() {
}

void BraveBrowserMainExtraParts::PreCreateThreads() {
  brave::InitializeResourceBundle();
}

void BraveBrowserMainExtraParts::PostBrowserStart() {
  brave::RegisterComponent(g_browser_process->component_updater(),
      "PDFJS", "439d57636ab8e17128fca58d5b31fb555477df26b3dc8489ed8da60e53679316",
      base::DoNothing(), base::DoNothing());
}
