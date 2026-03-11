/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGDXSINGLESPEED_IMPL_HPP
#define EPMODEL_COILHEATINGDXSINGLESPEED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API CoilHeatingDXSingleSpeed_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~CoilHeatingDXSingleSpeed_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  boost::optional<double> ratedTotalHeatingCapacity() const;
  bool isRatedTotalHeatingCapacityAutosized() const;

  double ratedCOP() const;

  boost::optional<double> ratedAirFlowRate() const;
  bool isRatedAirFlowRateAutosized() const;

  double ratedSupplyFanPowerPerVolumeFlowRate2017() const;
  double ratedSupplyFanPowerPerVolumeFlowRate2023() const;

  double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
  bool isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted() const;

  double maximumOutdoorDryBulbTemperatureforDefrostOperation() const;
  bool isMaximumOutdoorDryBulbTemperatureforDefrostOperationDefaulted() const;

  double crankcaseHeaterCapacity() const;
  bool isCrankcaseHeaterCapacityDefaulted() const;

  double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const;
  bool isMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperationDefaulted() const;

  std::vector<std::string> validDefrostStrategyValues() const;
  std::string defrostStrategy() const;
  bool isDefrostStrategyDefaulted() const;

  std::vector<std::string> validDefrostControlValues() const;
  std::string defrostControl() const;
  bool isDefrostControlDefaulted() const;

  double defrostTimePeriodFraction() const;
  bool isDefrostTimePeriodFractionDefaulted() const;

  boost::optional<double> resistiveDefrostHeaterCapacity() const;
  bool isResistiveDefrostHeaterCapacityDefaulted() const;
  bool isResistiveDefrostHeaterCapacityAutosized() const;

  bool setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity);
  void autosizeRatedTotalHeatingCapacity();

  bool setRatedCOP(double ratedCOP);

  bool setRatedAirFlowRate(double ratedAirFlowRate);
  void autosizeRatedAirFlowRate();

  bool setRatedSupplyFanPowerPerVolumeFlowRate2017(double ratedSupplyFanPowerPerVolumeFlowRate2017);
  bool setRatedSupplyFanPowerPerVolumeFlowRate2023(double ratedSupplyFanPowerPerVolumeFlowRate2023);

  bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);
  void resetMinimumOutdoorDryBulbTemperatureforCompressorOperation();

  bool setMaximumOutdoorDryBulbTemperatureforDefrostOperation(double maximumOutdoorDryBulbTemperatureforDefrostOperation);
  void resetMaximumOutdoorDryBulbTemperatureforDefrostOperation();

  bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);
  void resetCrankcaseHeaterCapacity();

  bool setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);
  void resetMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation();

  bool setDefrostStrategy(const std::string& defrostStrategy);
  void resetDefrostStrategy();

  bool setDefrostControl(const std::string& defrostControl);
  void resetDefrostControl();

  bool setDefrostTimePeriodFraction(double defrostTimePeriodFraction);
  void resetDefrostTimePeriodFraction();

  bool setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity);
  void resetResistiveDefrostHeaterCapacity();
  void autosizeResistiveDefrostHeaterCapacity();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
