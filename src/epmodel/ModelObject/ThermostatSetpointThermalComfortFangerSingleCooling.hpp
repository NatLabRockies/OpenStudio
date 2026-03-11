/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMOSTATSETPOINTTHERMALCOMFORTFANGERSINGLECOOLING_HPP
#define EPMODEL_THERMOSTATSETPOINTTHERMALCOMFORTFANGERSINGLECOOLING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ThermostatSetpointThermalComfortFangerSingleCooling_Impl;
  }

  class EPMODEL_API ThermostatSetpointThermalComfortFangerSingleCooling : public ModelObject
  {
   public:
    explicit ThermostatSetpointThermalComfortFangerSingleCooling(const Model& model);

    virtual ~ThermostatSetpointThermalComfortFangerSingleCooling() override = default;
    ThermostatSetpointThermalComfortFangerSingleCooling(const ThermostatSetpointThermalComfortFangerSingleCooling& other) = default;
    ThermostatSetpointThermalComfortFangerSingleCooling(ThermostatSetpointThermalComfortFangerSingleCooling&& other) = default;
    ThermostatSetpointThermalComfortFangerSingleCooling& operator=(const ThermostatSetpointThermalComfortFangerSingleCooling&) = default;
    ThermostatSetpointThermalComfortFangerSingleCooling& operator=(ThermostatSetpointThermalComfortFangerSingleCooling&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists, so the class name is IDD-derived.
    // - Field Mapping: Name remains available through the base ModelObject scalar API.
    // - Field Mapping: Fanger Thermal Comfort Schedule Name is a ScheduleNames object-list relationship and is intentionally excluded from scalar accessors.
    // - TODO(parity): Add schedule linkage helpers once scalar saturation is complete.

   protected:
    using ImplType = detail::ThermostatSetpointThermalComfortFangerSingleCooling_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ThermostatSetpointThermalComfortFangerSingleCooling(
      std::shared_ptr<detail::ThermostatSetpointThermalComfortFangerSingleCooling_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
