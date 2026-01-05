/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "EnergyPlusFixture.hpp"

#include "../ForwardTranslator.hpp"

#include "../../model/CoilSystemCoolingWater.hpp"
#include "../../model/CoilSystemCoolingWater_Impl.hpp"
#include "../../model/Schedule.hpp"
#include "../../model/Schedule_Impl.hpp"
#include "../../model/ScheduleConstant.hpp"
#include "../../model/CoilCoolingWater.hpp"
#include "../../model/CoilCoolingWater_Impl.hpp"
#include "../../model/CoilSystemCoolingWaterHeatExchangerAssisted.hpp"
#include "../../model/CoilSystemCoolingWaterHeatExchangerAssisted_Impl.hpp"
#include "../../model/HeatExchangerAirToAirSensibleAndLatent.hpp"
#include "../../model/HeatExchangerAirToAirSensibleAndLatent_Impl.hpp"
#include "../../model/AirLoopHVAC.hpp"
#include "../../model/AirLoopHVACUnitarySystem.hpp"
#include "../../model/Node.hpp"
#include "../../model/Node_Impl.hpp"
#include "../../model/AirLoopHVACOutdoorAirSystem.hpp"
#include "../../model/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "../../model/ControllerOutdoorAir.hpp"
#include "../../model/ControllerOutdoorAir_Impl.hpp"
#include "../../model/PipeAdiabatic.hpp"
#include "../../model/PipeAdiabatic_Impl.hpp"

#include "../../utilities/idf/Workspace.hpp"
#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include "../../utilities/idf/WorkspaceExtensibleGroup.hpp"

// E+ FieldEnums
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/CoilSystem_Cooling_Water_FieldEnums.hxx>
#include <utilities/idd/Coil_Cooling_Water_FieldEnums.hxx>
#include <utilities/idd/CoilSystem_Cooling_Water_HeatExchangerAssisted_FieldEnums.hxx>
#include <utilities/idd/HeatExchanger_AirToAir_SensibleAndLatent_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_FieldEnums.hxx>
#include <utilities/idd/BranchList_FieldEnums.hxx>
#include <utilities/idd/Branch_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_UnitarySystem_FieldEnums.hxx>
#include <utilities/idd/Controller_WaterCoil_FieldEnums.hxx>
#include <utilities/idd/Controller_OutdoorAir_FieldEnums.hxx>

using namespace openstudio::energyplus;
using namespace openstudio::model;
using namespace openstudio;

TEST_F(EnergyPlusFixture, ForwardTranslator_CoilSystemCoolingWater_WithoutCompanion) {
  ForwardTranslator ft;

  Model m;

  CoilSystemCoolingWater coilSystemCoolingWater(m);
  auto cc = coilSystemCoolingWater.coolingCoil().cast<CoilCoolingWater>();

  coilSystemCoolingWater.setName("My CoilSystemCoolingWater");
  Schedule availabilitySchedule = m.alwaysOnDiscreteSchedule();
  EXPECT_TRUE(coilSystemCoolingWater.setAvailabilitySchedule(availabilitySchedule));
  EXPECT_TRUE(coilSystemCoolingWater.setDehumidificationControlType("CoolReheat"));
  EXPECT_TRUE(coilSystemCoolingWater.setRunonSensibleLoad(false));  // Opposite from IDD default
  EXPECT_TRUE(coilSystemCoolingWater.setRunonLatentLoad(true));     // Opposite from IDD default
  EXPECT_TRUE(coilSystemCoolingWater.setMinimumAirToWaterTemperatureOffset(1.0));
  EXPECT_TRUE(coilSystemCoolingWater.setEconomizerLockout(false));  // Opposite from IDD default
  EXPECT_TRUE(coilSystemCoolingWater.setMinimumWaterLoopTemperatureForHeatRecovery(1.2));

  AirLoopHVAC airLoop(m);
  Node supplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_TRUE(coilSystemCoolingWater.addToNode(supplyOutletNode));

  // They must be connected to a PlantLoop too
  PlantLoop chw_p(m);
  chw_p.addDemandBranchForComponent(cc);

  const Workspace w = ft.translateModel(m);

  const auto idfCoilSystems = w.getObjectsByType(IddObjectType::CoilSystem_Cooling_Water);
  ASSERT_EQ(1u, idfCoilSystems.size());
  const auto& idfCoilSystem = idfCoilSystems.front();

  WorkspaceObjectVector idfCoils(w.getObjectsByType(IddObjectType::Coil_Cooling_Water));
  ASSERT_EQ(1u, idfCoils.size());
  WorkspaceObject idfCoil(idfCoils[0]);

  // Go from AirLoopHVAC to BranchList to Branch
  WorkspaceObjectVector idf_airloops = w.getObjectsByType(IddObjectType::AirLoopHVAC);
  ASSERT_EQ(1u, idf_airloops.size());

  WorkspaceObject& idf_airLoopHVAC = idf_airloops.front();
  WorkspaceObject idf_brlist = idf_airLoopHVAC.getTarget(AirLoopHVACFields::BranchListName).get();

  // Should have one branch only
  ASSERT_EQ(1u, idf_brlist.extensibleGroups().size());
  auto w_eg = idf_brlist.extensibleGroups()[0].cast<WorkspaceExtensibleGroup>();
  WorkspaceObject idf_branch = w_eg.getTarget(BranchListExtensibleFields::BranchName).get();

  // There should be only one equipment on the branch
  ASSERT_EQ(1u, idf_branch.extensibleGroups().size());
  auto w_eg2 = idf_branch.extensibleGroups()[0].cast<WorkspaceExtensibleGroup>();

  EXPECT_EQ(w_eg2.getString(BranchExtensibleFields::ComponentInletNodeName).get(), coilSystemCoolingWater.inletModelObject().get().nameString());
  EXPECT_EQ(w_eg2.getString(BranchExtensibleFields::ComponentOutletNodeName).get(), coilSystemCoolingWater.outletModelObject().get().nameString());
  EXPECT_EQ("CoilSystem:Cooling:Water", w_eg2.getString(BranchExtensibleFields::ComponentObjectType).get());

  EXPECT_EQ(coilSystemCoolingWater.inletModelObject().get().nameString(),
            idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::AirInletNodeName).get());
  EXPECT_EQ(coilSystemCoolingWater.outletModelObject().get().nameString(),
            idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::AirOutletNodeName).get());
  EXPECT_EQ(availabilitySchedule.nameString(), idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::AvailabilityScheduleName).get());
  EXPECT_EQ("Coil:Cooling:Water", idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::CoolingCoilObjectType).get());
  EXPECT_EQ(coilSystemCoolingWater.coolingCoil().nameString(), idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::CoolingCoilName).get());
  EXPECT_EQ("CoolReheat", idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::DehumidificationControlType).get());
  EXPECT_EQ("No", idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::RunonSensibleLoad).get());
  EXPECT_EQ("Yes", idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::RunonLatentLoad).get());
  EXPECT_EQ(1.0, idfCoilSystem.getDouble(CoilSystem_Cooling_WaterFields::MinimumAirToWaterTemperatureOffset).get());
  EXPECT_EQ("No", idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::EconomizerLockout).get());
  EXPECT_EQ(1.2, idfCoilSystem.getDouble(CoilSystem_Cooling_WaterFields::MinimumWaterLoopTemperatureForHeatRecovery).get());
  EXPECT_TRUE(idfCoilSystem.isEmpty(CoilSystem_Cooling_WaterFields::CompanionCoilUsedForHeatRecovery));

  EXPECT_EQ(coilSystemCoolingWater.coolingCoil().nameString(), idfCoil.getString(Coil_Cooling_WaterFields::Name).get());
  EXPECT_EQ("Always On Discrete", idfCoil.getString(Coil_Cooling_WaterFields::AvailabilityScheduleName).get());
  EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignWaterFlowRate).get());
  EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignAirFlowRate).get());
  EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignInletWaterTemperature).get());
  EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignInletAirTemperature).get());
  EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignInletAirHumidityRatio).get());
  EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignOutletAirHumidityRatio).get());
  EXPECT_EQ(cc.waterInletModelObject().get().nameString(), idfCoil.getString(Coil_Cooling_WaterFields::WaterInletNodeName).get());
  EXPECT_EQ(cc.waterOutletModelObject().get().nameString(), idfCoil.getString(Coil_Cooling_WaterFields::WaterOutletNodeName).get());
  EXPECT_EQ(idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::AirInletNodeName).get(),
            idfCoil.getString(Coil_Cooling_WaterFields::AirInletNodeName).get());
  EXPECT_EQ(idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::AirOutletNodeName).get(),
            idfCoil.getString(Coil_Cooling_WaterFields::AirOutletNodeName).get());
  EXPECT_EQ("SimpleAnalysis", idfCoil.getString(Coil_Cooling_WaterFields::TypeofAnalysis).get());
  EXPECT_EQ("CrossFlow", idfCoil.getString(Coil_Cooling_WaterFields::HeatExchangerConfiguration).get());
  EXPECT_TRUE(idfCoil.isEmpty(Coil_Cooling_WaterFields::CondensateCollectionWaterStorageTankName));
  EXPECT_TRUE(idfCoil.isEmpty(Coil_Cooling_WaterFields::DesignWaterTemperatureDifference));

  EXPECT_EQ(0, w.getObjectsByType(IddObjectType::Controller_WaterCoil).size());
}

TEST_F(EnergyPlusFixture, ForwardTranslator_CoilSystemCoolingWater_WithCompanion) {
  ForwardTranslator ft;

  Model m;

  CoilSystemCoolingWater coilSystemCoolingWater(m);
  auto cc = coilSystemCoolingWater.coolingCoil().cast<CoilCoolingWater>();

  coilSystemCoolingWater.setName("My CoilSystemCoolingWater");
  Schedule availabilitySchedule = m.alwaysOnDiscreteSchedule();
  EXPECT_TRUE(coilSystemCoolingWater.setAvailabilitySchedule(availabilitySchedule));
  EXPECT_TRUE(coilSystemCoolingWater.setDehumidificationControlType("CoolReheat"));
  EXPECT_TRUE(coilSystemCoolingWater.setRunonSensibleLoad(false));  // Opposite from IDD default
  EXPECT_TRUE(coilSystemCoolingWater.setRunonLatentLoad(true));     // Opposite from IDD default
  EXPECT_TRUE(coilSystemCoolingWater.setMinimumAirToWaterTemperatureOffset(1.0));
  EXPECT_TRUE(coilSystemCoolingWater.setEconomizerLockout(false));  // Opposite from IDD default
  EXPECT_TRUE(coilSystemCoolingWater.setMinimumWaterLoopTemperatureForHeatRecovery(1.2));
  CoilCoolingWater companionCoilUsedForHeatRecovery(m);
  companionCoilUsedForHeatRecovery.setName("CompanionCoilUsedForHeatRecovery");
  EXPECT_TRUE(coilSystemCoolingWater.setCompanionCoilUsedForHeatRecovery(companionCoilUsedForHeatRecovery));

  AirLoopHVAC airLoop(m);
  Node supplyOutletNode = airLoop.supplyOutletNode();
  ControllerOutdoorAir controller1(m);
  AirLoopHVACOutdoorAirSystem oaSystem(m, controller1);
  EXPECT_TRUE(oaSystem.addToNode(supplyOutletNode));
  Node oaNode = oaSystem.outboardOANode().get();
  EXPECT_TRUE(coilSystemCoolingWater.addToNode(oaNode));
  Node reliefNode = oaSystem.outboardReliefNode().get();
  EXPECT_TRUE(companionCoilUsedForHeatRecovery.addToNode(reliefNode));

  oaNode.setName("Outdoor Air Inlet Node");
  reliefNode.setName("Relief Node");
  oaSystem.reliefAirModelObject()->setName("Return to OA System Node");
  oaSystem.outdoorAirModelObject()->setName("OA System Outlet to Mixed Node");
  airLoop.mixedAirNode()->setName("Mixed Air Node");
  airLoop.supplyInletNode().setName("Supply Inlet Node");
  airLoop.supplyOutletNode().setName("Supply Outlet Node");

  // They must be connected to a PlantLoop too
  PlantLoop chw_p(m);
  chw_p.addDemandBranchForComponent(cc);
  PipeAdiabatic pipe(m);
  Node coolingOutlet = cc.waterOutletModelObject()->cast<Node>();
  EXPECT_TRUE(pipe.addToNode(coolingOutlet));
  Node pipeOutlet = pipe.outletModelObject()->cast<Node>();
  EXPECT_TRUE(companionCoilUsedForHeatRecovery.addToNode(pipeOutlet));

  cc.waterInletModelObject()->setName("Cooling Coil Water Inlet Node");
  cc.waterOutletModelObject()->setName("Cooling Coil Water Outlet to Pipe Inlet Node");
  pipe.outletModelObject()->setName("Pipe Outlet to Companion Coil Water Inlet Node");
  companionCoilUsedForHeatRecovery.waterOutletModelObject()->setName("Companion Coil Water Outlet Node");

  const Workspace w = ft.translateModel(m);

  const auto idfCoilSystems = w.getObjectsByType(IddObjectType::CoilSystem_Cooling_Water);
  ASSERT_EQ(1u, idfCoilSystems.size());
  const auto& idfCoilSystem = idfCoilSystems.front();

  WorkspaceObjectVector idfCoils(w.getObjectsByType(IddObjectType::Coil_Cooling_Water));
  ASSERT_EQ(2u, idfCoils.size());

  WorkspaceObjectVector idfControllers(w.getObjectsByType(IddObjectType::Controller_OutdoorAir));
  ASSERT_EQ(1u, idfControllers.size());
  const auto& idfController = idfControllers.front();

  // Go from AirLoopHVAC to BranchList to Branch
  WorkspaceObjectVector idf_airloops = w.getObjectsByType(IddObjectType::AirLoopHVAC);
  ASSERT_EQ(1u, idf_airloops.size());

  WorkspaceObject& idf_airLoopHVAC = idf_airloops.front();
  WorkspaceObject idf_brlist = idf_airLoopHVAC.getTarget(AirLoopHVACFields::BranchListName).get();

  // Should have one branch only
  ASSERT_EQ(1u, idf_brlist.extensibleGroups().size());
  auto w_eg = idf_brlist.extensibleGroups()[0].cast<WorkspaceExtensibleGroup>();
  WorkspaceObject idf_branch = w_eg.getTarget(BranchListExtensibleFields::BranchName).get();

  // There should be only one equipment on the branch
  ASSERT_EQ(1u, idf_branch.extensibleGroups().size());
  auto w_eg2 = idf_branch.extensibleGroups()[0].cast<WorkspaceExtensibleGroup>();

  /* EXPECT_EQ(w_eg2.getString(BranchExtensibleFields::ComponentInletNodeName).get(), coilSystemCoolingWater.inletModelObject().get().nameString());
    EXPECT_EQ(w_eg2.getString(BranchExtensibleFields::ComponentOutletNodeName).get(), coilSystemCoolingWater.outletModelObject().get().nameString()); */
  EXPECT_EQ("AirLoopHVAC:OutdoorAirSystem", w_eg2.getString(BranchExtensibleFields::ComponentObjectType).get());

  EXPECT_EQ(coilSystemCoolingWater.inletModelObject().get().nameString(),
            idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::AirInletNodeName).get());
  EXPECT_EQ(coilSystemCoolingWater.outletModelObject().get().nameString(),
            idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::AirOutletNodeName).get());
  EXPECT_EQ(availabilitySchedule.nameString(), idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::AvailabilityScheduleName).get());
  EXPECT_EQ("Coil:Cooling:Water", idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::CoolingCoilObjectType).get());
  EXPECT_EQ(coilSystemCoolingWater.coolingCoil().nameString(), idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::CoolingCoilName).get());
  EXPECT_EQ("CoolReheat", idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::DehumidificationControlType).get());
  EXPECT_EQ("No", idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::RunonSensibleLoad).get());
  EXPECT_EQ("Yes", idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::RunonLatentLoad).get());
  EXPECT_EQ(1.0, idfCoilSystem.getDouble(CoilSystem_Cooling_WaterFields::MinimumAirToWaterTemperatureOffset).get());
  EXPECT_EQ("No", idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::EconomizerLockout).get());
  EXPECT_EQ(1.2, idfCoilSystem.getDouble(CoilSystem_Cooling_WaterFields::MinimumWaterLoopTemperatureForHeatRecovery).get());
  EXPECT_EQ(companionCoilUsedForHeatRecovery.nameString(),
            idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::CompanionCoilUsedForHeatRecovery).get());

  WorkspaceObject idf_coolingCoil = idfCoilSystem.getTarget(CoilSystem_Cooling_WaterFields::CoolingCoilName).get();
  WorkspaceObject idf_companionCoil = idfCoilSystem.getTarget(CoilSystem_Cooling_WaterFields::CompanionCoilUsedForHeatRecovery).get();

  EXPECT_EQ(coilSystemCoolingWater.coolingCoil().nameString(), idf_coolingCoil.getString(Coil_Cooling_WaterFields::Name).get());
  EXPECT_EQ("Always On Discrete", idf_coolingCoil.getString(Coil_Cooling_WaterFields::AvailabilityScheduleName).get());
  EXPECT_EQ("Autosize", idf_coolingCoil.getString(Coil_Cooling_WaterFields::DesignWaterFlowRate).get());
  EXPECT_EQ("Autosize", idf_coolingCoil.getString(Coil_Cooling_WaterFields::DesignAirFlowRate).get());
  EXPECT_EQ("Autosize", idf_coolingCoil.getString(Coil_Cooling_WaterFields::DesignInletWaterTemperature).get());
  EXPECT_EQ("Autosize", idf_coolingCoil.getString(Coil_Cooling_WaterFields::DesignInletAirTemperature).get());
  EXPECT_EQ("Autosize", idf_coolingCoil.getString(Coil_Cooling_WaterFields::DesignInletAirHumidityRatio).get());
  EXPECT_EQ("Autosize", idf_coolingCoil.getString(Coil_Cooling_WaterFields::DesignOutletAirHumidityRatio).get());

  EXPECT_EQ(cc.waterInletModelObject().get().nameString(), idf_coolingCoil.getString(Coil_Cooling_WaterFields::WaterInletNodeName).get());
  EXPECT_EQ("Cooling Coil Water Inlet Node", idf_coolingCoil.getString(Coil_Cooling_WaterFields::WaterInletNodeName).get());
  EXPECT_EQ(cc.waterOutletModelObject().get().nameString(), idf_coolingCoil.getString(Coil_Cooling_WaterFields::WaterOutletNodeName).get());
  EXPECT_EQ("Cooling Coil Water Outlet to Pipe Inlet Node", idf_coolingCoil.getString(Coil_Cooling_WaterFields::WaterOutletNodeName).get());
  EXPECT_EQ(idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::AirInletNodeName).get(),
            idf_coolingCoil.getString(Coil_Cooling_WaterFields::AirInletNodeName).get());

  EXPECT_EQ("Outdoor Air Inlet Node", idf_coolingCoil.getString(Coil_Cooling_WaterFields::AirInletNodeName).get());
  EXPECT_EQ(idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::AirOutletNodeName).get(),
            idf_coolingCoil.getString(Coil_Cooling_WaterFields::AirOutletNodeName).get());
  EXPECT_EQ("OA System Outlet to Mixed Node", idf_coolingCoil.getString(Coil_Cooling_WaterFields::AirOutletNodeName).get());

  EXPECT_EQ("SimpleAnalysis", idf_coolingCoil.getString(Coil_Cooling_WaterFields::TypeofAnalysis).get());
  EXPECT_EQ("CrossFlow", idf_coolingCoil.getString(Coil_Cooling_WaterFields::HeatExchangerConfiguration).get());
  EXPECT_TRUE(idf_coolingCoil.isEmpty(Coil_Cooling_WaterFields::CondensateCollectionWaterStorageTankName));
  EXPECT_TRUE(idf_coolingCoil.isEmpty(Coil_Cooling_WaterFields::DesignWaterTemperatureDifference));

  EXPECT_EQ(coilSystemCoolingWater.companionCoilUsedForHeatRecovery().get().nameString(),
            idf_companionCoil.getString(Coil_Cooling_WaterFields::Name).get());
  EXPECT_EQ("Always On Discrete", idf_companionCoil.getString(Coil_Cooling_WaterFields::AvailabilityScheduleName).get());
  EXPECT_EQ("Autosize", idf_companionCoil.getString(Coil_Cooling_WaterFields::DesignWaterFlowRate).get());
  EXPECT_EQ("Autosize", idf_companionCoil.getString(Coil_Cooling_WaterFields::DesignAirFlowRate).get());
  EXPECT_EQ("Autosize", idf_companionCoil.getString(Coil_Cooling_WaterFields::DesignInletWaterTemperature).get());
  EXPECT_EQ("Autosize", idf_companionCoil.getString(Coil_Cooling_WaterFields::DesignInletAirTemperature).get());
  EXPECT_EQ("Autosize", idf_companionCoil.getString(Coil_Cooling_WaterFields::DesignInletAirHumidityRatio).get());
  EXPECT_EQ("Autosize", idf_companionCoil.getString(Coil_Cooling_WaterFields::DesignOutletAirHumidityRatio).get());

  EXPECT_EQ(companionCoilUsedForHeatRecovery.waterInletModelObject().get().nameString(),
            idf_companionCoil.getString(Coil_Cooling_WaterFields::WaterInletNodeName).get());
  EXPECT_EQ("Companion Coil Water Outlet Node", idf_companionCoil.getString(Coil_Cooling_WaterFields::WaterOutletNodeName).get());
  EXPECT_EQ(companionCoilUsedForHeatRecovery.waterOutletModelObject().get().nameString(),
            idf_companionCoil.getString(Coil_Cooling_WaterFields::WaterOutletNodeName).get());
  EXPECT_EQ("Pipe Outlet to Companion Coil Water Inlet Node", idf_companionCoil.getString(Coil_Cooling_WaterFields::WaterInletNodeName).get());

  EXPECT_EQ(idfController.getString(Controller_OutdoorAirFields::ReliefAirOutletNodeName).get(),
            idf_companionCoil.getString(Coil_Cooling_WaterFields::AirInletNodeName).get());
  EXPECT_EQ("Return to OA System Node", idf_companionCoil.getString(Coil_Cooling_WaterFields::AirInletNodeName).get());
  EXPECT_EQ("Relief Node", idf_companionCoil.getString(Coil_Cooling_WaterFields::AirOutletNodeName).get());

  EXPECT_EQ("SimpleAnalysis", idf_companionCoil.getString(Coil_Cooling_WaterFields::TypeofAnalysis).get());
  EXPECT_EQ("CrossFlow", idf_companionCoil.getString(Coil_Cooling_WaterFields::HeatExchangerConfiguration).get());
  EXPECT_TRUE(idf_companionCoil.isEmpty(Coil_Cooling_WaterFields::CondensateCollectionWaterStorageTankName));
  EXPECT_TRUE(idf_companionCoil.isEmpty(Coil_Cooling_WaterFields::DesignWaterTemperatureDifference));

  EXPECT_EQ(0, w.getObjectsByType(IddObjectType::Controller_WaterCoil).size());
}

TEST_F(EnergyPlusFixture, ForwardTranslator_CoilSystemCoolingWater_HXAssisted) {
  ForwardTranslator ft;

  Model m;

  CoilSystemCoolingWaterHeatExchangerAssisted coilSystemHXAssisted(m);
  coilSystemHXAssisted.setName("HX Assisted");
  auto cc = coilSystemHXAssisted.coolingCoil().cast<CoilCoolingWater>();
  auto hx = coilSystemHXAssisted.heatExchanger().cast<HeatExchangerAirToAirSensibleAndLatent>();
  cc.setName("Primary Cooling Coil inside HXAssisted");
  hx.setName("HX AirToAir");
  CoilSystemCoolingWater coilSystemCoolingWater(m, coilSystemHXAssisted);
  coilSystemCoolingWater.setName("My CoilSystemCoolingWater");

  ScheduleConstant availabilitySchedule(m);
  availabilitySchedule.setName("availabilitySchedule");
  EXPECT_TRUE(coilSystemCoolingWater.setAvailabilitySchedule(availabilitySchedule));
  EXPECT_TRUE(coilSystemCoolingWater.setDehumidificationControlType("CoolReheat"));
  EXPECT_TRUE(coilSystemCoolingWater.setRunonSensibleLoad(false));  // Opposite from IDD default
  EXPECT_TRUE(coilSystemCoolingWater.setRunonLatentLoad(true));     // Opposite from IDD default
  EXPECT_TRUE(coilSystemCoolingWater.setMinimumAirToWaterTemperatureOffset(1.0));
  EXPECT_TRUE(coilSystemCoolingWater.setEconomizerLockout(false));  // Opposite from IDD default
  EXPECT_TRUE(coilSystemCoolingWater.setMinimumWaterLoopTemperatureForHeatRecovery(1.2));
  CoilCoolingWater companionCoilUsedForHeatRecovery(m);
  companionCoilUsedForHeatRecovery.setName("CompanionCoilUsedForHeatRecovery");
  EXPECT_TRUE(coilSystemCoolingWater.setCompanionCoilUsedForHeatRecovery(companionCoilUsedForHeatRecovery));

  AirLoopHVAC airLoop(m);
  Node supplyOutletNode = airLoop.supplyOutletNode();
  ControllerOutdoorAir controller1(m);
  AirLoopHVACOutdoorAirSystem oaSystem(m, controller1);
  EXPECT_TRUE(oaSystem.addToNode(supplyOutletNode));
  Node oaNode = oaSystem.outboardOANode().get();
  EXPECT_TRUE(coilSystemCoolingWater.addToNode(oaNode));
  Node reliefNode = oaSystem.outboardReliefNode().get();
  EXPECT_TRUE(companionCoilUsedForHeatRecovery.addToNode(reliefNode));

  oaNode.setName("Outdoor Air Inlet Node");
  reliefNode.setName("Relief Node");
  oaSystem.reliefAirModelObject()->setName("Return to OA System Node");
  oaSystem.outdoorAirModelObject()->setName("OA System Outlet to Mixed Node");
  airLoop.mixedAirNode()->setName("Mixed Air Node");
  airLoop.supplyInletNode().setName("Supply Inlet Node");
  airLoop.supplyOutletNode().setName("Supply Outlet Node");

  // They must be connected to a PlantLoop too
  PlantLoop chw_p(m);
  chw_p.addDemandBranchForComponent(cc);
  PipeAdiabatic pipe(m);
  Node coolingOutlet = cc.waterOutletModelObject()->cast<Node>();
  EXPECT_TRUE(pipe.addToNode(coolingOutlet));
  Node pipeOutlet = pipe.outletModelObject()->cast<Node>();
  EXPECT_TRUE(companionCoilUsedForHeatRecovery.addToNode(pipeOutlet));

  cc.waterInletModelObject()->setName("Cooling Coil Water Inlet Node");
  cc.waterOutletModelObject()->setName("Cooling Coil Water Outlet to Pipe Inlet Node");
  pipe.outletModelObject()->setName("Pipe Outlet to Companion Coil Water Inlet Node");
  companionCoilUsedForHeatRecovery.waterOutletModelObject()->setName("Companion Coil Water Outlet Node");

  const Workspace w = ft.translateModel(m);

  const auto idfCoilSystems = w.getObjectsByType(IddObjectType::CoilSystem_Cooling_Water);
  ASSERT_EQ(1u, idfCoilSystems.size());
  const auto& idfCoilSystem = idfCoilSystems.front();

  WorkspaceObjectVector idfCoils(w.getObjectsByType(IddObjectType::Coil_Cooling_Water));
  ASSERT_EQ(2u, idfCoils.size());

  WorkspaceObjectVector idfControllers(w.getObjectsByType(IddObjectType::Controller_OutdoorAir));
  ASSERT_EQ(1u, idfControllers.size());
  const auto& idfController = idfControllers.front();

  // Go from AirLoopHVAC to BranchList to Branch
  WorkspaceObjectVector idf_airloops = w.getObjectsByType(IddObjectType::AirLoopHVAC);
  ASSERT_EQ(1u, idf_airloops.size());

  WorkspaceObject& idf_airLoopHVAC = idf_airloops.front();
  WorkspaceObject idf_brlist = idf_airLoopHVAC.getTarget(AirLoopHVACFields::BranchListName).get();

  // Should have one branch only
  ASSERT_EQ(1u, idf_brlist.extensibleGroups().size());
  auto w_eg = idf_brlist.extensibleGroups()[0].cast<WorkspaceExtensibleGroup>();
  WorkspaceObject idf_branch = w_eg.getTarget(BranchListExtensibleFields::BranchName).get();

  // There should be only one equipment on the branch
  ASSERT_EQ(1u, idf_branch.extensibleGroups().size());
  auto w_eg2 = idf_branch.extensibleGroups()[0].cast<WorkspaceExtensibleGroup>();

  /* EXPECT_EQ(w_eg2.getString(BranchExtensibleFields::ComponentInletNodeName).get(), coilSystemCoolingWater.inletModelObject().get().nameString());
    EXPECT_EQ(w_eg2.getString(BranchExtensibleFields::ComponentOutletNodeName).get(), coilSystemCoolingWater.outletModelObject().get().nameString()); */
  EXPECT_EQ("AirLoopHVAC:OutdoorAirSystem", w_eg2.getString(BranchExtensibleFields::ComponentObjectType).get());

  EXPECT_EQ(coilSystemCoolingWater.inletModelObject().get().nameString(),
            idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::AirInletNodeName).get());
  EXPECT_EQ(coilSystemCoolingWater.outletModelObject().get().nameString(),
            idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::AirOutletNodeName).get());
  EXPECT_EQ(availabilitySchedule.nameString(), idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::AvailabilityScheduleName).get());
  EXPECT_EQ("CoilSystem:Cooling:Water:HeatExchangerAssisted", idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::CoolingCoilObjectType).get());
  EXPECT_EQ(coilSystemCoolingWater.coolingCoil().nameString(), idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::CoolingCoilName).get());
  EXPECT_EQ("CoolReheat", idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::DehumidificationControlType).get());
  EXPECT_EQ("No", idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::RunonSensibleLoad).get());
  EXPECT_EQ("Yes", idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::RunonLatentLoad).get());
  EXPECT_EQ(1.0, idfCoilSystem.getDouble(CoilSystem_Cooling_WaterFields::MinimumAirToWaterTemperatureOffset).get());
  EXPECT_EQ("No", idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::EconomizerLockout).get());
  EXPECT_EQ(1.2, idfCoilSystem.getDouble(CoilSystem_Cooling_WaterFields::MinimumWaterLoopTemperatureForHeatRecovery).get());
  EXPECT_EQ(companionCoilUsedForHeatRecovery.nameString(),
            idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::CompanionCoilUsedForHeatRecovery).get());

  WorkspaceObject idf_hxAssisted = idfCoilSystem.getTarget(CoilSystem_Cooling_WaterFields::CoolingCoilName).get();
  EXPECT_EQ("HeatExchanger:AirToAir:SensibleAndLatent",
            idf_hxAssisted.getString(CoilSystem_Cooling_Water_HeatExchangerAssistedFields::HeatExchangerObjectType).get());
  EXPECT_EQ("HX AirToAir", idf_hxAssisted.getString(CoilSystem_Cooling_Water_HeatExchangerAssistedFields::HeatExchangerName).get());
  EXPECT_EQ("Coil:Cooling:Water", idf_hxAssisted.getString(CoilSystem_Cooling_Water_HeatExchangerAssistedFields::CoolingCoilObjectType).get());
  EXPECT_EQ("Primary Cooling Coil inside HXAssisted",
            idf_hxAssisted.getString(CoilSystem_Cooling_Water_HeatExchangerAssistedFields::CoolingCoilName).get());

  // This fails for some reason?
  // auto idf_hx = idf_hxAssisted.getTarget(CoilSystem_Cooling_Water_HeatExchangerAssistedFields::HeatExchangerName).get();
  ASSERT_EQ(1, w.getObjectsByType(IddObjectType::HeatExchanger_AirToAir_SensibleAndLatent).size());
  auto idf_hx = w.getObjectsByType(IddObjectType::HeatExchanger_AirToAir_SensibleAndLatent).front();

  EXPECT_EQ(hx.nameString(), idf_hx.getString(HeatExchanger_AirToAir_SensibleAndLatentFields::Name).get());
  EXPECT_EQ(idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::AirInletNodeName).get(),
            idf_hx.getString(HeatExchanger_AirToAir_SensibleAndLatentFields::SupplyAirInletNodeName).get());
  EXPECT_EQ("Outdoor Air Inlet Node", idf_hx.getString(HeatExchanger_AirToAir_SensibleAndLatentFields::SupplyAirInletNodeName).get());

  EXPECT_EQ(idfCoilSystem.getString(CoilSystem_Cooling_WaterFields::AirOutletNodeName).get(),
            idf_hx.getString(HeatExchanger_AirToAir_SensibleAndLatentFields::ExhaustAirOutletNodeName).get());
  EXPECT_EQ("OA System Outlet to Mixed Node", idf_hx.getString(HeatExchanger_AirToAir_SensibleAndLatentFields::ExhaustAirOutletNodeName).get());

  EXPECT_EQ("HX Assisted HX Supply Air Outlet - Cooling Inlet Node",
            idf_hx.getString(HeatExchanger_AirToAir_SensibleAndLatentFields::SupplyAirOutletNodeName).get());
  EXPECT_EQ("HX Assisted HX Exhaust Air Inlet - Cooling Outlet Node",
            idf_hx.getString(HeatExchanger_AirToAir_SensibleAndLatentFields::ExhaustAirInletNodeName).get());

  WorkspaceObject idf_coolingCoil = idf_hxAssisted.getTarget(CoilSystem_Cooling_Water_HeatExchangerAssistedFields::CoolingCoilName).get();
  WorkspaceObject idf_companionCoil = idfCoilSystem.getTarget(CoilSystem_Cooling_WaterFields::CompanionCoilUsedForHeatRecovery).get();

  EXPECT_EQ("Primary Cooling Coil inside HXAssisted", idf_coolingCoil.getString(Coil_Cooling_WaterFields::Name).get());
  EXPECT_EQ("Always On Discrete", idf_coolingCoil.getString(Coil_Cooling_WaterFields::AvailabilityScheduleName).get());
  EXPECT_EQ("Autosize", idf_coolingCoil.getString(Coil_Cooling_WaterFields::DesignWaterFlowRate).get());
  EXPECT_EQ("Autosize", idf_coolingCoil.getString(Coil_Cooling_WaterFields::DesignAirFlowRate).get());
  EXPECT_EQ("Autosize", idf_coolingCoil.getString(Coil_Cooling_WaterFields::DesignInletWaterTemperature).get());
  EXPECT_EQ("Autosize", idf_coolingCoil.getString(Coil_Cooling_WaterFields::DesignInletAirTemperature).get());
  EXPECT_EQ("Autosize", idf_coolingCoil.getString(Coil_Cooling_WaterFields::DesignInletAirHumidityRatio).get());
  EXPECT_EQ("Autosize", idf_coolingCoil.getString(Coil_Cooling_WaterFields::DesignOutletAirHumidityRatio).get());

  EXPECT_EQ(cc.waterInletModelObject().get().nameString(), idf_coolingCoil.getString(Coil_Cooling_WaterFields::WaterInletNodeName).get());
  EXPECT_EQ("Cooling Coil Water Inlet Node", idf_coolingCoil.getString(Coil_Cooling_WaterFields::WaterInletNodeName).get());
  EXPECT_EQ(cc.waterOutletModelObject().get().nameString(), idf_coolingCoil.getString(Coil_Cooling_WaterFields::WaterOutletNodeName).get());
  EXPECT_EQ("Cooling Coil Water Outlet to Pipe Inlet Node", idf_coolingCoil.getString(Coil_Cooling_WaterFields::WaterOutletNodeName).get());
  EXPECT_EQ(idf_hx.getString(HeatExchanger_AirToAir_SensibleAndLatentFields::SupplyAirOutletNodeName).get(),
            idf_coolingCoil.getString(Coil_Cooling_WaterFields::AirInletNodeName).get());
  EXPECT_EQ("HX Assisted HX Supply Air Outlet - Cooling Inlet Node", idf_coolingCoil.getString(Coil_Cooling_WaterFields::AirInletNodeName).get());
  EXPECT_EQ(idf_hx.getString(HeatExchanger_AirToAir_SensibleAndLatentFields::ExhaustAirInletNodeName).get(),
            idf_coolingCoil.getString(Coil_Cooling_WaterFields::AirOutletNodeName).get());
  EXPECT_EQ("HX Assisted HX Exhaust Air Inlet - Cooling Outlet Node", idf_coolingCoil.getString(Coil_Cooling_WaterFields::AirOutletNodeName).get());

  EXPECT_EQ("SimpleAnalysis", idf_coolingCoil.getString(Coil_Cooling_WaterFields::TypeofAnalysis).get());
  EXPECT_EQ("CrossFlow", idf_coolingCoil.getString(Coil_Cooling_WaterFields::HeatExchangerConfiguration).get());
  EXPECT_TRUE(idf_coolingCoil.isEmpty(Coil_Cooling_WaterFields::CondensateCollectionWaterStorageTankName));
  EXPECT_TRUE(idf_coolingCoil.isEmpty(Coil_Cooling_WaterFields::DesignWaterTemperatureDifference));

  EXPECT_EQ(coilSystemCoolingWater.companionCoilUsedForHeatRecovery().get().nameString(),
            idf_companionCoil.getString(Coil_Cooling_WaterFields::Name).get());
  EXPECT_EQ("Always On Discrete", idf_companionCoil.getString(Coil_Cooling_WaterFields::AvailabilityScheduleName).get());
  EXPECT_EQ("Autosize", idf_companionCoil.getString(Coil_Cooling_WaterFields::DesignWaterFlowRate).get());
  EXPECT_EQ("Autosize", idf_companionCoil.getString(Coil_Cooling_WaterFields::DesignAirFlowRate).get());
  EXPECT_EQ("Autosize", idf_companionCoil.getString(Coil_Cooling_WaterFields::DesignInletWaterTemperature).get());
  EXPECT_EQ("Autosize", idf_companionCoil.getString(Coil_Cooling_WaterFields::DesignInletAirTemperature).get());
  EXPECT_EQ("Autosize", idf_companionCoil.getString(Coil_Cooling_WaterFields::DesignInletAirHumidityRatio).get());
  EXPECT_EQ("Autosize", idf_companionCoil.getString(Coil_Cooling_WaterFields::DesignOutletAirHumidityRatio).get());

  EXPECT_EQ(companionCoilUsedForHeatRecovery.waterInletModelObject().get().nameString(),
            idf_companionCoil.getString(Coil_Cooling_WaterFields::WaterInletNodeName).get());
  EXPECT_EQ("Companion Coil Water Outlet Node", idf_companionCoil.getString(Coil_Cooling_WaterFields::WaterOutletNodeName).get());
  EXPECT_EQ(companionCoilUsedForHeatRecovery.waterOutletModelObject().get().nameString(),
            idf_companionCoil.getString(Coil_Cooling_WaterFields::WaterOutletNodeName).get());
  EXPECT_EQ("Pipe Outlet to Companion Coil Water Inlet Node", idf_companionCoil.getString(Coil_Cooling_WaterFields::WaterInletNodeName).get());

  EXPECT_EQ(idfController.getString(Controller_OutdoorAirFields::ReliefAirOutletNodeName).get(),
            idf_companionCoil.getString(Coil_Cooling_WaterFields::AirInletNodeName).get());
  EXPECT_EQ("Return to OA System Node", idf_companionCoil.getString(Coil_Cooling_WaterFields::AirInletNodeName).get());
  EXPECT_EQ("Relief Node", idf_companionCoil.getString(Coil_Cooling_WaterFields::AirOutletNodeName).get());

  EXPECT_EQ("SimpleAnalysis", idf_companionCoil.getString(Coil_Cooling_WaterFields::TypeofAnalysis).get());
  EXPECT_EQ("CrossFlow", idf_companionCoil.getString(Coil_Cooling_WaterFields::HeatExchangerConfiguration).get());
  EXPECT_TRUE(idf_companionCoil.isEmpty(Coil_Cooling_WaterFields::CondensateCollectionWaterStorageTankName));
  EXPECT_TRUE(idf_companionCoil.isEmpty(Coil_Cooling_WaterFields::DesignWaterTemperatureDifference));

  EXPECT_EQ(0, w.getObjectsByType(IddObjectType::Controller_WaterCoil).size());
}
