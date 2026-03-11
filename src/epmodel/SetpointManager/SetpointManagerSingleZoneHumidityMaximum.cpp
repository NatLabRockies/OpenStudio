/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerSingleZoneHumidityMaximum.hpp"
#include "SetpointManager/SetpointManagerSingleZoneHumidityMaximum_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SetpointManager_SingleZone_Humidity_Maximum_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SetpointManagerSingleZoneHumidityMaximum::SetpointManagerSingleZoneHumidityMaximum(const Model& model)
  : SetpointManager(SetpointManagerSingleZoneHumidityMaximum::iddObjectType(), model) {
  auto impl = getImpl<detail::SetpointManagerSingleZoneHumidityMaximum_Impl>();
  OS_ASSERT(impl);
  OS_ASSERT(setControlVariable("MaximumHumidityRatio"));
}

SetpointManagerSingleZoneHumidityMaximum::SetpointManagerSingleZoneHumidityMaximum(
  std::shared_ptr<detail::SetpointManagerSingleZoneHumidityMaximum_Impl> impl)
  : SetpointManager(std::move(impl)) {}

IddObjectType SetpointManagerSingleZoneHumidityMaximum::iddObjectType() {
  return IddObjectType::SetpointManager_SingleZone_Humidity_Maximum;
}

std::vector<std::string> SetpointManagerSingleZoneHumidityMaximum::controlVariableValues() {
  return {"MaximumHumidityRatio"};
}

std::string SetpointManagerSingleZoneHumidityMaximum::controlVariable() const {
  return "MaximumHumidityRatio";
}

bool SetpointManagerSingleZoneHumidityMaximum::setControlVariable(const std::string& controlVariable) {
  return openstudio::istringEqual(controlVariable, "MaximumHumidityRatio");
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned SetpointManagerSingleZoneHumidityMaximum_Impl::setpointNodeFieldIndex() const {
  return openstudio::SetpointManager_SingleZone_Humidity_MaximumFields::SetpointNodeorNodeListName;
}

unsigned SetpointManagerSingleZoneHumidityMaximum_Impl::controlVariableFieldIndex() const {
  // E+ SetpointManager:SingleZone:Humidity:Maximum has no explicit control variable field;
  // this placeholder index satisfies the abstract SetpointManager_Impl contract.
  return openstudio::SetpointManager_SingleZone_Humidity_MaximumFields::ControlZoneAirNodeName;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
