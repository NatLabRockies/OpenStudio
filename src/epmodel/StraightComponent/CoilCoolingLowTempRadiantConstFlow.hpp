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

class EPMODEL_API CoilCoolingLowTempRadiantConstFlow : public StraightComponent
{
 public:
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
  // Schema Alignment Notes:
  // - Status: Partial Parity. epmodel now exposes the canonical cooling-coil companion as a transient straight-component view over the
  //   parent radiant object, while the fuller surface-group behavior still lives on the parent.
  // - Canonical Counterpart: openstudio::model::CoilCoolingLowTempRadiantConstFlow.
  // - Implemented Parity: The four schedule relationships, water inlet/outlet ports, and condensation controls are available through the
  //   canonical child wrapper shape.
  // - Documented Delta: Unlike canonical model, this child is transient in epmodel because EnergyPlus does not persist a standalone coil object here.
  //   The child writes through to the parent `ZoneHVAC:LowTemperatureRadiant:ConstantFlow` object and its companion design object.
  // - Field/Storage Mapping: Child schedules and water nodes map to the parent EnergyPlus radiant object; condensation controls map to the
  //   parent EnergyPlus design object.
  // - Remaining Parity Work: Add richer canonical convenience APIs only if they are still useful after the parent relationship layer settles.
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
