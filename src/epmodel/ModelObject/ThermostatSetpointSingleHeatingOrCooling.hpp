/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMOSTATSETPOINTSINGLEHEATINGORCOOLING_HPP
#define EPMODEL_THERMOSTATSETPOINTSINGLEHEATINGORCOOLING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ThermostatSetpointSingleHeatingOrCooling_Impl;
  }

  class EPMODEL_API ThermostatSetpointSingleHeatingOrCooling : public ModelObject
  {
   public:
    explicit ThermostatSetpointSingleHeatingOrCooling(const Model& model);

    virtual ~ThermostatSetpointSingleHeatingOrCooling() override = default;
    ThermostatSetpointSingleHeatingOrCooling(const ThermostatSetpointSingleHeatingOrCooling& other) = default;
    ThermostatSetpointSingleHeatingOrCooling(ThermostatSetpointSingleHeatingOrCooling&& other) = default;
    ThermostatSetpointSingleHeatingOrCooling& operator=(const ThermostatSetpointSingleHeatingOrCooling&) = default;
    ThermostatSetpointSingleHeatingOrCooling& operator=(ThermostatSetpointSingleHeatingOrCooling&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists, so class/API naming follow the IDD strings directly.
    // - Field Mapping: Name remains available via the base ModelObject scalar API.
    // - Field Mapping: Setpoint Temperature Schedule Name is a ScheduleNames object-list relationship and intentionally excluded from scalar accessors.
    // - TODO(parity): Provide explicit schedule helpers once IDD relationship scaffolding is available.

   protected:
    using ImplType = detail::ThermostatSetpointSingleHeatingOrCooling_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ThermostatSetpointSingleHeatingOrCooling(std::shared_ptr<detail::ThermostatSetpointSingleHeatingOrCooling_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
