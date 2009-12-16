/**
 * Copyright 2009 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Author: Matthew Steele

#include "file_util.h"

namespace {

// replace anything that isn't an alphanumeric, . or - with _.
// limit filenames to 50 characters.
std::string SanitizeFilename(const std::string& str) {
  std::string sanitized;
  for (std::string::const_iterator iter = str.begin(), end = str.end();
       iter != end;
       ++iter) {
    char c = *iter;
    if (isalnum(c) || c == '-' || c == '.') {
      sanitized += c;
    } else {
      sanitized += '_';
    }
  }

  if (sanitized.length() < 50) {
    return sanitized;
  } else {
    return sanitized.substr(0, 50);
  }
}

}

namespace pagespeed {

std::string ChooseOutputFilename(const GURL& url, const std::string& hash) {
  const std::string url_path = url.path();
  const size_t last_slash = url_path.find_last_of('/');
  const size_t last_dot = url_path.find_last_of('.');
  const size_t start = (last_slash == std::string::npos ? 0 : last_slash + 1);
  if (last_dot == std::string::npos || last_dot < start) {
    return SanitizeFilename(url_path.substr(start)) + "_" + hash;
  } else {
    const std::string base = url_path.substr(start, last_dot - start);
    const std::string extension = url_path.substr(last_dot);
    return SanitizeFilename(base) + "_" + hash + SanitizeFilename(extension);
  }
}

}  // namespace pagespeed
