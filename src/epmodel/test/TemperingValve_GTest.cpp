/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/TemperingValve.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, TemperingValve_DefaultConstructor) {
  Model model;
  TemperingValve valve(model);

  EXPECT_FALSE(valve.stream2SourceNode());
  EXPECT_FALSE(valve.temperatureSetpointNode());
  EXPECT_FALSE(valve.pumpOutletNode());
}

TEST_F(EPModelFixture, TemperingValve_ScalarAccessors_RoundTrip) {
  Model model;
  TemperingValve valve(model);
  Node pumpNode = model.getOrCreateTransientByName<Node>("Pump Outlet Node");

  EXPECT_TRUE(valve.setPumpOutletNode(pumpNode));
  ASSERT_TRUE(valve.pumpOutletNode());
  EXPECT_EQ(pumpNode, *valve.pumpOutletNode());

  valve.resetPumpOutletNode();

  Node stream2Node = model.getOrCreateTransientByName<Node>("Stream2 Source Node");
  EXPECT_TRUE(valve.setStream2SourceNode(stream2Node));
  ASSERT_TRUE(valve.stream2SourceNode());
  EXPECT_EQ(stream2Node, *valve.stream2SourceNode());

  valve.resetStream2SourceNode();

  Node temperatureSetpointNode = model.getOrCreateTransientByName<Node>("Temperature Setpoint Node");
  EXPECT_TRUE(valve.setTemperatureSetpointNode(temperatureSetpointNode));
  ASSERT_TRUE(valve.temperatureSetpointNode());
  EXPECT_EQ(temperatureSetpointNode, *valve.temperatureSetpointNode());

  valve.resetTemperatureSetpointNode();
}
