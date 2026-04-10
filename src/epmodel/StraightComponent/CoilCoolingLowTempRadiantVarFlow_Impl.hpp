/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGLOWTEMPRADIANTVARFLOW_IMPL_HPP
#define EPMODEL_COILCOOLINGLOWTEMPRADIANTVARFLOW_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

class ModelObject;
class Node;
class Schedule;
class ZoneHVACLowTempRadiantVarFlow;

namespace detail {

class EPMODEL_API CoilCoolingLowTempRadiantVarFlow_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~CoilCoolingLowTempRadiantVarFlow_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;
  boost::optional<ModelObject> inletModelObject() const override;
  boost::optional<ModelObject> outletModelObject() const override;
  bool addToNode(Node& node) override;
  bool removeFromLoop() override;
  void disconnect() override;

  boost::optional<ZoneHVACLowTempRadiantVarFlow> parent() const;

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
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
