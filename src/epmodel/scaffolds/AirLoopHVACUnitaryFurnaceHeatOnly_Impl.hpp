/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACUNITARYFURNACEHEATONLY_IMPL_HPP
#define EPMODEL_AIRLOOPHVACUNITARYFURNACEHEATONLY_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirLoopHVACUnitaryFurnaceHeatOnly_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirLoopHVACUnitaryFurnaceHeatOnly_Impl() override = default;

  boost::optional<double> maximumSupplyAirTemperature() const;
  bool isMaximumSupplyAirTemperatureDefaulted() const;
  bool isMaximumSupplyAirTemperatureAutosized() const;
  bool setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature);
  void resetMaximumSupplyAirTemperature();
  void autosizeMaximumSupplyAirTemperature();

  boost::optional<double> heatingSupplyAirFlowRate() const;
  bool isHeatingSupplyAirFlowRateAutosized() const;
  bool setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate);
  void autosizeHeatingSupplyAirFlowRate();

  std::string supplyFanObjectType() const;
  bool setSupplyFanObjectType(const std::string& supplyFanObjectType);

  std::string fanPlacement() const;
  bool setFanPlacement(const std::string& fanPlacement);
  bool isFanPlacementDefaulted() const;
  void resetFanPlacement();

  std::string heatingCoilObjectType() const;
  bool setHeatingCoilObjectType(const std::string& heatingCoilObjectType);

  std::vector<std::string> supplyFanObjectTypeValues() const;
  std::vector<std::string> fanPlacementValues() const;
  std::vector<std::string> heatingCoilObjectTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
