/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERCOMBUSTIONTURBINE_IMPL_HPP
#define EPMODEL_CHILLERCOMBUSTIONTURBINE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API ChillerCombustionTurbine_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ChillerCombustionTurbine_Impl() override = default;

  std::string condenserType() const;
  bool isCondenserTypeDefaulted() const;
  bool setCondenserType(const std::string& condenserType);
  void resetCondenserType();

  boost::optional<double> nominalCapacity() const;
  bool isNominalCapacityAutosized() const;
  bool setNominalCapacity(double nominalCapacity);
  void autosizeNominalCapacity();

  double nominalCOP() const;
  bool setNominalCOP(double nominalCOP);

  boost::optional<double> minimumPartLoadRatio() const;
  bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
  void resetMinimumPartLoadRatio();

  boost::optional<double> maximumPartLoadRatio() const;
  bool setMaximumPartLoadRatio(double maximumPartLoadRatio);
  void resetMaximumPartLoadRatio();

  boost::optional<double> optimumPartLoadRatio() const;
  bool setOptimumPartLoadRatio(double optimumPartLoadRatio);
  void resetOptimumPartLoadRatio();

  boost::optional<double> designCondenserInletTemperature() const;
  bool setDesignCondenserInletTemperature(double designCondenserInletTemperature);
  void resetDesignCondenserInletTemperature();

  double temperatureRiseCoefficient() const;
  bool setTemperatureRiseCoefficient(double temperatureRiseCoefficient);

  boost::optional<double> designChilledWaterOutletTemperature() const;
  bool setDesignChilledWaterOutletTemperature(double designChilledWaterOutletTemperature);
  void resetDesignChilledWaterOutletTemperature();

  boost::optional<double> designChilledWaterFlowRate() const;
  bool isDesignChilledWaterFlowRateAutosized() const;
  bool setDesignChilledWaterFlowRate(double designChilledWaterFlowRate);
  void resetDesignChilledWaterFlowRate();
  void autosizeDesignChilledWaterFlowRate();

  boost::optional<double> designCondenserWaterFlowRate() const;
  bool isDesignCondenserWaterFlowRateAutosized() const;
  bool setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate);
  void resetDesignCondenserWaterFlowRate();
  void autosizeDesignCondenserWaterFlowRate();

  boost::optional<double> coefficient1ofCapacityRatioCurve() const;
  bool setCoefficient1ofCapacityRatioCurve(double coefficient1ofCapacityRatioCurve);
  void resetCoefficient1ofCapacityRatioCurve();

  boost::optional<double> coefficient2ofCapacityRatioCurve() const;
  bool setCoefficient2ofCapacityRatioCurve(double coefficient2ofCapacityRatioCurve);
  void resetCoefficient2ofCapacityRatioCurve();

  boost::optional<double> coefficient3ofCapacityRatioCurve() const;
  bool setCoefficient3ofCapacityRatioCurve(double coefficient3ofCapacityRatioCurve);
  void resetCoefficient3ofCapacityRatioCurve();

  boost::optional<double> coefficient1ofPowerRatioCurve() const;
  bool setCoefficient1ofPowerRatioCurve(double coefficient1ofPowerRatioCurve);
  void resetCoefficient1ofPowerRatioCurve();

  boost::optional<double> coefficient2ofPowerRatioCurve() const;
  bool setCoefficient2ofPowerRatioCurve(double coefficient2ofPowerRatioCurve);
  void resetCoefficient2ofPowerRatioCurve();

  boost::optional<double> coefficient3ofPowerRatioCurve() const;
  bool setCoefficient3ofPowerRatioCurve(double coefficient3ofPowerRatioCurve);
  void resetCoefficient3ofPowerRatioCurve();

  boost::optional<double> coefficient1ofFullLoadRatioCurve() const;
  bool setCoefficient1ofFullLoadRatioCurve(double coefficient1ofFullLoadRatioCurve);
  void resetCoefficient1ofFullLoadRatioCurve();

  boost::optional<double> coefficient2ofFullLoadRatioCurve() const;
  bool setCoefficient2ofFullLoadRatioCurve(double coefficient2ofFullLoadRatioCurve);
  void resetCoefficient2ofFullLoadRatioCurve();

  boost::optional<double> coefficient3ofFullLoadRatioCurve() const;
  bool setCoefficient3ofFullLoadRatioCurve(double coefficient3ofFullLoadRatioCurve);
  void resetCoefficient3ofFullLoadRatioCurve();

  boost::optional<double> chilledWaterOutletTemperatureLowerLimit() const;
  bool setChilledWaterOutletTemperatureLowerLimit(double chilledWaterOutletTemperatureLowerLimit);
  void resetChilledWaterOutletTemperatureLowerLimit();

  boost::optional<double> coefficient1ofFuelInputCurve() const;
  bool setCoefficient1ofFuelInputCurve(double coefficient1ofFuelInputCurve);
  void resetCoefficient1ofFuelInputCurve();

  boost::optional<double> coefficient2ofFuelInputCurve() const;
  bool setCoefficient2ofFuelInputCurve(double coefficient2ofFuelInputCurve);
  void resetCoefficient2ofFuelInputCurve();

  boost::optional<double> coefficient3ofFuelInputCurve() const;
  bool setCoefficient3ofFuelInputCurve(double coefficient3ofFuelInputCurve);
  void resetCoefficient3ofFuelInputCurve();

  boost::optional<double> coefficient1ofTemperatureBasedFuelInputCurve() const;
  bool setCoefficient1ofTemperatureBasedFuelInputCurve(double coefficient1ofTemperatureBasedFuelInputCurve);
  void resetCoefficient1ofTemperatureBasedFuelInputCurve();

  boost::optional<double> coefficient2ofTemperatureBasedFuelInputCurve() const;
  bool setCoefficient2ofTemperatureBasedFuelInputCurve(double coefficient2ofTemperatureBasedFuelInputCurve);
  void resetCoefficient2ofTemperatureBasedFuelInputCurve();

  boost::optional<double> coefficient3ofTemperatureBasedFuelInputCurve() const;
  bool setCoefficient3ofTemperatureBasedFuelInputCurve(double coefficient3ofTemperatureBasedFuelInputCurve);
  void resetCoefficient3ofTemperatureBasedFuelInputCurve();

  boost::optional<double> coefficient1ofExhaustFlowCurve() const;
  bool setCoefficient1ofExhaustFlowCurve(double coefficient1ofExhaustFlowCurve);
  void resetCoefficient1ofExhaustFlowCurve();

  boost::optional<double> coefficient2ofExhaustFlowCurve() const;
  bool setCoefficient2ofExhaustFlowCurve(double coefficient2ofExhaustFlowCurve);
  void resetCoefficient2ofExhaustFlowCurve();

  boost::optional<double> coefficient3ofExhaustFlowCurve() const;
  bool setCoefficient3ofExhaustFlowCurve(double coefficient3ofExhaustFlowCurve);
  void resetCoefficient3ofExhaustFlowCurve();

  boost::optional<double> coefficient1ofExhaustGasTemperatureCurve() const;
  bool setCoefficient1ofExhaustGasTemperatureCurve(double coefficient1ofExhaustGasTemperatureCurve);
  void resetCoefficient1ofExhaustGasTemperatureCurve();

  boost::optional<double> coefficient2ofExhaustGasTemperatureCurve() const;
  bool setCoefficient2ofExhaustGasTemperatureCurve(double coefficient2ofExhaustGasTemperatureCurve);
  void resetCoefficient2ofExhaustGasTemperatureCurve();

  boost::optional<double> coefficient3ofExhaustGasTemperatureCurve() const;
  bool setCoefficient3ofExhaustGasTemperatureCurve(double coefficient3ofExhaustGasTemperatureCurve);
  void resetCoefficient3ofExhaustGasTemperatureCurve();

  boost::optional<double> coefficient1ofTemperatureBasedExhaustGasTemperatureCurve() const;
  bool setCoefficient1ofTemperatureBasedExhaustGasTemperatureCurve(double coefficient1ofTemperatureBasedExhaustGasTemperatureCurve);
  void resetCoefficient1ofTemperatureBasedExhaustGasTemperatureCurve();

  boost::optional<double> coefficient2ofTemperatureBasedExhaustGasTemperatureCurve() const;
  bool setCoefficient2ofTemperatureBasedExhaustGasTemperatureCurve(double coefficient2ofTemperatureBasedExhaustGasTemperatureCurve);
  void resetCoefficient2ofTemperatureBasedExhaustGasTemperatureCurve();

  boost::optional<double> coefficient3ofTemperatureBasedExhaustGasTemperatureCurve() const;
  bool setCoefficient3ofTemperatureBasedExhaustGasTemperatureCurve(double coefficient3ofTemperatureBasedExhaustGasTemperatureCurve);
  void resetCoefficient3ofTemperatureBasedExhaustGasTemperatureCurve();

  boost::optional<double> coefficient1ofRecoveryLubeHeatCurve() const;
  bool setCoefficient1ofRecoveryLubeHeatCurve(double coefficient1ofRecoveryLubeHeatCurve);
  void resetCoefficient1ofRecoveryLubeHeatCurve();

  boost::optional<double> coefficient2ofRecoveryLubeHeatCurve() const;
  bool setCoefficient2ofRecoveryLubeHeatCurve(double coefficient2ofRecoveryLubeHeatCurve);
  void resetCoefficient2ofRecoveryLubeHeatCurve();

  boost::optional<double> coefficient3ofRecoveryLubeHeatCurve() const;
  bool setCoefficient3ofRecoveryLubeHeatCurve(double coefficient3ofRecoveryLubeHeatCurve);
  void resetCoefficient3ofRecoveryLubeHeatCurve();

  boost::optional<double> coefficient1ofUFactorTimesAreaCurve() const;
  bool setCoefficient1ofUFactorTimesAreaCurve(double coefficient1ofUFactorTimesAreaCurve);
  void resetCoefficient1ofUFactorTimesAreaCurve();

  boost::optional<double> coefficient2ofUFactorTimesAreaCurve() const;
  bool setCoefficient2ofUFactorTimesAreaCurve(double coefficient2ofUFactorTimesAreaCurve);
  void resetCoefficient2ofUFactorTimesAreaCurve();

  boost::optional<double> gasTurbineEngineCapacity() const;
  bool isGasTurbineEngineCapacityAutosized() const;
  bool setGasTurbineEngineCapacity(double gasTurbineEngineCapacity);
  void resetGasTurbineEngineCapacity();
  void autosizeGasTurbineEngineCapacity();

  boost::optional<double> maximumExhaustFlowperUnitofPowerOutput() const;
  bool setMaximumExhaustFlowperUnitofPowerOutput(double maximumExhaustFlowperUnitofPowerOutput);
  void resetMaximumExhaustFlowperUnitofPowerOutput();

  boost::optional<double> designSteamSaturationTemperature() const;
  bool setDesignSteamSaturationTemperature(double designSteamSaturationTemperature);
  void resetDesignSteamSaturationTemperature();

  boost::optional<double> fuelHigherHeatingValue() const;
  bool setFuelHigherHeatingValue(double fuelHigherHeatingValue);
  void resetFuelHigherHeatingValue();

  boost::optional<double> designHeatRecoveryWaterFlowRate() const;
  bool isDesignHeatRecoveryWaterFlowRateDefaulted() const;
  bool isDesignHeatRecoveryWaterFlowRateAutosized() const;
  bool setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate);
  void resetDesignHeatRecoveryWaterFlowRate();
  void autosizeDesignHeatRecoveryWaterFlowRate();

  std::string chillerFlowMode() const;
  bool isChillerFlowModeDefaulted() const;
  bool setChillerFlowMode(const std::string& chillerFlowMode);
  void resetChillerFlowMode();

  std::string fuelType() const;
  bool isFuelTypeDefaulted() const;
  bool setFuelType(const std::string& fuelType);
  void resetFuelType();

  double heatRecoveryMaximumTemperature() const;
  bool isHeatRecoveryMaximumTemperatureDefaulted() const;
  bool setHeatRecoveryMaximumTemperature(double heatRecoveryMaximumTemperature);
  void resetHeatRecoveryMaximumTemperature();

  double sizingFactor() const;
  bool isSizingFactorDefaulted() const;
  bool setSizingFactor(double sizingFactor);
  void resetSizingFactor();

  double basinHeaterCapacity() const;
  bool isBasinHeaterCapacityDefaulted() const;
  bool setBasinHeaterCapacity(double basinHeaterCapacity);
  void resetBasinHeaterCapacity();

  double basinHeaterSetpointTemperature() const;
  bool isBasinHeaterSetpointTemperatureDefaulted() const;
  bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);
  void resetBasinHeaterSetpointTemperature();

  boost::optional<double> condenserHeatRecoveryRelativeCapacityFraction() const;
  bool setCondenserHeatRecoveryRelativeCapacityFraction(double condenserHeatRecoveryRelativeCapacityFraction);
  void resetCondenserHeatRecoveryRelativeCapacityFraction();

  double turbineEngineEfficiency() const;
  bool isTurbineEngineEfficiencyDefaulted() const;
  bool setTurbineEngineEfficiency(double turbineEngineEfficiency);
  void resetTurbineEngineEfficiency();

  std::vector<std::string> condenserTypeValues() const;
  std::vector<std::string> chillerFlowModeValues() const;
  std::vector<std::string> fuelTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
