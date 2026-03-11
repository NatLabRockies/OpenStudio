/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerMultiZoneHeatingAverage.hpp"
#include "SetpointManager/SetpointManagerMultiZoneHeatingAverage_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SetpointManager_MultiZone_Heating_Average_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SetpointManagerMultiZoneHeatingAverage::SetpointManagerMultiZoneHeatingAverage(const Model& model)
  : SetpointManager(SetpointManagerMultiZoneHeatingAverage::iddObjectType(), model) {
  auto impl = getImpl<detail::SetpointManagerMultiZoneHeatingAverage_Impl>();
  OS_ASSERT(impl);
  OS_ASSERT(setMinimumSetpointTemperature(20.0));
  OS_ASSERT(setMaximumSetpointTemperature(50.0));
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

SetpointManagerMultiZoneHeatingAverage::SetpointManagerMultiZoneHeatingAverage(
  std::shared_ptr<detail::SetpointManagerMultiZoneHeatingAverage_Impl> impl)
  : SetpointManager(std::move(impl)) {}

IddObjectType SetpointManagerMultiZoneHeatingAverage::iddObjectType() {
  return IddObjectType::SetpointManager_MultiZone_Heating_Average;
}

std::vector<std::string> SetpointManagerMultiZoneHeatingAverage::controlVariableValues() {
  return {"Temperature"};
}

std::string SetpointManagerMultiZoneHeatingAverage::controlVariable() const {
  return "Temperature";
}

double SetpointManagerMultiZoneHeatingAverage::minimumSetpointTemperature() const {
  return getImpl<detail::SetpointManagerMultiZoneHeatingAverage_Impl>()->minimumSetpointTemperature();
}

double SetpointManagerMultiZoneHeatingAverage::maximumSetpointTemperature() const {
  return getImpl<detail::SetpointManagerMultiZoneHeatingAverage_Impl>()->maximumSetpointTemperature();
}

bool SetpointManagerMultiZoneHeatingAverage::setControlVariable(const std::string& controlVariable) {
  return openstudio::istringEqual(controlVariable, "Temperature");
}

bool SetpointManagerMultiZoneHeatingAverage::setMinimumSetpointTemperature(double minimumSetpointTemperature) {
  const bool result = getImpl<detail::SetpointManagerMultiZoneHeatingAverage_Impl>()->setMinimumSetpointTemperature(minimumSetpointTemperature);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerMultiZoneHeatingAverage::setMaximumSetpointTemperature(double maximumSetpointTemperature) {
  const bool result = getImpl<detail::SetpointManagerMultiZoneHeatingAverage_Impl>()->setMaximumSetpointTemperature(maximumSetpointTemperature);
  OS_ASSERT(result);
  return result;
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double SetpointManagerMultiZoneHeatingAverage_Impl::minimumSetpointTemperature() const {
  const auto value = getDouble(openstudio::SetpointManager_MultiZone_Heating_AverageFields::MinimumSetpointTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double SetpointManagerMultiZoneHeatingAverage_Impl::maximumSetpointTemperature() const {
  const auto value = getDouble(openstudio::SetpointManager_MultiZone_Heating_AverageFields::MaximumSetpointTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool SetpointManagerMultiZoneHeatingAverage_Impl::setMinimumSetpointTemperature(double minimumSetpointTemperature) {
  const bool result =
    setDouble(openstudio::SetpointManager_MultiZone_Heating_AverageFields::MinimumSetpointTemperature, minimumSetpointTemperature);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerMultiZoneHeatingAverage_Impl::setMaximumSetpointTemperature(double maximumSetpointTemperature) {
  const bool result =
    setDouble(openstudio::SetpointManager_MultiZone_Heating_AverageFields::MaximumSetpointTemperature, maximumSetpointTemperature);
  OS_ASSERT(result);
  return result;
}

unsigned SetpointManagerMultiZoneHeatingAverage_Impl::setpointNodeFieldIndex() const {
  return openstudio::SetpointManager_MultiZone_Heating_AverageFields::SetpointNodeorNodeListName;
}

unsigned SetpointManagerMultiZoneHeatingAverage_Impl::controlVariableFieldIndex() const {
  // E+ SetpointManager:MultiZone:Heating:Average has no explicit control variable field;
  // this placeholder index satisfies the abstract SetpointManager_Impl contract.
  return openstudio::SetpointManager_MultiZone_Heating_AverageFields::HVACAirLoopName;
}

void SetpointManagerMultiZoneHeatingAverage_Impl::doCanonicalize(LoadContext& context) {
  SetpointManager_Impl::doCanonicalize(context);

  if (auto value = getDouble(openstudio::SetpointManager_MultiZone_Heating_AverageFields::MinimumSetpointTemperature, true)) {
    (void)value;
  } else {
    OS_ASSERT(setDouble(openstudio::SetpointManager_MultiZone_Heating_AverageFields::MinimumSetpointTemperature, 20.0));
    detail::addLoadInfo(context, "Set default Minimum Setpoint Temperature to 20 for SetpointManager:MultiZone:Heating:Average '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }

  if (auto value = getDouble(openstudio::SetpointManager_MultiZone_Heating_AverageFields::MaximumSetpointTemperature, true)) {
    (void)value;
  } else {
    OS_ASSERT(setDouble(openstudio::SetpointManager_MultiZone_Heating_AverageFields::MaximumSetpointTemperature, 50.0));
    detail::addLoadInfo(context, "Set default Maximum Setpoint Temperature to 50 for SetpointManager:MultiZone:Heating:Average '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
