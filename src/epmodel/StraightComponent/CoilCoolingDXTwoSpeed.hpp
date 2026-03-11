/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXTWOSPEED_HPP
#define EPMODEL_COILCOOLINGDXTWOSPEED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;
class Node;

namespace detail {
class CoilCoolingDXTwoSpeed_Impl;
}

class EPMODEL_API CoilCoolingDXTwoSpeed : public StraightComponent
{
 public:
  explicit CoilCoolingDXTwoSpeed(const Model& model);

  virtual ~CoilCoolingDXTwoSpeed() override = default;
  CoilCoolingDXTwoSpeed(const CoilCoolingDXTwoSpeed& other) = default;
  CoilCoolingDXTwoSpeed(CoilCoolingDXTwoSpeed&& other) = default;
  CoilCoolingDXTwoSpeed& operator=(const CoilCoolingDXTwoSpeed&) = default;
  CoilCoolingDXTwoSpeed& operator=(CoilCoolingDXTwoSpeed&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> condenserTypeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::CoilCoolingDXTwoSpeed scalar accessor names/signatures.
  // - Field Mapping: APIs below map to EnergyPlus Coil:Cooling:DX:TwoSpeed scalar fields.
  // - Field Mapping: relationship-like fields (schedules, curves, node links, and tank links) are excluded.
  // - ForwardTranslator evidence: ForwardTranslateCoilCoolingDXTwoSpeed.cpp writes these scalar fields directly.
  // - TODO(parity): Add excluded relationship APIs in follow-up without changing preserved scalar signatures.
  boost::optional<double> ratedHighSpeedTotalCoolingCapacity() const;
  bool isRatedHighSpeedTotalCoolingCapacityAutosized() const;
  bool setRatedHighSpeedTotalCoolingCapacity(double ratedHighSpeedTotalCoolingCapacity);
  void autosizeRatedHighSpeedTotalCoolingCapacity();

  boost::optional<double> ratedHighSpeedSensibleHeatRatio() const;
  bool isRatedHighSpeedSensibleHeatRatioAutosized() const;
  bool setRatedHighSpeedSensibleHeatRatio(double ratedHighSpeedSensibleHeatRatio);
  void autosizeRatedHighSpeedSensibleHeatRatio();

  double ratedHighSpeedCOP() const;
  bool setRatedHighSpeedCOP(double ratedHighSpeedCOP);

  boost::optional<double> ratedHighSpeedAirFlowRate() const;
  bool isRatedHighSpeedAirFlowRateAutosized() const;
  bool setRatedHighSpeedAirFlowRate(double ratedHighSpeedAirFlowRate);
  void autosizeRatedHighSpeedAirFlowRate();

  double ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017() const;
  bool setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017(double ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017);

  double ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023() const;
  bool setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023(double ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023);

  boost::optional<double> ratedLowSpeedTotalCoolingCapacity() const;
  bool isRatedLowSpeedTotalCoolingCapacityAutosized() const;
  bool setRatedLowSpeedTotalCoolingCapacity(double ratedLowSpeedTotalCoolingCapacity);
  void autosizeRatedLowSpeedTotalCoolingCapacity();

  boost::optional<double> ratedLowSpeedSensibleHeatRatio() const;
  bool isRatedLowSpeedSensibleHeatRatioAutosized() const;
  bool setRatedLowSpeedSensibleHeatRatio(double ratedLowSpeedSensibleHeatRatio);
  void autosizeRatedLowSpeedSensibleHeatRatio();

  double ratedLowSpeedCOP() const;
  bool setRatedLowSpeedCOP(double ratedLowSpeedCOP);

  boost::optional<double> ratedLowSpeedAirFlowRate() const;
  bool isRatedLowSpeedAirFlowRateAutosized() const;
  bool setRatedLowSpeedAirFlowRate(double ratedLowSpeedAirFlowRate);
  void autosizeRatedLowSpeedAirFlowRate();

  double ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017() const;
  bool setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017(double ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017);

  double ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023() const;
  bool setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023(double ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023);

  std::string condenserType() const;
  bool setCondenserType(const std::string& condenserType);

  double highSpeedEvaporativeCondenserEffectiveness() const;
  bool setHighSpeedEvaporativeCondenserEffectiveness(double highSpeedEvaporativeCondenserEffectiveness);

  boost::optional<double> highSpeedEvaporativeCondenserAirFlowRate() const;
  bool isHighSpeedEvaporativeCondenserAirFlowRateAutosized() const;
  bool setHighSpeedEvaporativeCondenserAirFlowRate(double highSpeedEvaporativeCondenserAirFlowRate);
  void autosizeHighSpeedEvaporativeCondenserAirFlowRate();

  boost::optional<double> highSpeedEvaporativeCondenserPumpRatedPowerConsumption() const;
  bool isHighSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const;
  bool setHighSpeedEvaporativeCondenserPumpRatedPowerConsumption(double highSpeedEvaporativeCondenserPumpRatedPowerConsumption);
  void autosizeHighSpeedEvaporativeCondenserPumpRatedPowerConsumption();

  double lowSpeedEvaporativeCondenserEffectiveness() const;
  bool setLowSpeedEvaporativeCondenserEffectiveness(double lowSpeedEvaporativeCondenserEffectiveness);

  boost::optional<double> lowSpeedEvaporativeCondenserAirFlowRate() const;
  bool isLowSpeedEvaporativeCondenserAirFlowRateAutosized() const;
  bool setLowSpeedEvaporativeCondenserAirFlowRate(double lowSpeedEvaporativeCondenserAirFlowRate);
  void autosizeLowSpeedEvaporativeCondenserAirFlowRate();

  boost::optional<double> lowSpeedEvaporativeCondenserPumpRatedPowerConsumption() const;
  bool isLowSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const;
  bool setLowSpeedEvaporativeCondenserPumpRatedPowerConsumption(double lowSpeedEvaporativeCondenserPumpRatedPowerConsumption);
  void autosizeLowSpeedEvaporativeCondenserPumpRatedPowerConsumption();

  double basinHeaterCapacity() const;
  bool setBasinHeaterCapacity(double basinHeaterCapacity);

  double basinHeaterSetpointTemperature() const;
  bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);

  double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
  bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);

  double unitInternalStaticAirPressure() const;
  bool setUnitInternalStaticAirPressure(double unitInternalStaticAirPressure);

  bool addToNode(Node& node);

 protected:
  using ImplType = detail::CoilCoolingDXTwoSpeed_Impl;

  friend class Model;

  explicit CoilCoolingDXTwoSpeed(std::shared_ptr<detail::CoilCoolingDXTwoSpeed_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
