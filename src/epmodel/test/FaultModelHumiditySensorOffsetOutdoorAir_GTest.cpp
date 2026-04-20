/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/FaultModelHumiditySensorOffsetOutdoorAir.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FaultModelHumiditySensorOffsetOutdoorAir_DefaultConstructor) {
  Model model;
  FaultModelHumiditySensorOffsetOutdoorAir fault(model);
  EXPECT_EQ(FaultModelHumiditySensorOffsetOutdoorAir::iddObjectType(), fault.iddObject().type());

  EXPECT_TRUE(fault.isHumiditySensorOffsetDefaulted());
  EXPECT_DOUBLE_EQ(0.0, fault.humiditySensorOffset());
}

TEST_F(EPModelFixture, FaultModelHumiditySensorOffsetOutdoorAir_ScalarAccessors_RoundTrip) {
  Model model;
  FaultModelHumiditySensorOffsetOutdoorAir fault(model);

  EXPECT_TRUE(fault.setHumiditySensorOffset(0.01));
  EXPECT_DOUBLE_EQ(0.01, fault.humiditySensorOffset());
  EXPECT_FALSE(fault.isHumiditySensorOffsetDefaulted());

  EXPECT_FALSE(fault.setHumiditySensorOffset(0.02));
  EXPECT_DOUBLE_EQ(0.01, fault.humiditySensorOffset());

  fault.resetHumiditySensorOffset();
  EXPECT_TRUE(fault.isHumiditySensorOffsetDefaulted());
  EXPECT_DOUBLE_EQ(0.0, fault.humiditySensorOffset());
}
