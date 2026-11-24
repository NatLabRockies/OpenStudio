/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>
#include <stdexcept>

#include "EPModelFixture.hpp"
#include "../AirToAirComponent/HeatExchangerAirToAirSensibleAndLatent.hpp"
#include "../AirToAirComponent/HeatExchangerAirToAirSensibleAndLatent_Impl.hpp"
#include "../AirToAirComponent/HeatExchangerDesiccantBalancedFlow.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../HVACComponent/ControllerWaterCoil.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/AirLoopHVAC_Impl.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../ModelObject/AirLoopHVACControllerList.hpp"
#include "../ModelObject/AirLoopHVACControllerList_Impl.hpp"
#include "../StraightComponent/CoilSystemCoolingWater.hpp"
#include "../StraightComponent/FanSystemModel.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/CoilSystemCoolingWaterHeatExchangerAssisted.hpp"
#include "../StraightComponent/CoilSystemCoolingWaterHeatExchangerAssisted_Impl.hpp"
#include "../SetpointManager/SetpointManagerMixedAir.hpp"
#include "../SetpointManager/SetpointManagerMixedAir_Impl.hpp"
#include "../WaterToAirComponent/CoilCoolingWater.hpp"
#include "../WaterToAirComponent/CoilCoolingWater_Impl.hpp"
#include <utilities/idd/AirLoopHVAC_FieldEnums.hxx>
#include <utilities/idd/CoilSystem_Cooling_Water_FieldEnums.hxx>
#include <utilities/idd/CoilSystem_Cooling_Water_HeatExchangerAssisted_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilSystemCoolingWaterHeatExchangerAssisted_DefaultConstructor) {
  Model model;
  CoilSystemCoolingWaterHeatExchangerAssisted coilSystem(model);
  EXPECT_EQ(CoilSystemCoolingWaterHeatExchangerAssisted::iddObjectType(), coilSystem.iddObject().type());
  EXPECT_FALSE(coilSystem.nameString().empty());

  auto heatExchanger = coilSystem.heatExchanger();
  auto coolingCoil = coilSystem.coolingCoil();
  EXPECT_EQ("HeatExchanger:AirToAir:SensibleAndLatent", heatExchanger.iddObject().name());
  EXPECT_EQ("Coil:Cooling:Water", coolingCoil.iddObject().name());
  EXPECT_EQ(heatExchanger.iddObject().name(), coilSystem.heatExchangerObjectType());
  EXPECT_EQ(coolingCoil.iddObject().name(), coilSystem.coolingCoilObjectType());

  const auto children = coilSystem.children();
  EXPECT_EQ(2u, children.size());
  EXPECT_TRUE(std::any_of(children.begin(), children.end(), [&](const auto& object) { return object.handle() == coolingCoil.handle(); }));
  EXPECT_TRUE(std::any_of(children.begin(), children.end(), [&](const auto& object) { return object.handle() == heatExchanger.handle(); }));
}

TEST_F(EPModelFixture, CoilSystemCoolingWaterHeatExchangerAssisted_RenamedSystemsKeepDistinctContainedAirPaths) {
  Model model;
  AirLoopHVAC firstAirLoop(model);
  CoilSystemCoolingWaterHeatExchangerAssisted firstSystem(model);
  auto firstSupplyOutletNode = firstAirLoop.supplyOutletNode();
  ASSERT_TRUE(firstSystem.addToNode(firstSupplyOutletNode));
  auto firstHeatExchanger = firstSystem.heatExchanger();
  ASSERT_TRUE(firstHeatExchanger.primaryAirOutletModelObject());
  ASSERT_TRUE(firstHeatExchanger.secondaryAirInletModelObject());
  const auto firstSupplyConnectorHandle = firstHeatExchanger.primaryAirOutletModelObject()->handle();
  const auto firstExhaustConnectorHandle = firstHeatExchanger.secondaryAirInletModelObject()->handle();
  ASSERT_TRUE(firstSystem.setName("Renamed Assisted Water Coil System"));

  AirLoopHVAC secondAirLoop(model);
  CoilSystemCoolingWaterHeatExchangerAssisted secondSystem(model);
  auto secondSupplyOutletNode = secondAirLoop.supplyOutletNode();
  ASSERT_TRUE(secondSystem.addToNode(secondSupplyOutletNode));
  auto secondHeatExchanger = secondSystem.heatExchanger();
  ASSERT_TRUE(secondHeatExchanger.primaryAirOutletModelObject());
  ASSERT_TRUE(secondHeatExchanger.secondaryAirInletModelObject());

  EXPECT_NE(firstSupplyConnectorHandle, secondHeatExchanger.primaryAirOutletModelObject()->handle());
  EXPECT_NE(firstExhaustConnectorHandle, secondHeatExchanger.secondaryAirInletModelObject()->handle());
}

TEST_F(EPModelFixture, CoilSystemCoolingWaterHeatExchangerAssisted_ScalarAccessors_RoundTrip) {
  Model model;
  CoilSystemCoolingWaterHeatExchangerAssisted coilSystem(model);

  const auto heatExchangerObjectTypes = CoilSystemCoolingWaterHeatExchangerAssisted::heatExchangerObjectTypeValues();
  EXPECT_FALSE(heatExchangerObjectTypes.empty());
  EXPECT_TRUE(std::find(heatExchangerObjectTypes.begin(), heatExchangerObjectTypes.end(), "HeatExchanger:AirToAir:SensibleAndLatent")
              != heatExchangerObjectTypes.end());

  const auto coolingCoilObjectTypes = CoilSystemCoolingWaterHeatExchangerAssisted::coolingCoilObjectTypeValues();
  EXPECT_FALSE(coolingCoilObjectTypes.empty());
  EXPECT_TRUE(std::find(coolingCoilObjectTypes.begin(), coolingCoilObjectTypes.end(), "Coil:Cooling:Water") != coolingCoilObjectTypes.end());

  EXPECT_TRUE(coilSystem.setHeatExchangerObjectType("HeatExchanger:AirToAir:SensibleAndLatent"));
  EXPECT_EQ("HeatExchanger:AirToAir:SensibleAndLatent", coilSystem.heatExchangerObjectType());

  EXPECT_TRUE(coilSystem.setCoolingCoilObjectType("Coil:Cooling:Water"));
  EXPECT_EQ("Coil:Cooling:Water", coilSystem.coolingCoilObjectType());

  EXPECT_FALSE(coilSystem.setCoolingCoilObjectType("Invalid Coil Type"));
}

TEST_F(EPModelFixture, CoilSystemCoolingWaterHeatExchangerAssisted_RelationshipAccessors_RoundTrip) {
  Model model;
  HeatExchangerAirToAirSensibleAndLatent heatExchanger(model);
  CoilSystemCoolingWaterHeatExchangerAssisted coilSystem(model, heatExchanger);
  CoilCoolingWater coolingCoil(model);

  EXPECT_EQ(heatExchanger.handle(), coilSystem.heatExchanger().handle());
  EXPECT_EQ("Coil:Cooling:Water", coilSystem.coolingCoil().iddObject().name());

  EXPECT_TRUE(coilSystem.setCoolingCoil(coolingCoil));
  EXPECT_EQ(coolingCoil.handle(), coilSystem.coolingCoil().handle());
  EXPECT_EQ(coolingCoil.iddObject().name(), coilSystem.coolingCoilObjectType());

  HeatExchangerAirToAirSensibleAndLatent replacementHeatExchanger(model);
  EXPECT_TRUE(coilSystem.setHeatExchanger(replacementHeatExchanger));
  EXPECT_EQ(replacementHeatExchanger.handle(), coilSystem.heatExchanger().handle());
  EXPECT_EQ(replacementHeatExchanger.iddObject().name(), coilSystem.heatExchangerObjectType());
}

TEST_F(EPModelFixture, CoilSystemCoolingWaterHeatExchangerAssisted_RelationshipSurvivesHeatExchangerRename) {
  Model model;
  HeatExchangerAirToAirSensibleAndLatent heatExchanger(model);
  CoilSystemCoolingWaterHeatExchangerAssisted coilSystem(model, heatExchanger);

  ASSERT_TRUE(heatExchanger.setName("Renamed Assisted Heat Exchanger"));
  EXPECT_EQ(heatExchanger.handle(), coilSystem.heatExchanger().handle());

  const auto children = coilSystem.children();
  ASSERT_EQ(2u, children.size());
  EXPECT_TRUE(std::any_of(children.begin(), children.end(), [&](const auto& child) { return child.handle() == heatExchanger.handle(); }));
}

TEST_F(EPModelFixture, CoilSystemCoolingWaterHeatExchangerAssisted_InvalidRelationshipConstructorCleansUp) {
  Model model;
  HeatExchangerDesiccantBalancedFlow hxDesiccant(model);

  const auto beforeCount = model.getObjectsByType(CoilSystemCoolingWaterHeatExchangerAssisted::iddObjectType()).size();

  EXPECT_ANY_THROW((CoilSystemCoolingWaterHeatExchangerAssisted(model, hxDesiccant)));

  EXPECT_EQ(beforeCount, model.getObjectsByType(CoilSystemCoolingWaterHeatExchangerAssisted::iddObjectType()).size());
}

TEST_F(EPModelFixture, CoilSystemCoolingWaterHeatExchangerAssisted_AddToNodeRejected) {
  Model model;
  AirLoopHVAC airLoop(model);

  CoilSystemCoolingWaterHeatExchangerAssisted supplyCoilSystem(model);
  auto coolingCoil = supplyCoilSystem.coolingCoil();
  auto heatExchanger = supplyCoilSystem.heatExchanger();
  auto supplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(coolingCoil.addToNode(supplyOutletNode));
  EXPECT_FALSE(heatExchanger.addToNode(supplyOutletNode));
  EXPECT_EQ(2u, airLoop.supplyComponents().size());

  EXPECT_TRUE(supplyCoilSystem.addToNode(supplyOutletNode));
  EXPECT_EQ(3u, airLoop.supplyComponents().size());
  ASSERT_TRUE(supplyCoilSystem.airLoopHVAC());
  EXPECT_EQ(airLoop.handle(), supplyCoilSystem.airLoopHVAC()->handle());
  ASSERT_TRUE(coolingCoil.containingHVACComponent());
  EXPECT_EQ(supplyCoilSystem.handle(), coolingCoil.containingHVACComponent().get().handle());
  ASSERT_TRUE(heatExchanger.containingHVACComponent());
  EXPECT_EQ(supplyCoilSystem.handle(), heatExchanger.containingHVACComponent().get().handle());

  CoilSystemCoolingWaterHeatExchangerAssisted standaloneCoilSystem(model);
  Node orphanNode(model);
  EXPECT_FALSE(standaloneCoilSystem.addToNode(orphanNode));
}

TEST_F(EPModelFixture, CoilSystemCoolingWaterHeatExchangerAssisted_ContainedCoolingCoilDoesNotCreateStandaloneController) {
  Model model;
  CoilSystemCoolingWater system(model);
  CoilSystemCoolingWaterHeatExchangerAssisted hxAssisted(model);
  CoilCoolingWater coil(model);
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);

  ASSERT_TRUE(hxAssisted.setCoolingCoil(coil));
  ASSERT_TRUE(system.setCoolingCoil(hxAssisted));

  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(system.addToNode(supplyInletNode));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coil));

  EXPECT_FALSE(coil.controllerWaterCoil());
}

TEST_F(EPModelFixture, CoilSystemCoolingWaterHeatExchangerAssisted_DirectAirPathAndPlantController) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  CoilSystemCoolingWaterHeatExchangerAssisted coilSystem(model);
  ASSERT_TRUE(coilSystem.setName("Direct Assisted Water System"));

  auto heatExchanger = coilSystem.heatExchanger();
  auto coolingCoil = coilSystem.coolingCoil().cast<CoilCoolingWater>();
  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(coilSystem.addToNode(supplyOutletNode));

  ASSERT_TRUE(coilSystem.inletModelObject());
  ASSERT_TRUE(coilSystem.outletModelObject());
  ASSERT_TRUE(heatExchanger.primaryAirInletModelObject());
  ASSERT_TRUE(heatExchanger.primaryAirOutletModelObject());
  ASSERT_TRUE(heatExchanger.secondaryAirInletModelObject());
  ASSERT_TRUE(heatExchanger.secondaryAirOutletModelObject());
  ASSERT_TRUE(coolingCoil.airInletModelObject());
  ASSERT_TRUE(coolingCoil.airOutletModelObject());
  EXPECT_EQ(coilSystem.inletModelObject()->handle(), heatExchanger.primaryAirInletModelObject()->handle());
  EXPECT_EQ(heatExchanger.primaryAirOutletModelObject()->handle(), coolingCoil.airInletModelObject()->handle());
  EXPECT_EQ(coolingCoil.airOutletModelObject()->handle(), heatExchanger.secondaryAirInletModelObject()->handle());
  EXPECT_EQ(heatExchanger.secondaryAirOutletModelObject()->handle(), coilSystem.outletModelObject()->handle());
  EXPECT_NE(coilSystem.inletModelObject()->handle(), coolingCoil.airInletModelObject()->handle());
  EXPECT_NE(coolingCoil.airOutletModelObject()->handle(), coilSystem.outletModelObject()->handle());

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coolingCoil));
  auto controller = coolingCoil.controllerWaterCoil();
  ASSERT_TRUE(controller);
  ASSERT_TRUE(controller->actuatorNode());
  ASSERT_TRUE(controller->sensorNode());
  ASSERT_TRUE(coolingCoil.waterInletModelObject());
  EXPECT_EQ(coolingCoil.waterInletModelObject()->handle(), controller->actuatorNode()->handle());
  EXPECT_EQ(coolingCoil.airOutletModelObject()->handle(), controller->sensorNode()->handle());

  auto controllerList = airLoop.getModelObjectTarget<AirLoopHVACControllerList>(openstudio::AirLoopHVACFields::ControllerListName);
  ASSERT_TRUE(controllerList);
  const auto controllers = controllerList->controllers();
  EXPECT_TRUE(std::ranges::any_of(controllers, [&](const auto& object) { return object.handle() == controller->handle(); }));
}

TEST_F(EPModelFixture, CoilSystemCoolingWaterHeatExchangerAssisted_AdjacentInsertionKeepsBoundaryAligned) {
  Model model;
  AirLoopHVAC airLoop(model);
  CoilSystemCoolingWaterHeatExchangerAssisted coilSystem(model);
  ASSERT_TRUE(coilSystem.setName("Adjacent Assisted Water System"));

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(coilSystem.addToNode(supplyOutletNode));
  ASSERT_TRUE(coilSystem.inletModelObject());
  auto originalInlet = coilSystem.inletModelObject()->cast<Node>();

  FanSystemModel fan(model);
  ASSERT_TRUE(fan.addToNode(originalInlet));
  ASSERT_TRUE(fan.outletModelObject());
  ASSERT_TRUE(coilSystem.inletModelObject());
  EXPECT_EQ(fan.outletModelObject()->handle(), coilSystem.inletModelObject()->handle());

  const auto storageManagers = model.getConcreteModelObjects<SetpointManagerMixedAir>();
  ASSERT_EQ(1u, storageManagers.size());
  ASSERT_TRUE(storageManagers.front().setpointNode());
  ASSERT_TRUE(storageManagers.front().referenceSetpointNode());
  ASSERT_TRUE(storageManagers.front().fanInletNode());
  ASSERT_TRUE(storageManagers.front().fanOutletNode());
  auto coolingCoil = coilSystem.coolingCoil();
  ASSERT_TRUE(coolingCoil.airOutletModelObject());
  EXPECT_EQ(coolingCoil.airOutletModelObject()->handle(), storageManagers.front().setpointNode()->handle());
  EXPECT_EQ(airLoop.supplyOutletNode().handle(), storageManagers.front().referenceSetpointNode()->handle());
  EXPECT_EQ(fan.inletModelObject()->handle(), storageManagers.front().fanInletNode()->handle());
  EXPECT_EQ(fan.outletModelObject()->handle(), storageManagers.front().fanOutletNode()->handle());

  EXPECT_FALSE(fan.remove().empty());
  ASSERT_TRUE(coilSystem.inletModelObject());
  EXPECT_EQ(originalInlet.handle(), coilSystem.inletModelObject()->handle());
  EXPECT_TRUE(model.getConcreteModelObjects<SetpointManagerMixedAir>().empty());
}

TEST_F(EPModelFixture, CoilSystemCoolingWaterHeatExchangerAssisted_DirectPathSurvivesReloadAndRemoval) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-assisted-water-direct-roundtrip.idf");

  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ASSERT_TRUE(airLoop.setName("Roundtrip Assisted Water Air Loop"));
  ASSERT_TRUE(plantLoop.setName("Roundtrip Assisted Water Plant Loop"));
  CoilSystemCoolingWaterHeatExchangerAssisted coilSystem(model);
  ASSERT_TRUE(coilSystem.setName("Roundtrip Assisted Water System"));
  auto heatExchanger = coilSystem.heatExchanger();
  ASSERT_TRUE(heatExchanger.setName("Roundtrip Assisted Water Heat Exchanger"));
  auto coolingCoil = coilSystem.coolingCoil().cast<CoilCoolingWater>();
  ASSERT_TRUE(coolingCoil.setName("Roundtrip Assisted Water Coil"));

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(coilSystem.addToNode(supplyOutletNode));
  FanSystemModel fan(model);
  ASSERT_TRUE(fan.setName("Roundtrip Assisted Water Fan"));
  ASSERT_TRUE(fan.addToNode(supplyOutletNode));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coolingCoil));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedAirLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Roundtrip Assisted Water Air Loop");
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Roundtrip Assisted Water Plant Loop");
  auto loadedSystem = loadedModel->getConcreteModelObjectByName<CoilSystemCoolingWaterHeatExchangerAssisted>("Roundtrip Assisted Water System");
  auto loadedHeatExchanger =
    loadedModel->getConcreteModelObjectByName<HeatExchangerAirToAirSensibleAndLatent>("Roundtrip Assisted Water Heat Exchanger");
  auto loadedCoolingCoil = loadedModel->getConcreteModelObjectByName<CoilCoolingWater>("Roundtrip Assisted Water Coil");
  ASSERT_TRUE(loadedAirLoop);
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedSystem);
  ASSERT_TRUE(loadedHeatExchanger);
  ASSERT_TRUE(loadedCoolingCoil);

  ASSERT_TRUE(loadedSystem->inletModelObject());
  ASSERT_TRUE(loadedSystem->outletModelObject());
  ASSERT_TRUE(loadedHeatExchanger->primaryAirOutletModelObject());
  ASSERT_TRUE(loadedHeatExchanger->secondaryAirInletModelObject());
  ASSERT_TRUE(loadedCoolingCoil->airInletModelObject());
  ASSERT_TRUE(loadedCoolingCoil->airOutletModelObject());
  EXPECT_EQ(loadedHeatExchanger->primaryAirOutletModelObject()->handle(), loadedCoolingCoil->airInletModelObject()->handle());
  EXPECT_EQ(loadedCoolingCoil->airOutletModelObject()->handle(), loadedHeatExchanger->secondaryAirInletModelObject()->handle());
  ASSERT_TRUE(loadedCoolingCoil->controllerWaterCoil());
  ASSERT_TRUE(loadedCoolingCoil->controllerWaterCoil()->sensorNode());
  EXPECT_EQ(loadedCoolingCoil->airOutletModelObject()->handle(), loadedCoolingCoil->controllerWaterCoil()->sensorNode()->handle());
  const auto loadedStorageManagers = loadedModel->getConcreteModelObjects<SetpointManagerMixedAir>();
  ASSERT_EQ(1u, loadedStorageManagers.size());
  ASSERT_TRUE(loadedStorageManagers.front().setpointNode());
  EXPECT_EQ(loadedCoolingCoil->airOutletModelObject()->handle(), loadedStorageManagers.front().setpointNode()->handle());

  const auto systemHandle = loadedSystem->handle();
  const auto heatExchangerHandle = loadedHeatExchanger->handle();
  const auto coolingCoilHandle = loadedCoolingCoil->handle();
  EXPECT_FALSE(loadedSystem->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(systemHandle));
  EXPECT_FALSE(loadedModel->getObject(heatExchangerHandle));
  EXPECT_FALSE(loadedModel->getObject(coolingCoilHandle));
  EXPECT_EQ(3u, loadedAirLoop->supplyComponents().size());
  EXPECT_EQ(5u, loadedPlantLoop->demandComponents().size());
  EXPECT_TRUE(loadedModel->getConcreteModelObjects<SetpointManagerMixedAir>().empty());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, CoilSystemCoolingWaterHeatExchangerAssisted_RejectsForeignAndCompetingChildren) {
  Model model;
  Model foreignModel;
  CoilSystemCoolingWaterHeatExchangerAssisted first(model);
  CoilSystemCoolingWaterHeatExchangerAssisted second(model);
  HeatExchangerAirToAirSensibleAndLatent foreignHeatExchanger(foreignModel);
  CoilCoolingWater foreignCoolingCoil(foreignModel);

  const auto originalHeatExchanger = second.heatExchanger();
  const auto originalCoolingCoil = second.coolingCoil();
  EXPECT_FALSE(second.setHeatExchanger(first.heatExchanger()));
  EXPECT_FALSE(second.setCoolingCoil(first.coolingCoil()));
  EXPECT_FALSE(second.setHeatExchanger(foreignHeatExchanger));
  EXPECT_FALSE(second.setCoolingCoil(foreignCoolingCoil));
  EXPECT_EQ(originalHeatExchanger.handle(), second.heatExchanger().handle());
  EXPECT_EQ(originalCoolingCoil.handle(), second.coolingCoil().handle());

  const auto beforeCount = model.getObjectsByType(CoilSystemCoolingWaterHeatExchangerAssisted::iddObjectType()).size();
  EXPECT_THROW((CoilSystemCoolingWaterHeatExchangerAssisted(model, foreignHeatExchanger)), std::invalid_argument);
  EXPECT_EQ(beforeCount, model.getObjectsByType(CoilSystemCoolingWaterHeatExchangerAssisted::iddObjectType()).size());
}

TEST_F(EPModelFixture, CoilSystemCoolingWaterHeatExchangerAssisted_CanonicalizeRepairsRequiredChildren) {
  Model model;
  AirLoopHVAC airLoop(model);
  CoilSystemCoolingWaterHeatExchangerAssisted coilSystem(model);
  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(coilSystem.addToNode(supplyOutletNode));
  const auto originalHeatExchanger = coilSystem.heatExchanger();
  const auto originalCoolingCoil = coilSystem.coolingCoil();

  ASSERT_TRUE(coilSystem.setPointer(openstudio::CoilSystem_Cooling_Water_HeatExchangerAssistedFields::HeatExchangerName, openstudio::Handle()));
  ASSERT_TRUE(coilSystem.setPointer(openstudio::CoilSystem_Cooling_Water_HeatExchangerAssistedFields::CoolingCoilName, openstudio::Handle()));
  ASSERT_TRUE(coilSystem.setString(openstudio::CoilSystem_Cooling_Water_HeatExchangerAssistedFields::HeatExchangerObjectType,
                                   "HeatExchanger:AirToAir:SensibleAndLatent"));
  ASSERT_TRUE(coilSystem.setString(openstudio::CoilSystem_Cooling_Water_HeatExchangerAssistedFields::CoolingCoilObjectType,
                                   "Coil:Cooling:Water:DetailedGeometry"));

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_NE(originalHeatExchanger.handle(), coilSystem.heatExchanger().handle());
  EXPECT_NE(originalCoolingCoil.handle(), coilSystem.coolingCoil().handle());
  EXPECT_EQ(coilSystem.heatExchanger().iddObject().name(), coilSystem.heatExchangerObjectType());
  EXPECT_EQ(coilSystem.coolingCoil().iddObject().name(), coilSystem.coolingCoilObjectType());
  ASSERT_TRUE(coilSystem.inletModelObject());
  ASSERT_TRUE(coilSystem.outletModelObject());
  ASSERT_TRUE(coilSystem.heatExchanger().primaryAirOutletModelObject());
  ASSERT_TRUE(coilSystem.heatExchanger().secondaryAirInletModelObject());
  ASSERT_TRUE(coilSystem.coolingCoil().airInletModelObject());
  ASSERT_TRUE(coilSystem.coolingCoil().airOutletModelObject());
  EXPECT_EQ(coilSystem.heatExchanger().primaryAirOutletModelObject()->handle(), coilSystem.coolingCoil().airInletModelObject()->handle());
  EXPECT_EQ(coilSystem.coolingCoil().airOutletModelObject()->handle(), coilSystem.heatExchanger().secondaryAirInletModelObject()->handle());

  const auto heatExchangerCount = model.getModelObjects<AirToAirComponent>().size();
  const auto coolingCoilCount = model.getConcreteModelObjects<CoilCoolingWater>().size();
  const auto secondReport = model.canonicalize();
  EXPECT_EQ(0u, secondReport.errorCount);
  EXPECT_EQ(heatExchangerCount, model.getModelObjects<AirToAirComponent>().size());
  EXPECT_EQ(coolingCoilCount, model.getConcreteModelObjects<CoilCoolingWater>().size());
}

TEST_F(EPModelFixture, CoilSystemCoolingWaterHeatExchangerAssisted_AirLoopCanonicalizesBeforeUsingRequiredChildren) {
  Model model;
  AirLoopHVAC airLoop(model);
  CoilSystemCoolingWaterHeatExchangerAssisted coilSystem(model);
  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(coilSystem.addToNode(supplyOutletNode));

  ASSERT_TRUE(coilSystem.setPointer(openstudio::CoilSystem_Cooling_Water_HeatExchangerAssistedFields::HeatExchangerName, openstudio::Handle()));
  ASSERT_TRUE(coilSystem.setPointer(openstudio::CoilSystem_Cooling_Water_HeatExchangerAssistedFields::CoolingCoilName, openstudio::Handle()));

  // AirLoopHVAC is deliberately visited first. It must canonicalize the
  // compound supply component before coolingCoil() consumes its required child.
  detail::LoadContext context{model, SanitizationPolicy::Repair, SanitizationReport{}, {}};
  auto airLoopImpl = airLoop.getImpl<detail::AirLoopHVAC_Impl>();
  ASSERT_TRUE(airLoopImpl);
  EXPECT_NO_THROW(airLoopImpl->canonicalize(context));

  EXPECT_EQ(0u, context.report.errorCount);
  EXPECT_TRUE(context.visited.contains(coilSystem.handle()));
  EXPECT_NO_THROW(coilSystem.coolingCoil());
}

TEST_F(EPModelFixture, CoilSystemCoolingWaterHeatExchangerAssisted_InternalNodeRenamesSurviveCanonicalize) {
  Model model;
  AirLoopHVAC airLoop(model);
  CoilSystemCoolingWaterHeatExchangerAssisted coilSystem(model);
  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(coilSystem.addToNode(supplyOutletNode));
  auto heatExchanger = coilSystem.heatExchanger();
  auto coolingCoil = coilSystem.coolingCoil();
  auto firstConnector = heatExchanger.primaryAirOutletModelObject()->cast<Node>();
  auto secondConnector = coolingCoil.airOutletModelObject()->cast<Node>();
  ASSERT_TRUE(firstConnector.setName("Renamed Assisted Water First Connector"));
  ASSERT_TRUE(secondConnector.setName("Renamed Assisted Water Second Connector"));

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  ASSERT_TRUE(heatExchanger.primaryAirOutletModelObject());
  ASSERT_TRUE(coolingCoil.airInletModelObject());
  ASSERT_TRUE(coolingCoil.airOutletModelObject());
  ASSERT_TRUE(heatExchanger.secondaryAirInletModelObject());
  EXPECT_EQ(firstConnector.handle(), heatExchanger.primaryAirOutletModelObject()->handle());
  EXPECT_EQ(firstConnector.handle(), coolingCoil.airInletModelObject()->handle());
  EXPECT_EQ(secondConnector.handle(), coolingCoil.airOutletModelObject()->handle());
  EXPECT_EQ(secondConnector.handle(), heatExchanger.secondaryAirInletModelObject()->handle());
  EXPECT_EQ("Renamed Assisted Water First Connector", firstConnector.nameString());
  EXPECT_EQ("Renamed Assisted Water Second Connector", secondConnector.nameString());
}
