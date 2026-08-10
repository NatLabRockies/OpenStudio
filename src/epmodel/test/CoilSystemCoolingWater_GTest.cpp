/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ControllerWaterCoil.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../AirToAirComponent/HeatExchangerAirToAirSensibleAndLatent.hpp"
#include "../AirToAirComponent/HeatExchangerAirToAirSensibleAndLatent_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/AirLoopHVAC_Impl.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../WaterToAirComponent/CoilCoolingWater.hpp"
#include "../WaterToAirComponent/CoilCoolingWater_Impl.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/CoilSystemCoolingWater.hpp"
#include "../StraightComponent/CoilSystemCoolingWater_Impl.hpp"
#include "../StraightComponent/CoilSystemCoolingWaterHeatExchangerAssisted.hpp"
#include "../StraightComponent/CoilSystemCoolingWaterHeatExchangerAssisted_Impl.hpp"
#include <utilities/idd/CoilSystem_Cooling_Water_FieldEnums.hxx>
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilSystemCoolingWater_DefaultConstructor) {
  Model model;
  CoilSystemCoolingWater coilSystem(model);
  EXPECT_EQ(CoilSystemCoolingWater::iddObjectType(), coilSystem.iddObject().type());
  EXPECT_FALSE(coilSystem.nameString().empty());

  EXPECT_EQ("None", coilSystem.dehumidificationControlType());
  EXPECT_TRUE(coilSystem.runonSensibleLoad());
  EXPECT_FALSE(coilSystem.runonLatentLoad());
  EXPECT_DOUBLE_EQ(0.0, coilSystem.minimumAirToWaterTemperatureOffset());
  EXPECT_TRUE(coilSystem.economizerLockout());
  EXPECT_DOUBLE_EQ(0.0, coilSystem.minimumWaterLoopTemperatureForHeatRecovery());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), coilSystem.availabilitySchedule().handle());
  EXPECT_EQ("Coil:Cooling:Water", coilSystem.coolingCoil().iddObject().name());
}

TEST_F(EPModelFixture, CoilSystemCoolingWater_ScalarAccessors_RoundTrip) {
  Model model;
  CoilSystemCoolingWater coilSystem(model);

  const auto dehumidificationControlTypes = CoilSystemCoolingWater::dehumidificationControlTypeValues();
  EXPECT_FALSE(dehumidificationControlTypes.empty());
  EXPECT_TRUE(std::find(dehumidificationControlTypes.begin(), dehumidificationControlTypes.end(), "CoolReheat")
              != dehumidificationControlTypes.end());

  EXPECT_TRUE(coilSystem.setDehumidificationControlType("CoolReheat"));
  EXPECT_EQ("CoolReheat", coilSystem.dehumidificationControlType());
  EXPECT_FALSE(coilSystem.setDehumidificationControlType("Invalid Dehumidification Control Type"));

  EXPECT_TRUE(coilSystem.setRunonSensibleLoad(false));
  EXPECT_FALSE(coilSystem.runonSensibleLoad());

  EXPECT_TRUE(coilSystem.setRunonLatentLoad(true));
  EXPECT_TRUE(coilSystem.runonLatentLoad());

  EXPECT_TRUE(coilSystem.setMinimumAirToWaterTemperatureOffset(1.0));
  EXPECT_DOUBLE_EQ(1.0, coilSystem.minimumAirToWaterTemperatureOffset());

  EXPECT_TRUE(coilSystem.setEconomizerLockout(false));
  EXPECT_FALSE(coilSystem.economizerLockout());

  EXPECT_TRUE(coilSystem.setMinimumWaterLoopTemperatureForHeatRecovery(1.2));
  EXPECT_DOUBLE_EQ(1.2, coilSystem.minimumWaterLoopTemperatureForHeatRecovery());
}

TEST_F(EPModelFixture, CoilSystemCoolingWater_RelationshipAccessors_RoundTrip) {
  Model model;
  CoilSystemCoolingWater coilSystem(model);
  ScheduleConstant availabilitySchedule(model);
  CoilSystemCoolingWaterHeatExchangerAssisted heatExchangerAssisted(model);
  CoilCoolingWater companionCoil(model);
  CoilSystemCoolingWaterHeatExchangerAssisted invalidCompanion(model);

  EXPECT_TRUE(coilSystem.setAvailabilitySchedule(availabilitySchedule));
  EXPECT_EQ(availabilitySchedule.handle(), coilSystem.availabilitySchedule().handle());

  EXPECT_TRUE(coilSystem.setCoolingCoil(heatExchangerAssisted));
  EXPECT_EQ(heatExchangerAssisted.handle(), coilSystem.coolingCoil().handle());

  EXPECT_TRUE(coilSystem.setCompanionCoilUsedForHeatRecovery(companionCoil));
  ASSERT_TRUE(coilSystem.companionCoilUsedForHeatRecovery());
  EXPECT_EQ(companionCoil.handle(), coilSystem.companionCoilUsedForHeatRecovery()->handle());

  EXPECT_FALSE(coilSystem.setCompanionCoilUsedForHeatRecovery(invalidCompanion));
  EXPECT_EQ(companionCoil.handle(), coilSystem.companionCoilUsedForHeatRecovery()->handle());

  coilSystem.resetCompanionCoilUsedForHeatRecovery();
  EXPECT_FALSE(coilSystem.companionCoilUsedForHeatRecovery());

  const auto children = coilSystem.children();
  ASSERT_EQ(1u, children.size());
  EXPECT_EQ(heatExchangerAssisted.handle(), children.front().handle());
}

TEST_F(EPModelFixture, CoilSystemCoolingWater_ExplicitConstructor) {
  Model model;
  CoilSystemCoolingWaterHeatExchangerAssisted heatExchangerAssisted(model);
  CoilSystemCoolingWater coilSystem(model, heatExchangerAssisted);

  EXPECT_EQ(heatExchangerAssisted.handle(), coilSystem.coolingCoil().handle());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), coilSystem.availabilitySchedule().handle());
  EXPECT_EQ("None", coilSystem.dehumidificationControlType());
}

TEST_F(EPModelFixture, CoilSystemCoolingWater_AddToNodeCurrentPaths) {
  Model model;
  AirLoopHVAC airLoop(model);
  CoilSystemCoolingWater supplyCoilSystem(model);
  CoilSystemCoolingWater outdoorAirCoilSystem(model);
  CoilSystemCoolingWater demandCoilSystem(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(supplyCoilSystem.addToNode(supplyInletNode));
  ASSERT_TRUE(supplyCoilSystem.inletModelObject());
  EXPECT_EQ(supplyInletNode, supplyCoilSystem.inletModelObject()->cast<Node>());
  EXPECT_TRUE(supplyCoilSystem.outletModelObject());

  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(demandCoilSystem.addToNode(demandInletNode));
  EXPECT_FALSE(demandCoilSystem.airLoopHVAC());

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyOutletNode));
  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);
  EXPECT_TRUE(outdoorAirCoilSystem.addToNode(*outboardOANode));
  const auto oaComponents = oaSystem.oaComponents();
  EXPECT_FALSE(oaComponents.empty());
  EXPECT_TRUE(
    std::any_of(oaComponents.begin(), oaComponents.end(), [&](const auto& object) { return object.handle() == outdoorAirCoilSystem.handle(); }));
}

TEST_F(EPModelFixture, CoilSystemCoolingWater_ContainedCoolingCoilDoesNotCreateStandaloneController) {
  Model model;
  CoilSystemCoolingWater system(model);
  CoilCoolingWater coil(model);
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);

  ASSERT_TRUE(system.setCoolingCoil(coil));

  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(system.addToNode(supplyInletNode));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coil));

  EXPECT_FALSE(coil.controllerWaterCoil());
}

TEST_F(EPModelFixture, CoilSystemCoolingWater_NestedOwnedChildRemovalLifecycle) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  CoilSystemCoolingWaterHeatExchangerAssisted assistedSystem(model);
  auto coolingCoil = assistedSystem.coolingCoil();
  auto heatExchanger = assistedSystem.heatExchanger();
  CoilSystemCoolingWater outerSystem(model, assistedSystem);

  const auto outerChildren = outerSystem.children();
  ASSERT_EQ(1u, outerChildren.size());
  EXPECT_EQ(assistedSystem, outerChildren.front());
  const auto assistedChildren = assistedSystem.children();
  ASSERT_EQ(2u, assistedChildren.size());
  EXPECT_EQ(coolingCoil, assistedChildren[0]);
  EXPECT_EQ(heatExchanger, assistedChildren[1]);

  ASSERT_TRUE(assistedSystem.containingHVACComponent());
  EXPECT_EQ(outerSystem, assistedSystem.containingHVACComponent().get());
  ASSERT_TRUE(coolingCoil.containingHVACComponent());
  EXPECT_EQ(assistedSystem, coolingCoil.containingHVACComponent().get());
  ASSERT_TRUE(heatExchanger.containingHVACComponent());
  EXPECT_EQ(assistedSystem, heatExchanger.containingHVACComponent().get());
  EXPECT_FALSE(assistedSystem.isRemovable());
  EXPECT_FALSE(coolingCoil.isRemovable());
  EXPECT_FALSE(heatExchanger.isRemovable());

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(outerSystem.addToNode(supplyOutletNode));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coolingCoil));
  EXPECT_EQ(3u, airLoop.supplyComponents().size());
  EXPECT_EQ(7u, plantLoop.demandComponents().size());

  const auto outerHandle = outerSystem.handle();
  const auto assistedHandle = assistedSystem.handle();
  const auto coolingCoilHandle = coolingCoil.handle();
  const auto heatExchangerHandle = heatExchanger.handle();

  EXPECT_FALSE(outerSystem.remove().empty());
  EXPECT_FALSE(model.getObject(outerHandle));
  EXPECT_FALSE(model.getObject(assistedHandle));
  EXPECT_FALSE(model.getObject(coolingCoilHandle));
  EXPECT_FALSE(model.getObject(heatExchangerHandle));
  EXPECT_EQ(2u, airLoop.supplyComponents().size());
  EXPECT_EQ(5u, plantLoop.demandComponents().size());
  EXPECT_FALSE(plantLoop.demandComponent(coolingCoilHandle));
}

TEST_F(EPModelFixture, CoilSystemCoolingWater_NestedAssemblySurvivesSaveLoadAndRemoval) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-nested-cooling-system-roundtrip.idf");

  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ASSERT_TRUE(airLoop.setName("Roundtrip Nested Air Loop"));
  ASSERT_TRUE(plantLoop.setName("Roundtrip Nested Plant Loop"));

  HeatExchangerAirToAirSensibleAndLatent heatExchanger(model);
  ASSERT_TRUE(heatExchanger.setName("Roundtrip Nested Heat Exchanger"));
  CoilSystemCoolingWaterHeatExchangerAssisted assistedSystem(model, heatExchanger);
  ASSERT_TRUE(assistedSystem.setName("Roundtrip Assisted Cooling System"));
  auto coolingCoil = assistedSystem.coolingCoil().cast<CoilCoolingWater>();
  ASSERT_TRUE(coolingCoil.setName("Roundtrip Nested Cooling Coil"));
  CoilSystemCoolingWater outerSystem(model, assistedSystem);
  ASSERT_TRUE(outerSystem.setName("Roundtrip Outer Cooling System"));

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(outerSystem.addToNode(supplyOutletNode));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coolingCoil));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedAirLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Roundtrip Nested Air Loop");
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Roundtrip Nested Plant Loop");
  auto loadedOuterSystem =
    loadedModel->getConcreteModelObjectByName<CoilSystemCoolingWater>("Roundtrip Outer Cooling System");
  auto loadedAssistedSystem = loadedModel->getConcreteModelObjectByName<CoilSystemCoolingWaterHeatExchangerAssisted>(
    "Roundtrip Assisted Cooling System");
  auto loadedCoolingCoil = loadedModel->getConcreteModelObjectByName<CoilCoolingWater>("Roundtrip Nested Cooling Coil");
  auto loadedHeatExchanger =
    loadedModel->getConcreteModelObjectByName<HeatExchangerAirToAirSensibleAndLatent>("Roundtrip Nested Heat Exchanger");
  ASSERT_TRUE(loadedAirLoop);
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedOuterSystem);
  ASSERT_TRUE(loadedAssistedSystem);
  ASSERT_TRUE(loadedCoolingCoil);
  ASSERT_TRUE(loadedHeatExchanger);

  EXPECT_EQ(3u, loadedAirLoop->supplyComponents().size());
  EXPECT_EQ(7u, loadedPlantLoop->demandComponents().size());
  ASSERT_TRUE(loadedOuterSystem->airLoopHVAC());
  EXPECT_EQ(loadedAirLoop->handle(), loadedOuterSystem->airLoopHVAC()->handle());
  ASSERT_TRUE(loadedCoolingCoil->plantLoop());
  EXPECT_EQ(loadedPlantLoop->handle(), loadedCoolingCoil->plantLoop()->handle());
  EXPECT_TRUE(loadedPlantLoop->demandComponent(loadedCoolingCoil->handle()));

  const auto outerChildren = loadedOuterSystem->children();
  ASSERT_EQ(1u, outerChildren.size());
  EXPECT_EQ(loadedAssistedSystem->handle(), outerChildren.front().handle());
  const auto assistedChildren = loadedAssistedSystem->children();
  ASSERT_EQ(2u, assistedChildren.size());
  EXPECT_EQ(loadedCoolingCoil->handle(), assistedChildren[0].handle());
  EXPECT_EQ(loadedHeatExchanger->handle(), assistedChildren[1].handle());
  ASSERT_TRUE(loadedAssistedSystem->containingHVACComponent());
  ASSERT_TRUE(loadedCoolingCoil->containingHVACComponent());
  ASSERT_TRUE(loadedHeatExchanger->containingHVACComponent());
  EXPECT_EQ(loadedOuterSystem->handle(), loadedAssistedSystem->containingHVACComponent()->handle());
  EXPECT_EQ(loadedAssistedSystem->handle(), loadedCoolingCoil->containingHVACComponent()->handle());
  EXPECT_EQ(loadedAssistedSystem->handle(), loadedHeatExchanger->containingHVACComponent()->handle());
  EXPECT_FALSE(loadedAssistedSystem->isRemovable());
  EXPECT_FALSE(loadedCoolingCoil->isRemovable());
  EXPECT_FALSE(loadedHeatExchanger->isRemovable());

  const auto outerHandle = loadedOuterSystem->handle();
  const auto assistedHandle = loadedAssistedSystem->handle();
  const auto coolingCoilHandle = loadedCoolingCoil->handle();
  const auto heatExchangerHandle = loadedHeatExchanger->handle();
  EXPECT_FALSE(loadedOuterSystem->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(outerHandle));
  EXPECT_FALSE(loadedModel->getObject(assistedHandle));
  EXPECT_FALSE(loadedModel->getObject(coolingCoilHandle));
  EXPECT_FALSE(loadedModel->getObject(heatExchangerHandle));
  EXPECT_EQ(2u, loadedAirLoop->supplyComponents().size());
  EXPECT_EQ(5u, loadedPlantLoop->demandComponents().size());
  EXPECT_FALSE(loadedPlantLoop->demandComponent(coolingCoilHandle));

  openstudio::filesystem::remove(idfPath);
}
