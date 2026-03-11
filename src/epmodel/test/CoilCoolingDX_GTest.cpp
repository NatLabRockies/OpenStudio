/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/CoilCoolingDX.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingDX_DefaultConstructor) {
  Model model;
  CoilCoolingDX coil(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Coil_Cooling_DX), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
}

TEST_F(EPModelFixture, CoilCoolingDX_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingDX coil(model);

  EXPECT_TRUE(coil.setCondenserInletNodeName("DX Condenser Inlet"));
  EXPECT_TRUE(coil.setCondenserOutletNodeName("DX Condenser Outlet"));
  EXPECT_EQ("DX Condenser Inlet", coil.condenserInletNodeName());
  EXPECT_EQ("DX Condenser Outlet", coil.condenserOutletNodeName());
}
