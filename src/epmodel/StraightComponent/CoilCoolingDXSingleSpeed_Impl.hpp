/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXSINGLESPEED_IMPL_HPP
#define EPMODEL_COILCOOLINGDXSINGLESPEED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
class Node;
class CoilSystemCoolingDX;
class Schedule;
class Curve;
namespace detail {

class EPMODEL_API CoilCoolingDXSingleSpeed_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~CoilCoolingDXSingleSpeed_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;
  std::vector<ModelObject> children() const override;

  Schedule availabilitySchedule() const;
  bool setAvailabilitySchedule(Schedule& schedule);

  Curve totalCoolingCapacityFunctionOfTemperatureCurve() const;
  bool setTotalCoolingCapacityFunctionOfTemperatureCurve(const Curve& curve);

  Curve totalCoolingCapacityFunctionOfFlowFractionCurve() const;
  bool setTotalCoolingCapacityFunctionOfFlowFractionCurve(const Curve& curve);

  Curve energyInputRatioFunctionOfTemperatureCurve() const;
  bool setEnergyInputRatioFunctionOfTemperatureCurve(const Curve& curve);

  Curve energyInputRatioFunctionOfFlowFractionCurve() const;
  bool setEnergyInputRatioFunctionOfFlowFractionCurve(const Curve& curve);

  Curve partLoadFractionCorrelationCurve() const;
  bool setPartLoadFractionCorrelationCurve(const Curve& curve);

  std::vector<std::string> condenserTypeValues() const;
  std::string condenserType() const;
  bool setCondenserType(const std::string& condenserType);

  double ratedCOP() const;
  bool setRatedCOP(double ratedCOP);

  double ratedEvaporatorFanPowerPerVolumeFlowRate2017() const;
  bool setRatedEvaporatorFanPowerPerVolumeFlowRate2017(double ratedEvaporatorFanPowerPerVolumeFlowRate2017);

  double ratedEvaporatorFanPowerPerVolumeFlowRate2023() const;
  bool setRatedEvaporatorFanPowerPerVolumeFlowRate2023(double ratedEvaporatorFanPowerPerVolumeFlowRate2023);

  boost::optional<double> ratedTotalCoolingCapacity() const;
  bool isRatedTotalCoolingCapacityAutosized() const;
  bool setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity);
  void autosizeRatedTotalCoolingCapacity();

  boost::optional<double> ratedSensibleHeatRatio() const;
  bool isRatedSensibleHeatRatioAutosized() const;
  bool setRatedSensibleHeatRatio(double ratedSensibleHeatRatio);
  void autosizeRatedSensibleHeatRatio();

  boost::optional<double> ratedAirFlowRate() const;
  bool isRatedAirFlowRateAutosized() const;
  bool setRatedAirFlowRate(double ratedAirFlowRate);
  void autosizeRatedAirFlowRate();

  double nominalTimeForCondensateRemovalToBegin() const;
  bool setNominalTimeForCondensateRemovalToBegin(double nominalTimeForCondensateRemovalToBegin);

  double ratioOfInitialMoistureEvaporationRateAndSteadyStateLatentCapacity() const;
  bool setRatioOfInitialMoistureEvaporationRateAndSteadyStateLatentCapacity(
    double ratioOfInitialMoistureEvaporationRateAndSteadyStateLatentCapacity);

  double maximumCyclingRate() const;
  bool setMaximumCyclingRate(double maximumCyclingRate);

  double latentCapacityTimeConstant() const;
  bool setLatentCapacityTimeConstant(double latentCapacityTimeConstant);

  double evaporativeCondenserEffectiveness() const;
  bool setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness);

  boost::optional<double> evaporativeCondenserAirFlowRate() const;
  bool isEvaporativeCondenserAirFlowRateAutosized() const;
  bool setEvaporativeCondenserAirFlowRate(double evaporativeCondenserAirFlowRate);
  void autosizeEvaporativeCondenserAirFlowRate();

  boost::optional<double> evaporativeCondenserPumpRatedPowerConsumption() const;
  bool isEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const;
  bool setEvaporativeCondenserPumpRatedPowerConsumption(double evaporativeCondenserPumpRatedPowerConsumption);
  void autosizeEvaporativeCondenserPumpRatedPowerConsumption();

  double crankcaseHeaterCapacity() const;
  bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);

  boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve() const;
  bool setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve);
  void resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();

  double maximumOutdoorDryBulbTemperatureForCrankcaseHeaterOperation() const;
  bool setMaximumOutdoorDryBulbTemperatureForCrankcaseHeaterOperation(double maximumOutdoorDryBulbTemperatureForCrankcaseHeaterOperation);

  double basinHeaterCapacity() const;
  bool setBasinHeaterCapacity(double basinHeaterCapacity);

  double basinHeaterSetpointTemperature() const;
  bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);

  boost::optional<Schedule> basinHeaterOperatingSchedule() const;
  bool setBasinHeaterOperatingSchedule(Schedule& schedule);
  void resetBasinHeaterOperatingSchedule();

  double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
  bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);

  bool addToNode(Node& node);
  boost::optional<CoilSystemCoolingDX> coilSystemCoolingDX() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
