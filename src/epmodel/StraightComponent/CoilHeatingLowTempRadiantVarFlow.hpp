/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGLOWTEMPRADIANTVARFLOW_HPP
#define EPMODEL_COILHEATINGLOWTEMPRADIANTVARFLOW_HPP

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
class CoilHeatingLowTempRadiantVarFlow_Impl;
}

class EPMODEL_API CoilHeatingLowTempRadiantVarFlow : public StraightComponent
{
 public:
  explicit CoilHeatingLowTempRadiantVarFlow(const Model& model);

  virtual ~CoilHeatingLowTempRadiantVarFlow() override = default;
  CoilHeatingLowTempRadiantVarFlow(const CoilHeatingLowTempRadiantVarFlow& other) = default;
  CoilHeatingLowTempRadiantVarFlow(CoilHeatingLowTempRadiantVarFlow&& other) = default;
  CoilHeatingLowTempRadiantVarFlow& operator=(const CoilHeatingLowTempRadiantVarFlow&) = default;
  CoilHeatingLowTempRadiantVarFlow& operator=(CoilHeatingLowTempRadiantVarFlow&&) = default;

  static IddObjectType iddObjectType();
  static std::vector<std::string> heatingDesignCapacityMethodValues();

  // Schema Alignment Notes:
  // - Status: Partial Parity. epmodel preserves the canonical optional heating-coil child as a transient
  //   straight-component view over parent-owned EnergyPlus storage.
  // - Canonical Counterpart: openstudio::model::CoilHeatingLowTempRadiantVarFlow.
  // - Why This Type Is Slightly Different: canonical OpenStudio factors this family into one parent radiant object
  //   plus optional heating/cooling coil children. EnergyPlus does not persist a standalone heating coil here; it
  //   stores the heating-coil state directly on the parent radiant object and the persisted `...:Design` companion.
  //   Epmodel keeps the canonical child shape additively by exposing a transient child that reads and writes those
  //   parent-owned fields.
  // - Implemented Parity: The canonical heating-capacity, hot-water-flow, control schedule, throttling, and water-node
  //   APIs are available through this transient child wrapper.
  // - Documented Delta: Because this child is transient, it does not claim to be a persisted standalone loop
  //   component. `addToNode(...)` therefore remains disabled in the impl instead of pretending there is a real E+
  //   coil object behind the canonical child view.
  // - Field/Storage Mapping: Heating-side scalar fields live on the parent `ZoneHVAC:LowTemperatureRadiant:VariableFlow`
  //   object and its persisted `...:Design` companion object. This child is a write-through view over that storage.
  boost::optional<double> maximumHotWaterFlow() const;
  bool isMaximumHotWaterFlowDefaulted() const;
  bool isMaximumHotWaterFlowAutosized() const;
  bool setMaximumHotWaterFlow(double maximumHotWaterFlow);
  void resetMaximumHotWaterFlow();
  void autosizeMaximumHotWaterFlow();
  boost::optional<double> autosizedMaximumHotWaterFlow() const;

  double heatingControlThrottlingRange() const;
  bool isHeatingControlThrottlingRangeDefaulted() const;
  bool setHeatingControlThrottlingRange(double heatingControlThrottlingRange);
  void resetHeatingControlThrottlingRange();

  boost::optional<Schedule> heatingControlTemperatureSchedule() const;
  bool setHeatingControlTemperatureSchedule(Schedule& schedule);
  void resetHeatingControlTemperatureSchedule();

  std::string heatingDesignCapacityMethod() const;
  bool setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod);

  boost::optional<double> heatingDesignCapacity() const;
  bool isHeatingDesignCapacityAutosized() const;
  bool setHeatingDesignCapacity(double heatingDesignCapacity);
  void autosizeHeatingDesignCapacity();
  boost::optional<double> autosizedHeatingDesignCapacity() const;

  double heatingDesignCapacityPerFloorArea() const;
  bool setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea);

  double fractionofAutosizedHeatingDesignCapacity() const;
  bool setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity);

 protected:
  using ImplType = detail::CoilHeatingLowTempRadiantVarFlow_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilHeatingLowTempRadiantVarFlow(std::shared_ptr<detail::CoilHeatingLowTempRadiantVarFlow_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
