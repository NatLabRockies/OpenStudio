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

    boost::optional<double> tankVolume() const;
    bool isTankVolumeAutosized() const;

    boost::optional<double> tankHeight() const;
    bool isTankHeightAutosized() const;

    std::string tankShape() const;

    boost::optional<double> tankPerimeter() const;

    double maximumTemperatureLimit() const;

    std::string heaterPriorityControl() const;

    double heater1DeadbandTemperatureDifference() const;

    boost::optional<double> heater1Capacity() const;
    bool isHeater1CapacityAutosized() const;

    double heater1Height() const;

    double heater2DeadbandTemperatureDifference() const;

    double heater2Capacity() const;

    double heater2Height() const;

    std::string heaterFuelType() const;

    double heaterThermalEfficiency() const;

    double offCycleParasiticFuelConsumptionRate() const;

    std::string offCycleParasiticFuelType() const;

    double offCycleParasiticHeatFractiontoTank() const;

    double offCycleParasiticHeight() const;

    double onCycleParasiticFuelConsumptionRate() const;

    std::string onCycleParasiticFuelType() const;

    double onCycleParasiticHeatFractiontoTank() const;

    double onCycleParasiticHeight() const;

    std::string ambientTemperatureIndicator() const;

    boost::optional<std::string> ambientTemperatureOutdoorAirNodeName() const;

    boost::optional<double> uniformSkinLossCoefficientperUnitAreatoAmbientTemperature() const;

    double skinLossFractiontoZone() const;

    boost::optional<double> offCycleFlueLossCoefficienttoAmbientTemperature() const;

    double offCycleFlueLossFractiontoZone() const;

    boost::optional<double> peakUseFlowRate() const;

    double useSideEffectiveness() const;

    double useSideInletHeight() const;

    boost::optional<double> useSideOutletHeight() const;
    bool isUseSideOutletHeightAutocalculated() const;

    double sourceSideEffectiveness() const;

    boost::optional<double> sourceSideInletHeight() const;
    bool isSourceSideInletHeightAutocalculated() const;

    double sourceSideOutletHeight() const;

    std::string inletMode() const;

    boost::optional<double> useSideDesignFlowRate() const;
    bool isUseSideDesignFlowRateAutosized() const;

    boost::optional<double> sourceSideDesignFlowRate() const;
    bool isSourceSideDesignFlowRateAutosized() const;

    double indirectWaterHeatingRecoveryTime() const;

    int numberofNodes() const;

    double additionalDestratificationConductivity() const;

    double node1AdditionalLossCoefficient() const;
    double node2AdditionalLossCoefficient() const;
    double node3AdditionalLossCoefficient() const;
    double node4AdditionalLossCoefficient() const;
    double node5AdditionalLossCoefficient() const;
    double node6AdditionalLossCoefficient() const;
    double node7AdditionalLossCoefficient() const;
    double node8AdditionalLossCoefficient() const;
    double node9AdditionalLossCoefficient() const;
    double node10AdditionalLossCoefficient() const;
    double node11AdditionalLossCoefficient() const;
    double node12AdditionalLossCoefficient() const;

    std::string sourceSideFlowControlMode() const;

    boost::optional<double> autosizedTankVolume() const;
    boost::optional<double> autosizedTankHeight() const;
    boost::optional<double> autosizedHeater1Capacity() const;
    boost::optional<double> autosizedUseSideDesignFlowRate() const;
    boost::optional<double> autosizedSourceSideDesignFlowRate() const;

    bool setEndUseSubcategory(const std::string& endUseSubcategory);

    bool setTankVolume(double tankVolume);
    void autosizeTankVolume();

    bool setTankHeight(double tankHeight);
    void autosizeTankHeight();

    bool setTankShape(const std::string& tankShape);

    bool setTankPerimeter(double tankPerimeter);
    void resetTankPerimeter();

    bool setMaximumTemperatureLimit(double maximumTemperatureLimit);

    bool setHeaterPriorityControl(const std::string& heaterPriorityControl);

    bool setHeater1DeadbandTemperatureDifference(double heater1DeadbandTemperatureDifference);

    bool setHeater1Capacity(double heater1Capacity);
    void autosizeHeater1Capacity();

    bool setHeater1Height(double heater1Height);

    bool setHeater2DeadbandTemperatureDifference(double heater2DeadbandTemperatureDifference);

    bool setHeater2Capacity(double heater2Capacity);

    bool setHeater2Height(double heater2Height);

    bool setHeaterFuelType(const FuelType& heaterFuelType);
    bool setHeaterFuelType(const std::string& heaterFuelType);

    bool setHeaterThermalEfficiency(double heaterThermalEfficiency);

    bool setOffCycleParasiticFuelConsumptionRate(double offCycleParasiticFuelConsumptionRate);

    bool setOffCycleParasiticFuelType(const FuelType& offCycleParasiticFuelType);
    bool setOffCycleParasiticFuelType(const std::string& offCycleParasiticFuelType);

    bool setOffCycleParasiticHeatFractiontoTank(double offCycleParasiticHeatFractiontoTank);

    bool setOffCycleParasiticHeight(double offCycleParasiticHeight);

    bool setOnCycleParasiticFuelConsumptionRate(double onCycleParasiticFuelConsumptionRate);

    bool setOnCycleParasiticFuelType(const FuelType& onCycleParasiticFuelType);
    bool setOnCycleParasiticFuelType(const std::string& onCycleParasiticFuelType);

    bool setOnCycleParasiticHeatFractiontoTank(double onCycleParasiticHeatFractiontoTank);

    bool setOnCycleParasiticHeight(double onCycleParasiticHeight);

    bool setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator);

    bool setAmbientTemperatureOutdoorAirNodeName(const std::string& ambientTemperatureOutdoorAirNodeName);
    void resetAmbientTemperatureOutdoorAirNodeName();

    bool setUniformSkinLossCoefficientperUnitAreatoAmbientTemperature(double uniformSkinLossCoefficientperUnitAreatoAmbientTemperature);
    void resetUniformSkinLossCoefficientperUnitAreatoAmbientTemperature();

    bool setSkinLossFractiontoZone(double skinLossFractiontoZone);

    bool setOffCycleFlueLossCoefficienttoAmbientTemperature(double offCycleFlueLossCoefficienttoAmbientTemperature);
    void resetOffCycleFlueLossCoefficienttoAmbientTemperature();

    bool setOffCycleFlueLossFractiontoZone(double offCycleFlueLossFractiontoZone);

    bool setPeakUseFlowRate(double peakUseFlowRate);
    void resetPeakUseFlowRate();

    bool setUseSideEffectiveness(double useSideEffectiveness);

    bool setUseSideInletHeight(double useSideInletHeight);

    bool setUseSideOutletHeight(double useSideOutletHeight);
    void autocalculateUseSideOutletHeight();

    bool setSourceSideEffectiveness(double sourceSideEffectiveness);

    bool setSourceSideInletHeight(double sourceSideInletHeight);
    void autocalculateSourceSideInletHeight();

    bool setSourceSideOutletHeight(double sourceSideOutletHeight);

    bool setInletMode(const std::string& inletMode);

    bool setUseSideDesignFlowRate(double useSideDesignFlowRate);
    void autosizeUseSideDesignFlowRate();

    bool setSourceSideDesignFlowRate(double sourceSideDesignFlowRate);
    void autosizeSourceSideDesignFlowRate();

    bool setIndirectWaterHeatingRecoveryTime(double indirectWaterHeatingRecoveryTime);

    bool setNumberofNodes(int numberofNodes);

    bool setAdditionalDestratificationConductivity(double additionalDestratificationConductivity);

    bool setNode1AdditionalLossCoefficient(double node1AdditionalLossCoefficient);
    bool setNode2AdditionalLossCoefficient(double node2AdditionalLossCoefficient);
    bool setNode3AdditionalLossCoefficient(double node3AdditionalLossCoefficient);
    bool setNode4AdditionalLossCoefficient(double node4AdditionalLossCoefficient);
    bool setNode5AdditionalLossCoefficient(double node5AdditionalLossCoefficient);
    bool setNode6AdditionalLossCoefficient(double node6AdditionalLossCoefficient);
    bool setNode7AdditionalLossCoefficient(double node7AdditionalLossCoefficient);
    bool setNode8AdditionalLossCoefficient(double node8AdditionalLossCoefficient);
    bool setNode9AdditionalLossCoefficient(double node9AdditionalLossCoefficient);
    bool setNode10AdditionalLossCoefficient(double node10AdditionalLossCoefficient);
    bool setNode11AdditionalLossCoefficient(double node11AdditionalLossCoefficient);
    bool setNode12AdditionalLossCoefficient(double node12AdditionalLossCoefficient);

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
