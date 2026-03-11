/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/SolarCollectorFlatPlatePhotovoltaicThermal.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SolarCollectorFlatPlatePhotovoltaicThermal_DefaultConstructor) {
  Model model;
  SolarCollectorFlatPlatePhotovoltaicThermal object(model);
  EXPECT_EQ(SolarCollectorFlatPlatePhotovoltaicThermal::iddObjectType(), object.iddObject().type());
  EXPECT_FALSE(object.nameString().empty());
}

TEST_F(EPModelFixture, SolarCollectorFlatPlatePhotovoltaicThermal_ScalarAccessors_RoundTrip) {
  Model model;
  SolarCollectorFlatPlatePhotovoltaicThermal object(model);

  EXPECT_FALSE(object.designFlowRate());
  EXPECT_FALSE(object.isDesignFlowRateAutosized());

  EXPECT_TRUE(object.setDesignFlowRate(0.0123));
  ASSERT_TRUE(object.designFlowRate());
  EXPECT_DOUBLE_EQ(0.0123, object.designFlowRate().get());
  EXPECT_FALSE(object.isDesignFlowRateAutosized());

  object.autosizeDesignFlowRate();
  EXPECT_TRUE(object.isDesignFlowRateAutosized());

  object.resetDesignFlowRate();
  EXPECT_FALSE(object.designFlowRate());
}
