/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManagerReturnAirBypassFlow.hpp"
#include "SetpointManagerReturnAirBypassFlow_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/SetpointManager_ReturnAirBypassFlow_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SetpointManagerReturnAirBypassFlow::SetpointManagerReturnAirBypassFlow(const Model& model)
  : ModelObject(SetpointManagerReturnAirBypassFlow::iddObjectType(), model) {}

SetpointManagerReturnAirBypassFlow::SetpointManagerReturnAirBypassFlow(
  std::shared_ptr<detail::SetpointManagerReturnAirBypassFlow_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType SetpointManagerReturnAirBypassFlow::iddObjectType() {
  return IddObjectType::SetpointManager_ReturnAirBypassFlow;
}

std::vector<std::string> SetpointManagerReturnAirBypassFlow::controlVariableValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::SetpointManager_ReturnAirBypassFlowFields::ControlVariable);
}

std::string SetpointManagerReturnAirBypassFlow::controlVariable() const {
  return getImpl<detail::SetpointManagerReturnAirBypassFlow_Impl>()->controlVariable();
}

bool SetpointManagerReturnAirBypassFlow::isControlVariableDefaulted() const {
  return getImpl<detail::SetpointManagerReturnAirBypassFlow_Impl>()->isControlVariableDefaulted();
}

bool SetpointManagerReturnAirBypassFlow::setControlVariable(const std::string& controlVariable) {
  return getImpl<detail::SetpointManagerReturnAirBypassFlow_Impl>()->setControlVariable(controlVariable);
}

void SetpointManagerReturnAirBypassFlow::resetControlVariable() {
  getImpl<detail::SetpointManagerReturnAirBypassFlow_Impl>()->resetControlVariable();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string SetpointManagerReturnAirBypassFlow_Impl::controlVariable() const {
  const auto value = getString(openstudio::SetpointManager_ReturnAirBypassFlowFields::ControlVariable, true);
  OS_ASSERT(value);
  return *value;
}

bool SetpointManagerReturnAirBypassFlow_Impl::isControlVariableDefaulted() const {
  return isEmpty(openstudio::SetpointManager_ReturnAirBypassFlowFields::ControlVariable);
}

bool SetpointManagerReturnAirBypassFlow_Impl::setControlVariable(const std::string& controlVariable) {
  return setString(openstudio::SetpointManager_ReturnAirBypassFlowFields::ControlVariable, controlVariable);
}

void SetpointManagerReturnAirBypassFlow_Impl::resetControlVariable() {
  OS_ASSERT(setString(openstudio::SetpointManager_ReturnAirBypassFlowFields::ControlVariable, ""));
}

std::vector<std::string> SetpointManagerReturnAirBypassFlow_Impl::controlVariableValues() const {
  return SetpointManagerReturnAirBypassFlow::controlVariableValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
