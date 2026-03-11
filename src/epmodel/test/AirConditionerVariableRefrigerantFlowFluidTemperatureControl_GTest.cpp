/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/AirConditionerVariableRefrigerantFlowFluidTemperatureControl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlowFluidTemperatureControl_DefaultConstructor) {
  Model model;
  AirConditionerVariableRefrigerantFlowFluidTemperatureControl vrf(model);
  EXPECT_EQ(AirConditionerVariableRefrigerantFlowFluidTemperatureControl::iddObjectType(), vrf.iddObject().type());
  EXPECT_FALSE(vrf.nameString().empty());
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlowFluidTemperatureControl_ScalarAccessors_RoundTrip) {
  Model model;
  AirConditionerVariableRefrigerantFlowFluidTemperatureControl vrf(model);

  EXPECT_FALSE(vrf.refrigerantType().empty());

  EXPECT_TRUE(vrf.setRatedEvaporativeCapacity(45678.0));
  ASSERT_TRUE(vrf.ratedEvaporativeCapacity());
  EXPECT_DOUBLE_EQ(45678.0, vrf.ratedEvaporativeCapacity().get());
  EXPECT_FALSE(vrf.isRatedEvaporativeCapacityAutosized());
  vrf.autosizeRatedEvaporativeCapacity();
  EXPECT_TRUE(vrf.isRatedEvaporativeCapacityAutosized());

  EXPECT_TRUE(vrf.setRatedCompressorPowerPerUnitofRatedEvaporativeCapacity(0.41));
  EXPECT_DOUBLE_EQ(0.41, vrf.ratedCompressorPowerPerUnitofRatedEvaporativeCapacity());

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

  EXPECT_TRUE(vrf.setCompressorMaximumDeltaPressure(4.1e6));
  EXPECT_DOUBLE_EQ(4.1e6, vrf.compressorMaximumDeltaPressure());
}
