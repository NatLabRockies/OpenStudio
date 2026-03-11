/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerWarmestTemperatureFlow.hpp"
#include "SetpointManager/SetpointManagerWarmestTemperatureFlow_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/SetpointManager_WarmestTemperatureFlow_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SetpointManagerWarmestTemperatureFlow::SetpointManagerWarmestTemperatureFlow(const Model& model)
  : SetpointManager(SetpointManagerWarmestTemperatureFlow::iddObjectType(), model) {
  auto impl = getImpl<detail::SetpointManagerWarmestTemperatureFlow_Impl>();
  OS_ASSERT(impl);
  OS_ASSERT(setControlVariable("Temperature"));
  OS_ASSERT(setMinimumSetpointTemperature(12.0));
  OS_ASSERT(setMaximumSetpointTemperature(18.0));
  OS_ASSERT(setStrategy("TemperatureFirst"));
  OS_ASSERT(setMinimumTurndownRatio(0.2));
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

SetpointManagerWarmestTemperatureFlow::SetpointManagerWarmestTemperatureFlow(
  std::shared_ptr<detail::SetpointManagerWarmestTemperatureFlow_Impl> impl)
  : SetpointManager(std::move(impl)) {}

IddObjectType SetpointManagerWarmestTemperatureFlow::iddObjectType() {
  return IddObjectType::SetpointManager_WarmestTemperatureFlow;
}

std::vector<std::string> SetpointManagerWarmestTemperatureFlow::controlVariableValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::SetpointManager_WarmestTemperatureFlowFields::ControlVariable);
}

std::vector<std::string> SetpointManagerWarmestTemperatureFlow::strategyValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::SetpointManager_WarmestTemperatureFlowFields::Strategy);
}

double SetpointManagerWarmestTemperatureFlow::minimumSetpointTemperature() const {
  return getImpl<detail::SetpointManagerWarmestTemperatureFlow_Impl>()->minimumSetpointTemperature();
}

double SetpointManagerWarmestTemperatureFlow::maximumSetpointTemperature() const {
  return getImpl<detail::SetpointManagerWarmestTemperatureFlow_Impl>()->maximumSetpointTemperature();
}

std::string SetpointManagerWarmestTemperatureFlow::strategy() const {
  return getImpl<detail::SetpointManagerWarmestTemperatureFlow_Impl>()->strategy();
}

double SetpointManagerWarmestTemperatureFlow::minimumTurndownRatio() const {
  return getImpl<detail::SetpointManagerWarmestTemperatureFlow_Impl>()->minimumTurndownRatio();
}

bool SetpointManagerWarmestTemperatureFlow::setMinimumSetpointTemperature(double minimumSetpointTemperature) {
  const bool result = getImpl<detail::SetpointManagerWarmestTemperatureFlow_Impl>()->setMinimumSetpointTemperature(minimumSetpointTemperature);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerWarmestTemperatureFlow::setMaximumSetpointTemperature(double maximumSetpointTemperature) {
  const bool result = getImpl<detail::SetpointManagerWarmestTemperatureFlow_Impl>()->setMaximumSetpointTemperature(maximumSetpointTemperature);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerWarmestTemperatureFlow::setStrategy(const std::string& strategy) {
  return getImpl<detail::SetpointManagerWarmestTemperatureFlow_Impl>()->setStrategy(strategy);
}

bool SetpointManagerWarmestTemperatureFlow::setMinimumTurndownRatio(double minimumTurndownRatio) {
  const bool result = getImpl<detail::SetpointManagerWarmestTemperatureFlow_Impl>()->setMinimumTurndownRatio(minimumTurndownRatio);
  OS_ASSERT(result);
  return result;
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double SetpointManagerWarmestTemperatureFlow_Impl::minimumSetpointTemperature() const {
  const auto value = getDouble(openstudio::SetpointManager_WarmestTemperatureFlowFields::MinimumSetpointTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double SetpointManagerWarmestTemperatureFlow_Impl::maximumSetpointTemperature() const {
  const auto value = getDouble(openstudio::SetpointManager_WarmestTemperatureFlowFields::MaximumSetpointTemperature, true);
  OS_ASSERT(value);
  return *value;
}

std::string SetpointManagerWarmestTemperatureFlow_Impl::strategy() const {
  const auto value = getString(openstudio::SetpointManager_WarmestTemperatureFlowFields::Strategy, true);
  OS_ASSERT(value);
  return *value;
}

double SetpointManagerWarmestTemperatureFlow_Impl::minimumTurndownRatio() const {
  const auto value = getDouble(openstudio::SetpointManager_WarmestTemperatureFlowFields::MinimumTurndownRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool SetpointManagerWarmestTemperatureFlow_Impl::setMinimumSetpointTemperature(double minimumSetpointTemperature) {
  const bool result = setDouble(openstudio::SetpointManager_WarmestTemperatureFlowFields::MinimumSetpointTemperature, minimumSetpointTemperature);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerWarmestTemperatureFlow_Impl::setMaximumSetpointTemperature(double maximumSetpointTemperature) {
  const bool result = setDouble(openstudio::SetpointManager_WarmestTemperatureFlowFields::MaximumSetpointTemperature, maximumSetpointTemperature);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerWarmestTemperatureFlow_Impl::setStrategy(const std::string& strategy) {
  return setString(openstudio::SetpointManager_WarmestTemperatureFlowFields::Strategy, strategy);
}

bool SetpointManagerWarmestTemperatureFlow_Impl::setMinimumTurndownRatio(double minimumTurndownRatio) {
  const bool result = setDouble(openstudio::SetpointManager_WarmestTemperatureFlowFields::MinimumTurndownRatio, minimumTurndownRatio);
  OS_ASSERT(result);
  return result;
}

unsigned SetpointManagerWarmestTemperatureFlow_Impl::setpointNodeFieldIndex() const {
  return openstudio::SetpointManager_WarmestTemperatureFlowFields::SetpointNodeorNodeListName;
}

unsigned SetpointManagerWarmestTemperatureFlow_Impl::controlVariableFieldIndex() const {
  return openstudio::SetpointManager_WarmestTemperatureFlowFields::ControlVariable;
}

void SetpointManagerWarmestTemperatureFlow_Impl::doCanonicalize(LoadContext& context) {
  SetpointManager_Impl::doCanonicalize(context);

  if (auto value = getString(openstudio::SetpointManager_WarmestTemperatureFlowFields::ControlVariable, true)) {
    if (!value->empty()) {
      // continue
    } else {
      OS_ASSERT(setString(openstudio::SetpointManager_WarmestTemperatureFlowFields::ControlVariable, "Temperature"));
      detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:WarmestTemperatureFlow '"
                                     + getObject<ModelObject>().nameString() + "'.");
    }
  } else {
    OS_ASSERT(setString(openstudio::SetpointManager_WarmestTemperatureFlowFields::ControlVariable, "Temperature"));
    detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:WarmestTemperatureFlow '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }

  if (auto value = getDouble(openstudio::SetpointManager_WarmestTemperatureFlowFields::MinimumSetpointTemperature, true)) {
    (void)value;
  } else {
    OS_ASSERT(setDouble(openstudio::SetpointManager_WarmestTemperatureFlowFields::MinimumSetpointTemperature, 12.0));
    detail::addLoadInfo(context, "Set default Minimum Setpoint Temperature to 12 for SetpointManager:WarmestTemperatureFlow '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }

  if (auto value = getDouble(openstudio::SetpointManager_WarmestTemperatureFlowFields::MaximumSetpointTemperature, true)) {
    (void)value;
  } else {
    OS_ASSERT(setDouble(openstudio::SetpointManager_WarmestTemperatureFlowFields::MaximumSetpointTemperature, 18.0));
    detail::addLoadInfo(context, "Set default Maximum Setpoint Temperature to 18 for SetpointManager:WarmestTemperatureFlow '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }

  if (auto value = getString(openstudio::SetpointManager_WarmestTemperatureFlowFields::Strategy, true)) {
    if (!value->empty()) {
      // continue
    } else {
      OS_ASSERT(setString(openstudio::SetpointManager_WarmestTemperatureFlowFields::Strategy, "TemperatureFirst"));
      detail::addLoadInfo(context, "Set default Strategy to 'TemperatureFirst' for SetpointManager:WarmestTemperatureFlow '"
                                     + getObject<ModelObject>().nameString() + "'.");
    }
  } else {
    OS_ASSERT(setString(openstudio::SetpointManager_WarmestTemperatureFlowFields::Strategy, "TemperatureFirst"));
    detail::addLoadInfo(context, "Set default Strategy to 'TemperatureFirst' for SetpointManager:WarmestTemperatureFlow '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }

  if (auto value = getDouble(openstudio::SetpointManager_WarmestTemperatureFlowFields::MinimumTurndownRatio, true)) {
    (void)value;
  } else {
    OS_ASSERT(setDouble(openstudio::SetpointManager_WarmestTemperatureFlowFields::MinimumTurndownRatio, 0.2));
    detail::addLoadInfo(context, "Set default Minimum Turndown Ratio to 0.2 for SetpointManager:WarmestTemperatureFlow '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
