/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ThermostatSetpointThermalComfortFangerSingleHeating.hpp"
#include "ThermostatSetpointThermalComfortFangerSingleHeating_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ThermostatSetpointThermalComfortFangerSingleHeating::ThermostatSetpointThermalComfortFangerSingleHeating(const Model& model)
    : ModelObject(ThermostatSetpointThermalComfortFangerSingleHeating::iddObjectType(), model) {}

  ThermostatSetpointThermalComfortFangerSingleHeating::ThermostatSetpointThermalComfortFangerSingleHeating(
    std::shared_ptr<detail::ThermostatSetpointThermalComfortFangerSingleHeating_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ThermostatSetpointThermalComfortFangerSingleHeating::iddObjectType() {
    return IddObjectType::ThermostatSetpoint_ThermalComfort_Fanger_SingleHeating;
  }

}  // namespace epmodel
}  // namespace openstudio
