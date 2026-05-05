/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WATERHEATERSTRATIFIED_IMPL_HPP
#define EPMODEL_WATERHEATERSTRATIFIED_IMPL_HPP

#include "WaterToWaterComponent/WaterToWaterComponent_Impl.hpp"

#include <boost/optional.hpp>

#include <string>

namespace openstudio {
namespace epmodel {

  class Schedule;
  class ThermalZone;
  class WaterHeaterSizing;
  class Node;
  class PlantLoop;

  namespace detail {

    class EPMODEL_API WaterHeaterStratified_Impl : public WaterToWaterComponent_Impl
    {
     public:
      using WaterToWaterComponent_Impl::WaterToWaterComponent_Impl;
      virtual ~WaterHeaterStratified_Impl() override = default;

      void doCanonicalize(LoadContext& context) override;
      std::vector<ModelObject> children() const override;
      ModelObject clone(Model model) const;
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

      std::string endUseSubcategory() const;
      bool setEndUseSubcategory(const std::string& endUseSubcategory);

      boost::optional<double> tankVolume() const;
      bool isTankVolumeAutosized() const;
      bool setTankVolume(double tankVolume);
      void autosizeTankVolume();
      boost::optional<double> autosizedTankVolume() const;

      boost::optional<double> tankHeight() const;
      bool isTankHeightAutosized() const;
      bool setTankHeight(double tankHeight);
      void autosizeTankHeight();
      boost::optional<double> autosizedTankHeight() const;

      std::string tankShape() const;
      bool setTankShape(const std::string& tankShape);

      boost::optional<double> tankPerimeter() const;
      bool setTankPerimeter(double tankPerimeter);
      void resetTankPerimeter();

      double maximumTemperatureLimit() const;
      bool setMaximumTemperatureLimit(double maximumTemperatureLimit);

      std::string heaterPriorityControl() const;
      bool setHeaterPriorityControl(const std::string& heaterPriorityControl);

      boost::optional<Schedule> heater1SetpointTemperatureSchedule() const;
      bool setHeater1SetpointTemperatureSchedule(Schedule& schedule);
      void resetHeater1SetpointTemperatureSchedule();

      double heater1DeadbandTemperatureDifference() const;
      bool setHeater1DeadbandTemperatureDifference(double heater1DeadbandTemperatureDifference);

      boost::optional<double> heater1Capacity() const;
      bool isHeater1CapacityAutosized() const;
      bool setHeater1Capacity(double heater1Capacity);
      void autosizeHeater1Capacity();
      boost::optional<double> autosizedHeater1Capacity() const;

      double heater1Height() const;
      bool setHeater1Height(double heater1Height);

      boost::optional<Schedule> heater2SetpointTemperatureSchedule() const;
      bool setHeater2SetpointTemperatureSchedule(Schedule& schedule);
      void resetHeater2SetpointTemperatureSchedule();

      double heater2DeadbandTemperatureDifference() const;
      bool setHeater2DeadbandTemperatureDifference(double heater2DeadbandTemperatureDifference);

      double heater2Capacity() const;
      bool setHeater2Capacity(double heater2Capacity);

      double heater2Height() const;
      bool setHeater2Height(double heater2Height);

      std::string heaterFuelType() const;
      bool setHeaterFuelType(const std::string& heaterFuelType);

      double heaterThermalEfficiency() const;
      bool setHeaterThermalEfficiency(double heaterThermalEfficiency);

      double offCycleParasiticFuelConsumptionRate() const;
      bool setOffCycleParasiticFuelConsumptionRate(double offCycleParasiticFuelConsumptionRate);

      std::string offCycleParasiticFuelType() const;
      bool setOffCycleParasiticFuelType(const std::string& offCycleParasiticFuelType);

      double offCycleParasiticHeatFractiontoTank() const;
      bool setOffCycleParasiticHeatFractiontoTank(double offCycleParasiticHeatFractiontoTank);

      double offCycleParasiticHeight() const;
      bool setOffCycleParasiticHeight(double offCycleParasiticHeight);

      double onCycleParasiticFuelConsumptionRate() const;
      bool setOnCycleParasiticFuelConsumptionRate(double onCycleParasiticFuelConsumptionRate);

      std::string onCycleParasiticFuelType() const;
      bool setOnCycleParasiticFuelType(const std::string& onCycleParasiticFuelType);

      double onCycleParasiticHeatFractiontoTank() const;
      bool setOnCycleParasiticHeatFractiontoTank(double onCycleParasiticHeatFractiontoTank);

      double onCycleParasiticHeight() const;
      bool setOnCycleParasiticHeight(double onCycleParasiticHeight);

      std::string ambientTemperatureIndicator() const;
      bool setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator);

      boost::optional<Schedule> ambientTemperatureSchedule() const;
      bool setAmbientTemperatureSchedule(Schedule& schedule);
      void resetAmbientTemperatureSchedule();

      boost::optional<ThermalZone> ambientTemperatureThermalZone() const;
      bool setAmbientTemperatureThermalZone(const ThermalZone& thermalZone);
      void resetAmbientTemperatureThermalZone();

      boost::optional<std::string> ambientTemperatureOutdoorAirNodeName() const;
      bool setAmbientTemperatureOutdoorAirNodeName(const std::string& ambientTemperatureOutdoorAirNodeName);
      void resetAmbientTemperatureOutdoorAirNodeName();

      boost::optional<double> uniformSkinLossCoefficientperUnitAreatoAmbientTemperature() const;
      bool setUniformSkinLossCoefficientperUnitAreatoAmbientTemperature(double uniformSkinLossCoefficientperUnitAreatoAmbientTemperature);
      void resetUniformSkinLossCoefficientperUnitAreatoAmbientTemperature();

      double skinLossFractiontoZone() const;
      bool setSkinLossFractiontoZone(double skinLossFractiontoZone);

      boost::optional<double> offCycleFlueLossCoefficienttoAmbientTemperature() const;
      bool setOffCycleFlueLossCoefficienttoAmbientTemperature(double offCycleFlueLossCoefficienttoAmbientTemperature);
      void resetOffCycleFlueLossCoefficienttoAmbientTemperature();

      double offCycleFlueLossFractiontoZone() const;
      bool setOffCycleFlueLossFractiontoZone(double offCycleFlueLossFractiontoZone);

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
      bool setUseSideEffectiveness(double useSideEffectiveness);

      double useSideInletHeight() const;
      bool setUseSideInletHeight(double useSideInletHeight);

      boost::optional<double> useSideOutletHeight() const;
      bool isUseSideOutletHeightAutocalculated() const;
      bool setUseSideOutletHeight(double useSideOutletHeight);
      void autocalculateUseSideOutletHeight();

      double sourceSideEffectiveness() const;
      bool setSourceSideEffectiveness(double sourceSideEffectiveness);

      boost::optional<double> sourceSideInletHeight() const;
      bool isSourceSideInletHeightAutocalculated() const;
      bool setSourceSideInletHeight(double sourceSideInletHeight);
      void autocalculateSourceSideInletHeight();

      double sourceSideOutletHeight() const;
      bool setSourceSideOutletHeight(double sourceSideOutletHeight);

      std::string inletMode() const;
      bool setInletMode(const std::string& inletMode);

      boost::optional<double> useSideDesignFlowRate() const;
      bool isUseSideDesignFlowRateAutosized() const;
      bool setUseSideDesignFlowRate(double useSideDesignFlowRate);
      void autosizeUseSideDesignFlowRate();
      boost::optional<double> autosizedUseSideDesignFlowRate() const;

      boost::optional<double> sourceSideDesignFlowRate() const;
      bool isSourceSideDesignFlowRateAutosized() const;
      bool setSourceSideDesignFlowRate(double sourceSideDesignFlowRate);
      void autosizeSourceSideDesignFlowRate();
      boost::optional<double> autosizedSourceSideDesignFlowRate() const;

      double indirectWaterHeatingRecoveryTime() const;
      bool setIndirectWaterHeatingRecoveryTime(double indirectWaterHeatingRecoveryTime);

      int numberofNodes() const;
      bool setNumberofNodes(int numberofNodes);

      double additionalDestratificationConductivity() const;
      bool setAdditionalDestratificationConductivity(double additionalDestratificationConductivity);

      double node1AdditionalLossCoefficient() const;
      bool setNode1AdditionalLossCoefficient(double node1AdditionalLossCoefficient);

      double node2AdditionalLossCoefficient() const;
      bool setNode2AdditionalLossCoefficient(double node2AdditionalLossCoefficient);

      double node3AdditionalLossCoefficient() const;
      bool setNode3AdditionalLossCoefficient(double node3AdditionalLossCoefficient);

      double node4AdditionalLossCoefficient() const;
      bool setNode4AdditionalLossCoefficient(double node4AdditionalLossCoefficient);

      double node5AdditionalLossCoefficient() const;
      bool setNode5AdditionalLossCoefficient(double node5AdditionalLossCoefficient);

      double node6AdditionalLossCoefficient() const;
      bool setNode6AdditionalLossCoefficient(double node6AdditionalLossCoefficient);

      double node7AdditionalLossCoefficient() const;
      bool setNode7AdditionalLossCoefficient(double node7AdditionalLossCoefficient);

      double node8AdditionalLossCoefficient() const;
      bool setNode8AdditionalLossCoefficient(double node8AdditionalLossCoefficient);

      double node9AdditionalLossCoefficient() const;
      bool setNode9AdditionalLossCoefficient(double node9AdditionalLossCoefficient);

      double node10AdditionalLossCoefficient() const;
      bool setNode10AdditionalLossCoefficient(double node10AdditionalLossCoefficient);

      double node11AdditionalLossCoefficient() const;
      bool setNode11AdditionalLossCoefficient(double node11AdditionalLossCoefficient);

      double node12AdditionalLossCoefficient() const;
      bool setNode12AdditionalLossCoefficient(double node12AdditionalLossCoefficient);

      std::string sourceSideFlowControlMode() const;
      bool setSourceSideFlowControlMode(const std::string& sourceSideFlowControlMode);

      boost::optional<Schedule> indirectAlternateSetpointTemperatureSchedule() const;
      bool setIndirectAlternateSetpointTemperatureSchedule(Schedule& schedule);
      void resetIndirectAlternateSetpointTemperatureSchedule();

      WaterHeaterSizing waterHeaterSizing() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
