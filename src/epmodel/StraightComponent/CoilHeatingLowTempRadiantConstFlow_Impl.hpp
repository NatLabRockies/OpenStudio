/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGLOWTEMPRADIANTCONSTFLOW_IMPL_HPP
#define EPMODEL_COILHEATINGLOWTEMPRADIANTCONSTFLOW_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

class Schedule;
class ZoneHVACLowTempRadiantConstFlow;

namespace detail {

class EPMODEL_API CoilHeatingLowTempRadiantConstFlow_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~CoilHeatingLowTempRadiantConstFlow_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;
  boost::optional<ModelObject> inletModelObject() const override;
  boost::optional<ModelObject> outletModelObject() const override;
  bool addToNode(Node& node) override;
  bool removeFromLoop() override;
  void disconnect() override;

  boost::optional<Schedule> heatingHighWaterTemperatureSchedule() const;
  boost::optional<Schedule> heatingLowWaterTemperatureSchedule() const;
  boost::optional<Schedule> heatingHighControlTemperatureSchedule() const;
  boost::optional<Schedule> heatingLowControlTemperatureSchedule() const;

  bool setHeatingHighWaterTemperatureSchedule(Schedule& schedule);
  void resetHeatingHighWaterTemperatureSchedule();
  bool setHeatingLowWaterTemperatureSchedule(Schedule& schedule);
  void resetHeatingLowWaterTemperatureSchedule();
  bool setHeatingHighControlTemperatureSchedule(Schedule& schedule);
  void resetHeatingHighControlTemperatureSchedule();
  bool setHeatingLowControlTemperatureSchedule(Schedule& schedule);
  void resetHeatingLowControlTemperatureSchedule();

 private:
  boost::optional<ZoneHVACLowTempRadiantConstFlow> parent() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
