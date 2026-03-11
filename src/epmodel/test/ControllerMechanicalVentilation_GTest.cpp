/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ControllerMechanicalVentilation.hpp"

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ControllerMechanicalVentilation_DefaultConstructor) {
  Model model;
  ControllerMechanicalVentilation cmv(model);
  EXPECT_EQ(ControllerMechanicalVentilation::iddObjectType(), cmv.iddObject().type());
}

TEST_F(EPModelFixture, ControllerMechanicalVentilation_ScalarAccessors_RoundTrip) {
  Model model;
  ControllerMechanicalVentilation cmv(model);

  auto outdoorAirMethodValues = ControllerMechanicalVentilation::systemOutdoorAirMethodValues();
  ASSERT_FALSE(outdoorAirMethodValues.empty());
  EXPECT_NE(std::find(outdoorAirMethodValues.cbegin(), outdoorAirMethodValues.cend(), "Standard62.1VentilationRateProcedure"),
            outdoorAirMethodValues.cend());

  EXPECT_TRUE(cmv.setDemandControlledVentilation(true));
  EXPECT_TRUE(cmv.demandControlledVentilation());
  cmv.setDemandControlledVentilationNoFail(false);
  EXPECT_FALSE(cmv.demandControlledVentilation());

  EXPECT_TRUE(cmv.setSystemOutdoorAirMethod("ZoneSum"));
  EXPECT_EQ("ZoneSum", cmv.systemOutdoorAirMethod());

  cmv.resetDemandControlledVentilation();
  EXPECT_TRUE(cmv.isDemandControlledVentilationDefaulted());
  EXPECT_FALSE(cmv.demandControlledVentilation());

  cmv.resetSystemOutdoorAirMethod();
  EXPECT_TRUE(cmv.isSystemOutdoorAirMethodDefaulted());
  EXPECT_EQ("Standard62.1VentilationRateProcedure", cmv.systemOutdoorAirMethod());
}
