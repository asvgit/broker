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

#ifndef _TRANSACTIONTEST_H_
#define _TRANSACTIONTEST_H_

#include <gtest/gtest.h>
#include "CMSProvider.h"
#include "IntegrationCommon.h"

using namespace cms;

class TransactionTest : public ::testing::Test {
 protected:
  TransactionTest() = default;

  ~TransactionTest() override = default;

  void SetUp() override;

  void TearDown() override;

  std::unique_ptr<CMSProvider> cmsProvider;

  std::string getBrokerURL() const { return IntegrationCommon::getInstance().getOpenwireURL(); }

  static const size_t batchCount = 10;
  static const size_t batchSize = 20;
};

#endif /*_TRANSACTIONTEST_H_*/
