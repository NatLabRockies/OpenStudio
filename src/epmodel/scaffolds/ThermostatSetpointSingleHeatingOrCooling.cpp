/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ThermostatSetpointSingleHeatingOrCooling.hpp"
#include "ThermostatSetpointSingleHeatingOrCooling_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ThermostatSetpointSingleHeatingOrCooling::ThermostatSetpointSingleHeatingOrCooling(const Model& model)
    : ModelObject(ThermostatSetpointSingleHeatingOrCooling::iddObjectType(), model) {}

  ThermostatSetpointSingleHeatingOrCooling::ThermostatSetpointSingleHeatingOrCooling(
    std::shared_ptr<detail::ThermostatSetpointSingleHeatingOrCooling_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ThermostatSetpointSingleHeatingOrCooling::iddObjectType() {
    return IddObjectType::ThermostatSetpoint_SingleHeatingOrCooling;
  }

}  // namespace epmodel
}  // namespace openstudio
