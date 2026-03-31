/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToAirComponent/CoilUserDefined.hpp"

#include <utilities/idd/Coil_UserDefined_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilUserDefined_DefaultConstructor) {
  Model model;
  CoilUserDefined coil(model);
  EXPECT_EQ(CoilUserDefined::iddObjectType(), coil.iddObject().type());
  EXPECT_EQ(openstudio::Coil_UserDefinedFields::AirConnection1InletNodeName, coil.airInletPort());
  EXPECT_EQ(openstudio::Coil_UserDefinedFields::AirConnection1OutletNodeName, coil.airOutletPort());
  EXPECT_EQ(openstudio::Coil_UserDefinedFields::PlantConnectionInletNodeName, coil.waterInletPort());
  EXPECT_EQ(openstudio::Coil_UserDefinedFields::PlantConnectionOutletNodeName, coil.waterOutletPort());
  EXPECT_FALSE(coil.airInletModelObject());
  EXPECT_FALSE(coil.airOutletModelObject());
  EXPECT_FALSE(coil.waterInletModelObject());
  EXPECT_FALSE(coil.waterOutletModelObject());
}

TEST_F(EPModelFixture, CoilUserDefined_ScalarAccessors_RoundTrip) {
  Model model;
  CoilUserDefined coil(model);

  ASSERT_TRUE(coil.setInt(openstudio::Coil_UserDefinedFields::NumberofAirConnections, 1));
  EXPECT_EQ(1, coil.numberofAirConnections());

  ASSERT_TRUE(coil.setInt(openstudio::Coil_UserDefinedFields::NumberofAirConnections, 2));
  EXPECT_EQ(2, coil.numberofAirConnections());
}

TEST_F(EPModelFixture, CoilUserDefined_AddToNodeSupportsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  CoilUserDefined coil(model);

  EXPECT_TRUE(coil.addToNode(*outboardOANode));

  const auto oaComponents = oaSystem.oaComponents();
  ASSERT_EQ(3u, oaComponents.size());
  EXPECT_EQ(coil.handle(), oaComponents[1].handle());
}
