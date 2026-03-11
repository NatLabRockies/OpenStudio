/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ZoneHVACComponent/ZoneHVACLowTempRadiantConstFlow.hpp"

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantConstFlow_DefaultConstructor) {
  Model model;
  ZoneHVACLowTempRadiantConstFlow radiant(model);

  EXPECT_FALSE(radiant.hydronicTubingLength());
  EXPECT_FALSE(radiant.ratedFlowRate());
}

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantConstFlow_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACLowTempRadiantConstFlow radiant(model);

  EXPECT_TRUE(radiant.setHydronicTubingLength(200.0));
  ASSERT_TRUE(radiant.hydronicTubingLength());
  EXPECT_DOUBLE_EQ(200.0, radiant.hydronicTubingLength().get());
  radiant.autosizeHydronicTubingLength();
  EXPECT_TRUE(radiant.isHydronicTubingLengthAutosized());

  EXPECT_TRUE(radiant.setRatedFlowRate(0.25));
  ASSERT_TRUE(radiant.ratedFlowRate());
  EXPECT_DOUBLE_EQ(0.25, radiant.ratedFlowRate().get());
  radiant.autosizeRatedFlowRate();
  EXPECT_TRUE(radiant.isRatedFlowRateAutosized());

  EXPECT_TRUE(radiant.setRatedPumpHead(150000));
  EXPECT_DOUBLE_EQ(150000, radiant.ratedPumpHead());
  radiant.resetRatedPumpHead();
  EXPECT_TRUE(radiant.isRatedPumpHeadDefaulted());

  EXPECT_TRUE(radiant.setRatedPowerConsumption(1200));
  ASSERT_TRUE(radiant.ratedPowerConsumption());
  EXPECT_DOUBLE_EQ(1200, radiant.ratedPowerConsumption().get());
  radiant.resetRatedPowerConsumption();
  EXPECT_FALSE(radiant.ratedPowerConsumption());

  EXPECT_TRUE(radiant.setFluidtoRadiantSurfaceHeatTransferModel("ISOStandard"));
  EXPECT_EQ("ISOStandard", radiant.fluidtoRadiantSurfaceHeatTransferModel());
  radiant.resetFluidtoRadiantSurfaceHeatTransferModel();
  EXPECT_TRUE(radiant.isFluidtoRadiantSurfaceHeatTransferModelDefaulted());

  EXPECT_TRUE(radiant.setHydronicTubingInsideDiameter(0.02));
  EXPECT_DOUBLE_EQ(0.02, radiant.hydronicTubingInsideDiameter());
  radiant.resetHydronicTubingInsideDiameter();
  EXPECT_TRUE(radiant.isHydronicTubingInsideDiameterDefaulted());

  EXPECT_TRUE(radiant.setHydronicTubingOutsideDiameter(0.024));
  EXPECT_DOUBLE_EQ(0.024, radiant.hydronicTubingOutsideDiameter());
  radiant.resetHydronicTubingOutsideDiameter();
  EXPECT_TRUE(radiant.isHydronicTubingOutsideDiameterDefaulted());

  EXPECT_TRUE(radiant.setHydronicTubingConductivity(0.45));
  EXPECT_DOUBLE_EQ(0.45, radiant.hydronicTubingConductivity());
  radiant.resetHydronicTubingConductivity();
  EXPECT_TRUE(radiant.isHydronicTubingConductivityDefaulted());

  EXPECT_TRUE(radiant.setTemperatureControlType("SurfaceFaceTemperature"));
  EXPECT_EQ("SurfaceFaceTemperature", radiant.temperatureControlType());
  radiant.resetTemperatureControlType();
  EXPECT_TRUE(radiant.isTemperatureControlTypeDefaulted());

  EXPECT_TRUE(radiant.setRunningMeanOutdoorDryBulbTemperatureWeightingFactor(0.5));
  EXPECT_DOUBLE_EQ(0.5, radiant.runningMeanOutdoorDryBulbTemperatureWeightingFactor());
  radiant.resetRunningMeanOutdoorDryBulbTemperatureWeightingFactor();
  EXPECT_TRUE(radiant.isRunningMeanOutdoorDryBulbTemperatureWeightingFactorDefaulted());

  EXPECT_TRUE(radiant.setMotorEfficiency(0.95));
  EXPECT_DOUBLE_EQ(0.95, radiant.motorEfficiency());
  radiant.resetMotorEfficiency();
  EXPECT_TRUE(radiant.isMotorEfficiencyDefaulted());

  EXPECT_TRUE(radiant.setFractionofMotorInefficienciestoFluidStream(0.1));
  EXPECT_DOUBLE_EQ(0.1, radiant.fractionofMotorInefficienciestoFluidStream());
  radiant.resetFractionofMotorInefficienciestoFluidStream();
  EXPECT_TRUE(radiant.isFractionofMotorInefficienciestoFluidStreamDefaulted());

  EXPECT_TRUE(radiant.setNumberofCircuits("CalculateFromCircuitLength"));
  EXPECT_EQ("CalculateFromCircuitLength", radiant.numberofCircuits());
  radiant.resetNumberofCircuits();
  EXPECT_TRUE(radiant.isNumberofCircuitsDefaulted());

  EXPECT_TRUE(radiant.setCircuitLength(200.0));
  EXPECT_DOUBLE_EQ(200.0, radiant.circuitLength());
  radiant.resetCircuitLength();
  EXPECT_TRUE(radiant.isCircuitLengthDefaulted());
}
