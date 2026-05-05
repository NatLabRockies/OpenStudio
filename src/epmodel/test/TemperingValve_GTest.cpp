/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Mixer/Mixer.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/PipeAdiabatic.hpp"
#include "../StraightComponent/HeaderedPumpsConstantSpeed.hpp"
#include "../StraightComponent/HeaderedPumpsVariableSpeed.hpp"
#include "../StraightComponent/PumpConstantSpeed.hpp"
#include "../StraightComponent/PumpVariableSpeed.hpp"
#include "../StraightComponent/TemperingValve.hpp"
#include "../StraightComponent/TemperingValve_Impl.hpp"

#include <utilities/idd/TemperingValve_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, TemperingValve_DefaultConstructor) {
  Model model;
  TemperingValve valve(model);

  EXPECT_FALSE(valve.stream2SourceNode());
  EXPECT_FALSE(valve.temperatureSetpointNode());
  EXPECT_FALSE(valve.pumpOutletNode());

  auto valveCloneObject = model.addObject(valve.idfObject());
  ASSERT_TRUE(valveCloneObject);
  auto valveClone = valveCloneObject->cast<TemperingValve>();
  EXPECT_FALSE(valveClone.stream2SourceNode());
  EXPECT_FALSE(valveClone.temperatureSetpointNode());
  EXPECT_FALSE(valveClone.pumpOutletNode());
}

TEST_F(EPModelFixture, TemperingValve_ScalarAccessors_RoundTrip) {
  Model model;
  TemperingValve valve(model);
  Node pumpNode = model.getOrCreateTransientByName<Node>("Pump Outlet Node");

  EXPECT_TRUE(valve.setPumpOutletNode(pumpNode));
  ASSERT_TRUE(valve.pumpOutletNode());
  EXPECT_EQ(pumpNode, *valve.pumpOutletNode());

  valve.resetPumpOutletNode();
  EXPECT_FALSE(valve.pumpOutletNode());

  Node stream2Node = model.getOrCreateTransientByName<Node>("Stream2 Source Node");
  EXPECT_TRUE(valve.setStream2SourceNode(stream2Node));
  ASSERT_TRUE(valve.stream2SourceNode());
  EXPECT_EQ(stream2Node, *valve.stream2SourceNode());

  valve.resetStream2SourceNode();
  EXPECT_FALSE(valve.stream2SourceNode());

  Node temperatureSetpointNode = model.getOrCreateTransientByName<Node>("Temperature Setpoint Node");
  EXPECT_TRUE(valve.setTemperatureSetpointNode(temperatureSetpointNode));
  ASSERT_TRUE(valve.temperatureSetpointNode());
  EXPECT_EQ(temperatureSetpointNode, *valve.temperatureSetpointNode());

  valve.resetTemperatureSetpointNode();
  EXPECT_FALSE(valve.temperatureSetpointNode());
}

TEST_F(EPModelFixture, TemperingValve_AddToNode_PlantSupplyOnlyAndControlNodes) {
  Model model;
  TemperingValve rejectedValve(model);

  AirLoopHVAC airLoop(model);
  auto airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(rejectedValve.addToNode(airSupplyOutletNode));
  EXPECT_FALSE(rejectedValve.airLoopHVAC());

  PlantLoop plantLoop(model);
  auto demandOutletNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(rejectedValve.addToNode(demandOutletNode));
  EXPECT_FALSE(rejectedValve.plantLoop());

  PumpConstantSpeed pump(model);
  auto supplyInletNode = plantLoop.supplyInletNode();
  ASSERT_TRUE(pump.addToNode(supplyInletNode));

  PipeAdiabatic bypassA(model);
  PipeAdiabatic bypassB(model);
  PipeAdiabatic bypassC(model);
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(bypassA));
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(bypassB));
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(bypassC));

  auto mixerInlets = plantLoop.supplyMixer().inletModelObjects();
  ASSERT_EQ(3u, mixerInlets.size());
  auto valveBranchNode = mixerInlets.front().cast<Node>();
  auto terminalAlternateBranchNode = mixerInlets.back().cast<Node>();

  TemperingValve valve(model);
  EXPECT_TRUE(valve.addToNode(valveBranchNode));

  ASSERT_TRUE(valve.plantLoop());
  EXPECT_EQ(plantLoop.handle(), valve.plantLoop()->handle());
  EXPECT_EQ(1u, plantLoop.supplyComponents(TemperingValve::iddObjectType()).size());
  ASSERT_TRUE(valve.inletModelObject());
  ASSERT_TRUE(valve.outletModelObject());

  auto inletNode = valve.getModelObjectTarget<Node>(openstudio::TemperingValveFields::InletNodeName);
  auto outletNode = valve.getModelObjectTarget<Node>(openstudio::TemperingValveFields::OutletNodeName);
  ASSERT_TRUE(inletNode);
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(valve.inletModelObject()->handle(), inletNode->handle());
  EXPECT_EQ(valve.outletModelObject()->handle(), outletNode->handle());

  ASSERT_TRUE(valve.temperatureSetpointNode());
  EXPECT_EQ(plantLoop.supplyOutletNode().handle(), valve.temperatureSetpointNode()->handle());

  ASSERT_TRUE(valve.pumpOutletNode());
  ASSERT_TRUE(pump.outletModelObject());
  EXPECT_EQ(pump.outletModelObject()->cast<Node>().handle(), valve.pumpOutletNode()->handle());

  ASSERT_TRUE(valve.stream2SourceNode());
  EXPECT_EQ(terminalAlternateBranchNode.handle(), valve.stream2SourceNode()->handle());
  EXPECT_NE(valve.stream2SourceNode()->handle(), valve.outletModelObject()->handle());
}

TEST_F(EPModelFixture, TemperingValve_RelocateCloneAndDisconnect) {
  Model model;
  PlantLoop plantLoop(model);
  PumpConstantSpeed pump(model);
  auto firstSupplyInletNode = plantLoop.supplyInletNode();
  ASSERT_TRUE(pump.addToNode(firstSupplyInletNode));

  PipeAdiabatic firstBypass(model);
  PipeAdiabatic secondBypass(model);
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(firstBypass));
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(secondBypass));
  auto firstLoopBranchNode = plantLoop.supplyMixer().inletModelObjects().front().cast<Node>();

  TemperingValve valve(model);
  ASSERT_TRUE(valve.addToNode(firstLoopBranchNode));
  ASSERT_TRUE(valve.plantLoop());
  EXPECT_EQ(1u, plantLoop.supplyComponents(TemperingValve::iddObjectType()).size());

  PlantLoop plantLoop2(model);
  PumpConstantSpeed pump2(model);
  auto secondSupplyInletNode = plantLoop2.supplyInletNode();
  ASSERT_TRUE(pump2.addToNode(secondSupplyInletNode));
  PipeAdiabatic thirdBypass(model);
  PipeAdiabatic fourthBypass(model);
  ASSERT_TRUE(plantLoop2.addSupplyBranchForComponent(thirdBypass));
  ASSERT_TRUE(plantLoop2.addSupplyBranchForComponent(fourthBypass));
  auto secondLoopBranchNode = plantLoop2.supplyMixer().inletModelObjects().front().cast<Node>();

  auto originalStream2 = valve.stream2SourceNode();
  auto originalSetpoint = valve.temperatureSetpointNode();
  auto originalPumpOutlet = valve.pumpOutletNode();
  ASSERT_TRUE(originalStream2);
  ASSERT_TRUE(originalSetpoint);
  ASSERT_TRUE(originalPumpOutlet);

  ASSERT_TRUE(valve.addToNode(secondLoopBranchNode));
  ASSERT_TRUE(valve.plantLoop());
  EXPECT_EQ(plantLoop2.handle(), valve.plantLoop()->handle());
  EXPECT_EQ(0u, plantLoop.supplyComponents(TemperingValve::iddObjectType()).size());
  EXPECT_EQ(1u, plantLoop2.supplyComponents(TemperingValve::iddObjectType()).size());
  EXPECT_EQ(originalStream2->handle(), valve.stream2SourceNode()->handle());
  EXPECT_EQ(originalSetpoint->handle(), valve.temperatureSetpointNode()->handle());
  EXPECT_EQ(originalPumpOutlet->handle(), valve.pumpOutletNode()->handle());

  auto valveCloneObject = model.addObject(valve.idfObject());
  ASSERT_TRUE(valveCloneObject);
  auto valveClone = valveCloneObject->cast<TemperingValve>();
  ASSERT_TRUE(valveClone.stream2SourceNode());
  ASSERT_TRUE(valveClone.temperatureSetpointNode());
  ASSERT_TRUE(valveClone.pumpOutletNode());
  EXPECT_EQ(valve.stream2SourceNode()->handle(), valveClone.stream2SourceNode()->handle());
  EXPECT_EQ(valve.temperatureSetpointNode()->handle(), valveClone.temperatureSetpointNode()->handle());
  EXPECT_EQ(valve.pumpOutletNode()->handle(), valveClone.pumpOutletNode()->handle());

  auto cloneLoopBranchNode = plantLoop.supplyMixer().inletModelObjects().front().cast<Node>();
  ASSERT_TRUE(valveClone.addToNode(cloneLoopBranchNode));
  ASSERT_TRUE(valveClone.plantLoop());
  EXPECT_EQ(plantLoop.handle(), valveClone.plantLoop()->handle());
  EXPECT_EQ(1u, plantLoop.supplyComponents(TemperingValve::iddObjectType()).size());

  valve.disconnect();
  EXPECT_FALSE(valve.loop());
  EXPECT_FALSE(valve.inletModelObject());
  EXPECT_FALSE(valve.outletModelObject());
  EXPECT_EQ(0u, plantLoop2.supplyComponents(TemperingValve::iddObjectType()).size());
  ASSERT_TRUE(valve.stream2SourceNode());
  ASSERT_TRUE(valve.temperatureSetpointNode());
  ASSERT_TRUE(valve.pumpOutletNode());

  valveClone.disconnect();
  EXPECT_FALSE(valveClone.loop());
  EXPECT_FALSE(valveClone.inletModelObject());
  EXPECT_FALSE(valveClone.outletModelObject());
  EXPECT_EQ(0u, plantLoop.supplyComponents(TemperingValve::iddObjectType()).size());
  ASSERT_TRUE(valveClone.stream2SourceNode());
  ASSERT_TRUE(valveClone.temperatureSetpointNode());
  ASSERT_TRUE(valveClone.pumpOutletNode());
}

TEST_F(EPModelFixture, TemperingValve_SetControlNodes_PreservesPresetNodesAndUsesCanonicalPumpPrecedence) {
  Model model;

  PlantLoop plantLoop(model);
  PumpVariableSpeed variablePump(model);
  auto supplyInletNode = plantLoop.supplyInletNode();
  ASSERT_TRUE(variablePump.addToNode(supplyInletNode));
  ASSERT_TRUE(variablePump.outletModelObject());

  PumpConstantSpeed constantPump(model);
  auto variablePumpOutletNode = variablePump.outletModelObject()->cast<Node>();
  ASSERT_TRUE(constantPump.addToNode(variablePumpOutletNode));
  ASSERT_TRUE(constantPump.outletModelObject());

  PipeAdiabatic bypassA(model);
  PipeAdiabatic bypassB(model);
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(bypassA));
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(bypassB));

  auto valveBranchNode = plantLoop.supplyMixer().inletModelObjects().front().cast<Node>();

  TemperingValve valve(model);
  Node presetStream2 = model.getOrCreateTransientByName<Node>("Preset Stream 2 Source Node");
  Node presetSetpoint = model.getOrCreateTransientByName<Node>("Preset Temperature Setpoint Node");
  ASSERT_TRUE(valve.setStream2SourceNode(presetStream2));
  ASSERT_TRUE(valve.setTemperatureSetpointNode(presetSetpoint));

  ASSERT_TRUE(valve.addToNode(valveBranchNode));
  ASSERT_TRUE(valve.pumpOutletNode());
  EXPECT_EQ(presetStream2.handle(), valve.stream2SourceNode()->handle());
  EXPECT_EQ(presetSetpoint.handle(), valve.temperatureSetpointNode()->handle());
  EXPECT_EQ(constantPump.outletModelObject()->cast<Node>().handle(), valve.pumpOutletNode()->handle());

  valve.resetPumpOutletNode();
  EXPECT_FALSE(valve.pumpOutletNode());

  auto impl = valve.getImpl<openstudio::epmodel::detail::TemperingValve_Impl>();
  ASSERT_TRUE(impl->setControlNodes());
  ASSERT_TRUE(valve.pumpOutletNode());
  EXPECT_EQ(presetStream2.handle(), valve.stream2SourceNode()->handle());
  EXPECT_EQ(presetSetpoint.handle(), valve.temperatureSetpointNode()->handle());
  EXPECT_EQ(constantPump.outletModelObject()->cast<Node>().handle(), valve.pumpOutletNode()->handle());

  Node presetPumpOutlet = model.getOrCreateTransientByName<Node>("Preset Pump Outlet Node");
  ASSERT_TRUE(valve.setPumpOutletNode(presetPumpOutlet));
  valve.resetStream2SourceNode();
  valve.resetTemperatureSetpointNode();

  ASSERT_TRUE(impl->setControlNodes());
  ASSERT_TRUE(valve.stream2SourceNode());
  ASSERT_TRUE(valve.temperatureSetpointNode());
  ASSERT_TRUE(valve.pumpOutletNode());
  EXPECT_EQ(presetPumpOutlet.handle(), valve.pumpOutletNode()->handle());
  EXPECT_EQ(plantLoop.supplyOutletNode().handle(), valve.temperatureSetpointNode()->handle());
}

TEST_F(EPModelFixture, TemperingValve_SetControlNodes_UsesHeaderedPumpOutlets) {
  Model model;

  PlantLoop constantLoop(model);
  HeaderedPumpsConstantSpeed headeredConstantPump(model);
  auto constantSupplyInletNode = constantLoop.supplyInletNode();
  ASSERT_TRUE(headeredConstantPump.addToNode(constantSupplyInletNode));
  ASSERT_TRUE(headeredConstantPump.outletModelObject());

  PipeAdiabatic constantBypassA(model);
  PipeAdiabatic constantBypassB(model);
  ASSERT_TRUE(constantLoop.addSupplyBranchForComponent(constantBypassA));
  ASSERT_TRUE(constantLoop.addSupplyBranchForComponent(constantBypassB));

  auto constantValveBranchNode = constantLoop.supplyMixer().inletModelObjects().front().cast<Node>();

  TemperingValve constantValve(model);
  ASSERT_TRUE(constantValve.addToNode(constantValveBranchNode));
  ASSERT_TRUE(constantValve.pumpOutletNode());
  EXPECT_EQ(headeredConstantPump.outletModelObject()->cast<Node>().handle(), constantValve.pumpOutletNode()->handle());

  PlantLoop variableLoop(model);
  HeaderedPumpsVariableSpeed headeredVariablePump(model);
  auto variableSupplyInletNode = variableLoop.supplyInletNode();
  ASSERT_TRUE(headeredVariablePump.addToNode(variableSupplyInletNode));
  ASSERT_TRUE(headeredVariablePump.outletModelObject());

  PipeAdiabatic variableBypassA(model);
  PipeAdiabatic variableBypassB(model);
  ASSERT_TRUE(variableLoop.addSupplyBranchForComponent(variableBypassA));
  ASSERT_TRUE(variableLoop.addSupplyBranchForComponent(variableBypassB));

  auto variableValveBranchNode = variableLoop.supplyMixer().inletModelObjects().front().cast<Node>();

  TemperingValve variableValve(model);
  ASSERT_TRUE(variableValve.addToNode(variableValveBranchNode));
  ASSERT_TRUE(variableValve.pumpOutletNode());
  EXPECT_EQ(headeredVariablePump.outletModelObject()->cast<Node>().handle(), variableValve.pumpOutletNode()->handle());
}
