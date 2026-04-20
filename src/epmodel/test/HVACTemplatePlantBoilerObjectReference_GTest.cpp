/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/HVACTemplatePlantBoilerObjectReference.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplatePlantBoilerObjectReference_DefaultConstructor) {
  Model model;
  HVACTemplatePlantBoilerObjectReference object(model);
  EXPECT_EQ(HVACTemplatePlantBoilerObjectReference::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplatePlantBoilerObjectReference_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplatePlantBoilerObjectReference object(model);

  EXPECT_TRUE(object.isBoilerObjectTypeDefaulted());
  EXPECT_EQ("Boiler:HotWater", object.boilerObjectType());

  EXPECT_TRUE(object.setBoilerObjectType("Boiler:HotWater"));
  EXPECT_EQ("Boiler:HotWater", object.boilerObjectType());
  EXPECT_FALSE(object.isBoilerObjectTypeDefaulted());
  object.resetBoilerObjectType();
  EXPECT_TRUE(object.isBoilerObjectTypeDefaulted());
  EXPECT_EQ("Boiler:HotWater", object.boilerObjectType());

  EXPECT_TRUE(object.setPriority(2.0));
  ASSERT_TRUE(object.priority());
  EXPECT_DOUBLE_EQ(2.0, object.priority().get());
  object.resetPriority();
  EXPECT_FALSE(object.priority());

  EXPECT_TRUE(object.setTemplatePlantLoopType("MixedWater"));
  ASSERT_TRUE(object.templatePlantLoopType());
  EXPECT_EQ("MixedWater", object.templatePlantLoopType().get());
  object.resetTemplatePlantLoopType();
  if (object.templatePlantLoopType()) {
    EXPECT_NE("MixedWater", object.templatePlantLoopType().get());
  }

  EXPECT_FALSE(object.setBoilerObjectType("InvalidBoilerObjectType"));

  EXPECT_GE(HVACTemplatePlantBoilerObjectReference::boilerObjectTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplatePlantBoilerObjectReference::templatePlantLoopTypeValues().size(), 1u);
}
