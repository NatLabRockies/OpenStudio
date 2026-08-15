/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerScheduledDualSetpoint.hpp"
#include "SetpointManager/SetpointManagerScheduledDualSetpoint_Impl.hpp"

#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/SetpointManager_Scheduled_DualSetpoint_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SetpointManagerScheduledDualSetpoint::SetpointManagerScheduledDualSetpoint(const Model& model)
    : SetpointManager(SetpointManagerScheduledDualSetpoint::iddObjectType(), model) {
    auto impl = getImpl<detail::SetpointManagerScheduledDualSetpoint_Impl>();
    OS_ASSERT(impl);
    OS_ASSERT(setControlVariable("Temperature"));
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  SetpointManagerScheduledDualSetpoint::SetpointManagerScheduledDualSetpoint(std::shared_ptr<detail::SetpointManagerScheduledDualSetpoint_Impl> impl)
    : SetpointManager(std::move(impl)) {}

  IddObjectType SetpointManagerScheduledDualSetpoint::iddObjectType() {
    return IddObjectType::SetpointManager_Scheduled_DualSetpoint;
  }

  std::vector<std::string> SetpointManagerScheduledDualSetpoint::controlVariableValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SetpointManager_Scheduled_DualSetpointFields::ControlVariable);
  }

  boost::optional<Schedule> SetpointManagerScheduledDualSetpoint::highSetpointSchedule() const {
    return getImpl<detail::SetpointManagerScheduledDualSetpoint_Impl>()->highSetpointSchedule();
  }

  bool SetpointManagerScheduledDualSetpoint::setHighSetpointSchedule(Schedule& schedule) {
    return getImpl<detail::SetpointManagerScheduledDualSetpoint_Impl>()->setHighSetpointSchedule(schedule);
  }

  void SetpointManagerScheduledDualSetpoint::resetHighSetpointSchedule() {
    getImpl<detail::SetpointManagerScheduledDualSetpoint_Impl>()->resetHighSetpointSchedule();
  }

  boost::optional<Schedule> SetpointManagerScheduledDualSetpoint::lowSetpointSchedule() const {
    return getImpl<detail::SetpointManagerScheduledDualSetpoint_Impl>()->lowSetpointSchedule();
  }

  bool SetpointManagerScheduledDualSetpoint::setLowSetpointSchedule(Schedule& schedule) {
    return getImpl<detail::SetpointManagerScheduledDualSetpoint_Impl>()->setLowSetpointSchedule(schedule);
  }

  void SetpointManagerScheduledDualSetpoint::resetLowSetpointSchedule() {
    getImpl<detail::SetpointManagerScheduledDualSetpoint_Impl>()->resetLowSetpointSchedule();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    bool SetpointManagerScheduledDualSetpoint_Impl::isAllowedOnPlantLoop() const {
      return true;
    }

    boost::optional<openstudio::epmodel::Node> SetpointManagerScheduledDualSetpoint_Impl::setpointNode() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Node>(
        openstudio::SetpointManager_Scheduled_DualSetpointFields::SetpointNodeorNodeListName);
    }

    std::string SetpointManagerScheduledDualSetpoint_Impl::controlVariable() const {
      if (auto value = getString(openstudio::SetpointManager_Scheduled_DualSetpointFields::ControlVariable, true)) {
        return *value;
      }
      return "";
    }

    bool SetpointManagerScheduledDualSetpoint_Impl::setControlVariable(const std::string& value) {
      return setString(openstudio::SetpointManager_Scheduled_DualSetpointFields::ControlVariable, value);
    }

    boost::optional<Schedule> SetpointManagerScheduledDualSetpoint_Impl::highSetpointSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::SetpointManager_Scheduled_DualSetpointFields::HighSetpointScheduleName);
    }

    bool SetpointManagerScheduledDualSetpoint_Impl::setHighSetpointSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::SetpointManager_Scheduled_DualSetpointFields::HighSetpointScheduleName,
                                           "SetpointManagerScheduledDualSetpoint", "High Setpoint", schedule);
    }

    void SetpointManagerScheduledDualSetpoint_Impl::resetHighSetpointSchedule() {
      constexpr auto field = openstudio::SetpointManager_Scheduled_DualSetpointFields::HighSetpointScheduleName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<Schedule> SetpointManagerScheduledDualSetpoint_Impl::lowSetpointSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::SetpointManager_Scheduled_DualSetpointFields::LowSetpointScheduleName);
    }

    bool SetpointManagerScheduledDualSetpoint_Impl::setLowSetpointSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::SetpointManager_Scheduled_DualSetpointFields::LowSetpointScheduleName,
                                           "SetpointManagerScheduledDualSetpoint", "Low Setpoint", schedule);
    }

    void SetpointManagerScheduledDualSetpoint_Impl::resetLowSetpointSchedule() {
      constexpr auto field = openstudio::SetpointManager_Scheduled_DualSetpointFields::LowSetpointScheduleName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    bool SetpointManagerScheduledDualSetpoint_Impl::setSetpointNode(const openstudio::epmodel::Node& node) {
      return getObject<ModelObject>().setPointer(openstudio::SetpointManager_Scheduled_DualSetpointFields::SetpointNodeorNodeListName, node.handle());
    }

    void SetpointManagerScheduledDualSetpoint_Impl::doCanonicalize(LoadContext& context) {
      SetpointManager_Impl::doCanonicalize(context);
      canonicalizeSetpointNodeField(context, openstudio::SetpointManager_Scheduled_DualSetpointFields::SetpointNodeorNodeListName);

      bool hasControlVariable = false;
      if (auto value = getString(openstudio::SetpointManager_Scheduled_DualSetpointFields::ControlVariable, true)) {
        hasControlVariable = !value->empty();
      }

      auto owner = getObject<ModelObject>();
      if (!hasControlVariable) {
        OS_ASSERT(setString(openstudio::SetpointManager_Scheduled_DualSetpointFields::ControlVariable, "Temperature"));
        detail::addLoadInfo(context,
                            "Set default Control Variable to 'Temperature' for SetpointManager:Scheduled:DualSetpoint '" + owner.nameString() + "'.");
      }

      for (const auto field : {openstudio::SetpointManager_Scheduled_DualSetpointFields::HighSetpointScheduleName,
                               openstudio::SetpointManager_Scheduled_DualSetpointFields::LowSetpointScheduleName}) {
        const auto rawName = openstudio::detail::IdfObject_Impl::getString(field, false, true);
        if (!rawName || rawName->empty()) {
          continue;
        }

        boost::optional<Schedule> uniqueSchedule;
        bool ambiguous = false;
        for (const auto& candidate : model().getObjectsByName(*rawName, true)) {
          if (auto schedule = candidate.optionalCast<Schedule>()) {
            if (uniqueSchedule) {
              ambiguous = true;
              break;
            }
            uniqueSchedule = *schedule;
          }
        }

        if (uniqueSchedule && !ambiguous) {
          OS_ASSERT(setPointer(field, uniqueSchedule->handle(), false));
          detail::addLoadInfo(context, "Reattached schedule '" + uniqueSchedule->nameString() + "' to SetpointManager:Scheduled:DualSetpoint '"
                                         + owner.nameString() + "'.");
        } else {
          detail::addLoadWarning(context, "Preserved unresolved or ambiguous schedule reference '" + *rawName
                                            + "' on SetpointManager:Scheduled:DualSetpoint '" + owner.nameString() + "'.");
        }
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
