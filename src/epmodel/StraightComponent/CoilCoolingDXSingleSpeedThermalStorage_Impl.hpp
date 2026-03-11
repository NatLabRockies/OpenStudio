/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXSINGLESPEEDTHERMALSTORAGE_IMPL_HPP
#define EPMODEL_COILCOOLINGDXSINGLESPEEDTHERMALSTORAGE_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
class Node;
namespace detail {

class EPMODEL_API CoilCoolingDXSingleSpeedThermalStorage_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~CoilCoolingDXSingleSpeedThermalStorage_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  std::vector<std::string> operatingModeControlMethodValues() const;
  std::vector<std::string> storageTypeValues() const;
  std::vector<std::string> condenserTypeValues() const;

  std::string operatingModeControlMethod() const;
  bool setOperatingModeControlMethod(const std::string& operatingModeControlMethod);

  std::string storageType() const;
  bool setStorageType(const std::string& storageType);

  int glycolConcentration() const;
  bool setGlycolConcentration(int glycolConcentration);

  boost::optional<double> fluidStorageVolume() const;
  bool isFluidStorageVolumeAutosized() const;
  bool setFluidStorageVolume(double fluidStorageVolume);
  void resetFluidStorageVolume();
  void autosizeFluidStorageVolume();

  boost::optional<double> iceStorageCapacity() const;
  bool isIceStorageCapacityAutosized() const;
  bool setIceStorageCapacity(double iceStorageCapacity);
  void autosizeIceStorageCapacity();

  boost::optional<double> storageCapacitySizingFactor() const;
  bool setStorageCapacitySizingFactor(double storageCapacitySizingFactor);

  double storageTanktoAmbientUvalueTimesAreaHeatTransferCoefficient() const;
  bool setStorageTanktoAmbientUvalueTimesAreaHeatTransferCoefficient(double storageTanktoAmbientUvalueTimesAreaHeatTransferCoefficient);

  double fluidStorageTankRatingTemperature() const;
  bool setFluidStorageTankRatingTemperature(double fluidStorageTankRatingTemperature);

  boost::optional<double> ratedEvaporatorAirFlowRate() const;
  bool isRatedEvaporatorAirFlowRateAutosized() const;
  bool setRatedEvaporatorAirFlowRate(double ratedEvaporatorAirFlowRate);
  void autosizeRatedEvaporatorAirFlowRate();

  bool coolingOnlyModeAvailable() const;
  bool setCoolingOnlyModeAvailable(bool coolingOnlyModeAvailable);

  boost::optional<double> coolingOnlyModeRatedTotalEvaporatorCoolingCapacity() const;
  bool isCoolingOnlyModeRatedTotalEvaporatorCoolingCapacityAutosized() const;
  bool setCoolingOnlyModeRatedTotalEvaporatorCoolingCapacity(double coolingOnlyModeRatedTotalEvaporatorCoolingCapacity);
  void autosizeCoolingOnlyModeRatedTotalEvaporatorCoolingCapacity();

  double coolingOnlyModeRatedSensibleHeatRatio() const;
  bool setCoolingOnlyModeRatedSensibleHeatRatio(double coolingOnlyModeRatedSensibleHeatRatio);

  double coolingOnlyModeRatedCOP() const;
  bool setCoolingOnlyModeRatedCOP(double coolingOnlyModeRatedCOP);

  bool coolingAndChargeModeAvailable() const;
  bool setCoolingAndChargeModeAvailable(bool coolingAndChargeModeAvailable);

  boost::optional<double> coolingAndChargeModeRatedTotalEvaporatorCoolingCapacity() const;
  bool isCoolingAndChargeModeRatedTotalEvaporatorCoolingCapacityAutosized() const;
  bool setCoolingAndChargeModeRatedTotalEvaporatorCoolingCapacity(double coolingAndChargeModeRatedTotalEvaporatorCoolingCapacity);
  void autosizeCoolingAndChargeModeRatedTotalEvaporatorCoolingCapacity();

  double coolingAndChargeModeCapacitySizingFactor() const;
  bool setCoolingAndChargeModeCapacitySizingFactor(double coolingAndChargeModeCapacitySizingFactor);

  boost::optional<double> coolingAndChargeModeRatedStorageChargingCapacity() const;
  bool isCoolingAndChargeModeRatedStorageChargingCapacityAutosized() const;
  bool setCoolingAndChargeModeRatedStorageChargingCapacity(double coolingAndChargeModeRatedStorageChargingCapacity);
  void autosizeCoolingAndChargeModeRatedStorageChargingCapacity();

  double coolingAndChargeModeStorageCapacitySizingFactor() const;
  bool setCoolingAndChargeModeStorageCapacitySizingFactor(double coolingAndChargeModeStorageCapacitySizingFactor);

  double coolingAndChargeModeRatedSensibleHeatRatio() const;
  bool setCoolingAndChargeModeRatedSensibleHeatRatio(double coolingAndChargeModeRatedSensibleHeatRatio);

  double coolingAndChargeModeCoolingRatedCOP() const;
  bool setCoolingAndChargeModeCoolingRatedCOP(double coolingAndChargeModeCoolingRatedCOP);

  double coolingAndChargeModeChargingRatedCOP() const;
  bool setCoolingAndChargeModeChargingRatedCOP(double coolingAndChargeModeChargingRatedCOP);

  bool coolingAndDischargeModeAvailable() const;
  bool setCoolingAndDischargeModeAvailable(bool coolingAndDischargeModeAvailable);

  boost::optional<double> coolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity() const;
  bool isCoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacityAutosized() const;
  bool setCoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity(double coolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity);
  void autosizeCoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity();

  double coolingAndDischargeModeEvaporatorCapacitySizingFactor() const;
  bool setCoolingAndDischargeModeEvaporatorCapacitySizingFactor(double coolingAndDischargeModeEvaporatorCapacitySizingFactor);

  boost::optional<double> coolingAndDischargeModeRatedStorageDischargingCapacity() const;
  bool isCoolingAndDischargeModeRatedStorageDischargingCapacityAutosized() const;
  bool setCoolingAndDischargeModeRatedStorageDischargingCapacity(double coolingAndDischargeModeRatedStorageDischargingCapacity);
  void autosizeCoolingAndDischargeModeRatedStorageDischargingCapacity();

  double coolingAndDischargeModeStorageDischargeCapacitySizingFactor() const;
  bool setCoolingAndDischargeModeStorageDischargeCapacitySizingFactor(double coolingAndDischargeModeStorageDischargeCapacitySizingFactor);

  double coolingAndDischargeModeRatedSensibleHeatRatio() const;
  bool setCoolingAndDischargeModeRatedSensibleHeatRatio(double coolingAndDischargeModeRatedSensibleHeatRatio);

  double coolingAndDischargeModeCoolingRatedCOP() const;
  bool setCoolingAndDischargeModeCoolingRatedCOP(double coolingAndDischargeModeCoolingRatedCOP);

  double coolingAndDischargeModeDischargingRatedCOP() const;
  bool setCoolingAndDischargeModeDischargingRatedCOP(double coolingAndDischargeModeDischargingRatedCOP);

  bool chargeOnlyModeAvailable() const;
  bool setChargeOnlyModeAvailable(bool chargeOnlyModeAvailable);

  boost::optional<double> chargeOnlyModeRatedStorageChargingCapacity() const;
  bool isChargeOnlyModeRatedStorageChargingCapacityAutosized() const;
  bool setChargeOnlyModeRatedStorageChargingCapacity(double chargeOnlyModeRatedStorageChargingCapacity);
  void autosizeChargeOnlyModeRatedStorageChargingCapacity();

  double chargeOnlyModeCapacitySizingFactor() const;
  bool setChargeOnlyModeCapacitySizingFactor(double chargeOnlyModeCapacitySizingFactor);

  double chargeOnlyModeChargingRatedCOP() const;
  bool setChargeOnlyModeChargingRatedCOP(double chargeOnlyModeChargingRatedCOP);

  bool dischargeOnlyModeAvailable() const;
  bool setDischargeOnlyModeAvailable(bool dischargeOnlyModeAvailable);

  boost::optional<double> dischargeOnlyModeRatedStorageDischargingCapacity() const;
  bool isDischargeOnlyModeRatedStorageDischargingCapacityAutosized() const;
  bool setDischargeOnlyModeRatedStorageDischargingCapacity(double dischargeOnlyModeRatedStorageDischargingCapacity);
  void autosizeDischargeOnlyModeRatedStorageDischargingCapacity();

  double dischargeOnlyModeCapacitySizingFactor() const;
  bool setDischargeOnlyModeCapacitySizingFactor(double dischargeOnlyModeCapacitySizingFactor);

  double dischargeOnlyModeRatedSensibleHeatRatio() const;
  bool setDischargeOnlyModeRatedSensibleHeatRatio(double dischargeOnlyModeRatedSensibleHeatRatio);

  double dischargeOnlyModeRatedCOP() const;
  bool setDischargeOnlyModeRatedCOP(double dischargeOnlyModeRatedCOP);

  boost::optional<double> ancillaryElectricPower() const;
  bool setAncillaryElectricPower(double ancillaryElectricPower);

  boost::optional<double> coldWeatherOperationMinimumOutdoorAirTemperature() const;
  bool setColdWeatherOperationMinimumOutdoorAirTemperature(double coldWeatherOperationMinimumOutdoorAirTemperature);
  void resetColdWeatherOperationMinimumOutdoorAirTemperature();

  boost::optional<double> coldWeatherOperationAncillaryPower() const;
  bool setColdWeatherOperationAncillaryPower(double coldWeatherOperationAncillaryPower);

  boost::optional<double> condenserDesignAirFlowRate() const;
  bool isCondenserDesignAirFlowRateAutosized() const;
  bool setCondenserDesignAirFlowRate(double condenserDesignAirFlowRate);
  void autosizeCondenserDesignAirFlowRate();

  double condenserAirFlowSizingFactor() const;
  bool setCondenserAirFlowSizingFactor(double condenserAirFlowSizingFactor);

  std::string condenserType() const;
  bool setCondenserType(const std::string& condenserType);

  double evaporativeCondenserEffectiveness() const;
  bool setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness);

  boost::optional<double> evaporativeCondenserPumpRatedPowerConsumption() const;
  bool isEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const;
  bool setEvaporativeCondenserPumpRatedPowerConsumption(double evaporativeCondenserPumpRatedPowerConsumption);
  void autosizeEvaporativeCondenserPumpRatedPowerConsumption();

  double basinHeaterCapacity() const;
  bool setBasinHeaterCapacity(double basinHeaterCapacity);

  double basinHeaterSetpointTemperature() const;
  bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);

  bool addToNode(Node& node);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
