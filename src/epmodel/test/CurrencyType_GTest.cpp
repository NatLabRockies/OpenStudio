/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ParentObject/CurrencyType.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CurrencyType_DefaultConstructor) {
  Model model;
  CurrencyType currencyType(model);
  EXPECT_EQ(CurrencyType::iddObjectType(), currencyType.iddObject().type());
}

TEST_F(EPModelFixture, CurrencyType_ScalarAccessors_RoundTrip) {
  Model model;
  CurrencyType currencyType(model);

  ASSERT_TRUE(currencyType.monetaryUnit());

  EXPECT_TRUE(currencyType.setMonetaryUnit("USD"));
  ASSERT_TRUE(currencyType.monetaryUnit());
  EXPECT_EQ("USD", currencyType.monetaryUnit().get());

  EXPECT_TRUE(currencyType.setMonetaryUnit("EUR"));
  ASSERT_TRUE(currencyType.monetaryUnit());
  EXPECT_EQ("EUR", currencyType.monetaryUnit().get());
}
