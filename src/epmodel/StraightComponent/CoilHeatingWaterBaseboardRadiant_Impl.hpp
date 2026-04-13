/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGWATERBASEBOARDRADIANT_IMPL_HPP
#define EPMODEL_COILHEATINGWATERBASEBOARDRADIANT_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

class ZoneHVACBaseboardRadiantConvectiveWater;

namespace detail {

class EPMODEL_API CoilHeatingWaterBaseboardRadiant_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~CoilHeatingWaterBaseboardRadiant_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;
  boost::optional<ModelObject> inletModelObject() const override;
  boost::optional<ModelObject> outletModelObject() const override;
  bool addToNode(Node& node) override;
  bool removeFromLoop() override;
  void disconnect() override;

  double ratedAverageWaterTemperature() const;
  bool setRatedAverageWaterTemperature(double ratedAverageWaterTemperature);

  double ratedWaterMassFlowRate() const;
  bool setRatedWaterMassFlowRate(double ratedWaterMassFlowRate);

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

  boost::optional<double> maximumWaterFlowRate() const;
  bool isMaximumWaterFlowRateAutosized() const;
  bool setMaximumWaterFlowRate(double maximumWaterFlowRate);
  void autosizeMaximumWaterFlowRate();
  boost::optional<double> autosizedMaximumWaterFlowRate() const;

  double convergenceTolerance() const;
  bool setConvergenceTolerance(double convergenceTolerance);

 private:
  boost::optional<ZoneHVACBaseboardRadiantConvectiveWater> parent() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
