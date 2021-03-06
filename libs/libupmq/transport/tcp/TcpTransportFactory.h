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

#ifndef _UPMQ_TCP_TRANSPORT_FACTORY_H_
#define _UPMQ_TCP_TRANSPORT_FACTORY_H_

#include <decaf/net/URI.h>
#include <decaf/util/Properties.h>
#include <transport/AbstractTransportFactory.h>
#include <transport/Config.h>
#include <transport/Transport.h>
#include <transport/WireFormat.h>

namespace upmq {
namespace transport {
namespace tcp {

using decaf::lang::Pointer;

/**
 * Factory Responsible for creating the TcpTransport.
 */
class UPMQCPP_API TcpTransportFactory : public AbstractTransportFactory {
 public:
  virtual ~TcpTransportFactory() {}

  virtual Pointer<Transport> create(const decaf::net::URI &location);

  virtual Pointer<Transport> createComposite(const decaf::net::URI &location);

 protected:
  virtual Pointer<Transport> doCreateComposite(const decaf::net::URI &location,
                                               const Pointer<transport::WireFormat> &wireFormat,
                                               const decaf::util::Properties &properties);

  virtual void doConfigureTransport(const Pointer<Transport> &transport, const decaf::util::Properties &properties);
};
}  // namespace tcp
}  // namespace transport
}  // namespace upmq

#endif /*_UPMQ_TCP_TRANSPORT_FACTORY_H_*/
