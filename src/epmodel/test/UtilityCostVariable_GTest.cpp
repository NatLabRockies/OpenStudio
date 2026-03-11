/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "ModelObject/UtilityCostVariable.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, UtilityCostVariable_DefaultConstructor) {
  Model model;
  UtilityCostVariable variable(model);

  EXPECT_EQ(UtilityCostVariable::iddObjectType(), variable.iddObject().type());
  ASSERT_FALSE(UtilityCostVariable::variableTypeValues().empty());
  EXPECT_EQ("Dimensionless", variable.variableType());
  EXPECT_FALSE(variable.januaryValue());
  EXPECT_FALSE(variable.februaryValue());
  EXPECT_FALSE(variable.marchValue());
  EXPECT_FALSE(variable.aprilValue());
  EXPECT_FALSE(variable.mayValue());
  EXPECT_FALSE(variable.juneValue());
  EXPECT_FALSE(variable.julyValue());
  EXPECT_FALSE(variable.augustValue());
  EXPECT_FALSE(variable.septemberValue());
  EXPECT_FALSE(variable.octoberValue());
  EXPECT_FALSE(variable.novemberValue());
  EXPECT_FALSE(variable.decemberValue());
}

TEST_F(EPModelFixture, UtilityCostVariable_ScalarAccessors_RoundTrip) {
  Model model;
  UtilityCostVariable variable(model);

  ASSERT_FALSE(UtilityCostVariable::variableTypeValues().empty());
  const auto variableType = UtilityCostVariable::variableTypeValues().front();
  EXPECT_TRUE(variable.setVariableType(variableType));

  EXPECT_TRUE(variable.setJanuaryValue(1.0));
  EXPECT_TRUE(variable.setFebruaryValue(2.0));
  EXPECT_TRUE(variable.setMarchValue(3.0));
  EXPECT_TRUE(variable.setAprilValue(4.0));
  EXPECT_TRUE(variable.setMayValue(5.0));
  EXPECT_TRUE(variable.setJuneValue(6.0));
  EXPECT_TRUE(variable.setJulyValue(7.0));
  EXPECT_TRUE(variable.setAugustValue(8.0));
  EXPECT_TRUE(variable.setSeptemberValue(9.0));
  EXPECT_TRUE(variable.setOctoberValue(10.0));
  EXPECT_TRUE(variable.setNovemberValue(11.0));
  EXPECT_TRUE(variable.setDecemberValue(12.0));

  EXPECT_EQ(variableType, variable.variableType());
  ASSERT_TRUE(variable.januaryValue());
  EXPECT_DOUBLE_EQ(1.0, *variable.januaryValue());
  ASSERT_TRUE(variable.februaryValue());
  EXPECT_DOUBLE_EQ(2.0, *variable.februaryValue());
  ASSERT_TRUE(variable.marchValue());
  EXPECT_DOUBLE_EQ(3.0, *variable.marchValue());
  ASSERT_TRUE(variable.aprilValue());
  EXPECT_DOUBLE_EQ(4.0, *variable.aprilValue());
  ASSERT_TRUE(variable.mayValue());
  EXPECT_DOUBLE_EQ(5.0, *variable.mayValue());
  ASSERT_TRUE(variable.juneValue());
  EXPECT_DOUBLE_EQ(6.0, *variable.juneValue());
  ASSERT_TRUE(variable.julyValue());
  EXPECT_DOUBLE_EQ(7.0, *variable.julyValue());
  ASSERT_TRUE(variable.augustValue());
  EXPECT_DOUBLE_EQ(8.0, *variable.augustValue());
  ASSERT_TRUE(variable.septemberValue());
  EXPECT_DOUBLE_EQ(9.0, *variable.septemberValue());
  ASSERT_TRUE(variable.octoberValue());
  EXPECT_DOUBLE_EQ(10.0, *variable.octoberValue());
  ASSERT_TRUE(variable.novemberValue());
  EXPECT_DOUBLE_EQ(11.0, *variable.novemberValue());
  ASSERT_TRUE(variable.decemberValue());
  EXPECT_DOUBLE_EQ(12.0, *variable.decemberValue());

  variable.resetJanuaryValue();
  variable.resetFebruaryValue();
  variable.resetMarchValue();
  variable.resetAprilValue();
  variable.resetMayValue();
  variable.resetJuneValue();
  variable.resetJulyValue();
  variable.resetAugustValue();
  variable.resetSeptemberValue();
  variable.resetOctoberValue();
  variable.resetNovemberValue();
  variable.resetDecemberValue();

  EXPECT_FALSE(variable.januaryValue());
  EXPECT_FALSE(variable.februaryValue());
  EXPECT_FALSE(variable.marchValue());
  EXPECT_FALSE(variable.aprilValue());
  EXPECT_FALSE(variable.mayValue());
  EXPECT_FALSE(variable.juneValue());
  EXPECT_FALSE(variable.julyValue());
  EXPECT_FALSE(variable.augustValue());
  EXPECT_FALSE(variable.septemberValue());
  EXPECT_FALSE(variable.octoberValue());
  EXPECT_FALSE(variable.novemberValue());
  EXPECT_FALSE(variable.decemberValue());

  variable.resetVariableType();
  EXPECT_TRUE(variable.isVariableTypeDefaulted());
}
