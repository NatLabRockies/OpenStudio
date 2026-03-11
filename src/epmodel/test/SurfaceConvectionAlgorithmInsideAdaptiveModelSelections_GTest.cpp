/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SurfaceConvectionAlgorithmInsideAdaptiveModelSelections.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_DefaultConstructor) {
  Model model;
  SurfaceConvectionAlgorithmInsideAdaptiveModelSelections obj(model);
  EXPECT_EQ(SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::iddObjectType(), obj.iddObject().type());
}

TEST_F(EPModelFixture, SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_ScalarAccessors_RoundTrip) {
  Model model;
  SurfaceConvectionAlgorithmInsideAdaptiveModelSelections obj(model);

  // All 45 choice fields have defaults, so they should start as defaulted
  EXPECT_TRUE(obj.isSimpleBuoyancyVerticalWallEquationSourceDefaulted());
  EXPECT_FALSE(obj.simpleBuoyancyVerticalWallEquationSource().empty());

  // Test set / get / isDefaulted / reset cycle on a representative field
  EXPECT_TRUE(obj.setSimpleBuoyancyVerticalWallEquationSource("UserCurve"));
  EXPECT_EQ("UserCurve", obj.simpleBuoyancyVerticalWallEquationSource());
  EXPECT_FALSE(obj.isSimpleBuoyancyVerticalWallEquationSourceDefaulted());
  obj.resetSimpleBuoyancyVerticalWallEquationSource();
  EXPECT_TRUE(obj.isSimpleBuoyancyVerticalWallEquationSourceDefaulted());

  // Test a Floor Heat Ceiling Cool field
  EXPECT_TRUE(obj.isFloorHeatCeilingCoolVerticalWallEquationSourceDefaulted());
  EXPECT_TRUE(obj.setFloorHeatCeilingCoolVerticalWallEquationSource("UserCurve"));
  EXPECT_EQ("UserCurve", obj.floorHeatCeilingCoolVerticalWallEquationSource());
  EXPECT_FALSE(obj.isFloorHeatCeilingCoolVerticalWallEquationSourceDefaulted());
  obj.resetFloorHeatCeilingCoolVerticalWallEquationSource();
  EXPECT_TRUE(obj.isFloorHeatCeilingCoolVerticalWallEquationSourceDefaulted());

  // Test a Wall Panel Heating field
  EXPECT_TRUE(obj.isWallPanelHeatingVerticalWallEquationSourceDefaulted());
  EXPECT_TRUE(obj.setWallPanelHeatingVerticalWallEquationSource("UserCurve"));
  EXPECT_EQ("UserCurve", obj.wallPanelHeatingVerticalWallEquationSource());
  obj.resetWallPanelHeatingVerticalWallEquationSource();
  EXPECT_TRUE(obj.isWallPanelHeatingVerticalWallEquationSourceDefaulted());

  // Test a Convective Zone Heater field
  EXPECT_TRUE(obj.isConvectiveZoneHeaterVerticalWallEquationSourceDefaulted());
  EXPECT_TRUE(obj.setConvectiveZoneHeaterVerticalWallEquationSource("UserCurve"));
  EXPECT_EQ("UserCurve", obj.convectiveZoneHeaterVerticalWallEquationSource());
  obj.resetConvectiveZoneHeaterVerticalWallEquationSource();
  EXPECT_TRUE(obj.isConvectiveZoneHeaterVerticalWallEquationSourceDefaulted());

  // Test a Central Air Diffuser field
  EXPECT_TRUE(obj.isCentralAirDiffuserWallEquationSourceDefaulted());
  EXPECT_TRUE(obj.setCentralAirDiffuserWallEquationSource("UserCurve"));
  EXPECT_EQ("UserCurve", obj.centralAirDiffuserWallEquationSource());
  obj.resetCentralAirDiffuserWallEquationSource();
  EXPECT_TRUE(obj.isCentralAirDiffuserWallEquationSourceDefaulted());

  // Test a Mechanical Zone Fan Circulation field
  EXPECT_TRUE(obj.isMechanicalZoneFanCirculationVerticalWallEquationSourceDefaulted());
  EXPECT_TRUE(obj.setMechanicalZoneFanCirculationVerticalWallEquationSource("UserCurve"));
  EXPECT_EQ("UserCurve", obj.mechanicalZoneFanCirculationVerticalWallEquationSource());
  obj.resetMechanicalZoneFanCirculationVerticalWallEquationSource();
  EXPECT_TRUE(obj.isMechanicalZoneFanCirculationVerticalWallEquationSourceDefaulted());

  // Test a Mixed Regime field
  EXPECT_TRUE(obj.isMixedRegimeBuoyancyAssistingFlowonWallsEquationSourceDefaulted());
  EXPECT_TRUE(obj.setMixedRegimeBuoyancyAssistingFlowonWallsEquationSource("UserCurve"));
  EXPECT_EQ("UserCurve", obj.mixedRegimeBuoyancyAssistingFlowonWallsEquationSource());
  obj.resetMixedRegimeBuoyancyAssistingFlowonWallsEquationSource();
  EXPECT_TRUE(obj.isMixedRegimeBuoyancyAssistingFlowonWallsEquationSourceDefaulted());

  // Test invalid choice is rejected
  EXPECT_FALSE(obj.setSimpleBuoyancyVerticalWallEquationSource("InvalidChoice"));

  // Test Values helper returns non-empty
  auto values = SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::simpleBuoyancyVerticalWallEquationSourceValues();
  EXPECT_FALSE(values.empty());
}
