/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/HVACTemplatePlantMixedWaterLoop.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplatePlantMixedWaterLoop_DefaultConstructor) {
  Model model;
  HVACTemplatePlantMixedWaterLoop object(model);
  EXPECT_EQ(HVACTemplatePlantMixedWaterLoop::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplatePlantMixedWaterLoop_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplatePlantMixedWaterLoop object(model);

  EXPECT_TRUE(object.setPumpControlType("Continuous"));
  EXPECT_EQ("Continuous", object.pumpControlType());
  EXPECT_FALSE(object.isPumpControlTypeDefaulted());
  object.resetPumpControlType();
  EXPECT_TRUE(object.isPumpControlTypeDefaulted());

  EXPECT_TRUE(object.setOperationSchemeType("UserDefined"));
  EXPECT_EQ("UserDefined", object.operationSchemeType());
  EXPECT_FALSE(object.isOperationSchemeTypeDefaulted());
  object.resetOperationSchemeType();
  EXPECT_TRUE(object.isOperationSchemeTypeDefaulted());

  EXPECT_TRUE(object.setHighTemperatureDesignSetpoint(35.0));
  EXPECT_DOUBLE_EQ(35.0, object.highTemperatureDesignSetpoint());
  object.resetHighTemperatureDesignSetpoint();
  EXPECT_TRUE(object.isHighTemperatureDesignSetpointDefaulted());

  EXPECT_TRUE(object.setLowTemperatureDesignSetpoint(19.0));
  EXPECT_DOUBLE_EQ(19.0, object.lowTemperatureDesignSetpoint());
  object.resetLowTemperatureDesignSetpoint();
  EXPECT_TRUE(object.isLowTemperatureDesignSetpointDefaulted());

  EXPECT_TRUE(object.setWaterPumpRatedHead(210000.0));
  EXPECT_DOUBLE_EQ(210000.0, object.waterPumpRatedHead());
  EXPECT_FALSE(object.setWaterPumpRatedHead(-1.0));

  EXPECT_TRUE(object.setSupplySideBypassPipe(false));
  EXPECT_FALSE(object.supplySideBypassPipe());
  object.resetSupplySideBypassPipe();
  EXPECT_TRUE(object.supplySideBypassPipe());

  EXPECT_TRUE(object.setDemandSideBypassPipe(false));
  EXPECT_FALSE(object.demandSideBypassPipe());
  object.resetDemandSideBypassPipe();
  EXPECT_TRUE(object.demandSideBypassPipe());

  EXPECT_TRUE(object.setFluidType("EthyleneGlycol30"));
  EXPECT_EQ("EthyleneGlycol30", object.fluidType());
  EXPECT_FALSE(object.isFluidTypeDefaulted());
  object.resetFluidType();
  EXPECT_TRUE(object.isFluidTypeDefaulted());

  EXPECT_TRUE(object.setLoopDesignDeltaTemperature(4.2));
  EXPECT_DOUBLE_EQ(4.2, object.loopDesignDeltaTemperature());

  EXPECT_TRUE(object.setLoadDistributionScheme("UniformLoad"));
  EXPECT_EQ("UniformLoad", object.loadDistributionScheme());
  EXPECT_FALSE(object.isLoadDistributionSchemeDefaulted());
  object.resetLoadDistributionScheme();
  EXPECT_TRUE(object.isLoadDistributionSchemeDefaulted());

  EXPECT_GE(HVACTemplatePlantMixedWaterLoop::pumpControlTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplatePlantMixedWaterLoop::operationSchemeTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplatePlantMixedWaterLoop::waterPumpConfigurationValues().size(), 1u);
  EXPECT_GE(HVACTemplatePlantMixedWaterLoop::waterPumpTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplatePlantMixedWaterLoop::fluidTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplatePlantMixedWaterLoop::loadDistributionSchemeValues().size(), 1u);
}
