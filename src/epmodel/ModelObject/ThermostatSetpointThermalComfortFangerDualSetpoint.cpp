/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ThermostatSetpointThermalComfortFangerDualSetpoint.hpp"
#include "ThermostatSetpointThermalComfortFangerDualSetpoint_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ThermostatSetpointThermalComfortFangerDualSetpoint::ThermostatSetpointThermalComfortFangerDualSetpoint(const Model& model)
    : ModelObject(ThermostatSetpointThermalComfortFangerDualSetpoint::iddObjectType(), model) {}

  ThermostatSetpointThermalComfortFangerDualSetpoint::ThermostatSetpointThermalComfortFangerDualSetpoint(
    std::shared_ptr<detail::ThermostatSetpointThermalComfortFangerDualSetpoint_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ThermostatSetpointThermalComfortFangerDualSetpoint::iddObjectType() {
    return IddObjectType::ThermostatSetpoint_ThermalComfort_Fanger_DualSetpoint;
  }

}  // namespace epmodel
}  // namespace openstudio
