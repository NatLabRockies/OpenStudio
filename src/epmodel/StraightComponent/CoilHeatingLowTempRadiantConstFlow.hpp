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

  /** \brief Represents a heating-coil view of a constant-flow low-temperature radiant system.
   *
   * \par EnergyPlus object
   * No standalone EnergyPlus object. EPModel projects <code>OS:Coil:Heating:LowTemperatureRadiant:ConstantFlow</code> onto \epobject{group-radiative-convective-units.html#zonehvaclowtemperatureradiantconstantflow,ZoneHVAC:LowTemperatureRadiant:ConstantFlow} parent storage.
   *
   * \par Important behavior
   * This transient child writes its scalar and schedule fields through to the parent design/coil storage and maps
   * its water ports to the parent's <code>Heating Water Inlet Node Name</code> and <code>Heating Water Outlet Node Name</code> fields.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilHeatingLowTempRadiantConstFlow</code>.
   * <b>Changed:</b> the child is transient and cannot be persisted or placed independently as a plant component.
   *
   * \par Known limitations
   * Use the owning parent object for persistence and complete topology.
   */
  class EPMODEL_API CoilHeatingLowTempRadiantConstFlow : public StraightComponent
  {
   public:
    static constexpr bool is_transient = true;  // This is a Transient ModelObject

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
