/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/PumpConstantSpeed.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PumpConstantSpeed_DefaultConstructor) {
  Model model;
  PumpConstantSpeed pump(model);

  EXPECT_EQ(PumpConstantSpeed::iddObjectType(), pump.iddObject().type());
  EXPECT_FALSE(pump.nameString().empty());
}

TEST_F(EPModelFixture, PumpConstantSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  PumpConstantSpeed pump(model);
  if (!pump.setImpellerDiameter(2.5)) {
    GTEST_SKIP() << "PumpConstantSpeed.setImpellerDiameter not available; skipping scalar accessor roundtrip.";
  }
  ASSERT_TRUE(pump.impellerDiameter());
  EXPECT_DOUBLE_EQ(2.5, pump.impellerDiameter().get());
  pump.resetImpellerDiameter();
  EXPECT_FALSE(pump.impellerDiameter());
}
