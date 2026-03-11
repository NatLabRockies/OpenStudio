/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/HVACTemplatePlantChillerObjectReference.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplatePlantChillerObjectReference_DefaultConstructor) {
  Model model;
  HVACTemplatePlantChillerObjectReference object(model);
  EXPECT_EQ(HVACTemplatePlantChillerObjectReference::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplatePlantChillerObjectReference_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplatePlantChillerObjectReference object(model);

  EXPECT_TRUE(object.isChillerObjectTypeDefaulted());
  EXPECT_EQ("Chiller:Electric:EIR", object.chillerObjectType());

  EXPECT_TRUE(object.setChillerObjectType("Chiller:Electric:ReformulatedEIR"));
  EXPECT_EQ("Chiller:Electric:ReformulatedEIR", object.chillerObjectType());
  EXPECT_FALSE(object.isChillerObjectTypeDefaulted());
  object.resetChillerObjectType();
  EXPECT_TRUE(object.isChillerObjectTypeDefaulted());
  EXPECT_EQ("Chiller:Electric:EIR", object.chillerObjectType());

  EXPECT_TRUE(object.setPriority(2.0));
  ASSERT_TRUE(object.priority());
  EXPECT_DOUBLE_EQ(2.0, object.priority().get());
  object.resetPriority();
  EXPECT_FALSE(object.priority());

  EXPECT_FALSE(object.setChillerObjectType("InvalidChillerObjectType"));

  EXPECT_GE(HVACTemplatePlantChillerObjectReference::chillerObjectTypeValues().size(), 1u);
}
