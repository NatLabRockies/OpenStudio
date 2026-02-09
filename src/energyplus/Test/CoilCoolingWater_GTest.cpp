/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "EnergyPlusFixture.hpp"

#include "../ForwardTranslator.hpp"
#include "../ReverseTranslator.hpp"

#include "../../model/Model.hpp"
#include "../../model/CoilCoolingWater.hpp"
#include "../../model/CoilCoolingWater_Impl.hpp"

#include "../../model/AirLoopHVAC.hpp"
#include "../../model/AirLoopHVACUnitarySystem.hpp"
#include "../../model/Node.hpp"
#include "../../model/Schedule.hpp"
#include "../../model/ScheduleConstant.hpp"
#include "../../model/ScheduleConstant_Impl.hpp"

#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idf/IdfObject_Impl.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"
#include "../../utilities/idf/WorkspaceObject_Impl.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include "../../utilities/idf/WorkspaceExtensibleGroup.hpp"

#include <utilities/idd/Coil_Cooling_Water_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_FieldEnums.hxx>
#include <utilities/idd/BranchList_FieldEnums.hxx>
#include <utilities/idd/Branch_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_UnitarySystem_FieldEnums.hxx>
#include <utilities/idd/Controller_WaterCoil_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::energyplus;
using namespace openstudio::model;
using namespace openstudio;

TEST_F(EnergyPlusFixture, ForwardTranslator_CoilCoolingWater_Unitary) {
  Model m;
  CoilCoolingWater coil(m);
  coil.setName("My CoilCoolingWater");

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
  chw_p.addDemandBranchForComponent(coil);
  coil.waterInletModelObject()->setName("Coil Water Inlet Node");
  coil.waterOutletModelObject()->setName("Coil Water Outlet Node");

  ForwardTranslator ft;
  Workspace w = ft.translateModel(m);

  WorkspaceObjectVector idfUnitarys(w.getObjectsByType(IddObjectType::AirLoopHVAC_UnitarySystem));
  ASSERT_EQ(1u, idfUnitarys.size());
  WorkspaceObject idfUnitary(idfUnitarys[0]);

  WorkspaceObjectVector idfCoils(w.getObjectsByType(IddObjectType::Coil_Cooling_Water));
  ASSERT_EQ(1u, idfCoils.size());
  WorkspaceObject idfCoil(idfCoils[0]);

  // Check that the Unitary ends up with the CoilCoolingWater
  EXPECT_EQ("Coil:Cooling:Water", idfUnitary.getString(AirLoopHVAC_UnitarySystemFields::CoolingCoilObjectType).get());
  EXPECT_EQ(idfCoil.nameString(), idfUnitary.getString(AirLoopHVAC_UnitarySystemFields::CoolingCoilName).get());

  // Since the Unitary only has a Cooling Coil (no fan, not HC / Suppl HC), the nodes should match
  EXPECT_EQ(idfUnitary.getString(AirLoopHVAC_UnitarySystemFields::AirInletNodeName).get(),
            idfCoil.getString(Coil_Cooling_WaterFields::AirInletNodeName).get());

  EXPECT_EQ(idfUnitary.getString(AirLoopHVAC_UnitarySystemFields::AirOutletNodeName).get(),
            idfCoil.getString(Coil_Cooling_WaterFields::AirOutletNodeName).get());

  EXPECT_EQ("My CoilCoolingWater", idfCoil.getString(Coil_Cooling_WaterFields::Name).get());
  EXPECT_EQ("Always On Discrete", idfCoil.getString(Coil_Cooling_WaterFields::AvailabilityScheduleName).get());
  EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignWaterFlowRate).get());
  EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignAirFlowRate).get());
  EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignInletWaterTemperature).get());
  EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignInletAirTemperature).get());
  EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignInletAirHumidityRatio).get());
  EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignOutletAirHumidityRatio).get());
  EXPECT_EQ("Coil Water Inlet Node", idfCoil.getString(Coil_Cooling_WaterFields::WaterInletNodeName).get());
  EXPECT_EQ("Coil Water Outlet Node", idfCoil.getString(Coil_Cooling_WaterFields::WaterOutletNodeName).get());
  EXPECT_EQ("Coil Air Inlet Node", idfCoil.getString(Coil_Cooling_WaterFields::AirInletNodeName).get());
  EXPECT_EQ("Coil Air Outlet Node", idfCoil.getString(Coil_Cooling_WaterFields::AirOutletNodeName).get());
  EXPECT_EQ("SimpleAnalysis", idfCoil.getString(Coil_Cooling_WaterFields::TypeofAnalysis).get());
  EXPECT_EQ("CrossFlow", idfCoil.getString(Coil_Cooling_WaterFields::HeatExchangerConfiguration).get());
  EXPECT_TRUE(idfCoil.isEmpty(Coil_Cooling_WaterFields::CondensateCollectionWaterStorageTankName));
  EXPECT_TRUE(idfCoil.isEmpty(Coil_Cooling_WaterFields::DesignWaterTemperatureDifference));

  // Check Controller:WaterCoil created by coil.addToNode
  EXPECT_EQ(0, w.getObjectsByType(IddObjectType::Controller_WaterCoil).size());
}

TEST_F(EnergyPlusFixture, ForwardTranslator_CoilCoolingWater_AirLoopHVAC) {
  Model m;
  CoilCoolingWater coil(m);

  // put it on an AirLoopHVAC
  AirLoopHVAC airLoop(m);
  Node supplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_TRUE(coil.addToNode(supplyOutletNode));

  // They must be connected to a PlantLoop too
  PlantLoop chw_p(m);
  chw_p.addDemandBranchForComponent(coil);

  ForwardTranslator ft;
  Workspace w = ft.translateModel(m);

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

  EXPECT_EQ(w_eg2.getString(BranchExtensibleFields::ComponentInletNodeName).get(), coil.airInletModelObject().get().nameString());
  EXPECT_EQ(w_eg2.getString(BranchExtensibleFields::ComponentOutletNodeName).get(), coil.airOutletModelObject().get().nameString());
  EXPECT_EQ("Coil:Cooling:Water", w_eg2.getString(BranchExtensibleFields::ComponentObjectType).get());

  EXPECT_EQ(coil.nameString(), idfCoil.getString(Coil_Cooling_WaterFields::Name).get());
  EXPECT_EQ("Always On Discrete", idfCoil.getString(Coil_Cooling_WaterFields::AvailabilityScheduleName).get());
  EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignWaterFlowRate).get());
  EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignAirFlowRate).get());
  EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignInletWaterTemperature).get());
  EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignInletAirTemperature).get());
  EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignInletAirHumidityRatio).get());
  EXPECT_EQ("Autosize", idfCoil.getString(Coil_Cooling_WaterFields::DesignOutletAirHumidityRatio).get());
  EXPECT_EQ(coil.waterInletModelObject().get().nameString(), idfCoil.getString(Coil_Cooling_WaterFields::WaterInletNodeName).get());
  EXPECT_EQ(coil.waterOutletModelObject().get().nameString(), idfCoil.getString(Coil_Cooling_WaterFields::WaterOutletNodeName).get());
  EXPECT_EQ(coil.airInletModelObject().get().nameString(), idfCoil.getString(Coil_Cooling_WaterFields::AirInletNodeName).get());
  EXPECT_EQ(coil.airOutletModelObject().get().nameString(), idfCoil.getString(Coil_Cooling_WaterFields::AirOutletNodeName).get());
  EXPECT_EQ("SimpleAnalysis", idfCoil.getString(Coil_Cooling_WaterFields::TypeofAnalysis).get());
  EXPECT_EQ("CrossFlow", idfCoil.getString(Coil_Cooling_WaterFields::HeatExchangerConfiguration).get());
  EXPECT_TRUE(idfCoil.isEmpty(Coil_Cooling_WaterFields::CondensateCollectionWaterStorageTankName));
  EXPECT_TRUE(idfCoil.isEmpty(Coil_Cooling_WaterFields::DesignWaterTemperatureDifference));

  // Check Controller:WaterCoil created by coil.addToNode
  EXPECT_EQ(1, w.getObjectsByType(IddObjectType::Controller_WaterCoil).size());
}

TEST_F(EnergyPlusFixture, ReverseTranslator_CoilCoolingWater) {

  ReverseTranslator rt;

  Workspace w(StrictnessLevel::Minimal, IddFileType::EnergyPlus);

  auto woCCW = w.addObject(IdfObject(IddObjectType::Coil_Cooling_Water)).get();

  woCCW.setName("My CoilCoolingWater");
  auto woavailabilitySchedule = w.addObject(IdfObject(IddObjectType::Schedule_Constant)).get();
  woavailabilitySchedule.setName("My availabilitySchedule");
  EXPECT_TRUE(woCCW.setPointer(Coil_Cooling_WaterFields::AvailabilityScheduleName, woavailabilitySchedule.handle()));
  // Autosize
  // EXPECT_TRUE(woCCW.setString(Coil_Cooling_WaterFields::DesignWaterFlowRate, "Autosized"));
  EXPECT_TRUE(woCCW.setDouble(Coil_Cooling_WaterFields::DesignWaterFlowRate, 0.3));
  // Autosize
  // EXPECT_TRUE(woCCW.setString(Coil_Cooling_WaterFields::DesignAirFlowRate, "Autosized"));
  EXPECT_TRUE(woCCW.setDouble(Coil_Cooling_WaterFields::DesignAirFlowRate, 0.4));
  // Autosize
  // EXPECT_TRUE(woCCW.setString(Coil_Cooling_WaterFields::DesignInletWaterTemperature, "Autosized"));
  EXPECT_TRUE(woCCW.setDouble(Coil_Cooling_WaterFields::DesignInletWaterTemperature, 0.5));

  // Leave empty = Autosize
  // EXPECT_TRUE(woCCW.setString(Coil_Cooling_WaterFields::DesignInletAirTemperature, "Autosized"));
  // EXPECT_TRUE(woCCW.setDouble(Coil_Cooling_WaterFields::DesignInletAirTemperature, 0.6));

  // Explicit Autosize
  EXPECT_TRUE(woCCW.setString(Coil_Cooling_WaterFields::DesignOutletAirTemperature, "AutosiZED"));
  // EXPECT_TRUE(woCCW.setDouble(Coil_Cooling_WaterFields::DesignOutletAirTemperature, 0.7));

  // Autosize
  // EXPECT_TRUE(woCCW.setString(Coil_Cooling_WaterFields::DesignInletAirHumidityRatio, "Autosized"));
  EXPECT_TRUE(woCCW.setDouble(Coil_Cooling_WaterFields::DesignInletAirHumidityRatio, 0.8));
  // Autosize
  // EXPECT_TRUE(woCCW.setString(Coil_Cooling_WaterFields::DesignOutletAirHumidityRatio, "Autosized"));
  EXPECT_TRUE(woCCW.setDouble(Coil_Cooling_WaterFields::DesignOutletAirHumidityRatio, 0.9));

  auto wowaterInletNodeName = "My waterInletNodeName";
  EXPECT_TRUE(woCCW.setString(Coil_Cooling_WaterFields::WaterInletNodeName, wowaterInletNodeName));

  auto wowaterOutletNodeName = "My waterOutletNodeName";
  EXPECT_TRUE(woCCW.setString(Coil_Cooling_WaterFields::WaterOutletNodeName, wowaterOutletNodeName));

  auto woairInletNodeName = "My airInletNodeName";
  EXPECT_TRUE(woCCW.setString(Coil_Cooling_WaterFields::AirInletNodeName, woairInletNodeName));

  auto woairOutletNodeName = "My airOutletNodeName";
  EXPECT_TRUE(woCCW.setString(Coil_Cooling_WaterFields::AirOutletNodeName, woairOutletNodeName));

  EXPECT_TRUE(woCCW.setString(Coil_Cooling_WaterFields::TypeofAnalysis, "DetailedAnalysis"));
  EXPECT_TRUE(woCCW.setString(Coil_Cooling_WaterFields::HeatExchangerConfiguration, "CrossFlow"));

  // Unused currently
  auto wocondensateCollectionWaterStorageTank = w.addObject(IdfObject(IddObjectType::WaterUse_Storage)).get();
  wocondensateCollectionWaterStorageTank.setName("My condensateCollectionWaterStorageTank");
  EXPECT_TRUE(woCCW.setPointer(Coil_Cooling_WaterFields::CondensateCollectionWaterStorageTankName, wocondensateCollectionWaterStorageTank.handle()));

  // Unused currently
  EXPECT_TRUE(woCCW.setDouble(Coil_Cooling_WaterFields::DesignWaterTemperatureDifference, 1.7));

  const Model m = rt.translateWorkspace(w);
  const auto modelObjects = m.getConcreteModelObjects<CoilCoolingWater>();
  ASSERT_EQ(1u, modelObjects.size());

  auto modelObject = modelObjects.front();
  ASSERT_TRUE(modelObject.availabilitySchedule().optionalCast<ScheduleConstant>());
  EXPECT_EQ(woavailabilitySchedule.nameString(), modelObject.availabilitySchedule().nameString());

  EXPECT_FALSE(modelObject.isDesignWaterFlowRateAutosized());
  ASSERT_TRUE(modelObject.designWaterFlowRate());
  EXPECT_EQ(0.3, modelObject.designWaterFlowRate().get());

  EXPECT_FALSE(modelObject.isDesignAirFlowRateAutosized());
  ASSERT_TRUE(modelObject.designAirFlowRate());
  EXPECT_EQ(0.4, modelObject.designAirFlowRate().get());

  EXPECT_TRUE(modelObject.isDesignInletWaterTemperatureAutosized());

  EXPECT_TRUE(modelObject.isDesignInletAirTemperatureAutosized());

  EXPECT_FALSE(modelObject.isDesignOutletAirTemperatureAutosized());
  ASSERT_TRUE(modelObject.designOutletAirTemperature());
  EXPECT_EQ(0.7, modelObject.designOutletAirTemperature().get());

  EXPECT_FALSE(modelObject.isDesignInletAirHumidityRatioAutosized());
  ASSERT_TRUE(modelObject.designInletAirHumidityRatio());
  EXPECT_EQ(0.8, modelObject.designInletAirHumidityRatio().get());

  EXPECT_FALSE(modelObject.isDesignOutletAirHumidityRatioAutosized());
  ASSERT_TRUE(modelObject.designOutletAirHumidityRatio());
  EXPECT_EQ(0.9, modelObject.designOutletAirHumidityRatio().get());

  EXPECT_EQ("DetailedAnalysis", modelObject.typeOfAnalysis());
  EXPECT_EQ("CrossFlow", modelObject.heatExchangerConfiguration());
  // ASSERT_TRUE(modelObject.condensateCollectionWaterStorageTank().optionalCast<WaterStorageTank>());
  // EXPECT_EQ(wocondensateCollectionWaterStorageTank.nameString(), modelObject.condensateCollectionWaterStorageTank().nameString());
  // EXPECT_EQ(1.7, modelObject.designWaterTemperatureDifference());
}
