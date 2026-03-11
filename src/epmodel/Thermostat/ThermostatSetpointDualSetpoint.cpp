/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ThermostatSetpointDualSetpoint.hpp"
#include "ThermostatSetpointDualSetpoint_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <utility>

namespace openstudio {
namespace epmodel {

  ThermostatSetpointDualSetpoint::ThermostatSetpointDualSetpoint(const Model& model)
    : ModelObject(ThermostatSetpointDualSetpoint::iddObjectType(), model) {}

  ThermostatSetpointDualSetpoint::ThermostatSetpointDualSetpoint(std::shared_ptr<detail::ThermostatSetpointDualSetpoint_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ThermostatSetpointDualSetpoint::iddObjectType() {
    return IddObjectType::ThermostatSetpoint_DualSetpoint;
  }

}  // namespace epmodel
}  // namespace openstudio
