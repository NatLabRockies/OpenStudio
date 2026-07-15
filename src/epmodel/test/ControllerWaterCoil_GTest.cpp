/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ControllerWaterCoil.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToAirComponent/CoilCoolingWater.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ControllerWaterCoil_DefaultConstructor) {
  Model model;
  ControllerWaterCoil controller(model);
  EXPECT_EQ(ControllerWaterCoil::iddObjectType(), controller.iddObject().type());
  EXPECT_FALSE(controller.nameString().empty());
}

TEST_F(EPModelFixture, ControllerWaterCoil_ScalarAccessors_RoundTrip) {
  Model model;
  ControllerWaterCoil controller(model);

  const auto controlVariableValues = ControllerWaterCoil::validControlVariableValues();
  EXPECT_FALSE(controlVariableValues.empty());
  EXPECT_TRUE(std::find(controlVariableValues.begin(), controlVariableValues.end(), "Temperature") != controlVariableValues.end());

  const auto actionValues = ControllerWaterCoil::validActionValues();
  EXPECT_FALSE(actionValues.empty());
  EXPECT_TRUE(std::find(actionValues.begin(), actionValues.end(), "Normal") != actionValues.end());

  const auto actuatorVariableValues = ControllerWaterCoil::validActuatorVariableValues();
  EXPECT_FALSE(actuatorVariableValues.empty());
  EXPECT_TRUE(std::find(actuatorVariableValues.begin(), actuatorVariableValues.end(), "Flow") != actuatorVariableValues.end());

  EXPECT_TRUE(controller.controlVariable());
  EXPECT_FALSE(controller.isControlVariableDefaulted()) << controller;
  EXPECT_TRUE(controller.setControlVariable("Temperature"));
  ASSERT_TRUE(controller.controlVariable());
  EXPECT_EQ("Temperature", controller.controlVariable().get());
  controller.resetControlVariable();
  EXPECT_TRUE(controller.isControlVariableDefaulted());

  EXPECT_TRUE(controller.setAction("Normal"));
  ASSERT_TRUE(controller.action());
  EXPECT_EQ("Normal", controller.action().get());
  controller.resetAction();

  EXPECT_TRUE(controller.actuatorVariable());
  EXPECT_FALSE(controller.isActuatorVariableDefaulted());
  EXPECT_TRUE(controller.setActuatorVariable("Flow"));
  ASSERT_TRUE(controller.actuatorVariable());
  EXPECT_EQ("Flow", controller.actuatorVariable().get());
  controller.resetActuatorVariable();
  EXPECT_TRUE(controller.isActuatorVariableDefaulted());

  EXPECT_TRUE(controller.setControllerConvergenceTolerance(0.007));
  ASSERT_TRUE(controller.controllerConvergenceTolerance());
  EXPECT_DOUBLE_EQ(0.007, controller.controllerConvergenceTolerance().get());
  EXPECT_FALSE(controller.isControllerConvergenceToleranceAutosized());
  controller.autosizeControllerConvergenceTolerance();
  EXPECT_TRUE(controller.isControllerConvergenceToleranceAutosized());
  controller.resetControllerConvergenceTolerance();
  EXPECT_TRUE(controller.isControllerConvergenceToleranceDefaulted());

  EXPECT_TRUE(controller.setMaximumActuatedFlow(0.24));
  ASSERT_TRUE(controller.maximumActuatedFlow());
  EXPECT_DOUBLE_EQ(0.24, controller.maximumActuatedFlow().get());
  EXPECT_FALSE(controller.isMaximumActuatedFlowAutosized());
  controller.autosizeMaximumActuatedFlow();
  EXPECT_TRUE(controller.isMaximumActuatedFlowAutosized());

  EXPECT_TRUE(controller.setMinimumActuatedFlow(0.02));
  EXPECT_DOUBLE_EQ(0.02, controller.minimumActuatedFlow());
  EXPECT_FALSE(controller.isMinimumActuatedFlowDefaulted());
  controller.resetMinimumActuatedFlow();
  EXPECT_TRUE(controller.isMinimumActuatedFlowDefaulted());
  EXPECT_DOUBLE_EQ(0.0, controller.minimumActuatedFlow());
}

TEST_F(EPModelFixture, ControllerWaterCoil_NodeAccessors_RoundTrip) {
  Model model;
  ControllerWaterCoil controller(model);

  Node actuator = model.getOrCreateTransientByName<Node>("Controller Water Coil Actuator Node");
  Node sensor = model.getOrCreateTransientByName<Node>("Controller Water Coil Sensor Node");

  EXPECT_FALSE(controller.actuatorNode());
  EXPECT_FALSE(controller.sensorNode());

  EXPECT_TRUE(controller.setActuatorNode(actuator));
  EXPECT_TRUE(controller.setSensorNode(sensor));

  ASSERT_TRUE(controller.sensorNode());
  EXPECT_EQ(sensor.handle(), controller.sensorNode()->handle());
  ASSERT_TRUE(controller.actuatorNode());
  EXPECT_EQ(actuator.handle(), controller.actuatorNode()->handle());
}

TEST_F(EPModelFixture, ControllerWaterCoil_WaterCoilIsInferredFromCoolingCoilNodes) {
  Model model;
  CoilCoolingWater coil(model);
  PlantLoop plantLoop(model);
  AirLoopHVAC airLoop(model);

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coil));
  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(coil.addToNode(supplyOutletNode));

  auto controller = coil.controllerWaterCoil();
  ASSERT_TRUE(controller);
  auto waterCoil = controller->waterCoil();
  ASSERT_TRUE(waterCoil);
  EXPECT_EQ(coil.handle(), waterCoil->handle());
}

TEST_F(EPModelFixture, ControllerWaterCoil_WaterCoilIsInferredFromHeatingCoilNodes) {
  Model model;
  CoilHeatingWater coil(model);
  PlantLoop plantLoop(model);
  AirLoopHVAC airLoop(model);

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coil));
  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(coil.addToNode(supplyOutletNode));

  auto controller = coil.controllerWaterCoil();
  ASSERT_TRUE(controller);
  auto waterCoil = controller->waterCoil();
  ASSERT_TRUE(waterCoil);
  EXPECT_EQ(coil.handle(), waterCoil->handle());
}
