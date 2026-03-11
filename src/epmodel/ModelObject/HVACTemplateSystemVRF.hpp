/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATESYSTEMVRF_HPP
#define EPMODEL_HVACTEMPLATESYSTEMVRF_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HVACTemplateSystemVRF_Impl;
}

class EPMODEL_API HVACTemplateSystemVRF : public ModelObject
{
 public:
  explicit HVACTemplateSystemVRF(const Model& model);

  virtual ~HVACTemplateSystemVRF() override = default;
  HVACTemplateSystemVRF(const HVACTemplateSystemVRF& other) = default;
  HVACTemplateSystemVRF(HVACTemplateSystemVRF&& other) = default;
  HVACTemplateSystemVRF& operator=(const HVACTemplateSystemVRF&) = default;
  HVACTemplateSystemVRF& operator=(HVACTemplateSystemVRF&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> masterThermostatPriorityControlTypeValues();
  static std::vector<std::string> defrostStrategyValues();
  static std::vector<std::string> defrostControlValues();
  static std::vector<std::string> condenserTypeValues();
  static std::vector<std::string> fuelTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to HVACTemplate:System:VRF non-name, non-link scalar fields.
  // - Field Mapping: Schedule/zone object-list fields are relationship-like and excluded from scalar accessors.
  // - TODO(parity): Add relationship/object-link APIs in a later parity pass.
  boost::optional<double> grossRatedTotalCoolingCapacity() const;
  double grossRatedCoolingCOP() const;
  double minimumOutdoorTemperatureinCoolingMode() const;
  double maximumOutdoorTemperatureinCoolingMode() const;
  boost::optional<double> grossRatedHeatingCapacity() const;
  double ratedHeatingCapacitySizingRatio() const;
  double grossRatedHeatingCOP() const;
  double minimumOutdoorTemperatureinHeatingMode() const;
  double maximumOutdoorTemperatureinHeatingMode() const;
  double minimumHeatPumpPartLoadRatio() const;
  std::string masterThermostatPriorityControlType() const;
  bool heatPumpWasteHeatRecovery() const;
  double equivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode() const;
  double verticalHeightusedforPipingCorrectionFactor() const;
  double equivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode() const;
  double crankcaseHeaterPowerperCompressor() const;
  int numberofCompressors() const;
  double ratioofCompressorSizetoTotalCompressorCapacity() const;
  double maximumOutdoorDrybulbTemperatureforCrankcaseHeater() const;
  std::string defrostStrategy() const;
  std::string defrostControl() const;
  double defrostTimePeriodFraction() const;
  boost::optional<double> resistiveDefrostHeaterCapacity() const;
  double maximumOutdoorDrybulbTemperatureforDefrostOperation() const;
  std::string condenserType() const;
  boost::optional<double> waterCondenserVolumeFlowRate() const;
  double evaporativeCondenserEffectiveness() const;
  boost::optional<double> evaporativeCondenserAirFlowRate() const;
  boost::optional<double> evaporativeCondenserPumpRatedPowerConsumption() const;
  double basinHeaterCapacity() const;
  double basinHeaterSetpointTemperature() const;
  std::string fuelType() const;
  double minimumOutdoorTemperatureinHeatRecoveryMode() const;
  double maximumOutdoorTemperatureinHeatRecoveryMode() const;

  bool isGrossRatedTotalCoolingCapacityDefaulted() const;
  bool isGrossRatedCoolingCOPDefaulted() const;
  bool isMinimumOutdoorTemperatureinCoolingModeDefaulted() const;
  bool isMaximumOutdoorTemperatureinCoolingModeDefaulted() const;
  bool isGrossRatedHeatingCapacityDefaulted() const;
  bool isRatedHeatingCapacitySizingRatioDefaulted() const;
  bool isGrossRatedHeatingCOPDefaulted() const;
  bool isMinimumOutdoorTemperatureinHeatingModeDefaulted() const;
  bool isMaximumOutdoorTemperatureinHeatingModeDefaulted() const;
  bool isMinimumHeatPumpPartLoadRatioDefaulted() const;
  bool isMasterThermostatPriorityControlTypeDefaulted() const;
  bool isHeatPumpWasteHeatRecoveryDefaulted() const;
  bool isEquivalentPipingLengthusedforPipingCorrectionFactorinCoolingModeDefaulted() const;
  bool isVerticalHeightusedforPipingCorrectionFactorDefaulted() const;
  bool isEquivalentPipingLengthusedforPipingCorrectionFactorinHeatingModeDefaulted() const;
  bool isCrankcaseHeaterPowerperCompressorDefaulted() const;
  bool isNumberofCompressorsDefaulted() const;
  bool isRatioofCompressorSizetoTotalCompressorCapacityDefaulted() const;
  bool isMaximumOutdoorDrybulbTemperatureforCrankcaseHeaterDefaulted() const;
  bool isDefrostStrategyDefaulted() const;
  bool isDefrostControlDefaulted() const;
  bool isDefrostTimePeriodFractionDefaulted() const;
  bool isResistiveDefrostHeaterCapacityDefaulted() const;
  bool isMaximumOutdoorDrybulbTemperatureforDefrostOperationDefaulted() const;
  bool isCondenserTypeDefaulted() const;
  bool isWaterCondenserVolumeFlowRateDefaulted() const;
  bool isEvaporativeCondenserEffectivenessDefaulted() const;
  bool isEvaporativeCondenserAirFlowRateDefaulted() const;
  bool isEvaporativeCondenserPumpRatedPowerConsumptionDefaulted() const;
  bool isBasinHeaterCapacityDefaulted() const;
  bool isBasinHeaterSetpointTemperatureDefaulted() const;
  bool isFuelTypeDefaulted() const;
  bool isMinimumOutdoorTemperatureinHeatRecoveryModeDefaulted() const;
  bool isMaximumOutdoorTemperatureinHeatRecoveryModeDefaulted() const;
  bool isGrossRatedTotalCoolingCapacityAutosized() const;
  bool isGrossRatedHeatingCapacityAutosized() const;
  bool isResistiveDefrostHeaterCapacityAutosized() const;
  bool isWaterCondenserVolumeFlowRateAutosized() const;
  bool isEvaporativeCondenserAirFlowRateAutosized() const;
  bool isEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const;

  bool setGrossRatedTotalCoolingCapacity(double grossRatedTotalCoolingCapacity);
  bool setGrossRatedCoolingCOP(double grossRatedCoolingCOP);
  bool setMinimumOutdoorTemperatureinCoolingMode(double minimumOutdoorTemperatureinCoolingMode);
  bool setMaximumOutdoorTemperatureinCoolingMode(double maximumOutdoorTemperatureinCoolingMode);
  bool setGrossRatedHeatingCapacity(double grossRatedHeatingCapacity);
  bool setRatedHeatingCapacitySizingRatio(double ratedHeatingCapacitySizingRatio);
  bool setGrossRatedHeatingCOP(double grossRatedHeatingCOP);
  bool setMinimumOutdoorTemperatureinHeatingMode(double minimumOutdoorTemperatureinHeatingMode);
  bool setMaximumOutdoorTemperatureinHeatingMode(double maximumOutdoorTemperatureinHeatingMode);
  bool setMinimumHeatPumpPartLoadRatio(double minimumHeatPumpPartLoadRatio);
  bool setMasterThermostatPriorityControlType(const std::string& masterThermostatPriorityControlType);
  bool setHeatPumpWasteHeatRecovery(bool heatPumpWasteHeatRecovery);
  bool setEquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode(double equivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode);
  bool setVerticalHeightusedforPipingCorrectionFactor(double verticalHeightusedforPipingCorrectionFactor);
  bool setEquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode(double equivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode);
  bool setCrankcaseHeaterPowerperCompressor(double crankcaseHeaterPowerperCompressor);
  bool setNumberofCompressors(int numberofCompressors);
  bool setRatioofCompressorSizetoTotalCompressorCapacity(double ratioofCompressorSizetoTotalCompressorCapacity);
  bool setMaximumOutdoorDrybulbTemperatureforCrankcaseHeater(double maximumOutdoorDrybulbTemperatureforCrankcaseHeater);
  bool setDefrostStrategy(const std::string& defrostStrategy);
  bool setDefrostControl(const std::string& defrostControl);
  bool setDefrostTimePeriodFraction(double defrostTimePeriodFraction);
  bool setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity);
  bool setMaximumOutdoorDrybulbTemperatureforDefrostOperation(double maximumOutdoorDrybulbTemperatureforDefrostOperation);
  bool setCondenserType(const std::string& condenserType);
  bool setWaterCondenserVolumeFlowRate(double waterCondenserVolumeFlowRate);
  bool setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness);
  bool setEvaporativeCondenserAirFlowRate(double evaporativeCondenserAirFlowRate);
  bool setEvaporativeCondenserPumpRatedPowerConsumption(double evaporativeCondenserPumpRatedPowerConsumption);
  bool setBasinHeaterCapacity(double basinHeaterCapacity);
  bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);
  bool setFuelType(const std::string& fuelType);
  bool setMinimumOutdoorTemperatureinHeatRecoveryMode(double minimumOutdoorTemperatureinHeatRecoveryMode);
  bool setMaximumOutdoorTemperatureinHeatRecoveryMode(double maximumOutdoorTemperatureinHeatRecoveryMode);

  void resetGrossRatedTotalCoolingCapacity();
  void resetGrossRatedCoolingCOP();
  void resetMinimumOutdoorTemperatureinCoolingMode();
  void resetMaximumOutdoorTemperatureinCoolingMode();
  void resetGrossRatedHeatingCapacity();
  void resetRatedHeatingCapacitySizingRatio();
  void resetGrossRatedHeatingCOP();
  void resetMinimumOutdoorTemperatureinHeatingMode();
  void resetMaximumOutdoorTemperatureinHeatingMode();
  void resetMinimumHeatPumpPartLoadRatio();
  void resetMasterThermostatPriorityControlType();
  void resetHeatPumpWasteHeatRecovery();
  void resetEquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode();
  void resetVerticalHeightusedforPipingCorrectionFactor();
  void resetEquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode();
  void resetCrankcaseHeaterPowerperCompressor();
  void resetNumberofCompressors();
  void resetRatioofCompressorSizetoTotalCompressorCapacity();
  void resetMaximumOutdoorDrybulbTemperatureforCrankcaseHeater();
  void resetDefrostStrategy();
  void resetDefrostControl();
  void resetDefrostTimePeriodFraction();
  void resetResistiveDefrostHeaterCapacity();
  void resetMaximumOutdoorDrybulbTemperatureforDefrostOperation();
  void resetCondenserType();
  void resetWaterCondenserVolumeFlowRate();
  void resetEvaporativeCondenserEffectiveness();
  void resetEvaporativeCondenserAirFlowRate();
  void resetEvaporativeCondenserPumpRatedPowerConsumption();
  void resetBasinHeaterCapacity();
  void resetBasinHeaterSetpointTemperature();
  void resetFuelType();
  void resetMinimumOutdoorTemperatureinHeatRecoveryMode();
  void resetMaximumOutdoorTemperatureinHeatRecoveryMode();
  void autosizeGrossRatedTotalCoolingCapacity();
  void autosizeGrossRatedHeatingCapacity();
  void autosizeResistiveDefrostHeaterCapacity();
  void autosizeWaterCondenserVolumeFlowRate();
  void autosizeEvaporativeCondenserAirFlowRate();
  void autosizeEvaporativeCondenserPumpRatedPowerConsumption();

 protected:
  using ImplType = detail::HVACTemplateSystemVRF_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HVACTemplateSystemVRF(std::shared_ptr<detail::HVACTemplateSystemVRF_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
