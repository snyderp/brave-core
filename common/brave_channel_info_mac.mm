// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/common/channel_info.h"

#import <Foundation/Foundation.h>

#include "base/mac/bundle_locations.h"
#include "base/strings/sys_string_conversions.h"
#include "components/version_info/version_info.h"

namespace chrome {

std::string GetChannelSuffixForDataDir() {
  // Use the main Chrome application bundle and not the framework bundle.
  // Keystone keys don't live in the framework.
  NSBundle* bundle = base::mac::OuterBundle();
  NSString* channel = [bundle objectForInfoDictionaryKey:@"KSChannelID"];
  NSMutableString* suffix = [@"-" mutableCopy];

  if (!channel) {
    // For the stable channel, KSChannelID is not set.
    return std::string();
  } else if ([channel isEqual:@"beta"] ||
             [channel isEqual:@"dev"] ||
             [channel isEqual:@"canary"]) {
    [suffix appendString:channel];
  } else {
    [suffix appendString:@"unkown"];
  }

  std::string result = base::SysNSStringToUTF8(suffix);
  result[1] = std::toupper(result[1]);
  return result;
}

}  // namespace chrome
