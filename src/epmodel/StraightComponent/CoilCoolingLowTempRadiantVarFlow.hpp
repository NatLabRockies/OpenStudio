/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGLOWTEMPRADIANTVARFLOW_HPP
#define EPMODEL_COILCOOLINGLOWTEMPRADIANTVARFLOW_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <boost/optional.hpp>
#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class ZoneHVACLowTempRadiantVarFlow;

  namespace detail {
    class CoilCoolingLowTempRadiantVarFlow_Impl;
  }

  /** \brief Represents a cooling-coil view of a variable-flow low-temperature radiant system.
   *
   * \par EnergyPlus object
   * No standalone EnergyPlus object. EPModel projects <code>OS:Coil:Cooling:LowTemperatureRadiant:VariableFlow</code> onto \epobject{group-radiative-convective-units.html#zonehvaclowtemperatureradiantvariableflow,ZoneHVAC:LowTemperatureRadiant:VariableFlow} parent storage.
   *
   * \par Important behavior
   * This transient child writes its scalar and schedule fields through to the parent design/coil storage and maps
   * its water ports to the parent's <code>Cooling Water Inlet Node Name</code> and <code>Cooling Water Outlet Node Name</code> fields.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilCoolingLowTempRadiantVarFlow</code>.
   * <b>Changed:</b> the child is transient and cannot be persisted or placed independently as a plant component.
   *
   * \par Known limitations
   * Use the owning parent object for persistence and complete topology.
   */
  class EPMODEL_API CoilCoolingLowTempRadiantVarFlow : public StraightComponent
  {
   public:
    static constexpr bool is_transient = true;  // This is a Transient ModelObject

    explicit CoilCoolingLowTempRadiantVarFlow(const Model& model);

    virtual ~CoilCoolingLowTempRadiantVarFlow() override = default;
    CoilCoolingLowTempRadiantVarFlow(const CoilCoolingLowTempRadiantVarFlow& other) = default;
    CoilCoolingLowTempRadiantVarFlow(CoilCoolingLowTempRadiantVarFlow&& other) = default;
    CoilCoolingLowTempRadiantVarFlow& operator=(const CoilCoolingLowTempRadiantVarFlow&) = default;
    CoilCoolingLowTempRadiantVarFlow& operator=(CoilCoolingLowTempRadiantVarFlow&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> coolingDesignCapacityMethodValues();
    static std::vector<std::string> condensationControlTypeValues();

    boost::optional<double> maximumColdWaterFlow() const;
    bool isMaximumColdWaterFlowDefaulted() const;
    bool isMaximumColdWaterFlowAutosized() const;
    bool setMaximumColdWaterFlow(double maximumColdWaterFlow);
    void resetMaximumColdWaterFlow();
    void autosizeMaximumColdWaterFlow();
    boost::optional<double> autosizedMaximumColdWaterFlow() const;

    double coolingControlThrottlingRange() const;
    bool isCoolingControlThrottlingRangeDefaulted() const;
    bool setCoolingControlThrottlingRange(double coolingControlThrottlingRange);
    void resetCoolingControlThrottlingRange();

    boost::optional<Schedule> coolingControlTemperatureSchedule() const;
    bool setCoolingControlTemperatureSchedule(Schedule& schedule);
    void resetCoolingControlTemperatureSchedule();

    std::string condensationControlType() const;
    bool isCondensationControlTypeDefaulted() const;
    bool setCondensationControlType(const std::string& condensationControlType);
    void resetCondensationControlType();

    double condensationControlDewpointOffset() const;
    bool isCondensationControlDewpointOffsetDefaulted() const;
    bool setCondensationControlDewpointOffset(double condensationControlDewpointOffset);
    void resetCondensationControlDewpointOffset();

    std::string coolingDesignCapacityMethod() const;
    bool setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod);

    boost::optional<double> coolingDesignCapacity() const;
    bool isCoolingDesignCapacityAutosized() const;
    bool setCoolingDesignCapacity(double coolingDesignCapacity);
    void autosizeCoolingDesignCapacity();
    boost::optional<double> autosizedCoolingDesignCapacity() const;

    double coolingDesignCapacityPerFloorArea() const;
    bool setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea);

    double fractionofAutosizedCoolingDesignCapacity() const;
    bool setFractionofAutosizedCoolingDesignCapacity(double fractionofAutosizedCoolingDesignCapacity);

   protected:
    using ImplType = detail::CoilCoolingLowTempRadiantVarFlow_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilCoolingLowTempRadiantVarFlow(std::shared_ptr<detail::CoilCoolingLowTempRadiantVarFlow_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
