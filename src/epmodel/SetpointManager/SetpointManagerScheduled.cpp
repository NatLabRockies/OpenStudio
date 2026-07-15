/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerScheduled.hpp"
#include "SetpointManager/SetpointManagerScheduled_Impl.hpp"

#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddField.hpp>
#include <utilities/idd/IddKey.hpp>
#include <utilities/idd/SetpointManager_Scheduled_FieldEnums.hxx>

#include <boost/regex.hpp>

namespace openstudio {
namespace epmodel {
  SetpointManagerScheduled::SetpointManagerScheduled(const Model& model) : SetpointManager(SetpointManagerScheduled::iddObjectType(), model) {
    auto impl = getImpl<detail::SetpointManagerScheduled_Impl>();
    OS_ASSERT(impl);
    OS_ASSERT(setControlVariable("Temperature"));
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  SetpointManagerScheduled::SetpointManagerScheduled(std::shared_ptr<detail::SetpointManagerScheduled_Impl> impl)
    : SetpointManager(std::move(impl)) {}

  IddObjectType SetpointManagerScheduled::iddObjectType() {
    return IddObjectType::SetpointManager_Scheduled;
  }

  std::vector<std::string> SetpointManagerScheduled::controlVariableValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::SetpointManager_ScheduledFields::ControlVariable);
  }

  bool SetpointManagerScheduled::isControlVariableDefaulted() const {
    return getImpl<detail::SetpointManagerScheduled_Impl>()->isControlVariableDefaulted();
  }

  void SetpointManagerScheduled::resetControlVariable() {
    getImpl<detail::SetpointManagerScheduled_Impl>()->resetControlVariable();
  }

  Schedule SetpointManagerScheduled::schedule() const {
    return getImpl<detail::SetpointManagerScheduled_Impl>()->schedule();
  }

  bool SetpointManagerScheduled::hasSchedule() const {
    return static_cast<bool>(getModelObjectTarget<openstudio::epmodel::Schedule>(openstudio::SetpointManager_ScheduledFields::ScheduleName));
  }

  bool SetpointManagerScheduled::setSchedule(Schedule& schedule) {
    return getImpl<detail::SetpointManagerScheduled_Impl>()->setSchedule(schedule);
  }

  bool SetpointManagerScheduled::setControlVariableAndSchedule(const std::string& controlVariable, Schedule& schedule) {
    return getImpl<detail::SetpointManagerScheduled_Impl>()->setControlVariableAndSchedule(controlVariable, schedule);
  }

  boost::optional<ModelObject> SetpointManagerScheduled::scheduleAsModelObject() const {
    if (auto schedule = getModelObjectTarget<openstudio::epmodel::Schedule>(openstudio::SetpointManager_ScheduledFields::ScheduleName)) {
      return schedule->cast<ModelObject>();
    }
    return boost::none;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    bool SetpointManagerScheduled_Impl::isAllowedOnPlantLoop() const {
      return true;
    }

    bool SetpointManagerScheduled_Impl::isControlVariableDefaulted() const {
      return isEmpty(openstudio::SetpointManager_ScheduledFields::ControlVariable);
    }

    void SetpointManagerScheduled_Impl::resetControlVariable() {
      OS_ASSERT(setString(openstudio::SetpointManager_ScheduledFields::ControlVariable, ""));
    }

    boost::optional<openstudio::epmodel::Node> SetpointManagerScheduled_Impl::setpointNode() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Node>(
        openstudio::SetpointManager_ScheduledFields::SetpointNodeorNodeListName);
    }

    std::string SetpointManagerScheduled_Impl::controlVariable() const {
      if (auto value = getString(openstudio::SetpointManager_ScheduledFields::ControlVariable, true)) {
        return *value;
      }
      return "";
    }

    bool SetpointManagerScheduled_Impl::setControlVariable(const std::string& value) {
      std::string result;
      if (istringEqual(value, "Temperature")) {
        result = "Temperature";
      } else if (istringEqual(value, "MaximumTemperature")) {
        result = "MaximumTemperature";
      } else if (istringEqual(value, "MinimumTemperature")) {
        result = "MinimumTemperature";
      } else if (istringEqual(value, "HumidityRatio")) {
        result = "HumidityRatio";
      } else if (istringEqual(value, "MaximumHumidityRatio")) {
        result = "MaximumHumidityRatio";
      } else if (istringEqual(value, "MinimumHumidityRatio")) {
        result = "MinimumHumidityRatio";
      } else if (istringEqual(value, "MassFlowRate")) {
        result = "MassFlowRate";
      } else if (istringEqual(value, "MaximumMassFlowRate")) {
        result = "MaximumMassFlowRate";
      } else if (istringEqual(value, "MinimumMassFlowRate")) {
        result = "MinimumMassFlowRate";
      }

      if (!result.empty()) {
        return setString(openstudio::SetpointManager_ScheduledFields::ControlVariable, result);
      }

      return false;
    }

    openstudio::epmodel::Schedule SetpointManagerScheduled_Impl::schedule() const {
      auto schedule =
        getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Schedule>(openstudio::SetpointManager_ScheduledFields::ScheduleName);
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool SetpointManagerScheduled_Impl::setSchedule(openstudio::epmodel::Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::SetpointManager_ScheduledFields::ScheduleName, "SetpointManagerScheduled",
                                           scheduleDisplayName(), schedule);
    }

    bool SetpointManagerScheduled_Impl::setControlVariableAndSchedule(const std::string& controlVariable, openstudio::epmodel::Schedule& schedule) {
      if (auto field = iddObject().getField(openstudio::SetpointManager_ScheduledFields::ControlVariable)) {
        if (auto key = field->getKey(controlVariable)) {
          bool result = ModelObject_Impl::setSchedule(openstudio::SetpointManager_ScheduledFields::ScheduleName, "SetpointManagerScheduled",
                                                      scheduleDisplayName(key->name()), schedule);
          if (result) {
            result = setString(openstudio::SetpointManager_ScheduledFields::ControlVariable, key->name());
            OS_ASSERT(result);
          }
          return result;
        }
      }

      return false;
    }

    std::string SetpointManagerScheduled_Impl::scheduleDisplayName() const {
      return scheduleDisplayName(controlVariable());
    }

    std::string SetpointManagerScheduled_Impl::scheduleDisplayName(const std::string& candidateControlVariable) const {
      std::string result;
      static const boost::regex temperatureRegex("Temperature");
      static const boost::regex humidityRatioRegex("HumidityRatio");
      static const boost::regex massFlowRateRegex("MassFlowRate");
      if (boost::regex_search(candidateControlVariable, temperatureRegex)) {
        result = "(Exact, Min, Max) Temperature";
      } else if (boost::regex_search(candidateControlVariable, humidityRatioRegex)) {
        result = "(Exact, Min, Max) Humidity Ratio";
      } else if (boost::regex_search(candidateControlVariable, massFlowRateRegex)) {
        result = "(Exact, Min, Max) Mass Flow Rate";
      }
      return result;
    }

    bool SetpointManagerScheduled_Impl::setSetpointNode(const openstudio::epmodel::Node& node) {
      return getObject<ModelObject>().setPointer(openstudio::SetpointManager_ScheduledFields::SetpointNodeorNodeListName, node.handle());
    }

    void SetpointManagerScheduled_Impl::doCanonicalize(LoadContext& context) {
      SetpointManager_Impl::doCanonicalize(context);
      canonicalizeSetpointNodeField(context, openstudio::SetpointManager_ScheduledFields::SetpointNodeorNodeListName);

      bool hasControlVariable = false;
      if (auto value = getString(openstudio::SetpointManager_ScheduledFields::ControlVariable, true)) {
        hasControlVariable = !value->empty();
      }

      if (!hasControlVariable) {
        OS_ASSERT(setString(openstudio::SetpointManager_ScheduledFields::ControlVariable, "Temperature"));
        detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:Scheduled '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }

      if (auto schedule =
            getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Schedule>(openstudio::SetpointManager_ScheduledFields::ScheduleName)) {
        OS_ASSERT(setPointer(openstudio::SetpointManager_ScheduledFields::ScheduleName, schedule->handle(), false));
        return;
      }

      if (auto scheduleName = getString(openstudio::SetpointManager_ScheduledFields::ScheduleName)) {
        if (!scheduleName->empty()) {
          for (const auto& candidate : model().getObjectsByName(*scheduleName, true)) {
            if (auto schedule = candidate.optionalCast<openstudio::epmodel::Schedule>()) {
              OS_ASSERT(setPointer(openstudio::SetpointManager_ScheduledFields::ScheduleName, schedule->handle(), false));
              return;
            }
          }
        }
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
