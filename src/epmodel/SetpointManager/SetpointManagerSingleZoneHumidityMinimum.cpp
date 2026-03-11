/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerSingleZoneHumidityMinimum.hpp"
#include "SetpointManager/SetpointManagerSingleZoneHumidityMinimum_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SetpointManager_SingleZone_Humidity_Minimum_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SetpointManagerSingleZoneHumidityMinimum::SetpointManagerSingleZoneHumidityMinimum(const Model& model)
  : SetpointManager(SetpointManagerSingleZoneHumidityMinimum::iddObjectType(), model) {
  auto impl = getImpl<detail::SetpointManagerSingleZoneHumidityMinimum_Impl>();
  OS_ASSERT(impl);
  OS_ASSERT(setControlVariable("MinimumHumidityRatio"));
}

SetpointManagerSingleZoneHumidityMinimum::SetpointManagerSingleZoneHumidityMinimum(
  std::shared_ptr<detail::SetpointManagerSingleZoneHumidityMinimum_Impl> impl)
  : SetpointManager(std::move(impl)) {}

IddObjectType SetpointManagerSingleZoneHumidityMinimum::iddObjectType() {
  return IddObjectType::SetpointManager_SingleZone_Humidity_Minimum;
}

std::vector<std::string> SetpointManagerSingleZoneHumidityMinimum::controlVariableValues() {
  return {"MinimumHumidityRatio"};
}

std::string SetpointManagerSingleZoneHumidityMinimum::controlVariable() const {
  return "MinimumHumidityRatio";
}

bool SetpointManagerSingleZoneHumidityMinimum::setControlVariable(const std::string& controlVariable) {
  return openstudio::istringEqual(controlVariable, "MinimumHumidityRatio");
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned SetpointManagerSingleZoneHumidityMinimum_Impl::setpointNodeFieldIndex() const {
  return openstudio::SetpointManager_SingleZone_Humidity_MinimumFields::SetpointNodeorNodeListName;
}

unsigned SetpointManagerSingleZoneHumidityMinimum_Impl::controlVariableFieldIndex() const {
  // E+ SetpointManager:SingleZone:Humidity:Minimum has no explicit control variable field;
  // this placeholder index satisfies the abstract SetpointManager_Impl contract.
  return openstudio::SetpointManager_SingleZone_Humidity_MinimumFields::ControlZoneAirNodeName;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
