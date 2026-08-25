/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "../StraightComponent/CoilCoolingDXVariableRefrigerantFlow.hpp"
#include "../StraightComponent/CoilCoolingDXVariableRefrigerantFlow_Impl.hpp"
#include "../StraightComponent/CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl.hpp"
#include "../StraightComponent/CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl.hpp"
#include "../StraightComponent/CoilHeatingDXVariableRefrigerantFlow.hpp"
#include "../StraightComponent/CoilHeatingDXVariableRefrigerantFlow_Impl.hpp"
#include "../StraightComponent/CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl.hpp"
#include "../StraightComponent/CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/AirLoopHVAC_Impl.hpp"
#include "../ModelObject/OutdoorAirMixer.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/AirConditionerVariableRefrigerantFlow.hpp"
#include "../StraightComponent/AirConditionerVariableRefrigerantFlow_Impl.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/FanOnOff.hpp"
#include "../StraightComponent/FanOnOff_Impl.hpp"
#include "../StraightComponent/FanSystemModel.hpp"
#include "../StraightComponent/FanSystemModel_Impl.hpp"
#include "../StraightComponent/FanVariableVolume.hpp"
#include "../StraightComponent/FanVariableVolume_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow.hpp"
#include "../ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl.hpp"

#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Coil_Cooling_DX_VariableRefrigerantFlow_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_DX_VariableRefrigerantFlow_FieldEnums.hxx>
#include <utilities/idd/OutdoorAir_NodeList_FieldEnums.hxx>
#include <utilities/idd/OutdoorAir_Mixer_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_TerminalUnit_VariableRefrigerantFlow_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

using namespace openstudio::epmodel;

namespace {
unsigned outdoorAirNodeListEntryCount(const Model& model, const std::string& nodeName) {
  unsigned result = 0u;
  for (const auto& object : model.getObjectsByType(openstudio::IddObjectType::OutdoorAir_NodeList)) {
    for (const auto& group : object.extensibleGroups()) {
      auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
      if (!workspaceGroup) {
        continue;
      }
      auto listedNodeName = workspaceGroup->getString(openstudio::OutdoorAir_NodeListExtensibleFields::NodeorNodeListName);
      if (listedNodeName && openstudio::istringEqual(*listedNodeName, nodeName)) {
        ++result;
      }
    }
  }
  return result;
}
}  // namespace

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_DefaultConstructor) {
  Model model;
  ZoneHVACTerminalUnitVariableRefrigerantFlow vrf(model);

  EXPECT_FALSE(vrf.supplyAirFlowRateDuringCoolingOperation());
  EXPECT_TRUE(vrf.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_FALSE(vrf.supplyAirFlowRateWhenNoCoolingisNeeded());
  EXPECT_TRUE(vrf.isSupplyAirFlowRateWhenNoCoolingisNeededAutosized());
  EXPECT_FALSE(vrf.supplyAirFlowRateDuringHeatingOperation());
  EXPECT_TRUE(vrf.isSupplyAirFlowRateDuringHeatingOperationAutosized());
  EXPECT_FALSE(vrf.supplyAirFlowRateWhenNoHeatingisNeeded());
  EXPECT_TRUE(vrf.isSupplyAirFlowRateWhenNoHeatingisNeededAutosized());
  EXPECT_FALSE(vrf.outdoorAirFlowRateDuringCoolingOperation());
  EXPECT_TRUE(vrf.isOutdoorAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_FALSE(vrf.outdoorAirFlowRateDuringHeatingOperation());
  EXPECT_TRUE(vrf.isOutdoorAirFlowRateDuringHeatingOperationAutosized());
  EXPECT_FALSE(vrf.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_TRUE(vrf.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  EXPECT_DOUBLE_EQ(30.0, vrf.zoneTerminalUnitOnParasiticElectricEnergyUse());
  EXPECT_DOUBLE_EQ(20.0, vrf.zoneTerminalUnitOffParasiticElectricEnergyUse());
  EXPECT_DOUBLE_EQ(1.0, vrf.ratedTotalHeatingCapacitySizingRatio());
  EXPECT_TRUE(vrf.isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized());
  EXPECT_DOUBLE_EQ(21.0, vrf.maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation());
  EXPECT_FALSE(vrf.isSupplyAirFanPlacementDefaulted());
  EXPECT_EQ("DrawThrough", vrf.supplyAirFanPlacement());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), vrf.terminalUnitAvailabilityschedule());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), vrf.supplyAirFanOperatingModeSchedule());
  EXPECT_TRUE(vrf.supplyAirFan().optionalCast<FanOnOff>());
  auto coolingCoil = vrf.coolingCoil();
  auto heatingCoil = vrf.heatingCoil();
  ASSERT_TRUE(coolingCoil);
  ASSERT_TRUE(heatingCoil);
  EXPECT_TRUE(coolingCoil->optionalCast<CoilCoolingDXVariableRefrigerantFlow>());
  EXPECT_TRUE(heatingCoil->optionalCast<CoilHeatingDXVariableRefrigerantFlow>());
  EXPECT_FALSE(vrf.supplementalHeatingCoil());
  EXPECT_TRUE(vrf.outdoorAirMixer());
  ASSERT_TRUE(vrf.outdoorAirNode());
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(model, vrf.outdoorAirNode()->nameString()));
  const auto originalOutdoorAirNodeName = vrf.outdoorAirNode()->nameString();
  ASSERT_TRUE(vrf.setName("Renamed Default VRF Terminal"));
  ASSERT_TRUE(vrf.setSupplyAirFanPlacement("DrawThrough"));
  ASSERT_TRUE(vrf.outdoorAirNode());
  EXPECT_EQ(0u, outdoorAirNodeListEntryCount(model, originalOutdoorAirNodeName));
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(model, vrf.outdoorAirNode()->nameString()));
  EXPECT_NE(originalOutdoorAirNodeName, vrf.outdoorAirNode()->nameString());

  ZoneHVACTerminalUnitVariableRefrigerantFlow second(model);
  EXPECT_NE(vrf.nameString(), second.nameString());
  ASSERT_TRUE(vrf.inletNode());
  ASSERT_TRUE(second.inletNode());
  EXPECT_NE(vrf.inletNode()->handle(), second.inletNode()->handle());
  ASSERT_TRUE(vrf.coolingCoilOutletNode());
  ASSERT_TRUE(second.coolingCoilOutletNode());
  EXPECT_NE(vrf.coolingCoilOutletNode()->handle(), second.coolingCoilOutletNode()->handle());
  ASSERT_TRUE(second.outdoorAirNode());
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(model, second.outdoorAirNode()->nameString()));
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_FluidTemperatureControlConstructor) {
  Model model;
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model, true);

  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), terminal.terminalUnitAvailabilityschedule());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), terminal.supplyAirFanOperatingModeSchedule());
  EXPECT_TRUE(terminal.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_TRUE(terminal.isSupplyAirFlowRateWhenNoCoolingisNeededAutosized());
  EXPECT_TRUE(terminal.isSupplyAirFlowRateDuringHeatingOperationAutosized());
  EXPECT_TRUE(terminal.isSupplyAirFlowRateWhenNoHeatingisNeededAutosized());
  EXPECT_TRUE(terminal.isOutdoorAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_TRUE(terminal.isOutdoorAirFlowRateDuringHeatingOperationAutosized());
  EXPECT_TRUE(terminal.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  EXPECT_DOUBLE_EQ(30.0, terminal.zoneTerminalUnitOnParasiticElectricEnergyUse());
  EXPECT_DOUBLE_EQ(20.0, terminal.zoneTerminalUnitOffParasiticElectricEnergyUse());
  EXPECT_DOUBLE_EQ(1.0, terminal.ratedTotalHeatingCapacitySizingRatio());
  EXPECT_TRUE(terminal.isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized());
  EXPECT_DOUBLE_EQ(21.0, terminal.maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation());
  EXPECT_EQ("DrawThrough", terminal.supplyAirFanPlacement());
  EXPECT_TRUE(terminal.supplyAirFan().optionalCast<FanSystemModel>());
  ASSERT_TRUE(terminal.coolingCoil());
  ASSERT_TRUE(terminal.heatingCoil());
  EXPECT_TRUE(terminal.coolingCoil()->optionalCast<CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl>());
  EXPECT_TRUE(terminal.heatingCoil()->optionalCast<CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl>());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_ExplicitFluidTerminalsKeepRenamedAirPathsDistinct) {
  Model model;
  CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl firstCoolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl firstHeatingCoil(model);
  FanSystemModel firstFan(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow firstTerminal(model, firstCoolingCoil, firstHeatingCoil, firstFan);

  ASSERT_TRUE(firstTerminal.inletNode());
  ASSERT_TRUE(firstTerminal.coolingCoilOutletNode());
  ASSERT_TRUE(firstTerminal.outdoorAirMixer());
  const auto firstInletHandle = firstTerminal.inletNode()->handle();
  const auto firstCoolingOutletHandle = firstTerminal.coolingCoilOutletNode()->handle();
  const auto firstMixerHandle = firstTerminal.outdoorAirMixer()->handle();
  ASSERT_TRUE(firstTerminal.setName("Renamed Explicit FTC Terminal"));

  CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl secondCoolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl secondHeatingCoil(model);
  FanSystemModel secondFan(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow secondTerminal(model, secondCoolingCoil, secondHeatingCoil, secondFan);

  EXPECT_NE(firstTerminal.nameString(), secondTerminal.nameString());
  ASSERT_TRUE(secondTerminal.inletNode());
  ASSERT_TRUE(secondTerminal.coolingCoilOutletNode());
  ASSERT_TRUE(secondTerminal.outdoorAirMixer());
  EXPECT_NE(firstInletHandle, secondTerminal.inletNode()->handle());
  EXPECT_NE(firstCoolingOutletHandle, secondTerminal.coolingCoilOutletNode()->handle());
  EXPECT_NE(firstMixerHandle, secondTerminal.outdoorAirMixer()->handle());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_StandardChildConstructorAdoptsSuppliedObjects) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-vrf-terminal-explicit-children.idf");
  Model model;
  FanSystemModel fan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  ASSERT_TRUE(fan.setName("Supplied VRF Fan"));
  ASSERT_TRUE(coolingCoil.setName("Supplied VRF Cooling Coil"));
  ASSERT_TRUE(heatingCoil.setName("Supplied VRF Heating Coil"));

  EXPECT_EQ(1u, model.getConcreteModelObjects<FanSystemModel>().size());
  EXPECT_EQ(1u, model.getConcreteModelObjects<CoilCoolingDXVariableRefrigerantFlow>().size());
  EXPECT_EQ(1u, model.getConcreteModelObjects<CoilHeatingDXVariableRefrigerantFlow>().size());
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model, coolingCoil, heatingCoil, fan);
  ASSERT_TRUE(terminal.setName("Explicit Child VRF Terminal"));

  EXPECT_EQ(fan, terminal.supplyAirFan());
  ASSERT_TRUE(terminal.coolingCoil());
  ASSERT_TRUE(terminal.heatingCoil());
  EXPECT_EQ(coolingCoil, *terminal.coolingCoil());
  EXPECT_EQ(heatingCoil, *terminal.heatingCoil());
  EXPECT_EQ(1u, model.getConcreteModelObjects<FanSystemModel>().size());
  EXPECT_EQ(1u, model.getConcreteModelObjects<CoilCoolingDXVariableRefrigerantFlow>().size());
  EXPECT_EQ(1u, model.getConcreteModelObjects<CoilHeatingDXVariableRefrigerantFlow>().size());
  EXPECT_TRUE(model.getConcreteModelObjects<FanOnOff>().empty());
  EXPECT_EQ("DrawThrough", terminal.supplyAirFanPlacement());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), terminal.terminalUnitAvailabilityschedule());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), terminal.supplyAirFanOperatingModeSchedule());
  EXPECT_TRUE(terminal.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_TRUE(terminal.isOutdoorAirFlowRateDuringCoolingOperationAutosized());

  ThermalZone zone(model);
  AirConditionerVariableRefrigerantFlow outdoorUnit(model);
  ASSERT_TRUE(zone.setName("Explicit Child VRF Zone"));
  ASSERT_TRUE(outdoorUnit.setName("Explicit Child VRF Outdoor Unit"));
  ASSERT_TRUE(terminal.addToThermalZone(zone));
  ASSERT_TRUE(outdoorUnit.addTerminal(terminal));
  EXPECT_EQ(fan, terminal.supplyAirFan());
  EXPECT_EQ(coolingCoil, *terminal.coolingCoil());
  EXPECT_EQ(heatingCoil, *terminal.heatingCoil());
  ASSERT_TRUE(terminal.outdoorAirMixer());
  ASSERT_TRUE(terminal.outdoorAirMixer()->mixedAirNode());
  ASSERT_TRUE(coolingCoil.inletModelObject());
  ASSERT_TRUE(coolingCoil.outletModelObject());
  ASSERT_TRUE(heatingCoil.inletModelObject());
  ASSERT_TRUE(heatingCoil.outletModelObject());
  ASSERT_TRUE(fan.inletModelObject());
  ASSERT_TRUE(fan.outletModelObject());
  EXPECT_EQ(terminal.outdoorAirMixer()->mixedAirNode()->handle(), coolingCoil.inletModelObject()->handle());
  EXPECT_EQ(coolingCoil.outletModelObject()->handle(), heatingCoil.inletModelObject()->handle());
  EXPECT_EQ(heatingCoil.outletModelObject()->handle(), fan.inletModelObject()->handle());
  ASSERT_TRUE(terminal.outletNode());
  EXPECT_EQ(fan.outletModelObject()->handle(), terminal.outletNode()->handle());

  ASSERT_TRUE(model.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedTerminal = loadedModel->getConcreteModelObjectByName<ZoneHVACTerminalUnitVariableRefrigerantFlow>("Explicit Child VRF Terminal");
  auto loadedFan = loadedModel->getConcreteModelObjectByName<FanSystemModel>("Supplied VRF Fan");
  auto loadedCoolingCoil = loadedModel->getConcreteModelObjectByName<CoilCoolingDXVariableRefrigerantFlow>("Supplied VRF Cooling Coil");
  auto loadedHeatingCoil = loadedModel->getConcreteModelObjectByName<CoilHeatingDXVariableRefrigerantFlow>("Supplied VRF Heating Coil");
  ASSERT_TRUE(loadedTerminal);
  ASSERT_TRUE(loadedFan);
  ASSERT_TRUE(loadedCoolingCoil);
  ASSERT_TRUE(loadedHeatingCoil);
  EXPECT_EQ(*loadedFan, loadedTerminal->supplyAirFan());
  ASSERT_TRUE(loadedTerminal->coolingCoil());
  ASSERT_TRUE(loadedTerminal->heatingCoil());
  EXPECT_EQ(*loadedCoolingCoil, *loadedTerminal->coolingCoil());
  EXPECT_EQ(*loadedHeatingCoil, *loadedTerminal->heatingCoil());
  ASSERT_TRUE(loadedTerminal->thermalZone());
  EXPECT_EQ("Explicit Child VRF Zone", loadedTerminal->thermalZone()->nameString());
  ASSERT_TRUE(loadedTerminal->vrfSystem());
  EXPECT_EQ("Explicit Child VRF Outdoor Unit", loadedTerminal->vrfSystem()->nameString());
  EXPECT_EQ(1u, loadedModel->getConcreteModelObjects<FanSystemModel>().size());
  EXPECT_EQ(1u, loadedModel->getConcreteModelObjects<CoilCoolingDXVariableRefrigerantFlow>().size());
  EXPECT_EQ(1u, loadedModel->getConcreteModelObjects<CoilHeatingDXVariableRefrigerantFlow>().size());
  EXPECT_TRUE(loadedModel->getConcreteModelObjects<FanOnOff>().empty());
  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_StandardChildConstructorValidatesBeforeMutation) {
  Model model;
  Model foreignModel;
  FanVariableVolume invalidFan(model);
  FanSystemModel validFan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  CoilCoolingDXVariableRefrigerantFlow foreignCoolingCoil(foreignModel);

  const auto modelObjectCount = model.numObjects();
  EXPECT_ANY_THROW(ZoneHVACTerminalUnitVariableRefrigerantFlow(model, coolingCoil, heatingCoil, invalidFan));
  EXPECT_EQ(modelObjectCount, model.numObjects());
  EXPECT_TRUE(model.getObject(invalidFan.handle()));
  EXPECT_TRUE(model.getObject(coolingCoil.handle()));
  EXPECT_TRUE(model.getObject(heatingCoil.handle()));
  EXPECT_TRUE(model.getConcreteModelObjects<ZoneHVACTerminalUnitVariableRefrigerantFlow>().empty());

  EXPECT_ANY_THROW(ZoneHVACTerminalUnitVariableRefrigerantFlow(model, foreignCoolingCoil, heatingCoil, validFan));
  EXPECT_EQ(modelObjectCount, model.numObjects());
  EXPECT_TRUE(foreignModel.getObject(foreignCoolingCoil.handle()));
  EXPECT_TRUE(model.getObject(validFan.handle()));
  EXPECT_TRUE(model.getObject(heatingCoil.handle()));
  EXPECT_TRUE(model.getConcreteModelObjects<ZoneHVACTerminalUnitVariableRefrigerantFlow>().empty());

  FanOnOff onOffFan(model);
  FanConstantVolume constantVolumeFan(model);
  EXPECT_NO_THROW(ZoneHVACTerminalUnitVariableRefrigerantFlow(model, CoilCoolingDXVariableRefrigerantFlow(model),
                                                              CoilHeatingDXVariableRefrigerantFlow(model), onOffFan));
  EXPECT_NO_THROW(ZoneHVACTerminalUnitVariableRefrigerantFlow(model, CoilCoolingDXVariableRefrigerantFlow(model),
                                                              CoilHeatingDXVariableRefrigerantFlow(model), constantVolumeFan));
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_FluidChildConstructorAdoptsSuppliedObjects) {
  Model model;
  FanVariableVolume fan(model);
  CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl heatingCoil(model);
  ASSERT_TRUE(fan.setName("Supplied Fluid VRF Fan"));
  ASSERT_TRUE(coolingCoil.setName("Supplied Fluid VRF Cooling Coil"));
  ASSERT_TRUE(heatingCoil.setName("Supplied Fluid VRF Heating Coil"));

  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model, coolingCoil, heatingCoil, fan);
  auto convertedFan = terminal.supplyAirFan().optionalCast<FanSystemModel>();
  ASSERT_TRUE(convertedFan);
  EXPECT_EQ("Supplied Fluid VRF Fan FanSystemModel", convertedFan->nameString());
  ASSERT_TRUE(terminal.coolingCoil());
  ASSERT_TRUE(terminal.heatingCoil());
  EXPECT_EQ(coolingCoil, *terminal.coolingCoil());
  EXPECT_EQ(heatingCoil, *terminal.heatingCoil());
  EXPECT_EQ(1u, model.getConcreteModelObjects<FanVariableVolume>().size());
  EXPECT_EQ(1u, model.getConcreteModelObjects<CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl>().size());
  EXPECT_EQ(1u, model.getConcreteModelObjects<CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl>().size());
  EXPECT_EQ(1u, model.getConcreteModelObjects<FanSystemModel>().size());

  ThermalZone zone(model);
  ASSERT_TRUE(terminal.addToThermalZone(zone));
  ASSERT_TRUE(terminal.outdoorAirMixer());
  ASSERT_TRUE(terminal.outdoorAirMixer()->mixedAirNode());
  ASSERT_TRUE(coolingCoil.inletModelObject());
  ASSERT_TRUE(coolingCoil.outletModelObject());
  ASSERT_TRUE(heatingCoil.inletModelObject());
  ASSERT_TRUE(heatingCoil.outletModelObject());
  ASSERT_TRUE(convertedFan->inletModelObject());
  ASSERT_TRUE(convertedFan->outletModelObject());
  EXPECT_EQ(terminal.outdoorAirMixer()->mixedAirNode()->handle(), coolingCoil.inletModelObject()->handle());
  EXPECT_EQ(coolingCoil.outletModelObject()->handle(), heatingCoil.inletModelObject()->handle());
  EXPECT_EQ(heatingCoil.outletModelObject()->handle(), convertedFan->inletModelObject()->handle());
  ASSERT_TRUE(terminal.outletNode());
  EXPECT_EQ(convertedFan->outletModelObject()->handle(), terminal.outletNode()->handle());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_FluidChildConstructorValidatesBeforeMutation) {
  Model model;
  Model foreignModel;
  FanOnOff invalidFan(model);
  FanSystemModel validFan(model);
  CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl heatingCoil(model);
  CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl foreignCoolingCoil(foreignModel);
  const auto modelObjectCount = model.numObjects();

  EXPECT_ANY_THROW(ZoneHVACTerminalUnitVariableRefrigerantFlow(model, coolingCoil, heatingCoil, invalidFan));
  EXPECT_EQ(modelObjectCount, model.numObjects());
  EXPECT_TRUE(model.getObject(invalidFan.handle()));
  EXPECT_TRUE(model.getObject(coolingCoil.handle()));
  EXPECT_TRUE(model.getObject(heatingCoil.handle()));
  EXPECT_TRUE(model.getConcreteModelObjects<ZoneHVACTerminalUnitVariableRefrigerantFlow>().empty());

  EXPECT_ANY_THROW(ZoneHVACTerminalUnitVariableRefrigerantFlow(model, foreignCoolingCoil, heatingCoil, validFan));
  EXPECT_EQ(modelObjectCount, model.numObjects());
  EXPECT_TRUE(foreignModel.getObject(foreignCoolingCoil.handle()));
  EXPECT_TRUE(model.getObject(validFan.handle()));
  EXPECT_TRUE(model.getObject(heatingCoil.handle()));
  EXPECT_TRUE(model.getConcreteModelObjects<ZoneHVACTerminalUnitVariableRefrigerantFlow>().empty());

  EXPECT_NO_THROW(ZoneHVACTerminalUnitVariableRefrigerantFlow(model, CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl(model),
                                                              CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl(model), validFan));
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_LocalOutdoorAirDeclarationIsSharedSafely) {
  Model model;
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);
  ASSERT_TRUE(terminal.outdoorAirNode());
  const auto outdoorAirNode = *terminal.outdoorAirNode();
  const auto outdoorAirNodeName = outdoorAirNode.nameString();
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(model, outdoorAirNodeName));

  OutdoorAirMixer sharedMixer(model);
  ASSERT_TRUE(sharedMixer.setPointer(openstudio::OutdoorAir_MixerFields::OutdoorAirStreamNodeName, outdoorAirNode.handle()));
  EXPECT_FALSE(terminal.remove().empty());
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(model, outdoorAirNodeName));
  ASSERT_TRUE(sharedMixer.outdoorAirNode());
  EXPECT_EQ(outdoorAirNodeName, sharedMixer.outdoorAirNode()->nameString());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_PrefersImportedOutdoorAirNodeDeclaration) {
  Model model;
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);
  ASSERT_TRUE(terminal.outdoorAirNode());
  const auto outdoorAirNodeName = terminal.outdoorAirNode()->nameString();
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(model, outdoorAirNodeName));

  auto outdoorAirDeclaration = ModelObject::create(openstudio::IddObjectType::OutdoorAir_Node, model);
  ASSERT_TRUE(outdoorAirDeclaration.setName(outdoorAirNodeName));
  ASSERT_TRUE(terminal.setSupplyAirFanPlacement("BlowThrough"));
  EXPECT_EQ(0u, outdoorAirNodeListEntryCount(model, outdoorAirNodeName));
  ASSERT_EQ(1u, model.getObjectsByType(openstudio::IddObjectType::OutdoorAir_Node).size());

  EXPECT_FALSE(terminal.remove().empty());
  EXPECT_EQ(0u, outdoorAirNodeListEntryCount(model, outdoorAirNodeName));
  ASSERT_EQ(1u, model.getObjectsByType(openstudio::IddObjectType::OutdoorAir_Node).size());
  EXPECT_EQ(outdoorAirNodeName, model.getObjectsByType(openstudio::IddObjectType::OutdoorAir_Node).front().nameString());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACTerminalUnitVariableRefrigerantFlow vrf(model);

  EXPECT_TRUE(vrf.setSupplyAirFlowRateDuringCoolingOperation(0.5));
  ASSERT_TRUE(vrf.supplyAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(0.5, vrf.supplyAirFlowRateDuringCoolingOperation().get());
  EXPECT_FALSE(vrf.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  vrf.autosizeSupplyAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(vrf.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_FALSE(vrf.supplyAirFlowRateDuringCoolingOperation());

  EXPECT_TRUE(vrf.setSupplyAirFlowRateWhenNoCoolingisNeeded(0.18));
  ASSERT_TRUE(vrf.supplyAirFlowRateWhenNoCoolingisNeeded());
  EXPECT_DOUBLE_EQ(0.18, vrf.supplyAirFlowRateWhenNoCoolingisNeeded().get());
  vrf.resetSupplyAirFlowRateWhenNoCoolingisNeeded();
  EXPECT_FALSE(vrf.supplyAirFlowRateWhenNoCoolingisNeeded());
  vrf.autosizeSupplyAirFlowRateWhenNoCoolingisNeeded();
  EXPECT_TRUE(vrf.isSupplyAirFlowRateWhenNoCoolingisNeededAutosized());

  EXPECT_TRUE(vrf.setSupplyAirFlowRateDuringHeatingOperation(0.45));
  ASSERT_TRUE(vrf.supplyAirFlowRateDuringHeatingOperation());
  EXPECT_DOUBLE_EQ(0.45, vrf.supplyAirFlowRateDuringHeatingOperation().get());
  vrf.autosizeSupplyAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(vrf.isSupplyAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(vrf.setSupplyAirFlowRateWhenNoHeatingisNeeded(0.22));
  ASSERT_TRUE(vrf.supplyAirFlowRateWhenNoHeatingisNeeded());
  EXPECT_DOUBLE_EQ(0.22, vrf.supplyAirFlowRateWhenNoHeatingisNeeded().get());
  vrf.resetSupplyAirFlowRateWhenNoHeatingisNeeded();
  EXPECT_FALSE(vrf.supplyAirFlowRateWhenNoHeatingisNeeded());
  vrf.autosizeSupplyAirFlowRateWhenNoHeatingisNeeded();
  EXPECT_TRUE(vrf.isSupplyAirFlowRateWhenNoHeatingisNeededAutosized());

  EXPECT_TRUE(vrf.setOutdoorAirFlowRateDuringCoolingOperation(0.08));
  vrf.autosizeOutdoorAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(vrf.isOutdoorAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(vrf.setOutdoorAirFlowRateDuringHeatingOperation(0.03));
  vrf.autosizeOutdoorAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(vrf.isOutdoorAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(vrf.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.01));
  vrf.resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_FALSE(vrf.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded());
  vrf.autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(vrf.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(vrf.setZoneTerminalUnitOnParasiticElectricEnergyUse(0.9));
  EXPECT_DOUBLE_EQ(0.9, vrf.zoneTerminalUnitOnParasiticElectricEnergyUse());

  EXPECT_TRUE(vrf.setZoneTerminalUnitOffParasiticElectricEnergyUse(0.6));
  EXPECT_DOUBLE_EQ(0.6, vrf.zoneTerminalUnitOffParasiticElectricEnergyUse());

  EXPECT_TRUE(vrf.setRatedTotalHeatingCapacitySizingRatio(1.05));
  EXPECT_DOUBLE_EQ(1.05, vrf.ratedTotalHeatingCapacitySizingRatio());

  EXPECT_TRUE(vrf.setMaximumSupplyAirTemperaturefromSupplementalHeater(38.2));
  ASSERT_TRUE(vrf.maximumSupplyAirTemperaturefromSupplementalHeater());
  EXPECT_DOUBLE_EQ(38.2, vrf.maximumSupplyAirTemperaturefromSupplementalHeater().get());
  vrf.autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
  EXPECT_TRUE(vrf.isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized());

  EXPECT_TRUE(vrf.setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(33.3));
  EXPECT_DOUBLE_EQ(33.3, vrf.maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation());
  vrf.resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  EXPECT_TRUE(vrf.setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(25.0));
  EXPECT_DOUBLE_EQ(25.0, vrf.maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation());

  EXPECT_TRUE(vrf.setSupplyAirFanPlacement("DrawThrough"));
  EXPECT_EQ("DrawThrough", vrf.supplyAirFanPlacement());
  vrf.resetSupplyAirFanPlacement();
  EXPECT_TRUE(vrf.isSupplyAirFanPlacementDefaulted());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_TopologyAndChildren) {
  Model model;
  ThermalZone zone(model);
  FanOnOff fan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  CoilHeatingElectric supplementalHeatingCoil(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow vrf(model);

  ASSERT_TRUE(vrf.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(vrf.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(vrf.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(vrf.setSupplyAirFan(fan));
  ASSERT_TRUE(vrf.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(vrf.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(vrf.setSupplementalHeatingCoil(supplementalHeatingCoil));

  EXPECT_EQ(openstudio::ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::TerminalUnitAirInletNodeName, vrf.inletPort());
  EXPECT_EQ(openstudio::ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::TerminalUnitAirOutletNodeName, vrf.outletPort());

  ASSERT_TRUE(vrf.inletNode());
  ASSERT_TRUE(vrf.outletNode());
  ASSERT_TRUE(vrf.fanOutletNode());
  ASSERT_TRUE(vrf.coolingCoilOutletNode());
  ASSERT_TRUE(vrf.heatingCoilOutletNode());
  ASSERT_TRUE(vrf.outdoorAirMixer());
  ASSERT_TRUE(vrf.mixedAirNode());
  ASSERT_TRUE(vrf.outdoorAirNode());
  ASSERT_TRUE(vrf.reliefAirNode());

  const auto children = vrf.children();
  ASSERT_EQ(5u, children.size());
  EXPECT_EQ(fan.handle(), children[0].handle());
  EXPECT_EQ(coolingCoil.handle(), children[1].handle());
  EXPECT_EQ(heatingCoil.handle(), children[2].handle());
  EXPECT_EQ(supplementalHeatingCoil.handle(), children[3].handle());
  EXPECT_EQ(vrf.outdoorAirMixer()->handle(), children[4].handle());

  ASSERT_TRUE(fan.containingHVACComponent());
  ASSERT_TRUE(coolingCoil.containingHVACComponent());
  ASSERT_TRUE(heatingCoil.containingHVACComponent());
  ASSERT_TRUE(supplementalHeatingCoil.containingHVACComponent());
  EXPECT_EQ(vrf, fan.containingHVACComponent().get());
  EXPECT_EQ(vrf, coolingCoil.containingHVACComponent().get());
  EXPECT_EQ(vrf, heatingCoil.containingHVACComponent().get());
  EXPECT_EQ(vrf, supplementalHeatingCoil.containingHVACComponent().get());

  ASSERT_TRUE(vrf.addToThermalZone(zone));
  ASSERT_TRUE(vrf.thermalZone());
  EXPECT_EQ(zone, vrf.thermalZone().get());

  auto fanInlet = fan.inletModelObject()->optionalCast<Node>();
  auto fanOutlet = fan.outletModelObject()->optionalCast<Node>();
  auto supplementalInlet = supplementalHeatingCoil.inletModelObject()->optionalCast<Node>();
  auto supplementalOutlet = supplementalHeatingCoil.outletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(fanInlet);
  ASSERT_TRUE(fanOutlet);
  ASSERT_TRUE(supplementalInlet);
  ASSERT_TRUE(supplementalOutlet);
  auto coolingInlet = coolingCoil.getString(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::CoilAirInletNode, true);
  auto coolingOutlet = coolingCoil.getString(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::CoilAirOutletNode, true);
  auto heatingInlet = heatingCoil.getString(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::CoilAirInletNode, true);
  auto heatingOutlet = heatingCoil.getString(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::CoilAirOutletNode, true);
  ASSERT_TRUE(coolingInlet);
  ASSERT_TRUE(coolingOutlet);
  ASSERT_TRUE(heatingInlet);
  ASSERT_TRUE(heatingOutlet);

  EXPECT_EQ(*vrf.inletNode(), *vrf.outdoorAirMixer()->returnAirNode());
  EXPECT_EQ(vrf.mixedAirNode()->nameString(), *coolingInlet);
  EXPECT_EQ(*vrf.mixedAirNode(), *vrf.outdoorAirMixer()->mixedAirNode());
  EXPECT_EQ(*vrf.outdoorAirNode(), *vrf.outdoorAirMixer()->outdoorAirNode());
  EXPECT_EQ(*vrf.reliefAirNode(), *vrf.outdoorAirMixer()->reliefAirNode());
  EXPECT_EQ(vrf.coolingCoilOutletNode()->nameString(), *coolingOutlet);
  EXPECT_EQ(vrf.coolingCoilOutletNode()->nameString(), *heatingInlet);
  EXPECT_EQ(vrf.heatingCoilOutletNode()->nameString(), *heatingOutlet);
  EXPECT_EQ(*vrf.heatingCoilOutletNode(), *fanInlet);
  EXPECT_EQ(*vrf.fanOutletNode(), *fanOutlet);
  EXPECT_EQ(*vrf.fanOutletNode(), *supplementalInlet);
  EXPECT_EQ(*vrf.outletNode(), *supplementalOutlet);

  vrf.removeFromThermalZone();
  EXPECT_FALSE(vrf.thermalZone());
  EXPECT_TRUE(vrf.inletNode());
  EXPECT_TRUE(vrf.outletNode());
  EXPECT_TRUE(vrf.fanOutletNode());
  EXPECT_TRUE(vrf.coolingCoilOutletNode());
  EXPECT_TRUE(vrf.heatingCoilOutletNode());
  EXPECT_TRUE(vrf.outdoorAirMixer());
  EXPECT_TRUE(vrf.mixedAirNode());
  EXPECT_TRUE(vrf.outdoorAirNode());
  EXPECT_TRUE(vrf.reliefAirNode());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_OrdinaryZoneLifecycleSurvivesReload) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-vrf-terminal-zone-lifecycle.idf");
  Model model;
  ThermalZone firstZone(model);
  ThermalZone secondZone(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);
  AirConditionerVariableRefrigerantFlow outdoorUnit(model);
  ASSERT_TRUE(firstZone.setName("First VRF Zone"));
  ASSERT_TRUE(secondZone.setName("Second VRF Zone"));
  ASSERT_TRUE(terminal.setName("Ordinary Zone VRF Terminal"));
  ASSERT_TRUE(outdoorUnit.setName("Ordinary Zone VRF Outdoor Unit"));
  ASSERT_TRUE(outdoorUnit.addTerminal(terminal));

  ASSERT_TRUE(terminal.addToThermalZone(firstZone));
  ASSERT_TRUE(terminal.thermalZone());
  EXPECT_EQ(firstZone, *terminal.thermalZone());
  ASSERT_EQ(1u, firstZone.equipment().size());
  EXPECT_EQ(terminal, firstZone.equipment().front());
  auto firstConnections = firstZone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(firstConnections);
  ASSERT_EQ(1u, firstConnections->zoneAirInletNodes().size());
  ASSERT_EQ(1u, firstConnections->zoneAirExhaustNodes().size());
  EXPECT_EQ(*terminal.outletNode(), firstConnections->zoneAirInletNodes().front());
  EXPECT_EQ(*terminal.inletNode(), firstConnections->zoneAirExhaustNodes().front());

  ASSERT_TRUE(model.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedFirstZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("First VRF Zone");
  auto loadedSecondZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Second VRF Zone");
  auto loadedTerminal = loadedModel->getConcreteModelObjectByName<ZoneHVACTerminalUnitVariableRefrigerantFlow>("Ordinary Zone VRF Terminal");
  auto loadedOutdoorUnit = loadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Ordinary Zone VRF Outdoor Unit");
  ASSERT_TRUE(loadedFirstZone);
  ASSERT_TRUE(loadedSecondZone);
  ASSERT_TRUE(loadedTerminal);
  ASSERT_TRUE(loadedOutdoorUnit);
  ASSERT_TRUE(loadedTerminal->thermalZone());
  EXPECT_EQ(*loadedFirstZone, *loadedTerminal->thermalZone());
  ASSERT_TRUE(loadedTerminal->vrfSystem());
  EXPECT_EQ(*loadedOutdoorUnit, *loadedTerminal->vrfSystem());
  EXPECT_TRUE(loadedTerminal->supplyAirFan().optionalCast<FanOnOff>());
  ASSERT_TRUE(loadedTerminal->coolingCoil());
  ASSERT_TRUE(loadedTerminal->heatingCoil());
  EXPECT_TRUE(loadedTerminal->outdoorAirMixer());

  auto loadedFirstConnections = loadedFirstZone->getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(loadedFirstConnections);
  ASSERT_EQ(1u, loadedFirstConnections->zoneAirInletNodes().size());
  ASSERT_EQ(1u, loadedFirstConnections->zoneAirExhaustNodes().size());
  EXPECT_EQ(*loadedTerminal->outletNode(), loadedFirstConnections->zoneAirInletNodes().front());
  EXPECT_EQ(*loadedTerminal->inletNode(), loadedFirstConnections->zoneAirExhaustNodes().front());

  ASSERT_TRUE(loadedTerminal->addToThermalZone(*loadedSecondZone));
  EXPECT_TRUE(loadedFirstZone->equipment().empty());
  EXPECT_TRUE(loadedFirstConnections->zoneAirInletNodes().empty());
  EXPECT_TRUE(loadedFirstConnections->zoneAirExhaustNodes().empty());
  ASSERT_TRUE(loadedTerminal->thermalZone());
  EXPECT_EQ(*loadedSecondZone, *loadedTerminal->thermalZone());
  ASSERT_EQ(1u, loadedSecondZone->equipment().size());
  EXPECT_EQ(*loadedTerminal, loadedSecondZone->equipment().front());
  auto loadedSecondConnections = loadedSecondZone->getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(loadedSecondConnections);
  ASSERT_EQ(1u, loadedSecondConnections->zoneAirInletNodes().size());
  ASSERT_EQ(1u, loadedSecondConnections->zoneAirExhaustNodes().size());
  EXPECT_EQ(*loadedTerminal->outletNode(), loadedSecondConnections->zoneAirInletNodes().front());
  EXPECT_EQ(*loadedTerminal->inletNode(), loadedSecondConnections->zoneAirExhaustNodes().front());

  std::vector<openstudio::Handle> ownedHandles;
  for (const auto& child : loadedTerminal->children()) {
    ownedHandles.push_back(child.handle());
  }
  ASSERT_TRUE(loadedTerminal->outdoorAirNode());
  const auto localOutdoorAirNodeName = loadedTerminal->outdoorAirNode()->nameString();
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(*loadedModel, localOutdoorAirNodeName));
  ASSERT_FALSE(ownedHandles.empty());
  EXPECT_FALSE(loadedTerminal->remove().empty());
  EXPECT_TRUE(loadedSecondZone->equipment().empty());
  EXPECT_TRUE(loadedSecondConnections->zoneAirInletNodes().empty());
  EXPECT_TRUE(loadedSecondConnections->zoneAirExhaustNodes().empty());
  EXPECT_TRUE(loadedOutdoorUnit->terminals().empty());
  for (const auto& handle : ownedHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  EXPECT_EQ(0u, outdoorAirNodeListEntryCount(*loadedModel, localOutdoorAirNodeName));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_OutdoorAirMixerIsExposedWhenUsed) {
  Model model;
  FanOnOff fan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  CoilHeatingElectric supplementalHeatingCoil(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow vrf(model);

  ASSERT_TRUE(vrf.setOutdoorAirFlowRateDuringCoolingOperation(0.08));
  ASSERT_TRUE(vrf.setOutdoorAirFlowRateDuringHeatingOperation(0.03));
  ASSERT_TRUE(vrf.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.01));
  ASSERT_TRUE(vrf.setSupplyAirFan(fan));
  ASSERT_TRUE(vrf.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(vrf.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(vrf.setSupplementalHeatingCoil(supplementalHeatingCoil));

  ASSERT_TRUE(vrf.outdoorAirMixer());
  ASSERT_TRUE(vrf.mixedAirNode());
  ASSERT_TRUE(vrf.outdoorAirNode());
  ASSERT_TRUE(vrf.reliefAirNode());
  ASSERT_TRUE(vrf.outdoorAirMixer()->mixedAirNode());
  ASSERT_TRUE(vrf.outdoorAirMixer()->outdoorAirNode());
  ASSERT_TRUE(vrf.outdoorAirMixer()->reliefAirNode());
  const auto children = vrf.children();
  ASSERT_EQ(5u, children.size());
  EXPECT_EQ(vrf.outdoorAirMixer()->handle(), children.back().handle());
  EXPECT_EQ(OutdoorAirMixer::iddObjectType(), vrf.outdoorAirMixer()->iddObjectType());
  EXPECT_EQ(*vrf.mixedAirNode(), *vrf.outdoorAirMixer()->mixedAirNode());
  EXPECT_EQ(*vrf.outdoorAirNode(), *vrf.outdoorAirMixer()->outdoorAirNode());
  EXPECT_EQ(*vrf.reliefAirNode(), *vrf.outdoorAirMixer()->reliefAirNode());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_ControlRelationships_RoundTrip) {
  Model model;
  ZoneHVACTerminalUnitVariableRefrigerantFlow vrf(model);
  ThermalZone zone(model);

  auto defaultAvailability = vrf.terminalUnitAvailabilityschedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultAvailability);
  EXPECT_DOUBLE_EQ(1.0, defaultAvailability->value());
  auto defaultFanMode = vrf.supplyAirFanOperatingModeSchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultFanMode);
  EXPECT_DOUBLE_EQ(1.0, defaultFanMode->value());

  ScheduleCompact availability(model);
  ScheduleCompact fanMode(model);
  ASSERT_TRUE(availability.setToConstantValue(0.3));
  ASSERT_TRUE(fanMode.setToConstantValue(1.0));

  EXPECT_TRUE(vrf.setTerminalUnitAvailabilityschedule(availability));
  EXPECT_TRUE(vrf.setSupplyAirFanOperatingModeSchedule(fanMode));
  EXPECT_TRUE(vrf.setControllingZoneorThermostatLocation(zone));
  EXPECT_EQ(availability.handle(), vrf.terminalUnitAvailabilityschedule().handle());
  EXPECT_EQ(fanMode.handle(), vrf.supplyAirFanOperatingModeSchedule().handle());
  ASSERT_TRUE(vrf.controllingZoneorThermostatLocation());
  EXPECT_EQ(zone.handle(), vrf.controllingZoneorThermostatLocation()->handle());

  vrf.resetControllingZoneorThermostatLocation();
  EXPECT_FALSE(vrf.controllingZoneorThermostatLocation());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_NodeRolesFollowBlowThroughOrder) {
  Model model;
  FanOnOff fan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  CoilHeatingElectric supplementalHeatingCoil(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow vrf(model);

  ASSERT_TRUE(vrf.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(vrf.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(vrf.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(vrf.setSupplyAirFanPlacement("BlowThrough"));
  ASSERT_TRUE(vrf.setSupplyAirFan(fan));
  ASSERT_TRUE(vrf.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(vrf.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(vrf.setSupplementalHeatingCoil(supplementalHeatingCoil));

  ASSERT_TRUE(vrf.fanOutletNode());
  ASSERT_TRUE(vrf.coolingCoilOutletNode());
  ASSERT_TRUE(vrf.heatingCoilOutletNode());
  ASSERT_TRUE(vrf.outletNode());

  auto coolingInlet = coolingCoil.getString(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::CoilAirInletNode, true);
  auto heatingInlet = heatingCoil.getString(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::CoilAirInletNode, true);
  ASSERT_TRUE(coolingInlet);
  ASSERT_TRUE(heatingInlet);
  EXPECT_EQ(vrf.fanOutletNode()->nameString(), *coolingInlet);
  EXPECT_EQ(vrf.coolingCoilOutletNode()->nameString(), *heatingInlet);
  EXPECT_EQ(*vrf.heatingCoilOutletNode(), *supplementalHeatingCoil.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*vrf.outletNode(), *supplementalHeatingCoil.outletModelObject()->optionalCast<Node>());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_InternalNodeRenamesSurviveCanonicalize) {
  Model model;
  FanOnOff fan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  CoilHeatingElectric supplementalHeatingCoil(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow vrf(model);

  ASSERT_TRUE(vrf.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(vrf.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(vrf.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(vrf.setSupplyAirFan(fan));
  ASSERT_TRUE(vrf.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(vrf.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(vrf.setSupplementalHeatingCoil(supplementalHeatingCoil));

  ASSERT_TRUE(vrf.fanOutletNode());
  ASSERT_TRUE(vrf.coolingCoilOutletNode());
  ASSERT_TRUE(vrf.heatingCoilOutletNode());
  ASSERT_TRUE(vrf.fanOutletNode()->setName("Custom VRF Fan Outlet"));
  ASSERT_TRUE(vrf.coolingCoilOutletNode()->setName("Custom VRF Cooling Outlet"));
  ASSERT_TRUE(vrf.heatingCoilOutletNode()->setName("Custom VRF Heating Outlet"));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  ASSERT_TRUE(vrf.fanOutletNode());
  ASSERT_TRUE(vrf.coolingCoilOutletNode());
  ASSERT_TRUE(vrf.heatingCoilOutletNode());
  EXPECT_EQ("Custom VRF Fan Outlet", vrf.fanOutletNode()->nameString());
  EXPECT_EQ("Custom VRF Cooling Outlet", vrf.coolingCoilOutletNode()->nameString());
  EXPECT_EQ("Custom VRF Heating Outlet", vrf.heatingCoilOutletNode()->nameString());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_ContainedChildTopologyMutationsAreRejected) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanOnOff fan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  CoilHeatingElectric supplementalHeatingCoil(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow vrf(model);

  ASSERT_TRUE(vrf.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(vrf.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(vrf.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(vrf.setSupplyAirFan(fan));
  ASSERT_TRUE(vrf.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(vrf.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(vrf.setSupplementalHeatingCoil(supplementalHeatingCoil));

  auto originalFanOutlet = vrf.fanOutletNode();
  auto originalCoolingOutlet = vrf.coolingCoilOutletNode();
  auto originalHeatingOutlet = vrf.heatingCoilOutletNode();
  ASSERT_TRUE(originalFanOutlet);
  ASSERT_TRUE(originalCoolingOutlet);
  ASSERT_TRUE(originalHeatingOutlet);

  auto supplyOutletNode = airLoop.supplyOutletNode();

  fan.disconnect();
  EXPECT_FALSE(fan.addToNode(supplyOutletNode));
  EXPECT_FALSE(fan.isRemovable());
  EXPECT_TRUE(fan.remove().empty());

  coolingCoil.disconnect();
  EXPECT_FALSE(coolingCoil.addToNode(supplyOutletNode));
  EXPECT_FALSE(coolingCoil.isRemovable());
  EXPECT_TRUE(coolingCoil.remove().empty());

  heatingCoil.disconnect();
  EXPECT_FALSE(heatingCoil.addToNode(supplyOutletNode));
  EXPECT_FALSE(heatingCoil.isRemovable());
  EXPECT_TRUE(heatingCoil.remove().empty());

  supplementalHeatingCoil.disconnect();
  EXPECT_FALSE(supplementalHeatingCoil.addToNode(supplyOutletNode));
  EXPECT_FALSE(supplementalHeatingCoil.isRemovable());
  EXPECT_TRUE(supplementalHeatingCoil.remove().empty());

  ASSERT_TRUE(vrf.fanOutletNode());
  ASSERT_TRUE(vrf.coolingCoilOutletNode());
  ASSERT_TRUE(vrf.heatingCoilOutletNode());
  EXPECT_EQ(*originalFanOutlet, *vrf.fanOutletNode());
  EXPECT_EQ(*originalCoolingOutlet, *vrf.coolingCoilOutletNode());
  EXPECT_EQ(*originalHeatingOutlet, *vrf.heatingCoilOutletNode());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_CanonicalizeRepairsContainedNodePath) {
  Model model;
  FanOnOff fan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  CoilHeatingElectric supplementalHeatingCoil(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow vrf(model);

  ASSERT_TRUE(vrf.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(vrf.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(vrf.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(vrf.setSupplyAirFanPlacement("DrawThrough"));
  ASSERT_TRUE(vrf.setSupplyAirFan(fan));
  ASSERT_TRUE(vrf.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(vrf.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(vrf.setSupplementalHeatingCoil(supplementalHeatingCoil));

  ASSERT_TRUE(vrf.inletNode());
  ASSERT_TRUE(vrf.outletNode());
  auto expectedInlet = vrf.inletNode();
  auto expectedOutlet = vrf.outletNode();
  ASSERT_TRUE(expectedInlet);
  ASSERT_TRUE(expectedOutlet);

  Node rogueCoolingOutlet(model);
  ASSERT_TRUE(rogueCoolingOutlet.setName("Rogue VRF Cooling Outlet"));
  Node rogueHeatingOutlet(model);
  ASSERT_TRUE(rogueHeatingOutlet.setName("Rogue VRF Heating Outlet"));
  Node rogueFanOutlet(model);
  ASSERT_TRUE(rogueFanOutlet.setName("Rogue VRF Fan Outlet"));

  ASSERT_TRUE(coolingCoil.setPointer(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::CoilAirInletNode, vrf.inletNode()->handle()));
  ASSERT_TRUE(coolingCoil.setPointer(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::CoilAirOutletNode, rogueCoolingOutlet.handle()));
  ASSERT_TRUE(heatingCoil.setPointer(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::CoilAirInletNode, rogueCoolingOutlet.handle()));
  ASSERT_TRUE(heatingCoil.setPointer(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::CoilAirOutletNode, rogueHeatingOutlet.handle()));
  ASSERT_TRUE(fan.setPointer(fan.inletPort(), rogueHeatingOutlet.handle()));
  ASSERT_TRUE(fan.setPointer(fan.outletPort(), rogueFanOutlet.handle()));
  ASSERT_TRUE(supplementalHeatingCoil.setPointer(supplementalHeatingCoil.inletPort(), rogueFanOutlet.handle()));
  ASSERT_TRUE(supplementalHeatingCoil.setPointer(supplementalHeatingCoil.outletPort(), vrf.outletNode()->handle()));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  ASSERT_TRUE(vrf.inletNode());
  ASSERT_TRUE(vrf.outletNode());
  ASSERT_TRUE(vrf.coolingCoilOutletNode());
  ASSERT_TRUE(vrf.heatingCoilOutletNode());
  ASSERT_TRUE(vrf.fanOutletNode());
  EXPECT_EQ(*expectedInlet, *vrf.inletNode());
  EXPECT_EQ(*expectedOutlet, *vrf.outletNode());
  EXPECT_EQ("Rogue VRF Cooling Outlet", vrf.coolingCoilOutletNode()->nameString());
  EXPECT_EQ("Rogue VRF Heating Outlet", vrf.heatingCoilOutletNode()->nameString());
  EXPECT_EQ("Rogue VRF Fan Outlet", vrf.fanOutletNode()->nameString());
  auto repairedHeatingInlet = heatingCoil.getString(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::CoilAirInletNode, true);
  ASSERT_TRUE(repairedHeatingInlet);
  EXPECT_EQ(vrf.coolingCoilOutletNode()->nameString(), *repairedHeatingInlet);
  EXPECT_EQ(*vrf.heatingCoilOutletNode(), *fan.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*vrf.fanOutletNode(), *supplementalHeatingCoil.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*vrf.outletNode(), *supplementalHeatingCoil.outletModelObject()->optionalCast<Node>());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_DirectAirLoopBranchKeepsTerminalAsPublicComponent) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone controllingZone(model);
  FanOnOff ownedFan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);

  ASSERT_TRUE(terminal.setName("Direct VRF Terminal"));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(terminal.setSupplyAirFanPlacement("DrawThrough"));
  ASSERT_TRUE(terminal.setSupplyAirFan(ownedFan));
  ASSERT_TRUE(terminal.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(terminal.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(terminal.setControllingZoneorThermostatLocation(controllingZone));

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(terminal.addToNode(supplyOutletNode));

  const auto supplyComponents = airLoop.supplyComponents();
  ASSERT_EQ(3u, supplyComponents.size());
  EXPECT_EQ(terminal.handle(), supplyComponents[1].handle());
  ASSERT_TRUE(terminal.airLoopHVAC());
  EXPECT_EQ(airLoop.handle(), terminal.airLoopHVAC()->handle());
  ASSERT_TRUE(terminal.controllingZoneorThermostatLocation());
  EXPECT_EQ(controllingZone.handle(), terminal.controllingZoneorThermostatLocation()->handle());

  ASSERT_TRUE(terminal.inletNode());
  ASSERT_TRUE(terminal.outletNode());
  ASSERT_TRUE(coolingCoil.inletModelObject());
  ASSERT_TRUE(coolingCoil.outletModelObject());
  ASSERT_TRUE(heatingCoil.inletModelObject());
  ASSERT_TRUE(heatingCoil.outletModelObject());
  ASSERT_TRUE(ownedFan.inletModelObject());
  ASSERT_TRUE(ownedFan.outletModelObject());
  EXPECT_EQ(terminal.inletNode()->handle(), coolingCoil.inletModelObject()->handle());
  EXPECT_EQ(coolingCoil.outletModelObject()->handle(), heatingCoil.inletModelObject()->handle());
  EXPECT_EQ(heatingCoil.outletModelObject()->handle(), ownedFan.inletModelObject()->handle());
  EXPECT_EQ(ownedFan.outletModelObject()->handle(), terminal.outletNode()->handle());

  for (const auto& component : supplyComponents) {
    EXPECT_NE(ownedFan.handle(), component.handle());
    EXPECT_NE(coolingCoil.handle(), component.handle());
    EXPECT_NE(heatingCoil.handle(), component.handle());
  }
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_AdjacentFanInsertionKeepsOwnedPathAligned) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanOnOff ownedFan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);

  ASSERT_TRUE(terminal.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(terminal.setSupplyAirFanPlacement("DrawThrough"));
  ASSERT_TRUE(terminal.setSupplyAirFan(ownedFan));
  ASSERT_TRUE(terminal.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(terminal.setHeatingCoil(heatingCoil));

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(terminal.addToNode(supplyOutletNode));
  ASSERT_TRUE(terminal.inletNode());
  auto originalInlet = *terminal.inletNode();

  FanSystemModel branchFan(model);
  ASSERT_TRUE(branchFan.addToNode(originalInlet));
  ASSERT_TRUE(branchFan.outletModelObject());
  ASSERT_TRUE(terminal.inletNode());
  ASSERT_TRUE(coolingCoil.inletModelObject());
  EXPECT_EQ(branchFan.outletModelObject()->handle(), terminal.inletNode()->handle());
  EXPECT_EQ(terminal.inletNode()->handle(), coolingCoil.inletModelObject()->handle());

  EXPECT_FALSE(branchFan.remove().empty());
  ASSERT_TRUE(terminal.inletNode());
  ASSERT_TRUE(coolingCoil.inletModelObject());
  EXPECT_EQ(originalInlet.handle(), terminal.inletNode()->handle());
  EXPECT_EQ(terminal.inletNode()->handle(), coolingCoil.inletModelObject()->handle());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_DirectPlacementAcceptsMainBranchOutdoorAirBoundary) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  FanOnOff ownedFan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyOutletNode));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(terminal.setSupplyAirFan(ownedFan));
  ASSERT_TRUE(terminal.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(terminal.setHeatingCoil(heatingCoil));

  ASSERT_TRUE(terminal.addToNode(supplyOutletNode));
  const auto supplyComponents = airLoop.supplyComponents();
  const auto oaPosition = std::ranges::find_if(supplyComponents, [&](const auto& component) { return component.handle() == oaSystem.handle(); });
  const auto terminalPosition =
    std::ranges::find_if(supplyComponents, [&](const auto& component) { return component.handle() == terminal.handle(); });
  ASSERT_NE(supplyComponents.end(), oaPosition);
  ASSERT_NE(supplyComponents.end(), terminalPosition);
  EXPECT_LT(oaPosition, terminalPosition);
  EXPECT_TRUE(std::ranges::none_of(supplyComponents, [&](const auto& component) {
    return (component.handle() == ownedFan.handle()) || (component.handle() == coolingCoil.handle()) || (component.handle() == heatingCoil.handle());
  }));
  ASSERT_TRUE(terminal.inletNode());
  ASSERT_TRUE(terminal.outletNode());
  ASSERT_TRUE(coolingCoil.inletModelObject());
  EXPECT_EQ(terminal.inletNode()->handle(), coolingCoil.inletModelObject()->handle());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_OutdoorAirPlacementKeepsOwnedAndAdjacentPathsAligned) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  FanOnOff ownedFan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);
  FanSystemModel adjacentFan(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
  ASSERT_TRUE(terminal.setSupplyAirFanPlacement("DrawThrough"));
  ASSERT_TRUE(terminal.setSupplyAirFan(ownedFan));
  ASSERT_TRUE(terminal.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(terminal.setHeatingCoil(heatingCoil));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);
  ASSERT_TRUE(terminal.addToNode(*outboardOANode));

  auto oaComponents = oaSystem.oaComponents();
  ASSERT_EQ(3u, oaComponents.size());
  EXPECT_EQ(outboardOANode->handle(), oaComponents[0].handle());
  EXPECT_EQ(terminal.handle(), oaComponents[1].handle());
  ASSERT_TRUE(terminal.inletNode());
  ASSERT_TRUE(terminal.outletNode());
  EXPECT_EQ(terminal.inletNode()->handle(), oaComponents[0].handle());
  EXPECT_EQ(terminal.outletNode()->handle(), oaComponents[2].handle());
  ASSERT_TRUE(terminal.airLoopHVACOutdoorAirSystem());
  EXPECT_EQ(oaSystem.handle(), terminal.airLoopHVACOutdoorAirSystem()->handle());
  EXPECT_FALSE(terminal.outdoorAirMixer());

  ASSERT_TRUE(coolingCoil.inletModelObject());
  ASSERT_TRUE(coolingCoil.outletModelObject());
  ASSERT_TRUE(heatingCoil.inletModelObject());
  ASSERT_TRUE(heatingCoil.outletModelObject());
  ASSERT_TRUE(ownedFan.inletModelObject());
  ASSERT_TRUE(ownedFan.outletModelObject());
  EXPECT_EQ(terminal.inletNode()->handle(), coolingCoil.inletModelObject()->handle());
  EXPECT_EQ(coolingCoil.outletModelObject()->handle(), heatingCoil.inletModelObject()->handle());
  EXPECT_EQ(heatingCoil.outletModelObject()->handle(), ownedFan.inletModelObject()->handle());
  EXPECT_EQ(ownedFan.outletModelObject()->handle(), terminal.outletNode()->handle());

  auto terminalOutletNode = *terminal.outletNode();
  ASSERT_TRUE(adjacentFan.addToNode(terminalOutletNode));
  oaComponents = oaSystem.oaComponents();
  ASSERT_EQ(5u, oaComponents.size());
  EXPECT_EQ(terminal.handle(), oaComponents[1].handle());
  EXPECT_EQ(adjacentFan.handle(), oaComponents[3].handle());
  ASSERT_TRUE(adjacentFan.inletModelObject());
  ASSERT_TRUE(terminal.outletNode());
  EXPECT_EQ(terminal.outletNode()->handle(), adjacentFan.inletModelObject()->handle());
  ASSERT_TRUE(ownedFan.outletModelObject());
  EXPECT_EQ(ownedFan.outletModelObject()->handle(), terminal.outletNode()->handle());

  ASSERT_TRUE(terminal.removeFromAirLoopHVAC());
  oaComponents = oaSystem.oaComponents();
  ASSERT_EQ(3u, oaComponents.size());
  EXPECT_EQ(adjacentFan.handle(), oaComponents[1].handle());
  ASSERT_TRUE(adjacentFan.inletModelObject());
  EXPECT_EQ(outboardOANode->handle(), adjacentFan.inletModelObject()->handle());
  EXPECT_FALSE(terminal.inletNode());
  EXPECT_FALSE(terminal.outletNode());
  EXPECT_FALSE(coolingCoil.inletModelObject());
  EXPECT_FALSE(heatingCoil.inletModelObject());
  EXPECT_FALSE(ownedFan.inletModelObject());

  ASSERT_TRUE(terminal.addToNode(*outboardOANode));
  oaComponents = oaSystem.oaComponents();
  ASSERT_EQ(5u, oaComponents.size());
  EXPECT_EQ(terminal.handle(), oaComponents[1].handle());
  EXPECT_EQ(adjacentFan.handle(), oaComponents[3].handle());

  ASSERT_TRUE(terminal.removeFromAirLoopHVAC());
  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(terminal.addToNode(supplyOutletNode));
  const auto oaComponentsBeforeRejectedMove = oaSystem.oaComponents();
  const auto supplyComponentsBeforeRejectedMove = airLoop.supplyComponents();
  ASSERT_TRUE(terminal.inletNode());
  ASSERT_TRUE(terminal.outletNode());
  const auto terminalInletBeforeRejectedMove = terminal.inletNode()->handle();
  const auto terminalOutletBeforeRejectedMove = terminal.outletNode()->handle();

  EXPECT_FALSE(terminal.addToNode(*outboardOANode));
  EXPECT_EQ(oaComponentsBeforeRejectedMove, oaSystem.oaComponents());
  EXPECT_EQ(supplyComponentsBeforeRejectedMove, airLoop.supplyComponents());
  ASSERT_TRUE(terminal.inletNode());
  ASSERT_TRUE(terminal.outletNode());
  EXPECT_EQ(terminalInletBeforeRejectedMove, terminal.inletNode()->handle());
  EXPECT_EQ(terminalOutletBeforeRejectedMove, terminal.outletNode()->handle());
  EXPECT_TRUE(std::ranges::any_of(supplyComponentsBeforeRejectedMove, [&](const auto& object) { return object.handle() == terminal.handle(); }));
  EXPECT_TRUE(std::ranges::none_of(supplyComponentsBeforeRejectedMove, [&](const auto& object) {
    return (object.handle() == ownedFan.handle()) || (object.handle() == coolingCoil.handle()) || (object.handle() == heatingCoil.handle());
  }));

  ASSERT_TRUE(terminal.removeFromAirLoopHVAC());
  ASSERT_TRUE(terminal.addToNode(*outboardOANode));
  oaComponents = oaSystem.oaComponents();
  ASSERT_EQ(5u, oaComponents.size());
  EXPECT_EQ(terminal.handle(), oaComponents[1].handle());
  EXPECT_EQ(adjacentFan.handle(), oaComponents[3].handle());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_OutdoorAirPlacementSurvivesReloadAndRemoval) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-vrf-terminal-outdoor-air-roundtrip.idf");

  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  FanOnOff ownedFan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);

  ASSERT_TRUE(oaSystem.setName("Roundtrip VRF OA System"));
  ASSERT_TRUE(ownedFan.setName("Roundtrip OA VRF Owned Fan"));
  ASSERT_TRUE(coolingCoil.setName("Roundtrip OA VRF Cooling Coil"));
  ASSERT_TRUE(heatingCoil.setName("Roundtrip OA VRF Heating Coil"));
  ASSERT_TRUE(terminal.setName("Roundtrip OA VRF Terminal"));
  ASSERT_TRUE(terminal.setSupplyAirFanPlacement("DrawThrough"));
  ASSERT_TRUE(terminal.setSupplyAirFan(ownedFan));
  ASSERT_TRUE(terminal.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(terminal.setHeatingCoil(heatingCoil));

  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);
  ASSERT_TRUE(terminal.addToNode(*outboardOANode));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedOASystem = loadedModel->getConcreteModelObjectByName<AirLoopHVACOutdoorAirSystem>("Roundtrip VRF OA System");
  auto loadedFan = loadedModel->getConcreteModelObjectByName<FanOnOff>("Roundtrip OA VRF Owned Fan");
  auto loadedCoolingCoil = loadedModel->getConcreteModelObjectByName<CoilCoolingDXVariableRefrigerantFlow>("Roundtrip OA VRF Cooling Coil");
  auto loadedHeatingCoil = loadedModel->getConcreteModelObjectByName<CoilHeatingDXVariableRefrigerantFlow>("Roundtrip OA VRF Heating Coil");
  auto loadedTerminal = loadedModel->getConcreteModelObjectByName<ZoneHVACTerminalUnitVariableRefrigerantFlow>("Roundtrip OA VRF Terminal");
  ASSERT_TRUE(loadedOASystem);
  ASSERT_TRUE(loadedFan);
  ASSERT_TRUE(loadedCoolingCoil);
  ASSERT_TRUE(loadedHeatingCoil);
  ASSERT_TRUE(loadedTerminal);

  auto oaComponents = loadedOASystem->oaComponents();
  ASSERT_EQ(3u, oaComponents.size());
  EXPECT_EQ(loadedTerminal->handle(), oaComponents[1].handle());
  ASSERT_TRUE(loadedTerminal->airLoopHVACOutdoorAirSystem());
  EXPECT_EQ(loadedOASystem->handle(), loadedTerminal->airLoopHVACOutdoorAirSystem()->handle());
  ASSERT_TRUE(loadedTerminal->inletNode());
  ASSERT_TRUE(loadedTerminal->outletNode());
  ASSERT_TRUE(loadedCoolingCoil->inletModelObject());
  ASSERT_TRUE(loadedHeatingCoil->inletModelObject());
  ASSERT_TRUE(loadedFan->inletModelObject());
  EXPECT_EQ(loadedTerminal->inletNode()->handle(), loadedCoolingCoil->inletModelObject()->handle());
  EXPECT_EQ(loadedCoolingCoil->outletModelObject()->handle(), loadedHeatingCoil->inletModelObject()->handle());
  EXPECT_EQ(loadedHeatingCoil->outletModelObject()->handle(), loadedFan->inletModelObject()->handle());
  EXPECT_EQ(loadedFan->outletModelObject()->handle(), loadedTerminal->outletNode()->handle());

  ASSERT_TRUE(loadedTerminal->removeFromAirLoopHVAC());
  EXPECT_EQ(1u, loadedOASystem->oaComponents().size());
  EXPECT_TRUE(loadedModel->getObject(loadedTerminal->handle()));
  EXPECT_TRUE(loadedModel->getObject(loadedFan->handle()));
  auto loadedOutboardOANode = loadedOASystem->outboardOANode();
  ASSERT_TRUE(loadedOutboardOANode);
  ASSERT_TRUE(loadedTerminal->addToNode(*loadedOutboardOANode));

  const auto terminalHandle = loadedTerminal->handle();
  const auto fanHandle = loadedFan->handle();
  const auto coolingHandle = loadedCoolingCoil->handle();
  const auto heatingHandle = loadedHeatingCoil->handle();
  EXPECT_FALSE(loadedTerminal->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(terminalHandle));
  EXPECT_FALSE(loadedModel->getObject(fanHandle));
  EXPECT_FALSE(loadedModel->getObject(coolingHandle));
  EXPECT_FALSE(loadedModel->getObject(heatingHandle));
  EXPECT_EQ(1u, loadedOASystem->oaComponents().size());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_DirectDetachPreservesTerminalAndAllowsReattach) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone controllingZone(model);
  FanOnOff ownedFan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);

  ASSERT_TRUE(terminal.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(terminal.setSupplyAirFan(ownedFan));
  ASSERT_TRUE(terminal.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(terminal.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(terminal.setControllingZoneorThermostatLocation(controllingZone));

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(terminal.addToNode(supplyOutletNode));
  ASSERT_TRUE(terminal.removeFromAirLoopHVAC());

  EXPECT_EQ(2u, airLoop.supplyComponents().size());
  EXPECT_FALSE(terminal.airLoopHVAC());
  EXPECT_FALSE(terminal.inletNode());
  EXPECT_FALSE(terminal.outletNode());
  EXPECT_FALSE(ownedFan.inletModelObject());
  EXPECT_FALSE(ownedFan.outletModelObject());
  EXPECT_FALSE(coolingCoil.inletModelObject());
  EXPECT_FALSE(coolingCoil.outletModelObject());
  EXPECT_FALSE(heatingCoil.inletModelObject());
  EXPECT_FALSE(heatingCoil.outletModelObject());
  ASSERT_TRUE(terminal.coolingCoil());
  ASSERT_TRUE(terminal.heatingCoil());
  EXPECT_EQ(ownedFan.handle(), terminal.supplyAirFan().handle());
  EXPECT_EQ(coolingCoil.handle(), terminal.coolingCoil()->handle());
  EXPECT_EQ(heatingCoil.handle(), terminal.heatingCoil()->handle());
  ASSERT_TRUE(terminal.controllingZoneorThermostatLocation());
  EXPECT_EQ(controllingZone.handle(), terminal.controllingZoneorThermostatLocation()->handle());

  ASSERT_TRUE(terminal.addToNode(supplyOutletNode));
  ASSERT_TRUE(terminal.inletNode());
  ASSERT_TRUE(terminal.outletNode());
  EXPECT_EQ(3u, airLoop.supplyComponents().size());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_DirectPathSurvivesReloadAndRecursiveRemoval) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-vrf-terminal-direct-roundtrip.idf");

  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone controllingZone(model);
  FanOnOff ownedFan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);

  ASSERT_TRUE(airLoop.setName("Roundtrip VRF Air Loop"));
  ASSERT_TRUE(controllingZone.setName("Roundtrip VRF Controlling Zone"));
  ASSERT_TRUE(ownedFan.setName("Roundtrip VRF Owned Fan"));
  ASSERT_TRUE(coolingCoil.setName("Roundtrip VRF Cooling Coil"));
  ASSERT_TRUE(heatingCoil.setName("Roundtrip VRF Heating Coil"));
  ASSERT_TRUE(terminal.setName("Roundtrip VRF Terminal"));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(terminal.setSupplyAirFanPlacement("DrawThrough"));
  ASSERT_TRUE(terminal.setSupplyAirFan(ownedFan));
  ASSERT_TRUE(terminal.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(terminal.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(terminal.setControllingZoneorThermostatLocation(controllingZone));
  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(terminal.addToNode(supplyOutletNode));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedAirLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Roundtrip VRF Air Loop");
  auto loadedZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Roundtrip VRF Controlling Zone");
  auto loadedFan = loadedModel->getConcreteModelObjectByName<FanOnOff>("Roundtrip VRF Owned Fan");
  auto loadedCoolingCoil = loadedModel->getConcreteModelObjectByName<CoilCoolingDXVariableRefrigerantFlow>("Roundtrip VRF Cooling Coil");
  auto loadedHeatingCoil = loadedModel->getConcreteModelObjectByName<CoilHeatingDXVariableRefrigerantFlow>("Roundtrip VRF Heating Coil");
  auto loadedTerminal = loadedModel->getConcreteModelObjectByName<ZoneHVACTerminalUnitVariableRefrigerantFlow>("Roundtrip VRF Terminal");
  ASSERT_TRUE(loadedAirLoop);
  ASSERT_TRUE(loadedZone);
  ASSERT_TRUE(loadedFan);
  ASSERT_TRUE(loadedCoolingCoil);
  ASSERT_TRUE(loadedHeatingCoil);
  ASSERT_TRUE(loadedTerminal);
  ASSERT_TRUE(loadedTerminal->airLoopHVAC());
  EXPECT_EQ(loadedAirLoop->handle(), loadedTerminal->airLoopHVAC()->handle());
  ASSERT_TRUE(loadedTerminal->controllingZoneorThermostatLocation());
  EXPECT_EQ(loadedZone->handle(), loadedTerminal->controllingZoneorThermostatLocation()->handle());
  ASSERT_TRUE(loadedTerminal->inletNode());
  ASSERT_TRUE(loadedTerminal->outletNode());
  ASSERT_TRUE(loadedCoolingCoil->inletModelObject());
  ASSERT_TRUE(loadedCoolingCoil->outletModelObject());
  ASSERT_TRUE(loadedHeatingCoil->inletModelObject());
  ASSERT_TRUE(loadedHeatingCoil->outletModelObject());
  ASSERT_TRUE(loadedFan->inletModelObject());
  ASSERT_TRUE(loadedFan->outletModelObject());
  EXPECT_EQ(loadedTerminal->inletNode()->handle(), loadedCoolingCoil->inletModelObject()->handle());
  EXPECT_EQ(loadedCoolingCoil->outletModelObject()->handle(), loadedHeatingCoil->inletModelObject()->handle());
  EXPECT_EQ(loadedHeatingCoil->outletModelObject()->handle(), loadedFan->inletModelObject()->handle());
  EXPECT_EQ(loadedFan->outletModelObject()->handle(), loadedTerminal->outletNode()->handle());

  const auto terminalHandle = loadedTerminal->handle();
  const auto fanHandle = loadedFan->handle();
  const auto coolingHandle = loadedCoolingCoil->handle();
  const auto heatingHandle = loadedHeatingCoil->handle();
  EXPECT_FALSE(loadedTerminal->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(terminalHandle));
  EXPECT_FALSE(loadedModel->getObject(fanHandle));
  EXPECT_FALSE(loadedModel->getObject(coolingHandle));
  EXPECT_FALSE(loadedModel->getObject(heatingHandle));
  EXPECT_EQ(2u, loadedAirLoop->supplyComponents().size());
  EXPECT_TRUE(loadedModel->getObject(loadedZone->handle()));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_DirectPlacementRejectsUnsupportedNodesWithoutMutation) {
  Model model;
  Model foreignModel;
  AirLoopHVAC airLoop(model);
  AirLoopHVAC foreignAirLoop(foreignModel);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  ThermalZone equipmentZone(model);
  FanOnOff ownedFan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);

  ASSERT_TRUE(terminal.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(terminal.setSupplyAirFan(ownedFan));
  ASSERT_TRUE(terminal.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(terminal.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(terminal.inletNode());
  ASSERT_TRUE(terminal.outletNode());
  const auto originalInlet = terminal.inletNode()->handle();
  const auto originalOutlet = terminal.outletNode()->handle();

  auto foreignSupplyNode = foreignAirLoop.supplyOutletNode();
  EXPECT_FALSE(terminal.addToNode(foreignSupplyNode));
  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(terminal.addToNode(demandInletNode));
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
  ASSERT_TRUE(oaSystem.outboardReliefNode());
  auto outboardReliefNode = *oaSystem.outboardReliefNode();
  EXPECT_FALSE(terminal.addToNode(outboardReliefNode));

  ASSERT_TRUE(terminal.inletNode());
  ASSERT_TRUE(terminal.outletNode());
  EXPECT_EQ(originalInlet, terminal.inletNode()->handle());
  EXPECT_EQ(originalOutlet, terminal.outletNode()->handle());
  EXPECT_EQ(3u, airLoop.supplyComponents().size());

  ASSERT_TRUE(terminal.addToThermalZone(equipmentZone));
  auto supplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(terminal.addToNode(supplyOutletNode));
  ASSERT_TRUE(terminal.thermalZone());
  EXPECT_EQ(equipmentZone.handle(), terminal.thermalZone()->handle());
}
