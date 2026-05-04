/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXSINGLESPEED_HPP
#define EPMODEL_COILCOOLINGDXSINGLESPEED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;
class Node;
class Schedule;
class Curve;

namespace detail {
class CoilCoolingDXSingleSpeed_Impl;
}

class EPMODEL_API CoilCoolingDXSingleSpeed : public StraightComponent
{
 public:
  explicit CoilCoolingDXSingleSpeed(const Model& model);
  explicit CoilCoolingDXSingleSpeed(const Model& model, Schedule& availabilitySchedule, const Curve& coolingCurveFofTemp,
                                    const Curve& coolingCurveFofFlow, const Curve& energyInputRatioFofTemp,
                                    const Curve& energyInputRatioFofFlow, const Curve& partLoadFraction);

  virtual ~CoilCoolingDXSingleSpeed() override = default;
  CoilCoolingDXSingleSpeed(const CoilCoolingDXSingleSpeed& other) = default;
  CoilCoolingDXSingleSpeed(CoilCoolingDXSingleSpeed&& other) = default;
  CoilCoolingDXSingleSpeed& operator=(const CoilCoolingDXSingleSpeed&) = default;
  CoilCoolingDXSingleSpeed& operator=(CoilCoolingDXSingleSpeed&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> condenserTypeValues();

  // Schema Alignment Notes:
  // - Status: Partial Parity. The canonical scalar DX-coil surface plus the required schedule / curve relationships and the current epmodel
  //   supply-side air-loop insertion path are present, while condenser-air-node, AFN, tank-link, and broader OA / DOAS topology helpers remain
  //   out of scope.
  // - Canonical Counterpart: openstudio::model::CoilCoolingDXSingleSpeed.
  // - Implemented Parity: The scalar rated/capacity/efficiency and evaporative-condenser APIs preserve the canonical naming, defaults, autosize
  //   behavior, and 2017/2023 fan-power variants; `availabilitySchedule`, the five required performance curves, optional crankcase and basin
  //   schedule links, the relationship constructor, and the current supply-side air-loop `addToNode` path preserve the bounded canonical slice.
  // - Documented Delta: Condenser-air node, AFN, tank-link, and broader OA / DOAS topology helpers from canonical
  //   `openstudio::model::CoilCoolingDXSingleSpeed` are not exposed yet.
  // - Field/Storage Mapping: Preserved scalars and relationships map directly to EnergyPlus `Coil:Cooling:DX:SingleSpeed` fields.
  // - Evidence: `src/model/CoilCoolingDXSingleSpeed.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingDXSingleSpeed.cpp`, and `src/epmodel/test/CoilCoolingDXSingleSpeed_GTest.cpp`.
  // - Remaining Parity Work: Add condenser-air-node, AFN, tank-link, and broader OA / DOAS topology helpers without changing the preserved
  //   scalar signatures.
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

  boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve() const;
  bool setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve);
  void resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();

  boost::optional<Schedule> basinHeaterOperatingSchedule() const;
  bool setBasinHeaterOperatingSchedule(Schedule& schedule);
  void resetBasinHeaterOperatingSchedule();

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

  double maximumOutdoorDryBulbTemperatureForCrankcaseHeaterOperation() const;
  bool setMaximumOutdoorDryBulbTemperatureForCrankcaseHeaterOperation(double maximumOutdoorDryBulbTemperatureForCrankcaseHeaterOperation);

  double basinHeaterCapacity() const;
  bool setBasinHeaterCapacity(double basinHeaterCapacity);

  double basinHeaterSetpointTemperature() const;
  bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);

  double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
  bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);

  bool addToNode(Node& node);

 protected:
  using ImplType = detail::CoilCoolingDXSingleSpeed_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilCoolingDXSingleSpeed(std::shared_ptr<detail::CoilCoolingDXSingleSpeed_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
