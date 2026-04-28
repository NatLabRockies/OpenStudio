/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WATERHEATERMIXED_IMPL_HPP
#define EPMODEL_WATERHEATERMIXED_IMPL_HPP

#include "WaterToWaterComponent/WaterToWaterComponent_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  class CurveCubic;
  class PlantLoop;
  class Schedule;
  class ThermalZone;
  class WaterHeaterSizing;

  namespace detail {

    class EPMODEL_API WaterHeaterMixed_Impl : public WaterToWaterComponent_Impl
    {
     public:
     using WaterToWaterComponent_Impl::WaterToWaterComponent_Impl;
      virtual ~WaterHeaterMixed_Impl() override = default;

      std::vector<ModelObject> children() const override;

      boost::optional<double> tankVolume() const;
      bool isTankVolumeDefaulted() const;
      bool isTankVolumeAutosized() const;
      bool setTankVolume(double tankVolume);
      void resetTankVolume();
      void autosizeTankVolume();
      boost::optional<double> autosizedTankVolume() const;

      boost::optional<Schedule> setpointTemperatureSchedule() const;
      bool setSetpointTemperatureSchedule(Schedule& schedule);
      void resetSetpointTemperatureSchedule();

      double deadbandTemperatureDifference() const;
      bool isDeadbandTemperatureDifferenceDefaulted() const;
      bool setDeadbandTemperatureDifference(double deadbandTemperatureDifference);
      void resetDeadbandTemperatureDifference();

      boost::optional<double> maximumTemperatureLimit() const;
      bool setMaximumTemperatureLimit(double maximumTemperatureLimit);
      void resetMaximumTemperatureLimit();

      std::string heaterControlType() const;
      bool isHeaterControlTypeDefaulted() const;
      bool setHeaterControlType(const std::string& heaterControlType);
      void resetHeaterControlType();

      boost::optional<double> heaterMaximumCapacity() const;
      bool isHeaterMaximumCapacityAutosized() const;
      bool setHeaterMaximumCapacity(double heaterMaximumCapacity);
      void resetHeaterMaximumCapacity();
      void autosizeHeaterMaximumCapacity();
      boost::optional<double> autosizedHeaterMaximumCapacity() const;

      boost::optional<double> heaterMinimumCapacity() const;
      bool setHeaterMinimumCapacity(double heaterMinimumCapacity);
      void resetHeaterMinimumCapacity();

      double heaterIgnitionMinimumFlowRate() const;
      bool isHeaterIgnitionMinimumFlowRateDefaulted() const;
      bool setHeaterIgnitionMinimumFlowRate(double heaterIgnitionMinimumFlowRate);
      void resetHeaterIgnitionMinimumFlowRate();

      double heaterIgnitionDelay() const;
      bool isHeaterIgnitionDelayDefaulted() const;
      bool setHeaterIgnitionDelay(double heaterIgnitionDelay);
      void resetHeaterIgnitionDelay();

      std::string heaterFuelType() const;
      bool setHeaterFuelType(const std::string& heaterFuelType);
      void resetHeaterFuelType();

      boost::optional<double> heaterThermalEfficiency() const;
      bool setHeaterThermalEfficiency(double heaterThermalEfficiency);
      void resetHeaterThermalEfficiency();

      boost::optional<CurveCubic> partLoadFactorCurve() const;
      bool setPartLoadFactorCurve(const CurveCubic& partLoadFactorCurve);
      void resetPartLoadFactorCurve();

      double offCycleParasiticFuelConsumptionRate() const;
      bool isOffCycleParasiticFuelConsumptionRateDefaulted() const;
      bool setOffCycleParasiticFuelConsumptionRate(double offCycleParasiticFuelConsumptionRate);
      void resetOffCycleParasiticFuelConsumptionRate();

      boost::optional<std::string> offCycleParasiticFuelType() const;
      bool setOffCycleParasiticFuelType(const std::string& offCycleParasiticFuelType);
      void resetOffCycleParasiticFuelType();

      double offCycleParasiticHeatFractiontoTank() const;
      bool isOffCycleParasiticHeatFractiontoTankDefaulted() const;
      bool setOffCycleParasiticHeatFractiontoTank(double offCycleParasiticHeatFractiontoTank);
      void resetOffCycleParasiticHeatFractiontoTank();

      double onCycleParasiticFuelConsumptionRate() const;
      bool isOnCycleParasiticFuelConsumptionRateDefaulted() const;
      bool setOnCycleParasiticFuelConsumptionRate(double onCycleParasiticFuelConsumptionRate);
      void resetOnCycleParasiticFuelConsumptionRate();

      boost::optional<std::string> onCycleParasiticFuelType() const;
      bool setOnCycleParasiticFuelType(const std::string& onCycleParasiticFuelType);
      void resetOnCycleParasiticFuelType();

      double onCycleParasiticHeatFractiontoTank() const;
      bool isOnCycleParasiticHeatFractiontoTankDefaulted() const;
      bool setOnCycleParasiticHeatFractiontoTank(double onCycleParasiticHeatFractiontoTank);
      void resetOnCycleParasiticHeatFractiontoTank();

      std::string ambientTemperatureIndicator() const;
      bool setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator);

      boost::optional<Schedule> ambientTemperatureSchedule() const;
      bool setAmbientTemperatureSchedule(Schedule& schedule);
      void resetAmbientTemperatureSchedule();

      boost::optional<ThermalZone> ambientTemperatureThermalZone() const;
      bool setAmbientTemperatureThermalZone(const ThermalZone& ambientTemperatureThermalZone);
      void resetAmbientTemperatureThermalZone();

      boost::optional<std::string> ambientTemperatureOutdoorAirNodeName() const;
      bool setAmbientTemperatureOutdoorAirNodeName(const std::string& ambientTemperatureOutdoorAirNodeName);
      void resetAmbientTemperatureOutdoorAirNodeName();

      boost::optional<double> offCycleLossCoefficienttoAmbientTemperature() const;
      bool setOffCycleLossCoefficienttoAmbientTemperature(double offCycleLossCoefficienttoAmbientTemperature);
      void resetOffCycleLossCoefficienttoAmbientTemperature();

      double offCycleLossFractiontoThermalZone() const;
      bool isOffCycleLossFractiontoThermalZoneDefaulted() const;
      bool setOffCycleLossFractiontoThermalZone(double offCycleLossFractiontoThermalZone);
      void resetOffCycleLossFractiontoThermalZone();

      boost::optional<double> onCycleLossCoefficienttoAmbientTemperature() const;
      bool setOnCycleLossCoefficienttoAmbientTemperature(double onCycleLossCoefficienttoAmbientTemperature);
      void resetOnCycleLossCoefficienttoAmbientTemperature();

      double onCycleLossFractiontoThermalZone() const;
      bool isOnCycleLossFractiontoThermalZoneDefaulted() const;
      bool setOnCycleLossFractiontoThermalZone(double onCycleLossFractiontoThermalZone);
      void resetOnCycleLossFractiontoThermalZone();

      boost::optional<double> peakUseFlowRate() const;
      bool setPeakUseFlowRate(double peakUseFlowRate);
      void resetPeakUseFlowRate();

      boost::optional<Schedule> useFlowRateFractionSchedule() const;
      bool setUseFlowRateFractionSchedule(Schedule& schedule);
      void resetUseFlowRateFractionSchedule();

      boost::optional<Schedule> coldWaterSupplyTemperatureSchedule() const;
      bool setColdWaterSupplyTemperatureSchedule(Schedule& schedule);
      void resetColdWaterSupplyTemperatureSchedule();

      double useSideEffectiveness() const;
      bool isUseSideEffectivenessDefaulted() const;
      bool setUseSideEffectiveness(double useSideEffectiveness);
      void resetUseSideEffectiveness();

      double sourceSideEffectiveness() const;
      bool isSourceSideEffectivenessDefaulted() const;
      bool setSourceSideEffectiveness(double sourceSideEffectiveness);
      void resetSourceSideEffectiveness();

      boost::optional<double> useSideDesignFlowRate() const;
      bool isUseSideDesignFlowRateDefaulted() const;
      bool isUseSideDesignFlowRateAutosized() const;
      bool setUseSideDesignFlowRate(double useSideDesignFlowRate);
      void resetUseSideDesignFlowRate();
      void autosizeUseSideDesignFlowRate();
      boost::optional<double> autosizedUseSideDesignFlowRate() const;

      boost::optional<double> sourceSideDesignFlowRate() const;
      bool isSourceSideDesignFlowRateDefaulted() const;
      bool isSourceSideDesignFlowRateAutosized() const;
      bool setSourceSideDesignFlowRate(double sourceSideDesignFlowRate);
      void resetSourceSideDesignFlowRate();
      void autosizeSourceSideDesignFlowRate();
      boost::optional<double> autosizedSourceSideDesignFlowRate() const;

      double indirectWaterHeatingRecoveryTime() const;
      bool isIndirectWaterHeatingRecoveryTimeDefaulted() const;
      unsigned supplyInletPort() const override;
      unsigned supplyOutletPort() const override;
      unsigned demandInletPort() const override;
      unsigned demandOutletPort() const override;
      boost::optional<PlantLoop> plantLoop() const override;
      boost::optional<PlantLoop> secondaryPlantLoop() const override;
      bool removeFromSecondaryPlantLoop() override;
      bool addToNode(Node& node) override;
      bool addToSourceSideNode(Node& node);
      openstudio::ComponentType componentType() const override;
      std::vector<openstudio::FuelType> coolingFuelTypes() const override;
      std::vector<openstudio::FuelType> heatingFuelTypes() const override;
      std::vector<openstudio::AppGFuelType> appGHeatingFuelTypes() const override;
      bool setIndirectWaterHeatingRecoveryTime(double indirectWaterHeatingRecoveryTime);
      void resetIndirectWaterHeatingRecoveryTime();

      std::string sourceSideFlowControlMode() const;
      bool setSourceSideFlowControlMode(const std::string& sourceSideFlowControlMode);

      boost::optional<Schedule> indirectAlternateSetpointTemperatureSchedule() const;
      bool setIndirectAlternateSetpointTemperatureSchedule(Schedule& indirectAlternateSetpointTemperatureSchedule);
      void resetIndirectAlternateSetpointTemperatureSchedule();

      std::string endUseSubcategory() const;
      bool setEndUseSubcategory(const std::string& endUseSubcategory);

      WaterHeaterSizing waterHeaterSizing() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
