/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/PipeUnderground.hpp"
#include <utilities/idd/Pipe_Underground_FieldEnums.hxx>
#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PipeUnderground_DefaultConstructor) {
  Model model;
  PipeUnderground pipe(model);
  EXPECT_EQ(PipeUnderground::iddObjectType(), pipe.iddObject().type());
  EXPECT_FALSE(pipe.nameString().empty());

  EXPECT_EQ("NoSun", pipe.sunExposure());
  EXPECT_FALSE(pipe.pipeInsideDiameter().has_value());
  EXPECT_FALSE(pipe.pipeLength().has_value());
  EXPECT_TRUE(pipe.isPipeInsideDiameterDefaulted());
  EXPECT_TRUE(pipe.isPipeLengthDefaulted());
  EXPECT_EQ("Soil Material", pipe.soilMaterialName());
  EXPECT_EQ("Site:GroundTemperature:Undisturbed:FiniteDifference", pipe.undisturbedGroundTemperatureModelType());
}

TEST_F(EPModelFixture, PipeUnderground_ScalarAccessors_RoundTrip) {
  Model model;
  PipeUnderground pipe(model);

  const auto sunExposureValues = PipeUnderground::sunExposureValues();
  EXPECT_TRUE(std::find(sunExposureValues.begin(), sunExposureValues.end(), "SunExposed") != sunExposureValues.end());
  EXPECT_TRUE(std::find(sunExposureValues.begin(), sunExposureValues.end(), "NoSun") != sunExposureValues.end());

  const auto groundTempModelTypeValues = PipeUnderground::undisturbedGroundTemperatureModelTypeValues();
  EXPECT_TRUE(std::find(groundTempModelTypeValues.begin(), groundTempModelTypeValues.end(),
                        "Site:GroundTemperature:Undisturbed:FiniteDifference")
              != groundTempModelTypeValues.end());
  EXPECT_TRUE(std::find(groundTempModelTypeValues.begin(), groundTempModelTypeValues.end(),
                        "Site:GroundTemperature:Undisturbed:KusudaAchenbach")
              != groundTempModelTypeValues.end());
  EXPECT_TRUE(std::find(groundTempModelTypeValues.begin(), groundTempModelTypeValues.end(), "Site:GroundTemperature:Undisturbed:Xing")
              != groundTempModelTypeValues.end());

  EXPECT_TRUE(pipe.setSunExposure("SunExposed"));
  EXPECT_EQ("SunExposed", pipe.sunExposure());
  EXPECT_FALSE(pipe.setSunExposure("InvalidChoice"));

  EXPECT_TRUE(pipe.setPipeInsideDiameter(0.1));
  ASSERT_TRUE(pipe.pipeInsideDiameter().has_value());
  EXPECT_DOUBLE_EQ(0.1, *pipe.pipeInsideDiameter());
  EXPECT_FALSE(pipe.isPipeInsideDiameterDefaulted());
  pipe.resetPipeInsideDiameter();
  EXPECT_FALSE(pipe.pipeInsideDiameter().has_value());
  EXPECT_TRUE(pipe.isPipeInsideDiameterDefaulted());

  EXPECT_TRUE(pipe.setPipeLength(25.0));
  ASSERT_TRUE(pipe.pipeLength().has_value());
  EXPECT_DOUBLE_EQ(25.0, *pipe.pipeLength());
  EXPECT_FALSE(pipe.isPipeLengthDefaulted());
  pipe.resetPipeLength();
  EXPECT_FALSE(pipe.pipeLength().has_value());
  EXPECT_TRUE(pipe.isPipeLengthDefaulted());

  EXPECT_TRUE(pipe.setSoilMaterialName("LocalSoilMaterial"));
  EXPECT_EQ("LocalSoilMaterial", pipe.soilMaterialName());

  EXPECT_TRUE(pipe.setUndisturbedGroundTemperatureModelType("Site:GroundTemperature:Undisturbed:KusudaAchenbach"));
  EXPECT_EQ("Site:GroundTemperature:Undisturbed:KusudaAchenbach", pipe.undisturbedGroundTemperatureModelType());
  EXPECT_FALSE(pipe.setUndisturbedGroundTemperatureModelType("InvalidType"));
}
