/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/RefrigerationSubcoolerMechanical.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RefrigerationSubcoolerMechanical_DefaultConstructor) {
  Model model;
  RefrigerationSubcoolerMechanical subcooler(model);

  EXPECT_EQ(RefrigerationSubcoolerMechanical::iddObjectType(), subcooler.iddObject().type());
  EXPECT_EQ("Mechanical", subcooler.subcoolerType());
  ASSERT_TRUE(subcooler.outletControlTemperature());
  EXPECT_DOUBLE_EQ(10.0, *subcooler.outletControlTemperature());
}

TEST_F(EPModelFixture, RefrigerationSubcoolerMechanical_ScalarAccessors_RoundTrip) {
  Model model;
  RefrigerationSubcoolerMechanical subcooler(model);

  EXPECT_TRUE(subcooler.setOutletControlTemperature(7.4));
  ASSERT_TRUE(subcooler.outletControlTemperature());
  EXPECT_DOUBLE_EQ(7.4, *subcooler.outletControlTemperature());

  subcooler.resetOutletControlTemperature();
  EXPECT_FALSE(subcooler.outletControlTemperature());
}
