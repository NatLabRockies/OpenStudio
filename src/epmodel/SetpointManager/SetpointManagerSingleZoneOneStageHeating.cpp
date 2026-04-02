/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerSingleZoneOneStageHeating.hpp"
#include "SetpointManager/SetpointManagerSingleZoneOneStageHeating_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SetpointManager_SingleZone_OneStageHeating_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SetpointManagerSingleZoneOneStageHeating::SetpointManagerSingleZoneOneStageHeating(const Model& model)
  : SetpointManager(SetpointManagerSingleZoneOneStageHeating::iddObjectType(), model) {
  auto impl = getImpl<detail::SetpointManagerSingleZoneOneStageHeating_Impl>();
  OS_ASSERT(impl);
  OS_ASSERT(setControlVariable("Temperature"));
  OS_ASSERT(setHeatingStageOnSupplyAirSetpointTemperature(99.0));
  OS_ASSERT(setHeatingStageOffSupplyAirSetpointTemperature(-99.0));
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

SetpointManagerSingleZoneOneStageHeating::SetpointManagerSingleZoneOneStageHeating(
  std::shared_ptr<detail::SetpointManagerSingleZoneOneStageHeating_Impl> impl)
  : SetpointManager(std::move(impl)) {}

IddObjectType SetpointManagerSingleZoneOneStageHeating::iddObjectType() {
  return IddObjectType::SetpointManager_SingleZone_OneStageHeating;
}

std::vector<std::string> SetpointManagerSingleZoneOneStageHeating::controlVariableValues() {
  return {"Temperature"};
}

std::string SetpointManagerSingleZoneOneStageHeating::controlVariable() const {
  return "Temperature";
}

bool SetpointManagerSingleZoneOneStageHeating::setControlVariable(const std::string& controlVariable) {
  return openstudio::istringEqual(controlVariable, "Temperature");
}

double SetpointManagerSingleZoneOneStageHeating::heatingStageOnSupplyAirSetpointTemperature() const {
  return getImpl<detail::SetpointManagerSingleZoneOneStageHeating_Impl>()->heatingStageOnSupplyAirSetpointTemperature();
}

bool SetpointManagerSingleZoneOneStageHeating::setHeatingStageOnSupplyAirSetpointTemperature(double heatingStageOnSupplyAirSetpointTemperature) {
  const bool result =
    getImpl<detail::SetpointManagerSingleZoneOneStageHeating_Impl>()->setHeatingStageOnSupplyAirSetpointTemperature(
      heatingStageOnSupplyAirSetpointTemperature);
  OS_ASSERT(result);
  return result;
}

double SetpointManagerSingleZoneOneStageHeating::heatingStageOffSupplyAirSetpointTemperature() const {
  return getImpl<detail::SetpointManagerSingleZoneOneStageHeating_Impl>()->heatingStageOffSupplyAirSetpointTemperature();
}

bool SetpointManagerSingleZoneOneStageHeating::setHeatingStageOffSupplyAirSetpointTemperature(
  double heatingStageOffSupplyAirSetpointTemperature) {
  const bool result =
    getImpl<detail::SetpointManagerSingleZoneOneStageHeating_Impl>()->setHeatingStageOffSupplyAirSetpointTemperature(
      heatingStageOffSupplyAirSetpointTemperature);
  OS_ASSERT(result);
  return result;
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double SetpointManagerSingleZoneOneStageHeating_Impl::heatingStageOnSupplyAirSetpointTemperature() const {
  const auto value = getDouble(openstudio::SetpointManager_SingleZone_OneStageHeatingFields::HeatingStageOnSupplyAirSetpointTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool SetpointManagerSingleZoneOneStageHeating_Impl::setHeatingStageOnSupplyAirSetpointTemperature(double heatingStageOnSupplyAirSetpointTemperature) {
  const bool result = setDouble(openstudio::SetpointManager_SingleZone_OneStageHeatingFields::HeatingStageOnSupplyAirSetpointTemperature,
                                heatingStageOnSupplyAirSetpointTemperature);
  OS_ASSERT(result);
  return result;
}

double SetpointManagerSingleZoneOneStageHeating_Impl::heatingStageOffSupplyAirSetpointTemperature() const {
  const auto value = getDouble(openstudio::SetpointManager_SingleZone_OneStageHeatingFields::HeatingStageOffSupplyAirSetpointTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool SetpointManagerSingleZoneOneStageHeating_Impl::setHeatingStageOffSupplyAirSetpointTemperature(
  double heatingStageOffSupplyAirSetpointTemperature) {
  const bool result = setDouble(openstudio::SetpointManager_SingleZone_OneStageHeatingFields::HeatingStageOffSupplyAirSetpointTemperature,
                                heatingStageOffSupplyAirSetpointTemperature);
  OS_ASSERT(result);
  return result;
}

boost::optional<openstudio::epmodel::Node> SetpointManagerSingleZoneOneStageHeating_Impl::setpointNode() const {
  return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Node>(
    openstudio::SetpointManager_SingleZone_OneStageHeatingFields::SetpointNodeorNodeListName);
}

std::string SetpointManagerSingleZoneOneStageHeating_Impl::controlVariable() const {
  return "Temperature";
}

bool SetpointManagerSingleZoneOneStageHeating_Impl::setControlVariable(const std::string& value) {
  return openstudio::istringEqual(value, "Temperature");
}

bool SetpointManagerSingleZoneOneStageHeating_Impl::setSetpointNode(const openstudio::epmodel::Node& node) {
  return getObject<ModelObject>().setPointer(openstudio::SetpointManager_SingleZone_OneStageHeatingFields::SetpointNodeorNodeListName,
                                             node.handle());
}

void SetpointManagerSingleZoneOneStageHeating_Impl::doCanonicalize(LoadContext& context) {
  SetpointManager_Impl::doCanonicalize(context);
  canonicalizeSetpointNodeField(context, openstudio::SetpointManager_SingleZone_OneStageHeatingFields::SetpointNodeorNodeListName);

  if (auto value = getDouble(openstudio::SetpointManager_SingleZone_OneStageHeatingFields::HeatingStageOnSupplyAirSetpointTemperature, true)) {
    (void)value;
  } else {
    OS_ASSERT(setDouble(openstudio::SetpointManager_SingleZone_OneStageHeatingFields::HeatingStageOnSupplyAirSetpointTemperature, 99.0));
    detail::addLoadInfo(
      context, "Set default Heating Stage On Supply Air Setpoint Temperature to 99 for SetpointManager:SingleZone:OneStageHeating '"
                 + getObject<ModelObject>().nameString() + "'.");
  }

  if (auto value = getDouble(openstudio::SetpointManager_SingleZone_OneStageHeatingFields::HeatingStageOffSupplyAirSetpointTemperature, true)) {
    (void)value;
  } else {
    OS_ASSERT(setDouble(openstudio::SetpointManager_SingleZone_OneStageHeatingFields::HeatingStageOffSupplyAirSetpointTemperature, -99.0));
    detail::addLoadInfo(
      context, "Set default Heating Stage Off Supply Air Setpoint Temperature to -99 for SetpointManager:SingleZone:OneStageHeating '"
                 + getObject<ModelObject>().nameString() + "'.");
  }
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
