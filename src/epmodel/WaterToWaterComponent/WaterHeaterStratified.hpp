/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WATERHEATERSTRATIFIED_HPP
#define EPMODEL_WATERHEATERSTRATIFIED_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {

class FuelType;

namespace epmodel {

  class Model;

  namespace detail {

    class WaterHeaterStratified_Impl;

  }

  class EPMODEL_API WaterHeaterStratified : public ModelObject
  {
   public:
    explicit WaterHeaterStratified(const Model& model);

    virtual ~WaterHeaterStratified() override = default;
    WaterHeaterStratified(const WaterHeaterStratified& other) = default;
    WaterHeaterStratified(WaterHeaterStratified&& other) = default;
    WaterHeaterStratified& operator=(const WaterHeaterStratified&) = default;
    WaterHeaterStratified& operator=(WaterHeaterStratified&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> tankShapeValues();
    static std::vector<std::string> heaterPriorityControlValues();
    static std::vector<std::string> heaterFuelTypeValues();
    static std::vector<std::string> offCycleParasiticFuelTypeValues();
    static std::vector<std::string> onCycleParasiticFuelTypeValues();
    static std::vector<std::string> ambientTemperatureIndicatorValues();
    static std::vector<std::string> inletModeValues();
    static std::vector<std::string> sourceSideFlowControlModeValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::WaterHeaterStratified scalar accessor names/signatures to stay aligned with the translator.
    // - Field Mapping: Simple scalar values map directly to the EnergyPlus WaterHeater:Stratified fields documented in ForwardTranslateWaterHeaterStratified.
    // - TODO(parity): Surface, schedule, node, and plant relationships will be added later when the scalar scaffolding is complete.
    // - Field Mapping: ambientTemperatureIndicator exposes the OpenStudio-friendly "ThermalZone" label even though the EnergyPlus field uses "Zone"; the setter/getter normalize between these values.
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

    double heater1DeadbandTemperatureDifference() const;
    bool setHeater1DeadbandTemperatureDifference(double heater1DeadbandTemperatureDifference);

    boost::optional<double> heater1Capacity() const;
    bool isHeater1CapacityAutosized() const;
    bool setHeater1Capacity(double heater1Capacity);
    void autosizeHeater1Capacity();
    boost::optional<double> autosizedHeater1Capacity() const;

    double heater1Height() const;
    bool setHeater1Height(double heater1Height);

    double heater2DeadbandTemperatureDifference() const;
    bool setHeater2DeadbandTemperatureDifference(double heater2DeadbandTemperatureDifference);

    double heater2Capacity() const;
    bool setHeater2Capacity(double heater2Capacity);

    double heater2Height() const;
    bool setHeater2Height(double heater2Height);

    std::string heaterFuelType() const;
    bool setHeaterFuelType(const FuelType& heaterFuelType);
    bool setHeaterFuelType(const std::string& heaterFuelType);

    double heaterThermalEfficiency() const;
    bool setHeaterThermalEfficiency(double heaterThermalEfficiency);

    double offCycleParasiticFuelConsumptionRate() const;
    bool setOffCycleParasiticFuelConsumptionRate(double offCycleParasiticFuelConsumptionRate);

    std::string offCycleParasiticFuelType() const;
    bool setOffCycleParasiticFuelType(const FuelType& offCycleParasiticFuelType);
    bool setOffCycleParasiticFuelType(const std::string& offCycleParasiticFuelType);

    double offCycleParasiticHeatFractiontoTank() const;
    bool setOffCycleParasiticHeatFractiontoTank(double offCycleParasiticHeatFractiontoTank);

    double offCycleParasiticHeight() const;
    bool setOffCycleParasiticHeight(double offCycleParasiticHeight);

    double onCycleParasiticFuelConsumptionRate() const;
    bool setOnCycleParasiticFuelConsumptionRate(double onCycleParasiticFuelConsumptionRate);

    std::string onCycleParasiticFuelType() const;
    bool setOnCycleParasiticFuelType(const FuelType& onCycleParasiticFuelType);
    bool setOnCycleParasiticFuelType(const std::string& onCycleParasiticFuelType);

    double onCycleParasiticHeatFractiontoTank() const;
    bool setOnCycleParasiticHeatFractiontoTank(double onCycleParasiticHeatFractiontoTank);

    double onCycleParasiticHeight() const;
    bool setOnCycleParasiticHeight(double onCycleParasiticHeight);

    std::string ambientTemperatureIndicator() const;
    bool setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator);

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

   protected:
    using ImplType = detail::WaterHeaterStratified_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WaterHeaterStratified(std::shared_ptr<detail::WaterHeaterStratified_Impl> impl);
  };

  using OptionalWaterHeaterStratified = boost::optional<WaterHeaterStratified>;

}  // namespace epmodel
}  // namespace openstudio

#endif
