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
      const char* unitType;
      boost::optional<double> lowerLimitValue;
      boost::optional<double> upperLimitValue;
    };

    const ScheduleTypeSpec* findScheduleTypeSpec(const std::string& className, const std::string& scheduleDisplayName) {
      static const std::array<ScheduleTypeSpec, 78> specs{{
        {"AirLoopHVAC", "Availability Manager Scheduled On", false, "Availability", 0.0, 1.0},
        {"AvailabilityManagerScheduledOn", "Availability Manager Scheduled On", false, "Availability", 0.0, 1.0},
        {"AvailabilityManagerScheduledOff", "Availability Manager Scheduled Off", false, "Availability", 0.0, 1.0},
        {"ThermostatSetpointDualSetpoint", "Heating Setpoint Temperature", true, "Temperature", boost::none, boost::none},
        {"ThermostatSetpointDualSetpoint", "Cooling Setpoint Temperature", true, "Temperature", boost::none, boost::none},
        {"ZoneControlThermostatStagedDualSetpoint", "Heating Temperature Setpoint Schedule", true, "Temperature", boost::none, boost::none},
        {"ZoneControlThermostatStagedDualSetpoint", "Cooling Temperature Setpoint Base Schedule", true, "Temperature", boost::none, boost::none},
        {"FanConstantVolume", "Availability", false, "Availability", 0.0, 1.0},
        {"FanOnOff", "Availability", false, "Availability", 0.0, 1.0},
        {"FanVariableVolume", "Availability", false, "Availability", 0.0, 1.0},
        {"FanSystemModel", "Availability", false, "Availability", 0.0, 1.0},
        {"ZoneHVACUnitHeater", "Availability", false, "Availability", 0.0, 1.0},
        {"ZoneHVACUnitVentilator", "Availability", false, "Availability", 0.0, 1.0},
        {"ZoneHVACUnitVentilator", "Supply Air Fan Operating Mode", false, "Availability", 0.0, 1.0},
        {"ZoneHVACFourPipeFanCoil", "Availability", false, "Availability", 0.0, 1.0},
        {"ZoneHVACFourPipeFanCoil", "Outdoor Air", true, "Dimensionless", 0.0, 1.0},
        {"ZoneHVACFourPipeFanCoil", "Supply Air Fan Operating Mode", false, "Availability", 0.0, 1.0},
        {"ZoneHVACPackagedTerminalAirConditioner", "Availability", false, "Availability", 0.0, 1.0},
        {"ZoneHVACPackagedTerminalAirConditioner", "Supply Air Fan Operating Mode", false, "Availability", 0.0, 1.0},
        {"ZoneHVACPackagedTerminalHeatPump", "Availability", false, "Availability", 0.0, 1.0},
        {"ZoneHVACPackagedTerminalHeatPump", "Supply Air Fan Operating Mode", false, "Availability", 0.0, 1.0},
        {"ZoneHVACWaterToAirHeatPump", "Availability", false, "Availability", 0.0, 1.0},
        {"ZoneHVACWaterToAirHeatPump", "Supply Air Fan Operating Mode", false, "Availability", 0.0, 1.0},
        {"ZoneHVACBaseboardConvectiveWater", "Availability", false, "Availability", 0.0, 1.0},
        {"ZoneHVACDehumidifierDX", "Availability", false, "Availability", 0.0, 1.0},
        {"ZoneHVACBaseboardRadiantConvectiveWater", "Availability", false, "Availability", 0.0, 1.0},
        {"ZoneHVACBaseboardRadiantConvectiveElectric", "Availability", false, "Availability", 0.0, 1.0},
        {"ZoneHVACHighTemperatureRadiant", "Availability", false, "Availability", 0.0, 1.0},
        {"ZoneHVACHighTemperatureRadiant", "Heating Setpoint Temperature", true, "Temperature", boost::none, boost::none},
        {"ZoneHVACLowTemperatureRadiantElectric", "Availability", false, "Availability", 0.0, 1.0},
        {"ZoneHVACLowTemperatureRadiantElectric", "Heating Setpoint Temperature", true, "Temperature", boost::none, boost::none},
        {"ZoneHVACEnergyRecoveryVentilator", "Availability", false, "Availability", 0.0, 1.0},
        {"ZoneHVACEvaporativeCoolerUnit", "Availability", false, "Availability", 0.0, 1.0},
        {"ZoneHVACTerminalUnitVariableRefrigerantFlow", "Terminal Unit Availability", false, "Availability", 0.0, 1.0},
        {"ZoneHVACTerminalUnitVariableRefrigerantFlow", "Supply Air Fan Operating Mode", false, "Availability", 0.0, 1.0},
        {"AirLoopHVACUnitarySystem", "Availability", false, "Availability", 0.0, 1.0},
        {"AirLoopHVACUnitarySystem", "Supply Air Fan Operating Mode", false, "Availability", 0.0, 1.0},
        {"AirLoopHVACUnitaryHeatPumpAirToAir", "Availability", false, "Availability", 0.0, 1.0},
        {"AirLoopHVACUnitaryHeatPumpAirToAir", "Supply Air Fan Operating Mode", false, "Availability", 0.0, 1.0},
        {"AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed", "Availability Schedule", false, "Availability", 0.0, 1.0},
        {"AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed", "Supply Air Fan Operating Mode Schedule", false, "Availability", 0.0, 1.0},
        {"AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass", "Availability Schedule", false, "Availability", 0.0, 1.0},
        {"AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass", "Outdoor Air Flow Rate Multiplier Schedule", true, "Dimensionless", 0.0, 1.0},
        {"AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass", "Supply Air Fan Operating Mode Schedule", false, "Availability", 0.0, 1.0},
        {"CoilCoolingWater", "Availability", false, "Availability", 0.0, 1.0},
        {"CoilHeatingWater", "Availability", false, "Availability", 0.0, 1.0},
        {"CoilWaterHeatingAirToWaterHeatPump", "Availability Schedule", false, "Availability", 0.0, 1.0},
        {"CoilCoolingWaterToAirHeatPumpEquationFit", "Availability Schedule", false, "Availability", 0.0, 1.0},
        {"CoilHeatingWaterToAirHeatPumpEquationFit", "Availability Schedule", false, "Availability", 0.0, 1.0},
        {"CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit", "Availability Schedule", false, "Availability", 0.0, 1.0},
        {"CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit", "Availability Schedule", false, "Availability", 0.0, 1.0},
        {"CoilWaterHeatingAirToWaterHeatPumpVariableSpeed", "Availability Schedule", false, "Availability", 0.0, 1.0},
        {"WaterHeaterHeatPump", "Availability", false, "Availability", 0.0, 1.0},
        {"WaterHeaterHeatPump", "Compressor Setpoint Temperature", true, "Temperature", boost::none, boost::none},
        {"WaterHeaterHeatPump", "Inlet Air Temperature", true, "Temperature", boost::none, boost::none},
        {"WaterHeaterHeatPump", "Inlet Air Humidity", true, "Dimensionless", 0.0, 1.0},
        {"WaterHeaterHeatPump", "Compressor Ambient Temperature", true, "Temperature", boost::none, boost::none},
        {"WaterHeaterHeatPump", "Inlet Air Mixer", true, "Dimensionless", 0.0, 1.0},
        {"WaterHeaterHeatPumpWrappedCondenser", "Availability", false, "Availability", 0.0, 1.0},
        {"WaterHeaterHeatPumpWrappedCondenser", "Compressor Setpoint Temperature", true, "Temperature", boost::none, boost::none},
        {"WaterHeaterHeatPumpWrappedCondenser", "Inlet Air Temperature", true, "Temperature", boost::none, boost::none},
        {"WaterHeaterHeatPumpWrappedCondenser", "Inlet Air Humidity", true, "Dimensionless", 0.0, 1.0},
        {"WaterHeaterHeatPumpWrappedCondenser", "Compressor Ambient Temperature", true, "Temperature", boost::none, boost::none},
        {"WaterHeaterHeatPumpWrappedCondenser", "Inlet Air Mixer", true, "Dimensionless", 0.0, 1.0},
        {"AirTerminalSingleDuctConstantVolumeNoReheat", "Availability", false, "Availability", 0.0, 1.0},
        {"AirTerminalSingleDuctConstantVolumeReheat", "Availability", false, "Availability", 0.0, 1.0},
        {"AirTerminalSingleDuctVAVNoReheat", "Availability", false, "Availability", 0.0, 1.0},
        {"AirTerminalSingleDuctVAVNoReheat", "Minimum Air Flow Fraction", true, "Dimensionless", 0.0, 1.0},
        {"AirTerminalSingleDuctVAVNoReheat", "Minimum Air Flow Turndown", true, "Dimensionless", 0.0, 1.0},
        {"AirTerminalSingleDuctVAVReheat", "Availability", false, "Availability", 0.0, 1.0},
        {"AirTerminalSingleDuctVAVReheat", "Minimum Air Flow Fraction", true, "Dimensionless", 0.0, 1.0},
        {"AirTerminalSingleDuctVAVReheat", "Minimum Air Flow Turndown", true, "Dimensionless", 0.0, 1.0},
        {"AirTerminalSingleDuctSeriesPIUReheat", "Availability", false, "Availability", 0.0, 1.0},
        {"AirTerminalSingleDuctParallelPIUReheat", "Availability", false, "Availability", 0.0, 1.0},
        {"AirTerminalSingleDuctVAVHeatAndCoolNoReheat", "Availability", false, "Availability", 0.0, 1.0},
        {"AirTerminalSingleDuctVAVHeatAndCoolNoReheat", "Minimum Air Flow Turndown", true, "Dimensionless", 0.0, 1.0},
        {"AirTerminalSingleDuctVAVHeatAndCoolReheat", "Availability", false, "Availability", 0.0, 1.0},
        {"AirTerminalSingleDuctVAVHeatAndCoolReheat", "Minimum Air Flow Turndown", true, "Dimensionless", 0.0, 1.0},
      }};

      for (const auto& spec : specs) {
        if (openstudio::istringEqual(className, spec.className) && openstudio::istringEqual(scheduleDisplayName, spec.scheduleDisplayName)) {
          return &spec;
        }
      }

      static const ScheduleTypeSpec fanComponentModelAvailability{
        "FanComponentModel", "Availability", false, "Availability", 0.0, 1.0,
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

    bool isScheduleTypeCompatible(const ScheduleTypeSpec& spec, const openstudio::epmodel::ScheduleTypeLimits& limits) {
      if (!std::string(spec.unitType).empty()) {
        if (limits.isUnitTypeDefaulted() || !openstudio::istringEqual(limits.unitType(), spec.unitType)) {
          return false;
        }
      } else if (!limits.isUnitTypeDefaulted() && !limits.unitType().empty()) {
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
