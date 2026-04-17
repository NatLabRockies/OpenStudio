/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGDXVARIABLESPEED_IMPL_HPP
#define EPMODEL_COILHEATINGDXVARIABLESPEED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
class Node;
class Schedule;
class Curve;
namespace detail {

class EPMODEL_API CoilHeatingDXVariableSpeed_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~CoilHeatingDXVariableSpeed_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;
  std::vector<ModelObject> children() const override;

  bool addToNode(Node& node) override;

  Schedule availabilitySchedule() const;
  bool setAvailabilitySchedule(Schedule& schedule);

  int nominalSpeedLevel() const;
  bool setNominalSpeedLevel(int nominalSpeedLevel);

  boost::optional<double> ratedHeatingCapacityAtSelectedNominalSpeedLevel() const;
  bool isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized() const;
  bool setRatedHeatingCapacityAtSelectedNominalSpeedLevel(double ratedHeatingCapacityAtSelectedNominalSpeedLevel);
  void autosizeRatedHeatingCapacityAtSelectedNominalSpeedLevel();

  boost::optional<double> ratedAirFlowRateAtSelectedNominalSpeedLevel() const;
  bool isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized() const;
  bool setRatedAirFlowRateAtSelectedNominalSpeedLevel(double ratedAirFlowRateAtSelectedNominalSpeedLevel);
  void autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();

  Curve energyPartLoadFractionCurve() const;
  bool setEnergyPartLoadFractionCurve(const Curve& curve);

  boost::optional<Curve> defrostEnergyInputRatioFunctionofTemperatureCurve() const;
  bool setDefrostEnergyInputRatioFunctionofTemperatureCurve(const Curve& curve);
  void resetDefrostEnergyInputRatioFunctionofTemperatureCurve();

  double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
  bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);

  boost::optional<double> outdoorDryBulbTemperaturetoTurnOnCompressor() const;
  bool setOutdoorDryBulbTemperaturetoTurnOnCompressor(double outdoorDryBulbTemperaturetoTurnOnCompressor);
  void resetOutdoorDryBulbTemperaturetoTurnOnCompressor();

  double maximumOutdoorDryBulbTemperatureforDefrostOperation() const;
  bool setMaximumOutdoorDryBulbTemperatureforDefrostOperation(double maximumOutdoorDryBulbTemperatureforDefrostOperation);

  double crankcaseHeaterCapacity() const;
  bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);

  boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve() const;
  bool setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve);
  void resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();

  double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const;
  bool setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);

  std::vector<std::string> defrostStrategyValues() const;
  std::string defrostStrategy() const;
  bool setDefrostStrategy(const std::string& defrostStrategy);

  std::vector<std::string> defrostControlValues() const;
  std::string defrostControl() const;
  bool setDefrostControl(const std::string& defrostControl);

  double defrostTimePeriodFraction() const;
  bool setDefrostTimePeriodFraction(double defrostTimePeriodFraction);

  boost::optional<double> resistiveDefrostHeaterCapacity() const;
  bool isResistiveDefrostHeaterCapacityAutosized() const;
  bool setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity);
  void autosizeResistiveDefrostHeaterCapacity();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
