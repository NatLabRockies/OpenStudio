/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXSINGLESPEEDTHERMALSTORAGE_HPP
#define EPMODEL_COILCOOLINGDXSINGLESPEEDTHERMALSTORAGE_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;
class Node;
class Schedule;

namespace detail {
class CoilCoolingDXSingleSpeedThermalStorage_Impl;
}

class EPMODEL_API CoilCoolingDXSingleSpeedThermalStorage : public StraightComponent
{
 public:
  explicit CoilCoolingDXSingleSpeedThermalStorage(const Model& model);

  virtual ~CoilCoolingDXSingleSpeedThermalStorage() override = default;
  CoilCoolingDXSingleSpeedThermalStorage(const CoilCoolingDXSingleSpeedThermalStorage& other) = default;
  CoilCoolingDXSingleSpeedThermalStorage(CoilCoolingDXSingleSpeedThermalStorage&& other) = default;
  CoilCoolingDXSingleSpeedThermalStorage& operator=(const CoilCoolingDXSingleSpeedThermalStorage&) = default;
  CoilCoolingDXSingleSpeedThermalStorage& operator=(CoilCoolingDXSingleSpeedThermalStorage&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> operatingModeControlMethodValues();
  static std::vector<std::string> storageTypeValues();
  static std::vector<std::string> condenserTypeValues();

  // Schema Alignment Notes:
  // - Status: Partial Parity. The scalar thermal-storage surface, bounded schedule relationships, and the current epmodel supply-side air-loop
  //   insertion path are present, but the wider storage relationship and topology surface is still missing.
  // - Canonical Counterpart: openstudio::model::CoilCoolingDXSingleSpeedThermalStorage.
  // - Implemented Parity: The scalar operating-mode, storage, glycol, and capacity helpers preserve the canonical naming and autosize behavior;
  //   `availabilitySchedule`, `operationModeControlSchedule`, and `basinHeaterAvailabilitySchedule` are exposed, and the current supply-side
  //   air-loop `addToNode` path preserves the bounded canonical slice used by current epmodel loop insertion.
  // - Documented Delta: The broader curve, tank-link, and storage-topology helpers from canonical
  //   `openstudio::model::CoilCoolingDXSingleSpeedThermalStorage` are not exposed yet.
  // - Field/Storage Mapping: `glycolConcentration` is preserved through the user-defined fluid type encoding because EnergyPlus has no direct concentration field.
  // - Evidence: `src/model/CoilCoolingDXSingleSpeedThermalStorage.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingDXSingleSpeedThermalStorage.cpp`, and `src/epmodel/test/CoilCoolingDXSingleSpeedThermalStorage_GTest.cpp`.
  // - Remaining Parity Work: Add the omitted curve, tank-link, and broader storage relationship helpers without changing the preserved scalar
  //   signatures.
  Schedule availabilitySchedule() const;
  bool setAvailabilitySchedule(Schedule& schedule);

  std::string operatingModeControlMethod() const;
  bool setOperatingModeControlMethod(const std::string& operatingModeControlMethod);

  boost::optional<Schedule> operationModeControlSchedule() const;
  bool setOperationModeControlSchedule(Schedule& schedule);
  void resetOperationModeControlSchedule();

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

  boost::optional<Schedule> basinHeaterAvailabilitySchedule() const;
  bool setBasinHeaterAvailabilitySchedule(Schedule& schedule);
  void resetBasinHeaterAvailabilitySchedule();

  bool addToNode(Node& node);

 protected:
  using ImplType = detail::CoilCoolingDXSingleSpeedThermalStorage_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilCoolingDXSingleSpeedThermalStorage(std::shared_ptr<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
