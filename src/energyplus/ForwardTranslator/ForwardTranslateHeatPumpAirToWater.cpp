/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "../ForwardTranslator.hpp"
#include "../../model/Model.hpp"

#include "../../model/HeatPumpAirToWater.hpp"
#include "../../model/HeatPumpAirToWaterCooling.hpp"
#include "../../model/HeatPumpAirToWaterCoolingSpeedData.hpp"
#include "../../model/HeatPumpAirToWaterHeating.hpp"
#include "../../model/HeatPumpAirToWaterHeatingSpeedData.hpp"

#include "../../model/Schedule.hpp"
#include "../../model/Curve.hpp"
#include "../../model/Node.hpp"
#include "../../model/Node_Impl.hpp"

#include <utilities/idd/HeatPump_AirToWater_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

  void ForwardTranslator::translateHeatPumpAirToWaterCooling(model::HeatPumpAirToWaterCooling& modelObject, IdfObject& idfObject) {
    // Number of Speeds for Cooling: Optional Integer
    const int numberofSpeedsforCooling = modelObject.plantLoop() ? modelObject.numberOfSpeeds() : 0;
    idfObject.setInt(HeatPump_AirToWaterFields::NumberofSpeedsforCooling, numberofSpeedsforCooling);
    if (numberofSpeedsforCooling == 0) {
      return;
    }

    // Availability Schedule Name Cooling: Optional Object
    {
      auto sch = modelObject.availabilitySchedule();
      if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(sch)) {
        idfObject.setString(HeatPump_AirToWaterFields::AvailabilityScheduleNameCooling, wo_->nameString());
      }
    }

    // Rated Inlet Air Temperature in Cooling Mode: Optional Double
    const double ratedInletAirTemperature = modelObject.ratedInletAirTemperature();
    idfObject.setDouble(HeatPump_AirToWaterFields::RatedInletAirTemperatureinCoolingMode, ratedInletAirTemperature);

    // Rated Air Flow Rate
    if (modelObject.isRatedAirFlowRateAutosized()) {
      idfObject.setString(HeatPump_AirToWaterFields::RatedAirFlowRateinCoolingMode, "Autosize");
    } else {
      // Rated Air Flow Rate in Cooling Mode: boost::optional<double>
      if (boost::optional<double> ratedAirFlowRate_ = modelObject.ratedAirFlowRate()) {
        idfObject.setDouble(HeatPump_AirToWaterFields::RatedAirFlowRateinCoolingMode, ratedAirFlowRate_.get());
      }
    }

    // Rated Leaving Water Temperature in Cooling Mode: Optional Double
    const double ratedLeavingWaterTemperature = modelObject.ratedLeavingWaterTemperature();
    idfObject.setDouble(HeatPump_AirToWaterFields::RatedLeavingWaterTemperatureinCoolingMode, ratedLeavingWaterTemperature);

    if (modelObject.isRatedWaterFlowRateAutosized()) {
      idfObject.setString(HeatPump_AirToWaterFields::RatedWaterFlowRateinCoolingMode, "Autosize");
    } else {
      // Rated Water Flow Rate in Cooling Mode: boost::optional<double>
      if (boost::optional<double> ratedWaterFlowRate_ = modelObject.ratedWaterFlowRate()) {
        idfObject.setDouble(HeatPump_AirToWaterFields::RatedWaterFlowRateinCoolingMode, ratedWaterFlowRate_.get());
      }
    }

    // Minimum Outdoor Air Temperature in Cooling Mode: Optional Double
    const double minimumOutdoorAirTemperature = modelObject.minimumOutdoorAirTemperature();
    idfObject.setDouble(HeatPump_AirToWaterFields::MinimumOutdoorAirTemperatureinCoolingMode, minimumOutdoorAirTemperature);

    // Maximum Outdoor Air Temperature in Cooling Mode: Optional Double
    const double maximumOutdoorAirTemperature = modelObject.maximumOutdoorAirTemperature();
    idfObject.setDouble(HeatPump_AirToWaterFields::MaximumOutdoorAirTemperatureinCoolingMode, maximumOutdoorAirTemperature);

    // Minimum Leaving Water Temperature Curve Name in Cooling Mode: Optional Object
    if (boost::optional<Curve> minimumLeavingWaterTemperatureCurve_ = modelObject.minimumLeavingWaterTemperatureCurve()) {
      if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(minimumLeavingWaterTemperatureCurve_.get())) {
        idfObject.setString(HeatPump_AirToWaterFields::MinimumLeavingWaterTemperatureCurveNameinCoolingMode, wo_->nameString());
      }
    }

    // Maximum Leaving Water Temperature Curve Name in Cooling Mode: Optional Object
    if (boost::optional<Curve> maximumLeavingWaterTemperatureCurve_ = modelObject.maximumLeavingWaterTemperatureCurve()) {
      if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(maximumLeavingWaterTemperatureCurve_.get())) {
        idfObject.setString(HeatPump_AirToWaterFields::MaximumLeavingWaterTemperatureCurveNameinCoolingMode, wo_->nameString());
      }
    }

    // Sizing Factor for Cooling: Optional Double
    const double sizingFactor = modelObject.sizingFactor();
    idfObject.setDouble(HeatPump_AirToWaterFields::SizingFactorforCooling, sizingFactor);

    // Chilled Water Inlet Node Name: Optional Node
    if (boost::optional<ModelObject> mo_ = modelObject.inletModelObject()) {
      if (boost::optional<Node> node_ = mo_->optionalCast<Node>()) {
        idfObject.setString(HeatPump_AirToWaterFields::ChilledWaterInletNodeName, node_->nameString());
      }
    }

    // Chilled Water Outlet Node Name: Optional Node
    if (boost::optional<ModelObject> mo_ = modelObject.outletModelObject()) {
      if (boost::optional<Node> node_ = mo_->optionalCast<Node>()) {
        idfObject.setString(HeatPump_AirToWaterFields::ChilledWaterOutletNodeName, node_->nameString());
      }
    }

    auto speeds = modelObject.speeds();
    unsigned startIndex = HeatPump_AirToWaterFields::RatedCoolingCapacityatSpeed1;
    const unsigned number_fields =
      static_cast<unsigned>(HeatPump_AirToWaterFields::CoolingEnergyInputRatioFunctionofPLRCurveNameatSpeed1) - startIndex + 1;

    auto getFieldIndex = [&startIndex](HeatPump_AirToWaterFields::domain field) -> unsigned {
      return startIndex + (static_cast<unsigned>(field) - static_cast<unsigned>(HeatPump_AirToWaterFields::RatedCoolingCapacityatSpeed1));
    };

    for (const auto& speed : speeds) {

      // Rated Cooling Capacity at Speed
      if (speed.isRatedCoolingCapacityAutosized()) {
        idfObject.setString(getFieldIndex(HeatPump_AirToWaterFields::RatedCoolingCapacityatSpeed1), "Autosize");
      } else {
        idfObject.setDouble(getFieldIndex(HeatPump_AirToWaterFields::RatedCoolingCapacityatSpeed1), speed.ratedCoolingCapacity().get());
      }

      // Rated COP for Cooling at Speed
      idfObject.setDouble(getFieldIndex(HeatPump_AirToWaterFields::RatedCOPforCoolingatSpeed1), speed.ratedCOPforCooling());

      // Normalized Cooling Capacity Function of Temperature Curve Name at Speed
      {
        auto curve = speed.normalizedCoolingCapacityFunctionofTemperatureCurve();
        if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(curve)) {
          idfObject.setString(getFieldIndex(HeatPump_AirToWaterFields::NormalizedCoolingCapacityFunctionofTemperatureCurveNameatSpeed1),
                              wo_->nameString());
        }
      }

      // Cooling Energy Input Ratio Function of Temperature Curve Name at Speed
      {
        auto curve = speed.coolingEnergyInputRatioFunctionofTemperatureCurve();
        if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(curve)) {
          idfObject.setString(getFieldIndex(HeatPump_AirToWaterFields::CoolingEnergyInputRatioFunctionofTemperatureCurveNameatSpeed1),
                              wo_->nameString());
        }
      }

      // Cooling Energy Input Ratio Function of PLR Curve Name at Speed
      {
        auto curve = speed.coolingEnergyInputRatioFunctionofPLRCurve();
        if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(curve)) {
          idfObject.setString(getFieldIndex(HeatPump_AirToWaterFields::CoolingEnergyInputRatioFunctionofPLRCurveNameatSpeed1), wo_->nameString());
        }
      }

      startIndex += number_fields;
    }

    // Booster Mode On Speed: Optional HeatPump:AirToWater:CoolingSpeedData
    if (auto boosterModeOnSpeed_ = modelObject.boosterModeOnSpeed()) {

      idfObject.setString(HeatPump_AirToWaterFields::BoosterModeOnCooling, "Yes");

      auto speed = std::move(*boosterModeOnSpeed_);

      // Rated Cooling Capacity at Speed
      if (speed.isRatedCoolingCapacityAutosized()) {
        idfObject.setString(HeatPump_AirToWaterFields::RatedCoolingCapacityinBoosterMode, "Autosize");
      } else {
        idfObject.setDouble(HeatPump_AirToWaterFields::RatedCoolingCapacityinBoosterMode, speed.ratedCoolingCapacity().get());
      }

      // Rated COP for Cooling at Speed
      idfObject.setDouble(HeatPump_AirToWaterFields::RatedCoolingCOPinBoosterMode, speed.ratedCOPforCooling());

      // Normalized Cooling Capacity Function of Temperature Curve Name at Speed
      {
        auto curve = speed.normalizedCoolingCapacityFunctionofTemperatureCurve();
        if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(curve)) {
          idfObject.setString(HeatPump_AirToWaterFields::NormalizedCoolingCapacityFunctionofTemperatureCurveNameinBoosterMode, wo_->nameString());
        }
      }

      // Cooling Energy Input Ratio Function of Temperature Curve Name at Speed
      {
        auto curve = speed.coolingEnergyInputRatioFunctionofTemperatureCurve();
        if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(curve)) {
          idfObject.setString(HeatPump_AirToWaterFields::CoolingEnergyInputRatioFunctionofTemperatureCurveNameinBoosterMode, wo_->nameString());
        }
      }

      // Cooling Energy Input Ratio Function of PLR Curve Name at Speed
      {
        auto curve = speed.coolingEnergyInputRatioFunctionofPLRCurve();
        if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(curve)) {
          idfObject.setString(HeatPump_AirToWaterFields::CoolingEnergyInputRatioFunctionofPLRCurveNameinBoosterMode, wo_->nameString());
        }
      }

    } else {
      // Reset the field to blank if no booster mode
      idfObject.setString(HeatPump_AirToWaterFields::BoosterModeOnCooling, "No");
    }
  }

  void ForwardTranslator::translateHeatPumpAirToWaterHeating(model::HeatPumpAirToWaterHeating& modelObject, IdfObject& idfObject) {

    const int numberofSpeedsforHeating = modelObject.plantLoop() ? modelObject.numberOfSpeeds() : 0;
    idfObject.setInt(HeatPump_AirToWaterFields::NumberofSpeedsforHeating, numberofSpeedsforHeating);
    if (numberofSpeedsforHeating == 0) {
      return;
    }

    // Availability Schedule Name Heating: Optional Object
    {
      auto sch = modelObject.availabilitySchedule();
      if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(sch)) {
        idfObject.setString(HeatPump_AirToWaterFields::AvailabilityScheduleNameHeating, wo_->nameString());
      }
    }

    // Rated Inlet Air Temperature in Heating Mode: Optional Double
    const double ratedInletAirTemperature = modelObject.ratedInletAirTemperature();
    idfObject.setDouble(HeatPump_AirToWaterFields::RatedInletAirTemperatureinHeatingMode, ratedInletAirTemperature);

    // Rated Air Flow Rate
    if (modelObject.isRatedAirFlowRateAutosized()) {
      idfObject.setString(HeatPump_AirToWaterFields::RatedAirFlowRateinHeatingMode, "Autosize");
    } else {
      // Rated Air Flow Rate in Heating Mode: boost::optional<double>
      if (boost::optional<double> ratedAirFlowRate_ = modelObject.ratedAirFlowRate()) {
        idfObject.setDouble(HeatPump_AirToWaterFields::RatedAirFlowRateinHeatingMode, ratedAirFlowRate_.get());
      }
    }

    // Rated Leaving Water Temperature in Heating Mode: Optional Double
    const double ratedLeavingWaterTemperature = modelObject.ratedLeavingWaterTemperature();
    idfObject.setDouble(HeatPump_AirToWaterFields::RatedLeavingWaterTemperatureinHeatingMode, ratedLeavingWaterTemperature);

    if (modelObject.isRatedWaterFlowRateAutosized()) {
      idfObject.setString(HeatPump_AirToWaterFields::RatedWaterFlowRateinHeatingMode, "Autosize");
    } else {
      // Rated Water Flow Rate in Heating Mode: boost::optional<double>
      if (boost::optional<double> ratedWaterFlowRate_ = modelObject.ratedWaterFlowRate()) {
        idfObject.setDouble(HeatPump_AirToWaterFields::RatedWaterFlowRateinHeatingMode, ratedWaterFlowRate_.get());
      }
    }

    // Minimum Outdoor Air Temperature in Heating Mode: Optional Double
    const double minimumOutdoorAirTemperature = modelObject.minimumOutdoorAirTemperature();
    idfObject.setDouble(HeatPump_AirToWaterFields::MinimumOutdoorAirTemperatureinHeatingMode, minimumOutdoorAirTemperature);

    // Maximum Outdoor Air Temperature in Heating Mode: Optional Double
    const double maximumOutdoorAirTemperature = modelObject.maximumOutdoorAirTemperature();
    idfObject.setDouble(HeatPump_AirToWaterFields::MaximumOutdoorAirTemperatureinHeatingMode, maximumOutdoorAirTemperature);

    // Minimum Leaving Water Temperature Curve Name in Heating Mode: Optional Object
    if (boost::optional<Curve> minimumLeavingWaterTemperatureCurve_ = modelObject.minimumLeavingWaterTemperatureCurve()) {
      if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(minimumLeavingWaterTemperatureCurve_.get())) {
        idfObject.setString(HeatPump_AirToWaterFields::MinimumLeavingWaterTemperatureCurveNameinHeatingMode, wo_->nameString());
      }
    }

    // Maximum Leaving Water Temperature Curve Name in Heating Mode: Optional Object
    if (boost::optional<Curve> maximumLeavingWaterTemperatureCurve_ = modelObject.maximumLeavingWaterTemperatureCurve()) {
      if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(maximumLeavingWaterTemperatureCurve_.get())) {
        idfObject.setString(HeatPump_AirToWaterFields::MaximumLeavingWaterTemperatureCurveNameinHeatingMode, wo_->nameString());
      }
    }

    // Sizing Factor for Heating: Optional Double
    const double sizingFactor = modelObject.sizingFactor();
    idfObject.setDouble(HeatPump_AirToWaterFields::SizingFactorforHeating, sizingFactor);

    // Hot Water Inlet Node Name: Optional Node
    if (boost::optional<ModelObject> mo_ = modelObject.inletModelObject()) {
      if (boost::optional<Node> node_ = mo_->optionalCast<Node>()) {
        idfObject.setString(HeatPump_AirToWaterFields::HotWaterInletNodeName, node_->nameString());
      }
    }

    // Hot Water Outlet Node Name: Optional Node
    if (boost::optional<ModelObject> mo_ = modelObject.outletModelObject()) {
      if (boost::optional<Node> node_ = mo_->optionalCast<Node>()) {
        idfObject.setString(HeatPump_AirToWaterFields::HotWaterOutletNodeName, node_->nameString());
      }
    }

    auto speeds = modelObject.speeds();
    unsigned startIndex = HeatPump_AirToWaterFields::RatedHeatingCapacityatSpeed1;
    const unsigned number_fields =
      static_cast<unsigned>(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofPLRCurveNameatSpeed1) - startIndex + 1;

    auto getFieldIndex = [&startIndex](HeatPump_AirToWaterFields::domain field) -> unsigned {
      return startIndex + (static_cast<unsigned>(field) - static_cast<unsigned>(HeatPump_AirToWaterFields::RatedHeatingCapacityatSpeed1));
    };

    for (const auto& speed : speeds) {

      // Rated Heating Capacity at Speed
      if (speed.isRatedHeatingCapacityAutosized()) {
        idfObject.setString(getFieldIndex(HeatPump_AirToWaterFields::RatedHeatingCapacityatSpeed1), "Autosize");
      } else {
        idfObject.setDouble(getFieldIndex(HeatPump_AirToWaterFields::RatedHeatingCapacityatSpeed1), speed.ratedHeatingCapacity().get());
      }

      // Rated COP for Heating at Speed
      idfObject.setDouble(getFieldIndex(HeatPump_AirToWaterFields::RatedCOPforHeatingatSpeed1), speed.ratedCOPforHeating());

      // Normalized Heating Capacity Function of Temperature Curve Name at Speed
      {
        auto curve = speed.normalizedHeatingCapacityFunctionofTemperatureCurve();
        if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(curve)) {
          idfObject.setString(getFieldIndex(HeatPump_AirToWaterFields::NormalizedHeatingCapacityFunctionofTemperatureCurveNameatSpeed1),
                              wo_->nameString());
        }
      }

      // Heating Energy Input Ratio Function of Temperature Curve Name at Speed
      {
        auto curve = speed.heatingEnergyInputRatioFunctionofTemperatureCurve();
        if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(curve)) {
          idfObject.setString(getFieldIndex(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofTemperatureCurveNameatSpeed1),
                              wo_->nameString());
        }
      }

      // Heating Energy Input Ratio Function of PLR Curve Name at Speed
      {
        auto curve = speed.heatingEnergyInputRatioFunctionofPLRCurve();
        if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(curve)) {
          idfObject.setString(getFieldIndex(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofPLRCurveNameatSpeed1), wo_->nameString());
        }
      }

      startIndex += number_fields;
    }

    // Booster Mode On Speed: Optional HeatPump:AirToWater:HeatingSpeedData
    if (auto boosterModeOnSpeed_ = modelObject.boosterModeOnSpeed()) {

      idfObject.setString(HeatPump_AirToWaterFields::BoosterModeOnHeating, "Yes");

      auto speed = std::move(*boosterModeOnSpeed_);

      // Rated Heating Capacity at Speed
      if (speed.isRatedHeatingCapacityAutosized()) {
        idfObject.setString(HeatPump_AirToWaterFields::RatedHeatingCapacityinBoosterMode, "Autosize");
      } else {
        idfObject.setDouble(HeatPump_AirToWaterFields::RatedHeatingCapacityinBoosterMode, speed.ratedHeatingCapacity().get());
      }

      // Rated COP for Heating at Speed
      idfObject.setDouble(HeatPump_AirToWaterFields::RatedHeatingCOPinBoosterMode, speed.ratedCOPforHeating());

      // Normalized Heating Capacity Function of Temperature Curve Name at Speed
      {
        auto curve = speed.normalizedHeatingCapacityFunctionofTemperatureCurve();
        if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(curve)) {
          idfObject.setString(HeatPump_AirToWaterFields::NormalizedHeatingCapacityFunctionofTemperatureCurveNameinBoosterMode, wo_->nameString());
        }
      }

      // Heating Energy Input Ratio Function of Temperature Curve Name at Speed
      {
        auto curve = speed.heatingEnergyInputRatioFunctionofTemperatureCurve();
        if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(curve)) {
          idfObject.setString(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofTemperatureCurveNameinBoosterMode, wo_->nameString());
        }
      }

      // Heating Energy Input Ratio Function of PLR Curve Name at Speed
      {
        auto curve = speed.heatingEnergyInputRatioFunctionofPLRCurve();
        if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(curve)) {
          idfObject.setString(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofPLRCurveNameinBoosterMode, wo_->nameString());
        }
      }

    } else {
      // Reset the field to blank if no booster mode
      idfObject.setString(HeatPump_AirToWaterFields::BoosterModeOnHeating, "No");
    }
  }

  boost::optional<IdfObject> ForwardTranslator::translateHeatPumpAirToWater(model::HeatPumpAirToWater& modelObject) {

    // Instantiate an IdfObject of the class to store the values
    IdfObject idfObject = createRegisterAndNameIdfObject(openstudio::IddObjectType::HeatPump_AirToWater, modelObject);

    // Operating Mode Control Method: Optional String
    const std::string operatingModeControlMethod = modelObject.operatingModeControlMethod();
    idfObject.setString(HeatPump_AirToWaterFields::OperatingModeControlMethod, operatingModeControlMethod);

    // Operating Mode Control Option for Multiple Unit: Optional String
    const std::string operatingModeControlOptionforMultipleUnit = modelObject.operatingModeControlOptionforMultipleUnit();
    idfObject.setString(HeatPump_AirToWaterFields::OperatingModeControlOptionforMultipleUnit, operatingModeControlOptionforMultipleUnit);

    // Operating Mode Control Schedule Name: Optional Object
    if (boost::optional<Schedule> operatingModeControlSchedule_ = modelObject.operatingModeControlSchedule()) {
      if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(operatingModeControlSchedule_.get())) {
        idfObject.setString(HeatPump_AirToWaterFields::OperatingModeControlScheduleName, wo_->nameString());
      }
    }

    // Minimum Part Load Ratio: Optional Double
    const double minimumPartLoadRatio = modelObject.minimumPartLoadRatio();
    idfObject.setDouble(HeatPump_AirToWaterFields::MinimumPartLoadRatio, minimumPartLoadRatio);

    // Air Inlet Node Name: Required Node
    {
      IdfObject oaNodeListIdf(openstudio::IddObjectType::OutdoorAir_NodeList);
      {
        const std::string airInletNodeName = modelObject.airInletNodeName().value_or(modelObject.nameString() + " Air Inlet Node");
        idfObject.setString(HeatPump_AirToWaterFields::AirInletNodeName, airInletNodeName);
        oaNodeListIdf.setString(0, airInletNodeName);
      }

      // Air Outlet Node Name: Required Node
      {
        const std::string airOutletNodeName = modelObject.airOutletNodeName().value_or(modelObject.nameString() + " Air Outlet Node");
        idfObject.setString(HeatPump_AirToWaterFields::AirOutletNodeName, airOutletNodeName);
        oaNodeListIdf.setString(1, airOutletNodeName);
      }
      m_idfObjects.emplace_back(std::move(oaNodeListIdf));
    }

    // Maximum Outdoor Dry Bulb Temperature For Defrost Operation: Optional Double
    const double maximumOutdoorDryBulbTemperatureForDefrostOperation = modelObject.maximumOutdoorDryBulbTemperatureForDefrostOperation();
    idfObject.setDouble(HeatPump_AirToWaterFields::MaximumOutdoorDryBulbTemperatureForDefrostOperation,
                        maximumOutdoorDryBulbTemperatureForDefrostOperation);

    // Heat Pump Defrost Control: Optional String
    const std::string heatPumpDefrostControl = modelObject.heatPumpDefrostControl();
    idfObject.setString(HeatPump_AirToWaterFields::HeatPumpDefrostControl, heatPumpDefrostControl);

    // Heat Pump Defrost Time Period Fraction: Optional Double
    const double heatPumpDefrostTimePeriodFraction = modelObject.heatPumpDefrostTimePeriodFraction();
    idfObject.setDouble(HeatPump_AirToWaterFields::HeatPumpDefrostTimePeriodFraction, heatPumpDefrostTimePeriodFraction);

    const double resistiveDefrostHeaterCapacity = modelObject.resistiveDefrostHeaterCapacity();
    idfObject.setDouble(HeatPump_AirToWaterFields::ResistiveDefrostHeaterCapacity, resistiveDefrostHeaterCapacity);

    // Defrost Energy Input Ratio Function of Temperature Curve Name: Optional Object
    if (boost::optional<Curve> defrostEnergyInputRatioFunctionofTemperatureCurve_ = modelObject.defrostEnergyInputRatioFunctionofTemperatureCurve()) {
      if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(defrostEnergyInputRatioFunctionofTemperatureCurve_.get())) {
        idfObject.setString(HeatPump_AirToWaterFields::DefrostEnergyInputRatioFunctionofTemperatureCurveName, wo_->nameString());
      }
    }

    // Heat Pump Multiplier: Optional Integer
    const int heatPumpMultiplier = modelObject.heatPumpMultiplier();
    idfObject.setInt(HeatPump_AirToWaterFields::HeatPumpMultiplier, heatPumpMultiplier);

    // Control Type: Optional String
    const std::string controlType = modelObject.controlType();
    idfObject.setString(HeatPump_AirToWaterFields::ControlType, controlType);

    // Crankcase Heater Capacity: Optional Double
    const double crankcaseHeaterCapacity = modelObject.crankcaseHeaterCapacity();
    idfObject.setDouble(HeatPump_AirToWaterFields::CrankcaseHeaterCapacity, crankcaseHeaterCapacity);

    // Crankcase Heater Capacity Function of Temperature Curve Name: Optional Object
    if (boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve_ = modelObject.crankcaseHeaterCapacityFunctionofTemperatureCurve()) {
      if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(crankcaseHeaterCapacityFunctionofTemperatureCurve_.get())) {
        idfObject.setString(HeatPump_AirToWaterFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName, wo_->nameString());
      }
    }

    // Maximum Ambient Temperature for Crankcase Heater Operation: Optional Double
    const double maximumAmbientTemperatureforCrankcaseHeaterOperation = modelObject.maximumAmbientTemperatureforCrankcaseHeaterOperation();
    idfObject.setDouble(HeatPump_AirToWaterFields::MaximumAmbientTemperatureforCrankcaseHeaterOperation,
                        maximumAmbientTemperatureforCrankcaseHeaterOperation);

    if (auto awhp_cc_ = modelObject.coolingOperationMode()) {
      translateHeatPumpAirToWaterCooling(*awhp_cc_, idfObject);
    }

    if (auto awhp_cc_ = modelObject.heatingOperationMode()) {
      translateHeatPumpAirToWaterHeating(*awhp_cc_, idfObject);
    }

    return idfObject;
  }  // End of translate function

}  // end namespace energyplus
}  // end namespace openstudio
