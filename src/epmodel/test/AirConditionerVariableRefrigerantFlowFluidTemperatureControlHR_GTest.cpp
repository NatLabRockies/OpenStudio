/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_DefaultConstructor) {
  Model model;
  AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR vrf(model);
  EXPECT_EQ(AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::iddObjectType(), vrf.iddObject().type());
  EXPECT_FALSE(vrf.nameString().empty());
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_ScalarAccessors_RoundTrip) {
  Model model;
  AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR vrf(model);

  EXPECT_FALSE(vrf.refrigerantType().empty());

  EXPECT_TRUE(vrf.setRatedEvaporativeCapacity(45678.0));
  ASSERT_TRUE(vrf.ratedEvaporativeCapacity());
  EXPECT_DOUBLE_EQ(45678.0, vrf.ratedEvaporativeCapacity().get());
  EXPECT_FALSE(vrf.isRatedEvaporativeCapacityAutosized());
  vrf.autosizeRatedEvaporativeCapacity();
  EXPECT_TRUE(vrf.isRatedEvaporativeCapacityAutosized());

  EXPECT_TRUE(vrf.setMinimumOutdoorTemperatureinHeatRecoveryMode(-25.0));
  EXPECT_DOUBLE_EQ(-25.0, vrf.minimumOutdoorTemperatureinHeatRecoveryMode());

  EXPECT_TRUE(vrf.setDefrostStrategy("Resistive"));
  EXPECT_EQ("Resistive", vrf.defrostStrategy());

  EXPECT_TRUE(vrf.setDefrostControl("Timed"));
  EXPECT_EQ("Timed", vrf.defrostControl());

  EXPECT_TRUE(vrf.setResistiveDefrostHeaterCapacity(123.0));
  ASSERT_TRUE(vrf.resistiveDefrostHeaterCapacity());
  EXPECT_DOUBLE_EQ(123.0, vrf.resistiveDefrostHeaterCapacity().get());
  EXPECT_FALSE(vrf.isResistiveDefrostHeaterCapacityAutosized());
  vrf.autosizeResistiveDefrostHeaterCapacity();
  EXPECT_TRUE(vrf.isResistiveDefrostHeaterCapacityAutosized());

  EXPECT_TRUE(vrf.setInitialHeatRecoveryCoolingCapacityFraction(0.55));
  EXPECT_DOUBLE_EQ(0.55, vrf.initialHeatRecoveryCoolingCapacityFraction());

  EXPECT_TRUE(vrf.setHeatRecoveryHeatingEnergyTimeConstant(22.0));
  EXPECT_DOUBLE_EQ(22.0, vrf.heatRecoveryHeatingEnergyTimeConstant());

  EXPECT_TRUE(vrf.setCompressorMaximumDeltaPressure(4.1e6));
  EXPECT_DOUBLE_EQ(4.1e6, vrf.compressorMaximumDeltaPressure());

  EXPECT_TRUE(vrf.setCompressorInverterEfficiency(0.95));
  EXPECT_DOUBLE_EQ(0.95, vrf.compressorInverterEfficiency());
}
