/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerOutdoorAirReset.hpp"
#include "SetpointManager/SetpointManagerOutdoorAirReset_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/SetpointManager_OutdoorAirReset_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SetpointManagerOutdoorAirReset::SetpointManagerOutdoorAirReset(const Model& model)
  : SetpointManager(SetpointManagerOutdoorAirReset::iddObjectType(), model) {
  auto impl = getImpl<detail::SetpointManagerOutdoorAirReset_Impl>();
  OS_ASSERT(impl);
  OS_ASSERT(setControlVariable("Temperature"));
  OS_ASSERT(setSetpointatOutdoorLowTemperature(22.0));
  OS_ASSERT(setOutdoorLowTemperature(10.0));
  OS_ASSERT(setSetpointatOutdoorHighTemperature(10.0));
  OS_ASSERT(setOutdoorHighTemperature(24.0));
  resetSetpointatOutdoorLowTemperature2();
  resetOutdoorLowTemperature2();
  resetSetpointatOutdoorHighTemperature2();
  resetOutdoorHighTemperature2();
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

SetpointManagerOutdoorAirReset::SetpointManagerOutdoorAirReset(std::shared_ptr<detail::SetpointManagerOutdoorAirReset_Impl> impl)
  : SetpointManager(std::move(impl)) {}

IddObjectType SetpointManagerOutdoorAirReset::iddObjectType() {
  return IddObjectType::SetpointManager_OutdoorAirReset;
}

std::vector<std::string> SetpointManagerOutdoorAirReset::controlVariableValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::SetpointManager_OutdoorAirResetFields::ControlVariable);
}

bool SetpointManagerOutdoorAirReset::isControlVariableDefaulted() const {
  return getImpl<detail::SetpointManagerOutdoorAirReset_Impl>()->isControlVariableDefaulted();
}

double SetpointManagerOutdoorAirReset::setpointatOutdoorLowTemperature() const {
  return getImpl<detail::SetpointManagerOutdoorAirReset_Impl>()->setpointatOutdoorLowTemperature();
}

double SetpointManagerOutdoorAirReset::outdoorLowTemperature() const {
  return getImpl<detail::SetpointManagerOutdoorAirReset_Impl>()->outdoorLowTemperature();
}

double SetpointManagerOutdoorAirReset::setpointatOutdoorHighTemperature() const {
  return getImpl<detail::SetpointManagerOutdoorAirReset_Impl>()->setpointatOutdoorHighTemperature();
}

double SetpointManagerOutdoorAirReset::outdoorHighTemperature() const {
  return getImpl<detail::SetpointManagerOutdoorAirReset_Impl>()->outdoorHighTemperature();
}

boost::optional<double> SetpointManagerOutdoorAirReset::setpointatOutdoorLowTemperature2() const {
  return getImpl<detail::SetpointManagerOutdoorAirReset_Impl>()->setpointatOutdoorLowTemperature2();
}

boost::optional<double> SetpointManagerOutdoorAirReset::outdoorLowTemperature2() const {
  return getImpl<detail::SetpointManagerOutdoorAirReset_Impl>()->outdoorLowTemperature2();
}

boost::optional<double> SetpointManagerOutdoorAirReset::setpointatOutdoorHighTemperature2() const {
  return getImpl<detail::SetpointManagerOutdoorAirReset_Impl>()->setpointatOutdoorHighTemperature2();
}

boost::optional<double> SetpointManagerOutdoorAirReset::outdoorHighTemperature2() const {
  return getImpl<detail::SetpointManagerOutdoorAirReset_Impl>()->outdoorHighTemperature2();
}

void SetpointManagerOutdoorAirReset::resetControlVariable() {
  getImpl<detail::SetpointManagerOutdoorAirReset_Impl>()->resetControlVariable();
}

bool SetpointManagerOutdoorAirReset::setSetpointatOutdoorLowTemperature(double setpointatOutdoorLowTemperature) {
  const bool result = getImpl<detail::SetpointManagerOutdoorAirReset_Impl>()->setSetpointatOutdoorLowTemperature(setpointatOutdoorLowTemperature);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerOutdoorAirReset::setOutdoorLowTemperature(double outdoorLowTemperature) {
  const bool result = getImpl<detail::SetpointManagerOutdoorAirReset_Impl>()->setOutdoorLowTemperature(outdoorLowTemperature);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerOutdoorAirReset::setSetpointatOutdoorHighTemperature(double setpointatOutdoorHighTemperature) {
  const bool result =
    getImpl<detail::SetpointManagerOutdoorAirReset_Impl>()->setSetpointatOutdoorHighTemperature(setpointatOutdoorHighTemperature);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerOutdoorAirReset::setOutdoorHighTemperature(double outdoorHighTemperature) {
  const bool result = getImpl<detail::SetpointManagerOutdoorAirReset_Impl>()->setOutdoorHighTemperature(outdoorHighTemperature);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerOutdoorAirReset::setSetpointatOutdoorLowTemperature2(double setpointatOutdoorLowTemperature2) {
  const bool result =
    getImpl<detail::SetpointManagerOutdoorAirReset_Impl>()->setSetpointatOutdoorLowTemperature2(setpointatOutdoorLowTemperature2);
  OS_ASSERT(result);
  return result;
}

void SetpointManagerOutdoorAirReset::resetSetpointatOutdoorLowTemperature2() {
  getImpl<detail::SetpointManagerOutdoorAirReset_Impl>()->resetSetpointatOutdoorLowTemperature2();
}

bool SetpointManagerOutdoorAirReset::setOutdoorLowTemperature2(double outdoorLowTemperature2) {
  const bool result = getImpl<detail::SetpointManagerOutdoorAirReset_Impl>()->setOutdoorLowTemperature2(outdoorLowTemperature2);
  OS_ASSERT(result);
  return result;
}

void SetpointManagerOutdoorAirReset::resetOutdoorLowTemperature2() {
  getImpl<detail::SetpointManagerOutdoorAirReset_Impl>()->resetOutdoorLowTemperature2();
}

bool SetpointManagerOutdoorAirReset::setSetpointatOutdoorHighTemperature2(double setpointatOutdoorHighTemperature2) {
  const bool result =
    getImpl<detail::SetpointManagerOutdoorAirReset_Impl>()->setSetpointatOutdoorHighTemperature2(setpointatOutdoorHighTemperature2);
  OS_ASSERT(result);
  return result;
}

void SetpointManagerOutdoorAirReset::resetSetpointatOutdoorHighTemperature2() {
  getImpl<detail::SetpointManagerOutdoorAirReset_Impl>()->resetSetpointatOutdoorHighTemperature2();
}

bool SetpointManagerOutdoorAirReset::setOutdoorHighTemperature2(double outdoorHighTemperature2) {
  const bool result = getImpl<detail::SetpointManagerOutdoorAirReset_Impl>()->setOutdoorHighTemperature2(outdoorHighTemperature2);
  OS_ASSERT(result);
  return result;
}

void SetpointManagerOutdoorAirReset::resetOutdoorHighTemperature2() {
  getImpl<detail::SetpointManagerOutdoorAirReset_Impl>()->resetOutdoorHighTemperature2();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

bool SetpointManagerOutdoorAirReset_Impl::isControlVariableDefaulted() const {
  return isEmpty(openstudio::SetpointManager_OutdoorAirResetFields::ControlVariable);
}

double SetpointManagerOutdoorAirReset_Impl::setpointatOutdoorLowTemperature() const {
  const auto value = getDouble(openstudio::SetpointManager_OutdoorAirResetFields::SetpointatOutdoorLowTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double SetpointManagerOutdoorAirReset_Impl::outdoorLowTemperature() const {
  const auto value = getDouble(openstudio::SetpointManager_OutdoorAirResetFields::OutdoorLowTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double SetpointManagerOutdoorAirReset_Impl::setpointatOutdoorHighTemperature() const {
  const auto value = getDouble(openstudio::SetpointManager_OutdoorAirResetFields::SetpointatOutdoorHighTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double SetpointManagerOutdoorAirReset_Impl::outdoorHighTemperature() const {
  const auto value = getDouble(openstudio::SetpointManager_OutdoorAirResetFields::OutdoorHighTemperature, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> SetpointManagerOutdoorAirReset_Impl::setpointatOutdoorLowTemperature2() const {
  return getDouble(openstudio::SetpointManager_OutdoorAirResetFields::SetpointatOutdoorLowTemperature2, true);
}

boost::optional<double> SetpointManagerOutdoorAirReset_Impl::outdoorLowTemperature2() const {
  return getDouble(openstudio::SetpointManager_OutdoorAirResetFields::OutdoorLowTemperature2, true);
}

boost::optional<double> SetpointManagerOutdoorAirReset_Impl::setpointatOutdoorHighTemperature2() const {
  return getDouble(openstudio::SetpointManager_OutdoorAirResetFields::SetpointatOutdoorHighTemperature2, true);
}

boost::optional<double> SetpointManagerOutdoorAirReset_Impl::outdoorHighTemperature2() const {
  return getDouble(openstudio::SetpointManager_OutdoorAirResetFields::OutdoorHighTemperature2, true);
}

void SetpointManagerOutdoorAirReset_Impl::resetControlVariable() {
  OS_ASSERT(setString(openstudio::SetpointManager_OutdoorAirResetFields::ControlVariable, ""));
}

bool SetpointManagerOutdoorAirReset_Impl::setSetpointatOutdoorLowTemperature(double setpointatOutdoorLowTemperature) {
  const bool result = setDouble(openstudio::SetpointManager_OutdoorAirResetFields::SetpointatOutdoorLowTemperature, setpointatOutdoorLowTemperature);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerOutdoorAirReset_Impl::setOutdoorLowTemperature(double outdoorLowTemperature) {
  const bool result = setDouble(openstudio::SetpointManager_OutdoorAirResetFields::OutdoorLowTemperature, outdoorLowTemperature);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerOutdoorAirReset_Impl::setSetpointatOutdoorHighTemperature(double setpointatOutdoorHighTemperature) {
  const bool result =
    setDouble(openstudio::SetpointManager_OutdoorAirResetFields::SetpointatOutdoorHighTemperature, setpointatOutdoorHighTemperature);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerOutdoorAirReset_Impl::setOutdoorHighTemperature(double outdoorHighTemperature) {
  const bool result = setDouble(openstudio::SetpointManager_OutdoorAirResetFields::OutdoorHighTemperature, outdoorHighTemperature);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerOutdoorAirReset_Impl::setSetpointatOutdoorLowTemperature2(boost::optional<double> setpointatOutdoorLowTemperature2) {
  bool result = false;
  if (setpointatOutdoorLowTemperature2) {
    result = setDouble(openstudio::SetpointManager_OutdoorAirResetFields::SetpointatOutdoorLowTemperature2, *setpointatOutdoorLowTemperature2);
  } else {
    resetSetpointatOutdoorLowTemperature2();
    result = true;
  }
  OS_ASSERT(result);
  return result;
}

void SetpointManagerOutdoorAirReset_Impl::resetSetpointatOutdoorLowTemperature2() {
  OS_ASSERT(setString(openstudio::SetpointManager_OutdoorAirResetFields::SetpointatOutdoorLowTemperature2, ""));
}

bool SetpointManagerOutdoorAirReset_Impl::setOutdoorLowTemperature2(boost::optional<double> outdoorLowTemperature2) {
  bool result = false;
  if (outdoorLowTemperature2) {
    result = setDouble(openstudio::SetpointManager_OutdoorAirResetFields::OutdoorLowTemperature2, *outdoorLowTemperature2);
  } else {
    resetOutdoorLowTemperature2();
    result = true;
  }
  OS_ASSERT(result);
  return result;
}

void SetpointManagerOutdoorAirReset_Impl::resetOutdoorLowTemperature2() {
  OS_ASSERT(setString(openstudio::SetpointManager_OutdoorAirResetFields::OutdoorLowTemperature2, ""));
}

bool SetpointManagerOutdoorAirReset_Impl::setSetpointatOutdoorHighTemperature2(boost::optional<double> setpointatOutdoorHighTemperature2) {
  bool result = false;
  if (setpointatOutdoorHighTemperature2) {
    result = setDouble(openstudio::SetpointManager_OutdoorAirResetFields::SetpointatOutdoorHighTemperature2, *setpointatOutdoorHighTemperature2);
  } else {
    resetSetpointatOutdoorHighTemperature2();
    result = true;
  }
  OS_ASSERT(result);
  return result;
}

void SetpointManagerOutdoorAirReset_Impl::resetSetpointatOutdoorHighTemperature2() {
  OS_ASSERT(setString(openstudio::SetpointManager_OutdoorAirResetFields::SetpointatOutdoorHighTemperature2, ""));
}

bool SetpointManagerOutdoorAirReset_Impl::setOutdoorHighTemperature2(boost::optional<double> outdoorHighTemperature2) {
  bool result = false;
  if (outdoorHighTemperature2) {
    result = setDouble(openstudio::SetpointManager_OutdoorAirResetFields::OutdoorHighTemperature2, *outdoorHighTemperature2);
  } else {
    resetOutdoorHighTemperature2();
    result = true;
  }
  OS_ASSERT(result);
  return result;
}

void SetpointManagerOutdoorAirReset_Impl::resetOutdoorHighTemperature2() {
  OS_ASSERT(setString(openstudio::SetpointManager_OutdoorAirResetFields::OutdoorHighTemperature2, ""));
}

unsigned SetpointManagerOutdoorAirReset_Impl::setpointNodeFieldIndex() const {
  return openstudio::SetpointManager_OutdoorAirResetFields::SetpointNodeorNodeListName;
}

unsigned SetpointManagerOutdoorAirReset_Impl::controlVariableFieldIndex() const {
  return openstudio::SetpointManager_OutdoorAirResetFields::ControlVariable;
}

void SetpointManagerOutdoorAirReset_Impl::doCanonicalize(LoadContext& context) {
  SetpointManager_Impl::doCanonicalize(context);

  if (auto value = getString(openstudio::SetpointManager_OutdoorAirResetFields::ControlVariable, true)) {
    if (!value->empty()) {
      // continue
    } else {
      OS_ASSERT(setString(openstudio::SetpointManager_OutdoorAirResetFields::ControlVariable, "Temperature"));
      detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:OutdoorAirReset '"
                                     + getObject<ModelObject>().nameString() + "'.");
    }
  } else {
    OS_ASSERT(setString(openstudio::SetpointManager_OutdoorAirResetFields::ControlVariable, "Temperature"));
    detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:OutdoorAirReset '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }

  if (auto value = getDouble(openstudio::SetpointManager_OutdoorAirResetFields::SetpointatOutdoorLowTemperature, true)) {
    (void)value;
  } else {
    OS_ASSERT(setDouble(openstudio::SetpointManager_OutdoorAirResetFields::SetpointatOutdoorLowTemperature, 22.0));
    detail::addLoadInfo(context, "Set default Setpoint at Outdoor Low Temperature to 22 for SetpointManager:OutdoorAirReset '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }

  if (auto value = getDouble(openstudio::SetpointManager_OutdoorAirResetFields::OutdoorLowTemperature, true)) {
    (void)value;
  } else {
    OS_ASSERT(setDouble(openstudio::SetpointManager_OutdoorAirResetFields::OutdoorLowTemperature, 10.0));
    detail::addLoadInfo(context, "Set default Outdoor Low Temperature to 10 for SetpointManager:OutdoorAirReset '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }

  if (auto value = getDouble(openstudio::SetpointManager_OutdoorAirResetFields::SetpointatOutdoorHighTemperature, true)) {
    (void)value;
  } else {
    OS_ASSERT(setDouble(openstudio::SetpointManager_OutdoorAirResetFields::SetpointatOutdoorHighTemperature, 10.0));
    detail::addLoadInfo(context, "Set default Setpoint at Outdoor High Temperature to 10 for SetpointManager:OutdoorAirReset '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }

  if (auto value = getDouble(openstudio::SetpointManager_OutdoorAirResetFields::OutdoorHighTemperature, true)) {
    (void)value;
  } else {
    OS_ASSERT(setDouble(openstudio::SetpointManager_OutdoorAirResetFields::OutdoorHighTemperature, 24.0));
    detail::addLoadInfo(context, "Set default Outdoor High Temperature to 24 for SetpointManager:OutdoorAirReset '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
