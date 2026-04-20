/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMOSTATSETPOINTTHERMALCOMFORTFANGERDUALSETPOINT_HPP
#define EPMODEL_THERMOSTATSETPOINTTHERMALCOMFORTFANGERDUALSETPOINT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ThermostatSetpointThermalComfortFangerDualSetpoint_Impl;
  }

  class EPMODEL_API ThermostatSetpointThermalComfortFangerDualSetpoint : public ModelObject
  {
   public:
    explicit ThermostatSetpointThermalComfortFangerDualSetpoint(const Model& model);

    virtual ~ThermostatSetpointThermalComfortFangerDualSetpoint() override = default;
    ThermostatSetpointThermalComfortFangerDualSetpoint(const ThermostatSetpointThermalComfortFangerDualSetpoint& other) = default;
    ThermostatSetpointThermalComfortFangerDualSetpoint(ThermostatSetpointThermalComfortFangerDualSetpoint&& other) = default;
    ThermostatSetpointThermalComfortFangerDualSetpoint& operator=(const ThermostatSetpointThermalComfortFangerDualSetpoint&) = default;
    ThermostatSetpointThermalComfortFangerDualSetpoint& operator=(ThermostatSetpointThermalComfortFangerDualSetpoint&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type keeps IDD-derived class/API naming.
    // - Field Mapping: Name remains available through the base ModelObject scalar API.
    // - Field Mapping: Fanger Thermal Comfort Heating Schedule Name and Fanger Thermal Comfort Cooling Schedule Name
    //   are ScheduleNames object-list fields (relationship-like references) and are excluded from scalar accessors.
    // - TODO(parity): Add schedule-relationship APIs once scalar saturation is complete.

   protected:
    using ImplType = detail::ThermostatSetpointThermalComfortFangerDualSetpoint_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ThermostatSetpointThermalComfortFangerDualSetpoint(
      std::shared_ptr<detail::ThermostatSetpointThermalComfortFangerDualSetpoint_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
