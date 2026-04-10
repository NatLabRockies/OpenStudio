/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGLOWTEMPRADIANTCONSTFLOW_IMPL_HPP
#define EPMODEL_COILCOOLINGLOWTEMPRADIANTCONSTFLOW_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

class Schedule;
class ZoneHVACLowTempRadiantConstFlow;

namespace detail {

class EPMODEL_API CoilCoolingLowTempRadiantConstFlow_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~CoilCoolingLowTempRadiantConstFlow_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;
  boost::optional<ModelObject> inletModelObject() const override;
  boost::optional<ModelObject> outletModelObject() const override;
  bool addToNode(Node& node) override;
  bool removeFromLoop() override;
  void disconnect() override;

  boost::optional<Schedule> coolingHighWaterTemperatureSchedule() const;
  boost::optional<Schedule> coolingLowWaterTemperatureSchedule() const;
  boost::optional<Schedule> coolingHighControlTemperatureSchedule() const;
  boost::optional<Schedule> coolingLowControlTemperatureSchedule() const;

  std::string condensationControlType() const;
  bool isCondensationControlTypeDefaulted() const;
  double condensationControlDewpointOffset() const;
  bool isCondensationControlDewpointOffsetDefaulted() const;

  bool setCoolingHighWaterTemperatureSchedule(Schedule& schedule);
  void resetCoolingHighWaterTemperatureSchedule();
  bool setCoolingLowWaterTemperatureSchedule(Schedule& schedule);
  void resetCoolingLowWaterTemperatureSchedule();
  bool setCoolingHighControlTemperatureSchedule(Schedule& schedule);
  void resetCoolingHighControlTemperatureSchedule();
  bool setCoolingLowControlTemperatureSchedule(Schedule& schedule);
  void resetCoolingLowControlTemperatureSchedule();
  bool setCondensationControlType(const std::string& condensationControlType);
  void resetCondensationControlType();
  bool setCondensationControlDewpointOffset(double condensationControlDewpointOffset);
  void resetCondensationControlDewpointOffset();

 private:
  boost::optional<ZoneHVACLowTempRadiantConstFlow> parent() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
