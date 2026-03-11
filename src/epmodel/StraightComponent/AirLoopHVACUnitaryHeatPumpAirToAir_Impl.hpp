/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACUNITARYHEATPUMPAIRTOAIR_IMPL_HPP
#define EPMODEL_AIRLOOPHVACUNITARYHEATPUMPAIRTOAIR_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirLoopHVACUnitaryHeatPumpAirToAir_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirLoopHVACUnitaryHeatPumpAirToAir_Impl() override = default;

  boost::optional<double> supplyAirFlowRateDuringCoolingOperation() const;
  bool isSupplyAirFlowRateDuringCoolingOperationAutosized() const;
  bool setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation);
  void autosizeSupplyAirFlowRateDuringCoolingOperation();

  boost::optional<double> supplyAirFlowRateDuringHeatingOperation() const;
  bool isSupplyAirFlowRateDuringHeatingOperationAutosized() const;
  bool setSupplyAirFlowRateDuringHeatingOperation(double n2);
  void autosizeSupplyAirFlowRateDuringHeatingOperation();

  boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
  bool isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
  bool setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
  void resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  void autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();

  boost::optional<double> maximumSupplyAirTemperaturefromSupplementalHeater() const;
  bool isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const;
  bool setMaximumSupplyAirTemperaturefromSupplementalHeater(double maximumSupplyAirTemperaturefromSupplementalHeater);
  void autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();

  double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const;
  bool isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const;
  bool setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
  void resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();

  std::string fanPlacement() const;
  bool isFanPlacementDefaulted() const;
  bool setFanPlacement(const std::string& fanPlacement);
  void resetFanPlacement();

  std::string dehumidificationControlType() const;
  bool isDehumidificationControlTypeDefaulted() const;
  bool setDehumidificationControlType(const std::string& dehumidificationControlType);
  void resetDehumidificationControlType();

  double dXHeatingCoilSizingRatio() const;
  bool setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio);

  std::vector<std::string> validFanPlacementValues() const;
  std::vector<std::string> validDehumidificationControlTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
