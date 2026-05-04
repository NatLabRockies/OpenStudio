/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject.hpp"
#include "ModelObject_Impl.hpp"
#include "Model.hpp"
#include "Model_Impl.hpp"
#include "Node.hpp"
#include "ResourceObject/ScheduleTypeLimits.hpp"
#include "Schedule/Schedule.hpp"

#include "../../utilities/core/Assert.hpp"
#include "../../utilities/core/StringHelpers.hpp"
#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idf/WorkspaceObject_Impl.hpp"
#include "../../utilities/sql/SqlFile.hpp"

#include <array>
#include <string>

namespace openstudio {
namespace epmodel {

  ModelObject::ModelObject(IddObjectType type, const Model& model, bool fastName, bool isTransient)
    : WorkspaceObject(model.getImpl<detail::Model_Impl>()->createObject(IdfObject(type, fastName), false, isTransient)) {
    auto modelImpl = model.getImpl<detail::Model_Impl>();
    openstudio::detail::WorkspaceObject_ImplPtrVector impls;
    impls.push_back(openstudio::IdfObject::getImpl<openstudio::detail::WorkspaceObject_Impl>());
    modelImpl->addObjects(impls, openstudio::UHPointerVector(), openstudio::HUPointerVector(), false, false, false);
  }

  ModelObject::ModelObject(std::shared_ptr<ImplType> impl) : WorkspaceObject(std::move(impl)) {}

  std::shared_ptr<ModelObject::ImplType> ModelObject::getImpl() const {
    return openstudio::IdfObject::getImpl<detail::ModelObject_Impl>();
  }

  Model ModelObject::model() const {
    return getImpl<detail::ModelObject_Impl>()->model();
  }

  ModelObject ModelObject::create(IddObjectType type, const Model& model, bool fastName) {
    return ModelObject(type, model, fastName);
  }

  bool ModelObject::operator<(const ModelObject& right) const {
    return (getImpl<detail::ModelObject_Impl>()) < (right.getImpl<detail::ModelObject_Impl>());
  }

  bool ModelObject::operator==(const ModelObject& other) const {
    return (handle() == other.handle());
  }

  bool ModelObject::operator!=(const ModelObject& other) const {
    return (handle() != other.handle());
  }

  boost::optional<double> ModelObject::getAutosizedValue(const std::string& valueName, const std::string& units) const {
    return getImpl<detail::ModelObject_Impl>()->getAutosizedValue(valueName, units);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    struct ScheduleTypeSpec
    {
      const char* className;
      const char* scheduleDisplayName;
      bool isContinuous;
      bool enforceNumericType;
      const char* unitType;
      boost::optional<double> lowerLimitValue;
      boost::optional<double> upperLimitValue;
    };

    const ScheduleTypeSpec* findScheduleTypeSpec(const std::string& className, const std::string& scheduleDisplayName) {
      static const std::array<ScheduleTypeSpec, 133> specs{{
        {"AirLoopHVAC", "Availability Manager Scheduled On", false, true, "Availability", 0.0, 1.0},
        {"AvailabilityManagerScheduledOn", "Availability Manager Scheduled On", false, true, "Availability", 0.0, 1.0},
        {"AvailabilityManagerScheduledOff", "Availability Manager Scheduled Off", false, true, "Availability", 0.0, 1.0},
        {"SetpointManagerScheduled", "(Exact, Min, Max) Temperature", true, true, "Temperature", boost::none, boost::none},
        {"SetpointManagerScheduled", "(Exact, Min, Max) Humidity Ratio", true, true, "Dimensionless", 0.0, boost::none},
        {"SetpointManagerScheduled", "(Exact, Min, Max) Mass Flow Rate", true, true, "MassFlowRate", 0.0, boost::none},
        {"ThermostatSetpointDualSetpoint", "Heating Setpoint Temperature", true, true, "Temperature", boost::none, boost::none},
        {"ThermostatSetpointDualSetpoint", "Cooling Setpoint Temperature", true, true, "Temperature", boost::none, boost::none},
        {"ZoneControlThermostatStagedDualSetpoint", "Heating Temperature Setpoint Schedule", true, true, "Temperature", boost::none, boost::none},
        {"ZoneControlThermostatStagedDualSetpoint", "Cooling Temperature Setpoint Base Schedule", true, true, "Temperature", boost::none, boost::none},
        {"FanConstantVolume", "Availability", false, true, "Availability", 0.0, 1.0},
        {"FanOnOff", "Availability", false, true, "Availability", 0.0, 1.0},
        {"FanVariableVolume", "Availability", false, true, "Availability", 0.0, 1.0},
        {"FanSystemModel", "Availability", false, true, "Availability", 0.0, 1.0},
        {"ZoneHVACUnitHeater", "Availability", false, true, "Availability", 0.0, 1.0},
        {"ZoneHVACUnitVentilator", "Availability", false, true, "Availability", 0.0, 1.0},
        {"ZoneHVACUnitVentilator", "Supply Air Fan Operating Mode", false, true, "Availability", 0.0, 1.0},
        {"ZoneHVACFourPipeFanCoil", "Availability", false, true, "Availability", 0.0, 1.0},
        {"ZoneHVACFourPipeFanCoil", "Outdoor Air", true, true, "Dimensionless", 0.0, 1.0},
        {"ZoneHVACFourPipeFanCoil", "Supply Air Fan Operating Mode", false, true, "Availability", 0.0, 1.0},
        {"ZoneHVACPackagedTerminalAirConditioner", "Availability", false, true, "Availability", 0.0, 1.0},
        {"ZoneHVACPackagedTerminalAirConditioner", "Supply Air Fan Operating Mode", false, true, "Availability", 0.0, 1.0},
        {"ZoneHVACPackagedTerminalHeatPump", "Availability", false, true, "Availability", 0.0, 1.0},
        {"ZoneHVACPackagedTerminalHeatPump", "Supply Air Fan Operating Mode", false, true, "Availability", 0.0, 1.0},
        {"ZoneHVACWaterToAirHeatPump", "Availability", false, true, "Availability", 0.0, 1.0},
        {"ZoneHVACWaterToAirHeatPump", "Supply Air Fan Operating Mode", false, true, "Availability", 0.0, 1.0},
        {"ZoneHVACBaseboardConvectiveWater", "Availability", false, true, "Availability", 0.0, 1.0},
        {"ZoneHVACDehumidifierDX", "Availability", false, true, "Availability", 0.0, 1.0},
        {"ZoneHVACBaseboardRadiantConvectiveWater", "Availability", false, true, "Availability", 0.0, 1.0},
        {"ZoneHVACBaseboardRadiantConvectiveElectric", "Availability", false, true, "Availability", 0.0, 1.0},
        {"ZoneHVACHighTemperatureRadiant", "Availability", false, true, "Availability", 0.0, 1.0},
        {"ZoneHVACHighTemperatureRadiant", "Heating Setpoint Temperature", true, true, "Temperature", boost::none, boost::none},
        {"ZoneHVACLowTemperatureRadiantElectric", "Availability", false, true, "Availability", 0.0, 1.0},
        {"ZoneHVACLowTemperatureRadiantElectric", "Heating Setpoint Temperature", true, true, "Temperature", boost::none, boost::none},
        {"ZoneHVACEnergyRecoveryVentilator", "Availability", false, true, "Availability", 0.0, 1.0},
        {"ZoneHVACEvaporativeCoolerUnit", "Availability", false, true, "Availability", 0.0, 1.0},
        {"EvaporativeCoolerDirectResearchSpecial", "Availability", false, false, "Availability", 0.0, 1.0},
        {"EvaporativeCoolerIndirectResearchSpecial", "Availability", false, false, "Availability", 0.0, 1.0},
        {"ZoneHVACTerminalUnitVariableRefrigerantFlow", "Terminal Unit Availability", false, true, "Availability", 0.0, 1.0},
        {"ZoneHVACTerminalUnitVariableRefrigerantFlow", "Supply Air Fan Operating Mode", false, true, "Availability", 0.0, 1.0},
        {"AirTerminalSingleDuctConstantVolumeCooledBeam", "Availability", false, true, "Availability", 0.0, 1.0},
        {"AirLoopHVACUnitarySystem", "Availability", false, true, "Availability", 0.0, 1.0},
        {"AirLoopHVACUnitarySystem", "Supply Air Fan Operating Mode", false, true, "Availability", 0.0, 1.0},
        {"AirTerminalSingleDuctConstantVolumeFourPipeInduction", "Availability", false, true, "Availability", 0.0, 1.0},
        {"AirLoopHVACUnitaryHeatPumpAirToAir", "Availability", false, true, "Availability", 0.0, 1.0},
        {"AirLoopHVACUnitaryHeatPumpAirToAir", "Supply Air Fan Operating Mode", false, true, "Availability", 0.0, 1.0},
        {"AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed", "Availability Schedule", false, true, "Availability", 0.0, 1.0},
        {"AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed", "Supply Air Fan Operating Mode Schedule", false, true, "Availability", 0.0, 1.0},
        {"AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass", "Availability Schedule", false, true, "Availability", 0.0, 1.0},
        {"AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass", "Outdoor Air Flow Rate Multiplier Schedule", true, true, "Dimensionless", 0.0, 1.0},
        {"AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass", "Supply Air Fan Operating Mode Schedule", false, true, "Availability", 0.0, 1.0},
        {"CoilCoolingWater", "Availability", false, true, "Availability", 0.0, 1.0},
        {"CoilHeatingWater", "Availability", false, true, "Availability", 0.0, 1.0},
        {"HeatExchangerFluidToFluid", "Availability", false, true, "Availability", 0.0, 1.0},
        {"ThermalStorageChilledWaterStratified", "Setpoint Temperature", true, true, "Temperature", boost::none, boost::none},
        {"ThermalStorageChilledWaterStratified", "Ambient Temperature", true, true, "Temperature", boost::none, boost::none},
        {"ThermalStorageChilledWaterStratified", "Use Side Availability", false, true, "Availability", 0.0, 1.0},
        {"ThermalStorageChilledWaterStratified", "Source Side Availability", false, true, "Availability", 0.0, 1.0},
        {"WaterHeaterMixed", "Setpoint Temperature", true, true, "Temperature", boost::none, boost::none},
        {"WaterHeaterMixed", "Ambient Temperature", true, true, "Temperature", boost::none, boost::none},
        {"WaterHeaterMixed", "Use Flow Rate Fraction", true, true, "Dimensionless", 0.0, 1.0},
        {"WaterHeaterMixed", "Cold Water Supply Temperature", true, true, "Temperature", boost::none, boost::none},
        {"WaterHeaterMixed", "Indirect Alternate Setpoint Temperature", true, true, "Temperature", boost::none, boost::none},
        {"WaterHeaterStratified", "Heater 1 Setpoint Temperature", true, true, "Temperature", boost::none, boost::none},
        {"WaterHeaterStratified", "Heater 2 Setpoint Temperature", true, true, "Temperature", boost::none, boost::none},
        {"WaterHeaterStratified", "Ambient Temperature", true, true, "Temperature", boost::none, boost::none},
        {"WaterHeaterStratified", "Use Flow Rate Fraction", true, true, "Dimensionless", 0.0, 1.0},
        {"WaterHeaterStratified", "Cold Water Supply Temperature", true, true, "Temperature", boost::none, boost::none},
        {"WaterHeaterStratified", "Indirect Alternate Setpoint Temperature", true, true, "Temperature", boost::none, boost::none},
        {"WaterUseConnections", "Hot Water Supply Temperature", true, true, "Temperature", boost::none, boost::none},
        {"WaterUseConnections", "Cold Water Supply Temperature", true, true, "Temperature", boost::none, boost::none},
        {"HeatPumpAirToWater", "Operating Mode Control", false, true, "", 0.0, 2.0},
        {"RefrigerationCondenserWaterCooled", "Water Outlet Temperature", true, true, "Temperature", boost::none, boost::none},
        {"RefrigerationCompressorRack", "Water Cooled Condenser Outlet Temperature", true, true, "Temperature", boost::none, boost::none},
        {"RefrigerationCompressorRack", "Evaporative Condenser Availability", false, true, "Availability", 0.0, 1.0},
        {"CentralHeatPumpSystem", "Ancillary Operation", false, true, "Availability", 0.0, 1.0},
        {"ChillerElectricEIR", "Basin Heater Operating", false, true, "Availability", 0.0, 1.0},
        {"CoolingTowerSingleSpeed", "Basin Heater Operating", false, true, "Availability", 0.0, 1.0},
        {"CoolingTowerSingleSpeed", "Blowdown Makeup Water Usage", false, true, "Availability", 0.0, 1.0},
        {"CoolingTowerVariableSpeed", "Basin Heater Operating Schedule", false, false, "Availability", 0.0, 1.0},
        {"CoolingTowerVariableSpeed", "Blowdown Makeup Water Usage Schedule", true, false, "VolumetricFlowRate", 0.0, boost::none},
        {"CoolingTowerTwoSpeed", "Basin Heater Operating", false, false, "Availability", 0.0, 1.0},
        {"CoolingTowerTwoSpeed", "Blowdown Makeup Water Usage", true, false, "VolumetricFlowRate", 0.0, boost::none},
        {"ChillerElectricEIR", "Heat Recovery Inlet High Temperature Limit", true, true, "Temperature", boost::none, boost::none},
        {"ChillerElectricEIR", "Temperature Difference Across Condenser", true, true, "Temperature", boost::none, boost::none},
        {"ChillerElectricASHRAE205", "Ambient Temperature", true, true, "Temperature", boost::none, boost::none},
        {"ChillerElectricReformulatedEIR", "Heat Recovery Inlet High Temperature Limit", true, true, "Temperature", boost::none, boost::none},
        {"ChillerElectricReformulatedEIR", "Temperature Difference Across Condenser", true, true, "Temperature", boost::none, boost::none},
        {"CoilWaterHeatingAirToWaterHeatPump", "Availability Schedule", false, true, "Availability", 0.0, 1.0},
        {"CoilCoolingWaterToAirHeatPumpEquationFit", "Availability Schedule", false, true, "Availability", 0.0, 1.0},
        {"CoilHeatingWaterToAirHeatPumpEquationFit", "Availability Schedule", false, true, "Availability", 0.0, 1.0},
        {"CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit", "Availability Schedule", false, true, "Availability", 0.0, 1.0},
        {"CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit", "Availability Schedule", false, true, "Availability", 0.0, 1.0},
        {"CoilWaterHeatingAirToWaterHeatPumpVariableSpeed", "Availability Schedule", false, true, "Availability", 0.0, 1.0},
        {"WaterHeaterHeatPump", "Availability", false, true, "Availability", 0.0, 1.0},
        {"WaterHeaterHeatPump", "Compressor Setpoint Temperature", true, true, "Temperature", boost::none, boost::none},
        {"WaterHeaterHeatPump", "Inlet Air Temperature", true, true, "Temperature", boost::none, boost::none},
        {"WaterHeaterHeatPump", "Inlet Air Humidity", true, true, "Dimensionless", 0.0, 1.0},
        {"WaterHeaterHeatPump", "Compressor Ambient Temperature", true, true, "Temperature", boost::none, boost::none},
        {"WaterHeaterHeatPump", "Inlet Air Mixer", true, true, "Dimensionless", 0.0, 1.0},
        {"WaterHeaterHeatPumpWrappedCondenser", "Availability", false, true, "Availability", 0.0, 1.0},
        {"WaterHeaterHeatPumpWrappedCondenser", "Compressor Setpoint Temperature", true, true, "Temperature", boost::none, boost::none},
        {"WaterHeaterHeatPumpWrappedCondenser", "Inlet Air Temperature", true, true, "Temperature", boost::none, boost::none},
        {"WaterHeaterHeatPumpWrappedCondenser", "Inlet Air Humidity", true, true, "Dimensionless", 0.0, 1.0},
        {"WaterHeaterHeatPumpWrappedCondenser", "Compressor Ambient Temperature", true, true, "Temperature", boost::none, boost::none},
        {"WaterHeaterHeatPumpWrappedCondenser", "Inlet Air Mixer", true, true, "Dimensionless", 0.0, 1.0},
        {"DistrictCooling", "Capacity Fraction", true, true, "Dimensionless", 0.0, boost::none},
        {"DistrictHeatingWater", "Capacity Fraction", true, true, "Dimensionless", 0.0, boost::none},
        {"DistrictHeatingSteam", "Capacity Fraction", true, true, "Dimensionless", 0.0, boost::none},
        {"LoadProfilePlant", "Load", true, false, "", boost::none, boost::none},
        {"LoadProfilePlant", "Flow Rate Fraction", true, false, "", 0.0, 1.0},
        {"PlantComponentTemperatureSource", "Source Temperature", true, false, "Temperature", boost::none, boost::none},
        {"PipeIndoor", "Ambient Temperature Schedule", true, true, "Temperature", boost::none, boost::none},
        {"PipeIndoor", "Ambient Air Velocity Schedule", true, true, "Velocity", 0.0, boost::none},
        {"AirTerminalSingleDuctConstantVolumeNoReheat", "Availability", false, true, "Availability", 0.0, 1.0},
        {"AirTerminalSingleDuctConstantVolumeReheat", "Availability", false, true, "Availability", 0.0, 1.0},
        {"AirTerminalSingleDuctConstantVolumeFourPipeBeam", "Primary Air Availability", false, true, "Availability", 0.0, 1.0},
        {"AirTerminalSingleDuctConstantVolumeFourPipeBeam", "Cooling Availability", false, true, "Availability", 0.0, 1.0},
        {"AirTerminalSingleDuctConstantVolumeFourPipeBeam", "Heating Availability", false, true, "Availability", 0.0, 1.0},
        {"AirTerminalSingleDuctVAVNoReheat", "Availability", false, true, "Availability", 0.0, 1.0},
        {"AirTerminalSingleDuctVAVNoReheat", "Minimum Air Flow Fraction", true, true, "Dimensionless", 0.0, 1.0},
        {"AirTerminalSingleDuctVAVNoReheat", "Minimum Air Flow Turndown", true, true, "Dimensionless", 0.0, 1.0},
        {"AirTerminalSingleDuctVAVReheat", "Availability", false, true, "Availability", 0.0, 1.0},
        {"AirTerminalSingleDuctVAVReheat", "Minimum Air Flow Fraction", true, true, "Dimensionless", 0.0, 1.0},
        {"AirTerminalSingleDuctVAVReheat", "Minimum Air Flow Turndown", true, true, "Dimensionless", 0.0, 1.0},
        {"AirTerminalSingleDuctSeriesPIUReheat", "Availability", false, true, "Availability", 0.0, 1.0},
        {"AirTerminalSingleDuctParallelPIUReheat", "Availability", false, true, "Availability", 0.0, 1.0},
        {"AirTerminalSingleDuctVAVHeatAndCoolNoReheat", "Availability", false, true, "Availability", 0.0, 1.0},
        {"AirTerminalSingleDuctVAVHeatAndCoolNoReheat", "Minimum Air Flow Turndown", true, true, "Dimensionless", 0.0, 1.0},
        {"AirTerminalSingleDuctVAVHeatAndCoolReheat", "Availability", false, true, "Availability", 0.0, 1.0},
        {"AirTerminalSingleDuctVAVHeatAndCoolReheat", "Minimum Air Flow Turndown", true, true, "Dimensionless", 0.0, 1.0},
        {"HumidifierSteamElectric", "Availability", false, true, "Availability", 0.0, 1.0},
        {"HumidifierSteamGas", "Availability", false, true, "Availability", 0.0, 1.0},
      }};

      for (const auto& spec : specs) {
        if (openstudio::istringEqual(className, spec.className) && openstudio::istringEqual(scheduleDisplayName, spec.scheduleDisplayName)) {
          return &spec;
        }
      }

      static const ScheduleTypeSpec fanComponentModelAvailability{
        "FanComponentModel", "Availability", false, true, "Availability", 0.0, 1.0,
      };
      if (openstudio::istringEqual(className, fanComponentModelAvailability.className)
          && openstudio::istringEqual(scheduleDisplayName, fanComponentModelAvailability.scheduleDisplayName)) {
        return &fanComponentModelAvailability;
      }

      return nullptr;
    }

    std::string defaultScheduleTypeLimitsName(const ScheduleTypeSpec& spec) {
      std::string result = spec.unitType;
      if (result.empty()) {
        if (spec.isContinuous) {
          if (spec.lowerLimitValue && (*spec.lowerLimitValue == 0.0) && spec.upperLimitValue && (*spec.upperLimitValue == 1.0)) {
            result = "Fractional";
          } else {
            result = "Dimensionless";
          }
        } else if (spec.lowerLimitValue && (*spec.lowerLimitValue == 0.0) && spec.upperLimitValue && (*spec.upperLimitValue == 1.0)) {
          result = "Binary";
        } else {
          result = "Integer";
        }
      } else if (openstudio::istringEqual(result, "Availability")) {
        result = "OnOff";
      }
      return result;
    }

    bool isDimensionlessEquivalentUnitType(const std::string& unitType) {
      return unitType.empty() || openstudio::istringEqual(unitType, "Dimensionless") || openstudio::istringEqual(unitType, "Availability")
             || openstudio::istringEqual(unitType, "ControlMode");
    }

    bool isUnitTypeCompatible(const ScheduleTypeSpec& spec, const openstudio::epmodel::ScheduleTypeLimits& limits) {
      std::string candidateUnitType;
      if (!limits.isUnitTypeDefaulted()) {
        candidateUnitType = limits.unitType();
      }

      if (isDimensionlessEquivalentUnitType(spec.unitType)) {
        return isDimensionlessEquivalentUnitType(candidateUnitType);
      }

      return !candidateUnitType.empty() && openstudio::istringEqual(candidateUnitType, spec.unitType);
    }

    bool isScheduleTypeCompatible(const ScheduleTypeSpec& spec, const openstudio::epmodel::ScheduleTypeLimits& limits) {
      if (spec.enforceNumericType) {
        if (auto numericType = limits.numericType()) {
          const auto* expectedNumericType = spec.isContinuous ? "Continuous" : "Discrete";
          if (!openstudio::istringEqual(*numericType, expectedNumericType)) {
            return false;
          }
        }
      }

      if (!isUnitTypeCompatible(spec, limits)) {
        return false;
      }

      if (spec.lowerLimitValue) {
        if (!limits.lowerLimitValue() || (*limits.lowerLimitValue() < *spec.lowerLimitValue)) {
          return false;
        }
      }

      if (spec.upperLimitValue) {
        if (!limits.upperLimitValue() || (*limits.upperLimitValue() > *spec.upperLimitValue)) {
          return false;
        }
      }

      return true;
    }

    openstudio::epmodel::ScheduleTypeLimits makeScheduleTypeLimits(const ScheduleTypeSpec& spec, openstudio::epmodel::Model model) {
      openstudio::epmodel::ScheduleTypeLimits limits(model);
      if (!defaultScheduleTypeLimitsName(spec).empty()) {
        limits.setName(defaultScheduleTypeLimitsName(spec));
      }
      if (spec.lowerLimitValue) {
        OS_ASSERT(limits.setLowerLimitValue(*spec.lowerLimitValue));
      }
      if (spec.upperLimitValue) {
        OS_ASSERT(limits.setUpperLimitValue(*spec.upperLimitValue));
      }
      OS_ASSERT(limits.setNumericType(spec.isContinuous ? "Continuous" : "Discrete"));
      if (std::string(spec.unitType).empty()) {
        limits.resetUnitType();
      } else {
        OS_ASSERT(limits.setUnitType(spec.unitType));
      }
      return limits;
    }

    ModelObject_Impl::ModelObject_Impl(const openstudio::IdfObject& idfObject, Model_Impl* model, bool keepHandle)
      : openstudio::detail::WorkspaceObject_Impl(idfObject, model, keepHandle) {}

    ModelObject_Impl::ModelObject_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle)
      : openstudio::detail::WorkspaceObject_Impl(other, model, keepHandle) {}

    openstudio::epmodel::Model ModelObject_Impl::model() const {
      return workspace().cast<Model>();
    }

    void ModelObject_Impl::canonicalize(LoadContext& context) {
      if (context.visited.contains(handle())) {
        return;
      }
      context.visited.insert(handle());
      doCanonicalize(context);
    }

    void ModelObject_Impl::doCanonicalize(LoadContext&) {}

    boost::optional<double> ModelObject_Impl::getAutosizedValueFromInitializationSummary(const std::string& valueName,
                                                                                         const std::string& units) const {
      if (!name()) {
        LOG_FREE(Warn, "openstudio.epmodel.ModelObject",
                 "This object does not have a name, cannot retrieve the autosized value '" << valueName << "'.");
        return boost::none;
      }

      if (!model().sqlFile()) {
        LOG_FREE(Warn, "openstudio.epmodel.ModelObject",
                 "This model has no sql file, cannot retrieve the autosized value '" << valueName << "'.");
        return boost::none;
      }

      std::string sqlName = name().get();
      boost::to_upper(sqlName);

      const std::string rowsQuery = R"(
      SELECT RowName FROM TabularDataWithStrings
        WHERE ReportName = 'InitializationSummary'
        AND ReportForString = 'Entire Facility'
        AND TableName = 'Component Sizing Information'
        AND Value = ?;)";

      auto rowNames = model().sqlFile()->execAndReturnVectorOfString(rowsQuery, sqlName);
      if (!rowNames) {
        LOG_FREE(Warn, "openstudio.epmodel.ModelObject",
                 "Could not find a component called '" << sqlName << "' in any rows of the InitializationSummary Component Sizing table.");
        return boost::none;
      }

      std::string valueNameAndUnits = valueName;
      if (units == "typo_in_energyplus") {
        valueNameAndUnits += " []";
      } else if (!units.empty()) {
        valueNameAndUnits += " [" + units + "]";
      }

      for (const std::string& rowName : *rowNames) {
        const std::string rowCheckQuery = R"(
        SELECT Value FROM TabularDataWithStrings
          WHERE ReportName = 'InitializationSummary'
          AND ReportForString = 'Entire Facility'
          AND TableName = 'Component Sizing Information'
          AND RowName = ?
          AND Value = ?;)";
        const auto rowValueName = model().sqlFile()->execAndReturnFirstString(rowCheckQuery, rowName, valueNameAndUnits);
        if (!rowValueName) {
          continue;
        }

        const std::string valQuery = R"(
        SELECT Value FROM TabularDataWithStrings
          WHERE ReportName = 'InitializationSummary'
          AND ReportForString = 'Entire Facility'
          AND TableName = 'Component Sizing Information'
          AND ColumnName='Value'
          AND RowName = ?;)";
        if (auto val = model().sqlFile()->execAndReturnFirstDouble(valQuery, rowName)) {
          return val;
        }
      }

      LOG_FREE(Debug, "openstudio.epmodel.ModelObject",
               "The autosized value query for '" << valueNameAndUnits << "' of '" << sqlName << "' returned no value.");
      return boost::none;
    }

    boost::optional<double> ModelObject_Impl::getAutosizedValue(const std::string& valueName, const std::string& units,
                                                                std::string overrideCompType) const {
      if (!name()) {
        LOG_FREE(Warn, "openstudio.epmodel.ModelObject",
                 "This object does not have a name, cannot retrieve the autosized value '" << valueName << "'.");
        return boost::none;
      }

      if (!model().sqlFile()) {
        LOG_FREE(Warn, "openstudio.epmodel.ModelObject",
                 "This model has no sql file, cannot retrieve the autosized value '" << valueName << "'.");
        return boost::none;
      }

      std::string sqlName = name().get();
      boost::to_upper(sqlName);

      if (overrideCompType.empty()) {
        overrideCompType = iddObject().type().valueDescription();
      }

      const std::string directQuery = R"sql(
      SELECT Value FROM ComponentSizes
        WHERE CompType = ?
          AND CompName = ?
          AND Description = ?
          AND Units = ?;
    )sql";

      auto val = model().sqlFile()->execAndReturnFirstDouble(directQuery, overrideCompType, sqlName, valueName, units);
      if (!val) {
        LOG_FREE(Debug, "openstudio.epmodel.ModelObject",
                 "The direct autosized value query returned no value for component type '" << overrideCompType << "', component '" << sqlName
                   << "', description '" << valueName << "', units '" << units << "'.");
      }
      return val;
    }

    boost::optional<openstudio::epmodel::Node> ModelObject_Impl::resolvedNodeTarget(unsigned fieldIndex) const {
      if (auto node = getObject<openstudio::epmodel::ModelObject>().getModelObjectTarget<openstudio::epmodel::Node>(fieldIndex)) {
        return node;
      }

      auto name = getString(fieldIndex);
      if (name && !name->empty()) {
        // WorkspaceObject::getTarget(...) already treats Node fields as a
        // special case and may materialize the pointer during const lookup.
        // We follow the same rule here: resolving an already-named Node is
        // restoring the live link for existing persisted meaning, not
        // inventing new topology.
        auto node = model().getOrCreateTransientByName<openstudio::epmodel::Node>(*name);
        if (!const_cast<ModelObject_Impl*>(this)->setPointer(fieldIndex, node.handle(), false)) {
          LOG_FREE(Warn, "openstudio.epmodel.ModelObject",
                   "Resolved transient Node '" << node.nameString() << "' for field index " << fieldIndex << " but failed to attach the pointer.");
          return boost::none;
        }
        return node;
      }

      return boost::none;
    }

    openstudio::epmodel::Node ModelObject_Impl::resolvedOrCreatedNodeTarget(unsigned fieldIndex, const std::string& suggestedName) {
      if (auto existingNode = resolvedNodeTarget(fieldIndex)) {
        return *existingNode;
      }

      // The field was blank, so this call is choosing a new node on purpose
      // rather than merely materializing persisted meaning.
      auto node = model().getOrCreateTransientByName<openstudio::epmodel::Node>(suggestedName);
      OS_ASSERT(setPointer(fieldIndex, node.handle(), false));
      return node;
    }

    bool ModelObject_Impl::setSchedule(unsigned fieldIndex, const std::string& className, const std::string& scheduleDisplayName,
                                       openstudio::epmodel::Schedule& schedule) {
      if (schedule.model() != model()) {
        return false;
      }

      const auto* spec = findScheduleTypeSpec(className, scheduleDisplayName);
      if (!spec) {
        return false;
      }

      if (auto limits = schedule.scheduleTypeLimits()) {
        if (!isScheduleTypeCompatible(*spec, *limits)) {
          return false;
        }
      } else {
        auto candidate = makeScheduleTypeLimits(*spec, model());
        if (!schedule.setScheduleTypeLimits(candidate)) {
          candidate.remove();
          return false;
        }
      }

      return setPointer(fieldIndex, schedule.handle(), false);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
