/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMOSTAT_THERMOSTATSETPOINTDUALSETPOINT_HPP
#define EPMODEL_THERMOSTAT_THERMOSTATSETPOINTDUALSETPOINT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ThermostatSetpointDualSetpoint_Impl;
  }

  class EPMODEL_API ThermostatSetpointDualSetpoint : public ModelObject
  {
   public:
    explicit ThermostatSetpointDualSetpoint(const Model& model);

    virtual ~ThermostatSetpointDualSetpoint() override = default;
    ThermostatSetpointDualSetpoint(const ThermostatSetpointDualSetpoint& other) = default;
    ThermostatSetpointDualSetpoint(ThermostatSetpointDualSetpoint&& other) = default;
    ThermostatSetpointDualSetpoint& operator=(const ThermostatSetpointDualSetpoint&) = default;
    ThermostatSetpointDualSetpoint& operator=(ThermostatSetpointDualSetpoint&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This model-counterpart class mirrors the EnergyPlus ThermostatSetpoint:DualSetpoint naming and the C++ model counterpart.
    // - Field Mapping: Name remains available through the base ModelObject scalar API.
    // - Field Mapping: Heating Setpoint Temperature Schedule Name and Cooling Setpoint Temperature Schedule Name reference Schedule object lists and are intentionally omitted from scalar accessors.
    // - Field Mapping: ThermostatSetpoint:SingleCooling and ThermostatSetpoint:SingleHeating are translated into this class when only a cooling or heating schedule exists, so Model_Impl::createObject now maps those IDD types here too while still exposing only the base Name scalar.
    // - TODO(parity): Add relationship-centric helpers for those schedule references once scalar saturation allows it.

   protected:
    using ImplType = detail::ThermostatSetpointDualSetpoint_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ThermostatSetpointDualSetpoint(std::shared_ptr<detail::ThermostatSetpointDualSetpoint_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
