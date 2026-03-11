/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling.hpp"
#include "ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling::ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling(const Model& model)
    : ModelObject(ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling::iddObjectType(), model) {}

  ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling::ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling(
    std::shared_ptr<detail::ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling::iddObjectType() {
    return IddObjectType::ThermostatSetpoint_ThermalComfort_Fanger_SingleHeatingOrCooling;
  }

}  // namespace epmodel
}  // namespace openstudio
