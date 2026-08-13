/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "../Curve/CurveQuadratic.hpp"
#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/AirLoopHVAC_Impl.hpp"
#include "../ModelObject/Branch.hpp"
#include "../ModelObject/BranchList.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/CoilHeatingGas.hpp"
#include "../StraightComponent/CoilHeatingGas_Impl.hpp"
#include "../StraightComponent/Duct.hpp"
#include "../StraightComponent/Node.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeReheat.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeReheat_Impl.hpp"

#include <utilities/idd/Coil_Heating_Fuel_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingGas_DefaultConstructor) {
  Model model;
  CoilHeatingGas coil(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Coil_Heating_Fuel), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
  auto availability = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(availability);
  EXPECT_DOUBLE_EQ(1.0, availability->value());
  EXPECT_FALSE(coil.partLoadFractionCorrelationCurve());
  EXPECT_FALSE(coil.getTarget(openstudio::Coil_Heating_FuelFields::TemperatureSetpointNodeName));
}

TEST_F(EPModelFixture, CoilHeatingGas_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingGas coil(model);

  EXPECT_FALSE(CoilHeatingGas::validFuelTypeValues().empty());
  EXPECT_EQ("NaturalGas", coil.fuelType());

  EXPECT_TRUE(coil.setFuelType("Propane"));
  EXPECT_EQ("Propane", coil.fuelType());
  coil.resetFuelType();
  EXPECT_EQ("NaturalGas", coil.fuelType());

  EXPECT_TRUE(coil.setGasBurnerEfficiency(0.81));
  EXPECT_DOUBLE_EQ(0.81, coil.gasBurnerEfficiency());

  EXPECT_TRUE(coil.setOnCycleParasiticElectricLoad(10.5));
  EXPECT_DOUBLE_EQ(10.5, coil.onCycleParasiticElectricLoad());
  EXPECT_DOUBLE_EQ(10.5, coil.parasiticElectricLoad());
  EXPECT_TRUE(coil.setParasiticElectricLoad(11.5));
  EXPECT_DOUBLE_EQ(11.5, coil.onCycleParasiticElectricLoad());

  EXPECT_TRUE(coil.setOffCycleParasiticGasLoad(2.25));
  EXPECT_DOUBLE_EQ(2.25, coil.offCycleParasiticGasLoad());
  EXPECT_DOUBLE_EQ(2.25, coil.parasiticGasLoad());
  EXPECT_TRUE(coil.setParasiticGasLoad(3.25));
  EXPECT_DOUBLE_EQ(3.25, coil.offCycleParasiticGasLoad());

  EXPECT_TRUE(coil.isNominalCapacityAutosized());
  EXPECT_FALSE(coil.nominalCapacity());
  EXPECT_TRUE(coil.setNominalCapacity(1200.0));
  ASSERT_TRUE(coil.nominalCapacity());
  EXPECT_DOUBLE_EQ(1200.0, coil.nominalCapacity().get());
  EXPECT_FALSE(coil.isNominalCapacityAutosized());
  coil.resetNominalCapacity();
  EXPECT_FALSE(coil.nominalCapacity());
  coil.autosizeNominalCapacity();
  EXPECT_TRUE(coil.isNominalCapacityAutosized());
  EXPECT_FALSE(coil.autosizedNominalCapacity());
}

TEST_F(EPModelFixture, CoilHeatingGas_RelationshipSetters_RoundTrip) {
  Model model;
  CoilHeatingGas coil(model);
  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.4));
  CurveQuadratic plf(model);
  ASSERT_TRUE(plf.setCoefficient1Constant(0.8));
  ASSERT_TRUE(plf.setCoefficient2x(0.2));
  ASSERT_TRUE(plf.setCoefficient3xPOW2(0.0));

  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());

  EXPECT_TRUE(coil.setPartLoadFractionCorrelationCurve(plf));
  ASSERT_TRUE(coil.partLoadFractionCorrelationCurve());
  EXPECT_EQ(plf.handle(), coil.partLoadFractionCorrelationCurve()->handle());

  const auto children = coil.children();
  ASSERT_EQ(1u, children.size());
  EXPECT_EQ(plf.handle(), children[0].handle());

  coil.resetPartLoadFractionCorrelationCurve();
  EXPECT_FALSE(coil.partLoadFractionCorrelationCurve());
  EXPECT_TRUE(coil.children().empty());
}

TEST_F(EPModelFixture, CoilHeatingGas_AddToNodeRejectsAirLoopDemandNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  CoilHeatingGas coil(model);

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto demandBranchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(demandBranchNode);

  ThermalZone zone(model);
  ASSERT_TRUE(zone.addToNode(*demandBranchNode));
  EXPECT_FALSE(coil.addToNode(*demandBranchNode));
}

TEST_F(EPModelFixture, CoilHeatingGas_AddToNodeSupportsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  CoilHeatingGas supplyCoil(model);
  EXPECT_TRUE(supplyCoil.addToNode(supplyInletNode));
  EXPECT_EQ(5u, airLoop.supplyComponents().size());
  EXPECT_FALSE(oaSystem.component(supplyCoil.handle()));

  CoilHeatingGas coil(model);
  EXPECT_TRUE(coil.addToNode(*outboardOANode));
  EXPECT_EQ(3u, oaSystem.oaComponents().size());

  auto inletObject = coil.inletModelObject();
  auto outletObject = coil.outletModelObject();
  ASSERT_TRUE(inletObject);
  ASSERT_TRUE(outletObject);
  EXPECT_FALSE(coil.addToNode(*outboardOANode));
  EXPECT_EQ(3u, oaSystem.oaComponents().size());
  ASSERT_TRUE(coil.inletModelObject());
  ASSERT_TRUE(coil.outletModelObject());
  EXPECT_EQ(inletObject->handle(), coil.inletModelObject()->handle());
  EXPECT_EQ(outletObject->handle(), coil.outletModelObject()->handle());

  auto setpointNode = coil.getTarget(openstudio::Coil_Heating_FuelFields::TemperatureSetpointNodeName);
  ASSERT_TRUE(setpointNode);
  EXPECT_EQ(coil.outletModelObject()->handle(), setpointNode->handle());
  EXPECT_TRUE(coil.removeFromLoop());
  EXPECT_FALSE(coil.getTarget(openstudio::Coil_Heating_FuelFields::TemperatureSetpointNodeName));
}

TEST_F(EPModelFixture, CoilHeatingGas_DualDuctSetpointNodeLifecycleAcrossReload) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-gas-coil-dual-duct.idf");

  Model model;
  AirLoopHVAC airLoop(model, true);
  ASSERT_TRUE(airLoop.setName("Gas Coil Dual Duct Loop"));
  auto deckOutlets = airLoop.supplyOutletNodes();
  ASSERT_EQ(2u, deckOutlets.size());

  Duct hotDeckDuct(model);
  ASSERT_TRUE(hotDeckDuct.setName("Gas Coil Hot Deck Duct"));
  ASSERT_TRUE(hotDeckDuct.addToNode(deckOutlets[0]));

  CoilHeatingGas heatingCoil(model);
  ASSERT_TRUE(heatingCoil.setName("Gas Coil Hot Deck Heating Coil"));
  ASSERT_TRUE(heatingCoil.addToNode(deckOutlets[0]));

  Duct coldDeckDuct(model);
  ASSERT_TRUE(coldDeckDuct.setName("Gas Coil Cold Deck Duct"));
  ASSERT_TRUE(coldDeckDuct.addToNode(deckOutlets[1]));

  ASSERT_TRUE(heatingCoil.airLoopHVAC());
  EXPECT_EQ(airLoop.handle(), heatingCoil.airLoopHVAC()->handle());
  ASSERT_TRUE(heatingCoil.outletModelObject());
  auto setpointNode = heatingCoil.getTarget(openstudio::Coil_Heating_FuelFields::TemperatureSetpointNodeName);
  ASSERT_TRUE(setpointNode);
  EXPECT_EQ(heatingCoil.outletModelObject()->handle(), setpointNode->handle());
  EXPECT_EQ(deckOutlets[0].handle(), setpointNode->handle());

  auto branches = airLoop.getImpl<detail::AirLoopHVAC_Impl>()->branchList().branches();
  ASSERT_EQ(3u, branches.size());
  ASSERT_EQ(2u, branches[1].components().size());
  EXPECT_EQ(hotDeckDuct.handle(), branches[1].components().front().handle());
  EXPECT_EQ(heatingCoil.handle(), branches[1].components().back().handle());
  ASSERT_EQ(1u, branches[2].components().size());
  EXPECT_EQ(coldDeckDuct.handle(), branches[2].components().front().handle());

  EXPECT_TRUE(heatingCoil.removeFromLoop());
  EXPECT_FALSE(heatingCoil.airLoopHVAC());
  EXPECT_FALSE(heatingCoil.getTarget(openstudio::Coil_Heating_FuelFields::TemperatureSetpointNodeName));
  EXPECT_TRUE(hotDeckDuct.airLoopHVAC());
  EXPECT_TRUE(coldDeckDuct.airLoopHVAC());
  ASSERT_EQ(1u, branches[1].components().size());
  EXPECT_EQ(hotDeckDuct.handle(), branches[1].components().front().handle());

  ASSERT_TRUE(heatingCoil.addToNode(deckOutlets[0]));
  setpointNode = heatingCoil.getTarget(openstudio::Coil_Heating_FuelFields::TemperatureSetpointNodeName);
  ASSERT_TRUE(setpointNode);
  ASSERT_TRUE(heatingCoil.outletModelObject());
  EXPECT_EQ(heatingCoil.outletModelObject()->handle(), setpointNode->handle());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Gas Coil Dual Duct Loop");
  auto loadedCoil = loadedModel->getConcreteModelObjectByName<CoilHeatingGas>("Gas Coil Hot Deck Heating Coil");
  ASSERT_TRUE(loadedLoop);
  ASSERT_TRUE(loadedCoil);
  ASSERT_TRUE(loadedCoil->airLoopHVAC());
  EXPECT_EQ(loadedLoop->handle(), loadedCoil->airLoopHVAC()->handle());
  ASSERT_TRUE(loadedCoil->outletModelObject());
  const auto loadedSetpointNode = loadedCoil->getTarget(openstudio::Coil_Heating_FuelFields::TemperatureSetpointNodeName);
  ASSERT_TRUE(loadedSetpointNode);
  EXPECT_EQ(loadedCoil->outletModelObject()->handle(), loadedSetpointNode->handle());

  const auto loadedCoilHandle = loadedCoil->handle();
  EXPECT_FALSE(loadedLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(loadedCoilHandle));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, CoilHeatingGas_SetpointNodeFollowsOutletRewiring) {
  Model model;
  AirLoopHVAC airLoop(model);
  auto supplyInlet = airLoop.supplyInletNode();

  CoilHeatingGas heatingCoil(model);
  ASSERT_TRUE(heatingCoil.addToNode(supplyInlet));
  ASSERT_TRUE(heatingCoil.outletModelObject());
  const auto originalOutlet = heatingCoil.outletModelObject()->handle();

  Duct downstreamDuct(model);
  auto heatingCoilOutlet = heatingCoil.outletModelObject()->cast<Node>();
  ASSERT_TRUE(downstreamDuct.addToNode(heatingCoilOutlet));
  ASSERT_TRUE(heatingCoil.outletModelObject());
  EXPECT_NE(originalOutlet, heatingCoil.outletModelObject()->handle());
  auto setpointNode = heatingCoil.getTarget(openstudio::Coil_Heating_FuelFields::TemperatureSetpointNodeName);
  ASSERT_TRUE(setpointNode);
  EXPECT_EQ(heatingCoil.outletModelObject()->handle(), setpointNode->handle());

  EXPECT_TRUE(downstreamDuct.removeFromLoop());
  ASSERT_TRUE(heatingCoil.outletModelObject());
  setpointNode = heatingCoil.getTarget(openstudio::Coil_Heating_FuelFields::TemperatureSetpointNodeName);
  ASSERT_TRUE(setpointNode);
  EXPECT_EQ(heatingCoil.outletModelObject()->handle(), setpointNode->handle());
}

TEST_F(EPModelFixture, CoilHeatingGas_ParentContainedCoilDoesNotReceiveDirectBranchSetpointNode) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-contained-gas-coil.idf");

  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  auto availability = model.alwaysOnDiscreteSchedule();
  CoilHeatingGas reheatCoil(model);
  ASSERT_TRUE(reheatCoil.setName("Contained Gas Reheat Coil"));
  AirTerminalSingleDuctConstantVolumeReheat terminal(model, availability, reheatCoil);
  ASSERT_TRUE(terminal.setName("Gas Reheat Terminal"));

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(reheatCoil.inletModelObject());
  ASSERT_TRUE(reheatCoil.outletModelObject());
  EXPECT_FALSE(reheatCoil.getTarget(openstudio::Coil_Heating_FuelFields::TemperatureSetpointNodeName));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedTerminal = loadedModel->getConcreteModelObjectByName<AirTerminalSingleDuctConstantVolumeReheat>("Gas Reheat Terminal");
  auto loadedCoil = loadedModel->getConcreteModelObjectByName<CoilHeatingGas>("Contained Gas Reheat Coil");
  ASSERT_TRUE(loadedTerminal);
  ASSERT_TRUE(loadedCoil);
  ASSERT_TRUE(loadedCoil->inletModelObject());
  ASSERT_TRUE(loadedCoil->outletModelObject());
  EXPECT_FALSE(loadedCoil->getTarget(openstudio::Coil_Heating_FuelFields::TemperatureSetpointNodeName));

  ASSERT_TRUE(loadedTerminal->removeFromLoop());
  EXPECT_FALSE(loadedCoil->inletModelObject());
  EXPECT_FALSE(loadedCoil->outletModelObject());
  EXPECT_FALSE(loadedCoil->getTarget(openstudio::Coil_Heating_FuelFields::TemperatureSetpointNodeName));

  openstudio::filesystem::remove(idfPath);
}
