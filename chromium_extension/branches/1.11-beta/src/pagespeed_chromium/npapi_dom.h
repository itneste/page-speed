// Copyright 2010 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef PAGESPEED_CHROMIUM_NPAPI_DOM_H_
#define PAGESPEED_CHROMIUM_NPAPI_DOM_H_

#include "third_party/npapi/npapi.h"
#include "third_party/npapi/npfunctions.h"

#include "pagespeed/core/dom.h"

namespace pagespeed_chromium {

pagespeed::DomDocument* CreateDocument(NPP npp, NPObject* document);

}  // namespace pagespeed_chromium

#endif  // PAGESPEED_CHROMIUM_NPAPI_DOM_H_
