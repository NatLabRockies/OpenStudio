/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGLOWTEMPRADIANTCONSTFLOW_HPP
#define EPMODEL_COILHEATINGLOWTEMPRADIANTCONSTFLOW_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;

  namespace detail {
    class CoilHeatingLowTempRadiantConstFlow_Impl;
  }

  class EPMODEL_API CoilHeatingLowTempRadiantConstFlow : public StraightComponent
  {
   public:
    explicit CoilHeatingLowTempRadiantConstFlow(const Model& model);

    virtual ~CoilHeatingLowTempRadiantConstFlow() override = default;
    CoilHeatingLowTempRadiantConstFlow(const CoilHeatingLowTempRadiantConstFlow& other) = default;
    CoilHeatingLowTempRadiantConstFlow(CoilHeatingLowTempRadiantConstFlow&& other) = default;
    CoilHeatingLowTempRadiantConstFlow& operator=(const CoilHeatingLowTempRadiantConstFlow&) = default;
    CoilHeatingLowTempRadiantConstFlow& operator=(CoilHeatingLowTempRadiantConstFlow&&) = default;

    static IddObjectType iddObjectType();

    // This is a transient canonical companion wrapper, not a standalone
    // EnergyPlus object. openstudio::model factors the radiant parent into a
    // parent ZoneHVAC object plus heating/cooling coil children, but EnergyPlus
    // stores the heating-coil state directly on the parent radiant object. In
    // epmodel we preserve that canonical child shape by exposing a transient
    // child that reads and writes the parent-owned fields.
    //
    // Schema Alignment Notes:
    // - Status: Partial Parity. epmodel now exposes the canonical heating-coil companion as a transient straight-component view over the
    //   parent radiant object, while the fuller surface-group behavior still lives on the parent.
    // - Canonical Counterpart: openstudio::model::CoilHeatingLowTempRadiantConstFlow.
    // - Implemented Parity: The four schedule relationships and water inlet/outlet ports are available through the canonical child wrapper shape.
    // - Documented Delta: Unlike canonical model, this child is transient in epmodel because EnergyPlus does not persist a standalone coil object here.
    //   The child writes through to the parent `ZoneHVAC:LowTemperatureRadiant:ConstantFlow` object instead of owning separate storage.
    // - Field/Storage Mapping: Child schedule and node APIs map directly to the parent EnergyPlus radiant fields.
    // - Remaining Parity Work: Add richer canonical convenience APIs only if they are still useful after the parent relationship layer settles.
    boost::optional<Schedule> heatingHighWaterTemperatureSchedule() const;
    bool setHeatingHighWaterTemperatureSchedule(Schedule& schedule);
    void resetHeatingHighWaterTemperatureSchedule();

    boost::optional<Schedule> heatingLowWaterTemperatureSchedule() const;
    bool setHeatingLowWaterTemperatureSchedule(Schedule& schedule);
    void resetHeatingLowWaterTemperatureSchedule();

    boost::optional<Schedule> heatingHighControlTemperatureSchedule() const;
    bool setHeatingHighControlTemperatureSchedule(Schedule& schedule);
    void resetHeatingHighControlTemperatureSchedule();

    boost::optional<Schedule> heatingLowControlTemperatureSchedule() const;
    bool setHeatingLowControlTemperatureSchedule(Schedule& schedule);
    void resetHeatingLowControlTemperatureSchedule();

   protected:
    using ImplType = detail::CoilHeatingLowTempRadiantConstFlow_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilHeatingLowTempRadiantConstFlow(std::shared_ptr<detail::CoilHeatingLowTempRadiantConstFlow_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
