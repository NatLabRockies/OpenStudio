/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMOSTATSETPOINTTHERMALCOMFORTFANGERSINGLEHEATING_HPP
#define EPMODEL_THERMOSTATSETPOINTTHERMALCOMFORTFANGERSINGLEHEATING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ThermostatSetpointThermalComfortFangerSingleHeating_Impl;
  }

  class EPMODEL_API ThermostatSetpointThermalComfortFangerSingleHeating : public ModelObject
  {
   public:
    explicit ThermostatSetpointThermalComfortFangerSingleHeating(const Model& model);

    virtual ~ThermostatSetpointThermalComfortFangerSingleHeating() override = default;
    ThermostatSetpointThermalComfortFangerSingleHeating(const ThermostatSetpointThermalComfortFangerSingleHeating& other) = default;
    ThermostatSetpointThermalComfortFangerSingleHeating(ThermostatSetpointThermalComfortFangerSingleHeating&& other) = default;
    ThermostatSetpointThermalComfortFangerSingleHeating& operator=(const ThermostatSetpointThermalComfortFangerSingleHeating&) = default;
    ThermostatSetpointThermalComfortFangerSingleHeating& operator=(ThermostatSetpointThermalComfortFangerSingleHeating&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists, so the class name is IDD-derived.
    // - Field Mapping: Name remains available through the base ModelObject scalar API.
    // - Field Mapping: Fanger Thermal Comfort Schedule Name is a ScheduleNames object-list relationship and is intentionally excluded from scalar accessors.
    // - TODO(parity): Add schedule linkage helpers once scalar saturation is complete.

   protected:
    using ImplType = detail::ThermostatSetpointThermalComfortFangerSingleHeating_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ThermostatSetpointThermalComfortFangerSingleHeating(
      std::shared_ptr<detail::ThermostatSetpointThermalComfortFangerSingleHeating_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
