/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/DesignSpecificationAirTerminalSizing.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, DesignSpecificationAirTerminalSizing_DefaultConstructor) {
  Model model;
  DesignSpecificationAirTerminalSizing object(model);
  EXPECT_EQ(DesignSpecificationAirTerminalSizing::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, DesignSpecificationAirTerminalSizing_ScalarAccessors_RoundTrip) {
  Model model;
  DesignSpecificationAirTerminalSizing object(model);

  EXPECT_TRUE(object.isFractionofDesignCoolingLoadDefaulted());
  EXPECT_DOUBLE_EQ(1.0, object.fractionofDesignCoolingLoad());
  EXPECT_TRUE(object.setFractionofDesignCoolingLoad(0.8));
  EXPECT_DOUBLE_EQ(0.8, object.fractionofDesignCoolingLoad());
  EXPECT_FALSE(object.isFractionofDesignCoolingLoadDefaulted());
  EXPECT_FALSE(object.setFractionofDesignCoolingLoad(-0.1));
  object.resetFractionofDesignCoolingLoad();
  EXPECT_TRUE(object.isFractionofDesignCoolingLoadDefaulted());
  EXPECT_DOUBLE_EQ(1.0, object.fractionofDesignCoolingLoad());

  EXPECT_TRUE(object.isCoolingDesignSupplyAirTemperatureDifferenceRatioDefaulted());
  EXPECT_DOUBLE_EQ(1.0, object.coolingDesignSupplyAirTemperatureDifferenceRatio());
  EXPECT_TRUE(object.setCoolingDesignSupplyAirTemperatureDifferenceRatio(0.95));
  EXPECT_DOUBLE_EQ(0.95, object.coolingDesignSupplyAirTemperatureDifferenceRatio());
  EXPECT_FALSE(object.isCoolingDesignSupplyAirTemperatureDifferenceRatioDefaulted());
  EXPECT_FALSE(object.setCoolingDesignSupplyAirTemperatureDifferenceRatio(0.0));
  object.resetCoolingDesignSupplyAirTemperatureDifferenceRatio();
  EXPECT_TRUE(object.isCoolingDesignSupplyAirTemperatureDifferenceRatioDefaulted());
  EXPECT_DOUBLE_EQ(1.0, object.coolingDesignSupplyAirTemperatureDifferenceRatio());

  EXPECT_TRUE(object.isFractionofDesignHeatingLoadDefaulted());
  EXPECT_DOUBLE_EQ(1.0, object.fractionofDesignHeatingLoad());
  EXPECT_TRUE(object.setFractionofDesignHeatingLoad(0.9));
  EXPECT_DOUBLE_EQ(0.9, object.fractionofDesignHeatingLoad());
  EXPECT_FALSE(object.isFractionofDesignHeatingLoadDefaulted());
  EXPECT_FALSE(object.setFractionofDesignHeatingLoad(-0.1));
  object.resetFractionofDesignHeatingLoad();
  EXPECT_TRUE(object.isFractionofDesignHeatingLoadDefaulted());
  EXPECT_DOUBLE_EQ(1.0, object.fractionofDesignHeatingLoad());

  EXPECT_TRUE(object.isHeatingDesignSupplyAirTemperatureDifferenceRatioDefaulted());
  EXPECT_DOUBLE_EQ(1.0, object.heatingDesignSupplyAirTemperatureDifferenceRatio());
  EXPECT_TRUE(object.setHeatingDesignSupplyAirTemperatureDifferenceRatio(1.05));
  EXPECT_DOUBLE_EQ(1.05, object.heatingDesignSupplyAirTemperatureDifferenceRatio());
  EXPECT_FALSE(object.isHeatingDesignSupplyAirTemperatureDifferenceRatioDefaulted());
  EXPECT_FALSE(object.setHeatingDesignSupplyAirTemperatureDifferenceRatio(0.0));
  object.resetHeatingDesignSupplyAirTemperatureDifferenceRatio();
  EXPECT_TRUE(object.isHeatingDesignSupplyAirTemperatureDifferenceRatioDefaulted());
  EXPECT_DOUBLE_EQ(1.0, object.heatingDesignSupplyAirTemperatureDifferenceRatio());

  EXPECT_TRUE(object.isFractionofMinimumOutdoorAirFlowDefaulted());
  EXPECT_DOUBLE_EQ(1.0, object.fractionofMinimumOutdoorAirFlow());
  EXPECT_TRUE(object.setFractionofMinimumOutdoorAirFlow(0.85));
  EXPECT_DOUBLE_EQ(0.85, object.fractionofMinimumOutdoorAirFlow());
  EXPECT_FALSE(object.isFractionofMinimumOutdoorAirFlowDefaulted());
  EXPECT_FALSE(object.setFractionofMinimumOutdoorAirFlow(-0.1));
  object.resetFractionofMinimumOutdoorAirFlow();
  EXPECT_TRUE(object.isFractionofMinimumOutdoorAirFlowDefaulted());
  EXPECT_DOUBLE_EQ(1.0, object.fractionofMinimumOutdoorAirFlow());
}
