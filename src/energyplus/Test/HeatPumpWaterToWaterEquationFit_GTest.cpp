/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "EnergyPlusFixture.hpp"

#include "../ForwardTranslator.hpp"

#include "../../model/CurveQuadLinear.hpp"
#include "../../model/Model.hpp"
#include "../../model/HeatPumpWaterToWaterEquationFitCooling.hpp"
#include "../../model/HeatPumpWaterToWaterEquationFitHeating.hpp"
#include "../../model/Node.hpp"
#include "../../model/PlantLoop.hpp"

#include <utilities/idd/HeatPump_WaterToWater_EquationFit_Cooling_FieldEnums.hxx>
#include <utilities/idd/HeatPump_WaterToWater_EquationFit_Heating_FieldEnums.hxx>

#include <utilities/idd/IddEnums.hxx>
#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idf/IdfObject_Impl.hpp"

#include "../../utilities/idf/WorkspaceObject.hpp"
#include "../../utilities/idf/WorkspaceObject_Impl.hpp"

using namespace openstudio::energyplus;
using namespace openstudio::model;
using namespace openstudio;

TEST_F(EnergyPlusFixture, ForwardTranslator_HeatPumpWaterToWaterEquationFit) {

  Model m;

  PlantLoop plant_loop_cup_clg(m);
  PlantLoop plant_loop_cup_htg(m);
  PlantLoop plant_loop_wwhp_clg(m);
  PlantLoop plant_loop_wwhp_htg(m);

  HeatPumpWaterToWaterEquationFitCooling wwhp_clg(m);
  HeatPumpWaterToWaterEquationFitHeating wwhp_htg(m);

  ASSERT_TRUE(wwhp_clg.setName("WWHP Cooling"));
  ASSERT_TRUE(wwhp_htg.setName("WWHP Heating"));

  EXPECT_TRUE(plant_loop_cup_clg.addDemandBranchForComponent(wwhp_clg));
  EXPECT_TRUE(plant_loop_wwhp_clg.addSupplyBranchForComponent(wwhp_clg));
  EXPECT_TRUE(plant_loop_cup_htg.addDemandBranchForComponent(wwhp_htg));
  EXPECT_TRUE(plant_loop_wwhp_htg.addSupplyBranchForComponent(wwhp_htg));

  ASSERT_TRUE(wwhp_clg.supplyInletModelObject());
  ASSERT_TRUE(wwhp_clg.supplyOutletModelObject());
  ASSERT_TRUE(wwhp_clg.demandInletModelObject());
  ASSERT_TRUE(wwhp_clg.demandOutletModelObject());
  EXPECT_TRUE(wwhp_clg.supplyInletModelObject()->setName("Cooling Load Inlet Node"));
  EXPECT_TRUE(wwhp_clg.supplyOutletModelObject()->setName("Cooling Load Outlet Node"));
  EXPECT_TRUE(wwhp_clg.demandInletModelObject()->setName("Cooling Source Inlet Node"));
  EXPECT_TRUE(wwhp_clg.demandOutletModelObject()->setName("Cooling Source Outlet Node"));

  ASSERT_TRUE(wwhp_htg.supplyInletModelObject());
  ASSERT_TRUE(wwhp_htg.supplyOutletModelObject());
  ASSERT_TRUE(wwhp_htg.demandInletModelObject());
  ASSERT_TRUE(wwhp_htg.demandOutletModelObject());
  EXPECT_TRUE(wwhp_htg.supplyInletModelObject()->setName("Heating Load Inlet Node"));
  EXPECT_TRUE(wwhp_htg.supplyOutletModelObject()->setName("Heating Load Outlet Node"));
  EXPECT_TRUE(wwhp_htg.demandInletModelObject()->setName("Heating Source Inlet Node"));
  EXPECT_TRUE(wwhp_htg.demandOutletModelObject()->setName("Heating Source Outlet Node"));

  EXPECT_TRUE(wwhp_clg.setReferenceLoadSideFlowRate(0.101));
  EXPECT_TRUE(wwhp_clg.setReferenceSourceSideFlowRate(0.202));
  EXPECT_TRUE(wwhp_clg.setRatedCoolingCapacity(12345.0));
  EXPECT_TRUE(wwhp_clg.setRatedCoolingPowerConsumption(3456.0));
  EXPECT_TRUE(wwhp_clg.setReferenceCoefficientofPerformance(4.25));
  EXPECT_TRUE(wwhp_clg.setSizingFactor(1.15));

  EXPECT_TRUE(wwhp_htg.setReferenceLoadSideFlowRate(0.303));
  EXPECT_TRUE(wwhp_htg.setReferenceSourceSideFlowRate(0.404));
  EXPECT_TRUE(wwhp_htg.setRatedHeatingCapacity(23456.0));
  EXPECT_TRUE(wwhp_htg.setRatedHeatingPowerConsumption(4567.0));
  EXPECT_TRUE(wwhp_htg.setReferenceCoefficientofPerformance(5.5));
  EXPECT_TRUE(wwhp_htg.setSizingFactor(1.25));

  CurveQuadLinear coolingCapacityCurve = wwhp_clg.coolingCapacityCurve();
  CurveQuadLinear coolingPowerCurve = wwhp_clg.coolingCompressorPowerCurve();
  ASSERT_TRUE(coolingCapacityCurve.setName("Cooling Capacity Curve"));
  ASSERT_TRUE(coolingPowerCurve.setName("Cooling Power Curve"));

  CurveQuadLinear heatingCapacityCurve = wwhp_htg.heatingCapacityCurve();
  CurveQuadLinear heatingPowerCurve = wwhp_htg.heatingCompressorPowerCurve();
  ASSERT_TRUE(heatingCapacityCurve.setName("Heating Capacity Curve"));
  ASSERT_TRUE(heatingPowerCurve.setName("Heating Power Curve"));

  // #3837: These two reference each other, and we want to avoid a recursion problem (each FT function calling each other)
  EXPECT_TRUE(wwhp_clg.setCompanionHeatingHeatPump(wwhp_htg));
  EXPECT_TRUE(wwhp_htg.setCompanionCoolingHeatPump(wwhp_clg));

  openstudio::energyplus::ForwardTranslator ft;
  Workspace w = ft.translateModel(m);

  EXPECT_EQ(0u, ft.errors().size());

  {
    WorkspaceObjectVector idf_ccs(w.getObjectsByType(IddObjectType::HeatPump_WaterToWater_EquationFit_Cooling));
    ASSERT_EQ(1u, idf_ccs.size());
    WorkspaceObject idf_cc(idf_ccs[0]);

    EXPECT_EQ("WWHP Cooling", idf_cc.getString(HeatPump_WaterToWater_EquationFit_CoolingFields::Name).get());
    EXPECT_EQ("Cooling Load Inlet Node", idf_cc.getString(HeatPump_WaterToWater_EquationFit_CoolingFields::LoadSideInletNodeName).get());
    EXPECT_EQ("Cooling Load Outlet Node", idf_cc.getString(HeatPump_WaterToWater_EquationFit_CoolingFields::LoadSideOutletNodeName).get());
    EXPECT_EQ("Cooling Source Inlet Node", idf_cc.getString(HeatPump_WaterToWater_EquationFit_CoolingFields::SourceSideInletNodeName).get());
    EXPECT_EQ("Cooling Source Outlet Node", idf_cc.getString(HeatPump_WaterToWater_EquationFit_CoolingFields::SourceSideOutletNodeName).get());
    EXPECT_DOUBLE_EQ(0.101, idf_cc.getDouble(HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceLoadSideFlowRate).get());
    EXPECT_DOUBLE_EQ(0.202, idf_cc.getDouble(HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceSourceSideFlowRate).get());
    EXPECT_DOUBLE_EQ(12345.0, idf_cc.getDouble(HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceCoolingCapacity).get());
    EXPECT_DOUBLE_EQ(3456.0, idf_cc.getDouble(HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceCoolingPowerConsumption).get());
    EXPECT_DOUBLE_EQ(4.25, idf_cc.getDouble(HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceCoefficientofPerformance).get());
    EXPECT_DOUBLE_EQ(1.15, idf_cc.getDouble(HeatPump_WaterToWater_EquationFit_CoolingFields::SizingFactor).get());
    EXPECT_EQ("Cooling Capacity Curve", idf_cc.getString(HeatPump_WaterToWater_EquationFit_CoolingFields::CoolingCapacityCurveName).get());
    EXPECT_EQ("Cooling Power Curve", idf_cc.getString(HeatPump_WaterToWater_EquationFit_CoolingFields::CoolingCompressorPowerCurveName).get());

    auto coolingCapacityCurveTarget = idf_cc.getTarget(HeatPump_WaterToWater_EquationFit_CoolingFields::CoolingCapacityCurveName);
    ASSERT_TRUE(coolingCapacityCurveTarget);
    EXPECT_EQ(IddObjectType(IddObjectType::Curve_QuadLinear), coolingCapacityCurveTarget->iddObject().type());

    auto coolingPowerCurveTarget = idf_cc.getTarget(HeatPump_WaterToWater_EquationFit_CoolingFields::CoolingCompressorPowerCurveName);
    ASSERT_TRUE(coolingPowerCurveTarget);
    EXPECT_EQ(IddObjectType(IddObjectType::Curve_QuadLinear), coolingPowerCurveTarget->iddObject().type());

    EXPECT_EQ(wwhp_htg.nameString(), idf_cc.getString(HeatPump_WaterToWater_EquationFit_CoolingFields::CompanionHeatingHeatPumpName).get());
  }

  {
    WorkspaceObjectVector idf_hcs(w.getObjectsByType(IddObjectType::HeatPump_WaterToWater_EquationFit_Heating));
    ASSERT_EQ(1u, idf_hcs.size());
    WorkspaceObject idf_hc(idf_hcs[0]);

    EXPECT_EQ("WWHP Heating", idf_hc.getString(HeatPump_WaterToWater_EquationFit_HeatingFields::Name).get());
    EXPECT_EQ("Heating Load Inlet Node", idf_hc.getString(HeatPump_WaterToWater_EquationFit_HeatingFields::LoadSideInletNodeName).get());
    EXPECT_EQ("Heating Load Outlet Node", idf_hc.getString(HeatPump_WaterToWater_EquationFit_HeatingFields::LoadSideOutletNodeName).get());
    EXPECT_EQ("Heating Source Inlet Node", idf_hc.getString(HeatPump_WaterToWater_EquationFit_HeatingFields::SourceSideInletNodeName).get());
    EXPECT_EQ("Heating Source Outlet Node", idf_hc.getString(HeatPump_WaterToWater_EquationFit_HeatingFields::SourceSideOutletNodeName).get());
    EXPECT_DOUBLE_EQ(0.303, idf_hc.getDouble(HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceLoadSideFlowRate).get());
    EXPECT_DOUBLE_EQ(0.404, idf_hc.getDouble(HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceSourceSideFlowRate).get());
    EXPECT_DOUBLE_EQ(23456.0, idf_hc.getDouble(HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceHeatingCapacity).get());
    EXPECT_DOUBLE_EQ(4567.0, idf_hc.getDouble(HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceHeatingPowerConsumption).get());
    EXPECT_DOUBLE_EQ(5.5, idf_hc.getDouble(HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceCoefficientofPerformance).get());
    EXPECT_DOUBLE_EQ(1.25, idf_hc.getDouble(HeatPump_WaterToWater_EquationFit_HeatingFields::SizingFactor).get());
    EXPECT_EQ("Heating Capacity Curve", idf_hc.getString(HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCapacityCurveName).get());
    EXPECT_EQ("Heating Power Curve", idf_hc.getString(HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCompressorPowerCurveName).get());

    auto heatingCapacityCurveTarget = idf_hc.getTarget(HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCapacityCurveName);
    ASSERT_TRUE(heatingCapacityCurveTarget);
    EXPECT_EQ(IddObjectType(IddObjectType::Curve_QuadLinear), heatingCapacityCurveTarget->iddObject().type());

    auto heatingPowerCurveTarget = idf_hc.getTarget(HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCompressorPowerCurveName);
    ASSERT_TRUE(heatingPowerCurveTarget);
    EXPECT_EQ(IddObjectType(IddObjectType::Curve_QuadLinear), heatingPowerCurveTarget->iddObject().type());

    EXPECT_EQ(wwhp_clg.nameString(), idf_hc.getString(HeatPump_WaterToWater_EquationFit_HeatingFields::CompanionCoolingHeatPumpName).get());
  }
}

TEST_F(EnergyPlusFixture, ForwardTranslator_HeatPumpWaterToWaterEquationFitCooling_AutosizeFields) {
  Model m;

  PlantLoop loadLoop(m);
  PlantLoop sourceLoop(m);

  HeatPumpWaterToWaterEquationFitCooling wwhpClg(m);

  EXPECT_TRUE(loadLoop.addDemandBranchForComponent(wwhpClg));
  EXPECT_TRUE(sourceLoop.addSupplyBranchForComponent(wwhpClg));

  wwhpClg.autosizeReferenceLoadSideFlowRate();
  wwhpClg.autosizeReferenceSourceSideFlowRate();
  wwhpClg.autosizeRatedCoolingCapacity();
  wwhpClg.autosizeRatedCoolingPowerConsumption();

  ForwardTranslator ft;
  Workspace w = ft.translateModel(m);

  EXPECT_EQ(0u, ft.errors().size());

  WorkspaceObjectVector idf_ccs(w.getObjectsByType(IddObjectType::HeatPump_WaterToWater_EquationFit_Cooling));
  ASSERT_EQ(1u, idf_ccs.size());
  WorkspaceObject idf_cc(idf_ccs[0]);

  EXPECT_EQ("Autosize", idf_cc.getString(HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceLoadSideFlowRate).get());
  EXPECT_EQ("Autosize", idf_cc.getString(HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceSourceSideFlowRate).get());
  EXPECT_EQ("Autosize", idf_cc.getString(HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceCoolingCapacity).get());
  EXPECT_EQ("Autosize", idf_cc.getString(HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceCoolingPowerConsumption).get());
}

TEST_F(EnergyPlusFixture, ForwardTranslator_HeatPumpWaterToWaterEquationFitHeating_AutosizeFields) {
  Model m;

  PlantLoop loadLoop(m);
  PlantLoop sourceLoop(m);

  HeatPumpWaterToWaterEquationFitHeating wwhpHtg(m);

  EXPECT_TRUE(loadLoop.addDemandBranchForComponent(wwhpHtg));
  EXPECT_TRUE(sourceLoop.addSupplyBranchForComponent(wwhpHtg));

  wwhpHtg.autosizeReferenceLoadSideFlowRate();
  wwhpHtg.autosizeReferenceSourceSideFlowRate();
  wwhpHtg.autosizeRatedHeatingCapacity();
  wwhpHtg.autosizeRatedHeatingPowerConsumption();

  ForwardTranslator ft;
  Workspace w = ft.translateModel(m);

  EXPECT_EQ(0u, ft.errors().size());

  WorkspaceObjectVector idf_hcs(w.getObjectsByType(IddObjectType::HeatPump_WaterToWater_EquationFit_Heating));
  ASSERT_EQ(1u, idf_hcs.size());
  WorkspaceObject idf_hc(idf_hcs[0]);

  EXPECT_EQ("Autosize", idf_hc.getString(HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceLoadSideFlowRate).get());
  EXPECT_EQ("Autosize", idf_hc.getString(HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceSourceSideFlowRate).get());
  EXPECT_EQ("Autosize", idf_hc.getString(HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceHeatingCapacity).get());
  EXPECT_EQ("Autosize", idf_hc.getString(HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceHeatingPowerConsumption).get());
}
