/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/AirLoopHVAC_Impl.hpp"
#include "../ModelObject/AirLoopHVACDedicatedOutdoorAirSystem.hpp"
#include "../ModelObject/AirLoopHVACDedicatedOutdoorAirSystem_Impl.hpp"
#include "../ModelObject/AirLoopHVACMixer.hpp"
#include "../ModelObject/AirLoopHVACMixer_Impl.hpp"
#include "../ModelObject/AirLoopHVACSplitter.hpp"
#include "../ModelObject/AirLoopHVACSplitter_Impl.hpp"
#include "../ModelObject/AirLoopHVACControllerList.hpp"
#include "../ModelObject/AirLoopHVACControllerList_Impl.hpp"
#include "../ModelObject/AirLoopHVACOutdoorAirSystemEquipmentList.hpp"
#include "../ModelObject/AirLoopHVACOutdoorAirSystemEquipmentList_Impl.hpp"
#include "../ModelObject/OutdoorAirMixer.hpp"
#include "../ModelObject/OutdoorAirMixer_Impl.hpp"
#include "../ModelObject/ControllerMechanicalVentilation.hpp"
#include "../ModelObject/ControllerMechanicalVentilation_Impl.hpp"
#include "../ParentObject/ControllerOutdoorAir.hpp"
#include "../ParentObject/ControllerOutdoorAir_Impl.hpp"
#include "../Schedule/Schedule.hpp"
#include "../StraightComponent/FanSystemModel.hpp"
#include "../StraightComponent/FanSystemModel_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToAirComponent/CoilCoolingWater.hpp"
#include "../WaterToAirComponent/CoilCoolingWater_Impl.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"
#include "../WaterToAirComponent/CoilHeatingWater_Impl.hpp"
#include "../HVACComponent/ControllerWaterCoil.hpp"
#include "../HVACComponent/ControllerWaterCoil_Impl.hpp"
#include "../Loop/PlantLoop.hpp"
#include <utilities/idd/AirLoopHVAC_DedicatedOutdoorAirSystem_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_Mixer_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_OutdoorAirSystem_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_OutdoorAirSystem_EquipmentList_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_Splitter_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_ControllerList_FieldEnums.hxx>
#include <utilities/idd/Controller_OutdoorAir_FieldEnums.hxx>
#include <utilities/idd/Fan_SystemModel_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>
#include <utilities/idf/IdfFile.hpp>

#include <stdexcept>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirLoopHVACDedicatedOutdoorAirSystem_DefaultConstructor) {
  Model model;
  AirLoopHVACDedicatedOutdoorAirSystem doas(model);
  EXPECT_EQ(AirLoopHVACDedicatedOutdoorAirSystem::iddObjectType(), doas.iddObject().type());
  EXPECT_DOUBLE_EQ(4.5, doas.preheatDesignTemperature());
  EXPECT_DOUBLE_EQ(0.004, doas.preheatDesignHumidityRatio());
  EXPECT_DOUBLE_EQ(17.5, doas.precoolDesignTemperature());
  EXPECT_DOUBLE_EQ(0.012, doas.precoolDesignHumidityRatio());
}

TEST_F(EPModelFixture, AirLoopHVACDedicatedOutdoorAirSystem_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACDedicatedOutdoorAirSystem doas(model);

  EXPECT_TRUE(doas.setPreheatDesignTemperature(5.2));
  EXPECT_TRUE(doas.setPreheatDesignHumidityRatio(0.0052));
  EXPECT_TRUE(doas.setPrecoolDesignTemperature(18.1));
  EXPECT_TRUE(doas.setPrecoolDesignHumidityRatio(0.0111));

  EXPECT_DOUBLE_EQ(5.2, doas.preheatDesignTemperature());
  EXPECT_DOUBLE_EQ(0.0052, doas.preheatDesignHumidityRatio());
  EXPECT_DOUBLE_EQ(18.1, doas.precoolDesignTemperature());
  EXPECT_DOUBLE_EQ(0.0111, doas.precoolDesignHumidityRatio());
}

TEST_F(EPModelFixture, AirLoopHVACDedicatedOutdoorAirSystem_OutdoorAirSystemConstructor) {
  Model model;
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  AirLoopHVACDedicatedOutdoorAirSystem doas(oaSystem);

  EXPECT_EQ(oaSystem, doas.airLoopHVACOutdoorAirSystem());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), doas.availabilitySchedule());
  ASSERT_TRUE(oaSystem.airLoopHVACDedicatedOutdoorAirSystem());
  EXPECT_EQ(doas, *oaSystem.airLoopHVACDedicatedOutdoorAirSystem());
  EXPECT_EQ(1u, model.getConcreteModelObjects<AirLoopHVACMixer>().size());
  EXPECT_EQ(1u, model.getConcreteModelObjects<AirLoopHVACSplitter>().size());
}

TEST_F(EPModelFixture, AirLoopHVACDedicatedOutdoorAirSystem_ProjectsOnlyDedicatedEquipmentToEnergyPlus) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-doas-equipment-projection.idf");
  Model model;
  AirLoopHVACOutdoorAirSystem dedicatedOA(model);
  AirLoopHVACDedicatedOutdoorAirSystem doas(dedicatedOA);

  auto equipmentList = dedicatedOA.getModelObjectTarget<AirLoopHVACOutdoorAirSystemEquipmentList>(
    openstudio::AirLoopHVAC_OutdoorAirSystemFields::OutdoorAirEquipmentListName);
  auto controllerLists = model.getConcreteModelObjects<AirLoopHVACControllerList>();
  ASSERT_TRUE(equipmentList);
  ASSERT_EQ(1u, controllerLists.size());
  auto controllerList = controllerLists.front();
  EXPECT_TRUE(equipmentList->extensibleGroups().empty());
  EXPECT_EQ(1u, controllerList.extensibleGroups().size());
  EXPECT_TRUE(controllerList.getImpl<detail::AirLoopHVACControllerList_Impl>()->isTransient());
  EXPECT_FALSE(dedicatedOA.getTarget(openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName));

  const auto conceptualMixers = model.getConcreteModelObjects<OutdoorAirMixer>();
  const auto conceptualControllers = model.getConcreteModelObjects<ControllerOutdoorAir>();
  ASSERT_EQ(1u, conceptualMixers.size());
  ASSERT_EQ(1u, conceptualControllers.size());
  EXPECT_TRUE(conceptualMixers.front().getImpl<detail::OutdoorAirMixer_Impl>()->isTransient());
  EXPECT_TRUE(conceptualControllers.front().getImpl<detail::ControllerOutdoorAir_Impl>()->isTransient());
  EXPECT_EQ(conceptualControllers.front(), dedicatedOA.getControllerOutdoorAir());
  ASSERT_TRUE(dedicatedOA.getControllerOutdoorAir().airLoopHVACOutdoorAirSystem());
  EXPECT_EQ(dedicatedOA, *dedicatedOA.getControllerOutdoorAir().airLoopHVACOutdoorAirSystem());
  ControllerOutdoorAir unrelatedController(model);
  auto dedicatedOutdoorNode = dedicatedOA.outdoorAirModelObject();
  ASSERT_TRUE(dedicatedOutdoorNode);
  ASSERT_TRUE(unrelatedController.setPointer(openstudio::Controller_OutdoorAirFields::ActuatorNodeName, dedicatedOutdoorNode->handle()));
  EXPECT_FALSE(unrelatedController.airLoopHVACOutdoorAirSystem());
  unrelatedController.remove();
  auto mechanicalVentilation = dedicatedOA.getControllerOutdoorAir().controllerMechanicalVentilation();
  EXPECT_TRUE(mechanicalVentilation.getImpl<detail::ControllerMechanicalVentilation_Impl>()->isTransient());

  FanSystemModel fan(model);
  auto outboardNode = dedicatedOA.outboardOANode();
  ASSERT_TRUE(outboardNode);
  ASSERT_TRUE(fan.addToNode(*outboardNode));
  ASSERT_EQ(1u, equipmentList->extensibleGroups().size());
  auto equipmentGroup = equipmentList->extensibleGroups().front().cast<openstudio::WorkspaceExtensibleGroup>();
  EXPECT_EQ("Fan:SystemModel",
            equipmentGroup.getString(openstudio::AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields::ComponentObjectType).get());
  EXPECT_EQ(fan,
            equipmentGroup.getTarget(openstudio::AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields::ComponentName)->cast<FanSystemModel>());

  auto splitter = model.getConcreteModelObjects<AirLoopHVACSplitter>().front();
  auto splitterInlet = splitter.getModelObjectTarget<Node>(openstudio::AirLoopHVAC_SplitterFields::InletNodeName);
  auto fanOutlet = fan.outletModelObject();
  ASSERT_TRUE(splitterInlet);
  ASSERT_TRUE(fanOutlet);
  EXPECT_EQ(*splitterInlet, fanOutlet->cast<Node>());
  auto liveController = dedicatedOA.getControllerOutdoorAir();
  auto liveActuator = liveController.getModelObjectTarget<Node>(openstudio::Controller_OutdoorAirFields::ActuatorNodeName);
  ASSERT_TRUE(liveActuator);
  EXPECT_EQ(fanOutlet->cast<Node>(), *liveActuator);
  ASSERT_TRUE(liveController.airLoopHVACOutdoorAirSystem());
  EXPECT_EQ(dedicatedOA, *liveController.airLoopHVACOutdoorAirSystem());

  FanSystemModel secondFan(model);
  ASSERT_TRUE(secondFan.addToNode(*liveActuator));
  ASSERT_EQ(2u, dedicatedOA.oaComponents(openstudio::IddObjectType::Fan_SystemModel).size());
  EXPECT_EQ(liveController, dedicatedOA.getControllerOutdoorAir());
  auto secondFanOutlet = secondFan.outletModelObject();
  auto secondActuator = liveController.getModelObjectTarget<Node>(openstudio::Controller_OutdoorAirFields::ActuatorNodeName);
  ASSERT_TRUE(secondFanOutlet);
  ASSERT_TRUE(secondActuator);
  EXPECT_EQ(secondFanOutlet->cast<Node>(), *secondActuator);
  ASSERT_TRUE(liveController.airLoopHVACOutdoorAirSystem());
  EXPECT_EQ(dedicatedOA, *liveController.airLoopHVACOutdoorAirSystem());
  ASSERT_TRUE(secondFan.removeFromLoop());
  EXPECT_EQ(1u, dedicatedOA.oaComponents(openstudio::IddObjectType::Fan_SystemModel).size());
  EXPECT_EQ(liveController, dedicatedOA.getControllerOutdoorAir());
  auto restoredActuator = liveController.getModelObjectTarget<Node>(openstudio::Controller_OutdoorAirFields::ActuatorNodeName);
  auto restoredFanOutlet = fan.outletModelObject();
  auto restoredSplitterInlet = splitter.getModelObjectTarget<Node>(openstudio::AirLoopHVAC_SplitterFields::InletNodeName);
  ASSERT_TRUE(restoredActuator);
  ASSERT_TRUE(restoredFanOutlet);
  ASSERT_TRUE(restoredSplitterInlet);
  EXPECT_EQ(restoredFanOutlet->cast<Node>(), *restoredActuator);
  EXPECT_EQ(*restoredSplitterInlet, *restoredActuator);
  ASSERT_TRUE(liveController.airLoopHVACOutdoorAirSystem());
  EXPECT_EQ(dedicatedOA, *liveController.airLoopHVACOutdoorAirSystem());

  auto serialized = model.toIdfFile();
  EXPECT_TRUE(serialized.getObjectsByType(openstudio::IddObjectType::OutdoorAir_Mixer).empty());
  EXPECT_TRUE(serialized.getObjectsByType(openstudio::IddObjectType::Controller_OutdoorAir).empty());
  EXPECT_TRUE(serialized.getObjectsByType(openstudio::IddObjectType::Controller_MechanicalVentilation).empty());
  EXPECT_TRUE(serialized.getObjectsByType(openstudio::IddObjectType::AirLoopHVAC_ControllerList).empty());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedDOAS = loadedModel->getConcreteModelObjects<AirLoopHVACDedicatedOutdoorAirSystem>();
  ASSERT_EQ(1u, loadedDOAS.size());
  auto loadedOA = loadedDOAS.front().airLoopHVACOutdoorAirSystem();
  EXPECT_EQ(1u, loadedOA.oaComponents(openstudio::IddObjectType::Fan_SystemModel).size());
  EXPECT_TRUE(loadedOA.getControllerOutdoorAir().getImpl<detail::ControllerOutdoorAir_Impl>()->isTransient());
  ASSERT_TRUE(loadedOA.getControllerOutdoorAir().airLoopHVACOutdoorAirSystem());
  EXPECT_EQ(loadedOA, *loadedOA.getControllerOutdoorAir().airLoopHVACOutdoorAirSystem());
  EXPECT_EQ(1u, loadedModel->getConcreteModelObjects<OutdoorAirMixer>().size());
  EXPECT_TRUE(loadedModel->getConcreteModelObjects<OutdoorAirMixer>().front().getImpl<detail::OutdoorAirMixer_Impl>()->isTransient());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, AirLoopHVACDedicatedOutdoorAirSystem_ReplacesProjectedOutdoorAirController) {
  Model model;
  AirLoopHVACOutdoorAirSystem dedicatedOA(model);
  AirLoopHVACDedicatedOutdoorAirSystem doas(dedicatedOA);
  auto oldController = dedicatedOA.getControllerOutdoorAir();
  auto oldMechanicalVentilation = oldController.controllerMechanicalVentilation();
  const auto oldControllerHandle = oldController.handle();
  const auto oldMechanicalVentilationHandle = oldMechanicalVentilation.handle();

  ControllerOutdoorAir replacement(model);
  auto replacementMechanicalVentilation = replacement.controllerMechanicalVentilation();
  EXPECT_FALSE(replacement.getImpl<detail::ControllerOutdoorAir_Impl>()->isTransient());
  EXPECT_FALSE(replacementMechanicalVentilation.getImpl<detail::ControllerMechanicalVentilation_Impl>()->isTransient());

  ASSERT_TRUE(dedicatedOA.setControllerOutdoorAir(replacement));
  EXPECT_EQ(replacement, dedicatedOA.getControllerOutdoorAir());
  EXPECT_TRUE(replacement.getImpl<detail::ControllerOutdoorAir_Impl>()->isTransient());
  EXPECT_TRUE(replacementMechanicalVentilation.getImpl<detail::ControllerMechanicalVentilation_Impl>()->isTransient());
  ASSERT_TRUE(replacement.airLoopHVACOutdoorAirSystem());
  EXPECT_EQ(dedicatedOA, *replacement.airLoopHVACOutdoorAirSystem());
  EXPECT_FALSE(model.getObject(oldControllerHandle));
  EXPECT_FALSE(model.getObject(oldMechanicalVentilationHandle));

  auto serialized = model.toIdfFile();
  EXPECT_TRUE(serialized.getObjectsByType(openstudio::IddObjectType::Controller_OutdoorAir).empty());
  EXPECT_TRUE(serialized.getObjectsByType(openstudio::IddObjectType::Controller_MechanicalVentilation).empty());
}

TEST_F(EPModelFixture, AirLoopHVACDedicatedOutdoorAirSystem_ProjectsWaterCoilControllers) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-doas-water-coil-projection.idf");
  Model model;
  AirLoopHVACOutdoorAirSystem dedicatedOA(model);
  AirLoopHVACDedicatedOutdoorAirSystem doas(dedicatedOA);
  CoilCoolingWater coolingCoil(model);
  CoilHeatingWater heatingCoil(model);
  ASSERT_TRUE(coolingCoil.setName("Dedicated Cooling Coil"));
  ASSERT_TRUE(heatingCoil.setName("Dedicated Heating Coil"));

  auto outdoorNode = dedicatedOA.outboardOANode();
  ASSERT_TRUE(outdoorNode);
  ASSERT_TRUE(coolingCoil.addToNode(*outdoorNode));
  outdoorNode = dedicatedOA.outboardOANode();
  ASSERT_TRUE(outdoorNode);
  ASSERT_TRUE(heatingCoil.addToNode(*outdoorNode));
  EXPECT_FALSE(coolingCoil.controllerWaterCoil());
  EXPECT_FALSE(heatingCoil.controllerWaterCoil());
  EXPECT_FALSE(dedicatedOA.getTarget(openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName));

  PlantLoop chilledWaterLoop(model);
  PlantLoop hotWaterLoop(model);
  ASSERT_TRUE(chilledWaterLoop.addDemandBranchForComponent(coolingCoil));
  ASSERT_TRUE(hotWaterLoop.addDemandBranchForComponent(heatingCoil));
  auto coolingController = coolingCoil.controllerWaterCoil();
  auto heatingController = heatingCoil.controllerWaterCoil();
  ASSERT_TRUE(coolingController);
  ASSERT_TRUE(heatingController);

  auto controllerList =
    dedicatedOA.getModelObjectTarget<AirLoopHVACControllerList>(openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName);
  ASSERT_TRUE(controllerList);
  EXPECT_FALSE(controllerList->getImpl<detail::AirLoopHVACControllerList_Impl>()->isTransient());
  ASSERT_EQ(2u, controllerList->controllers().size());
  EXPECT_EQ(*heatingController, controllerList->controllers()[0]);
  EXPECT_EQ(*coolingController, controllerList->controllers()[1]);
  EXPECT_FALSE(controllerList->optionalControllerOutdoorAir());
  EXPECT_TRUE(dedicatedOA.getControllerOutdoorAir().getImpl<detail::ControllerOutdoorAir_Impl>()->isTransient());
  ASSERT_TRUE(dedicatedOA.getControllerOutdoorAir().airLoopHVACOutdoorAirSystem());
  EXPECT_EQ(dedicatedOA, *dedicatedOA.getControllerOutdoorAir().airLoopHVACOutdoorAirSystem());

  ASSERT_TRUE(doas.setAirLoopHVACOutdoorAirSystem(dedicatedOA));
  auto idempotentControllerList =
    dedicatedOA.getModelObjectTarget<AirLoopHVACControllerList>(openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName);
  ASSERT_TRUE(idempotentControllerList);
  EXPECT_EQ(*controllerList, *idempotentControllerList);
  EXPECT_EQ(2u, model.getConcreteModelObjects<AirLoopHVACControllerList>().size());
  EXPECT_EQ(1u, model.toIdfFile().getObjectsByType(openstudio::IddObjectType::AirLoopHVAC_ControllerList).size());

  auto serialized = model.toIdfFile();
  EXPECT_EQ(1u, serialized.getObjectsByType(openstudio::IddObjectType::AirLoopHVAC_ControllerList).size());
  EXPECT_EQ(2u, serialized.getObjectsByType(openstudio::IddObjectType::Controller_WaterCoil).size());
  EXPECT_TRUE(serialized.getObjectsByType(openstudio::IddObjectType::Controller_OutdoorAir).empty());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedDOAS = loadedModel->getConcreteModelObjects<AirLoopHVACDedicatedOutdoorAirSystem>();
  ASSERT_EQ(1u, loadedDOAS.size());
  auto loadedOA = loadedDOAS.front().airLoopHVACOutdoorAirSystem();
  auto loadedControllerList =
    loadedOA.getModelObjectTarget<AirLoopHVACControllerList>(openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName);
  ASSERT_TRUE(loadedControllerList);
  EXPECT_EQ(2u, loadedControllerList->controllers().size());
  EXPECT_FALSE(loadedControllerList->optionalControllerOutdoorAir());
  EXPECT_TRUE(loadedOA.getControllerOutdoorAir().getImpl<detail::ControllerOutdoorAir_Impl>()->isTransient());
  const auto loadedControllerLists = loadedModel->getConcreteModelObjects<AirLoopHVACControllerList>();
  ASSERT_EQ(2u, loadedControllerLists.size());
  const auto transientControllerList = std::ranges::find_if(
    loadedControllerLists, [](const auto& list) { return list.template getImpl<detail::AirLoopHVACControllerList_Impl>()->isTransient(); });
  ASSERT_NE(loadedControllerLists.end(), transientControllerList);
  ASSERT_EQ(1u, transientControllerList->controllers().size());
  EXPECT_TRUE(transientControllerList->optionalControllerOutdoorAir());
  ASSERT_TRUE(loadedOA.getControllerOutdoorAir().airLoopHVACOutdoorAirSystem());
  EXPECT_EQ(loadedOA, *loadedOA.getControllerOutdoorAir().airLoopHVACOutdoorAirSystem());
  auto loadedCoolingCoil = loadedModel->getConcreteModelObjectByName<CoilCoolingWater>("Dedicated Cooling Coil");
  auto loadedHeatingCoil = loadedModel->getConcreteModelObjectByName<CoilHeatingWater>("Dedicated Heating Coil");
  ASSERT_TRUE(loadedCoolingCoil);
  ASSERT_TRUE(loadedHeatingCoil);
  EXPECT_TRUE(loadedCoolingCoil->controllerWaterCoil());
  EXPECT_TRUE(loadedHeatingCoil->controllerWaterCoil());

  EXPECT_FALSE(loadedHeatingCoil->remove().empty());
  EXPECT_EQ(1u, loadedOA.oaComponents(openstudio::IddObjectType::Coil_Cooling_Water).size());
  EXPECT_TRUE(loadedOA.oaComponents(openstudio::IddObjectType::Coil_Heating_Water).empty());
  loadedControllerList = loadedOA.getModelObjectTarget<AirLoopHVACControllerList>(openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName);
  ASSERT_TRUE(loadedControllerList);
  ASSERT_EQ(1u, loadedControllerList->controllers().size());
  EXPECT_EQ(*loadedCoolingCoil->controllerWaterCoil(), loadedControllerList->controllers().front());

  EXPECT_FALSE(loadedDOAS.front().remove().empty());
  EXPECT_FALSE(loadedOA.airLoopHVACDedicatedOutdoorAirSystem());
  auto restoredControllerList =
    loadedOA.getModelObjectTarget<AirLoopHVACControllerList>(openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName);
  ASSERT_TRUE(restoredControllerList);
  EXPECT_FALSE(restoredControllerList->getImpl<detail::AirLoopHVACControllerList_Impl>()->isTransient());
  EXPECT_TRUE(restoredControllerList->optionalControllerOutdoorAir());
  ASSERT_EQ(2u, restoredControllerList->controllers().size());
  EXPECT_TRUE(loadedOA.getControllerOutdoorAir().airLoopHVACOutdoorAirSystem());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, AirLoopHVACOutdoorAirSystem_ProjectsWaterCoilControllerWithOutdoorAirController) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  CoilCoolingWater coolingCoil(model);
  PlantLoop chilledWaterLoop(model);

  auto supplyOutlet = airLoop.supplyOutletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyOutlet));
  auto outdoorNode = oaSystem.outboardOANode();
  ASSERT_TRUE(outdoorNode);
  ASSERT_TRUE(coolingCoil.addToNode(*outdoorNode));
  ASSERT_TRUE(chilledWaterLoop.addDemandBranchForComponent(coolingCoil));
  auto waterController = coolingCoil.controllerWaterCoil();
  ASSERT_TRUE(waterController);

  auto controllerList = oaSystem.getModelObjectTarget<AirLoopHVACControllerList>(openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName);
  ASSERT_TRUE(controllerList);
  ASSERT_EQ(2u, controllerList->controllers().size());
  EXPECT_EQ(oaSystem.getControllerOutdoorAir(), controllerList->controllers()[0]);
  EXPECT_EQ(*waterController, controllerList->controllers()[1]);

  auto serialized = model.toIdfFile();
  EXPECT_EQ(1u, serialized.getObjectsByType(openstudio::IddObjectType::Controller_OutdoorAir).size());
  EXPECT_EQ(1u, serialized.getObjectsByType(openstudio::IddObjectType::Controller_WaterCoil).size());
}

TEST_F(EPModelFixture, AirLoopHVACDedicatedOutdoorAirSystem_ProjectsReliefStreamWaterCoilController) {
  Model model;
  AirLoopHVACOutdoorAirSystem dedicatedOA(model);
  AirLoopHVACDedicatedOutdoorAirSystem doas(dedicatedOA);
  CoilHeatingWater heatingCoil(model);
  PlantLoop hotWaterLoop(model);

  auto reliefNode = dedicatedOA.outboardReliefNode();
  ASSERT_TRUE(reliefNode);
  ASSERT_TRUE(heatingCoil.addToNode(*reliefNode));
  ASSERT_TRUE(hotWaterLoop.addDemandBranchForComponent(heatingCoil));
  auto waterController = heatingCoil.controllerWaterCoil();
  ASSERT_TRUE(waterController);

  auto controllerList =
    dedicatedOA.getModelObjectTarget<AirLoopHVACControllerList>(openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName);
  ASSERT_TRUE(controllerList);
  ASSERT_EQ(1u, controllerList->controllers().size());
  EXPECT_EQ(*waterController, controllerList->controllers().front());
  EXPECT_FALSE(controllerList->optionalControllerOutdoorAir());
}

TEST_F(EPModelFixture, AirLoopHVACDedicatedOutdoorAirSystem_PreservesWaterCoilControllerAcrossMove) {
  Model model;
  AirLoopHVACOutdoorAirSystem firstOA(model);
  AirLoopHVACOutdoorAirSystem secondOA(model);
  AirLoopHVACDedicatedOutdoorAirSystem firstDOAS(firstOA);
  AirLoopHVACDedicatedOutdoorAirSystem secondDOAS(secondOA);
  CoilCoolingWater coolingCoil(model);
  PlantLoop chilledWaterLoop(model);

  auto firstOutdoorNode = firstOA.outboardOANode();
  ASSERT_TRUE(firstOutdoorNode);
  ASSERT_TRUE(coolingCoil.addToNode(*firstOutdoorNode));
  ASSERT_TRUE(chilledWaterLoop.addDemandBranchForComponent(coolingCoil));
  auto originalController = coolingCoil.controllerWaterCoil();
  ASSERT_TRUE(originalController);

  ASSERT_TRUE(coolingCoil.removeFromAirLoopHVAC());
  ASSERT_TRUE(coolingCoil.controllerWaterCoil());
  EXPECT_EQ(*originalController, *coolingCoil.controllerWaterCoil());
  EXPECT_FALSE(firstOA.getTarget(openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName));

  auto secondOutdoorNode = secondOA.outboardOANode();
  ASSERT_TRUE(secondOutdoorNode);
  ASSERT_TRUE(coolingCoil.addToNode(*secondOutdoorNode));
  ASSERT_TRUE(coolingCoil.controllerWaterCoil());
  EXPECT_EQ(*originalController, *coolingCoil.controllerWaterCoil());
  EXPECT_EQ(1u, model.getConcreteModelObjects<ControllerWaterCoil>().size());
  auto secondControllerList =
    secondOA.getModelObjectTarget<AirLoopHVACControllerList>(openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName);
  ASSERT_TRUE(secondControllerList);
  ASSERT_EQ(1u, secondControllerList->controllers().size());
  EXPECT_EQ(*originalController, secondControllerList->controllers().front());
}

TEST_F(EPModelFixture, AirLoopHVACDedicatedOutdoorAirSystem_RejectsSharedMechanicalVentilationController) {
  Model model;
  AirLoopHVACOutdoorAirSystem ordinaryOA(model);
  auto ordinaryController = ordinaryOA.getControllerOutdoorAir();
  auto ordinaryMechanicalVentilation = ordinaryController.controllerMechanicalVentilation();
  EXPECT_FALSE(ordinaryMechanicalVentilation.getImpl<detail::ControllerMechanicalVentilation_Impl>()->isTransient());
  AirLoopHVACOutdoorAirSystem secondOrdinaryOA(model);
  auto secondOrdinaryController = secondOrdinaryOA.getControllerOutdoorAir();
  ASSERT_TRUE(secondOrdinaryController.setControllerMechanicalVentilation(ordinaryMechanicalVentilation));
  EXPECT_EQ(ordinaryMechanicalVentilation, secondOrdinaryController.controllerMechanicalVentilation());

  AirLoopHVACOutdoorAirSystem dedicatedOA(model);
  AirLoopHVACDedicatedOutdoorAirSystem doas(dedicatedOA);
  auto dedicatedController = dedicatedOA.getControllerOutdoorAir();
  auto dedicatedMechanicalVentilation = dedicatedController.controllerMechanicalVentilation();
  ASSERT_NE(ordinaryMechanicalVentilation, dedicatedMechanicalVentilation);
  EXPECT_FALSE(dedicatedController.setControllerMechanicalVentilation(ordinaryMechanicalVentilation));
  EXPECT_EQ(dedicatedMechanicalVentilation, dedicatedController.controllerMechanicalVentilation());
  EXPECT_FALSE(ordinaryMechanicalVentilation.getImpl<detail::ControllerMechanicalVentilation_Impl>()->isTransient());
  ASSERT_TRUE(ordinaryController.airLoopHVACOutdoorAirSystem());
  EXPECT_EQ(ordinaryOA, *ordinaryController.airLoopHVACOutdoorAirSystem());
}

TEST_F(EPModelFixture, AirLoopHVACDedicatedOutdoorAirSystem_RejectsSharedOutdoorAirControllerWithoutMutation) {
  Model model;
  AirLoopHVACOutdoorAirSystem firstOA(model);
  AirLoopHVACOutdoorAirSystem secondOA(model);
  auto sharedController = firstOA.getControllerOutdoorAir();
  ASSERT_TRUE(secondOA.setControllerOutdoorAir(sharedController));

  AirLoopHVACDedicatedOutdoorAirSystem doas(model);
  EXPECT_FALSE(doas.setAirLoopHVACOutdoorAirSystem(firstOA));
  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACMixer>().empty());
  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACSplitter>().empty());
  EXPECT_EQ(sharedController, firstOA.getControllerOutdoorAir());
  EXPECT_EQ(sharedController, secondOA.getControllerOutdoorAir());
  EXPECT_FALSE(sharedController.getImpl<detail::ControllerOutdoorAir_Impl>()->isTransient());
  EXPECT_TRUE(firstOA.getTarget(openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName));
  EXPECT_TRUE(secondOA.getTarget(openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName));
}

TEST_F(EPModelFixture, AirLoopHVACDedicatedOutdoorAirSystem_CanonicalizeClonesSharedOutdoorAirController) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-doas-shared-controller-load.idf");
  Model model;
  AirLoopHVACOutdoorAirSystem dedicatedOA(model);
  AirLoopHVACOutdoorAirSystem ordinaryOA(model);
  auto sharedController = ordinaryOA.getControllerOutdoorAir();
  AirLoopHVACDedicatedOutdoorAirSystem doas(dedicatedOA);

  AirLoopHVACControllerList importedList(model);
  importedList.setName("Imported Shared Dedicated Controllers");
  ASSERT_TRUE(importedList.getImpl<detail::AirLoopHVACControllerList_Impl>()->setControllerOutdoorAir(sharedController));
  ASSERT_TRUE(dedicatedOA.setPointer(openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName, importedList.handle()));
  ASSERT_TRUE(model.toIdfFile().save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedDOAS = loadedModel->getConcreteModelObjects<AirLoopHVACDedicatedOutdoorAirSystem>();
  ASSERT_EQ(1u, loadedDOAS.size());
  auto loadedDedicatedOA = loadedDOAS.front().airLoopHVACOutdoorAirSystem();
  auto loadedOrdinaryOA = loadedModel->getConcreteModelObjectByName<AirLoopHVACOutdoorAirSystem>(ordinaryOA.nameString());
  ASSERT_TRUE(loadedOrdinaryOA);

  auto projectedController = loadedDedicatedOA.getControllerOutdoorAir();
  auto ordinaryController = loadedOrdinaryOA->getControllerOutdoorAir();
  EXPECT_NE(ordinaryController, projectedController);
  EXPECT_NE(ordinaryController.controllerMechanicalVentilation(), projectedController.controllerMechanicalVentilation());
  EXPECT_FALSE(ordinaryController.getImpl<detail::ControllerOutdoorAir_Impl>()->isTransient());
  EXPECT_TRUE(projectedController.getImpl<detail::ControllerOutdoorAir_Impl>()->isTransient());
  ASSERT_TRUE(ordinaryController.airLoopHVACOutdoorAirSystem());
  EXPECT_EQ(*loadedOrdinaryOA, *ordinaryController.airLoopHVACOutdoorAirSystem());

  auto serialized = loadedModel->toIdfFile();
  EXPECT_EQ(1u, serialized.getObjectsByType(openstudio::IddObjectType::Controller_OutdoorAir).size());
  EXPECT_EQ(ordinaryController.nameString(), serialized.getObjectsByType(openstudio::IddObjectType::Controller_OutdoorAir).front().nameString());
  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, AirLoopHVACDedicatedOutdoorAirSystem_ConstructorRejectsOwnedOutdoorAirSystemWithoutResidue) {
  Model model;
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  AirLoopHVACDedicatedOutdoorAirSystem doas(oaSystem);

  EXPECT_THROW({ AirLoopHVACDedicatedOutdoorAirSystem duplicate(oaSystem); }, std::runtime_error);
  EXPECT_EQ(1u, model.getConcreteModelObjects<AirLoopHVACDedicatedOutdoorAirSystem>().size());
  EXPECT_EQ(1u, model.getConcreteModelObjects<AirLoopHVACMixer>().size());
  EXPECT_EQ(1u, model.getConcreteModelObjects<AirLoopHVACSplitter>().size());
  ASSERT_TRUE(oaSystem.airLoopHVACDedicatedOutdoorAirSystem());
  EXPECT_EQ(doas, *oaSystem.airLoopHVACDedicatedOutdoorAirSystem());
}

TEST_F(EPModelFixture, AirLoopHVACDedicatedOutdoorAirSystem_RejectsOutdoorAirSystemInstalledOnAirLoopWithoutResidue) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem attachedOA(model);
  auto supplyInlet = airLoop.supplyInletNode();
  ASSERT_TRUE(attachedOA.addToNode(supplyInlet));
  auto originalController = attachedOA.getControllerOutdoorAir();
  auto equipmentList = attachedOA.getModelObjectTarget<AirLoopHVACOutdoorAirSystemEquipmentList>(
    openstudio::AirLoopHVAC_OutdoorAirSystemFields::OutdoorAirEquipmentListName);
  ASSERT_TRUE(equipmentList);
  auto originalEquipment = equipmentList->equipment();

  EXPECT_THROW({ AirLoopHVACDedicatedOutdoorAirSystem rejected(attachedOA); }, std::runtime_error);
  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACDedicatedOutdoorAirSystem>().empty());
  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACMixer>().empty());
  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACSplitter>().empty());
  ASSERT_TRUE(attachedOA.airLoopHVAC());
  EXPECT_EQ(airLoop, *attachedOA.airLoopHVAC());
  EXPECT_FALSE(attachedOA.airLoopHVACDedicatedOutdoorAirSystem());
  EXPECT_EQ(originalController, attachedOA.getControllerOutdoorAir());
  EXPECT_EQ(originalEquipment, equipmentList->equipment());
  EXPECT_FALSE(originalController.getImpl<detail::ControllerOutdoorAir_Impl>()->isTransient());
}

TEST_F(EPModelFixture, AirLoopHVACDedicatedOutdoorAirSystem_MembershipKeepsEnergyPlusRowsAligned) {
  Model model;
  AirLoopHVACOutdoorAirSystem dedicatedOA(model);
  AirLoopHVACDedicatedOutdoorAirSystem doas(dedicatedOA);
  AirLoopHVAC firstLoop(model);
  AirLoopHVAC secondLoop(model);
  AirLoopHVACOutdoorAirSystem firstOA(model);
  AirLoopHVACOutdoorAirSystem secondOA(model);
  auto firstSupplyOutlet = firstLoop.supplyOutletNode();
  auto secondSupplyOutlet = secondLoop.supplyOutletNode();
  ASSERT_TRUE(firstOA.addToNode(firstSupplyOutlet));
  ASSERT_TRUE(secondOA.addToNode(secondSupplyOutlet));

  ASSERT_TRUE(doas.addAirLoop(firstLoop));
  ASSERT_TRUE(doas.addAirLoop(secondLoop));
  EXPECT_TRUE(doas.addAirLoop(firstLoop));
  EXPECT_EQ(2u, doas.numberofAirLoops());
  ASSERT_TRUE(doas.airLoopIndex(firstLoop));
  ASSERT_TRUE(doas.airLoopIndex(secondLoop));
  EXPECT_EQ(1u, *doas.airLoopIndex(firstLoop));
  EXPECT_EQ(2u, *doas.airLoopIndex(secondLoop));
  ASSERT_EQ(2u, doas.airLoops().size());
  EXPECT_EQ(firstLoop, doas.airLoops()[0]);
  EXPECT_EQ(secondLoop, doas.airLoops()[1]);
  ASSERT_TRUE(firstLoop.airLoopHVACDedicatedOutdoorAirSystem());
  EXPECT_EQ(doas, *firstLoop.airLoopHVACDedicatedOutdoorAirSystem());

  const auto mixers = model.getConcreteModelObjects<AirLoopHVACMixer>();
  const auto splitters = model.getConcreteModelObjects<AirLoopHVACSplitter>();
  ASSERT_EQ(1u, mixers.size());
  ASSERT_EQ(1u, splitters.size());
  EXPECT_EQ(2u, mixers.front().numExtensibleGroups());
  EXPECT_EQ(2u, splitters.front().numExtensibleGroups());
  EXPECT_EQ(2, doas.getInt(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::NumberofAirLoopHVAC).get());

  auto firstMixerGroup = mixers.front().extensibleGroups()[0].cast<openstudio::WorkspaceExtensibleGroup>();
  auto firstSplitterGroup = splitters.front().extensibleGroups()[0].cast<openstudio::WorkspaceExtensibleGroup>();
  ASSERT_TRUE(firstMixerGroup.getTarget(openstudio::AirLoopHVAC_MixerExtensibleFields::InletNodeName));
  ASSERT_TRUE(firstSplitterGroup.getTarget(openstudio::AirLoopHVAC_SplitterExtensibleFields::OutletNodeName));
  EXPECT_EQ(*firstOA.outboardReliefNode(), firstMixerGroup.getTarget(openstudio::AirLoopHVAC_MixerExtensibleFields::InletNodeName)->cast<Node>());
  EXPECT_EQ(*firstOA.outboardOANode(), firstSplitterGroup.getTarget(openstudio::AirLoopHVAC_SplitterExtensibleFields::OutletNodeName)->cast<Node>());

  EXPECT_TRUE(doas.removeAirLoop(1u));
  EXPECT_EQ(1u, doas.numberofAirLoops());
  ASSERT_TRUE(doas.airLoopIndex(secondLoop));
  EXPECT_EQ(1u, *doas.airLoopIndex(secondLoop));
  EXPECT_EQ(1u, mixers.front().numExtensibleGroups());
  EXPECT_EQ(1u, splitters.front().numExtensibleGroups());
  EXPECT_FALSE(firstLoop.airLoopHVACDedicatedOutdoorAirSystem());

  doas.removeAllAirLoops();
  EXPECT_EQ(0u, doas.numberofAirLoops());
  EXPECT_EQ(0u, mixers.front().numExtensibleGroups());
  EXPECT_EQ(0u, splitters.front().numExtensibleGroups());
}

TEST_F(EPModelFixture, AirLoopHVACDedicatedOutdoorAirSystem_RejectsInvalidOwnershipWithoutMutation) {
  Model model;
  AirLoopHVACOutdoorAirSystem dedicatedOA1(model);
  AirLoopHVACOutdoorAirSystem dedicatedOA2(model);
  AirLoopHVACDedicatedOutdoorAirSystem firstDOAS(dedicatedOA1);
  AirLoopHVACDedicatedOutdoorAirSystem secondDOAS(dedicatedOA2);
  AirLoopHVAC servedLoop(model);
  AirLoopHVACOutdoorAirSystem servedOA(model);
  auto supplyOutlet = servedLoop.supplyOutletNode();
  ASSERT_TRUE(servedOA.addToNode(supplyOutlet));
  ASSERT_TRUE(firstDOAS.addAirLoop(servedLoop));

  EXPECT_FALSE(secondDOAS.addAirLoop(servedLoop));
  EXPECT_EQ(0u, secondDOAS.numberofAirLoops());
  EXPECT_FALSE(secondDOAS.setAirLoopHVACOutdoorAirSystem(dedicatedOA1));
  EXPECT_EQ(dedicatedOA2, secondDOAS.airLoopHVACOutdoorAirSystem());
  ASSERT_TRUE(servedLoop.airLoopHVACDedicatedOutdoorAirSystem());
  EXPECT_EQ(firstDOAS, *servedLoop.airLoopHVACDedicatedOutdoorAirSystem());

  AirLoopHVAC loopWithoutOA(model);
  EXPECT_FALSE(secondDOAS.addAirLoop(loopWithoutOA));
  EXPECT_EQ(0u, secondDOAS.numberofAirLoops());
}

TEST_F(EPModelFixture, AirLoopHVACDedicatedOutdoorAirSystem_ChangingOutdoorAirSystemRestoresTheOldProjection) {
  Model model;
  AirLoopHVACOutdoorAirSystem firstOA(model);
  AirLoopHVACOutdoorAirSystem secondOA(model);
  AirLoopHVACDedicatedOutdoorAirSystem doas(firstOA);

  EXPECT_FALSE(firstOA.getTarget(openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName));
  ASSERT_TRUE(doas.setAirLoopHVACOutdoorAirSystem(secondOA));
  EXPECT_EQ(secondOA, doas.airLoopHVACOutdoorAirSystem());
  EXPECT_FALSE(secondOA.getTarget(openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName));

  auto restoredControllerList =
    firstOA.getModelObjectTarget<AirLoopHVACControllerList>(openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName);
  ASSERT_TRUE(restoredControllerList);
  EXPECT_FALSE(restoredControllerList->getImpl<detail::AirLoopHVACControllerList_Impl>()->isTransient());
  EXPECT_FALSE(firstOA.getControllerOutdoorAir().getImpl<detail::ControllerOutdoorAir_Impl>()->isTransient());
  EXPECT_TRUE(secondOA.getControllerOutdoorAir().getImpl<detail::ControllerOutdoorAir_Impl>()->isTransient());
}

TEST_F(EPModelFixture, AirLoopHVACDedicatedOutdoorAirSystem_BatchAdditionIsAllOrNothing) {
  Model model;
  AirLoopHVACOutdoorAirSystem dedicatedOA(model);
  AirLoopHVACDedicatedOutdoorAirSystem doas(dedicatedOA);
  AirLoopHVAC validLoop(model);
  AirLoopHVAC invalidLoop(model);
  AirLoopHVACOutdoorAirSystem validOA(model);
  auto supplyOutlet = validLoop.supplyOutletNode();
  ASSERT_TRUE(validOA.addToNode(supplyOutlet));

  EXPECT_FALSE(doas.addAirLoops({validLoop, invalidLoop}));
  EXPECT_EQ(0u, doas.numberofAirLoops());
  EXPECT_FALSE(validLoop.airLoopHVACDedicatedOutdoorAirSystem());
}

TEST_F(EPModelFixture, AirLoopHVACDedicatedOutdoorAirSystem_MalformedRowsRejectAdditionWithoutMutation) {
  Model model;
  AirLoopHVACOutdoorAirSystem dedicatedOA(model);
  AirLoopHVACDedicatedOutdoorAirSystem doas(dedicatedOA);
  AirLoopHVAC firstLoop(model);
  AirLoopHVAC secondLoop(model);
  AirLoopHVACOutdoorAirSystem firstOA(model);
  AirLoopHVACOutdoorAirSystem secondOA(model);
  auto firstSupplyOutlet = firstLoop.supplyOutletNode();
  auto secondSupplyOutlet = secondLoop.supplyOutletNode();
  ASSERT_TRUE(firstOA.addToNode(firstSupplyOutlet));
  ASSERT_TRUE(secondOA.addToNode(secondSupplyOutlet));
  ASSERT_TRUE(doas.addAirLoop(firstLoop));

  auto mixer = model.getConcreteModelObjects<AirLoopHVACMixer>().front();
  auto splitter = model.getConcreteModelObjects<AirLoopHVACSplitter>().front();
  auto splitterInlet = splitter.getTarget(openstudio::AirLoopHVAC_SplitterFields::InletNodeName);
  ASSERT_TRUE(splitterInlet);
  splitter.clearExtensibleGroups();

  EXPECT_FALSE(doas.addAirLoop(secondLoop));
  EXPECT_EQ(1u, doas.numberofAirLoops());
  EXPECT_EQ(1u, mixer.numExtensibleGroups());
  EXPECT_EQ(0u, splitter.numExtensibleGroups());
  ASSERT_TRUE(splitter.getTarget(openstudio::AirLoopHVAC_SplitterFields::InletNodeName));
  EXPECT_EQ(splitterInlet->handle(), splitter.getTarget(openstudio::AirLoopHVAC_SplitterFields::InletNodeName)->handle());
  EXPECT_FALSE(secondLoop.airLoopHVACDedicatedOutdoorAirSystem());
}

TEST_F(EPModelFixture, AirLoopHVACDedicatedOutdoorAirSystem_ServedLoopRemovalCompactsAlignedRows) {
  Model model;
  AirLoopHVACOutdoorAirSystem dedicatedOA(model);
  AirLoopHVACDedicatedOutdoorAirSystem doas(dedicatedOA);
  AirLoopHVAC firstLoop(model);
  AirLoopHVAC secondLoop(model);
  AirLoopHVACOutdoorAirSystem firstOA(model);
  AirLoopHVACOutdoorAirSystem secondOA(model);
  auto firstSupplyOutlet = firstLoop.supplyOutletNode();
  auto secondSupplyOutlet = secondLoop.supplyOutletNode();
  ASSERT_TRUE(firstOA.addToNode(firstSupplyOutlet));
  ASSERT_TRUE(secondOA.addToNode(secondSupplyOutlet));
  ASSERT_TRUE(doas.addAirLoops({firstLoop, secondLoop}));

  EXPECT_FALSE(firstLoop.remove().empty());
  EXPECT_EQ(1u, doas.numberofAirLoops());
  ASSERT_TRUE(doas.airLoopIndex(secondLoop));
  EXPECT_EQ(1u, *doas.airLoopIndex(secondLoop));
  EXPECT_EQ(1u, model.getConcreteModelObjects<AirLoopHVACMixer>().front().numExtensibleGroups());
  EXPECT_EQ(1u, model.getConcreteModelObjects<AirLoopHVACSplitter>().front().numExtensibleGroups());
}

TEST_F(EPModelFixture, AirLoopHVACDedicatedOutdoorAirSystem_AmbiguousMembershipRefusesServedLoopRemoval) {
  Model model;
  AirLoopHVACOutdoorAirSystem dedicatedOA1(model);
  AirLoopHVACOutdoorAirSystem dedicatedOA2(model);
  AirLoopHVACDedicatedOutdoorAirSystem firstDOAS(dedicatedOA1);
  AirLoopHVACDedicatedOutdoorAirSystem secondDOAS(dedicatedOA2);
  AirLoopHVAC servedLoop(model);
  AirLoopHVACOutdoorAirSystem servedOA(model);
  auto supplyOutlet = servedLoop.supplyOutletNode();
  ASSERT_TRUE(servedOA.addToNode(supplyOutlet));
  ASSERT_TRUE(firstDOAS.addAirLoop(servedLoop));

  // Bypass the public ownership guard to model malformed imported storage.
  auto secondGroup = secondDOAS.pushExtensibleGroup().cast<openstudio::WorkspaceExtensibleGroup>();
  ASSERT_TRUE(secondGroup.setPointer(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields::AirLoopHVACName, servedLoop.handle()));
  auto secondMixer = model.getConcreteModelObjectByName<AirLoopHVACMixer>(secondDOAS.nameString() + " Mixer");
  auto secondSplitter = model.getConcreteModelObjectByName<AirLoopHVACSplitter>(secondDOAS.nameString() + " Splitter");
  ASSERT_TRUE(secondMixer);
  ASSERT_TRUE(secondSplitter);
  auto secondMixerGroup = secondMixer->pushExtensibleGroup().cast<openstudio::WorkspaceExtensibleGroup>();
  auto secondSplitterGroup = secondSplitter->pushExtensibleGroup().cast<openstudio::WorkspaceExtensibleGroup>();
  ASSERT_TRUE(
    secondMixerGroup.setPointer(openstudio::AirLoopHVAC_MixerExtensibleFields::InletNodeName, servedOA.outboardReliefNode()->handle(), false));
  ASSERT_TRUE(
    secondSplitterGroup.setPointer(openstudio::AirLoopHVAC_SplitterExtensibleFields::OutletNodeName, servedOA.outboardOANode()->handle(), false));

  EXPECT_TRUE(servedLoop.remove().empty());
  EXPECT_TRUE(model.getObject(servedLoop.handle()));
  EXPECT_EQ(1u, firstDOAS.numberofAirLoops());
  EXPECT_EQ(1u, secondDOAS.numberofAirLoops());
}

TEST_F(EPModelFixture, AirLoopHVACDedicatedOutdoorAirSystem_RemoveCleansOwnedConnectors) {
  Model model;
  AirLoopHVACOutdoorAirSystem dedicatedOA(model);
  AirLoopHVACDedicatedOutdoorAirSystem doas(dedicatedOA);
  AirLoopHVAC servedLoop(model);
  AirLoopHVACOutdoorAirSystem servedOA(model);
  auto supplyOutlet = servedLoop.supplyOutletNode();
  ASSERT_TRUE(servedOA.addToNode(supplyOutlet));
  ASSERT_TRUE(doas.addAirLoop(servedLoop));

  auto mixerOutlet = model.getConcreteModelObjects<AirLoopHVACMixer>().front().getTarget(openstudio::AirLoopHVAC_MixerFields::OutletNodeName);
  ASSERT_TRUE(mixerOutlet);

  EXPECT_FALSE(doas.remove().empty());
  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACDedicatedOutdoorAirSystem>().empty());
  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACMixer>().empty());
  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACSplitter>().empty());
  EXPECT_FALSE(dedicatedOA.airLoopHVACDedicatedOutdoorAirSystem());
  EXPECT_FALSE(servedLoop.airLoopHVACDedicatedOutdoorAirSystem());
  EXPECT_FALSE(model.getObject(mixerOutlet->handle()));
  EXPECT_EQ(2u, model.getConcreteModelObjects<AirLoopHVACOutdoorAirSystem>().size());

  auto restoredControllerList =
    dedicatedOA.getModelObjectTarget<AirLoopHVACControllerList>(openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName);
  ASSERT_TRUE(restoredControllerList);
  EXPECT_FALSE(restoredControllerList->getImpl<detail::AirLoopHVACControllerList_Impl>()->isTransient());
  EXPECT_FALSE(dedicatedOA.getControllerOutdoorAir().getImpl<detail::ControllerOutdoorAir_Impl>()->isTransient());
  auto restoredMixers = model.getConcreteModelObjects<OutdoorAirMixer>();
  ASSERT_EQ(2u, restoredMixers.size());
  EXPECT_TRUE(
    std::ranges::none_of(restoredMixers, [](const OutdoorAirMixer& mixer) { return mixer.getImpl<detail::OutdoorAirMixer_Impl>()->isTransient(); }));
}

TEST_F(EPModelFixture, AirLoopHVACDedicatedOutdoorAirSystem_RemovePreservesSharedConnectors) {
  Model model;
  AirLoopHVACOutdoorAirSystem firstOA(model);
  AirLoopHVACOutdoorAirSystem secondOA(model);
  AirLoopHVACDedicatedOutdoorAirSystem firstDOAS(firstOA);
  AirLoopHVACDedicatedOutdoorAirSystem secondDOAS(secondOA);

  auto firstMixer = firstDOAS.getTarget(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::AirLoopHVAC_MixerName);
  auto firstSplitter = firstDOAS.getTarget(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::AirLoopHVAC_SplitterName);
  ASSERT_TRUE(firstMixer);
  ASSERT_TRUE(firstSplitter);

  // Bypass the public ownership rules to model imported storage in which two
  // DOAS objects share connector objects.
  ASSERT_TRUE(secondDOAS.setPointer(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::AirLoopHVAC_MixerName, firstMixer->handle()));
  ASSERT_TRUE(secondDOAS.setPointer(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::AirLoopHVAC_SplitterName, firstSplitter->handle()));

  EXPECT_FALSE(firstDOAS.remove().empty());
  ASSERT_TRUE(model.getObject(firstMixer->handle()));
  ASSERT_TRUE(model.getObject(firstSplitter->handle()));
  ASSERT_TRUE(secondDOAS.getTarget(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::AirLoopHVAC_MixerName));
  ASSERT_TRUE(secondDOAS.getTarget(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::AirLoopHVAC_SplitterName));
  EXPECT_EQ(firstMixer->handle(), secondDOAS.getTarget(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::AirLoopHVAC_MixerName)->handle());
  EXPECT_EQ(firstSplitter->handle(),
            secondDOAS.getTarget(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::AirLoopHVAC_SplitterName)->handle());
}

TEST_F(EPModelFixture, AirLoopHVACDedicatedOutdoorAirSystem_MembershipSurvivesReload) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-doas-membership-roundtrip.idf");
  Model model;
  AirLoopHVACOutdoorAirSystem dedicatedOA(model);
  AirLoopHVACDedicatedOutdoorAirSystem doas(dedicatedOA);
  AirLoopHVAC servedLoop(model);
  AirLoopHVACOutdoorAirSystem servedOA(model);
  ASSERT_TRUE(doas.setName("Roundtrip DOAS"));
  ASSERT_TRUE(servedLoop.setName("Roundtrip Served Air Loop"));
  auto supplyOutlet = servedLoop.supplyOutletNode();
  ASSERT_TRUE(servedOA.addToNode(supplyOutlet));
  ASSERT_TRUE(doas.addAirLoop(servedLoop));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedDOAS = loadedModel->getConcreteModelObjectByName<AirLoopHVACDedicatedOutdoorAirSystem>("Roundtrip DOAS");
  auto loadedLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Roundtrip Served Air Loop");
  ASSERT_TRUE(loadedDOAS);
  ASSERT_TRUE(loadedLoop);
  EXPECT_EQ(1u, loadedDOAS->numberofAirLoops());
  ASSERT_TRUE(loadedDOAS->airLoopIndex(*loadedLoop));
  ASSERT_TRUE(loadedLoop->airLoopHVACDedicatedOutdoorAirSystem());
  EXPECT_EQ(*loadedDOAS, *loadedLoop->airLoopHVACDedicatedOutdoorAirSystem());

  auto loadedServedOA = loadedLoop->airLoopHVACOutdoorAirSystem();
  ASSERT_TRUE(loadedServedOA);
  auto loadedMixers = loadedModel->getConcreteModelObjects<AirLoopHVACMixer>();
  auto loadedSplitters = loadedModel->getConcreteModelObjects<AirLoopHVACSplitter>();
  ASSERT_EQ(1u, loadedMixers.size());
  ASSERT_EQ(1u, loadedSplitters.size());
  auto loadedMixer = loadedMixers.front();
  auto loadedSplitter = loadedSplitters.front();
  ASSERT_EQ(1u, loadedMixer.numExtensibleGroups());
  ASSERT_EQ(1u, loadedSplitter.numExtensibleGroups());
  auto loadedMixerGroup = loadedMixer.extensibleGroups()[0].cast<openstudio::WorkspaceExtensibleGroup>();
  auto loadedSplitterGroup = loadedSplitter.extensibleGroups()[0].cast<openstudio::WorkspaceExtensibleGroup>();
  ASSERT_TRUE(loadedMixerGroup.getTarget(openstudio::AirLoopHVAC_MixerExtensibleFields::InletNodeName));
  ASSERT_TRUE(loadedSplitterGroup.getTarget(openstudio::AirLoopHVAC_SplitterExtensibleFields::OutletNodeName));
  EXPECT_EQ(*loadedServedOA->outboardReliefNode(),
            loadedMixerGroup.getTarget(openstudio::AirLoopHVAC_MixerExtensibleFields::InletNodeName)->cast<Node>());
  EXPECT_EQ(*loadedServedOA->outboardOANode(),
            loadedSplitterGroup.getTarget(openstudio::AirLoopHVAC_SplitterExtensibleFields::OutletNodeName)->cast<Node>());

  EXPECT_TRUE(loadedDOAS->removeAirLoop(*loadedLoop));
  EXPECT_EQ(0u, loadedDOAS->numberofAirLoops());
  EXPECT_TRUE(loadedDOAS->addAirLoop(*loadedLoop));
}
