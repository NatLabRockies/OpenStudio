/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "EnergyPlusFixture.hpp"

#include "../ForwardTranslator.hpp"

#include "../../model/ThermalStorageChilledWaterStratified.hpp"

#include "../../model/Model.hpp"
#include "../../model/PlantLoop.hpp"
#include "../../model/Schedule.hpp"
#include "../../model/ScheduleConstant.hpp"
#include "../../model/Space.hpp"
#include "../../model/ThermalZone.hpp"

#include "../../utilities/idf/Workspace.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"

// E+ FieldEnums
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ThermalStorage_ChilledWater_Stratified_FieldEnums.hxx>
#include <utilities/idd/WaterHeater_Sizing_FieldEnums.hxx>

using namespace openstudio::energyplus;
using namespace openstudio::model;
using namespace openstudio;

/* Gtest for https://github.com/NREL/OpenStudio/issues/2373 */
TEST_F(EnergyPlusFixture, ForwardTranslator_ThermalStorageChilledWaterStratified_NumNodesAndTankTime) {
  Model model;

  ThermalStorageChilledWaterStratified t(model);

  ASSERT_TRUE(t.setTankRecoveryTime(4.25));
  ASSERT_TRUE(t.setNumberofNodes(7));

  PlantLoop p(model);
  ASSERT_TRUE(p.addSupplyBranchForComponent(t));

  ForwardTranslator forwardTranslator;
  Workspace workspace = forwardTranslator.translateModel(model);

  WorkspaceObjectVector idfObjs(workspace.getObjectsByType(IddObjectType::ThermalStorage_ChilledWater_Stratified));
  EXPECT_EQ(1u, idfObjs.size());
  WorkspaceObject idf_t(idfObjs[0]);

  EXPECT_DOUBLE_EQ(4.25, *idf_t.getDouble(ThermalStorage_ChilledWater_StratifiedFields::TankRecoveryTime));
  EXPECT_EQ(7, *idf_t.getInt(ThermalStorage_ChilledWater_StratifiedFields::NumberofNodes));
}

TEST_F(EnergyPlusFixture, ForwardTranslator_ThermalStorageChilledWaterStratified) {

  ForwardTranslator ft;

  Model m;
  ThermalStorageChilledWaterStratified chw_storage(m);

  chw_storage.setName("My ThermalStorageChilledWaterStratified");
  EXPECT_TRUE(chw_storage.setTankVolume(0.2));
  EXPECT_TRUE(chw_storage.setTankHeight(0.3));
  EXPECT_TRUE(chw_storage.setTankShape("VerticalCylinder"));
  EXPECT_TRUE(chw_storage.setTankPerimeter(0.5));

  ScheduleConstant setpointTemperatureSchedule(m);
  setpointTemperatureSchedule.setName("Setpoint Temp Schedule");
  EXPECT_TRUE(chw_storage.setSetpointTemperatureSchedule(setpointTemperatureSchedule));

  EXPECT_TRUE(chw_storage.setDeadbandTemperatureDifference(0.7));
  EXPECT_TRUE(chw_storage.setTemperatureSensorHeight(0.8));
  EXPECT_TRUE(chw_storage.setMinimumTemperatureLimit(0.9));
  EXPECT_TRUE(chw_storage.setNominalCoolingCapacity(1.0));
  EXPECT_TRUE(chw_storage.setAmbientTemperatureIndicator("Schedule"));

  ScheduleConstant ambientTemperatureSchedule(m);
  ambientTemperatureSchedule.setName("Ambient Temp Schedule");
  EXPECT_TRUE(chw_storage.setAmbientTemperatureSchedule(ambientTemperatureSchedule));

  ThermalZone ambientTemperatureZone(m);
  Space s(m);
  s.setThermalZone(ambientTemperatureZone);

  ambientTemperatureZone.setName("Ambient Temp Zone");
  EXPECT_TRUE(chw_storage.setAmbientTemperatureThermalZone(ambientTemperatureZone));

  const std::string ambientTemperatureOutdoorAirNodeName = "My Ambient Temp Outdoor Air Node";
  EXPECT_TRUE(chw_storage.setAmbientTemperatureOutdoorAirNodeName(ambientTemperatureOutdoorAirNodeName));

  EXPECT_TRUE(chw_storage.setUniformSkinLossCoefficientperUnitAreatoAmbientTemperature(1.5));

  PlantLoop useLoop(m);
  ASSERT_TRUE(useLoop.addSupplyBranchForComponent(chw_storage));

  const std::string useSideInletNodeName = "Use Side Inlet Node";
  chw_storage.supplyInletModelObject()->setName(useSideInletNodeName);

  const std::string useSideOutletNodeName = "Use Side Outlet Node";
  chw_storage.supplyOutletModelObject()->setName(useSideOutletNodeName);

  EXPECT_TRUE(chw_storage.setUseSideHeatTransferEffectiveness(0.947));

  ScheduleConstant useSideAvailabilitySchedule(m);
  useSideAvailabilitySchedule.setName("Use Side Availability Schedule");
  EXPECT_TRUE(chw_storage.setUseSideAvailabilitySchedule(useSideAvailabilitySchedule));

  // Autocalculate
  chw_storage.autocalculateUseSideInletHeight();
  EXPECT_TRUE(chw_storage.setUseSideOutletHeight(2.1));

  // Autosize
  chw_storage.autosizeUseSideDesignFlowRate();

  PlantLoop sourceLoop(m);
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(chw_storage));

  const std::string sourceSideInletNodeName = "Source Side Inlet Node";
  chw_storage.demandInletModelObject()->setName(sourceSideInletNodeName);

  const std::string sourceSideOutletNodeName = "Source Side Outlet Node";
  chw_storage.demandOutletModelObject()->setName(sourceSideOutletNodeName);

  EXPECT_TRUE(chw_storage.setSourceSideHeatTransferEffectiveness(0.962));

  ScheduleConstant sourceSideAvailabilitySchedule(m);
  sourceSideAvailabilitySchedule.setName("Source Side Availability Schedule");
  EXPECT_TRUE(chw_storage.setSourceSideAvailabilitySchedule(sourceSideAvailabilitySchedule));
  EXPECT_TRUE(chw_storage.setSourceSideInletHeight(2.7));
  // Autocalculate
  // chw_storage.autocalculateSourceSideOutletHeight();
  EXPECT_TRUE(chw_storage.setSourceSideOutletHeight(2.8));
  // Autosize
  // chw_storage.autosizeSourceSideDesignFlowRate();
  EXPECT_TRUE(chw_storage.setSourceSideDesignFlowRate(2.9));
  EXPECT_TRUE(chw_storage.setTankRecoveryTime(3.0));
  EXPECT_TRUE(chw_storage.setInletMode("Fixed"));
  EXPECT_TRUE(chw_storage.setNumberofNodes(6));
  EXPECT_TRUE(chw_storage.setAdditionalDestratificationConductivity(3.3));
  EXPECT_TRUE(chw_storage.setNode1AdditionalLossCoefficient(3.4));
  EXPECT_TRUE(chw_storage.setNode2AdditionalLossCoefficient(3.5));
  EXPECT_TRUE(chw_storage.setNode3AdditionalLossCoefficient(3.6));
  EXPECT_TRUE(chw_storage.setNode4AdditionalLossCoefficient(3.7));
  EXPECT_TRUE(chw_storage.setNode5AdditionalLossCoefficient(3.8));
  EXPECT_TRUE(chw_storage.setNode6AdditionalLossCoefficient(3.9));

  // These shouldn't be translated since num nodes is 6, but set them anyway to test
  EXPECT_TRUE(chw_storage.setNode7AdditionalLossCoefficient(4.0));
  EXPECT_TRUE(chw_storage.setNode8AdditionalLossCoefficient(4.1));
  EXPECT_TRUE(chw_storage.setNode9AdditionalLossCoefficient(4.2));
  EXPECT_TRUE(chw_storage.setNode10AdditionalLossCoefficient(4.3));

  const Workspace w = ft.translateModel(m);

  const auto idfObjs = w.getObjectsByType(IddObjectType::ThermalStorage_ChilledWater_Stratified);
  ASSERT_EQ(1u, idfObjs.size());

  const auto& idfObject = idfObjs.front();
  EXPECT_EQ(0.2, idfObject.getDouble(ThermalStorage_ChilledWater_StratifiedFields::TankVolume).get());
  EXPECT_EQ(0.3, idfObject.getDouble(ThermalStorage_ChilledWater_StratifiedFields::TankHeight).get());
  EXPECT_EQ("VerticalCylinder", idfObject.getString(ThermalStorage_ChilledWater_StratifiedFields::TankShape).get());
  EXPECT_EQ(0.5, idfObject.getDouble(ThermalStorage_ChilledWater_StratifiedFields::TankPerimeter).get());
  EXPECT_EQ(setpointTemperatureSchedule.nameString(),
            idfObject.getString(ThermalStorage_ChilledWater_StratifiedFields::SetpointTemperatureScheduleName).get());
  EXPECT_EQ(0.7, idfObject.getDouble(ThermalStorage_ChilledWater_StratifiedFields::DeadbandTemperatureDifference).get());
  EXPECT_EQ(0.8, idfObject.getDouble(ThermalStorage_ChilledWater_StratifiedFields::TemperatureSensorHeight).get());
  EXPECT_EQ(0.9, idfObject.getDouble(ThermalStorage_ChilledWater_StratifiedFields::MinimumTemperatureLimit).get());
  EXPECT_EQ(1.0, idfObject.getDouble(ThermalStorage_ChilledWater_StratifiedFields::NominalCoolingCapacity).get());
  EXPECT_EQ("Schedule", idfObject.getString(ThermalStorage_ChilledWater_StratifiedFields::AmbientTemperatureIndicator).get());
  EXPECT_EQ(ambientTemperatureSchedule.nameString(),
            idfObject.getString(ThermalStorage_ChilledWater_StratifiedFields::AmbientTemperatureScheduleName).get());
  EXPECT_EQ(ambientTemperatureZone.nameString(), idfObject.getString(ThermalStorage_ChilledWater_StratifiedFields::AmbientTemperatureZoneName).get());
  EXPECT_EQ(ambientTemperatureOutdoorAirNodeName,
            idfObject.getString(ThermalStorage_ChilledWater_StratifiedFields::AmbientTemperatureOutdoorAirNodeName).get());
  EXPECT_EQ(1.5, idfObject.getDouble(ThermalStorage_ChilledWater_StratifiedFields::UniformSkinLossCoefficientperUnitAreatoAmbientTemperature).get());
  EXPECT_EQ(useSideInletNodeName, idfObject.getString(ThermalStorage_ChilledWater_StratifiedFields::UseSideInletNodeName).get());
  EXPECT_EQ(useSideOutletNodeName, idfObject.getString(ThermalStorage_ChilledWater_StratifiedFields::UseSideOutletNodeName).get());
  EXPECT_EQ(0.947, idfObject.getDouble(ThermalStorage_ChilledWater_StratifiedFields::UseSideHeatTransferEffectiveness).get());
  EXPECT_EQ(useSideAvailabilitySchedule.nameString(),
            idfObject.getString(ThermalStorage_ChilledWater_StratifiedFields::UseSideAvailabilityScheduleName).get());
  EXPECT_EQ("Autocalculate", idfObject.getString(ThermalStorage_ChilledWater_StratifiedFields::UseSideInletHeight).get());
  EXPECT_EQ(2.1, idfObject.getDouble(ThermalStorage_ChilledWater_StratifiedFields::UseSideOutletHeight).get());
  EXPECT_EQ("Autosize", idfObject.getString(ThermalStorage_ChilledWater_StratifiedFields::UseSideDesignFlowRate).get());
  EXPECT_EQ(sourceSideInletNodeName, idfObject.getString(ThermalStorage_ChilledWater_StratifiedFields::SourceSideInletNodeName).get());
  EXPECT_EQ(sourceSideOutletNodeName, idfObject.getString(ThermalStorage_ChilledWater_StratifiedFields::SourceSideOutletNodeName).get());
  EXPECT_EQ(0.962, idfObject.getDouble(ThermalStorage_ChilledWater_StratifiedFields::SourceSideHeatTransferEffectiveness).get());
  EXPECT_EQ(sourceSideAvailabilitySchedule.nameString(),
            idfObject.getString(ThermalStorage_ChilledWater_StratifiedFields::SourceSideAvailabilityScheduleName).get());
  EXPECT_EQ(2.7, idfObject.getDouble(ThermalStorage_ChilledWater_StratifiedFields::SourceSideInletHeight).get());
  // EXPECT_EQ("Autocalculate", idfObject.getString(ThermalStorage_ChilledWater_StratifiedFields::SourceSideOutletHeight).get());
  EXPECT_EQ(2.8, idfObject.getDouble(ThermalStorage_ChilledWater_StratifiedFields::SourceSideOutletHeight).get());
  // EXPECT_EQ("Autosize", idfObject.getString(ThermalStorage_ChilledWater_StratifiedFields::SourceSideDesignFlowRate).get());
  EXPECT_EQ(2.9, idfObject.getDouble(ThermalStorage_ChilledWater_StratifiedFields::SourceSideDesignFlowRate).get());
  EXPECT_EQ(3.0, idfObject.getDouble(ThermalStorage_ChilledWater_StratifiedFields::TankRecoveryTime).get());
  EXPECT_EQ("Fixed", idfObject.getString(ThermalStorage_ChilledWater_StratifiedFields::InletMode).get());

  EXPECT_EQ(6, idfObject.getInt(ThermalStorage_ChilledWater_StratifiedFields::NumberofNodes).get());
  EXPECT_EQ(3.3, idfObject.getDouble(ThermalStorage_ChilledWater_StratifiedFields::AdditionalDestratificationConductivity).get());
  EXPECT_EQ(3.4, idfObject.getDouble(ThermalStorage_ChilledWater_StratifiedFields::Node1AdditionalLossCoefficient).get());
  EXPECT_EQ(3.5, idfObject.getDouble(ThermalStorage_ChilledWater_StratifiedFields::Node2AdditionalLossCoefficient).get());
  EXPECT_EQ(3.6, idfObject.getDouble(ThermalStorage_ChilledWater_StratifiedFields::Node3AdditionalLossCoefficient).get());
  EXPECT_EQ(3.7, idfObject.getDouble(ThermalStorage_ChilledWater_StratifiedFields::Node4AdditionalLossCoefficient).get());
  EXPECT_EQ(3.8, idfObject.getDouble(ThermalStorage_ChilledWater_StratifiedFields::Node5AdditionalLossCoefficient).get());
  EXPECT_EQ(3.9, idfObject.getDouble(ThermalStorage_ChilledWater_StratifiedFields::Node6AdditionalLossCoefficient).get());

  // After num nodes, we don't write it, or E+ issues a warning
  EXPECT_TRUE(idfObject.isEmpty(ThermalStorage_ChilledWater_StratifiedFields::Node7AdditionalLossCoefficient));
  EXPECT_TRUE(idfObject.isEmpty(ThermalStorage_ChilledWater_StratifiedFields::Node8AdditionalLossCoefficient));
  EXPECT_TRUE(idfObject.isEmpty(ThermalStorage_ChilledWater_StratifiedFields::Node9AdditionalLossCoefficient));
  EXPECT_TRUE(idfObject.isEmpty(ThermalStorage_ChilledWater_StratifiedFields::Node10AdditionalLossCoefficient));

  // CHECK WaterHeater:Sizing
  const auto whSizings = w.getObjectsByType(IddObjectType::WaterHeater_Sizing);
  ASSERT_EQ(1u, whSizings.size());
  const auto& whSizing = whSizings.front();
  EXPECT_EQ("My ThermalStorageChilledWaterStratified", whSizing.getString(WaterHeater_SizingFields::WaterHeaterName).get());
}
