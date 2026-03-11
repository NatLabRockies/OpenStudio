/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AirTerminalSingleDuctConstantVolumeNoReheat.hpp"
#include "../Node.hpp"
#include "../ZoneHVACAirDistributionUnit.hpp"
#include "../ZoneHVACAirDistributionUnit_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_ZoneHVACAirDistributionUnit_DefaultConstructor) {
  Model model;
  ZoneHVACAirDistributionUnit adu(model);
  EXPECT_EQ(ZoneHVACAirDistributionUnit::iddObjectType(), adu.iddObject().type());
  EXPECT_FALSE(adu.nameString().empty());
}

TEST_F(EPModelFixture, API_ZoneHVACAirDistributionUnit_GetterResolution) {
  Model model;
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);
  auto outletNode = model.getOrCreateTransientByName<Node>("ADU Outlet Node");
  ZoneHVACAirDistributionUnit adu(model);

  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));
  ASSERT_TRUE(aduImpl->setOutletNode(outletNode));

  auto airTerminal = adu.airTerminal();
  ASSERT_TRUE(airTerminal);
  EXPECT_EQ(terminal.cast<ModelObject>(), airTerminal.get());

  auto resolvedOutletNode = adu.outletNode();
  ASSERT_TRUE(resolvedOutletNode);
  EXPECT_EQ(outletNode, resolvedOutletNode.get());
}
