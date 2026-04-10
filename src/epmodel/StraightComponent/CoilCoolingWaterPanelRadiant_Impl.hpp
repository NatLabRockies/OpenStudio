/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGWATERPANELRADIANT_IMPL_HPP
#define EPMODEL_COILCOOLINGWATERPANELRADIANT_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

class ModelObject;
class Node;
class Schedule;
class ZoneHVACCoolingPanelRadiantConvectiveWater;

namespace detail {

class CoilCoolingWaterPanelRadiant_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~CoilCoolingWaterPanelRadiant_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  boost::optional<ModelObject> inletModelObject() const override;
  boost::optional<ModelObject> outletModelObject() const override;
  bool addToNode(Node& node) override;
  bool removeFromLoop() override;
  void disconnect() override;

  boost::optional<ZoneHVACCoolingPanelRadiantConvectiveWater> parent() const;

  double ratedInletWaterTemperature() const;
  bool isRatedInletWaterTemperatureDefaulted() const;
  bool setRatedInletWaterTemperature(double ratedInletWaterTemperature);
  void resetRatedInletWaterTemperature();

  double ratedInletSpaceTemperature() const;
  bool isRatedInletSpaceTemperatureDefaulted() const;
  bool setRatedInletSpaceTemperature(double ratedInletSpaceTemperature);
  void resetRatedInletSpaceTemperature();

  double ratedWaterMassFlowRate() const;
  bool isRatedWaterMassFlowRateDefaulted() const;
  bool setRatedWaterMassFlowRate(double ratedWaterMassFlowRate);
  void resetRatedWaterMassFlowRate();

  std::string coolingDesignCapacityMethod() const;
  bool isCoolingDesignCapacityMethodDefaulted() const;
  bool setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod);
  void resetCoolingDesignCapacityMethod();

  boost::optional<double> coolingDesignCapacity() const;
  bool isCoolingDesignCapacityAutosized() const;
  bool setCoolingDesignCapacity(double coolingDesignCapacity);
  void autosizeCoolingDesignCapacity();
  boost::optional<double> autosizedCoolingDesignCapacity() const;

  double coolingDesignCapacityPerFloorArea() const;
  bool setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea);

  double fractionofAutosizedCoolingDesignCapacity() const;
  bool setFractionofAutosizedCoolingDesignCapacity(double fractionofAutosizedCoolingDesignCapacity);

  boost::optional<double> maximumChilledWaterFlowRate() const;
  bool isMaximumChilledWaterFlowRateAutosized() const;
  bool setMaximumChilledWaterFlowRate(double maximumChilledWaterFlowRate);
  void autosizeMaximumChilledWaterFlowRate();
  boost::optional<double> autosizedMaximumChilledWaterFlowRate() const;

  std::string controlType() const;
  bool isControlTypeDefaulted() const;
  bool setControlType(const std::string& controlType);
  void resetControlType();

  double coolingControlThrottlingRange() const;
  bool isCoolingControlThrottlingRangeDefaulted() const;
  bool setCoolingControlThrottlingRange(double coolingControlThrottlingRange);
  void resetCoolingControlThrottlingRange();

  boost::optional<Schedule> coolingControlTemperatureSchedule() const;
  bool setCoolingControlTemperatureSchedule(Schedule& coolingControlTemperatureSchedule);
  void resetCoolingControlTemperatureSchedule();

  std::string condensationControlType() const;
  bool isCondensationControlTypeDefaulted() const;
  bool setCondensationControlType(const std::string& condensationControlType);
  void resetCondensationControlType();

  double condensationControlDewpointOffset() const;
  bool isCondensationControlDewpointOffsetDefaulted() const;
  bool setCondensationControlDewpointOffset(double condensationControlDewpointOffset);
  void resetCondensationControlDewpointOffset();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
