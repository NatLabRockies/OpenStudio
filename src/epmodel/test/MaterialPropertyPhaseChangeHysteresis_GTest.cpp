/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/MaterialPropertyPhaseChangeHysteresis.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, MaterialPropertyPhaseChangeHysteresis_DefaultConstructor) {
  Model model;
  MaterialPropertyPhaseChangeHysteresis object(model);
  EXPECT_EQ(MaterialPropertyPhaseChangeHysteresis::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, MaterialPropertyPhaseChangeHysteresis_ScalarAccessors_RoundTrip) {
  Model model;
  MaterialPropertyPhaseChangeHysteresis object(model);

  EXPECT_TRUE(object.setLatentHeatduringtheEntirePhaseChangeProcess(10000.0));
  EXPECT_DOUBLE_EQ(10000.0, object.latentHeatduringtheEntirePhaseChangeProcess());

  EXPECT_TRUE(object.setLiquidStateThermalConductivity(1.5));
  EXPECT_DOUBLE_EQ(1.5, object.liquidStateThermalConductivity());

  EXPECT_TRUE(object.setLiquidStateDensity(2200.0));
  EXPECT_DOUBLE_EQ(2200.0, object.liquidStateDensity());

  EXPECT_TRUE(object.setLiquidStateSpecificHeat(2000.0));
  EXPECT_DOUBLE_EQ(2000.0, object.liquidStateSpecificHeat());

  EXPECT_TRUE(object.setHighTemperatureDifferenceofMeltingCurve(1.0));
  EXPECT_DOUBLE_EQ(1.0, object.highTemperatureDifferenceofMeltingCurve());

  EXPECT_TRUE(object.setPeakMeltingTemperature(23.0));
  EXPECT_DOUBLE_EQ(23.0, object.peakMeltingTemperature());

  EXPECT_TRUE(object.setLowTemperatureDifferenceofMeltingCurve(1.0));
  EXPECT_DOUBLE_EQ(1.0, object.lowTemperatureDifferenceofMeltingCurve());

  EXPECT_TRUE(object.setSolidStateThermalConductivity(1.8));
  EXPECT_DOUBLE_EQ(1.8, object.solidStateThermalConductivity());

  EXPECT_TRUE(object.setSolidStateDensity(2300.0));
  EXPECT_DOUBLE_EQ(2300.0, object.solidStateDensity());

  EXPECT_TRUE(object.setSolidStateSpecificHeat(2000.0));
  EXPECT_DOUBLE_EQ(2000.0, object.solidStateSpecificHeat());

  EXPECT_TRUE(object.setHighTemperatureDifferenceofFreezingCurve(1.0));
  EXPECT_DOUBLE_EQ(1.0, object.highTemperatureDifferenceofFreezingCurve());

  EXPECT_TRUE(object.setPeakFreezingTemperature(20.0));
  EXPECT_DOUBLE_EQ(20.0, object.peakFreezingTemperature());

  EXPECT_TRUE(object.setLowTemperatureDifferenceofFreezingCurve(1.0));
  EXPECT_DOUBLE_EQ(1.0, object.lowTemperatureDifferenceofFreezingCurve());
}
