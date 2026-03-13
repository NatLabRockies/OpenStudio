/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerSystemNodeResetHumidity.hpp"
#include "SetpointManager/SetpointManagerSystemNodeResetHumidity_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/SetpointManager_SystemNodeReset_Humidity_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SetpointManagerSystemNodeResetHumidity::SetpointManagerSystemNodeResetHumidity(const Model& model)
    : SetpointManager(SetpointManagerSystemNodeResetHumidity::iddObjectType(), model) {
    auto impl = getImpl<detail::SetpointManagerSystemNodeResetHumidity_Impl>();
    OS_ASSERT(impl);
    OS_ASSERT(setControlVariable("MaximumHumidityRatio"));
    OS_ASSERT(setSetpointatLowReferenceHumidityRatio(0.00924));
    OS_ASSERT(setSetpointatHighReferenceHumidityRatio(0.00600));
    OS_ASSERT(setLowReferenceHumidityRatio(0.00850));
    OS_ASSERT(setHighReferenceHumidityRatio(0.01000));
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  SetpointManagerSystemNodeResetHumidity::SetpointManagerSystemNodeResetHumidity(
    std::shared_ptr<detail::SetpointManagerSystemNodeResetHumidity_Impl> impl)
    : SetpointManager(std::move(impl)) {}

  IddObjectType SetpointManagerSystemNodeResetHumidity::iddObjectType() {
    return IddObjectType::SetpointManager_SystemNodeReset_Humidity;
  }

  std::vector<std::string> SetpointManagerSystemNodeResetHumidity::controlVariableValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SetpointManager_SystemNodeReset_HumidityFields::ControlVariable);
  }

  double SetpointManagerSystemNodeResetHumidity::setpointatLowReferenceHumidityRatio() const {
    return getImpl<detail::SetpointManagerSystemNodeResetHumidity_Impl>()->setpointatLowReferenceHumidityRatio();
  }

  bool SetpointManagerSystemNodeResetHumidity::setSetpointatLowReferenceHumidityRatio(double setpointatLowReferenceHumidityRatio) {
    const bool result =
      getImpl<detail::SetpointManagerSystemNodeResetHumidity_Impl>()->setSetpointatLowReferenceHumidityRatio(setpointatLowReferenceHumidityRatio);
    OS_ASSERT(result);
    return result;
  }

  double SetpointManagerSystemNodeResetHumidity::setpointatHighReferenceHumidityRatio() const {
    return getImpl<detail::SetpointManagerSystemNodeResetHumidity_Impl>()->setpointatHighReferenceHumidityRatio();
  }

  bool SetpointManagerSystemNodeResetHumidity::setSetpointatHighReferenceHumidityRatio(double setpointatHighReferenceHumidityRatio) {
    const bool result =
      getImpl<detail::SetpointManagerSystemNodeResetHumidity_Impl>()->setSetpointatHighReferenceHumidityRatio(setpointatHighReferenceHumidityRatio);
    OS_ASSERT(result);
    return result;
  }

  double SetpointManagerSystemNodeResetHumidity::lowReferenceHumidityRatio() const {
    return getImpl<detail::SetpointManagerSystemNodeResetHumidity_Impl>()->lowReferenceHumidityRatio();
  }

  bool SetpointManagerSystemNodeResetHumidity::setLowReferenceHumidityRatio(double lowReferenceHumidityRatio) {
    const bool result = getImpl<detail::SetpointManagerSystemNodeResetHumidity_Impl>()->setLowReferenceHumidityRatio(lowReferenceHumidityRatio);
    OS_ASSERT(result);
    return result;
  }

  double SetpointManagerSystemNodeResetHumidity::highReferenceHumidityRatio() const {
    return getImpl<detail::SetpointManagerSystemNodeResetHumidity_Impl>()->highReferenceHumidityRatio();
  }

  bool SetpointManagerSystemNodeResetHumidity::setHighReferenceHumidityRatio(double highReferenceHumidityRatio) {
    const bool result = getImpl<detail::SetpointManagerSystemNodeResetHumidity_Impl>()->setHighReferenceHumidityRatio(highReferenceHumidityRatio);
    OS_ASSERT(result);
    return result;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double SetpointManagerSystemNodeResetHumidity_Impl::setpointatLowReferenceHumidityRatio() const {
      const auto value = getDouble(openstudio::SetpointManager_SystemNodeReset_HumidityFields::SetpointatLowReferenceHumidityRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerSystemNodeResetHumidity_Impl::setSetpointatLowReferenceHumidityRatio(double setpointatLowReferenceHumidityRatio) {
      const bool result = setDouble(openstudio::SetpointManager_SystemNodeReset_HumidityFields::SetpointatLowReferenceHumidityRatio,
                                    setpointatLowReferenceHumidityRatio);
      OS_ASSERT(result);
      return result;
    }

    double SetpointManagerSystemNodeResetHumidity_Impl::setpointatHighReferenceHumidityRatio() const {
      const auto value = getDouble(openstudio::SetpointManager_SystemNodeReset_HumidityFields::SetpointatHighReferenceHumidityRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerSystemNodeResetHumidity_Impl::setSetpointatHighReferenceHumidityRatio(double setpointatHighReferenceHumidityRatio) {
      const bool result = setDouble(openstudio::SetpointManager_SystemNodeReset_HumidityFields::SetpointatHighReferenceHumidityRatio,
                                    setpointatHighReferenceHumidityRatio);
      OS_ASSERT(result);
      return result;
    }

    double SetpointManagerSystemNodeResetHumidity_Impl::lowReferenceHumidityRatio() const {
      const auto value = getDouble(openstudio::SetpointManager_SystemNodeReset_HumidityFields::LowReferenceHumidityRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerSystemNodeResetHumidity_Impl::setLowReferenceHumidityRatio(double lowReferenceHumidityRatio) {
      const bool result = setDouble(openstudio::SetpointManager_SystemNodeReset_HumidityFields::LowReferenceHumidityRatio, lowReferenceHumidityRatio);
      OS_ASSERT(result);
      return result;
    }

    double SetpointManagerSystemNodeResetHumidity_Impl::highReferenceHumidityRatio() const {
      const auto value = getDouble(openstudio::SetpointManager_SystemNodeReset_HumidityFields::HighReferenceHumidityRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerSystemNodeResetHumidity_Impl::setHighReferenceHumidityRatio(double highReferenceHumidityRatio) {
      const bool result =
        setDouble(openstudio::SetpointManager_SystemNodeReset_HumidityFields::HighReferenceHumidityRatio, highReferenceHumidityRatio);
      OS_ASSERT(result);
      return result;
    }

    unsigned SetpointManagerSystemNodeResetHumidity_Impl::setpointNodeFieldIndex() const {
      return openstudio::SetpointManager_SystemNodeReset_HumidityFields::SetpointNodeorNodeListName;
    }

    unsigned SetpointManagerSystemNodeResetHumidity_Impl::controlVariableFieldIndex() const {
      return openstudio::SetpointManager_SystemNodeReset_HumidityFields::ControlVariable;
    }

    void SetpointManagerSystemNodeResetHumidity_Impl::doCanonicalize(LoadContext& context) {
      SetpointManager_Impl::doCanonicalize(context);

      if (auto value = getString(openstudio::SetpointManager_SystemNodeReset_HumidityFields::ControlVariable, true)) {
        if (!value->empty()) {
          // continue
        } else {
          OS_ASSERT(setString(openstudio::SetpointManager_SystemNodeReset_HumidityFields::ControlVariable, "MaximumHumidityRatio"));
          detail::addLoadInfo(context, "Set default Control Variable to 'MaximumHumidityRatio' for SetpointManager:SystemNodeReset:Humidity '"
                                         + getObject<ModelObject>().nameString() + "'.");
        }
      } else {
        OS_ASSERT(setString(openstudio::SetpointManager_SystemNodeReset_HumidityFields::ControlVariable, "MaximumHumidityRatio"));
        detail::addLoadInfo(context, "Set default Control Variable to 'MaximumHumidityRatio' for SetpointManager:SystemNodeReset:Humidity '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }

      if (auto value = getDouble(openstudio::SetpointManager_SystemNodeReset_HumidityFields::SetpointatLowReferenceHumidityRatio, true)) {
        (void)value;
      } else {
        OS_ASSERT(setDouble(openstudio::SetpointManager_SystemNodeReset_HumidityFields::SetpointatLowReferenceHumidityRatio, 0.00924));
        detail::addLoadInfo(context, "Set default Setpoint at Low Reference Humidity Ratio to 0.00924 for SetpointManager:SystemNodeReset:Humidity '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }

      if (auto value = getDouble(openstudio::SetpointManager_SystemNodeReset_HumidityFields::SetpointatHighReferenceHumidityRatio, true)) {
        (void)value;
      } else {
        OS_ASSERT(setDouble(openstudio::SetpointManager_SystemNodeReset_HumidityFields::SetpointatHighReferenceHumidityRatio, 0.00600));
        detail::addLoadInfo(context, "Set default Setpoint at High Reference Humidity Ratio to 0.006 for SetpointManager:SystemNodeReset:Humidity '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }

      if (auto value = getDouble(openstudio::SetpointManager_SystemNodeReset_HumidityFields::LowReferenceHumidityRatio, true)) {
        (void)value;
      } else {
        OS_ASSERT(setDouble(openstudio::SetpointManager_SystemNodeReset_HumidityFields::LowReferenceHumidityRatio, 0.00850));
        detail::addLoadInfo(context, "Set default Low Reference Humidity Ratio to 0.0085 for SetpointManager:SystemNodeReset:Humidity '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }

      if (auto value = getDouble(openstudio::SetpointManager_SystemNodeReset_HumidityFields::HighReferenceHumidityRatio, true)) {
        (void)value;
      } else {
        OS_ASSERT(setDouble(openstudio::SetpointManager_SystemNodeReset_HumidityFields::HighReferenceHumidityRatio, 0.01000));
        detail::addLoadInfo(context, "Set default High Reference Humidity Ratio to 0.01 for SetpointManager:SystemNodeReset:Humidity '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
