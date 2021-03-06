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

#ifndef BROKER_FAKE_CPP14_H
#define BROKER_FAKE_CPP14_H

#include <memory>

#ifdef _WIN32
#define COMPILER_HAS_NOT_CPP14 (_MSC_VER < 1800)
#else
#define COMPILER_HAS_NOT_CPP14 (__cplusplus < 201402L)
#endif

#if COMPILER_HAS_NOT_CPP14

namespace std {
template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args &&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
}  // namespace std

#endif  // c++ std < 14

#endif  // BROKER_FAKE_CPP14_H
