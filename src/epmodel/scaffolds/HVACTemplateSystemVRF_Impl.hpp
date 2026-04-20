/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATESYSTEMVRF_IMPL_HPP
#define EPMODEL_HVACTEMPLATESYSTEMVRF_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API HVACTemplateSystemVRF_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~HVACTemplateSystemVRF_Impl() override = default;

      boost::optional<double> grossRatedTotalCoolingCapacity() const;
      bool isGrossRatedTotalCoolingCapacityDefaulted() const;
      bool isGrossRatedTotalCoolingCapacityAutosized() const;
      bool setGrossRatedTotalCoolingCapacity(double grossRatedTotalCoolingCapacity);
      void resetGrossRatedTotalCoolingCapacity();
      void autosizeGrossRatedTotalCoolingCapacity();

      double grossRatedCoolingCOP() const;
      bool isGrossRatedCoolingCOPDefaulted() const;
      bool setGrossRatedCoolingCOP(double grossRatedCoolingCOP);
      void resetGrossRatedCoolingCOP();

      double minimumOutdoorTemperatureinCoolingMode() const;
      bool isMinimumOutdoorTemperatureinCoolingModeDefaulted() const;
      bool setMinimumOutdoorTemperatureinCoolingMode(double minimumOutdoorTemperatureinCoolingMode);
      void resetMinimumOutdoorTemperatureinCoolingMode();

      double maximumOutdoorTemperatureinCoolingMode() const;
      bool isMaximumOutdoorTemperatureinCoolingModeDefaulted() const;
      bool setMaximumOutdoorTemperatureinCoolingMode(double maximumOutdoorTemperatureinCoolingMode);
      void resetMaximumOutdoorTemperatureinCoolingMode();

      boost::optional<double> grossRatedHeatingCapacity() const;
      bool isGrossRatedHeatingCapacityDefaulted() const;
      bool isGrossRatedHeatingCapacityAutosized() const;
      bool setGrossRatedHeatingCapacity(double grossRatedHeatingCapacity);
      void resetGrossRatedHeatingCapacity();
      void autosizeGrossRatedHeatingCapacity();

      double ratedHeatingCapacitySizingRatio() const;
      bool isRatedHeatingCapacitySizingRatioDefaulted() const;
      bool setRatedHeatingCapacitySizingRatio(double ratedHeatingCapacitySizingRatio);
      void resetRatedHeatingCapacitySizingRatio();

      double grossRatedHeatingCOP() const;
      bool isGrossRatedHeatingCOPDefaulted() const;
      bool setGrossRatedHeatingCOP(double grossRatedHeatingCOP);
      void resetGrossRatedHeatingCOP();

      double minimumOutdoorTemperatureinHeatingMode() const;
      bool isMinimumOutdoorTemperatureinHeatingModeDefaulted() const;
      bool setMinimumOutdoorTemperatureinHeatingMode(double minimumOutdoorTemperatureinHeatingMode);
      void resetMinimumOutdoorTemperatureinHeatingMode();

      double maximumOutdoorTemperatureinHeatingMode() const;
      bool isMaximumOutdoorTemperatureinHeatingModeDefaulted() const;
      bool setMaximumOutdoorTemperatureinHeatingMode(double maximumOutdoorTemperatureinHeatingMode);
      void resetMaximumOutdoorTemperatureinHeatingMode();

      double minimumHeatPumpPartLoadRatio() const;
      bool isMinimumHeatPumpPartLoadRatioDefaulted() const;
      bool setMinimumHeatPumpPartLoadRatio(double minimumHeatPumpPartLoadRatio);
      void resetMinimumHeatPumpPartLoadRatio();

      std::string masterThermostatPriorityControlType() const;
      bool isMasterThermostatPriorityControlTypeDefaulted() const;
      bool setMasterThermostatPriorityControlType(const std::string& masterThermostatPriorityControlType);
      void resetMasterThermostatPriorityControlType();

      bool heatPumpWasteHeatRecovery() const;
      bool isHeatPumpWasteHeatRecoveryDefaulted() const;
      bool setHeatPumpWasteHeatRecovery(bool heatPumpWasteHeatRecovery);
      void resetHeatPumpWasteHeatRecovery();

      double equivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode() const;
      bool isEquivalentPipingLengthusedforPipingCorrectionFactorinCoolingModeDefaulted() const;
      bool
        setEquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode(double equivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode);
      void resetEquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode();

      double verticalHeightusedforPipingCorrectionFactor() const;
      bool isVerticalHeightusedforPipingCorrectionFactorDefaulted() const;
      bool setVerticalHeightusedforPipingCorrectionFactor(double verticalHeightusedforPipingCorrectionFactor);
      void resetVerticalHeightusedforPipingCorrectionFactor();

      double equivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode() const;
      bool isEquivalentPipingLengthusedforPipingCorrectionFactorinHeatingModeDefaulted() const;
      bool
        setEquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode(double equivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode);
      void resetEquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode();

      double crankcaseHeaterPowerperCompressor() const;
      bool isCrankcaseHeaterPowerperCompressorDefaulted() const;
      bool setCrankcaseHeaterPowerperCompressor(double crankcaseHeaterPowerperCompressor);
      void resetCrankcaseHeaterPowerperCompressor();

      int numberofCompressors() const;
      bool isNumberofCompressorsDefaulted() const;
      bool setNumberofCompressors(int numberofCompressors);
      void resetNumberofCompressors();

      double ratioofCompressorSizetoTotalCompressorCapacity() const;
      bool isRatioofCompressorSizetoTotalCompressorCapacityDefaulted() const;
      bool setRatioofCompressorSizetoTotalCompressorCapacity(double ratioofCompressorSizetoTotalCompressorCapacity);
      void resetRatioofCompressorSizetoTotalCompressorCapacity();

      double maximumOutdoorDrybulbTemperatureforCrankcaseHeater() const;
      bool isMaximumOutdoorDrybulbTemperatureforCrankcaseHeaterDefaulted() const;
      bool setMaximumOutdoorDrybulbTemperatureforCrankcaseHeater(double maximumOutdoorDrybulbTemperatureforCrankcaseHeater);
      void resetMaximumOutdoorDrybulbTemperatureforCrankcaseHeater();

      std::string defrostStrategy() const;
      bool isDefrostStrategyDefaulted() const;
      bool setDefrostStrategy(const std::string& defrostStrategy);
      void resetDefrostStrategy();

      std::string defrostControl() const;
      bool isDefrostControlDefaulted() const;
      bool setDefrostControl(const std::string& defrostControl);
      void resetDefrostControl();

      double defrostTimePeriodFraction() const;
      bool isDefrostTimePeriodFractionDefaulted() const;
      bool setDefrostTimePeriodFraction(double defrostTimePeriodFraction);
      void resetDefrostTimePeriodFraction();

      boost::optional<double> resistiveDefrostHeaterCapacity() const;
      bool isResistiveDefrostHeaterCapacityDefaulted() const;
      bool isResistiveDefrostHeaterCapacityAutosized() const;
      bool setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity);
      void resetResistiveDefrostHeaterCapacity();
      void autosizeResistiveDefrostHeaterCapacity();

      double maximumOutdoorDrybulbTemperatureforDefrostOperation() const;
      bool isMaximumOutdoorDrybulbTemperatureforDefrostOperationDefaulted() const;
      bool setMaximumOutdoorDrybulbTemperatureforDefrostOperation(double maximumOutdoorDrybulbTemperatureforDefrostOperation);
      void resetMaximumOutdoorDrybulbTemperatureforDefrostOperation();

      std::string condenserType() const;
      bool isCondenserTypeDefaulted() const;
      bool setCondenserType(const std::string& condenserType);
      void resetCondenserType();

      boost::optional<double> waterCondenserVolumeFlowRate() const;
      bool isWaterCondenserVolumeFlowRateDefaulted() const;
      bool isWaterCondenserVolumeFlowRateAutosized() const;
      bool setWaterCondenserVolumeFlowRate(double waterCondenserVolumeFlowRate);
      void resetWaterCondenserVolumeFlowRate();
      void autosizeWaterCondenserVolumeFlowRate();

      double evaporativeCondenserEffectiveness() const;
      bool isEvaporativeCondenserEffectivenessDefaulted() const;
      bool setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness);
      void resetEvaporativeCondenserEffectiveness();

      boost::optional<double> evaporativeCondenserAirFlowRate() const;
      bool isEvaporativeCondenserAirFlowRateDefaulted() const;
      bool isEvaporativeCondenserAirFlowRateAutosized() const;
      bool setEvaporativeCondenserAirFlowRate(double evaporativeCondenserAirFlowRate);
      void resetEvaporativeCondenserAirFlowRate();
      void autosizeEvaporativeCondenserAirFlowRate();

      boost::optional<double> evaporativeCondenserPumpRatedPowerConsumption() const;
      bool isEvaporativeCondenserPumpRatedPowerConsumptionDefaulted() const;
      bool isEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const;
      bool setEvaporativeCondenserPumpRatedPowerConsumption(double evaporativeCondenserPumpRatedPowerConsumption);
      void resetEvaporativeCondenserPumpRatedPowerConsumption();
      void autosizeEvaporativeCondenserPumpRatedPowerConsumption();

      double basinHeaterCapacity() const;
      bool isBasinHeaterCapacityDefaulted() const;
      bool setBasinHeaterCapacity(double basinHeaterCapacity);
      void resetBasinHeaterCapacity();

      double basinHeaterSetpointTemperature() const;
      bool isBasinHeaterSetpointTemperatureDefaulted() const;
      bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);
      void resetBasinHeaterSetpointTemperature();

      std::string fuelType() const;
      bool isFuelTypeDefaulted() const;
      bool setFuelType(const std::string& fuelType);
      void resetFuelType();

      double minimumOutdoorTemperatureinHeatRecoveryMode() const;
      bool isMinimumOutdoorTemperatureinHeatRecoveryModeDefaulted() const;
      bool setMinimumOutdoorTemperatureinHeatRecoveryMode(double minimumOutdoorTemperatureinHeatRecoveryMode);
      void resetMinimumOutdoorTemperatureinHeatRecoveryMode();

      double maximumOutdoorTemperatureinHeatRecoveryMode() const;
      bool isMaximumOutdoorTemperatureinHeatRecoveryModeDefaulted() const;
      bool setMaximumOutdoorTemperatureinHeatRecoveryMode(double maximumOutdoorTemperatureinHeatRecoveryMode);
      void resetMaximumOutdoorTemperatureinHeatRecoveryMode();

      std::vector<std::string> masterThermostatPriorityControlTypeValues() const;
      std::vector<std::string> defrostStrategyValues() const;
      std::vector<std::string> defrostControlValues() const;
      std::vector<std::string> condenserTypeValues() const;
      std::vector<std::string> fuelTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
