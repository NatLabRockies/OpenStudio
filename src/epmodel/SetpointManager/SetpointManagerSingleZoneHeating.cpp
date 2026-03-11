/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerSingleZoneHeating.hpp"
#include "SetpointManager/SetpointManagerSingleZoneHeating_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SetpointManager_SingleZone_Heating_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SetpointManagerSingleZoneHeating::SetpointManagerSingleZoneHeating(const Model& model)
  : SetpointManager(SetpointManagerSingleZoneHeating::iddObjectType(), model) {
  auto impl = getImpl<detail::SetpointManagerSingleZoneHeating_Impl>();
  OS_ASSERT(impl);
  OS_ASSERT(setControlVariable("Temperature"));
  OS_ASSERT(setMinimumSupplyAirTemperature(-99.0));
  OS_ASSERT(setMaximumSupplyAirTemperature(99.0));
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

SetpointManagerSingleZoneHeating::SetpointManagerSingleZoneHeating(std::shared_ptr<detail::SetpointManagerSingleZoneHeating_Impl> impl)
  : SetpointManager(std::move(impl)) {}

IddObjectType SetpointManagerSingleZoneHeating::iddObjectType() {
  return IddObjectType::SetpointManager_SingleZone_Heating;
}

double SetpointManagerSingleZoneHeating::minimumSupplyAirTemperature() const {
  return getImpl<detail::SetpointManagerSingleZoneHeating_Impl>()->minimumSupplyAirTemperature();
}

double SetpointManagerSingleZoneHeating::maximumSupplyAirTemperature() const {
  return getImpl<detail::SetpointManagerSingleZoneHeating_Impl>()->maximumSupplyAirTemperature();
}

bool SetpointManagerSingleZoneHeating::setMinimumSupplyAirTemperature(double minimumSupplyAirTemperature) {
  const bool result = getImpl<detail::SetpointManagerSingleZoneHeating_Impl>()->setMinimumSupplyAirTemperature(minimumSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerSingleZoneHeating::setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature) {
  const bool result = getImpl<detail::SetpointManagerSingleZoneHeating_Impl>()->setMaximumSupplyAirTemperature(maximumSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double SetpointManagerSingleZoneHeating_Impl::minimumSupplyAirTemperature() const {
  const auto value = getDouble(openstudio::SetpointManager_SingleZone_HeatingFields::MinimumSupplyAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double SetpointManagerSingleZoneHeating_Impl::maximumSupplyAirTemperature() const {
  const auto value = getDouble(openstudio::SetpointManager_SingleZone_HeatingFields::MaximumSupplyAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool SetpointManagerSingleZoneHeating_Impl::setMinimumSupplyAirTemperature(double minimumSupplyAirTemperature) {
  const bool result = setDouble(openstudio::SetpointManager_SingleZone_HeatingFields::MinimumSupplyAirTemperature, minimumSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerSingleZoneHeating_Impl::setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature) {
  const bool result = setDouble(openstudio::SetpointManager_SingleZone_HeatingFields::MaximumSupplyAirTemperature, maximumSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

unsigned SetpointManagerSingleZoneHeating_Impl::setpointNodeFieldIndex() const {
  return openstudio::SetpointManager_SingleZone_HeatingFields::SetpointNodeorNodeListName;
}

unsigned SetpointManagerSingleZoneHeating_Impl::controlVariableFieldIndex() const {
  return openstudio::SetpointManager_SingleZone_HeatingFields::ControlVariable;
}

void SetpointManagerSingleZoneHeating_Impl::doCanonicalize(LoadContext& context) {
  SetpointManager_Impl::doCanonicalize(context);

  if (auto value = getString(openstudio::SetpointManager_SingleZone_HeatingFields::ControlVariable, true)) {
    if (!value->empty()) {
      // continue
    } else {
      OS_ASSERT(setString(openstudio::SetpointManager_SingleZone_HeatingFields::ControlVariable, "Temperature"));
      detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:SingleZone:Heating '"
                                     + getObject<ModelObject>().nameString() + "'.");
    }
  } else {
    OS_ASSERT(setString(openstudio::SetpointManager_SingleZone_HeatingFields::ControlVariable, "Temperature"));
    detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:SingleZone:Heating '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }

  if (auto value = getDouble(openstudio::SetpointManager_SingleZone_HeatingFields::MinimumSupplyAirTemperature, true)) {
    (void)value;
  } else {
    OS_ASSERT(setDouble(openstudio::SetpointManager_SingleZone_HeatingFields::MinimumSupplyAirTemperature, -99.0));
    detail::addLoadInfo(context, "Set default Minimum Supply Air Temperature to -99 for SetpointManager:SingleZone:Heating '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }

  if (auto value = getDouble(openstudio::SetpointManager_SingleZone_HeatingFields::MaximumSupplyAirTemperature, true)) {
    (void)value;
  } else {
    OS_ASSERT(setDouble(openstudio::SetpointManager_SingleZone_HeatingFields::MaximumSupplyAirTemperature, 99.0));
    detail::addLoadInfo(context, "Set default Maximum Supply Air Temperature to 99 for SetpointManager:SingleZone:Heating '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
