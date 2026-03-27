/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACHighTemperatureRadiant.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACHighTemperatureRadiant_DefaultConstructor) {
  Model model;
  ZoneHVACHighTemperatureRadiant radiant(model);

  EXPECT_TRUE(radiant.isMaximumPowerInputAutosized());
  EXPECT_FALSE(radiant.maximumPowerInput());
  EXPECT_EQ("NaturalGas", radiant.fuelType());
  EXPECT_DOUBLE_EQ(0.90, radiant.combustionEfficiency());
  EXPECT_DOUBLE_EQ(0.70, radiant.fractionofInputConvertedtoRadiantEnergy());
  EXPECT_DOUBLE_EQ(0.0, radiant.fractionofInputConvertedtoLatentEnergy());
  EXPECT_DOUBLE_EQ(0.0, radiant.fractionofInputthatIsLost());
  EXPECT_EQ("OperativeTemperature", radiant.temperatureControlType());
  EXPECT_DOUBLE_EQ(2.0, radiant.heatingThrottlingRange());
  EXPECT_DOUBLE_EQ(0.04, radiant.fractionofRadiantEnergyIncidentonPeople());
  EXPECT_FALSE(radiant.isFuelTypeDefaulted());
  EXPECT_FALSE(radiant.isCombustionEfficiencyDefaulted());
  EXPECT_FALSE(radiant.isFractionofInputConvertedtoRadiantEnergyDefaulted());
  EXPECT_FALSE(radiant.isFractionofInputConvertedtoLatentEnergyDefaulted());
  EXPECT_FALSE(radiant.isFractionofInputthatIsLostDefaulted());
  EXPECT_FALSE(radiant.isTemperatureControlTypeDefaulted());
  EXPECT_FALSE(radiant.isHeatingThrottlingRangeDefaulted());
  EXPECT_EQ(0u, radiant.inletPort());
  EXPECT_EQ(0u, radiant.outletPort());
}

TEST_F(EPModelFixture, ZoneHVACHighTemperatureRadiant_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACHighTemperatureRadiant radiant(model);

  EXPECT_TRUE(radiant.setMaximumPowerInput(12000.0));
  ASSERT_TRUE(radiant.maximumPowerInput());
  EXPECT_DOUBLE_EQ(12000.0, radiant.maximumPowerInput().get());
  EXPECT_FALSE(radiant.isMaximumPowerInputAutosized());
  radiant.autosizeMaximumPowerInput();
  EXPECT_TRUE(radiant.isMaximumPowerInputAutosized());
  EXPECT_FALSE(radiant.maximumPowerInput());

  EXPECT_TRUE(radiant.setFuelType("Electricity"));
  EXPECT_FALSE(radiant.isFuelTypeDefaulted());
  radiant.resetFuelType();
  EXPECT_TRUE(radiant.isFuelTypeDefaulted());
  EXPECT_TRUE(radiant.setFuelType("Electricity"));

  EXPECT_TRUE(radiant.setCombustionEfficiency(0.92));
  EXPECT_FALSE(radiant.isCombustionEfficiencyDefaulted());
  radiant.resetCombustionEfficiency();
  EXPECT_TRUE(radiant.isCombustionEfficiencyDefaulted());
  EXPECT_TRUE(radiant.setCombustionEfficiency(0.92));

  EXPECT_TRUE(radiant.setFractionofInputConvertedtoRadiantEnergy(0.55));
  EXPECT_FALSE(radiant.isFractionofInputConvertedtoRadiantEnergyDefaulted());
  radiant.resetFractionofInputConvertedtoRadiantEnergy();
  EXPECT_TRUE(radiant.isFractionofInputConvertedtoRadiantEnergyDefaulted());
  EXPECT_TRUE(radiant.setFractionofInputConvertedtoRadiantEnergy(0.55));

  EXPECT_TRUE(radiant.setFractionofInputConvertedtoLatentEnergy(0.12));
  EXPECT_FALSE(radiant.isFractionofInputConvertedtoLatentEnergyDefaulted());
  EXPECT_TRUE(radiant.setFractionofInputthatIsLost(0.08));
  EXPECT_FALSE(radiant.isFractionofInputthatIsLostDefaulted());

  EXPECT_TRUE(radiant.setTemperatureControlType("MeanAirTemperature"));
  EXPECT_EQ("MeanAirTemperature", radiant.temperatureControlType());
  radiant.resetTemperatureControlType();
  EXPECT_TRUE(radiant.isTemperatureControlTypeDefaulted());
  EXPECT_TRUE(radiant.setTemperatureControlType("MeanAirTemperature"));

  EXPECT_TRUE(radiant.setHeatingThrottlingRange(1.5));
  EXPECT_DOUBLE_EQ(1.5, radiant.heatingThrottlingRange());
  radiant.resetHeatingThrottlingRange();
  EXPECT_TRUE(radiant.isHeatingThrottlingRangeDefaulted());
  EXPECT_TRUE(radiant.setHeatingThrottlingRange(1.5));

  EXPECT_TRUE(radiant.setFractionofRadiantEnergyIncidentonPeople(0.21));
  EXPECT_DOUBLE_EQ(0.21, radiant.fractionofRadiantEnergyIncidentonPeople());
}

TEST_F(EPModelFixture, ZoneHVACHighTemperatureRadiant_ZoneAttachment) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACHighTemperatureRadiant radiant(model);

  EXPECT_TRUE(radiant.addToThermalZone(zone));
  ASSERT_TRUE(radiant.thermalZone());
  EXPECT_EQ(zone, radiant.thermalZone().get());
  EXPECT_FALSE(radiant.inletNode());
  EXPECT_FALSE(radiant.outletNode());

  radiant.removeFromThermalZone();
  EXPECT_FALSE(radiant.thermalZone());
}
