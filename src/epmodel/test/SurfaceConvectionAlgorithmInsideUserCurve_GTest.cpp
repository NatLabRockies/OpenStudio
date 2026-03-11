/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SurfaceConvectionAlgorithmInsideUserCurve.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfaceConvectionAlgorithmInsideUserCurve_DefaultConstructor) {
  Model model;
  SurfaceConvectionAlgorithmInsideUserCurve userCurve(model);
  EXPECT_EQ(SurfaceConvectionAlgorithmInsideUserCurve::iddObjectType(), userCurve.iddObject().type());
}

TEST_F(EPModelFixture, SurfaceConvectionAlgorithmInsideUserCurve_ScalarAccessors_RoundTrip) {
  Model model;
  SurfaceConvectionAlgorithmInsideUserCurve userCurve(model);

  // referenceTemperatureforConvectionHeatTransfer is an optional choice field (no default, not required)
  // Verify initially empty
  EXPECT_FALSE(userCurve.referenceTemperatureforConvectionHeatTransfer());

  // Set and roundtrip each valid key
  EXPECT_TRUE(userCurve.setReferenceTemperatureforConvectionHeatTransfer("MeanAirTemperature"));
  ASSERT_TRUE(userCurve.referenceTemperatureforConvectionHeatTransfer());
  EXPECT_EQ("MeanAirTemperature", userCurve.referenceTemperatureforConvectionHeatTransfer().get());

  EXPECT_TRUE(userCurve.setReferenceTemperatureforConvectionHeatTransfer("AdjacentAirTemperature"));
  ASSERT_TRUE(userCurve.referenceTemperatureforConvectionHeatTransfer());
  EXPECT_EQ("AdjacentAirTemperature", userCurve.referenceTemperatureforConvectionHeatTransfer().get());

  EXPECT_TRUE(userCurve.setReferenceTemperatureforConvectionHeatTransfer("SupplyAirTemperature"));
  ASSERT_TRUE(userCurve.referenceTemperatureforConvectionHeatTransfer());
  EXPECT_EQ("SupplyAirTemperature", userCurve.referenceTemperatureforConvectionHeatTransfer().get());

  // Invalid key should fail
  EXPECT_FALSE(userCurve.setReferenceTemperatureforConvectionHeatTransfer("InvalidKey"));
  // Value should remain unchanged after failed set
  ASSERT_TRUE(userCurve.referenceTemperatureforConvectionHeatTransfer());
  EXPECT_EQ("SupplyAirTemperature", userCurve.referenceTemperatureforConvectionHeatTransfer().get());

  // Reset
  userCurve.resetReferenceTemperatureforConvectionHeatTransfer();
  // After reset the field is cleared
  EXPECT_TRUE(userCurve.referenceTemperatureforConvectionHeatTransfer());
  EXPECT_TRUE(userCurve.referenceTemperatureforConvectionHeatTransfer()->empty());

  // Values helper
  auto values = SurfaceConvectionAlgorithmInsideUserCurve::referenceTemperatureforConvectionHeatTransferValues();
  EXPECT_EQ(3u, values.size());

  // Name roundtrip (base ModelObject)
  EXPECT_TRUE(userCurve.setName("TestUserCurve"));
  EXPECT_EQ("TestUserCurve", userCurve.nameString());
}
