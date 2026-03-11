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

namespace detail {
class CoilCoolingDXSingleSpeed_Impl;
}

class EPMODEL_API CoilCoolingDXSingleSpeed : public StraightComponent
{
 public:
  explicit CoilCoolingDXSingleSpeed(const Model& model);

  virtual ~CoilCoolingDXSingleSpeed() override = default;
  CoilCoolingDXSingleSpeed(const CoilCoolingDXSingleSpeed& other) = default;
  CoilCoolingDXSingleSpeed(CoilCoolingDXSingleSpeed&& other) = default;
  CoilCoolingDXSingleSpeed& operator=(const CoilCoolingDXSingleSpeed&) = default;
  CoilCoolingDXSingleSpeed& operator=(CoilCoolingDXSingleSpeed&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> condenserTypeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::CoilCoolingDXSingleSpeed scalar accessor naming/signatures where implemented.
  // - Field Mapping: Scalar APIs below map to EnergyPlus Coil:Cooling:DX:SingleSpeed scalar fields.
  // - Field Mapping: Relationship-like fields (schedules, curves, node links, and tank links) are excluded in this pass.
  // - ForwardTranslator evidence: ForwardTranslateCoilCoolingDXSingleSpeed.cpp writes these scalar fields directly.
  // - TODO(parity): Add remaining relationship APIs without changing preserved signatures.
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

  explicit CoilCoolingDXSingleSpeed(std::shared_ptr<detail::CoilCoolingDXSingleSpeed_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
