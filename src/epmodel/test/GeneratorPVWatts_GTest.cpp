/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Generator/GeneratorPVWatts.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GeneratorPVWatts_DefaultConstructor) {
  Model model;
  GeneratorPVWatts generator(model);
  EXPECT_EQ(GeneratorPVWatts::iddObjectType(), generator.iddObject().type());
}

TEST_F(EPModelFixture, GeneratorPVWatts_ScalarAccessors_RoundTrip) {
  Model model;
  GeneratorPVWatts generator(model);

  const auto pvWattsVersions = GeneratorPVWatts::pvWattsVersionValues();
  EXPECT_FALSE(pvWattsVersions.empty());

  EXPECT_TRUE(generator.setDCSystemCapacity(5000.0));
  EXPECT_DOUBLE_EQ(5000.0, generator.dcSystemCapacity());

  const auto moduleTypes = GeneratorPVWatts::moduleTypeValues();
  EXPECT_FALSE(moduleTypes.empty());
  EXPECT_TRUE(generator.setModuleType("Premium"));
  EXPECT_EQ("Premium", generator.moduleType());
  EXPECT_FALSE(generator.isModuleTypeDefaulted());
  generator.resetModuleType();
  EXPECT_TRUE(generator.isModuleTypeDefaulted());

  const auto arrayTypes = GeneratorPVWatts::arrayTypeValues();
  EXPECT_FALSE(arrayTypes.empty());
  EXPECT_TRUE(generator.setArrayType("TwoAxis"));
  EXPECT_EQ("TwoAxis", generator.arrayType());
  EXPECT_FALSE(generator.isArrayTypeDefaulted());
  generator.resetArrayType();
  EXPECT_TRUE(generator.isArrayTypeDefaulted());

  EXPECT_TRUE(generator.isSystemLossesDefaulted());
  EXPECT_DOUBLE_EQ(0.14, generator.systemLosses());
  EXPECT_TRUE(generator.setSystemLosses(0.2));
  EXPECT_DOUBLE_EQ(0.2, generator.systemLosses());
  EXPECT_FALSE(generator.isSystemLossesDefaulted());
  generator.resetSystemLosses();
  EXPECT_TRUE(generator.isSystemLossesDefaulted());
  EXPECT_DOUBLE_EQ(0.14, generator.systemLosses());

  EXPECT_TRUE(generator.isTiltAngleDefaulted());
  EXPECT_DOUBLE_EQ(20.0, generator.tiltAngle());
  EXPECT_TRUE(generator.setTiltAngle(30.0));
  EXPECT_DOUBLE_EQ(30.0, generator.tiltAngle());
  EXPECT_FALSE(generator.isTiltAngleDefaulted());
  generator.resetTiltAngle();
  EXPECT_TRUE(generator.isTiltAngleDefaulted());
  EXPECT_DOUBLE_EQ(20.0, generator.tiltAngle());

  EXPECT_TRUE(generator.isAzimuthAngleDefaulted());
  EXPECT_DOUBLE_EQ(180.0, generator.azimuthAngle());
  EXPECT_TRUE(generator.setAzimuthAngle(135.0));
  EXPECT_DOUBLE_EQ(135.0, generator.azimuthAngle());
  EXPECT_FALSE(generator.isAzimuthAngleDefaulted());
  generator.resetAzimuthAngle();
  EXPECT_TRUE(generator.isAzimuthAngleDefaulted());
  EXPECT_DOUBLE_EQ(180.0, generator.azimuthAngle());

  EXPECT_TRUE(generator.isGroundCoverageRatioDefaulted());
  EXPECT_DOUBLE_EQ(0.4, generator.groundCoverageRatio());
  EXPECT_TRUE(generator.setGroundCoverageRatio(0.5));
  EXPECT_DOUBLE_EQ(0.5, generator.groundCoverageRatio());
  EXPECT_FALSE(generator.isGroundCoverageRatioDefaulted());
  generator.resetGroundCoverageRatio();
  EXPECT_TRUE(generator.isGroundCoverageRatioDefaulted());
  EXPECT_DOUBLE_EQ(0.4, generator.groundCoverageRatio());
}
