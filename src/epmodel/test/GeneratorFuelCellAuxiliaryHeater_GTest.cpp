/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/GeneratorFuelCellAuxiliaryHeater.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GeneratorFuelCellAuxiliaryHeater_DefaultConstructor) {
  Model model;
  GeneratorFuelCellAuxiliaryHeater auxiliaryHeater(model);
  EXPECT_EQ(GeneratorFuelCellAuxiliaryHeater::iddObjectType(), auxiliaryHeater.iddObject().type());
}

TEST_F(EPModelFixture, GeneratorFuelCellAuxiliaryHeater_ScalarAccessors_RoundTrip) {
  Model model;
  GeneratorFuelCellAuxiliaryHeater auxiliaryHeater(model);

  EXPECT_TRUE(auxiliaryHeater.setExcessAirRatio(0.13));
  EXPECT_DOUBLE_EQ(0.13, auxiliaryHeater.excessAirRatio());
  auxiliaryHeater.resetExcessAirRatio();
  EXPECT_DOUBLE_EQ(0.0, auxiliaryHeater.excessAirRatio());

  EXPECT_TRUE(auxiliaryHeater.setAncillaryPowerConstantTerm(12.0));
  EXPECT_DOUBLE_EQ(12.0, auxiliaryHeater.ancillaryPowerConstantTerm());
  auxiliaryHeater.resetAncillaryPowerConstantTerm();
  EXPECT_DOUBLE_EQ(0.0, auxiliaryHeater.ancillaryPowerConstantTerm());

  EXPECT_TRUE(auxiliaryHeater.setAncillaryPowerLinearTerm(0.5));
  EXPECT_DOUBLE_EQ(0.5, auxiliaryHeater.ancillaryPowerLinearTerm());
  auxiliaryHeater.resetAncillaryPowerLinearTerm();
  EXPECT_DOUBLE_EQ(0.0, auxiliaryHeater.ancillaryPowerLinearTerm());

  EXPECT_TRUE(auxiliaryHeater.setSkinLossUFactorTimesAreaValue(0.87));
  EXPECT_DOUBLE_EQ(0.87, auxiliaryHeater.skinLossUFactorTimesAreaValue());
  auxiliaryHeater.resetSkinLossUFactorTimesAreaValue();
  EXPECT_DOUBLE_EQ(0.5, auxiliaryHeater.skinLossUFactorTimesAreaValue());

  auto skinLossDestinationValues = GeneratorFuelCellAuxiliaryHeater::skinLossDestinationValues();
  ASSERT_FALSE(skinLossDestinationValues.empty());
  EXPECT_TRUE(auxiliaryHeater.setSkinLossDestination(skinLossDestinationValues.front()));
  EXPECT_EQ(skinLossDestinationValues.front(), auxiliaryHeater.skinLossDestination());
  auxiliaryHeater.resetSkinLossDestination();
  EXPECT_EQ("AirInletForFuelCell", auxiliaryHeater.skinLossDestination());

  auto heatingCapacityUnitsValues = GeneratorFuelCellAuxiliaryHeater::heatingCapacityUnitsValues();
  ASSERT_FALSE(heatingCapacityUnitsValues.empty());
  EXPECT_TRUE(auxiliaryHeater.setHeatingCapacityUnits(heatingCapacityUnitsValues.front()));
  EXPECT_EQ(heatingCapacityUnitsValues.front(), auxiliaryHeater.heatingCapacityUnits());
  auxiliaryHeater.resetHeatingCapacityUnits();
  EXPECT_EQ("Watts", auxiliaryHeater.heatingCapacityUnits());

  EXPECT_TRUE(auxiliaryHeater.setMaximumHeatingCapacityinWatts(1500.0));
  EXPECT_DOUBLE_EQ(1500.0, auxiliaryHeater.maximumHeatingCapacityinWatts());
  auxiliaryHeater.resetMaximumHeatingCapacityinWatts();
  EXPECT_DOUBLE_EQ(0.0, auxiliaryHeater.maximumHeatingCapacityinWatts());

  EXPECT_TRUE(auxiliaryHeater.setMinimumHeatingCapacityinWatts(350.0));
  EXPECT_DOUBLE_EQ(350.0, auxiliaryHeater.minimumHeatingCapacityinWatts());
  auxiliaryHeater.resetMinimumHeatingCapacityinWatts();
  EXPECT_DOUBLE_EQ(0.0, auxiliaryHeater.minimumHeatingCapacityinWatts());

  EXPECT_TRUE(auxiliaryHeater.setMaximumHeatingCapacityinKmolperSecond(0.0043));
  EXPECT_DOUBLE_EQ(0.0043, auxiliaryHeater.maximumHeatingCapacityinKmolperSecond());
  auxiliaryHeater.resetMaximumHeatingCapacityinKmolperSecond();
  EXPECT_DOUBLE_EQ(0.0, auxiliaryHeater.maximumHeatingCapacityinKmolperSecond());

  EXPECT_TRUE(auxiliaryHeater.setMinimumHeatingCapacityinKmolperSecond(0.0018));
  EXPECT_DOUBLE_EQ(0.0018, auxiliaryHeater.minimumHeatingCapacityinKmolperSecond());
  auxiliaryHeater.resetMinimumHeatingCapacityinKmolperSecond();
  EXPECT_DOUBLE_EQ(0.0, auxiliaryHeater.minimumHeatingCapacityinKmolperSecond());
}
