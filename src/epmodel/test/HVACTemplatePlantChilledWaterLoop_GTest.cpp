/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/HVACTemplatePlantChilledWaterLoop.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplatePlantChilledWaterLoop_DefaultConstructor) {
  Model model;
  HVACTemplatePlantChilledWaterLoop object(model);
  EXPECT_EQ(HVACTemplatePlantChilledWaterLoop::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplatePlantChilledWaterLoop_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplatePlantChilledWaterLoop object(model);

  EXPECT_TRUE(object.setPumpControlType("Continuous"));
  EXPECT_EQ("Continuous", object.pumpControlType());
  EXPECT_FALSE(object.isPumpControlTypeDefaulted());
  object.resetPumpControlType();
  EXPECT_TRUE(object.isPumpControlTypeDefaulted());

  EXPECT_TRUE(object.setPrimaryChilledWaterPumpRatedHead(200000.0));
  EXPECT_DOUBLE_EQ(200000.0, object.primaryChilledWaterPumpRatedHead());
  EXPECT_FALSE(object.setPrimaryChilledWaterPumpRatedHead(-1.0));

  EXPECT_TRUE(object.setCondenserWaterTemperatureControlType("SpecifiedSetpoint"));
  ASSERT_TRUE(object.condenserWaterTemperatureControlType());
  EXPECT_EQ("SpecifiedSetpoint", object.condenserWaterTemperatureControlType().get());
  object.resetCondenserWaterTemperatureControlType();
  if (object.condenserWaterTemperatureControlType()) {
    EXPECT_NE("SpecifiedSetpoint", object.condenserWaterTemperatureControlType().get());
  }

  EXPECT_TRUE(object.setChilledWaterSupplySideBypassPipe(false));
  EXPECT_FALSE(object.chilledWaterSupplySideBypassPipe());
  object.resetChilledWaterSupplySideBypassPipe();
  EXPECT_TRUE(object.chilledWaterSupplySideBypassPipe());

  EXPECT_TRUE(object.setMinimumOutdoorDryBulbTemperature(-5.0));
  ASSERT_TRUE(object.minimumOutdoorDryBulbTemperature());
  EXPECT_DOUBLE_EQ(-5.0, object.minimumOutdoorDryBulbTemperature().get());
  object.resetMinimumOutdoorDryBulbTemperature();
  EXPECT_FALSE(object.minimumOutdoorDryBulbTemperature());

  EXPECT_TRUE(object.setCondenserWaterLoadDistributionScheme("UniformLoad"));
  EXPECT_EQ("UniformLoad", object.condenserWaterLoadDistributionScheme());
  EXPECT_FALSE(object.isCondenserWaterLoadDistributionSchemeDefaulted());
  object.resetCondenserWaterLoadDistributionScheme();
  EXPECT_TRUE(object.isCondenserWaterLoadDistributionSchemeDefaulted());

  EXPECT_GE(HVACTemplatePlantChilledWaterLoop::pumpControlTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplatePlantChilledWaterLoop::condenserWaterTemperatureControlTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplatePlantChilledWaterLoop::fluidTypeValues().size(), 1u);
}
