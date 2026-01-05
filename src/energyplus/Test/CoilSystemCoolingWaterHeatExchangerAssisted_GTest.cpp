/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "EnergyPlusFixture.hpp"

#include "../ForwardTranslator.hpp"

#include "../../model/Model.hpp"
#include "../../model/CoilSystemCoolingWaterHeatExchangerAssisted.hpp"
#include "../../model/CoilSystemCoolingWaterHeatExchangerAssisted_Impl.hpp"
#include "../../model/CoilCoolingWater.hpp"
#include "../../model/CoilCoolingWater_Impl.hpp"
#include "../../model/HeatExchangerAirToAirSensibleAndLatent.hpp"
#include "../../model/HeatExchangerAirToAirSensibleAndLatent_Impl.hpp"

#include "../../model/AirLoopHVAC.hpp"
#include "../../model/AirLoopHVACUnitarySystem.hpp"
#include "../../model/Node.hpp"

#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idf/IdfObject_Impl.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"
#include "../../utilities/idf/WorkspaceObject_Impl.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include "../../utilities/idf/WorkspaceExtensibleGroup.hpp"

#include <utilities/idd/CoilSystem_Cooling_Water_HeatExchangerAssisted_FieldEnums.hxx>
#include <utilities/idd/Coil_Cooling_Water_FieldEnums.hxx>
#include <utilities/idd/HeatExchanger_AirToAir_SensibleAndLatent_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_FieldEnums.hxx>
#include <utilities/idd/BranchList_FieldEnums.hxx>
#include <utilities/idd/Branch_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_UnitarySystem_FieldEnums.hxx>
#include <utilities/idd/Controller_WaterCoil_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::energyplus;
using namespace openstudio::model;
using namespace openstudio;

TEST_F(EnergyPlusFixture, ForwardTranslator_CoilSystemCoolingWaterHeatExchangerAssisted_Unitary) {
  Model m;
  CoilSystemCoolingWaterHeatExchangerAssisted coil(m);
  coil.setName("My CoilSystemCoolingWaterHeatExchangerAssisted");

  // put it inside a Unitary, and put Unitary on an AirLoopHVAC so it gets translated
  AirLoopHVACUnitarySystem unitary(m);
  unitary.setCoolingCoil(coil);
  AirLoopHVAC airLoop(m);
  Node supplyOutletNode = airLoop.supplyOutletNode();
  unitary.addToNode(supplyOutletNode);
  ASSERT_TRUE(unitary.inletNode());
  EXPECT_TRUE(unitary.inletNode()->setName("Coil Air Inlet Node"));
  ASSERT_TRUE(unitary.outletNode());
  EXPECT_TRUE(unitary.outletNode()->setName("Coil Air Outlet Node"));

  // They must be connected to a PlantLoop too
  PlantLoop chw_p(m);
  chw_p.addDemandBranchForComponent(coil.coolingCoil());

  ForwardTranslator ft;
  Workspace w = ft.translateModel(m);

  WorkspaceObjectVector idfUnitarys(w.getObjectsByType(IddObjectType::AirLoopHVAC_UnitarySystem));
  ASSERT_EQ(1u, idfUnitarys.size());
  WorkspaceObject idfUnitary(idfUnitarys[0]);

  WorkspaceObjectVector idfCoilSystems(w.getObjectsByType(IddObjectType::CoilSystem_Cooling_Water_HeatExchangerAssisted));
  ASSERT_EQ(1u, idfCoilSystems.size());
  WorkspaceObject idfCoilSystem(idfCoilSystems[0]);

  WorkspaceObjectVector idfHXs(w.getObjectsByType(IddObjectType::HeatExchanger_AirToAir_SensibleAndLatent));
  ASSERT_EQ(1u, idfHXs.size());
  WorkspaceObject idfHX(idfHXs[0]);

  WorkspaceObjectVector idfCoils(w.getObjectsByType(IddObjectType::Coil_Cooling_Water));
  ASSERT_EQ(1u, idfCoils.size());
  WorkspaceObject idfCoil(idfCoils[0]);

  // Check that the Unitary ends up with the CoilSystemCoolingWaterHeatExchangerAssisted
  EXPECT_EQ("CoilSystem:Cooling:Water:HeatExchangerAssisted", idfUnitary.getString(AirLoopHVAC_UnitarySystemFields::CoolingCoilObjectType).get());
  EXPECT_EQ(idfCoilSystem.nameString(), idfUnitary.getString(AirLoopHVAC_UnitarySystemFields::CoolingCoilName).get());

  // Since the Unitary only has a Cooling Coil (no fan, not HC / Suppl HC), the nodes should match
  EXPECT_EQ(idfUnitary.getString(AirLoopHVAC_UnitarySystemFields::AirInletNodeName).get(),
            idfHX.getString(HeatExchanger_AirToAir_SensibleAndLatentFields::SupplyAirInletNodeName).get());

  EXPECT_EQ(idfUnitary.getString(AirLoopHVAC_UnitarySystemFields::AirOutletNodeName).get(),
            idfHX.getString(HeatExchanger_AirToAir_SensibleAndLatentFields::ExhaustAirOutletNodeName).get());

  EXPECT_EQ("My CoilSystemCoolingWaterHeatExchangerAssisted",
            idfCoilSystem.getString(CoilSystem_Cooling_Water_HeatExchangerAssistedFields::Name).get());
  EXPECT_EQ("HeatExchanger:AirToAir:SensibleAndLatent",
            idfCoilSystem.getString(CoilSystem_Cooling_Water_HeatExchangerAssistedFields::HeatExchangerObjectType).get());
  EXPECT_EQ(coil.heatExchanger().nameString(),
            idfCoilSystem.getString(CoilSystem_Cooling_Water_HeatExchangerAssistedFields::HeatExchangerName).get());
  EXPECT_EQ("Coil:Cooling:Water", idfCoilSystem.getString(CoilSystem_Cooling_Water_HeatExchangerAssistedFields::CoolingCoilObjectType).get());
  EXPECT_EQ(coil.coolingCoil().nameString(), idfCoilSystem.getString(CoilSystem_Cooling_Water_HeatExchangerAssistedFields::CoolingCoilName).get());

  EXPECT_EQ(coil.coolingCoil().nameString(), idfCoil.getString(Coil_Cooling_WaterFields::Name).get());
  EXPECT_EQ("Always On Discrete", idfCoil.getString(Coil_Cooling_WaterFields::AvailabilityScheduleName).get());
  EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignWaterFlowRate).get());
  EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignAirFlowRate).get());
  EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignInletWaterTemperature).get());
  EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignInletAirTemperature).get());
  EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignInletAirHumidityRatio).get());
  EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignOutletAirHumidityRatio).get());
  EXPECT_EQ(coil.coolingCoil().waterInletModelObject().get().nameString(), idfCoil.getString(Coil_Cooling_WaterFields::WaterInletNodeName).get());
  EXPECT_EQ(coil.coolingCoil().waterOutletModelObject().get().nameString(), idfCoil.getString(Coil_Cooling_WaterFields::WaterOutletNodeName).get());
  EXPECT_EQ(idfHX.getString(HeatExchanger_AirToAir_SensibleAndLatentFields::SupplyAirOutletNodeName).get(),
            idfCoil.getString(Coil_Cooling_WaterFields::AirInletNodeName).get());
  EXPECT_EQ(idfHX.getString(HeatExchanger_AirToAir_SensibleAndLatentFields::ExhaustAirInletNodeName).get(),
            idfCoil.getString(Coil_Cooling_WaterFields::AirOutletNodeName).get());
  EXPECT_EQ("SimpleAnalysis", idfCoil.getString(Coil_Cooling_WaterFields::TypeofAnalysis).get());
  EXPECT_EQ("CrossFlow", idfCoil.getString(Coil_Cooling_WaterFields::HeatExchangerConfiguration).get());
  EXPECT_TRUE(idfCoil.isEmpty(Coil_Cooling_WaterFields::CondensateCollectionWaterStorageTankName));
  EXPECT_TRUE(idfCoil.isEmpty(Coil_Cooling_WaterFields::DesignWaterTemperatureDifference));

  // Check Controller:WaterCoil created by coil.addToNode
  EXPECT_EQ(1, w.getObjectsByType(IddObjectType::Controller_WaterCoil).size());
}

TEST_F(EnergyPlusFixture, ForwardTranslator_CoilSystemCoolingWaterHeatExchangerAssisted_AirLoopHVAC) {
  // connect coil system to air loop, and then connect coil to plant
  {
    Model m;
    CoilSystemCoolingWaterHeatExchangerAssisted coil(m);
    EXPECT_FALSE(coil.coolingCoil().waterInletModelObject());

    // put it on an AirLoopHVAC
    AirLoopHVAC airLoop(m);
    Node supplyOutletNode = airLoop.supplyOutletNode();
    EXPECT_TRUE(coil.addToNode(supplyOutletNode));
    EXPECT_FALSE(coil.coolingCoil().waterInletModelObject());

    // They must be connected to a PlantLoop too
    PlantLoop chw_p(m);
    chw_p.addDemandBranchForComponent(coil.coolingCoil());
    EXPECT_TRUE(coil.coolingCoil().waterInletModelObject());

    ForwardTranslator ft;
    Workspace w = ft.translateModel(m);

    WorkspaceObjectVector idfCoilSystems(w.getObjectsByType(IddObjectType::CoilSystem_Cooling_Water_HeatExchangerAssisted));
    ASSERT_EQ(1u, idfCoilSystems.size());
    WorkspaceObject idfCoilSystem(idfCoilSystems[0]);

    WorkspaceObjectVector idfCoils(w.getObjectsByType(IddObjectType::Coil_Cooling_Water));
    ASSERT_EQ(1u, idfCoils.size());
    WorkspaceObject idfCoil(idfCoils[0]);

    WorkspaceObjectVector idfHXs(w.getObjectsByType(IddObjectType::HeatExchanger_AirToAir_SensibleAndLatent));
    ASSERT_EQ(1u, idfHXs.size());
    WorkspaceObject idfHX(idfHXs[0]);

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

    EXPECT_EQ(w_eg2.getString(BranchExtensibleFields::ComponentInletNodeName).get(), coil.inletModelObject().get().nameString());
    EXPECT_EQ(w_eg2.getString(BranchExtensibleFields::ComponentOutletNodeName).get(), coil.outletModelObject().get().nameString());
    EXPECT_EQ("CoilSystem:Cooling:Water:HeatExchangerAssisted", w_eg2.getString(BranchExtensibleFields::ComponentObjectType).get());

    EXPECT_EQ(coil.nameString(), idfCoilSystem.getString(CoilSystem_Cooling_Water_HeatExchangerAssistedFields::Name).get());
    EXPECT_EQ("HeatExchanger:AirToAir:SensibleAndLatent",
              idfCoilSystem.getString(CoilSystem_Cooling_Water_HeatExchangerAssistedFields::HeatExchangerObjectType).get());
    EXPECT_EQ(coil.heatExchanger().nameString(),
              idfCoilSystem.getString(CoilSystem_Cooling_Water_HeatExchangerAssistedFields::HeatExchangerName).get());
    EXPECT_EQ("Coil:Cooling:Water", idfCoilSystem.getString(CoilSystem_Cooling_Water_HeatExchangerAssistedFields::CoolingCoilObjectType).get());
    EXPECT_EQ(coil.coolingCoil().nameString(), idfCoilSystem.getString(CoilSystem_Cooling_Water_HeatExchangerAssistedFields::CoolingCoilName).get());

    EXPECT_EQ(coil.coolingCoil().nameString(), idfCoil.getString(Coil_Cooling_WaterFields::Name).get());
    EXPECT_EQ("Always On Discrete", idfCoil.getString(Coil_Cooling_WaterFields::AvailabilityScheduleName).get());
    EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignWaterFlowRate).get());
    EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignAirFlowRate).get());
    EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignInletWaterTemperature).get());
    EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignInletAirTemperature).get());
    EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignInletAirHumidityRatio).get());
    EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignOutletAirHumidityRatio).get());
    EXPECT_EQ(coil.coolingCoil().waterInletModelObject().get().nameString(), idfCoil.getString(Coil_Cooling_WaterFields::WaterInletNodeName).get());
    EXPECT_EQ(coil.coolingCoil().waterOutletModelObject().get().nameString(), idfCoil.getString(Coil_Cooling_WaterFields::WaterOutletNodeName).get());
    EXPECT_EQ(idfHX.getString(HeatExchanger_AirToAir_SensibleAndLatentFields::SupplyAirOutletNodeName).get(),
              idfCoil.getString(Coil_Cooling_WaterFields::AirInletNodeName).get());
    EXPECT_EQ(idfHX.getString(HeatExchanger_AirToAir_SensibleAndLatentFields::ExhaustAirInletNodeName).get(),
              idfCoil.getString(Coil_Cooling_WaterFields::AirOutletNodeName).get());
    EXPECT_EQ("SimpleAnalysis", idfCoil.getString(Coil_Cooling_WaterFields::TypeofAnalysis).get());
    EXPECT_EQ("CrossFlow", idfCoil.getString(Coil_Cooling_WaterFields::HeatExchangerConfiguration).get());
    EXPECT_TRUE(idfCoil.isEmpty(Coil_Cooling_WaterFields::CondensateCollectionWaterStorageTankName));
    EXPECT_TRUE(idfCoil.isEmpty(Coil_Cooling_WaterFields::DesignWaterTemperatureDifference));

    // Check Controller:WaterCoil created by coil.addToNode
    EXPECT_EQ(1, w.getObjectsByType(IddObjectType::Controller_WaterCoil).size());
  }

  // Test for #4895: connect coil to plant, and then connect coil system to air loop
  {
    Model m;
    CoilSystemCoolingWaterHeatExchangerAssisted coil(m);
    EXPECT_FALSE(coil.coolingCoil().waterInletModelObject());

    // They must be connected to a PlantLoop too
    PlantLoop chw_p(m);
    chw_p.addDemandBranchForComponent(coil.coolingCoil());
    EXPECT_TRUE(coil.coolingCoil().waterInletModelObject());

    // put it on an AirLoopHVAC
    AirLoopHVAC airLoop(m);
    Node supplyOutletNode = airLoop.supplyOutletNode();
    EXPECT_TRUE(coil.addToNode(supplyOutletNode));
    EXPECT_TRUE(coil.coolingCoil().waterInletModelObject());

    ForwardTranslator ft;
    Workspace w = ft.translateModel(m);

    WorkspaceObjectVector idfCoilSystems(w.getObjectsByType(IddObjectType::CoilSystem_Cooling_Water_HeatExchangerAssisted));
    ASSERT_EQ(1u, idfCoilSystems.size());
    WorkspaceObject idfCoilSystem(idfCoilSystems[0]);

    WorkspaceObjectVector idfCoils(w.getObjectsByType(IddObjectType::Coil_Cooling_Water));
    ASSERT_EQ(1u, idfCoils.size());
    WorkspaceObject idfCoil(idfCoils[0]);

    WorkspaceObjectVector idfHXs(w.getObjectsByType(IddObjectType::HeatExchanger_AirToAir_SensibleAndLatent));
    ASSERT_EQ(1u, idfHXs.size());
    WorkspaceObject idfHX(idfHXs[0]);

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

    EXPECT_EQ(w_eg2.getString(BranchExtensibleFields::ComponentInletNodeName).get(), coil.inletModelObject().get().nameString());
    EXPECT_EQ(w_eg2.getString(BranchExtensibleFields::ComponentOutletNodeName).get(), coil.outletModelObject().get().nameString());
    EXPECT_EQ("CoilSystem:Cooling:Water:HeatExchangerAssisted", w_eg2.getString(BranchExtensibleFields::ComponentObjectType).get());

    EXPECT_EQ(coil.nameString(), idfCoilSystem.getString(CoilSystem_Cooling_Water_HeatExchangerAssistedFields::Name).get());
    EXPECT_EQ("HeatExchanger:AirToAir:SensibleAndLatent",
              idfCoilSystem.getString(CoilSystem_Cooling_Water_HeatExchangerAssistedFields::HeatExchangerObjectType).get());
    EXPECT_EQ(coil.heatExchanger().nameString(),
              idfCoilSystem.getString(CoilSystem_Cooling_Water_HeatExchangerAssistedFields::HeatExchangerName).get());
    EXPECT_EQ("Coil:Cooling:Water", idfCoilSystem.getString(CoilSystem_Cooling_Water_HeatExchangerAssistedFields::CoolingCoilObjectType).get());
    EXPECT_EQ(coil.coolingCoil().nameString(), idfCoilSystem.getString(CoilSystem_Cooling_Water_HeatExchangerAssistedFields::CoolingCoilName).get());

    EXPECT_EQ(coil.coolingCoil().nameString(), idfCoil.getString(Coil_Cooling_WaterFields::Name).get());
    EXPECT_EQ("Always On Discrete", idfCoil.getString(Coil_Cooling_WaterFields::AvailabilityScheduleName).get());
    EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignWaterFlowRate).get());
    EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignAirFlowRate).get());
    EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignInletWaterTemperature).get());
    EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignInletAirTemperature).get());
    EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignInletAirHumidityRatio).get());
    EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignOutletAirHumidityRatio).get());
    EXPECT_EQ(coil.coolingCoil().waterInletModelObject().get().nameString(), idfCoil.getString(Coil_Cooling_WaterFields::WaterInletNodeName).get());
    EXPECT_EQ(coil.coolingCoil().waterOutletModelObject().get().nameString(), idfCoil.getString(Coil_Cooling_WaterFields::WaterOutletNodeName).get());
    EXPECT_EQ(idfHX.getString(HeatExchanger_AirToAir_SensibleAndLatentFields::SupplyAirOutletNodeName).get(),
              idfCoil.getString(Coil_Cooling_WaterFields::AirInletNodeName).get());
    EXPECT_EQ(idfHX.getString(HeatExchanger_AirToAir_SensibleAndLatentFields::ExhaustAirInletNodeName).get(),
              idfCoil.getString(Coil_Cooling_WaterFields::AirOutletNodeName).get());
    EXPECT_EQ("SimpleAnalysis", idfCoil.getString(Coil_Cooling_WaterFields::TypeofAnalysis).get());
    EXPECT_EQ("CrossFlow", idfCoil.getString(Coil_Cooling_WaterFields::HeatExchangerConfiguration).get());
    EXPECT_TRUE(idfCoil.isEmpty(Coil_Cooling_WaterFields::CondensateCollectionWaterStorageTankName));
    EXPECT_TRUE(idfCoil.isEmpty(Coil_Cooling_WaterFields::DesignWaterTemperatureDifference));

    // Check Controller:WaterCoil created by coil.addToNode
    EXPECT_EQ(1, w.getObjectsByType(IddObjectType::Controller_WaterCoil).size());
  }
}
