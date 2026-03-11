/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACUNITARYHEATPUMPAIRTOAIRMULTISPEED_IMPL_HPP
#define EPMODEL_AIRLOOPHVACUNITARYHEATPUMPAIRTOAIRMULTISPEED_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl() override = default;

  std::string supplyAirFanPlacement() const;
  bool setSupplyAirFanPlacement(const std::string& supplyAirFanPlacement);

  double dXHeatingCoilSizingRatio() const;
  bool setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio);

  boost::optional<double> maximumSupplyAirTemperaturefromSupplementalHeater() const;
  bool isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const;
  bool setMaximumSupplyAirTemperaturefromSupplementalHeater(double maximumSupplyAirTemperaturefromSupplementalHeater);
  void autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();

  double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const;
  bool setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);

  double auxiliaryOnCycleElectricPower() const;
  bool setAuxiliaryOnCycleElectricPower(double auxiliaryOnCycleElectricPower);

  double auxiliaryOffCycleElectricPower() const;
  bool setAuxiliaryOffCycleElectricPower(double auxiliaryOffCycleElectricPower);

  double designHeatRecoveryWaterFlowRate() const;
  bool setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate);

  double maximumTemperatureforHeatRecovery() const;
  bool setMaximumTemperatureforHeatRecovery(double maximumTemperatureforHeatRecovery);

  boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
  bool isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
  bool setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
  void autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();

  int numberofSpeedsforHeating() const;
  bool setNumberofSpeedsforHeating(int numberofSpeedsforHeating);

  int numberofSpeedsforCooling() const;
  bool setNumberofSpeedsforCooling(int numberofSpeedsforCooling);

  boost::optional<double> speed1SupplyAirFlowRateDuringHeatingOperation() const;
  bool isSpeed1SupplyAirFlowRateDuringHeatingOperationAutosized() const;
  bool setSpeed1SupplyAirFlowRateDuringHeatingOperation(double speed1SupplyAirFlowRateDuringHeatingOperation);
  void autosizeSpeed1SupplyAirFlowRateDuringHeatingOperation();

  boost::optional<double> speed2SupplyAirFlowRateDuringHeatingOperation() const;
  bool isSpeed2SupplyAirFlowRateDuringHeatingOperationAutosized() const;
  bool setSpeed2SupplyAirFlowRateDuringHeatingOperation(double speed2SupplyAirFlowRateDuringHeatingOperation);
  void autosizeSpeed2SupplyAirFlowRateDuringHeatingOperation();

  boost::optional<double> speed3SupplyAirFlowRateDuringHeatingOperation() const;
  bool isSpeed3SupplyAirFlowRateDuringHeatingOperationAutosized() const;
  bool setSpeed3SupplyAirFlowRateDuringHeatingOperation(double speed3SupplyAirFlowRateDuringHeatingOperation);
  void autosizeSpeed3SupplyAirFlowRateDuringHeatingOperation();

  boost::optional<double> speed4SupplyAirFlowRateDuringHeatingOperation() const;
  bool isSpeed4SupplyAirFlowRateDuringHeatingOperationAutosized() const;
  bool setSpeed4SupplyAirFlowRateDuringHeatingOperation(double speed4SupplyAirFlowRateDuringHeatingOperation);
  void autosizeSpeed4SupplyAirFlowRateDuringHeatingOperation();

  boost::optional<double> speed1SupplyAirFlowRateDuringCoolingOperation() const;
  bool isSpeed1SupplyAirFlowRateDuringCoolingOperationAutosized() const;
  bool setSpeed1SupplyAirFlowRateDuringCoolingOperation(double speed1SupplyAirFlowRateDuringCoolingOperation);
  void autosizeSpeed1SupplyAirFlowRateDuringCoolingOperation();

  boost::optional<double> speed2SupplyAirFlowRateDuringCoolingOperation() const;
  bool isSpeed2SupplyAirFlowRateDuringCoolingOperationAutosized() const;
  bool setSpeed2SupplyAirFlowRateDuringCoolingOperation(double speed2SupplyAirFlowRateDuringCoolingOperation);
  void autosizeSpeed2SupplyAirFlowRateDuringCoolingOperation();

  boost::optional<double> speed3SupplyAirFlowRateDuringCoolingOperation() const;
  bool isSpeed3SupplyAirFlowRateDuringCoolingOperationAutosized() const;
  bool setSpeed3SupplyAirFlowRateDuringCoolingOperation(double speed3SupplyAirFlowRateDuringCoolingOperation);
  void autosizeSpeed3SupplyAirFlowRateDuringCoolingOperation();

  boost::optional<double> speed4SupplyAirFlowRateDuringCoolingOperation() const;
  bool isSpeed4SupplyAirFlowRateDuringCoolingOperationAutosized() const;
  bool setSpeed4SupplyAirFlowRateDuringCoolingOperation(double speed4SupplyAirFlowRateDuringCoolingOperation);
  void autosizeSpeed4SupplyAirFlowRateDuringCoolingOperation();

  std::vector<std::string> supplyAirFanPlacementValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
