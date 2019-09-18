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

#ifndef BROKER_SINGLETON_H
#define BROKER_SINGLETON_H

template <typename T>
class Singleton {
 public:
  static T &Instance() {
    if (Singleton::_instance == nullptr) {
      throw std::runtime_error("singleton instance is null");
    }
    return *(Singleton<T>::_instance);
  }

  static void destroyInstance() {
    delete Singleton<T>::_instance;
    Singleton::_instance = nullptr;
  }

  template <typename... Args>
  static void makeInstance(Args &&... args) {
    if (Singleton::_instance != nullptr) {
      destroyInstance();
    }
    Singleton::_instance = new T(std::forward<Args>(args)...);
  }

 protected:
  virtual ~Singleton() {
    try {
      destroyInstance();
    } catch (...) {
    }
  }
  inline explicit Singleton() {
    static_assert(Singleton<T>::_instance == 0, "empty instance");
    Singleton::_instance = static_cast<T *>(this);
  }

 private:
  static T *_instance;
  template <typename... Args>
  static T *CreateInstance(Args &&... args) {
    return new T(std::forward<Args>(args)...);
  }
};

template <typename T>
T *Singleton<T>::_instance = 0;

#endif  // BROKER_SINGLETON_H
