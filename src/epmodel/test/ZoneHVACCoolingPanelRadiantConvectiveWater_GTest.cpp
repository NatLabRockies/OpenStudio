/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../StraightComponent/Node.hpp"
#include "ZoneHVACComponent/ZoneHVACCoolingPanelRadiantConvectiveWater.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACCoolingPanelRadiantConvectiveWater_DefaultConstructor) {
  Model model;
  ZoneHVACCoolingPanelRadiantConvectiveWater panel(model);

  EXPECT_EQ(ZoneHVACCoolingPanelRadiantConvectiveWater::iddObjectType(), panel.iddObject().type());
  EXPECT_FALSE(panel.nameString().empty());
  EXPECT_EQ(0u, panel.inletPort());
  EXPECT_EQ(0u, panel.outletPort());
}

TEST_F(EPModelFixture, ZoneHVACCoolingPanelRadiantConvectiveWater_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACCoolingPanelRadiantConvectiveWater panel(model);

  EXPECT_DOUBLE_EQ(5.0, panel.ratedInletWaterTemperature());
  EXPECT_TRUE(panel.isRatedInletWaterTemperatureDefaulted());
  EXPECT_TRUE(panel.setRatedInletWaterTemperature(7.5));
  EXPECT_DOUBLE_EQ(7.5, panel.ratedInletWaterTemperature());
  EXPECT_FALSE(panel.isRatedInletWaterTemperatureDefaulted());
  panel.resetRatedInletWaterTemperature();
  EXPECT_TRUE(panel.isRatedInletWaterTemperatureDefaulted());

  EXPECT_DOUBLE_EQ(24.0, panel.ratedInletSpaceTemperature());
  EXPECT_TRUE(panel.isRatedInletSpaceTemperatureDefaulted());
  EXPECT_TRUE(panel.setRatedInletSpaceTemperature(22.5));
  EXPECT_DOUBLE_EQ(22.5, panel.ratedInletSpaceTemperature());
  panel.resetRatedInletSpaceTemperature();
  EXPECT_TRUE(panel.isRatedInletSpaceTemperatureDefaulted());

  EXPECT_DOUBLE_EQ(0.063, panel.ratedWaterMassFlowRate());
  EXPECT_TRUE(panel.isRatedWaterMassFlowRateDefaulted());
  EXPECT_TRUE(panel.setRatedWaterMassFlowRate(0.075));
  EXPECT_DOUBLE_EQ(0.075, panel.ratedWaterMassFlowRate());
  panel.resetRatedWaterMassFlowRate();
  EXPECT_TRUE(panel.isRatedWaterMassFlowRateDefaulted());

  EXPECT_DOUBLE_EQ(0.5, panel.coolingControlThrottlingRange());
  EXPECT_TRUE(panel.isCoolingControlThrottlingRangeDefaulted());
  EXPECT_TRUE(panel.setCoolingControlThrottlingRange(0.75));
  EXPECT_DOUBLE_EQ(0.75, panel.coolingControlThrottlingRange());
  EXPECT_FALSE(panel.isCoolingControlThrottlingRangeDefaulted());
  panel.resetCoolingControlThrottlingRange();
  EXPECT_TRUE(panel.isCoolingControlThrottlingRangeDefaulted());

  EXPECT_DOUBLE_EQ(1.0, panel.condensationControlDewpointOffset());
  EXPECT_TRUE(panel.isCondensationControlDewpointOffsetDefaulted());
  EXPECT_TRUE(panel.setCondensationControlDewpointOffset(1.5));
  EXPECT_DOUBLE_EQ(1.5, panel.condensationControlDewpointOffset());
  EXPECT_FALSE(panel.isCondensationControlDewpointOffsetDefaulted());
  panel.resetCondensationControlDewpointOffset();
  EXPECT_TRUE(panel.isCondensationControlDewpointOffsetDefaulted());

  EXPECT_TRUE(panel.setCoolingDesignCapacity(12000.0));
  ASSERT_TRUE(panel.coolingDesignCapacity());
  EXPECT_DOUBLE_EQ(12000.0, panel.coolingDesignCapacity().get());
  EXPECT_FALSE(panel.isCoolingDesignCapacityAutosized());
  panel.autosizeCoolingDesignCapacity();
  EXPECT_TRUE(panel.isCoolingDesignCapacityAutosized());

  EXPECT_TRUE(panel.setMaximumChilledWaterFlowRate(0.08));
  ASSERT_TRUE(panel.maximumChilledWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.08, panel.maximumChilledWaterFlowRate().get());
  EXPECT_FALSE(panel.isMaximumChilledWaterFlowRateAutosized());
  panel.autosizeMaximumChilledWaterFlowRate();
  EXPECT_TRUE(panel.isMaximumChilledWaterFlowRateAutosized());

  EXPECT_TRUE(panel.setControlType("OutdoorDryBulbTemperature"));
  EXPECT_EQ("OutdoorDryBulbTemperature", panel.controlType());
  panel.resetControlType();
  EXPECT_TRUE(panel.isControlTypeDefaulted());

  EXPECT_TRUE(panel.setFractionRadiant(0.6));
  EXPECT_DOUBLE_EQ(0.6, panel.fractionRadiant());

  EXPECT_TRUE(panel.setFractionOfRadiantEnergyIncidentOnPeople(0.25));
  ASSERT_TRUE(panel.fractionOfRadiantEnergyIncidentOnPeople());
  EXPECT_DOUBLE_EQ(0.25, panel.fractionOfRadiantEnergyIncidentOnPeople().get());

  EXPECT_TRUE(panel.setCondensationControlType("VariableOff"));
  EXPECT_EQ("VariableOff", panel.condensationControlType());
  panel.resetCondensationControlType();
  EXPECT_TRUE(panel.isCondensationControlTypeDefaulted());
}

TEST_F(EPModelFixture, ZoneHVACCoolingPanelRadiantConvectiveWater_ZoneAttachment) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACCoolingPanelRadiantConvectiveWater panel(model);

  EXPECT_TRUE(panel.addToThermalZone(zone));
  ASSERT_TRUE(panel.thermalZone());
  EXPECT_EQ(zone, panel.thermalZone().get());
  EXPECT_FALSE(panel.inletNode());
  EXPECT_FALSE(panel.outletNode());

  panel.removeFromThermalZone();
  EXPECT_FALSE(panel.thermalZone());
}
