/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SolarCollectorPerformancePhotovoltaicThermalSimple.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SolarCollectorPerformancePhotovoltaicThermalSimple_DefaultConstructor) {
  Model model;
  SolarCollectorPerformancePhotovoltaicThermalSimple object(model);
  EXPECT_EQ(SolarCollectorPerformancePhotovoltaicThermalSimple::iddObjectType(), object.iddObject().type());
  EXPECT_FALSE(object.nameString().empty());
}

TEST_F(EPModelFixture, SolarCollectorPerformancePhotovoltaicThermalSimple_ScalarAccessors_RoundTrip) {
  Model model;
  SolarCollectorPerformancePhotovoltaicThermalSimple object(model);

  const auto thermalConversionEfficiencyInputModeTypeValues =
    SolarCollectorPerformancePhotovoltaicThermalSimple::thermalConversionEfficiencyInputModeTypeValues();
  EXPECT_FALSE(thermalConversionEfficiencyInputModeTypeValues.empty());
  EXPECT_FALSE(object.thermalConversionEfficiencyInputModeType().empty());

  EXPECT_TRUE(object.setFractionOfSurfaceAreaWithActiveThermalCollector(0.62));
  EXPECT_DOUBLE_EQ(0.62, object.fractionOfSurfaceAreaWithActiveThermalCollector());

  EXPECT_TRUE(object.setThermalConversionEfficiency(0.37));
  EXPECT_TRUE(object.thermalConversionEfficiency());
  EXPECT_DOUBLE_EQ(0.37, object.thermalConversionEfficiency().get());
  EXPECT_EQ("Fixed", object.thermalConversionEfficiencyInputModeType());

  object.resetThermalConversionEfficiency();
  EXPECT_TRUE(object.thermalConversionEfficiency());
  EXPECT_DOUBLE_EQ(0.3, object.thermalConversionEfficiency().get());

  EXPECT_TRUE(object.setFrontSurfaceEmittance(0.84));
  EXPECT_DOUBLE_EQ(0.84, object.frontSurfaceEmittance());

  object.resetFrontSurfaceEmittance();
  EXPECT_TRUE(object.isFrontSurfaceEmittanceDefaulted());
}
