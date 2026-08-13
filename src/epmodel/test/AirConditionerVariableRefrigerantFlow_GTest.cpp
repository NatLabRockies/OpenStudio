/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/AirConditionerVariableRefrigerantFlow.hpp"
#include "../StraightComponent/AirConditionerVariableRefrigerantFlow_Impl.hpp"
#include "../StraightComponent/CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl.hpp"
#include "../StraightComponent/CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ModelObject/ModelObject_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow.hpp"
#include "../ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl.hpp"

#include <utilities/idd/AirConditioner_VariableRefrigerantFlow_FieldEnums.hxx>
#include <utilities/idd/ZoneTerminalUnitList_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_DefaultConstructor) {
  Model model;
  AirConditionerVariableRefrigerantFlow vrf(model);
  EXPECT_EQ(AirConditionerVariableRefrigerantFlow::iddObjectType(), vrf.iddObject().type());
  EXPECT_FALSE(vrf.nameString().empty());
  EXPECT_TRUE(vrf.isCondenserTypeDefaulted());
  EXPECT_EQ("AirCooled", vrf.condenserType());
  EXPECT_TRUE(vrf.terminals().empty());
  const auto lists = model.getObjectsByType(openstudio::IddObjectType::ZoneTerminalUnitList);
  ASSERT_EQ(1u, lists.size());
  auto list = vrf.getModelObjectTarget<ModelObject>(openstudio::AirConditioner_VariableRefrigerantFlowFields::ZoneTerminalUnitListName);
  ASSERT_TRUE(list);
  EXPECT_EQ(lists.front().handle(), list->handle());
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_ScalarAccessors_RoundTrip) {
  Model model;
  AirConditionerVariableRefrigerantFlow vrf(model);

  EXPECT_TRUE(vrf.setGrossRatedTotalCoolingCapacity(12345.0));
  ASSERT_TRUE(vrf.grossRatedTotalCoolingCapacity());
  EXPECT_DOUBLE_EQ(12345.0, vrf.grossRatedTotalCoolingCapacity().get());
  EXPECT_FALSE(vrf.isGrossRatedTotalCoolingCapacityAutosized());

  vrf.autosizeGrossRatedTotalCoolingCapacity();
  EXPECT_TRUE(vrf.isGrossRatedTotalCoolingCapacityAutosized());

  EXPECT_TRUE(vrf.setGrossRatedCoolingCOP(3.4));
  EXPECT_DOUBLE_EQ(3.4, vrf.grossRatedCoolingCOP());

  EXPECT_TRUE(vrf.setGrossRatedHeatingCapacity(9876.0));
  ASSERT_TRUE(vrf.grossRatedHeatingCapacity());
  EXPECT_DOUBLE_EQ(9876.0, vrf.grossRatedHeatingCapacity().get());
  EXPECT_FALSE(vrf.isGrossRatedHeatingCapacityAutosized());

  vrf.autosizeGrossRatedHeatingCapacity();
  EXPECT_TRUE(vrf.isGrossRatedHeatingCapacityAutosized());

  EXPECT_TRUE(vrf.setRatedHeatingCapacitySizingRatio(1.15));
  EXPECT_DOUBLE_EQ(1.15, vrf.ratedHeatingCapacitySizingRatio());

  const auto heatingValues = AirConditionerVariableRefrigerantFlow::heatingPerformanceCurveOutdoorTemperatureTypeValues();
  ASSERT_FALSE(heatingValues.empty());
  EXPECT_TRUE(vrf.setHeatingPerformanceCurveOutdoorTemperatureType(heatingValues.front()));
  EXPECT_EQ(heatingValues.front(), vrf.heatingPerformanceCurveOutdoorTemperatureType());

  EXPECT_TRUE(vrf.setHeatPumpWasteHeatRecovery(true));
  EXPECT_TRUE(vrf.heatPumpWasteHeatRecovery());
  EXPECT_TRUE(vrf.setHeatPumpWasteHeatRecovery(false));
  EXPECT_FALSE(vrf.heatPumpWasteHeatRecovery());

  EXPECT_TRUE(vrf.setNumberofCompressors(3));
  EXPECT_EQ(3, vrf.numberofCompressors());

  const auto defrostValues = AirConditionerVariableRefrigerantFlow::defrostStrategyValues();
  ASSERT_FALSE(defrostValues.empty());
  EXPECT_TRUE(vrf.setDefrostStrategy(defrostValues.front()));
  EXPECT_EQ(defrostValues.front(), vrf.defrostStrategy());

  const auto condenserValues = AirConditionerVariableRefrigerantFlow::condenserTypeValues();
  ASSERT_FALSE(condenserValues.empty());
  EXPECT_TRUE(vrf.setCondenserType(condenserValues.front()));
  EXPECT_FALSE(vrf.isCondenserTypeDefaulted());
  EXPECT_EQ(condenserValues.front(), vrf.condenserType());
  vrf.resetCondenserType();
  EXPECT_TRUE(vrf.isCondenserTypeDefaulted());
  EXPECT_EQ("AirCooled", vrf.condenserType());
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_AddToNode_DemandSideDefaultedCondenserType) {
  Model model;
  PlantLoop plantLoop(model);
  AirConditionerVariableRefrigerantFlow vrf(model);

  Node supplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_FALSE(vrf.addToNode(supplyOutletNode));
  EXPECT_FALSE(vrf.plantLoop());
  EXPECT_TRUE(vrf.isCondenserTypeDefaulted());
  EXPECT_EQ("AirCooled", vrf.condenserType());

  Node demandOutletNode = plantLoop.demandOutletNode();
  EXPECT_TRUE(vrf.addToNode(demandOutletNode));
  EXPECT_TRUE(vrf.plantLoop());
  EXPECT_TRUE(vrf.isCondenserTypeDefaulted());
  EXPECT_EQ("WaterCooled", vrf.condenserType());
  EXPECT_EQ(7u, plantLoop.demandComponents().size());
  EXPECT_EQ(1u, plantLoop.demandComponents(AirConditionerVariableRefrigerantFlow::iddObjectType()).size());

  ASSERT_TRUE(vrf.inletModelObject());
  ASSERT_TRUE(vrf.outletModelObject());
  EXPECT_NE(vrf.inletModelObject()->handle(), vrf.outletModelObject()->handle());
  EXPECT_EQ(demandOutletNode.handle(), vrf.outletModelObject()->handle());
  EXPECT_EQ(1u, plantLoop
                  .demandComponents(vrf.inletModelObject()->cast<Node>(), vrf.outletModelObject()->cast<Node>(),
                                    AirConditionerVariableRefrigerantFlow::iddObjectType())
                  .size());

  EXPECT_TRUE(vrf.removeFromLoop());
  EXPECT_FALSE(vrf.plantLoop());
  EXPECT_TRUE(vrf.isCondenserTypeDefaulted());
  EXPECT_EQ("AirCooled", vrf.condenserType());
  EXPECT_EQ(5u, plantLoop.demandComponents().size());
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_TerminalRelationshipIsExclusiveAndRenameSafe) {
  Model model;
  AirConditionerVariableRefrigerantFlow first(model);
  AirConditionerVariableRefrigerantFlow second(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);

  ASSERT_TRUE(first.setName("First VRF Outdoor Unit"));
  ASSERT_TRUE(second.setName("Second VRF Outdoor Unit"));
  ASSERT_TRUE(terminal.setName("VRF Indoor Terminal"));
  EXPECT_TRUE(first.addTerminal(terminal));
  EXPECT_TRUE(first.addTerminal(terminal));
  ASSERT_EQ(1u, first.terminals().size());
  EXPECT_EQ(terminal.handle(), first.terminals().front().handle());
  ASSERT_TRUE(terminal.vrfSystem());
  EXPECT_EQ(first.handle(), terminal.vrfSystem()->handle());

  EXPECT_FALSE(second.addTerminal(terminal));
  EXPECT_TRUE(second.terminals().empty());
  ASSERT_TRUE(terminal.vrfSystem());
  EXPECT_EQ(first.handle(), terminal.vrfSystem()->handle());

  ASSERT_TRUE(terminal.setName("Renamed VRF Indoor Terminal"));
  ASSERT_EQ(1u, first.terminals().size());
  EXPECT_EQ(terminal.handle(), first.terminals().front().handle());
  auto list = first.getModelObjectTarget<ModelObject>(openstudio::AirConditioner_VariableRefrigerantFlowFields::ZoneTerminalUnitListName);
  ASSERT_TRUE(list);
  ASSERT_EQ(1u, list->extensibleGroups().size());
  auto group = list->extensibleGroups().front().optionalCast<openstudio::WorkspaceExtensibleGroup>();
  ASSERT_TRUE(group);
  auto target = group->getTarget(openstudio::ZoneTerminalUnitListExtensibleFields::ZoneTerminalUnitName);
  ASSERT_TRUE(target);
  EXPECT_EQ(terminal.handle(), target->handle());

  first.removeTerminal(terminal);
  EXPECT_TRUE(first.terminals().empty());
  EXPECT_FALSE(terminal.vrfSystem());
  EXPECT_TRUE(second.addTerminal(terminal));
  ASSERT_TRUE(terminal.vrfSystem());
  EXPECT_EQ(second.handle(), terminal.vrfSystem()->handle());
  second.removeAllTerminals();
  EXPECT_TRUE(second.terminals().empty());
  EXPECT_FALSE(terminal.vrfSystem());
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_TerminalRelationshipRejectsForeignAndFluidControlTerminals) {
  Model model;
  Model foreignModel;
  AirConditionerVariableRefrigerantFlow system(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow foreignTerminal(foreignModel);
  ZoneHVACTerminalUnitVariableRefrigerantFlow fluidTerminal(model);
  CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl fluidCoolingCoil(model);

  ASSERT_TRUE(fluidTerminal.setCoolingCoil(fluidCoolingCoil));
  EXPECT_FALSE(system.addTerminal(foreignTerminal));
  EXPECT_FALSE(system.addTerminal(fluidTerminal));
  EXPECT_TRUE(system.terminals().empty());
  EXPECT_FALSE(fluidTerminal.vrfSystem());
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_TerminalRelationshipSurvivesReload) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-vrf-terminal-list-roundtrip.idf");

  Model model;
  AirConditionerVariableRefrigerantFlow system(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);
  ASSERT_TRUE(system.setName("Roundtrip VRF Outdoor Unit"));
  ASSERT_TRUE(terminal.setName("Roundtrip VRF Indoor Terminal"));
  ASSERT_TRUE(system.addTerminal(terminal));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedSystem = loadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Roundtrip VRF Outdoor Unit");
  auto loadedTerminal = loadedModel->getConcreteModelObjectByName<ZoneHVACTerminalUnitVariableRefrigerantFlow>("Roundtrip VRF Indoor Terminal");
  ASSERT_TRUE(loadedSystem);
  ASSERT_TRUE(loadedTerminal);
  ASSERT_EQ(1u, loadedSystem->terminals().size());
  EXPECT_EQ(loadedTerminal->handle(), loadedSystem->terminals().front().handle());
  ASSERT_TRUE(loadedTerminal->vrfSystem());
  EXPECT_EQ(loadedSystem->handle(), loadedTerminal->vrfSystem()->handle());
  EXPECT_EQ(1u, loadedModel->getObjectsByType(openstudio::IddObjectType::ZoneTerminalUnitList).size());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_TerminalAndSystemRemovalOwnOnlyTheirTopology) {
  Model model;
  AirConditionerVariableRefrigerantFlow firstSystem(model);
  AirConditionerVariableRefrigerantFlow secondSystem(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow firstTerminal(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow secondTerminal(model);
  ASSERT_TRUE(firstSystem.addTerminal(firstTerminal));
  ASSERT_TRUE(secondSystem.addTerminal(secondTerminal));

  const auto firstTerminalHandle = firstTerminal.handle();
  EXPECT_FALSE(firstTerminal.remove().empty());
  EXPECT_FALSE(model.getObject(firstTerminalHandle));
  EXPECT_TRUE(firstSystem.terminals().empty());
  EXPECT_EQ(1u, secondSystem.terminals().size());
  EXPECT_EQ(2u, model.getObjectsByType(openstudio::IddObjectType::ZoneTerminalUnitList).size());

  const auto secondSystemHandle = secondSystem.handle();
  EXPECT_FALSE(secondSystem.remove().empty());
  EXPECT_FALSE(model.getObject(secondSystemHandle));
  EXPECT_TRUE(model.getObject(secondTerminal.handle()));
  EXPECT_FALSE(secondTerminal.vrfSystem());
  EXPECT_EQ(1u, model.getObjectsByType(openstudio::IddObjectType::ZoneTerminalUnitList).size());
}
