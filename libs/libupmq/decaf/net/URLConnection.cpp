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

#include <decaf/net/URLConnection.h>

#include <decaf/io/IOException.h>
#include <decaf/lang/Integer.h>
#include <decaf/lang/exceptions/IllegalStateException.h>
#include <decaf/lang/exceptions/NullPointerException.h>
#include <decaf/lang/exceptions/NumberFormatException.h>
#include <decaf/lang/exceptions/UnsupportedOperationException.h>

using namespace decaf;
using namespace decaf::net;
using namespace decaf::lang;
using namespace decaf::lang::exceptions;

////////////////////////////////////////////////////////////////////////////////
bool URLConnection::defaultAllowUserInteraction;
bool URLConnection::defaultUseCaches = true;

////////////////////////////////////////////////////////////////////////////////
namespace decaf {
namespace net {

class URLConnectionImpl {
 public:
  std::string contentType;

  //        static bool defaultAllowUserInteraction;
  //        static bool defaultUseCaches = true;
  //        ContentHandler defaultHandler = new DefaultContentHandler();

  long long lastModified;
  int readTimeout;
  int connectTimeout;

 public:
  URLConnectionImpl() : contentType(), lastModified(-1), readTimeout(0), connectTimeout(0) {}
};
}  // namespace net
}  // namespace decaf

////////////////////////////////////////////////////////////////////////////////
URLConnection::URLConnection(const URL &url_)
    : impl(new URLConnectionImpl), url(url_), ifModifiedSince(), useCaches(), connected(), doOutput(), doInput(true), allowUserInteraction() {}

////////////////////////////////////////////////////////////////////////////////
URLConnection::~URLConnection() {
  try {
    delete this->impl;
  }
  DECAF_CATCHALL_NOTHROW()
}

////////////////////////////////////////////////////////////////////////////////
int URLConnection::getConnectTimeout() const { return impl->connectTimeout; }

////////////////////////////////////////////////////////////////////////////////
int URLConnection::getReadTimeout() const { return impl->readTimeout; }

////////////////////////////////////////////////////////////////////////////////
long long URLConnection::getHeaderFieldDate(const std::string &field, long long defaultValue) const {
  std::string date = getHeaderField(field);
  if (date.empty()) {
    return defaultValue;
  }

  throw UnsupportedOperationException(__FILE__, __LINE__, "Not yet implemented");
}

////////////////////////////////////////////////////////////////////////////////
int URLConnection::getHeaderFieldInt(const std::string &field, int defaultValue) const {
  try {
    return Integer::parseInt(getHeaderField(field));
  } catch (NumberFormatException &) {
    return defaultValue;
  }
}

////////////////////////////////////////////////////////////////////////////////
void URLConnection::setAllowUserInteraction(bool newValue) {
  if (connected) {
    throw IllegalStateException(__FILE__, __LINE__, "Connection already established");
  }

  allowUserInteraction = newValue;
}

////////////////////////////////////////////////////////////////////////////////
void URLConnection::setDefaultUseCaches(bool newValue) {
  if (connected) {
    throw IllegalStateException(__FILE__, __LINE__, "Connection already established");
  }
  defaultUseCaches = newValue;
}

////////////////////////////////////////////////////////////////////////////////
void URLConnection::setDoInput(bool newValue) {
  if (connected) {
    throw IllegalStateException(__FILE__, __LINE__, "Connection already established");
  }
  doInput = newValue;
}

////////////////////////////////////////////////////////////////////////////////
void URLConnection::setDoOutput(bool newValue) {
  if (connected) {
    throw IllegalStateException(__FILE__, __LINE__, "Connection already established");
  }
  doOutput = newValue;
}

////////////////////////////////////////////////////////////////////////////////
void URLConnection::setUseCaches(bool newValue) {
  if (connected) {
    throw IllegalStateException(__FILE__, __LINE__, "Connection already established");
  }
  useCaches = newValue;
}

////////////////////////////////////////////////////////////////////////////////
void URLConnection::setConnectTimeout(int timeout) {
  if (0 > timeout) {
    throw IllegalStateException(__FILE__, __LINE__, "Invalid negative timeout");
  }
  impl->connectTimeout = timeout;
}

////////////////////////////////////////////////////////////////////////////////
void URLConnection::setReadTimeout(int timeout) {
  if (0 > timeout) {
    throw IllegalStateException(__FILE__, __LINE__, "Invalid negative timeout");
  }
  impl->readTimeout = timeout;
}

std::string URLConnection::getHeaderField(int pos) const {
  DECAF_UNUSED_VAR(pos);
  return "";
}

std::string URLConnection::getHeaderField(const std::string &key) const {
  DECAF_UNUSED_VAR(key);
  return "";
}

////////////////////////////////////////////////////////////////////////////////
long long URLConnection::getLastModified() const {
  if (impl->lastModified != -1) {
    return impl->lastModified;
  }

  return impl->lastModified = getHeaderFieldDate("Last-Modified", 0);
}

////////////////////////////////////////////////////////////////////////////////
void URLConnection::setIfModifiedSince(long long newValue) {
  if (connected) {
    throw IllegalStateException(__FILE__, __LINE__, "Connection already established");
  }
  ifModifiedSince = newValue;
}
