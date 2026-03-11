/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerWarmest.hpp"
#include "SetpointManager/SetpointManagerWarmest_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/SetpointManager_Warmest_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SetpointManagerWarmest::SetpointManagerWarmest(const Model& model) : SetpointManager(SetpointManagerWarmest::iddObjectType(), model) {
  auto impl = getImpl<detail::SetpointManagerWarmest_Impl>();
  OS_ASSERT(impl);
  OS_ASSERT(setControlVariable("Temperature"));
  OS_ASSERT(setMinimumSetpointTemperature(12.2));
  OS_ASSERT(setMaximumSetpointTemperature(15.6));
  OS_ASSERT(setStrategy("MaximumTemperature"));
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

SetpointManagerWarmest::SetpointManagerWarmest(std::shared_ptr<detail::SetpointManagerWarmest_Impl> impl) : SetpointManager(std::move(impl)) {}

IddObjectType SetpointManagerWarmest::iddObjectType() {
  return IddObjectType::SetpointManager_Warmest;
}

std::vector<std::string> SetpointManagerWarmest::controlVariableValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::SetpointManager_WarmestFields::ControlVariable);
}

std::vector<std::string> SetpointManagerWarmest::strategyValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::SetpointManager_WarmestFields::Strategy);
}

double SetpointManagerWarmest::minimumSetpointTemperature() const {
  return getImpl<detail::SetpointManagerWarmest_Impl>()->minimumSetpointTemperature();
}

double SetpointManagerWarmest::maximumSetpointTemperature() const {
  return getImpl<detail::SetpointManagerWarmest_Impl>()->maximumSetpointTemperature();
}

std::string SetpointManagerWarmest::strategy() const {
  return getImpl<detail::SetpointManagerWarmest_Impl>()->strategy();
}

bool SetpointManagerWarmest::setMinimumSetpointTemperature(double minimumSetpointTemperature) {
  const bool result = getImpl<detail::SetpointManagerWarmest_Impl>()->setMinimumSetpointTemperature(minimumSetpointTemperature);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerWarmest::setMaximumSetpointTemperature(double maximumSetpointTemperature) {
  const bool result = getImpl<detail::SetpointManagerWarmest_Impl>()->setMaximumSetpointTemperature(maximumSetpointTemperature);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerWarmest::setStrategy(const std::string& strategy) {
  return getImpl<detail::SetpointManagerWarmest_Impl>()->setStrategy(strategy);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double SetpointManagerWarmest_Impl::minimumSetpointTemperature() const {
  const auto value = getDouble(openstudio::SetpointManager_WarmestFields::MinimumSetpointTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double SetpointManagerWarmest_Impl::maximumSetpointTemperature() const {
  const auto value = getDouble(openstudio::SetpointManager_WarmestFields::MaximumSetpointTemperature, true);
  OS_ASSERT(value);
  return *value;
}

std::string SetpointManagerWarmest_Impl::strategy() const {
  const auto value = getString(openstudio::SetpointManager_WarmestFields::Strategy, true);
  OS_ASSERT(value);
  return *value;
}

bool SetpointManagerWarmest_Impl::setMinimumSetpointTemperature(double minimumSetpointTemperature) {
  const bool result = setDouble(openstudio::SetpointManager_WarmestFields::MinimumSetpointTemperature, minimumSetpointTemperature);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerWarmest_Impl::setMaximumSetpointTemperature(double maximumSetpointTemperature) {
  const bool result = setDouble(openstudio::SetpointManager_WarmestFields::MaximumSetpointTemperature, maximumSetpointTemperature);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerWarmest_Impl::setStrategy(const std::string& strategy) {
  return setString(openstudio::SetpointManager_WarmestFields::Strategy, strategy);
}

unsigned SetpointManagerWarmest_Impl::setpointNodeFieldIndex() const {
  return openstudio::SetpointManager_WarmestFields::SetpointNodeorNodeListName;
}

unsigned SetpointManagerWarmest_Impl::controlVariableFieldIndex() const {
  return openstudio::SetpointManager_WarmestFields::ControlVariable;
}

void SetpointManagerWarmest_Impl::doCanonicalize(LoadContext& context) {
  SetpointManager_Impl::doCanonicalize(context);

  if (auto value = getString(openstudio::SetpointManager_WarmestFields::ControlVariable, true)) {
    if (!value->empty()) {
      // continue
    } else {
      OS_ASSERT(setString(openstudio::SetpointManager_WarmestFields::ControlVariable, "Temperature"));
      detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:Warmest '"
                                     + getObject<ModelObject>().nameString() + "'.");
    }
  } else {
    OS_ASSERT(setString(openstudio::SetpointManager_WarmestFields::ControlVariable, "Temperature"));
    detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:Warmest '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }

  if (auto value = getDouble(openstudio::SetpointManager_WarmestFields::MinimumSetpointTemperature, true)) {
    (void)value;
  } else {
    OS_ASSERT(setDouble(openstudio::SetpointManager_WarmestFields::MinimumSetpointTemperature, 12.2));
    detail::addLoadInfo(context, "Set default Minimum Setpoint Temperature to 12.2 for SetpointManager:Warmest '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }

  if (auto value = getDouble(openstudio::SetpointManager_WarmestFields::MaximumSetpointTemperature, true)) {
    (void)value;
  } else {
    OS_ASSERT(setDouble(openstudio::SetpointManager_WarmestFields::MaximumSetpointTemperature, 15.6));
    detail::addLoadInfo(context, "Set default Maximum Setpoint Temperature to 15.6 for SetpointManager:Warmest '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }

  if (auto value = getString(openstudio::SetpointManager_WarmestFields::Strategy, true)) {
    if (!value->empty()) {
      return;
    }
  }

  OS_ASSERT(setString(openstudio::SetpointManager_WarmestFields::Strategy, "MaximumTemperature"));
  detail::addLoadInfo(context, "Set default Strategy to 'MaximumTemperature' for SetpointManager:Warmest '"
                                 + getObject<ModelObject>().nameString() + "'.");
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
