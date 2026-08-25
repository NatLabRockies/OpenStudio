/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGLOWTEMPRADIANTCONSTFLOW_HPP
#define EPMODEL_COILCOOLINGLOWTEMPRADIANTCONSTFLOW_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;

  namespace detail {
    class CoilCoolingLowTempRadiantConstFlow_Impl;
  }

  /** \brief Represents a cooling-coil view of a constant-flow low-temperature radiant system.
   *
   * \par EnergyPlus object
   * No standalone EnergyPlus object. EPModel projects <code>OS:Coil:Cooling:LowTemperatureRadiant:ConstantFlow</code> onto \epobject{group-radiative-convective-units.html#zonehvaclowtemperatureradiantconstantflow,ZoneHVAC:LowTemperatureRadiant:ConstantFlow} parent storage.
   *
   * \par Important behavior
   * This transient child writes its scalar and schedule fields through to the parent design/coil storage and maps
   * its water ports to the parent's <code>Cooling Water Inlet Node Name</code> and <code>Cooling Water Outlet Node Name</code> fields.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilCoolingLowTempRadiantConstFlow</code>.
   * <b>Changed:</b> the child is transient and cannot be persisted or placed independently as a plant component.
   *
   * \par Known limitations
   * Use the owning parent object for persistence and complete topology.
   */
  class EPMODEL_API CoilCoolingLowTempRadiantConstFlow : public StraightComponent
  {
   public:
    static constexpr bool is_transient = true;  // This is a Transient ModelObject

    explicit CoilCoolingLowTempRadiantConstFlow(const Model& model);

    virtual ~CoilCoolingLowTempRadiantConstFlow() override = default;
    CoilCoolingLowTempRadiantConstFlow(const CoilCoolingLowTempRadiantConstFlow& other) = default;
    CoilCoolingLowTempRadiantConstFlow(CoilCoolingLowTempRadiantConstFlow&& other) = default;
    CoilCoolingLowTempRadiantConstFlow& operator=(const CoilCoolingLowTempRadiantConstFlow&) = default;
    CoilCoolingLowTempRadiantConstFlow& operator=(CoilCoolingLowTempRadiantConstFlow&&) = default;

    static IddObjectType iddObjectType();

    // This is a transient canonical companion wrapper, not a standalone
    // EnergyPlus object. openstudio::model factors the radiant parent into a
    // parent ZoneHVAC object plus heating/cooling coil children, but EnergyPlus
    // stores the cooling-coil state directly on the parent radiant object and
    // its companion design object. In epmodel we preserve that canonical child
    // shape by exposing a transient child that reads and writes those
    // parent-owned fields.
    //
    boost::optional<Schedule> coolingHighWaterTemperatureSchedule() const;
    bool setCoolingHighWaterTemperatureSchedule(Schedule& schedule);
    void resetCoolingHighWaterTemperatureSchedule();

    boost::optional<Schedule> coolingLowWaterTemperatureSchedule() const;
    bool setCoolingLowWaterTemperatureSchedule(Schedule& schedule);
    void resetCoolingLowWaterTemperatureSchedule();

    boost::optional<Schedule> coolingHighControlTemperatureSchedule() const;
    bool setCoolingHighControlTemperatureSchedule(Schedule& schedule);
    void resetCoolingHighControlTemperatureSchedule();

    boost::optional<Schedule> coolingLowControlTemperatureSchedule() const;
    bool setCoolingLowControlTemperatureSchedule(Schedule& schedule);
    void resetCoolingLowControlTemperatureSchedule();

    std::string condensationControlType() const;
    bool isCondensationControlTypeDefaulted() const;
    bool setCondensationControlType(const std::string& condensationControlType);
    void resetCondensationControlType();

    double condensationControlDewpointOffset() const;
    bool isCondensationControlDewpointOffsetDefaulted() const;
    bool setCondensationControlDewpointOffset(double condensationControlDewpointOffset);
    void resetCondensationControlDewpointOffset();

   protected:
    using ImplType = detail::CoilCoolingLowTempRadiantConstFlow_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilCoolingLowTempRadiantConstFlow(std::shared_ptr<detail::CoilCoolingLowTempRadiantConstFlow_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
