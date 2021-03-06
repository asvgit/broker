/*
 * Copyright 2014-present IVK JSC. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Tracked.h"

#include <transport/UPMQException.h>

using namespace upmq;
using namespace upmq::state;
using namespace upmq::transport;
using namespace decaf;
using namespace decaf::lang;

////////////////////////////////////////////////////////////////////////////////
Tracked::Tracked() : transport::Response(), runnable() {}

////////////////////////////////////////////////////////////////////////////////
Tracked::Tracked(Pointer<Runnable> runnable_) : transport::Response(), runnable(runnable_) {}

////////////////////////////////////////////////////////////////////////////////
void Tracked::onResponse() {
  try {
    if (this->runnable != nullptr) {
      this->runnable->run();
      this->runnable.reset(nullptr);
    }
  }
  AMQ_CATCH_RETHROW(UPMQException)
  AMQ_CATCHALL_THROW(UPMQException)
}
