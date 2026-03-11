/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ThermostatSetpointThermalComfortFangerSingleCooling.hpp"
#include "ThermostatSetpointThermalComfortFangerSingleCooling_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ThermostatSetpointThermalComfortFangerSingleCooling::ThermostatSetpointThermalComfortFangerSingleCooling(const Model& model)
    : ModelObject(ThermostatSetpointThermalComfortFangerSingleCooling::iddObjectType(), model) {}

  ThermostatSetpointThermalComfortFangerSingleCooling::ThermostatSetpointThermalComfortFangerSingleCooling(
    std::shared_ptr<detail::ThermostatSetpointThermalComfortFangerSingleCooling_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ThermostatSetpointThermalComfortFangerSingleCooling::iddObjectType() {
    return IddObjectType::ThermostatSetpoint_ThermalComfort_Fanger_SingleCooling;
  }

}  // namespace epmodel
}  // namespace openstudio
