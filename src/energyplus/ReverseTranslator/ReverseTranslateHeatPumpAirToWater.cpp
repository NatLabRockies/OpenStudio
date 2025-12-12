/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "../ReverseTranslator.hpp"

#include "../../model/HeatPumpAirToWater.hpp"
#include "../../model/HeatPumpAirToWaterCooling.hpp"
#include "../../model/HeatPumpAirToWaterCooling_Impl.hpp"
#include "../../model/HeatPumpAirToWaterCoolingSpeedData.hpp"
#include "../../model/HeatPumpAirToWaterHeating.hpp"
#include "../../model/HeatPumpAirToWaterHeating_Impl.hpp"
#include "../../model/HeatPumpAirToWaterHeatingSpeedData.hpp"

#include "../../model/Schedule.hpp"
#include "../../model/Schedule_Impl.hpp"

#include "../../model/Curve.hpp"
#include "../../model/Curve_Impl.hpp"

#include <utilities/idd/HeatPump_AirToWater_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

  boost::optional<model::ModelObject> ReverseTranslator::translateHeatPumpAirToWaterCooling(const WorkspaceObject& workspaceObject) {
    // Number of Speeds for Cooling: Optional Integer
    int numberofSpeedsforCooling = workspaceObject.getInt(HeatPump_AirToWaterFields::NumberofSpeedsforCooling).value_or(0);
    if (numberofSpeedsforCooling == 0) {
      return boost::none;
    }

    HeatPumpAirToWaterCooling awhp_cc(m_model);
    awhp_cc.setName(workspaceObject.nameString() + " Cooling");

    // Availability Schedule Name Cooling: Optional Object
    if (boost::optional<WorkspaceObject> wo_ = workspaceObject.getTarget(HeatPump_AirToWaterFields::AvailabilityScheduleNameCooling)) {
      if (boost::optional<ModelObject> mo_ = translateAndMapWorkspaceObject(wo_.get())) {
        if (boost::optional<Schedule> availabilityScheduleCooling_ = mo_->optionalCast<Schedule>()) {
          awhp_cc.setAvailabilitySchedule(availabilityScheduleCooling_.get());
        } else {
          LOG(Warn, workspaceObject.briefDescription() << " has a wrong type for 'Availability Schedule Name Cooling'");
        }
      }
    }

    // Rated Inlet Air Temperature in Cooling Mode: Optional Double
    if (boost::optional<double> ratedInletAirTemperature_ =
          workspaceObject.getDouble(HeatPump_AirToWaterFields::RatedInletAirTemperatureinCoolingMode)) {
      awhp_cc.setRatedInletAirTemperature(ratedInletAirTemperature_.get());
    }

    // Rated Air Flow Rate in Cooling Mode: Optional Double
    if (boost::optional<double> ratedAirFlowRate_ = workspaceObject.getDouble(HeatPump_AirToWaterFields::RatedAirFlowRateinCoolingMode)) {
      awhp_cc.setRatedAirFlowRate(ratedAirFlowRate_.get());
    }

    // Rated Leaving Water Temperature in Cooling Mode: Optional Double
    if (boost::optional<double> ratedLeavingWaterTemperature_ =
          workspaceObject.getDouble(HeatPump_AirToWaterFields::RatedLeavingWaterTemperatureinCoolingMode)) {
      awhp_cc.setRatedLeavingWaterTemperature(ratedLeavingWaterTemperature_.get());
    }

    // Rated Water Flow Rate in Cooling Mode: Optional Double
    if (boost::optional<double> ratedWaterFlowRate_ = workspaceObject.getDouble(HeatPump_AirToWaterFields::RatedWaterFlowRateinCoolingMode)) {
      awhp_cc.setRatedWaterFlowRate(ratedWaterFlowRate_.get());
    }

    // Minimum Outdoor Air Temperature in Cooling Mode: Optional Double
    if (boost::optional<double> minimumOutdoorAirTemperature_ =
          workspaceObject.getDouble(HeatPump_AirToWaterFields::MinimumOutdoorAirTemperatureinCoolingMode)) {
      awhp_cc.setMinimumOutdoorAirTemperature(minimumOutdoorAirTemperature_.get());
    }

    // Maximum Outdoor Air Temperature in Cooling Mode: Optional Double
    if (boost::optional<double> maximumOutdoorAirTemperature_ =
          workspaceObject.getDouble(HeatPump_AirToWaterFields::MaximumOutdoorAirTemperatureinCoolingMode)) {
      awhp_cc.setMaximumOutdoorAirTemperature(maximumOutdoorAirTemperature_.get());
    }

    // Minimum Leaving Water Temperature Curve Name in Cooling Mode: Optional Object
    if (boost::optional<WorkspaceObject> wo_ =
          workspaceObject.getTarget(HeatPump_AirToWaterFields::MinimumLeavingWaterTemperatureCurveNameinCoolingMode)) {
      if (boost::optional<ModelObject> mo_ = translateAndMapWorkspaceObject(wo_.get())) {
        if (boost::optional<Curve> minimumLeavingWaterTemperatureCurveinCoolingMode_ = mo_->optionalCast<Curve>()) {
          awhp_cc.setMinimumLeavingWaterTemperatureCurve(minimumLeavingWaterTemperatureCurveinCoolingMode_.get());
        } else {
          LOG(Warn, workspaceObject.briefDescription() << " has a wrong type for 'Minimum Leaving Water Temperature Curve Name in Cooling Mode'");
        }
      }
    }
    // Maximum Leaving Water Temperature Curve Name in Cooling Mode: Optional Object
    if (boost::optional<WorkspaceObject> wo_ =
          workspaceObject.getTarget(HeatPump_AirToWaterFields::MaximumLeavingWaterTemperatureCurveNameinCoolingMode)) {
      if (boost::optional<ModelObject> mo_ = translateAndMapWorkspaceObject(wo_.get())) {
        if (boost::optional<Curve> maximumLeavingWaterTemperatureCurveinCoolingMode_ = mo_->optionalCast<Curve>()) {
          awhp_cc.setMaximumLeavingWaterTemperatureCurve(maximumLeavingWaterTemperatureCurveinCoolingMode_.get());
        } else {
          LOG(Warn, workspaceObject.briefDescription() << " has a wrong type for 'Maximum Leaving Water Temperature Curve Name in Cooling Mode'");
        }
      }
    }

    // Sizing Factor for Cooling: Optional Double
    if (boost::optional<double> sizingFactor_ = workspaceObject.getDouble(HeatPump_AirToWaterFields::SizingFactorforCooling)) {
      awhp_cc.setSizingFactor(sizingFactor_.get());
    }

    unsigned startIndex = HeatPump_AirToWaterFields::RatedCoolingCapacityatSpeed1;
    const unsigned number_fields =
      static_cast<unsigned>(HeatPump_AirToWaterFields::CoolingEnergyInputRatioFunctionofPLRCurveNameatSpeed1) - startIndex + 1;

    auto getFieldIndex = [&startIndex](HeatPump_AirToWaterFields::domain field) -> unsigned {
      return startIndex + (static_cast<unsigned>(field) - static_cast<unsigned>(HeatPump_AirToWaterFields::RatedCoolingCapacityatSpeed1));
    };
    for (int i = 1; i <= numberofSpeedsforCooling; ++i) {

      HeatPumpAirToWaterCoolingSpeedData speed(m_model);
      speed.setName(awhp_cc.nameString() + " Speed " + std::to_string(i));
      // Rated Cooling Capacity at Speed
      if (boost::optional<double> ratedCoolingCapacityatSpeed_ =
            workspaceObject.getDouble(getFieldIndex(HeatPump_AirToWaterFields::RatedCoolingCapacityatSpeed1))) {
        speed.setRatedCoolingCapacity(ratedCoolingCapacityatSpeed_.get());
      }

      // Rated COP for Cooling at Speed
      if (boost::optional<double> ratedCOPforCoolingatSpeed_ =
            workspaceObject.getDouble(getFieldIndex(HeatPump_AirToWaterFields::RatedCOPforCoolingatSpeed1))) {
        speed.setRatedCOPforCooling(ratedCOPforCoolingatSpeed_.get());
      }

      // Normalized Cooling Capacity Function of Temperature Curve Name at Speed
      if (boost::optional<WorkspaceObject> wo_ =
            workspaceObject.getTarget(getFieldIndex(HeatPump_AirToWaterFields::NormalizedCoolingCapacityFunctionofTemperatureCurveNameatSpeed1))) {
        if (boost::optional<ModelObject> mo_ = translateAndMapWorkspaceObject(wo_.get())) {
          if (boost::optional<Curve> normalizedCoolingCapacityFunctionofTemperatureCurveatSpeed_ = mo_->optionalCast<Curve>()) {
            speed.normalizedCoolingCapacityFunctionofTemperatureCurve().remove();
            speed.setNormalizedCoolingCapacityFunctionofTemperatureCurve(normalizedCoolingCapacityFunctionofTemperatureCurveatSpeed_.get());
          } else {
            LOG(Warn, workspaceObject.briefDescription()
                        << " has a wrong type for 'Normalized Cooling Capacity Function of Temperature Curve Name at Speed " << i);
          }
        }
      }

      // Cooling Energy Input Ratio Function of Temperature Curve Name at Speed
      if (boost::optional<WorkspaceObject> wo_ =
            workspaceObject.getTarget(getFieldIndex(HeatPump_AirToWaterFields::CoolingEnergyInputRatioFunctionofTemperatureCurveNameatSpeed1))) {
        if (boost::optional<ModelObject> mo_ = translateAndMapWorkspaceObject(wo_.get())) {
          if (boost::optional<Curve> coolingEnergyInputRatioFunctionofTemperatureCurveatSpeed_ = mo_->optionalCast<Curve>()) {
            speed.coolingEnergyInputRatioFunctionofTemperatureCurve().remove();
            speed.setCoolingEnergyInputRatioFunctionofTemperatureCurve(coolingEnergyInputRatioFunctionofTemperatureCurveatSpeed_.get());
          } else {
            LOG(Warn, workspaceObject.briefDescription()
                        << " has a wrong type for 'Cooling Energy Input Ratio Function of Temperature Curve Name at Speed " << i);
          }
        }
      }

      // Cooling Energy Input Ratio Function of PLR Curve Name at Speed
      if (boost::optional<WorkspaceObject> wo_ =
            workspaceObject.getTarget(getFieldIndex(HeatPump_AirToWaterFields::CoolingEnergyInputRatioFunctionofPLRCurveNameatSpeed1))) {
        if (boost::optional<ModelObject> mo_ = translateAndMapWorkspaceObject(wo_.get())) {
          if (boost::optional<Curve> coolingEnergyInputRatioFunctionofPLRCurveatSpeed_ = mo_->optionalCast<Curve>()) {
            speed.coolingEnergyInputRatioFunctionofPLRCurve().remove();
            speed.setCoolingEnergyInputRatioFunctionofPLRCurve(coolingEnergyInputRatioFunctionofPLRCurveatSpeed_.get());
          } else {
            LOG(Warn, workspaceObject.briefDescription()
                        << " has a wrong type for 'Cooling Energy Input Ratio Function of PLR Curve Name at Speed " << i)
          }
        }
      }

      if (!awhp_cc.addSpeed(speed)) {
        LOG(Error, "For " << workspaceObject.briefDescription() << ", cannot add speed data " << i << " to HeatPumpAirToWaterCooling");
      }

      startIndex += number_fields;
    }

    // Booster Mode On Cooling: Optional Boolean
    const std::string boosterModeOnCooling = workspaceObject.getString(HeatPump_AirToWaterFields::BoosterModeOnCooling, true).get();
    if (istringEqual("Yes", boosterModeOnCooling)) {
      HeatPumpAirToWaterCoolingSpeedData speed(m_model);
      speed.setName(awhp_cc.nameString() + " Booster Mode On Speed");

      // Rated Cooling Capacity in Booster Mode: Optional Double
      if (boost::optional<double> ratedCoolingCapacityinBoosterMode_ =
            workspaceObject.getDouble(HeatPump_AirToWaterFields::RatedCoolingCapacityinBoosterMode)) {
        speed.setRatedCoolingCapacity(ratedCoolingCapacityinBoosterMode_.get());
      }

      // Rated Cooling COP in Booster Mode: Optional Double
      if (boost::optional<double> ratedCoolingCOPinBoosterMode_ =
            workspaceObject.getDouble(HeatPump_AirToWaterFields::RatedCoolingCOPinBoosterMode)) {
        speed.setRatedCOPforCooling(ratedCoolingCOPinBoosterMode_.get());
      }

      // Normalized Cooling Capacity Function of Temperature Curve Name in Booster Mode: Optional Object
      if (boost::optional<WorkspaceObject> wo_ =
            workspaceObject.getTarget(HeatPump_AirToWaterFields::NormalizedCoolingCapacityFunctionofTemperatureCurveNameinBoosterMode)) {
        if (boost::optional<ModelObject> mo_ = translateAndMapWorkspaceObject(wo_.get())) {
          if (boost::optional<Curve> normalizedCoolingCapacityFunctionofTemperatureCurveinBoosterMode_ = mo_->optionalCast<Curve>()) {
            speed.normalizedCoolingCapacityFunctionofTemperatureCurve().remove();
            speed.setNormalizedCoolingCapacityFunctionofTemperatureCurve(normalizedCoolingCapacityFunctionofTemperatureCurveinBoosterMode_.get());
          } else {
            LOG(Warn, workspaceObject.briefDescription()
                        << " has a wrong type for 'Normalized Cooling Capacity Function of Temperature Curve Name in Booster Mode'");
          }
        }
      }
      // Cooling Energy Input Ratio Function of Temperature Curve Name in Booster Mode: Optional Object
      if (boost::optional<WorkspaceObject> wo_ =
            workspaceObject.getTarget(HeatPump_AirToWaterFields::CoolingEnergyInputRatioFunctionofTemperatureCurveNameinBoosterMode)) {
        if (boost::optional<ModelObject> mo_ = translateAndMapWorkspaceObject(wo_.get())) {
          if (boost::optional<Curve> coolingEnergyInputRatioFunctionofTemperatureCurveinBoosterMode_ = mo_->optionalCast<Curve>()) {
            speed.coolingEnergyInputRatioFunctionofTemperatureCurve().remove();
            speed.setCoolingEnergyInputRatioFunctionofTemperatureCurve(coolingEnergyInputRatioFunctionofTemperatureCurveinBoosterMode_.get());
          } else {
            LOG(Warn, workspaceObject.briefDescription()
                        << " has a wrong type for 'Cooling Energy Input Ratio Function of Temperature Curve Name in Booster Mode'");
          }
        }
      }
      // Cooling Energy Input Ratio Function of PLR Curve Name in Booster Mode: Optional Object
      if (boost::optional<WorkspaceObject> wo_ =
            workspaceObject.getTarget(HeatPump_AirToWaterFields::CoolingEnergyInputRatioFunctionofPLRCurveNameinBoosterMode)) {
        if (boost::optional<ModelObject> mo_ = translateAndMapWorkspaceObject(wo_.get())) {
          if (boost::optional<Curve> coolingEnergyInputRatioFunctionofPLRCurveinBoosterMode_ = mo_->optionalCast<Curve>()) {
            speed.coolingEnergyInputRatioFunctionofPLRCurve().remove();
            speed.setCoolingEnergyInputRatioFunctionofPLRCurve(coolingEnergyInputRatioFunctionofPLRCurveinBoosterMode_.get());
          } else {
            LOG(Warn, workspaceObject.briefDescription()
                        << " has a wrong type for 'Cooling Energy Input Ratio Function of PLR Curve Name in Booster Mode'");
          }
        }
      }
      if (!awhp_cc.setBoosterModeOnSpeed(speed)) {
        LOG(Error, "For " << workspaceObject.briefDescription() << ", cannot set booster mode on speed to HeatPumpAirToWaterCooling");
      }
    }

    return awhp_cc;
  }

  boost::optional<model::ModelObject> ReverseTranslator::translateHeatPumpAirToWaterHeating(const WorkspaceObject& workspaceObject) {
    // Number of Speeds for Heating: Optional Integer
    int numberofSpeedsforHeating = workspaceObject.getInt(HeatPump_AirToWaterFields::NumberofSpeedsforHeating).value_or(0);
    if (numberofSpeedsforHeating == 0) {
      return boost::none;
    }

    HeatPumpAirToWaterHeating awhp_hc(m_model);
    awhp_hc.setName(workspaceObject.nameString() + " Heating");

    // Availability Schedule Name Heating: Optional Object
    if (boost::optional<WorkspaceObject> wo_ = workspaceObject.getTarget(HeatPump_AirToWaterFields::AvailabilityScheduleNameHeating)) {
      if (boost::optional<ModelObject> mo_ = translateAndMapWorkspaceObject(wo_.get())) {
        if (boost::optional<Schedule> availabilityScheduleHeating_ = mo_->optionalCast<Schedule>()) {
          awhp_hc.setAvailabilitySchedule(availabilityScheduleHeating_.get());
        } else {
          LOG(Warn, workspaceObject.briefDescription() << " has a wrong type for 'Availability Schedule Name Heating'");
        }
      }
    }

    // Rated Inlet Air Temperature in Heating Mode: Optional Double
    if (boost::optional<double> ratedInletAirTemperature_ =
          workspaceObject.getDouble(HeatPump_AirToWaterFields::RatedInletAirTemperatureinHeatingMode)) {
      awhp_hc.setRatedInletAirTemperature(ratedInletAirTemperature_.get());
    }

    // Rated Air Flow Rate in Heating Mode: Optional Double
    if (boost::optional<double> ratedAirFlowRate_ = workspaceObject.getDouble(HeatPump_AirToWaterFields::RatedAirFlowRateinHeatingMode)) {
      awhp_hc.setRatedAirFlowRate(ratedAirFlowRate_.get());
    }

    // Rated Leaving Water Temperature in Heating Mode: Optional Double
    if (boost::optional<double> ratedLeavingWaterTemperature_ =
          workspaceObject.getDouble(HeatPump_AirToWaterFields::RatedLeavingWaterTemperatureinHeatingMode)) {
      awhp_hc.setRatedLeavingWaterTemperature(ratedLeavingWaterTemperature_.get());
    }

    // Rated Water Flow Rate in Heating Mode: Optional Double
    if (boost::optional<double> ratedWaterFlowRate_ = workspaceObject.getDouble(HeatPump_AirToWaterFields::RatedWaterFlowRateinHeatingMode)) {
      awhp_hc.setRatedWaterFlowRate(ratedWaterFlowRate_.get());
    }

    // Minimum Outdoor Air Temperature in Heating Mode: Optional Double
    if (boost::optional<double> minimumOutdoorAirTemperature_ =
          workspaceObject.getDouble(HeatPump_AirToWaterFields::MinimumOutdoorAirTemperatureinHeatingMode)) {
      awhp_hc.setMinimumOutdoorAirTemperature(minimumOutdoorAirTemperature_.get());
    }

    // Maximum Outdoor Air Temperature in Heating Mode: Optional Double
    if (boost::optional<double> maximumOutdoorAirTemperature_ =
          workspaceObject.getDouble(HeatPump_AirToWaterFields::MaximumOutdoorAirTemperatureinHeatingMode)) {
      awhp_hc.setMaximumOutdoorAirTemperature(maximumOutdoorAirTemperature_.get());
    }

    // Minimum Leaving Water Temperature Curve Name in Heating Mode: Optional Object
    if (boost::optional<WorkspaceObject> wo_ =
          workspaceObject.getTarget(HeatPump_AirToWaterFields::MinimumLeavingWaterTemperatureCurveNameinHeatingMode)) {
      if (boost::optional<ModelObject> mo_ = translateAndMapWorkspaceObject(wo_.get())) {
        if (boost::optional<Curve> minimumLeavingWaterTemperatureCurveinHeatingMode_ = mo_->optionalCast<Curve>()) {
          awhp_hc.setMinimumLeavingWaterTemperatureCurve(minimumLeavingWaterTemperatureCurveinHeatingMode_.get());
        } else {
          LOG(Warn, workspaceObject.briefDescription() << " has a wrong type for 'Minimum Leaving Water Temperature Curve Name in Heating Mode'");
        }
      }
    }
    // Maximum Leaving Water Temperature Curve Name in Heating Mode: Optional Object
    if (boost::optional<WorkspaceObject> wo_ =
          workspaceObject.getTarget(HeatPump_AirToWaterFields::MaximumLeavingWaterTemperatureCurveNameinHeatingMode)) {
      if (boost::optional<ModelObject> mo_ = translateAndMapWorkspaceObject(wo_.get())) {
        if (boost::optional<Curve> maximumLeavingWaterTemperatureCurveinHeatingMode_ = mo_->optionalCast<Curve>()) {
          awhp_hc.setMaximumLeavingWaterTemperatureCurve(maximumLeavingWaterTemperatureCurveinHeatingMode_.get());
        } else {
          LOG(Warn, workspaceObject.briefDescription() << " has a wrong type for 'Maximum Leaving Water Temperature Curve Name in Heating Mode'");
        }
      }
    }

    // Sizing Factor for Heating: Optional Double
    if (boost::optional<double> sizingFactor_ = workspaceObject.getDouble(HeatPump_AirToWaterFields::SizingFactorforHeating)) {
      awhp_hc.setSizingFactor(sizingFactor_.get());
    }

    unsigned startIndex = HeatPump_AirToWaterFields::RatedHeatingCapacityatSpeed1;
    const unsigned number_fields =
      static_cast<unsigned>(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofPLRCurveNameatSpeed1) - startIndex + 1;

    auto getFieldIndex = [&startIndex](HeatPump_AirToWaterFields::domain field) -> unsigned {
      return startIndex + (static_cast<unsigned>(field) - static_cast<unsigned>(HeatPump_AirToWaterFields::RatedHeatingCapacityatSpeed1));
    };
    for (int i = 1; i <= numberofSpeedsforHeating; ++i) {

      HeatPumpAirToWaterHeatingSpeedData speed(m_model);
      speed.setName(awhp_hc.nameString() + " Speed " + std::to_string(i));
      // Rated Heating Capacity at Speed
      if (boost::optional<double> ratedHeatingCapacityatSpeed_ =
            workspaceObject.getDouble(getFieldIndex(HeatPump_AirToWaterFields::RatedHeatingCapacityatSpeed1))) {
        speed.setRatedHeatingCapacity(ratedHeatingCapacityatSpeed_.get());
      }

      // Rated COP for Heating at Speed
      if (boost::optional<double> ratedCOPforHeatingatSpeed_ =
            workspaceObject.getDouble(getFieldIndex(HeatPump_AirToWaterFields::RatedCOPforHeatingatSpeed1))) {
        speed.setRatedCOPforHeating(ratedCOPforHeatingatSpeed_.get());
      }

      // Normalized Heating Capacity Function of Temperature Curve Name at Speed
      if (boost::optional<WorkspaceObject> wo_ =
            workspaceObject.getTarget(getFieldIndex(HeatPump_AirToWaterFields::NormalizedHeatingCapacityFunctionofTemperatureCurveNameatSpeed1))) {
        if (boost::optional<ModelObject> mo_ = translateAndMapWorkspaceObject(wo_.get())) {
          if (boost::optional<Curve> normalizedHeatingCapacityFunctionofTemperatureCurveatSpeed_ = mo_->optionalCast<Curve>()) {
            speed.normalizedHeatingCapacityFunctionofTemperatureCurve().remove();
            speed.setNormalizedHeatingCapacityFunctionofTemperatureCurve(normalizedHeatingCapacityFunctionofTemperatureCurveatSpeed_.get());
          } else {
            LOG(Warn, workspaceObject.briefDescription()
                        << " has a wrong type for 'Normalized Heating Capacity Function of Temperature Curve Name at Speed " << i);
          }
        }
      }

      // Heating Energy Input Ratio Function of Temperature Curve Name at Speed
      if (boost::optional<WorkspaceObject> wo_ =
            workspaceObject.getTarget(getFieldIndex(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofTemperatureCurveNameatSpeed1))) {
        if (boost::optional<ModelObject> mo_ = translateAndMapWorkspaceObject(wo_.get())) {
          if (boost::optional<Curve> heatingEnergyInputRatioFunctionofTemperatureCurveatSpeed_ = mo_->optionalCast<Curve>()) {
            speed.heatingEnergyInputRatioFunctionofTemperatureCurve().remove();
            speed.setHeatingEnergyInputRatioFunctionofTemperatureCurve(heatingEnergyInputRatioFunctionofTemperatureCurveatSpeed_.get());
          } else {
            LOG(Warn, workspaceObject.briefDescription()
                        << " has a wrong type for 'Heating Energy Input Ratio Function of Temperature Curve Name at Speed " << i);
          }
        }
      }

      // Heating Energy Input Ratio Function of PLR Curve Name at Speed
      if (boost::optional<WorkspaceObject> wo_ =
            workspaceObject.getTarget(getFieldIndex(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofPLRCurveNameatSpeed1))) {
        if (boost::optional<ModelObject> mo_ = translateAndMapWorkspaceObject(wo_.get())) {
          if (boost::optional<Curve> heatingEnergyInputRatioFunctionofPLRCurveatSpeed_ = mo_->optionalCast<Curve>()) {
            speed.heatingEnergyInputRatioFunctionofPLRCurve().remove();
            speed.setHeatingEnergyInputRatioFunctionofPLRCurve(heatingEnergyInputRatioFunctionofPLRCurveatSpeed_.get());
          } else {
            LOG(Warn, workspaceObject.briefDescription()
                        << " has a wrong type for 'Heating Energy Input Ratio Function of PLR Curve Name at Speed " << i)
          }
        }
      }

      if (!awhp_hc.addSpeed(speed)) {
        LOG(Error, "For " << workspaceObject.briefDescription() << ", cannot add speed data " << i << " to HeatPumpAirToWaterHeating");
      }

      startIndex += number_fields;
    }

    // Booster Mode On Heating: Optional Boolean
    const std::string boosterModeOnHeating = workspaceObject.getString(HeatPump_AirToWaterFields::BoosterModeOnHeating, true).get();
    if (istringEqual("Yes", boosterModeOnHeating)) {
      HeatPumpAirToWaterHeatingSpeedData speed(m_model);
      speed.setName(awhp_hc.nameString() + " Booster Mode On Speed");

      // Rated Heating Capacity in Booster Mode: Optional Double
      if (boost::optional<double> ratedHeatingCapacityinBoosterMode_ =
            workspaceObject.getDouble(HeatPump_AirToWaterFields::RatedHeatingCapacityinBoosterMode)) {
        speed.setRatedHeatingCapacity(ratedHeatingCapacityinBoosterMode_.get());
      }

      // Rated Heating COP in Booster Mode: Optional Double
      if (boost::optional<double> ratedHeatingCOPinBoosterMode_ =
            workspaceObject.getDouble(HeatPump_AirToWaterFields::RatedHeatingCOPinBoosterMode)) {
        speed.setRatedCOPforHeating(ratedHeatingCOPinBoosterMode_.get());
      }

      // Normalized Heating Capacity Function of Temperature Curve Name in Booster Mode: Optional Object
      if (boost::optional<WorkspaceObject> wo_ =
            workspaceObject.getTarget(HeatPump_AirToWaterFields::NormalizedHeatingCapacityFunctionofTemperatureCurveNameinBoosterMode)) {
        if (boost::optional<ModelObject> mo_ = translateAndMapWorkspaceObject(wo_.get())) {
          if (boost::optional<Curve> normalizedHeatingCapacityFunctionofTemperatureCurveinBoosterMode_ = mo_->optionalCast<Curve>()) {
            speed.normalizedHeatingCapacityFunctionofTemperatureCurve().remove();
            speed.setNormalizedHeatingCapacityFunctionofTemperatureCurve(normalizedHeatingCapacityFunctionofTemperatureCurveinBoosterMode_.get());
          } else {
            LOG(Warn, workspaceObject.briefDescription()
                        << " has a wrong type for 'Normalized Heating Capacity Function of Temperature Curve Name in Booster Mode'");
          }
        }
      }
      // Heating Energy Input Ratio Function of Temperature Curve Name in Booster Mode: Optional Object
      if (boost::optional<WorkspaceObject> wo_ =
            workspaceObject.getTarget(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofTemperatureCurveNameinBoosterMode)) {
        if (boost::optional<ModelObject> mo_ = translateAndMapWorkspaceObject(wo_.get())) {
          if (boost::optional<Curve> heatingEnergyInputRatioFunctionofTemperatureCurveinBoosterMode_ = mo_->optionalCast<Curve>()) {
            speed.heatingEnergyInputRatioFunctionofTemperatureCurve().remove();
            speed.setHeatingEnergyInputRatioFunctionofTemperatureCurve(heatingEnergyInputRatioFunctionofTemperatureCurveinBoosterMode_.get());
          } else {
            LOG(Warn, workspaceObject.briefDescription()
                        << " has a wrong type for 'Heating Energy Input Ratio Function of Temperature Curve Name in Booster Mode'");
          }
        }
      }
      // Heating Energy Input Ratio Function of PLR Curve Name in Booster Mode: Optional Object
      if (boost::optional<WorkspaceObject> wo_ =
            workspaceObject.getTarget(HeatPump_AirToWaterFields::HeatingEnergyInputRatioFunctionofPLRCurveNameinBoosterMode)) {
        if (boost::optional<ModelObject> mo_ = translateAndMapWorkspaceObject(wo_.get())) {
          if (boost::optional<Curve> heatingEnergyInputRatioFunctionofPLRCurveinBoosterMode_ = mo_->optionalCast<Curve>()) {
            speed.heatingEnergyInputRatioFunctionofPLRCurve().remove();
            speed.setHeatingEnergyInputRatioFunctionofPLRCurve(heatingEnergyInputRatioFunctionofPLRCurveinBoosterMode_.get());
          } else {
            LOG(Warn, workspaceObject.briefDescription()
                        << " has a wrong type for 'Heating Energy Input Ratio Function of PLR Curve Name in Booster Mode'");
          }
        }
      }
      if (!awhp_hc.setBoosterModeOnSpeed(speed)) {
        LOG(Error, "For " << workspaceObject.briefDescription() << ", cannot set booster mode on speed to HeatPumpAirToWaterHeating");
      }
    }

    return awhp_hc;
  }

  boost::optional<ModelObject> ReverseTranslator::translateHeatPumpAirToWater(const WorkspaceObject& workspaceObject) {

    openstudio::model::HeatPumpAirToWater modelObject(m_model);

    // Name
    if (boost::optional<std::string> name_ = workspaceObject.name()) {
      modelObject.setName(name_.get());
    }

    // Operating Mode Control Method: Optional String
    if (boost::optional<std::string> operatingModeControlMethod_ = workspaceObject.getString(HeatPump_AirToWaterFields::OperatingModeControlMethod)) {
      modelObject.setOperatingModeControlMethod(operatingModeControlMethod_.get());
    }

    // Operating Mode Control Option for Multiple Unit: Optional String
    if (boost::optional<std::string> operatingModeControlOptionforMultipleUnit_ =
          workspaceObject.getString(HeatPump_AirToWaterFields::OperatingModeControlOptionforMultipleUnit)) {
      modelObject.setOperatingModeControlOptionforMultipleUnit(operatingModeControlOptionforMultipleUnit_.get());
    }

    // Operating Mode Control Schedule Name: Optional Object
    if (boost::optional<WorkspaceObject> wo_ = workspaceObject.getTarget(HeatPump_AirToWaterFields::OperatingModeControlScheduleName)) {
      if (boost::optional<ModelObject> mo_ = translateAndMapWorkspaceObject(wo_.get())) {
        if (boost::optional<Schedule> operatingModeControlSchedule_ = mo_->optionalCast<Schedule>()) {
          modelObject.setOperatingModeControlSchedule(operatingModeControlSchedule_.get());
        } else {
          LOG(Warn, workspaceObject.briefDescription() << " has a wrong type for 'Operating Mode Control Schedule Name'");
        }
      }
    }

    // Minimum Part Load Ratio: Optional Double
    if (boost::optional<double> minimumPartLoadRatio_ = workspaceObject.getDouble(HeatPump_AirToWaterFields::MinimumPartLoadRatio)) {
      modelObject.setMinimumPartLoadRatio(minimumPartLoadRatio_.get());
    }

    // Air Inlet Node Name: Required Node
    if (auto airInletNodeName_ = workspaceObject.getString(HeatPump_AirToWaterFields::AirInletNodeName)) {
      modelObject.setAirInletNodeName(airInletNodeName_.get());
    }

    // Air Outlet Node Name: Required Node
    if (auto airOutletNodeName_ = workspaceObject.getString(HeatPump_AirToWaterFields::AirOutletNodeName)) {
      modelObject.setAirOutletNodeName(airOutletNodeName_.get());
    }
    // Hot Water Inlet Node Name: Optional Node

    // Hot Water Outlet Node Name: Optional Node

    // Chilled Water Inlet Node Name: Optional Node

    // Chilled Water Outlet Node Name: Optional Node

    // Maximum Outdoor Dry Bulb Temperature For Defrost Operation: Optional Double
    if (boost::optional<double> maximumOutdoorDryBulbTemperatureForDefrostOperation_ =
          workspaceObject.getDouble(HeatPump_AirToWaterFields::MaximumOutdoorDryBulbTemperatureForDefrostOperation)) {
      modelObject.setMaximumOutdoorDryBulbTemperatureForDefrostOperation(maximumOutdoorDryBulbTemperatureForDefrostOperation_.get());
    }

    // Heat Pump Defrost Control: Optional String
    if (boost::optional<std::string> heatPumpDefrostControl_ = workspaceObject.getString(HeatPump_AirToWaterFields::HeatPumpDefrostControl)) {
      modelObject.setHeatPumpDefrostControl(heatPumpDefrostControl_.get());
    }

    // Heat Pump Defrost Time Period Fraction: Optional Double
    if (boost::optional<double> heatPumpDefrostTimePeriodFraction_ =
          workspaceObject.getDouble(HeatPump_AirToWaterFields::HeatPumpDefrostTimePeriodFraction)) {
      modelObject.setHeatPumpDefrostTimePeriodFraction(heatPumpDefrostTimePeriodFraction_.get());
    }

    // Resistive Defrost Heater Capacity: Optional Double
    if (boost::optional<double> resistiveDefrostHeaterCapacity_ =
          workspaceObject.getDouble(HeatPump_AirToWaterFields::ResistiveDefrostHeaterCapacity)) {
      modelObject.setResistiveDefrostHeaterCapacity(resistiveDefrostHeaterCapacity_.get());
    }

    // Defrost Energy Input Ratio Function of Temperature Curve Name: Optional Object
    if (boost::optional<WorkspaceObject> wo_ =
          workspaceObject.getTarget(HeatPump_AirToWaterFields::DefrostEnergyInputRatioFunctionofTemperatureCurveName)) {
      if (boost::optional<ModelObject> mo_ = translateAndMapWorkspaceObject(wo_.get())) {
        if (boost::optional<Curve> defrostEnergyInputRatioFunctionofTemperatureCurve_ = mo_->optionalCast<Curve>()) {
          modelObject.setDefrostEnergyInputRatioFunctionofTemperatureCurve(defrostEnergyInputRatioFunctionofTemperatureCurve_.get());
        } else {
          LOG(Warn, workspaceObject.briefDescription() << " has a wrong type for 'Defrost Energy Input Ratio Function of Temperature Curve Name'");
        }
      }
    }
    // Heat Pump Multiplier: Optional Integer
    if (boost::optional<int> heatPumpMultiplier_ = workspaceObject.getInt(HeatPump_AirToWaterFields::HeatPumpMultiplier)) {
      modelObject.setHeatPumpMultiplier(heatPumpMultiplier_.get());
    }

    // Control Type: Optional String
    if (boost::optional<std::string> controlType_ = workspaceObject.getString(HeatPump_AirToWaterFields::ControlType)) {
      modelObject.setControlType(controlType_.get());
    }

    // Crankcase Heater Capacity: Optional Double
    if (boost::optional<double> crankcaseHeaterCapacity_ = workspaceObject.getDouble(HeatPump_AirToWaterFields::CrankcaseHeaterCapacity)) {
      modelObject.setCrankcaseHeaterCapacity(crankcaseHeaterCapacity_.get());
    }

    // Crankcase Heater Capacity Function of Temperature Curve Name: Optional Object
    if (boost::optional<WorkspaceObject> wo_ =
          workspaceObject.getTarget(HeatPump_AirToWaterFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName)) {
      if (boost::optional<ModelObject> mo_ = translateAndMapWorkspaceObject(wo_.get())) {
        if (boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve_ = mo_->optionalCast<Curve>()) {
          modelObject.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(crankcaseHeaterCapacityFunctionofTemperatureCurve_.get());
        } else {
          LOG(Warn, workspaceObject.briefDescription() << " has a wrong type for 'Crankcase Heater Capacity Function of Temperature Curve Name'");
        }
      }
    }
    // Maximum Ambient Temperature for Crankcase Heater Operation: Optional Double
    if (boost::optional<double> maximumAmbientTemperatureforCrankcaseHeaterOperation_ =
          workspaceObject.getDouble(HeatPump_AirToWaterFields::MaximumAmbientTemperatureforCrankcaseHeaterOperation)) {
      modelObject.setMaximumAmbientTemperatureforCrankcaseHeaterOperation(maximumAmbientTemperatureforCrankcaseHeaterOperation_.get());
    }

    if (auto awhp_hc_ = translateHeatPumpAirToWaterHeating(workspaceObject)) {
      modelObject.setHeatingOperationMode(awhp_hc_->cast<HeatPumpAirToWaterHeating>());
    }
    if (auto awhp_cc_ = translateHeatPumpAirToWaterCooling(workspaceObject)) {
      modelObject.setCoolingOperationMode(awhp_cc_->cast<HeatPumpAirToWaterCooling>());
    }

    return modelObject;
  }  // End of translate function

}  // end namespace energyplus
}  // end namespace openstudio
