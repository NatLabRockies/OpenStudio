/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Generator/GeneratorMicroTurbine.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GeneratorMicroTurbine_DefaultConstructor) {
  Model model;
  GeneratorMicroTurbine generator(model);
  EXPECT_EQ(GeneratorMicroTurbine::iddObjectType(), generator.iddObject().type());
}

TEST_F(EPModelFixture, GeneratorMicroTurbine_ScalarAccessors_RoundTrip) {
  Model model;
  GeneratorMicroTurbine generator(model);

  EXPECT_TRUE(generator.setReferenceElectricalPowerOutput(65000.0));
  EXPECT_DOUBLE_EQ(65000.0, generator.referenceElectricalPowerOutput());

  EXPECT_TRUE(generator.setReferenceElectricalEfficiencyUsingLowerHeatingValue(0.29));
  EXPECT_DOUBLE_EQ(0.29, generator.referenceElectricalEfficiencyUsingLowerHeatingValue());

  EXPECT_TRUE(generator.isMinimumFullLoadElectricalPowerOutputDefaulted());
  EXPECT_DOUBLE_EQ(0.0, generator.minimumFullLoadElectricalPowerOutput());
  EXPECT_TRUE(generator.setMinimumFullLoadElectricalPowerOutput(10000.0));
  EXPECT_DOUBLE_EQ(10000.0, generator.minimumFullLoadElectricalPowerOutput());
  EXPECT_FALSE(generator.isMinimumFullLoadElectricalPowerOutputDefaulted());
  generator.resetMinimumFullLoadElectricalPowerOutput();
  EXPECT_TRUE(generator.isMinimumFullLoadElectricalPowerOutputDefaulted());
  EXPECT_DOUBLE_EQ(0.0, generator.minimumFullLoadElectricalPowerOutput());

  EXPECT_TRUE(generator.isMaximumFullLoadElectricalPowerOutputDefaulted());
  EXPECT_DOUBLE_EQ(65000.0, generator.maximumFullLoadElectricalPowerOutput());
  EXPECT_TRUE(generator.setMaximumFullLoadElectricalPowerOutput(70000.0));
  EXPECT_DOUBLE_EQ(70000.0, generator.maximumFullLoadElectricalPowerOutput());
  EXPECT_FALSE(generator.isMaximumFullLoadElectricalPowerOutputDefaulted());
  generator.resetMaximumFullLoadElectricalPowerOutput();
  EXPECT_TRUE(generator.isMaximumFullLoadElectricalPowerOutputDefaulted());
  EXPECT_DOUBLE_EQ(65000.0, generator.maximumFullLoadElectricalPowerOutput());

  EXPECT_TRUE(generator.isReferenceCombustionAirInletTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(15.0, generator.referenceCombustionAirInletTemperature());
  EXPECT_TRUE(generator.setReferenceCombustionAirInletTemperature(18.0));
  EXPECT_DOUBLE_EQ(18.0, generator.referenceCombustionAirInletTemperature());
  generator.resetReferenceCombustionAirInletTemperature();
  EXPECT_TRUE(generator.isReferenceCombustionAirInletTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(15.0, generator.referenceCombustionAirInletTemperature());

  EXPECT_TRUE(generator.isReferenceCombustionAirInletHumidityRatioDefaulted());
  EXPECT_DOUBLE_EQ(0.00638, generator.referenceCombustionAirInletHumidityRatio());
  EXPECT_TRUE(generator.setReferenceCombustionAirInletHumidityRatio(0.007));
  EXPECT_DOUBLE_EQ(0.007, generator.referenceCombustionAirInletHumidityRatio());
  generator.resetReferenceCombustionAirInletHumidityRatio();
  EXPECT_TRUE(generator.isReferenceCombustionAirInletHumidityRatioDefaulted());
  EXPECT_DOUBLE_EQ(0.00638, generator.referenceCombustionAirInletHumidityRatio());

  EXPECT_TRUE(generator.isReferenceElevationDefaulted());
  EXPECT_DOUBLE_EQ(0.0, generator.referenceElevation());
  EXPECT_TRUE(generator.setReferenceElevation(150.0));
  EXPECT_DOUBLE_EQ(150.0, generator.referenceElevation());
  generator.resetReferenceElevation();
  EXPECT_TRUE(generator.isReferenceElevationDefaulted());
  EXPECT_DOUBLE_EQ(0.0, generator.referenceElevation());

  EXPECT_TRUE(generator.isFuelTypeDefaulted());
  EXPECT_EQ("NaturalGas", generator.fuelType());
  const auto fuelTypes = GeneratorMicroTurbine::validFuelTypeValues();
  EXPECT_FALSE(fuelTypes.empty());
  EXPECT_TRUE(generator.setFuelType("Diesel"));
  EXPECT_EQ("Diesel", generator.fuelType());
  EXPECT_FALSE(generator.isFuelTypeDefaulted());
  generator.resetFuelType();
  EXPECT_TRUE(generator.isFuelTypeDefaulted());
  EXPECT_EQ("NaturalGas", generator.fuelType());

  EXPECT_TRUE(generator.isFuelHigherHeatingValueDefaulted());
  EXPECT_DOUBLE_EQ(50000.0, generator.fuelHigherHeatingValue());
  EXPECT_TRUE(generator.setFuelHigherHeatingValue(49000.0));
  EXPECT_DOUBLE_EQ(49000.0, generator.fuelHigherHeatingValue());
  generator.resetFuelHigherHeatingValue();
  EXPECT_TRUE(generator.isFuelHigherHeatingValueDefaulted());
  EXPECT_DOUBLE_EQ(50000.0, generator.fuelHigherHeatingValue());

  EXPECT_TRUE(generator.isFuelLowerHeatingValueDefaulted());
  EXPECT_DOUBLE_EQ(45450.0, generator.fuelLowerHeatingValue());
  EXPECT_TRUE(generator.setFuelLowerHeatingValue(44500.0));
  EXPECT_DOUBLE_EQ(44500.0, generator.fuelLowerHeatingValue());
  generator.resetFuelLowerHeatingValue();
  EXPECT_TRUE(generator.isFuelLowerHeatingValueDefaulted());
  EXPECT_DOUBLE_EQ(45450.0, generator.fuelLowerHeatingValue());

  EXPECT_TRUE(generator.isStandbyPowerDefaulted());
  EXPECT_DOUBLE_EQ(0.0, generator.standbyPower());
  EXPECT_TRUE(generator.setStandbyPower(125.0));
  EXPECT_DOUBLE_EQ(125.0, generator.standbyPower());
  generator.resetStandbyPower();
  EXPECT_TRUE(generator.isStandbyPowerDefaulted());
  EXPECT_DOUBLE_EQ(0.0, generator.standbyPower());

  EXPECT_TRUE(generator.isAncillaryPowerDefaulted());
  EXPECT_DOUBLE_EQ(0.0, generator.ancillaryPower());
  EXPECT_TRUE(generator.setAncillaryPower(150.0));
  EXPECT_DOUBLE_EQ(150.0, generator.ancillaryPower());
  generator.resetAncillaryPower();
  EXPECT_TRUE(generator.isAncillaryPowerDefaulted());
  EXPECT_DOUBLE_EQ(0.0, generator.ancillaryPower());

  EXPECT_FALSE(generator.referenceExhaustAirMassFlowRate());
  EXPECT_TRUE(generator.setReferenceExhaustAirMassFlowRate(0.75));
  ASSERT_TRUE(generator.referenceExhaustAirMassFlowRate());
  EXPECT_DOUBLE_EQ(0.75, generator.referenceExhaustAirMassFlowRate().get());
  generator.resetReferenceExhaustAirMassFlowRate();
  EXPECT_FALSE(generator.referenceExhaustAirMassFlowRate());

  EXPECT_FALSE(generator.nominalExhaustAirOutletTemperature());
  EXPECT_TRUE(generator.setNominalExhaustAirOutletTemperature(305.0));
  ASSERT_TRUE(generator.nominalExhaustAirOutletTemperature());
  EXPECT_DOUBLE_EQ(305.0, generator.nominalExhaustAirOutletTemperature().get());
  generator.resetNominalExhaustAirOutletTemperature();
  EXPECT_FALSE(generator.nominalExhaustAirOutletTemperature());
}
