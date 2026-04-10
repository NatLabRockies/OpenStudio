/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGLOWTEMPRADIANTVARFLOW_IMPL_HPP
#define EPMODEL_COILHEATINGLOWTEMPRADIANTVARFLOW_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

class ModelObject;
class Node;
class Schedule;
class ZoneHVACLowTempRadiantVarFlow;

namespace detail {

class EPMODEL_API CoilHeatingLowTempRadiantVarFlow_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~CoilHeatingLowTempRadiantVarFlow_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;
  boost::optional<ModelObject> inletModelObject() const override;
  boost::optional<ModelObject> outletModelObject() const override;
  bool addToNode(Node& node) override;
  bool removeFromLoop() override;
  void disconnect() override;

  boost::optional<ZoneHVACLowTempRadiantVarFlow> parent() const;

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
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
