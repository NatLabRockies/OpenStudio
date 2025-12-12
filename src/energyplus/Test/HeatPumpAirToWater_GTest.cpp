/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "EnergyPlusFixture.hpp"

#include "../ForwardTranslator.hpp"
#include "../ReverseTranslator.hpp"

#include "../../model/HeatPumpAirToWater.hpp"
#include "../../model/HeatPumpAirToWater_Impl.hpp"
#include "../../model/HeatPumpAirToWaterCooling.hpp"
#include "../../model/HeatPumpAirToWaterCooling_Impl.hpp"
#include "../../model/HeatPumpAirToWaterCoolingSpeedData.hpp"
#include "../../model/HeatPumpAirToWaterCoolingSpeedData_Impl.hpp"
#include "../../model/HeatPumpAirToWaterHeating.hpp"
#include "../../model/HeatPumpAirToWaterHeating_Impl.hpp"
#include "../../model/HeatPumpAirToWaterHeatingSpeedData.hpp"
#include "../../model/HeatPumpAirToWaterHeatingSpeedData_Impl.hpp"

#include "../../model/Model.hpp"
#include "../../model/Curve.hpp"
#include "../../model/Curve_Impl.hpp"
#include "../../model/CurveBiquadratic.hpp"
#include "../../model/CurveQuadratic.hpp"
#include "../../model/PlantLoop.hpp"
#include "../../model/Node.hpp"
#include "../../model/Schedule.hpp"
#include "../../model/ScheduleConstant.hpp"

#include "../../utilities/idf/Workspace.hpp"
#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"
#include "../../utilities/idf/WorkspaceObject_Impl.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include "../../utilities/idf/WorkspaceExtensibleGroup.hpp"

// E+ FieldEnums
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

#include <utilities/idd/HeatPump_AirToWater_FieldEnums.hxx>

#include <utilities/idd/BranchList_FieldEnums.hxx>
#include <utilities/idd/Branch_FieldEnums.hxx>
#include <utilities/idd/PlantEquipmentList_FieldEnums.hxx>
#include <utilities/idd/PlantEquipmentOperationSchemes_FieldEnums.hxx>
#include <utilities/idd/PlantEquipmentOperation_HeatingLoad_FieldEnums.hxx>
#include <utilities/idd/PlantEquipmentOperation_CoolingLoad_FieldEnums.hxx>
#include <utilities/idd/PlantEquipmentOperation_Uncontrolled_FieldEnums.hxx>
#include <utilities/idd/PlantLoop_FieldEnums.hxx>

using namespace openstudio::energyplus;
using namespace openstudio::model;
using namespace openstudio;

HeatPumpAirToWater makeAWHP(const Model& m) {

  HeatPumpAirToWater awhp(m);
  awhp.setName("AWHP");

  // Operating Mode Control Option for Multiple Unit: Required String
  EXPECT_TRUE(awhp.setOperatingModeControlOptionforMultipleUnit("CoolingPriority"));

  // Operating Mode Control Schedule Name: Optional Object
  ScheduleConstant operatingModeControlSchedule(m);
  operatingModeControlSchedule.setName(awhp.nameString() + " Operating Mode Control Schedule");
  EXPECT_TRUE(awhp.setOperatingModeControlSchedule(operatingModeControlSchedule));
  // Operating Mode Control Method: Required String
  EXPECT_EQ("ScheduledModes", awhp.operatingModeControlMethod());

  // Minimum Part Load Ratio: Required Double
  EXPECT_TRUE(awhp.setMinimumPartLoadRatio(0.6));

  // Air Inlet Node Name: Optional String
  EXPECT_TRUE(awhp.setAirInletNodeName(awhp.nameString() + " Air Inlet Node"));

  // Air Outlet Node Name: Optional String
  EXPECT_TRUE(awhp.setAirOutletNodeName(awhp.nameString() + " Air Outlet Node"));

  // Maximum Outdoor Dry Bulb Temperature For Defrost Operation: Required Double
  EXPECT_TRUE(awhp.setMaximumOutdoorDryBulbTemperatureForDefrostOperation(0.9));

  // Heat Pump Defrost Control: Required String
  EXPECT_TRUE(awhp.setHeatPumpDefrostControl("TimedEmpirical"));

  // Heat Pump Defrost Time Period Fraction: Required Double
  EXPECT_TRUE(awhp.setHeatPumpDefrostTimePeriodFraction(1.1));

  // Resistive Defrost Heater Capacity: Required Double
  EXPECT_TRUE(awhp.setResistiveDefrostHeaterCapacity(100.0));

  // Defrost Energy Input Ratio Function of Temperature Curve Name: Optional Object, BivariateFunctions
  CurveBiquadratic defrostEnergyInputRatioFunctionofTemperatureCurve(m);
  defrostEnergyInputRatioFunctionofTemperatureCurve.setName(awhp.nameString() + " Defrost EIR FT Curve");
  EXPECT_TRUE(awhp.setDefrostEnergyInputRatioFunctionofTemperatureCurve(defrostEnergyInputRatioFunctionofTemperatureCurve));

  // Heat Pump Multiplier: Required Integer
  EXPECT_TRUE(awhp.setHeatPumpMultiplier(14));

  // Control Type: Required String
  EXPECT_TRUE(awhp.setControlType("FixedSpeed"));

  // Crankcase Heater Capacity: Required Double
  EXPECT_TRUE(awhp.setCrankcaseHeaterCapacity(1.6));

  // Crankcase Heater Capacity Function of Temperature Curve Name: Optional Object, UnivariateFunctions
  CurveQuadratic crankcaseHeaterCapacityFunctionofTemperatureCurve(m);
  crankcaseHeaterCapacityFunctionofTemperatureCurve.setName("AWHP Crankcase Heater Cap FT Curve");
  EXPECT_TRUE(awhp.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(crankcaseHeaterCapacityFunctionofTemperatureCurve));

  // Maximum Ambient Temperature for Crankcase Heater Operation: Required Double
  EXPECT_TRUE(awhp.setMaximumAmbientTemperatureforCrankcaseHeaterOperation(1.8));

  return awhp;
}

HeatPumpAirToWaterHeating makeAWHP_Heating(const Model& m) {

  HeatPumpAirToWaterHeating awhp_hc(m);

  awhp_hc.setName("AWHP Heating");

  ScheduleConstant availabilitySchedule(m);
  availabilitySchedule.setName(awhp_hc.nameString() + " Avail Schedule");
  EXPECT_TRUE(awhp_hc.setAvailabilitySchedule(availabilitySchedule));

  // Rated Inlet Air Temperature: Required Double
  EXPECT_TRUE(awhp_hc.setRatedInletAirTemperature(0.4));

  // Rated Air Flow Rate: Required Double
  EXPECT_TRUE(awhp_hc.setRatedAirFlowRate(0.5));

  // Rated Leaving Water Temperature: Required Double
  EXPECT_TRUE(awhp_hc.setRatedLeavingWaterTemperature(0.6));

  // Rated Water Flow Rate: Required Double
  EXPECT_TRUE(awhp_hc.setRatedWaterFlowRate(0.7));

  // Minimum Outdoor Air Temperature: Required Double
  EXPECT_TRUE(awhp_hc.setMinimumOutdoorAirTemperature(0.8));

  // Maximum Outdoor Air Temperature: Required Double
  EXPECT_TRUE(awhp_hc.setMaximumOutdoorAirTemperature(0.9));

  // Minimum Leaving Water Temperature Curve Name: Optional Object
  CurveQuadratic minimumLeavingWaterTemperatureCurve(m);
  minimumLeavingWaterTemperatureCurve.setName(awhp_hc.nameString() + " MinLWT Curve");
  EXPECT_TRUE(awhp_hc.setMinimumLeavingWaterTemperatureCurve(minimumLeavingWaterTemperatureCurve));

  // Maximum Leaving Water Temperature Curve Name: Optional Object
  CurveQuadratic maximumLeavingWaterTemperatureCurve(m);
  maximumLeavingWaterTemperatureCurve.setName(awhp_hc.nameString() + " MaxLWT Curve");
  EXPECT_TRUE(awhp_hc.setMaximumLeavingWaterTemperatureCurve(maximumLeavingWaterTemperatureCurve));

  // Sizing Factor: Required Double
  EXPECT_TRUE(awhp_hc.setSizingFactor(1.2));

  // Booster Mode On Speed: Optional Object
  HeatPumpAirToWaterHeatingSpeedData boosterModeOnSpeed(m);
  boosterModeOnSpeed.setName(awhp_hc.nameString() + " Booster Mode On Speed");
  boosterModeOnSpeed.setRatedHeatingCapacity(6000.0);
  boosterModeOnSpeed.setRatedCOPforHeating(3.0);
  boosterModeOnSpeed.normalizedHeatingCapacityFunctionofTemperatureCurve().setName(boosterModeOnSpeed.nameString() + " CapFT Curve");
  boosterModeOnSpeed.heatingEnergyInputRatioFunctionofTemperatureCurve().setName(boosterModeOnSpeed.nameString() + " EIRfT Curve");
  boosterModeOnSpeed.heatingEnergyInputRatioFunctionofPLRCurve().setName(boosterModeOnSpeed.nameString() + " EIRfPLR Curve");
  EXPECT_TRUE(awhp_hc.setBoosterModeOnSpeed(boosterModeOnSpeed));

  for (unsigned i = 1; i <= HeatPumpAirToWaterHeating::maximum_number_of_speeds; ++i) {
    HeatPumpAirToWaterHeatingSpeedData speed(m);
    speed.setName(awhp_hc.nameString() + " Speed " + std::to_string(i));
    if (i == HeatPumpAirToWaterCooling::maximum_number_of_speeds) {
      speed.autosizeRatedHeatingCapacity();
    } else {
      speed.setRatedHeatingCapacity(1000.0 * i);
    }
    speed.setRatedCOPforHeating(4.0 - 0.1 * (i - 1));
    speed.normalizedHeatingCapacityFunctionofTemperatureCurve().setName(speed.nameString() + " CapFT Curve");
    speed.heatingEnergyInputRatioFunctionofTemperatureCurve().setName(speed.nameString() + " EIRfT Curve");
    speed.heatingEnergyInputRatioFunctionofPLRCurve().setName(speed.nameString() + " EIRfPLR Curve");
    EXPECT_TRUE(awhp_hc.addSpeed(speed));
  }

  return awhp_hc;
}

HeatPumpAirToWaterCooling makeAWHP_Cooling(const Model& m) {

  HeatPumpAirToWaterCooling awhp_cc(m);

  awhp_cc.setName("AWHP Cooling");

  ScheduleConstant availabilitySchedule(m);
  availabilitySchedule.setName(awhp_cc.nameString() + " Avail Schedule");
  EXPECT_TRUE(awhp_cc.setAvailabilitySchedule(availabilitySchedule));

  // Rated Inlet Air Temperature: Required Double
  EXPECT_TRUE(awhp_cc.setRatedInletAirTemperature(0.6));

  // Rated Air Flow Rate: Required Double
  EXPECT_TRUE(awhp_cc.setRatedAirFlowRate(0.7));

  // Rated Leaving Water Temperature: Required Double
  EXPECT_TRUE(awhp_cc.setRatedLeavingWaterTemperature(0.8));

  // Rated Water Flow Rate: Required Double
  EXPECT_TRUE(awhp_cc.setRatedWaterFlowRate(0.9));

  // Minimum Outdoor Air Temperature: Required Double
  EXPECT_TRUE(awhp_cc.setMinimumOutdoorAirTemperature(-5.0));

  // Maximum Outdoor Air Temperature: Required Double
  EXPECT_TRUE(awhp_cc.setMaximumOutdoorAirTemperature(50.0));

  // Minimum Leaving Water Temperature Curve Name: Optional Object
  CurveQuadratic minimumLeavingWaterTemperatureCurve(m);
  minimumLeavingWaterTemperatureCurve.setName(awhp_cc.nameString() + " MinLWT Curve");
  EXPECT_TRUE(awhp_cc.setMinimumLeavingWaterTemperatureCurve(minimumLeavingWaterTemperatureCurve));

  // Maximum Leaving Water Temperature Curve Name: Optional Object
  CurveQuadratic maximumLeavingWaterTemperatureCurve(m);
  maximumLeavingWaterTemperatureCurve.setName(awhp_cc.nameString() + " MaxLWT Curve");
  EXPECT_TRUE(awhp_cc.setMaximumLeavingWaterTemperatureCurve(maximumLeavingWaterTemperatureCurve));

  // Sizing Factor: Required Double
  EXPECT_TRUE(awhp_cc.setSizingFactor(1.5));

  // Booster Mode On Speed: Optional Object
  HeatPumpAirToWaterCoolingSpeedData boosterModeOnSpeed(m);
  boosterModeOnSpeed.setName(awhp_cc.nameString() + " Booster Mode On Speed");
  boosterModeOnSpeed.setRatedCoolingCapacity(12000.0);
  boosterModeOnSpeed.setRatedCOPforCooling(3.5);
  boosterModeOnSpeed.normalizedCoolingCapacityFunctionofTemperatureCurve().setName(boosterModeOnSpeed.nameString() + " CapFT Curve");
  boosterModeOnSpeed.coolingEnergyInputRatioFunctionofTemperatureCurve().setName(boosterModeOnSpeed.nameString() + " EIRfT Curve");
  boosterModeOnSpeed.coolingEnergyInputRatioFunctionofPLRCurve().setName(boosterModeOnSpeed.nameString() + " EIRfPLR Curve");
  EXPECT_TRUE(awhp_cc.setBoosterModeOnSpeed(boosterModeOnSpeed));

  for (unsigned i = 1; i <= HeatPumpAirToWaterCooling::maximum_number_of_speeds; ++i) {
    HeatPumpAirToWaterCoolingSpeedData speed(m);
    speed.setName(awhp_cc.nameString() + " Speed " + std::to_string(i));
    if (i == HeatPumpAirToWaterCooling::maximum_number_of_speeds) {
      speed.autosizeRatedCoolingCapacity();
    } else {
      speed.setRatedCoolingCapacity(2000.0 * i);
    }

    speed.setRatedCOPforCooling(4.5 - 0.1 * (i - 1));
    speed.normalizedCoolingCapacityFunctionofTemperatureCurve().setName(speed.nameString() + " CapFT Curve");
    speed.coolingEnergyInputRatioFunctionofTemperatureCurve().setName(speed.nameString() + " EIRfT Curve");
    speed.coolingEnergyInputRatioFunctionofPLRCurve().setName(speed.nameString() + " EIRfPLR Curve");
    EXPECT_TRUE(awhp_cc.addSpeed(speed));
  }

  return awhp_cc;
}

PlantLoop createLoop(Model& m, const std::string& prefix) {
  PlantLoop p(m);
  static constexpr std::array<std::string_view, 10> compNames = {
    "Supply Inlet", "Supply Splitter", "Supply Connection Node", "Supply Mixer", "Supply Outlet",
    "Demand Inlet", "Demand Splitter", "Demand Connection Node", "Demand Mixer", "Demand Outlet",
  };
  p.setName(prefix);
  for (size_t i = 0; auto& comp : p.components()) {
    comp.setName(prefix + " " + std::string{compNames[i++]});
  }
  return p;
}

TEST_F(EnergyPlusFixture, ForwardTranslator_HeatPumpAirToWater) {

  ForwardTranslator ft;
  ft.setExcludeLCCObjects(true);

  Model m;

  HeatPumpAirToWater awhp = makeAWHP(m);
  HeatPumpAirToWaterHeating awhp_hc = makeAWHP_Heating(m);
  EXPECT_TRUE(awhp.setHeatingOperationMode(awhp_hc));

  HeatPumpAirToWaterCooling awhp_cc = makeAWHP_Cooling(m);
  EXPECT_TRUE(awhp.setCoolingOperationMode(awhp_cc));

  // Not on a PlantLoop: not translated
  {
    const Workspace w = ft.translateModel(m);
    const auto idfObjs = w.getObjectsByType(IddObjectType::HeatPump_AirToWater);
    ASSERT_EQ(0u, idfObjs.size());
  }

  PlantLoop hwLoop = createLoop(m, "HW Loop");
  EXPECT_TRUE(hwLoop.addSupplyBranchForComponent(awhp_hc));

  // Check node names on supply/demand branches
  // Checks that the special case implemented in ForwardTranslatePlantLoop::populateBranch does the right job

  struct Expected
  {
    bool isHeating = true;
    std::string plantName;
    std::string inletNodeName;
    std::string outletNodeName;
  };

  // Only on a Heating Loop, so even though I have a cooling operation mode and speeds for it, only the heating side is translated
  {
    Workspace w = ft.translateModel(m);

    const auto idfObjs = w.getObjectsByType(IddObjectType::HeatPump_AirToWater);
    ASSERT_EQ(1u, idfObjs.size());

    const auto& idfObject = idfObjs.front();
    EXPECT_EQ("ScheduledModes", idfObject.getString(HeatPump_AirToWaterFields::OperatingModeControlMethod).get());
    EXPECT_EQ("CoolingPriority", idfObject.getString(HeatPump_AirToWaterFields::OperatingModeControlOptionforMultipleUnit).get());
    EXPECT_EQ("AWHP Operating Mode Control Schedule", idfObject.getString(HeatPump_AirToWaterFields::OperatingModeControlScheduleName).get());
    EXPECT_EQ(0.6, idfObject.getDouble(HeatPump_AirToWaterFields::MinimumPartLoadRatio).get());

    EXPECT_EQ("AWHP Air Inlet Node", idfObject.getString(HeatPump_AirToWaterFields::AirInletNodeName).get());
    EXPECT_EQ("AWHP Air Outlet Node", idfObject.getString(HeatPump_AirToWaterFields::AirOutletNodeName).get());

    EXPECT_EQ(0.9, idfObject.getDouble(HeatPump_AirToWaterFields::MaximumOutdoorDryBulbTemperatureForDefrostOperation).get());
    EXPECT_EQ("TimedEmpirical", idfObject.getString(HeatPump_AirToWaterFields::HeatPumpDefrostControl).get());
    EXPECT_EQ(1.1, idfObject.getDouble(HeatPump_AirToWaterFields::HeatPumpDefrostTimePeriodFraction).get());
    EXPECT_EQ(100.0, idfObject.getDouble(HeatPump_AirToWaterFields::ResistiveDefrostHeaterCapacity).get());
    EXPECT_EQ("AWHP Defrost EIR FT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::DefrostEnergyInputRatioFunctionofTemperatureCurveName).get());
    EXPECT_EQ(14, idfObject.getInt(HeatPump_AirToWaterFields::HeatPumpMultiplier).get());
    EXPECT_EQ("FixedSpeed", idfObject.getString(HeatPump_AirToWaterFields::ControlType).get());
    EXPECT_EQ(1.6, idfObject.getDouble(HeatPump_AirToWaterFields::CrankcaseHeaterCapacity).get());
    EXPECT_EQ("AWHP Crankcase Heater Cap FT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName).get());
    EXPECT_EQ(1.8, idfObject.getDouble(HeatPump_AirToWaterFields::MaximumAmbientTemperatureforCrankcaseHeaterOperation).get());

    // Heating
    EXPECT_EQ("AWHP Heating Avail Schedule", idfObject.getString(HeatPump_AirToWaterFields::AvailabilityScheduleNameHeating).get());
    EXPECT_EQ(0.4, idfObject.getDouble(HeatPump_AirToWaterFields::RatedInletAirTemperatureinHeatingMode).get());
    // EXPECT_EQ("Autosize", idfObject.getString(HeatPump_AirToWaterFields::RatedAirFlowRateinHeatingMode).get());
    EXPECT_EQ(0.5, idfObject.getDouble(HeatPump_AirToWaterFields::RatedAirFlowRateinHeatingMode).get());
    EXPECT_EQ(0.6, idfObject.getDouble(HeatPump_AirToWaterFields::RatedLeavingWaterTemperatureinHeatingMode).get());
    // EXPECT_EQ("Autosize", idfObject.getString(HeatPump_AirToWaterFields::RatedWaterFlowRateinHeatingMode).get());
    EXPECT_EQ(0.7, idfObject.getDouble(HeatPump_AirToWaterFields::RatedWaterFlowRateinHeatingMode).get());
    EXPECT_EQ(0.8, idfObject.getDouble(HeatPump_AirToWaterFields::MinimumOutdoorAirTemperatureinHeatingMode).get());
    EXPECT_EQ(0.9, idfObject.getDouble(HeatPump_AirToWaterFields::MaximumOutdoorAirTemperatureinHeatingMode).get());
    EXPECT_EQ("AWHP Heating MinLWT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::MinimumLeavingWaterTemperatureCurveNameinHeatingMode).get());
    EXPECT_EQ("AWHP Heating MaxLWT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::MaximumLeavingWaterTemperatureCurveNameinHeatingMode).get());

    EXPECT_EQ(1.2, idfObject.getDouble(HeatPump_AirToWaterFields::SizingFactorforHeating).get());

    EXPECT_EQ(awhp_hc.inletModelObject()->nameString(), idfObject.getString(HeatPump_AirToWaterFields::HotWaterInletNodeName).get());
    EXPECT_EQ(awhp_hc.outletModelObject()->nameString(), idfObject.getString(HeatPump_AirToWaterFields::HotWaterOutletNodeName).get());

    EXPECT_EQ(5, idfObject.getInt(HeatPump_AirToWaterFields::NumberofSpeedsforHeating).get());

    // EXPECT_EQ("Autosize", idfObject.getString(HeatPump_AirToWaterFields::RatedHeatingCapacityatSpeed1).get());
    EXPECT_EQ(1000.0, idfObject.getDouble(HeatPump_AirToWaterFields::RatedHeatingCapacityatSpeed1).get());
    EXPECT_EQ(4.0, idfObject.getDouble(HeatPump_AirToWaterFields::RatedCOPforHeatingatSpeed1).get());
    EXPECT_EQ("AWHP Heating Speed 1 CapFT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::NormalizedHeatingCapacityFunctionofTemperatureCurveNameatSpeed1).get());
    EXPECT_EQ("AWHP Heating Speed 1 EIRfT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofTemperatureCurveNameatSpeed1).get());
    EXPECT_EQ("AWHP Heating Speed 1 EIRfPLR Curve",
              idfObject.getString(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofPLRCurveNameatSpeed1).get());
    EXPECT_EQ(2000.0, idfObject.getDouble(HeatPump_AirToWaterFields::RatedHeatingCapacityatSpeed2).get());
    EXPECT_EQ(3.9, idfObject.getDouble(HeatPump_AirToWaterFields::RatedCOPforHeatingatSpeed2).get());
    EXPECT_EQ("AWHP Heating Speed 2 CapFT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::NormalizedHeatingCapacityFunctionofTemperatureCurveNameatSpeed2).get());
    EXPECT_EQ("AWHP Heating Speed 2 EIRfT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofTemperatureCurveNameatSpeed2).get());
    EXPECT_EQ("AWHP Heating Speed 2 EIRfPLR Curve",
              idfObject.getString(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofPLRCurveNameatSpeed2).get());
    EXPECT_EQ(3000.0, idfObject.getDouble(HeatPump_AirToWaterFields::RatedHeatingCapacityatSpeed3).get());
    EXPECT_EQ(3.8, idfObject.getDouble(HeatPump_AirToWaterFields::RatedCOPforHeatingatSpeed3).get());
    EXPECT_EQ("AWHP Heating Speed 3 CapFT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::NormalizedHeatingCapacityFunctionofTemperatureCurveNameatSpeed3).get());
    EXPECT_EQ("AWHP Heating Speed 3 EIRfT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofTemperatureCurveNameatSpeed3).get());
    EXPECT_EQ("AWHP Heating Speed 3 EIRfPLR Curve",
              idfObject.getString(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofPLRCurveNameatSpeed3).get());
    EXPECT_EQ(4000.0, idfObject.getDouble(HeatPump_AirToWaterFields::RatedHeatingCapacityatSpeed4).get());
    EXPECT_EQ(3.7, idfObject.getDouble(HeatPump_AirToWaterFields::RatedCOPforHeatingatSpeed4).get());
    EXPECT_EQ("AWHP Heating Speed 4 CapFT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::NormalizedHeatingCapacityFunctionofTemperatureCurveNameatSpeed4).get());
    EXPECT_EQ("AWHP Heating Speed 4 EIRfT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofTemperatureCurveNameatSpeed4).get());
    EXPECT_EQ("AWHP Heating Speed 4 EIRfPLR Curve",
              idfObject.getString(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofPLRCurveNameatSpeed4).get());
    EXPECT_EQ("Autosize", idfObject.getString(HeatPump_AirToWaterFields::RatedHeatingCapacityatSpeed5).get());
    EXPECT_EQ(3.6, idfObject.getDouble(HeatPump_AirToWaterFields::RatedCOPforHeatingatSpeed5).get());
    EXPECT_EQ("AWHP Heating Speed 5 CapFT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::NormalizedHeatingCapacityFunctionofTemperatureCurveNameatSpeed5).get());
    EXPECT_EQ("AWHP Heating Speed 5 EIRfT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofTemperatureCurveNameatSpeed5).get());
    EXPECT_EQ("AWHP Heating Speed 5 EIRfPLR Curve",
              idfObject.getString(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofPLRCurveNameatSpeed5).get());
    EXPECT_EQ("Yes", idfObject.getString(HeatPump_AirToWaterFields::BoosterModeOnHeating).get());
    EXPECT_EQ(6000.0, idfObject.getDouble(HeatPump_AirToWaterFields::RatedHeatingCapacityinBoosterMode).get());
    EXPECT_EQ(3.0, idfObject.getDouble(HeatPump_AirToWaterFields::RatedHeatingCOPinBoosterMode).get());
    EXPECT_EQ("AWHP Heating Booster Mode On Speed CapFT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::NormalizedHeatingCapacityFunctionofTemperatureCurveNameinBoosterMode).get());
    EXPECT_EQ("AWHP Heating Booster Mode On Speed EIRfT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofTemperatureCurveNameinBoosterMode).get());
    EXPECT_EQ("AWHP Heating Booster Mode On Speed EIRfPLR Curve",
              idfObject.getString(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofPLRCurveNameinBoosterMode).get());

    // COOLING
    // Everything cooling is empty
    EXPECT_TRUE(idfObject.isEmpty(HeatPump_AirToWaterFields::AvailabilityScheduleNameCooling));
    EXPECT_TRUE(idfObject.isEmpty(HeatPump_AirToWaterFields::RatedInletAirTemperatureinCoolingMode));
    EXPECT_TRUE(idfObject.isEmpty(HeatPump_AirToWaterFields::RatedAirFlowRateinCoolingMode));
    EXPECT_TRUE(idfObject.isEmpty(HeatPump_AirToWaterFields::RatedLeavingWaterTemperatureinCoolingMode));
    EXPECT_TRUE(idfObject.isEmpty(HeatPump_AirToWaterFields::RatedWaterFlowRateinCoolingMode));
    EXPECT_TRUE(idfObject.isEmpty(HeatPump_AirToWaterFields::MinimumOutdoorAirTemperatureinCoolingMode));
    EXPECT_TRUE(idfObject.isEmpty(HeatPump_AirToWaterFields::MaximumOutdoorAirTemperatureinCoolingMode));
    EXPECT_TRUE(idfObject.isEmpty(HeatPump_AirToWaterFields::MinimumLeavingWaterTemperatureCurveNameinCoolingMode));
    EXPECT_TRUE(idfObject.isEmpty(HeatPump_AirToWaterFields::MaximumLeavingWaterTemperatureCurveNameinCoolingMode));
    EXPECT_TRUE(idfObject.isEmpty(HeatPump_AirToWaterFields::SizingFactorforCooling));
    EXPECT_TRUE(idfObject.isEmpty(HeatPump_AirToWaterFields::ChilledWaterInletNodeName));
    EXPECT_TRUE(idfObject.isEmpty(HeatPump_AirToWaterFields::ChilledWaterOutletNodeName));

    EXPECT_EQ(0, idfObject.getInt(HeatPump_AirToWaterFields::NumberofSpeedsforCooling).get());

    for (unsigned index = HeatPump_AirToWaterFields::RatedCoolingCapacityatSpeed1;
         index <= HeatPump_AirToWaterFields::CoolingEnergyInputRatioFunctionofPLRCurveNameatSpeed5; ++index) {
      EXPECT_TRUE(idfObject.isEmpty(index));
    }

    EXPECT_TRUE(idfObject.isEmpty(HeatPump_AirToWaterFields::ChilledWaterInletNodeName));
    EXPECT_TRUE(idfObject.isEmpty(HeatPump_AirToWaterFields::ChilledWaterOutletNodeName));

    EXPECT_TRUE(idfObject.isEmpty(HeatPump_AirToWaterFields::BoosterModeOnCooling));
    EXPECT_TRUE(idfObject.isEmpty(HeatPump_AirToWaterFields::RatedCoolingCapacityinBoosterMode));
    EXPECT_TRUE(idfObject.isEmpty(HeatPump_AirToWaterFields::RatedCoolingCOPinBoosterMode));
    EXPECT_TRUE(idfObject.isEmpty(HeatPump_AirToWaterFields::NormalizedCoolingCapacityFunctionofTemperatureCurveNameinBoosterMode));
    EXPECT_TRUE(idfObject.isEmpty(HeatPump_AirToWaterFields::CoolingEnergyInputRatioFunctionofTemperatureCurveNameinBoosterMode));
    EXPECT_TRUE(idfObject.isEmpty(HeatPump_AirToWaterFields::CoolingEnergyInputRatioFunctionofPLRCurveNameinBoosterMode));

    const size_t expectedNumCurves = 1                   // defrostEnergyInputRatioFunctionofTemperatureCurve
                                     + 1                 // crankcaseHeaterCapacityFunctionofTemperatureCurve
                                     + 2 * 2             // awhp_hc/cc min/max LWT curves
                                     + 2 * (5 + 1) * 3;  // awhp_hc/cc: 5 speeds + one booster mode, each with 3 curves
    EXPECT_EQ(expectedNumCurves,
              w.getObjectsByType(IddObjectType::Curve_Biquadratic).size() + w.getObjectsByType(IddObjectType::Curve_Quadratic).size());
    auto oaNodeList = w.getObjectsByType(IddObjectType::OutdoorAir_NodeList);
    ASSERT_EQ(1, oaNodeList.size());
    EXPECT_EQ("AWHP Air Inlet Node", oaNodeList.front().getString(0).get());
    EXPECT_EQ("AWHP Air Outlet Node", oaNodeList.front().getString(1).get());

    EXPECT_EQ(1, w.getObjectsByType(IddObjectType::PlantLoop).size());

    std::vector<Expected> expecteds = {
      Expected{.isHeating = true,
               .plantName = hwLoop.nameString(),
               .inletNodeName = awhp_hc.inletModelObject()->nameString(),
               .outletNodeName = awhp_hc.outletModelObject()->nameString()},
    };
    for (const auto& e : expecteds) {
      auto p_ = w.getObjectByTypeAndName(IddObjectType::PlantLoop, e.plantName);
      ASSERT_TRUE(p_.is_initialized()) << "Cannot find PlantLoop named " << e.plantName;
      WorkspaceObject idf_plant = p_.get();
      WorkspaceObject idf_brlist = idf_plant.getTarget(PlantLoopFields::PlantSideBranchListName).get();

      // Should have at three branches: supply inlet, the one with the AWHP, supply outlet.
      ASSERT_EQ(3, idf_brlist.extensibleGroups().size()) << "Failed for " << e.plantName;
      // Get the AWHP one
      auto w_eg = idf_brlist.extensibleGroups()[1].cast<WorkspaceExtensibleGroup>();
      WorkspaceObject idf_branch = w_eg.getTarget(BranchListExtensibleFields::BranchName).get();

      // There should be only one equipment on the branch
      ASSERT_EQ(1, idf_branch.extensibleGroups().size());
      auto w_eg2 = idf_branch.extensibleGroups()[0].cast<WorkspaceExtensibleGroup>();

      ASSERT_EQ(w_eg2.getString(BranchExtensibleFields::ComponentName).get(), awhp.nameString());
      ASSERT_EQ(w_eg2.getString(BranchExtensibleFields::ComponentInletNodeName).get(), e.inletNodeName);
      ASSERT_EQ(w_eg2.getString(BranchExtensibleFields::ComponentOutletNodeName).get(), e.outletNodeName);

      WorkspaceObject idf_plant_op = p_->getTarget(PlantLoopFields::PlantEquipmentOperationSchemeName).get();
      // Should have created a Cooling Load one only
      ASSERT_EQ(1, idf_plant_op.extensibleGroups().size());
      auto w_eg_schemes = idf_plant_op.extensibleGroups()[0].cast<WorkspaceExtensibleGroup>();
      ASSERT_EQ(e.isHeating ? "PlantEquipmentOperation:HeatingLoad" : "PlantEquipmentOperation:CoolingLoad",
                w_eg_schemes.getString(PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeObjectType).get());

      // Get the Operation Scheme
      auto op_scheme_ = w_eg_schemes.getTarget(PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeName);
      ASSERT_TRUE(op_scheme_);

      // Get the Plant Equipment List of this CoolingLoad/HeatingLoad scheme
      // There should only be one Load Range
      ASSERT_EQ(1u, op_scheme_->extensibleGroups().size());

      // Load range 1
      w_eg = op_scheme_->extensibleGroups()[0].cast<WorkspaceExtensibleGroup>();
      boost::optional<WorkspaceObject> peq_list_;
      if (e.isHeating) {
        peq_list_ = w_eg.getTarget(PlantEquipmentOperation_HeatingLoadExtensibleFields::RangeEquipmentListName);
      } else {
        peq_list_ = w_eg.getTarget(PlantEquipmentOperation_CoolingLoadExtensibleFields::RangeEquipmentListName);
      }
      ASSERT_TRUE(peq_list_);

      // Should have one equipment on it: HeatPump:AirToWater
      auto peqs = peq_list_->extensibleGroups();
      ASSERT_EQ(1, peqs.size());
      ASSERT_EQ("HeatPump:AirToWater", peqs.front().getString(PlantEquipmentListExtensibleFields::EquipmentObjectType).get());
      ASSERT_EQ(awhp.nameString(), peqs.front().getString(PlantEquipmentListExtensibleFields::EquipmentName).get());
    }
  }

  PlantLoop chwLoop = createLoop(m, "ChW Loop");
  EXPECT_TRUE(chwLoop.addSupplyBranchForComponent(awhp_cc));

  // On both a Heating and a Cooling Loop
  {
    Workspace w = ft.translateModel(m);

    const auto idfObjs = w.getObjectsByType(IddObjectType::HeatPump_AirToWater);
    ASSERT_EQ(1u, idfObjs.size());

    const auto& idfObject = idfObjs.front();
    EXPECT_EQ("ScheduledModes", idfObject.getString(HeatPump_AirToWaterFields::OperatingModeControlMethod).get());
    EXPECT_EQ("CoolingPriority", idfObject.getString(HeatPump_AirToWaterFields::OperatingModeControlOptionforMultipleUnit).get());
    EXPECT_EQ("AWHP Operating Mode Control Schedule", idfObject.getString(HeatPump_AirToWaterFields::OperatingModeControlScheduleName).get());
    EXPECT_EQ(0.6, idfObject.getDouble(HeatPump_AirToWaterFields::MinimumPartLoadRatio).get());

    EXPECT_EQ("AWHP Air Inlet Node", idfObject.getString(HeatPump_AirToWaterFields::AirInletNodeName).get());
    EXPECT_EQ("AWHP Air Outlet Node", idfObject.getString(HeatPump_AirToWaterFields::AirOutletNodeName).get());

    EXPECT_EQ(0.9, idfObject.getDouble(HeatPump_AirToWaterFields::MaximumOutdoorDryBulbTemperatureForDefrostOperation).get());
    EXPECT_EQ("TimedEmpirical", idfObject.getString(HeatPump_AirToWaterFields::HeatPumpDefrostControl).get());
    EXPECT_EQ(1.1, idfObject.getDouble(HeatPump_AirToWaterFields::HeatPumpDefrostTimePeriodFraction).get());
    EXPECT_EQ(100.0, idfObject.getDouble(HeatPump_AirToWaterFields::ResistiveDefrostHeaterCapacity).get());
    EXPECT_EQ("AWHP Defrost EIR FT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::DefrostEnergyInputRatioFunctionofTemperatureCurveName).get());
    EXPECT_EQ(14, idfObject.getInt(HeatPump_AirToWaterFields::HeatPumpMultiplier).get());
    EXPECT_EQ("FixedSpeed", idfObject.getString(HeatPump_AirToWaterFields::ControlType).get());
    EXPECT_EQ(1.6, idfObject.getDouble(HeatPump_AirToWaterFields::CrankcaseHeaterCapacity).get());
    EXPECT_EQ("AWHP Crankcase Heater Cap FT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName).get());
    EXPECT_EQ(1.8, idfObject.getDouble(HeatPump_AirToWaterFields::MaximumAmbientTemperatureforCrankcaseHeaterOperation).get());

    // Heating
    EXPECT_EQ("AWHP Heating Avail Schedule", idfObject.getString(HeatPump_AirToWaterFields::AvailabilityScheduleNameHeating).get());
    EXPECT_EQ(0.4, idfObject.getDouble(HeatPump_AirToWaterFields::RatedInletAirTemperatureinHeatingMode).get());
    // EXPECT_EQ("Autosize", idfObject.getString(HeatPump_AirToWaterFields::RatedAirFlowRateinHeatingMode).get());
    EXPECT_EQ(0.5, idfObject.getDouble(HeatPump_AirToWaterFields::RatedAirFlowRateinHeatingMode).get());
    EXPECT_EQ(0.6, idfObject.getDouble(HeatPump_AirToWaterFields::RatedLeavingWaterTemperatureinHeatingMode).get());
    // EXPECT_EQ("Autosize", idfObject.getString(HeatPump_AirToWaterFields::RatedWaterFlowRateinHeatingMode).get());
    EXPECT_EQ(0.7, idfObject.getDouble(HeatPump_AirToWaterFields::RatedWaterFlowRateinHeatingMode).get());
    EXPECT_EQ(0.8, idfObject.getDouble(HeatPump_AirToWaterFields::MinimumOutdoorAirTemperatureinHeatingMode).get());
    EXPECT_EQ(0.9, idfObject.getDouble(HeatPump_AirToWaterFields::MaximumOutdoorAirTemperatureinHeatingMode).get());
    EXPECT_EQ("AWHP Heating MinLWT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::MinimumLeavingWaterTemperatureCurveNameinHeatingMode).get());
    EXPECT_EQ("AWHP Heating MaxLWT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::MaximumLeavingWaterTemperatureCurveNameinHeatingMode).get());

    EXPECT_EQ(1.2, idfObject.getDouble(HeatPump_AirToWaterFields::SizingFactorforHeating).get());

    EXPECT_EQ(awhp_hc.inletModelObject()->nameString(), idfObject.getString(HeatPump_AirToWaterFields::HotWaterInletNodeName).get());
    EXPECT_EQ(awhp_hc.outletModelObject()->nameString(), idfObject.getString(HeatPump_AirToWaterFields::HotWaterOutletNodeName).get());

    EXPECT_EQ(5, idfObject.getInt(HeatPump_AirToWaterFields::NumberofSpeedsforHeating).get());

    // EXPECT_EQ("Autosize", idfObject.getString(HeatPump_AirToWaterFields::RatedHeatingCapacityatSpeed1).get());
    EXPECT_EQ(1000.0, idfObject.getDouble(HeatPump_AirToWaterFields::RatedHeatingCapacityatSpeed1).get());
    EXPECT_EQ(4.0, idfObject.getDouble(HeatPump_AirToWaterFields::RatedCOPforHeatingatSpeed1).get());
    EXPECT_EQ("AWHP Heating Speed 1 CapFT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::NormalizedHeatingCapacityFunctionofTemperatureCurveNameatSpeed1).get());
    EXPECT_EQ("AWHP Heating Speed 1 EIRfT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofTemperatureCurveNameatSpeed1).get());
    EXPECT_EQ("AWHP Heating Speed 1 EIRfPLR Curve",
              idfObject.getString(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofPLRCurveNameatSpeed1).get());
    EXPECT_EQ(2000.0, idfObject.getDouble(HeatPump_AirToWaterFields::RatedHeatingCapacityatSpeed2).get());
    EXPECT_EQ(3.9, idfObject.getDouble(HeatPump_AirToWaterFields::RatedCOPforHeatingatSpeed2).get());
    EXPECT_EQ("AWHP Heating Speed 2 CapFT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::NormalizedHeatingCapacityFunctionofTemperatureCurveNameatSpeed2).get());
    EXPECT_EQ("AWHP Heating Speed 2 EIRfT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofTemperatureCurveNameatSpeed2).get());
    EXPECT_EQ("AWHP Heating Speed 2 EIRfPLR Curve",
              idfObject.getString(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofPLRCurveNameatSpeed2).get());
    EXPECT_EQ(3000.0, idfObject.getDouble(HeatPump_AirToWaterFields::RatedHeatingCapacityatSpeed3).get());
    EXPECT_EQ(3.8, idfObject.getDouble(HeatPump_AirToWaterFields::RatedCOPforHeatingatSpeed3).get());
    EXPECT_EQ("AWHP Heating Speed 3 CapFT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::NormalizedHeatingCapacityFunctionofTemperatureCurveNameatSpeed3).get());
    EXPECT_EQ("AWHP Heating Speed 3 EIRfT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofTemperatureCurveNameatSpeed3).get());
    EXPECT_EQ("AWHP Heating Speed 3 EIRfPLR Curve",
              idfObject.getString(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofPLRCurveNameatSpeed3).get());
    EXPECT_EQ(4000.0, idfObject.getDouble(HeatPump_AirToWaterFields::RatedHeatingCapacityatSpeed4).get());
    EXPECT_EQ(3.7, idfObject.getDouble(HeatPump_AirToWaterFields::RatedCOPforHeatingatSpeed4).get());
    EXPECT_EQ("AWHP Heating Speed 4 CapFT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::NormalizedHeatingCapacityFunctionofTemperatureCurveNameatSpeed4).get());
    EXPECT_EQ("AWHP Heating Speed 4 EIRfT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofTemperatureCurveNameatSpeed4).get());
    EXPECT_EQ("AWHP Heating Speed 4 EIRfPLR Curve",
              idfObject.getString(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofPLRCurveNameatSpeed4).get());
    EXPECT_EQ("Autosize", idfObject.getString(HeatPump_AirToWaterFields::RatedHeatingCapacityatSpeed5).get());
    EXPECT_EQ(3.6, idfObject.getDouble(HeatPump_AirToWaterFields::RatedCOPforHeatingatSpeed5).get());
    EXPECT_EQ("AWHP Heating Speed 5 CapFT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::NormalizedHeatingCapacityFunctionofTemperatureCurveNameatSpeed5).get());
    EXPECT_EQ("AWHP Heating Speed 5 EIRfT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofTemperatureCurveNameatSpeed5).get());
    EXPECT_EQ("AWHP Heating Speed 5 EIRfPLR Curve",
              idfObject.getString(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofPLRCurveNameatSpeed5).get());
    EXPECT_EQ("Yes", idfObject.getString(HeatPump_AirToWaterFields::BoosterModeOnHeating).get());
    EXPECT_EQ(6000.0, idfObject.getDouble(HeatPump_AirToWaterFields::RatedHeatingCapacityinBoosterMode).get());
    EXPECT_EQ(3.0, idfObject.getDouble(HeatPump_AirToWaterFields::RatedHeatingCOPinBoosterMode).get());
    EXPECT_EQ("AWHP Heating Booster Mode On Speed CapFT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::NormalizedHeatingCapacityFunctionofTemperatureCurveNameinBoosterMode).get());
    EXPECT_EQ("AWHP Heating Booster Mode On Speed EIRfT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofTemperatureCurveNameinBoosterMode).get());
    EXPECT_EQ("AWHP Heating Booster Mode On Speed EIRfPLR Curve",
              idfObject.getString(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofPLRCurveNameinBoosterMode).get());

    // COOLING
    EXPECT_EQ("AWHP Cooling Avail Schedule", idfObject.getString(HeatPump_AirToWaterFields::AvailabilityScheduleNameCooling).get());
    EXPECT_EQ(0.6, idfObject.getDouble(HeatPump_AirToWaterFields::RatedInletAirTemperatureinCoolingMode).get());
    // EXPECT_EQ("Autosize", idfObject.getString(HeatPump_AirToWaterFields::RatedAirFlowRateinCoolingMode).get());
    EXPECT_EQ(0.7, idfObject.getDouble(HeatPump_AirToWaterFields::RatedAirFlowRateinCoolingMode).get());
    EXPECT_EQ(0.8, idfObject.getDouble(HeatPump_AirToWaterFields::RatedLeavingWaterTemperatureinCoolingMode).get());
    // EXPECT_EQ("Autosize", idfObject.getString(HeatPump_AirToWaterFields::RatedWaterFlowRateinCoolingMode).get());
    EXPECT_EQ(0.9, idfObject.getDouble(HeatPump_AirToWaterFields::RatedWaterFlowRateinCoolingMode).get());
    EXPECT_EQ(-5.0, idfObject.getDouble(HeatPump_AirToWaterFields::MinimumOutdoorAirTemperatureinCoolingMode).get());
    EXPECT_EQ(50.0, idfObject.getDouble(HeatPump_AirToWaterFields::MaximumOutdoorAirTemperatureinCoolingMode).get());
    EXPECT_EQ("AWHP Cooling MinLWT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::MinimumLeavingWaterTemperatureCurveNameinCoolingMode).get());
    EXPECT_EQ("AWHP Cooling MaxLWT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::MaximumLeavingWaterTemperatureCurveNameinCoolingMode).get());

    EXPECT_EQ(1.5, idfObject.getDouble(HeatPump_AirToWaterFields::SizingFactorforCooling).get());

    EXPECT_EQ(awhp_cc.inletModelObject()->nameString(), idfObject.getString(HeatPump_AirToWaterFields::ChilledWaterInletNodeName).get());
    EXPECT_EQ(awhp_cc.outletModelObject()->nameString(), idfObject.getString(HeatPump_AirToWaterFields::ChilledWaterOutletNodeName).get());

    EXPECT_EQ(5, idfObject.getInt(HeatPump_AirToWaterFields::NumberofSpeedsforCooling).get());

    // EXPECT_EQ("Autosize", idfObject.getString(HeatPump_AirToWaterFields::RatedCoolingCapacityatSpeed1).get());
    EXPECT_EQ(2000.0, idfObject.getDouble(HeatPump_AirToWaterFields::RatedCoolingCapacityatSpeed1).get());
    EXPECT_EQ(4.5, idfObject.getDouble(HeatPump_AirToWaterFields::RatedCOPforCoolingatSpeed1).get());
    EXPECT_EQ("AWHP Cooling Speed 1 CapFT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::NormalizedCoolingCapacityFunctionofTemperatureCurveNameatSpeed1).get());
    EXPECT_EQ("AWHP Cooling Speed 1 EIRfT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::CoolingEnergyInputRatioFunctionofTemperatureCurveNameatSpeed1).get());
    EXPECT_EQ("AWHP Cooling Speed 1 EIRfPLR Curve",
              idfObject.getString(HeatPump_AirToWaterFields::CoolingEnergyInputRatioFunctionofPLRCurveNameatSpeed1).get());
    EXPECT_EQ(4000.0, idfObject.getDouble(HeatPump_AirToWaterFields::RatedCoolingCapacityatSpeed2).get());
    EXPECT_EQ(4.4, idfObject.getDouble(HeatPump_AirToWaterFields::RatedCOPforCoolingatSpeed2).get());
    EXPECT_EQ("AWHP Cooling Speed 2 CapFT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::NormalizedCoolingCapacityFunctionofTemperatureCurveNameatSpeed2).get());
    EXPECT_EQ("AWHP Cooling Speed 2 EIRfT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::CoolingEnergyInputRatioFunctionofTemperatureCurveNameatSpeed2).get());
    EXPECT_EQ("AWHP Cooling Speed 2 EIRfPLR Curve",
              idfObject.getString(HeatPump_AirToWaterFields::CoolingEnergyInputRatioFunctionofPLRCurveNameatSpeed2).get());
    EXPECT_EQ(6000.0, idfObject.getDouble(HeatPump_AirToWaterFields::RatedCoolingCapacityatSpeed3).get());
    EXPECT_EQ(4.3, idfObject.getDouble(HeatPump_AirToWaterFields::RatedCOPforCoolingatSpeed3).get());
    EXPECT_EQ("AWHP Cooling Speed 3 CapFT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::NormalizedCoolingCapacityFunctionofTemperatureCurveNameatSpeed3).get());
    EXPECT_EQ("AWHP Cooling Speed 3 EIRfT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::CoolingEnergyInputRatioFunctionofTemperatureCurveNameatSpeed3).get());
    EXPECT_EQ("AWHP Cooling Speed 3 EIRfPLR Curve",
              idfObject.getString(HeatPump_AirToWaterFields::CoolingEnergyInputRatioFunctionofPLRCurveNameatSpeed3).get());
    EXPECT_EQ(8000.0, idfObject.getDouble(HeatPump_AirToWaterFields::RatedCoolingCapacityatSpeed4).get());
    EXPECT_EQ(4.2, idfObject.getDouble(HeatPump_AirToWaterFields::RatedCOPforCoolingatSpeed4).get());
    EXPECT_EQ("AWHP Cooling Speed 4 CapFT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::NormalizedCoolingCapacityFunctionofTemperatureCurveNameatSpeed4).get());
    EXPECT_EQ("AWHP Cooling Speed 4 EIRfT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::CoolingEnergyInputRatioFunctionofTemperatureCurveNameatSpeed4).get());
    EXPECT_EQ("AWHP Cooling Speed 4 EIRfPLR Curve",
              idfObject.getString(HeatPump_AirToWaterFields::CoolingEnergyInputRatioFunctionofPLRCurveNameatSpeed4).get());
    EXPECT_EQ("Autosize", idfObject.getString(HeatPump_AirToWaterFields::RatedCoolingCapacityatSpeed5).get());
    EXPECT_EQ(4.1, idfObject.getDouble(HeatPump_AirToWaterFields::RatedCOPforCoolingatSpeed5).get());
    EXPECT_EQ("AWHP Cooling Speed 5 CapFT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::NormalizedCoolingCapacityFunctionofTemperatureCurveNameatSpeed5).get());
    EXPECT_EQ("AWHP Cooling Speed 5 EIRfT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::CoolingEnergyInputRatioFunctionofTemperatureCurveNameatSpeed5).get());
    EXPECT_EQ("AWHP Cooling Speed 5 EIRfPLR Curve",
              idfObject.getString(HeatPump_AirToWaterFields::CoolingEnergyInputRatioFunctionofPLRCurveNameatSpeed5).get());
    EXPECT_EQ("Yes", idfObject.getString(HeatPump_AirToWaterFields::BoosterModeOnCooling).get());
    EXPECT_EQ(12000.0, idfObject.getDouble(HeatPump_AirToWaterFields::RatedCoolingCapacityinBoosterMode).get());
    EXPECT_EQ(3.5, idfObject.getDouble(HeatPump_AirToWaterFields::RatedCoolingCOPinBoosterMode).get());
    EXPECT_EQ("AWHP Cooling Booster Mode On Speed CapFT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::NormalizedCoolingCapacityFunctionofTemperatureCurveNameinBoosterMode).get());
    EXPECT_EQ("AWHP Cooling Booster Mode On Speed EIRfT Curve",
              idfObject.getString(HeatPump_AirToWaterFields::CoolingEnergyInputRatioFunctionofTemperatureCurveNameinBoosterMode).get());
    EXPECT_EQ("AWHP Cooling Booster Mode On Speed EIRfPLR Curve",
              idfObject.getString(HeatPump_AirToWaterFields::CoolingEnergyInputRatioFunctionofPLRCurveNameinBoosterMode).get());

    const size_t expectedNumCurves = 1                   // defrostEnergyInputRatioFunctionofTemperatureCurve
                                     + 1                 // crankcaseHeaterCapacityFunctionofTemperatureCurve
                                     + 2 * 2             // awhp_hc/cc min/max LWT curves
                                     + 2 * (5 + 1) * 3;  // awhp_hc/cc: 5 speeds + one booster mode, each with 3 curves
    EXPECT_EQ(expectedNumCurves,
              w.getObjectsByType(IddObjectType::Curve_Biquadratic).size() + w.getObjectsByType(IddObjectType::Curve_Quadratic).size());
    auto oaNodeList = w.getObjectsByType(IddObjectType::OutdoorAir_NodeList);
    ASSERT_EQ(1, oaNodeList.size());
    EXPECT_EQ("AWHP Air Inlet Node", oaNodeList.front().getString(0).get());
    EXPECT_EQ("AWHP Air Outlet Node", oaNodeList.front().getString(1).get());

    EXPECT_EQ(2, w.getObjectsByType(IddObjectType::PlantLoop).size());

    std::vector<Expected> expecteds = {
      Expected{.isHeating = true,
               .plantName = hwLoop.nameString(),
               .inletNodeName = awhp_hc.inletModelObject()->nameString(),
               .outletNodeName = awhp_hc.outletModelObject()->nameString()},
      Expected{.isHeating = false,
               .plantName = chwLoop.nameString(),
               .inletNodeName = awhp_cc.inletModelObject()->nameString(),
               .outletNodeName = awhp_cc.outletModelObject()->nameString()},
    };
    for (const auto& e : expecteds) {
      auto p_ = w.getObjectByTypeAndName(IddObjectType::PlantLoop, e.plantName);
      ASSERT_TRUE(p_.is_initialized()) << "Cannot find PlantLoop named " << e.plantName;
      WorkspaceObject idf_plant = p_.get();
      WorkspaceObject idf_brlist = idf_plant.getTarget(PlantLoopFields::PlantSideBranchListName).get();

      // Should have at three branches: supply inlet, the one with the AWHP, supply outlet.
      ASSERT_EQ(3, idf_brlist.extensibleGroups().size()) << "Failed for " << e.plantName;
      // Get the AWHP one
      auto w_eg = idf_brlist.extensibleGroups()[1].cast<WorkspaceExtensibleGroup>();
      WorkspaceObject idf_branch = w_eg.getTarget(BranchListExtensibleFields::BranchName).get();

      // There should be only one equipment on the branch
      ASSERT_EQ(1, idf_branch.extensibleGroups().size());
      auto w_eg2 = idf_branch.extensibleGroups()[0].cast<WorkspaceExtensibleGroup>();

      ASSERT_EQ(w_eg2.getString(BranchExtensibleFields::ComponentName).get(), awhp.nameString());
      ASSERT_EQ(w_eg2.getString(BranchExtensibleFields::ComponentInletNodeName).get(), e.inletNodeName);
      ASSERT_EQ(w_eg2.getString(BranchExtensibleFields::ComponentOutletNodeName).get(), e.outletNodeName);

      WorkspaceObject idf_plant_op = p_->getTarget(PlantLoopFields::PlantEquipmentOperationSchemeName).get();
      // Should have created a Cooling Load one only
      ASSERT_EQ(1, idf_plant_op.extensibleGroups().size());
      auto w_eg_schemes = idf_plant_op.extensibleGroups()[0].cast<WorkspaceExtensibleGroup>();
      ASSERT_EQ(e.isHeating ? "PlantEquipmentOperation:HeatingLoad" : "PlantEquipmentOperation:CoolingLoad",
                w_eg_schemes.getString(PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeObjectType).get());

      // Get the Operation Scheme
      auto op_scheme_ = w_eg_schemes.getTarget(PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeName);
      ASSERT_TRUE(op_scheme_);

      // Get the Plant Equipment List of this CoolingLoad/HeatingLoad scheme
      // There should only be one Load Range
      ASSERT_EQ(1u, op_scheme_->extensibleGroups().size());

      // Load range 1
      w_eg = op_scheme_->extensibleGroups()[0].cast<WorkspaceExtensibleGroup>();
      boost::optional<WorkspaceObject> peq_list_;
      if (e.isHeating) {
        peq_list_ = w_eg.getTarget(PlantEquipmentOperation_HeatingLoadExtensibleFields::RangeEquipmentListName);
      } else {
        peq_list_ = w_eg.getTarget(PlantEquipmentOperation_CoolingLoadExtensibleFields::RangeEquipmentListName);
      }
      ASSERT_TRUE(peq_list_);

      // Should have one equipment on it: HeatPump:AirToWater
      auto peqs = peq_list_->extensibleGroups();
      ASSERT_EQ(1, peqs.size());
      ASSERT_EQ("HeatPump:AirToWater", peqs.front().getString(PlantEquipmentListExtensibleFields::EquipmentObjectType).get());
      ASSERT_EQ(awhp.nameString(), peqs.front().getString(PlantEquipmentListExtensibleFields::EquipmentName).get());
    }
  }
}

TEST_F(EnergyPlusFixture, ReverseTranslator_HeatPumpAirToWater) {

  ForwardTranslator ft;
  ft.setExcludeLCCObjects(true);

  Model m;

  HeatPumpAirToWater awhp = makeAWHP(m);
  HeatPumpAirToWaterHeating awhp_hc = makeAWHP_Heating(m);
  EXPECT_TRUE(awhp.setHeatingOperationMode(awhp_hc));

  HeatPumpAirToWaterCooling awhp_cc = makeAWHP_Cooling(m);
  EXPECT_TRUE(awhp.setCoolingOperationMode(awhp_cc));

  PlantLoop hwLoop = createLoop(m, "HW Loop");
  EXPECT_TRUE(hwLoop.addSupplyBranchForComponent(awhp_hc));

  PlantLoop chwLoop = createLoop(m, "ChW Loop");
  EXPECT_TRUE(chwLoop.addSupplyBranchForComponent(awhp_cc));

  {
    Workspace w = ft.translateModel(m);
    ReverseTranslator rt;
    Model m2 = rt.translateWorkspace(w);
    EXPECT_EQ(1, m.getConcreteModelObjects<HeatPumpAirToWater>().size());
    EXPECT_EQ(1, m.getConcreteModelObjects<HeatPumpAirToWaterHeating>().size());
    EXPECT_EQ(5, m.getConcreteModelObjects<HeatPumpAirToWaterHeating>().front().numberOfSpeeds());
    EXPECT_TRUE(m.getConcreteModelObjects<HeatPumpAirToWaterHeating>().front().boosterModeOnSpeed());
    EXPECT_EQ(6, m.getConcreteModelObjects<HeatPumpAirToWaterHeatingSpeedData>().size());
    EXPECT_EQ(1, m.getConcreteModelObjects<HeatPumpAirToWaterCooling>().size());
    EXPECT_EQ(5, m.getConcreteModelObjects<HeatPumpAirToWaterCooling>().front().numberOfSpeeds());
    EXPECT_TRUE(m.getConcreteModelObjects<HeatPumpAirToWaterCooling>().front().boosterModeOnSpeed());
    EXPECT_EQ(6, m.getConcreteModelObjects<HeatPumpAirToWaterCoolingSpeedData>().size());
    const size_t expectedNumCurves = 1                   // defrostEnergyInputRatioFunctionofTemperatureCurve
                                     + 1                 // crankcaseHeaterCapacityFunctionofTemperatureCurve
                                     + 2 * 2             // awhp_hc/cc min/max LWT curves
                                     + 2 * (5 + 1) * 3;  // awhp_hc/cc: 5 speeds + one booster mode, each with 3 curves
    EXPECT_EQ(expectedNumCurves, m.getModelObjects<Curve>().size());
    // m.save("HeatPumpAirToWater_original.osm");
    // m2.save("HeatPumpAirToWater_roundtrip.osm");
  }
}
