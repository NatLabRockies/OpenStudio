/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMOSTATSETPOINTTHERMALCOMFORTFANGERSINGLEHEATINGORCOOLING_HPP
#define EPMODEL_THERMOSTATSETPOINTTHERMALCOMFORTFANGERSINGLEHEATINGORCOOLING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling_Impl;
  }

  class EPMODEL_API ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling : public ModelObject
  {
   public:
    explicit ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling(const Model& model);

    virtual ~ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling() override = default;
    ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling(const ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling& other) = default;
    ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling(ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling&& other) = default;
    ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling&
      operator=(const ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling&) = default;
    ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling& operator=(ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists, so the class name stays IDD-derived.
    // - Field Mapping: Name remains available through the base ModelObject scalar API.
    // - Field Mapping: Fanger Thermal Comfort Schedule Name is a ScheduleNames object-list relationship and is intentionally excluded from scalar accessor generation.
    // - TODO(parity): Add helpers for schedule linkage once scalar saturation tackles relationship fields.

   protected:
    using ImplType = detail::ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling(
      std::shared_ptr<detail::ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
