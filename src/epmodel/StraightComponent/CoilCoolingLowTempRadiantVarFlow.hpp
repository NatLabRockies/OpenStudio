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

  class EPMODEL_API CoilCoolingLowTempRadiantVarFlow : public StraightComponent
  {
   public:
    explicit CoilCoolingLowTempRadiantVarFlow(const Model& model);

    virtual ~CoilCoolingLowTempRadiantVarFlow() override = default;
    CoilCoolingLowTempRadiantVarFlow(const CoilCoolingLowTempRadiantVarFlow& other) = default;
    CoilCoolingLowTempRadiantVarFlow(CoilCoolingLowTempRadiantVarFlow&& other) = default;
    CoilCoolingLowTempRadiantVarFlow& operator=(const CoilCoolingLowTempRadiantVarFlow&) = default;
    CoilCoolingLowTempRadiantVarFlow& operator=(CoilCoolingLowTempRadiantVarFlow&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> coolingDesignCapacityMethodValues();
    static std::vector<std::string> condensationControlTypeValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. epmodel preserves the canonical optional cooling-coil child as a transient
    //   straight-component view over parent-owned EnergyPlus storage.
    // - Canonical Counterpart: openstudio::model::CoilCoolingLowTempRadiantVarFlow.
    // - Why This Type Is Slightly Different: canonical OpenStudio factors this family into one parent radiant object
    //   plus optional heating/cooling coil children. EnergyPlus does not persist a standalone cooling coil here; it
    //   stores the cooling-coil state directly on the parent radiant object and the persisted `...:Design` companion.
    //   Epmodel keeps the canonical child shape additively by exposing a transient child that reads and writes those
    //   parent-owned fields.
    // - Implemented Parity: The canonical cooling-capacity, cold-water-flow, control schedule, throttling,
    //   condensation-control, and water-node APIs are available through this transient child wrapper.
    // - Plant Loop Behavior: The child is still transient, but it now supports the canonical plant-loop API surface.
    //   Epmodel persists the parent radiant unit on the branch and projects that stored parent row back to this
    //   transient cooling coil in high-level plant-loop traversal when the branch water-node pair matches the
    //   cooling-side role.
    // - Field/Storage Mapping: Cooling-side scalar fields live on the parent `ZoneHVAC:LowTemperatureRadiant:VariableFlow`
    //   object and its persisted `...:Design` companion object. This child is a write-through view over that storage.
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
