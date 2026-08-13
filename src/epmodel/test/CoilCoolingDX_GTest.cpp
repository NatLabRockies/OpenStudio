/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/AirLoopHVAC_Impl.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../ModelObject/Branch.hpp"
#include "../ModelObject/BranchList.hpp"
#include "../ModelObject/CoilSystemCoolingDX.hpp"
#include "../ModelObject/CoilSystemCoolingDX_Impl.hpp"
#include "../ResourceObject/CoilCoolingDXCurveFitOperatingMode.hpp"
#include "../ResourceObject/CoilCoolingDXCurveFitPerformance.hpp"
#include "../ResourceObject/CoilCoolingDXCurveFitSpeed.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/CoilCoolingDX.hpp"
#include "../StraightComponent/CoilCoolingDX_Impl.hpp"
#include "../StraightComponent/Duct.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/StraightComponent.hpp"
#include "../HVACComponent/ThermalZone.hpp"

#include <utilities/idd/Coil_Cooling_DX_FieldEnums.hxx>
#include <utilities/idd/Coil_Cooling_DX_CurveFit_Performance_FieldEnums.hxx>
#include <utilities/idd/CoilSystem_Cooling_DX_FieldEnums.hxx>
#include <utilities/core/PathHelpers.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingDX_DefaultConstructor) {
  Model model;
  CoilCoolingDX coil(model);

  EXPECT_EQ(CoilCoolingDX::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
  auto availability = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(availability);
  EXPECT_DOUBLE_EQ(1.0, availability->value());
  EXPECT_EQ(CoilCoolingDXCurveFitPerformance::iddObjectType(), coil.performanceObject().iddObject().type());

  const auto children = coil.children();
  ASSERT_EQ(1u, children.size());
  EXPECT_EQ(coil.performanceObject().handle(), children.front().handle());
  EXPECT_FALSE(coil.condenserZone());
}

TEST_F(EPModelFixture, CoilCoolingDX_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingDX coil(model);

  EXPECT_TRUE(coil.setCondenserInletNodeName("DX Condenser Inlet"));
  EXPECT_TRUE(coil.setCondenserOutletNodeName("DX Condenser Outlet"));
  EXPECT_EQ("DX Condenser Inlet", coil.condenserInletNodeName());
  EXPECT_EQ("DX Condenser Outlet", coil.condenserOutletNodeName());
}

TEST_F(EPModelFixture, CoilCoolingDX_RelationshipSetters_RoundTrip) {
  Model model;
  CoilCoolingDX coil(model);

  ScheduleConstant schedule(model);
  EXPECT_TRUE(schedule.setValue(0.25));
  EXPECT_TRUE(coil.setAvailabilitySchedule(schedule));
  EXPECT_EQ(schedule.handle(), coil.availabilitySchedule().handle());

  CoilCoolingDXCurveFitPerformance performance(model);
  EXPECT_TRUE(coil.setPerformanceObject(performance));
  EXPECT_EQ(performance.handle(), coil.performanceObject().handle());

  Model otherModel;
  CoilCoolingDXCurveFitPerformance foreignPerformance(otherModel);
  EXPECT_FALSE(coil.setPerformanceObject(foreignPerformance));
  EXPECT_EQ(performance.handle(), coil.performanceObject().handle());

  const auto performanceChildren = coil.children();
  ASSERT_EQ(1u, performanceChildren.size());
  EXPECT_EQ(performance.handle(), performanceChildren.front().handle());

  ThermalZone zone(model);
  EXPECT_FALSE(coil.condenserZone());
  EXPECT_TRUE(coil.setCondenserZone(zone));
  ASSERT_TRUE(coil.condenserZone());
  EXPECT_EQ(zone.handle(), coil.condenserZone()->handle());
  coil.resetCondenserZone();
  EXPECT_FALSE(coil.condenserZone());
}

TEST_F(EPModelFixture, CoilCoolingDX_FourSpeedPerformanceGraphPersistsOnAirLoop) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-curve-fit-dx-four-speed-graph.idf");

  Model model;
  CurveBiquadratic temperatureCurve(model);
  CurveQuadratic flowCurve(model);
  CurveQuadratic partLoadFractionCurve(model);
  ASSERT_TRUE(temperatureCurve.setName("Curve Fit Shared Temperature Curve"));
  ASSERT_TRUE(flowCurve.setName("Curve Fit Shared Flow Curve"));
  ASSERT_TRUE(partLoadFractionCurve.setName("Curve Fit Shared Part Load Curve"));

  CoilCoolingDXCurveFitSpeed firstSpeed(model);
  CoilCoolingDXCurveFitSpeed secondSpeed(model);
  CoilCoolingDXCurveFitSpeed thirdSpeed(model);
  CoilCoolingDXCurveFitSpeed fourthSpeed(model);
  ASSERT_TRUE(firstSpeed.setName("Curve Fit Speed 1"));
  ASSERT_TRUE(secondSpeed.setName("Curve Fit Speed 2"));
  ASSERT_TRUE(thirdSpeed.setName("Curve Fit Speed 3"));
  ASSERT_TRUE(fourthSpeed.setName("Curve Fit Speed 4"));

  for (auto* speed : {&firstSpeed, &secondSpeed, &thirdSpeed, &fourthSpeed}) {
    ASSERT_TRUE(speed->setTotalCoolingCapacityModifierFunctionofTemperatureCurve(temperatureCurve));
    ASSERT_TRUE(speed->setTotalCoolingCapacityModifierFunctionofAirFlowFractionCurve(flowCurve));
    ASSERT_TRUE(speed->setEnergyInputRatioModifierFunctionofTemperatureCurve(temperatureCurve));
    ASSERT_TRUE(speed->setEnergyInputRatioModifierFunctionofAirFlowFractionCurve(flowCurve));
    ASSERT_TRUE(speed->setPartLoadFractionCorrelationCurve(partLoadFractionCurve));
    ASSERT_TRUE(speed->setWasteHeatModifierFunctionofTemperatureCurve(temperatureCurve));
  }

  CoilCoolingDXCurveFitOperatingMode operatingMode(model);
  ASSERT_TRUE(operatingMode.setName("Curve Fit Four Speed Operating Mode"));
  ASSERT_TRUE(operatingMode.addSpeed(firstSpeed));
  ASSERT_TRUE(operatingMode.addSpeed(secondSpeed));
  ASSERT_TRUE(operatingMode.addSpeed(thirdSpeed));
  ASSERT_TRUE(operatingMode.addSpeed(fourthSpeed));
  ASSERT_TRUE(operatingMode.setNominalSpeedNumber(1));

  CoilCoolingDXCurveFitPerformance performance(model, operatingMode);
  ASSERT_TRUE(performance.setName("Curve Fit Four Speed Performance"));
  CoilCoolingDX coil(model, performance);
  ASSERT_TRUE(coil.setName("Curve Fit Four Speed Coil"));
  AirLoopHVAC airLoop(model);
  ASSERT_TRUE(airLoop.setName("Curve Fit Four Speed Air Loop"));
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(coil.addToNode(supplyInletNode));
  EXPECT_TRUE(airLoop.supplyComponent(coil.handle()));
  EXPECT_EQ(performance.handle(), coil.performanceObject().handle());
  EXPECT_EQ(operatingMode.handle(), performance.baseOperatingMode().handle());
  EXPECT_EQ(4u, operatingMode.numberOfSpeeds());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedAirLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Curve Fit Four Speed Air Loop");
  auto loadedCoil = loadedModel->getConcreteModelObjectByName<CoilCoolingDX>("Curve Fit Four Speed Coil");
  ASSERT_TRUE(loadedAirLoop);
  ASSERT_TRUE(loadedCoil);
  EXPECT_TRUE(loadedAirLoop->supplyComponent(loadedCoil->handle()));

  const auto loadedPerformance = loadedCoil->performanceObject();
  EXPECT_EQ("Curve Fit Four Speed Performance", loadedPerformance.nameString());
  const auto loadedBasinHeaterSchedule =
    loadedPerformance.getTarget(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::EvaporativeCondenserBasinHeaterOperatingScheduleName);
  ASSERT_TRUE(loadedBasinHeaterSchedule);
  EXPECT_EQ(loadedModel->alwaysOnDiscreteSchedule().handle(), loadedBasinHeaterSchedule->handle());
  const auto loadedOperatingMode = loadedPerformance.baseOperatingMode();
  EXPECT_EQ("Curve Fit Four Speed Operating Mode", loadedOperatingMode.nameString());
  const auto loadedSpeeds = loadedOperatingMode.speeds();
  ASSERT_EQ(4u, loadedSpeeds.size());
  EXPECT_EQ("Curve Fit Speed 1", loadedSpeeds[0].nameString());
  EXPECT_EQ("Curve Fit Speed 2", loadedSpeeds[1].nameString());
  EXPECT_EQ("Curve Fit Speed 3", loadedSpeeds[2].nameString());
  EXPECT_EQ("Curve Fit Speed 4", loadedSpeeds[3].nameString());
  EXPECT_EQ(1u, loadedOperatingMode.nominalSpeedNumber());
  for (const auto& loadedSpeed : loadedSpeeds) {
    ASSERT_TRUE(loadedSpeed.totalCoolingCapacityModifierFunctionofTemperatureCurve());
    ASSERT_TRUE(loadedSpeed.totalCoolingCapacityModifierFunctionofAirFlowFractionCurve());
    ASSERT_TRUE(loadedSpeed.energyInputRatioModifierFunctionofTemperatureCurve());
    ASSERT_TRUE(loadedSpeed.energyInputRatioModifierFunctionofAirFlowFractionCurve());
    ASSERT_TRUE(loadedSpeed.partLoadFractionCorrelationCurve());
    ASSERT_TRUE(loadedSpeed.wasteHeatModifierFunctionofTemperatureCurve());
    EXPECT_EQ("Curve Fit Shared Temperature Curve", loadedSpeed.totalCoolingCapacityModifierFunctionofTemperatureCurve()->nameString());
    EXPECT_EQ("Curve Fit Shared Flow Curve", loadedSpeed.totalCoolingCapacityModifierFunctionofAirFlowFractionCurve()->nameString());
    EXPECT_EQ("Curve Fit Shared Temperature Curve", loadedSpeed.energyInputRatioModifierFunctionofTemperatureCurve()->nameString());
    EXPECT_EQ("Curve Fit Shared Flow Curve", loadedSpeed.energyInputRatioModifierFunctionofAirFlowFractionCurve()->nameString());
    EXPECT_EQ("Curve Fit Shared Part Load Curve", loadedSpeed.partLoadFractionCorrelationCurve()->nameString());
    EXPECT_EQ("Curve Fit Shared Temperature Curve", loadedSpeed.wasteHeatModifierFunctionofTemperatureCurve()->nameString());
  }

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, CoilCoolingDX_StraightComponentPortsWithoutLoopPlacement) {
  Model model;
  CoilCoolingDX coil(model);

  EXPECT_TRUE(coil.optionalCast<StraightComponent>());
  EXPECT_EQ(openstudio::Coil_Cooling_DXFields::EvaporatorInletNodeName, coil.inletPort());
  EXPECT_EQ(openstudio::Coil_Cooling_DXFields::EvaporatorOutletNodeName, coil.outletPort());
}

TEST_F(EPModelFixture, CoilCoolingDX_AddToNodeSupplyOnly) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  CoilCoolingDX supplyCoil(model);
  CoilCoolingDX demandCoil(model);
  CoilCoolingDX oaCoil(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(supplyCoil.addToNode(supplyInletNode));
  ASSERT_TRUE(supplyCoil.inletModelObject());
  EXPECT_EQ(supplyInletNode, supplyCoil.inletModelObject()->cast<Node>());
  EXPECT_TRUE(supplyCoil.outletModelObject());
  auto systems = model.getConcreteModelObjects<CoilSystemCoolingDX>();
  ASSERT_EQ(1u, systems.size());
  auto system = systems.front();
  ASSERT_TRUE(system.coolingCoil());
  EXPECT_EQ(supplyCoil.handle(), system.coolingCoil()->handle());
  ASSERT_TRUE(system.inletModelObject());
  ASSERT_TRUE(system.outletModelObject());
  ASSERT_TRUE(system.sensorNode());
  EXPECT_EQ(supplyCoil.inletModelObject()->handle(), system.inletModelObject()->handle());
  EXPECT_EQ(supplyCoil.outletModelObject()->handle(), system.outletModelObject()->handle());
  EXPECT_EQ(system.outletModelObject()->handle(), system.sensorNode()->handle());
  EXPECT_EQ(supplyCoil.iddObject().name(), system.coolingCoilObjectType());
  EXPECT_TRUE(airLoop.supplyComponent(supplyCoil.handle()));
  EXPECT_FALSE(airLoop.supplyComponent(system.handle()));

  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(demandCoil.addToNode(demandInletNode));
  EXPECT_FALSE(demandCoil.airLoopHVAC());

  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);
  EXPECT_FALSE(oaCoil.addToNode(*outboardOANode));
  EXPECT_FALSE(oaCoil.airLoopHVAC());
}

TEST_F(EPModelFixture, CoilCoolingDX_AdapterLifecycleAcrossReloadAndAirLoopRemoval) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-curve-fit-dx-adapter.idf");

  Model model;
  AirLoopHVAC airLoop(model);
  ASSERT_TRUE(airLoop.setName("Curve Fit DX Adapter Loop"));
  CoilCoolingDX coil(model);
  ASSERT_TRUE(coil.setName("Curve Fit DX Coil"));
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(coil.addToNode(supplyInletNode));

  auto systems = model.getConcreteModelObjects<CoilSystemCoolingDX>();
  ASSERT_EQ(1u, systems.size());
  auto system = systems.front();

  ScheduleConstant alternateAvailability(model);
  ASSERT_TRUE(alternateAvailability.setValue(0.8));
  ASSERT_TRUE(coil.setAvailabilitySchedule(alternateAvailability));
  auto systemAvailability = system.getTarget(openstudio::CoilSystem_Cooling_DXFields::AvailabilityScheduleName);
  ASSERT_TRUE(systemAvailability);
  EXPECT_EQ(alternateAvailability.handle(), systemAvailability->handle());

  Duct downstreamDuct(model);
  ASSERT_TRUE(downstreamDuct.setName("Curve Fit DX Downstream Duct"));
  ASSERT_TRUE(downstreamDuct.addToNode(supplyInletNode));
  ASSERT_TRUE(system.outletModelObject());
  ASSERT_TRUE(system.sensorNode());
  ASSERT_TRUE(coil.outletModelObject());
  EXPECT_EQ(system.outletModelObject()->handle(), coil.outletModelObject()->handle());
  EXPECT_EQ(system.outletModelObject()->handle(), system.sensorNode()->handle());

  EXPECT_TRUE(coil.removeFromLoop());
  EXPECT_FALSE(coil.airLoopHVAC());
  EXPECT_FALSE(system.airLoopHVAC());
  EXPECT_FALSE(coil.inletModelObject());
  EXPECT_FALSE(coil.outletModelObject());
  EXPECT_FALSE(system.inletModelObject());
  EXPECT_FALSE(system.outletModelObject());
  EXPECT_FALSE(system.sensorNode());
  EXPECT_TRUE(downstreamDuct.airLoopHVAC());

  ASSERT_TRUE(coil.addToNode(supplyInletNode));
  EXPECT_EQ(1u, model.getConcreteModelObjects<CoilSystemCoolingDX>().size());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Curve Fit DX Adapter Loop");
  auto loadedCoil = loadedModel->getConcreteModelObjectByName<CoilCoolingDX>("Curve Fit DX Coil");
  auto loadedSystem = loadedModel->getConcreteModelObjectByName<CoilSystemCoolingDX>("Curve Fit DX Coil CoilSystem");
  ASSERT_TRUE(loadedLoop);
  ASSERT_TRUE(loadedCoil);
  ASSERT_TRUE(loadedSystem);
  ASSERT_TRUE(loadedSystem->coolingCoil());
  EXPECT_EQ(loadedCoil->handle(), loadedSystem->coolingCoil()->handle());
  EXPECT_TRUE(loadedLoop->supplyComponent(loadedCoil->handle()));
  EXPECT_FALSE(loadedLoop->supplyComponent(loadedSystem->handle()));
  ASSERT_TRUE(loadedSystem->sensorNode());
  ASSERT_TRUE(loadedCoil->outletModelObject());
  EXPECT_EQ(loadedCoil->outletModelObject()->handle(), loadedSystem->sensorNode()->handle());

  const auto loadedCoilHandle = loadedCoil->handle();
  const auto loadedSystemHandle = loadedSystem->handle();
  EXPECT_FALSE(loadedLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(loadedCoilHandle));
  EXPECT_FALSE(loadedModel->getObject(loadedSystemHandle));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, CoilCoolingDX_MovesBetweenDualDuctDecksWithOneAdapter) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  auto deckOutlets = airLoop.supplyOutletNodes();
  ASSERT_EQ(2u, deckOutlets.size());

  CoilCoolingDX coil(model);
  ASSERT_TRUE(coil.addToNode(deckOutlets[0]));
  auto systems = model.getConcreteModelObjects<CoilSystemCoolingDX>();
  ASSERT_EQ(1u, systems.size());
  const auto systemHandle = systems.front().handle();

  ASSERT_TRUE(coil.addToNode(deckOutlets[1]));
  systems = model.getConcreteModelObjects<CoilSystemCoolingDX>();
  ASSERT_EQ(1u, systems.size());
  auto system = systems.front();
  EXPECT_EQ(systemHandle, system.handle());

  const auto branches = airLoop.getImpl<detail::AirLoopHVAC_Impl>()->branchList().branches();
  ASSERT_EQ(3u, branches.size());
  EXPECT_TRUE(branches[1].components().empty());
  ASSERT_EQ(1u, branches[2].components().size());
  EXPECT_EQ(system.handle(), branches[2].components().front().handle());

  ASSERT_TRUE(system.inletModelObject());
  ASSERT_TRUE(system.outletModelObject());
  ASSERT_TRUE(system.sensorNode());
  ASSERT_TRUE(coil.inletModelObject());
  ASSERT_TRUE(coil.outletModelObject());
  EXPECT_EQ(system.inletModelObject()->handle(), coil.inletModelObject()->handle());
  EXPECT_EQ(system.outletModelObject()->handle(), coil.outletModelObject()->handle());
  EXPECT_EQ(system.outletModelObject()->handle(), system.sensorNode()->handle());

  const auto hotPath = airLoop.supplyComponents(airLoop.supplyInletNode(), deckOutlets[0]);
  const auto coldPath = airLoop.supplyComponents(airLoop.supplyInletNode(), deckOutlets[1]);
  EXPECT_EQ(hotPath.end(), std::ranges::find(hotPath, coil.cast<ModelObject>()));
  EXPECT_NE(coldPath.end(), std::ranges::find(coldPath, coil.cast<ModelObject>()));
  EXPECT_EQ(coldPath.end(), std::ranges::find(coldPath, system.cast<ModelObject>()));
}

TEST_F(EPModelFixture, CoilCoolingDX_RejectsAmbiguousAdaptersWithoutBranchMutation) {
  Model model;
  AirLoopHVAC airLoop(model);
  CoilCoolingDX coil(model);
  CoilSystemCoolingDX firstSystem(model);
  CoilSystemCoolingDX secondSystem(model);

  for (auto* system : {&firstSystem, &secondSystem}) {
    ASSERT_TRUE(system->setCoolingCoilObjectType(coil.iddObject().name()));
    ASSERT_TRUE(system->setPointer(openstudio::CoilSystem_Cooling_DXFields::CoolingCoilName, coil.handle()));
  }

  const auto branches = airLoop.getImpl<detail::AirLoopHVAC_Impl>()->branchList().branches();
  ASSERT_EQ(1u, branches.size());
  EXPECT_TRUE(branches.front().components().empty());
  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_FALSE(coil.addToNode(supplyInletNode));
  EXPECT_TRUE(branches.front().components().empty());
  EXPECT_FALSE(coil.inletModelObject());
  EXPECT_FALSE(coil.outletModelObject());
}

TEST_F(EPModelFixture, CoilCoolingDX_MalformedPersistedAdapterIsNotProjected) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-curve-fit-dx-malformed-adapter.idf");

  Model model;
  AirLoopHVAC airLoop(model);
  ASSERT_TRUE(airLoop.setName("Malformed Curve Fit DX Adapter Loop"));
  CoilCoolingDX coil(model);
  ASSERT_TRUE(coil.setName("Malformed Curve Fit DX Adapter Coil"));
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(coil.addToNode(supplyInletNode));

  auto systems = model.getConcreteModelObjects<CoilSystemCoolingDX>();
  ASSERT_EQ(1u, systems.size());
  auto system = systems.front();
  ASSERT_TRUE(system.inletModelObject());
  ASSERT_TRUE(system.outletModelObject());
  ASSERT_TRUE(system.setPointer(openstudio::CoilSystem_Cooling_DXFields::DXCoolingCoilSystemSensorNodeName, system.inletModelObject()->handle()));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Malformed Curve Fit DX Adapter Loop");
  auto loadedCoil = loadedModel->getConcreteModelObjectByName<CoilCoolingDX>("Malformed Curve Fit DX Adapter Coil");
  auto loadedSystem = loadedModel->getConcreteModelObjectByName<CoilSystemCoolingDX>("Malformed Curve Fit DX Adapter Coil CoilSystem");
  ASSERT_TRUE(loadedLoop);
  ASSERT_TRUE(loadedCoil);
  ASSERT_TRUE(loadedSystem);
  EXPECT_TRUE(loadedLoop->supplyComponent(loadedSystem->handle()));
  EXPECT_FALSE(loadedLoop->supplyComponent(loadedCoil->handle()));
  EXPECT_TRUE(loadedSystem->airLoopHVAC());
  EXPECT_FALSE(loadedCoil->airLoopHVAC());
  EXPECT_FALSE(loadedCoil->removeFromLoop());
  EXPECT_FALSE(loadedSystem->removeFromLoop());
  EXPECT_TRUE(loadedSystem->remove().empty());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, CoilCoolingDX_RemoveDeletesAdapterAndPreservesAdjacentComponent) {
  Model model;
  AirLoopHVAC airLoop(model);
  CoilCoolingDX coil(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(coil.addToNode(supplyInletNode));
  Duct downstreamDuct(model);
  ASSERT_TRUE(downstreamDuct.addToNode(supplyInletNode));

  auto systems = model.getConcreteModelObjects<CoilSystemCoolingDX>();
  ASSERT_EQ(1u, systems.size());
  const auto coilHandle = coil.handle();
  const auto systemHandle = systems.front().handle();
  EXPECT_FALSE(coil.remove().empty());
  EXPECT_FALSE(model.getObject(coilHandle));
  EXPECT_FALSE(model.getObject(systemHandle));
  EXPECT_TRUE(downstreamDuct.airLoopHVAC());
}

TEST_F(EPModelFixture, CoilSystemCoolingDX_DirectRemovalDetachesCurveFitChildAndHealsBranch) {
  Model model;
  AirLoopHVAC airLoop(model);
  CoilCoolingDX coil(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(coil.addToNode(supplyInletNode));
  Duct downstreamDuct(model);
  ASSERT_TRUE(downstreamDuct.addToNode(supplyInletNode));

  auto systems = model.getConcreteModelObjects<CoilSystemCoolingDX>();
  ASSERT_EQ(1u, systems.size());
  auto system = systems.front();
  const auto systemHandle = system.handle();
  EXPECT_FALSE(system.remove().empty());
  EXPECT_FALSE(model.getObject(systemHandle));
  EXPECT_TRUE(model.getObject(coil.handle()));
  EXPECT_FALSE(coil.airLoopHVAC());
  EXPECT_FALSE(coil.inletModelObject());
  EXPECT_FALSE(coil.outletModelObject());
  EXPECT_TRUE(downstreamDuct.airLoopHVAC());

  EXPECT_TRUE(coil.addToNode(supplyInletNode));
  EXPECT_TRUE(coil.airLoopHVAC());
  EXPECT_EQ(1u, model.getConcreteModelObjects<CoilSystemCoolingDX>().size());
}
