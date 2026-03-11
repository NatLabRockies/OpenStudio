/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/HVACTemplatePlantHotWaterLoop.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplatePlantHotWaterLoop_DefaultConstructor) {
  Model model;
  HVACTemplatePlantHotWaterLoop object(model);
  EXPECT_EQ(HVACTemplatePlantHotWaterLoop::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplatePlantHotWaterLoop_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplatePlantHotWaterLoop object(model);

  EXPECT_TRUE(object.setPumpControlType("Continuous"));
  EXPECT_EQ("Continuous", object.pumpControlType());
  EXPECT_FALSE(object.isPumpControlTypeDefaulted());
  object.resetPumpControlType();
  EXPECT_TRUE(object.isPumpControlTypeDefaulted());

  EXPECT_TRUE(object.setHotWaterDesignSetpoint(80.0));
  EXPECT_DOUBLE_EQ(80.0, object.hotWaterDesignSetpoint());

  EXPECT_TRUE(object.setHotWaterPumpRatedHead(150000.0));
  EXPECT_DOUBLE_EQ(150000.0, object.hotWaterPumpRatedHead());
  EXPECT_FALSE(object.setHotWaterPumpRatedHead(-1.0));

  EXPECT_TRUE(object.setSupplySideBypassPipe(false));
  EXPECT_FALSE(object.supplySideBypassPipe());
  object.resetSupplySideBypassPipe();
  EXPECT_TRUE(object.supplySideBypassPipe());

  EXPECT_TRUE(object.setMaximumOutdoorDryBulbTemperature(18.0));
  ASSERT_TRUE(object.maximumOutdoorDryBulbTemperature());
  EXPECT_DOUBLE_EQ(18.0, object.maximumOutdoorDryBulbTemperature().get());
  object.resetMaximumOutdoorDryBulbTemperature();
  EXPECT_FALSE(object.maximumOutdoorDryBulbTemperature());

  EXPECT_TRUE(object.setLoadDistributionScheme("UniformLoad"));
  EXPECT_EQ("UniformLoad", object.loadDistributionScheme());
  EXPECT_FALSE(object.isLoadDistributionSchemeDefaulted());
  object.resetLoadDistributionScheme();
  EXPECT_TRUE(object.isLoadDistributionSchemeDefaulted());

  EXPECT_GE(HVACTemplatePlantHotWaterLoop::pumpControlTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplatePlantHotWaterLoop::hotWaterPumpTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplatePlantHotWaterLoop::loadDistributionSchemeValues().size(), 1u);
}
