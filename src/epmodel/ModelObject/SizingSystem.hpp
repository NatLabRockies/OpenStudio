/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SIZINGSYSTEM_HPP
#define EPMODEL_SIZINGSYSTEM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class AirLoopHVAC;

  namespace detail {
    class SizingSystem_Impl;
  }

  class EPMODEL_API SizingSystem : public ModelObject
  {
   public:
    explicit SizingSystem(const Model& model, const AirLoopHVAC& airLoopHVAC);

    virtual ~SizingSystem() override = default;
    SizingSystem(const SizingSystem& other) = default;
    SizingSystem(SizingSystem&& other) = default;
    SizingSystem& operator=(const SizingSystem&) = default;
    SizingSystem& operator=(SizingSystem&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validTypeofLoadtoSizeOnValues();
    static std::vector<std::string> validSizingOptionValues();
    static std::vector<std::string> validCoolingDesignAirFlowMethodValues();
    static std::vector<std::string> validHeatingDesignAirFlowMethodValues();
    static std::vector<std::string> validSystemOutdoorAirMethodValues();
    static std::vector<std::string> heatingCoilSizingMethodValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model SizingSystem scalar accessor names/signatures.
    // - Field Mapping: sizingOption maps to E+ Sizing:System field Type of Zone Sum to Use.
    // - Field Mapping: cooling/heatingDesignAirFlowMethod and cooling/heatingDesignAirFlowRate
    //   map to E+ Cooling/Heating Supply Air Flow Rate Method/Rate fields.
    // - Field Mapping: AirLoopName is a relationship field and is intentionally excluded from
    //   scalar accessor coverage.
    // - ForwardTranslator Evidence: ForwardTranslateSizingSystem confirms these drift mappings.
    // - TODO(parity): Add relationship accessor parity for AirLoopName in a non-scalar pass.
    std::string typeofLoadtoSizeOn() const;
    bool isTypeofLoadtoSizeOnDefaulted() const;
    bool setTypeofLoadtoSizeOn(const std::string& typeofLoadtoSizeOn);
    void resetTypeofLoadtoSizeOn();

    boost::optional<double> designOutdoorAirFlowRate() const;
    bool isDesignOutdoorAirFlowRateDefaulted() const;
    bool isDesignOutdoorAirFlowRateAutosized() const;
    bool setDesignOutdoorAirFlowRate(double designOutdoorAirFlowRate);
    void resetDesignOutdoorAirFlowRate();
    void autosizeDesignOutdoorAirFlowRate();

    boost::optional<double> centralHeatingMaximumSystemAirFlowRatio() const;
    bool isCentralHeatingMaximumSystemAirFlowRatioDefaulted() const;
    bool isCentralHeatingMaximumSystemAirFlowRatioAutosized() const;
    bool setCentralHeatingMaximumSystemAirFlowRatio(double centralHeatingMaximumSystemAirFlowRatio);
    void resetCentralHeatingMaximumSystemAirFlowRatio();
    void autosizeCentralHeatingMaximumSystemAirFlowRatio();

    double preheatDesignTemperature() const;
    bool setPreheatDesignTemperature(double preheatDesignTemperature);

    double preheatDesignHumidityRatio() const;
    bool setPreheatDesignHumidityRatio(double preheatDesignHumidityRatio);

    double precoolDesignTemperature() const;
    bool setPrecoolDesignTemperature(double precoolDesignTemperature);

    double precoolDesignHumidityRatio() const;
    bool setPrecoolDesignHumidityRatio(double precoolDesignHumidityRatio);

    double centralCoolingDesignSupplyAirTemperature() const;
    bool setCentralCoolingDesignSupplyAirTemperature(double centralCoolingDesignSupplyAirTemperature);

    double centralHeatingDesignSupplyAirTemperature() const;
    bool setCentralHeatingDesignSupplyAirTemperature(double centralHeatingDesignSupplyAirTemperature);

    std::string sizingOption() const;
    bool isSizingOptionDefaulted() const;
    bool setSizingOption(const std::string& sizingOption);
    void resetSizingOption();

    bool allOutdoorAirinCooling() const;
    bool isAllOutdoorAirinCoolingDefaulted() const;
    bool setAllOutdoorAirinCooling(bool allOutdoorAirinCooling);
    void resetAllOutdoorAirinCooling();

    bool allOutdoorAirinHeating() const;
    bool isAllOutdoorAirinHeatingDefaulted() const;
    bool setAllOutdoorAirinHeating(bool allOutdoorAirinHeating);
    void resetAllOutdoorAirinHeating();

    double centralCoolingDesignSupplyAirHumidityRatio() const;
    bool isCentralCoolingDesignSupplyAirHumidityRatioDefaulted() const;
    bool setCentralCoolingDesignSupplyAirHumidityRatio(double centralCoolingDesignSupplyAirHumidityRatio);
    void resetCentralCoolingDesignSupplyAirHumidityRatio();

    double centralHeatingDesignSupplyAirHumidityRatio() const;
    bool isCentralHeatingDesignSupplyAirHumidityRatioDefaulted() const;
    bool setCentralHeatingDesignSupplyAirHumidityRatio(double centralHeatingDesignSupplyAirHumidityRatio);
    void resetCentralHeatingDesignSupplyAirHumidityRatio();

    std::string coolingDesignAirFlowMethod() const;
    bool isCoolingDesignAirFlowMethodDefaulted() const;
    bool setCoolingDesignAirFlowMethod(const std::string& coolingDesignAirFlowMethod);
    void resetCoolingDesignAirFlowMethod();

    double coolingDesignAirFlowRate() const;
    bool isCoolingDesignAirFlowRateDefaulted() const;
    bool setCoolingDesignAirFlowRate(double coolingDesignAirFlowRate);
    void resetCoolingDesignAirFlowRate();

    std::string heatingDesignAirFlowMethod() const;
    bool isHeatingDesignAirFlowMethodDefaulted() const;
    bool setHeatingDesignAirFlowMethod(const std::string& heatingDesignAirFlowMethod);
    void resetHeatingDesignAirFlowMethod();

    double heatingDesignAirFlowRate() const;
    bool isHeatingDesignAirFlowRateDefaulted() const;
    bool setHeatingDesignAirFlowRate(double heatingDesignAirFlowRate);
    void resetHeatingDesignAirFlowRate();

    std::string systemOutdoorAirMethod() const;
    bool isSystemOutdoorAirMethodDefaulted() const;
    bool setSystemOutdoorAirMethod(const std::string& systemOutdoorAirMethod);
    void resetSystemOutdoorAirMethod();

    double zoneMaximumOutdoorAirFraction() const;
    bool setZoneMaximumOutdoorAirFraction(double zoneMaximumOutdoorAirFraction);

    double coolingSupplyAirFlowRatePerFloorArea() const;
    bool setCoolingSupplyAirFlowRatePerFloorArea(double coolingSupplyAirFlowRatePerFloorArea);

    double coolingFractionofAutosizedCoolingSupplyAirFlowRate() const;
    bool setCoolingFractionofAutosizedCoolingSupplyAirFlowRate(double coolingFractionofAutosizedCoolingSupplyAirFlowRate);

    double coolingSupplyAirFlowRatePerUnitCoolingCapacity() const;
    bool setCoolingSupplyAirFlowRatePerUnitCoolingCapacity(double coolingSupplyAirFlowRatePerUnitCoolingCapacity);

    double heatingSupplyAirFlowRatePerFloorArea() const;
    bool setHeatingSupplyAirFlowRatePerFloorArea(double heatingSupplyAirFlowRatePerFloorArea);

    double heatingFractionofAutosizedHeatingSupplyAirFlowRate() const;
    bool setHeatingFractionofAutosizedHeatingSupplyAirFlowRate(double heatingFractionofAutosizedHeatingSupplyAirFlowRate);

    double heatingFractionofAutosizedCoolingSupplyAirFlowRate() const;
    bool setHeatingFractionofAutosizedCoolingSupplyAirFlowRate(double heatingFractionofAutosizedCoolingSupplyAirFlowRate);

    double heatingSupplyAirFlowRatePerUnitHeatingCapacity() const;
    bool setHeatingSupplyAirFlowRatePerUnitHeatingCapacity(double heatingSupplyAirFlowRatePerUnitHeatingCapacity);

    std::string coolingDesignCapacityMethod() const;
    bool setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod);

    boost::optional<double> coolingDesignCapacity() const;
    bool isCoolingDesignCapacityAutosized() const;
    bool setCoolingDesignCapacity(double coolingDesignCapacity);
    void autosizeCoolingDesignCapacity();

    double coolingDesignCapacityPerFloorArea() const;
    bool setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea);

    double fractionofAutosizedCoolingDesignCapacity() const;
    bool setFractionofAutosizedCoolingDesignCapacity(double fractionofAutosizedCoolingDesignCapacity);

    std::string heatingDesignCapacityMethod() const;
    bool setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod);

    boost::optional<double> heatingDesignCapacity() const;
    bool isHeatingDesignCapacityAutosized() const;
    bool setHeatingDesignCapacity(double heatingDesignCapacity);
    void autosizeHeatingDesignCapacity();

    double heatingDesignCapacityPerFloorArea() const;
    bool setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea);

    double fractionofAutosizedHeatingDesignCapacity() const;
    bool setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity);

    std::string centralCoolingCapacityControlMethod() const;
    bool setCentralCoolingCapacityControlMethod(const std::string& centralCoolingCapacityControlMethod);

    boost::optional<double> occupantDiversity() const;
    bool isOccupantDiversityAutosized() const;
    bool setOccupantDiversity(double occupantDiversity);
    void autosizeOccupantDiversity();

    std::string heatingCoilSizingMethod() const;
    bool setHeatingCoilSizingMethod(const std::string& heatingCoilSizingMethod);

    double maximumHeatingCapacityToCoolingCapacitySizingRatio() const;
    bool setMaximumHeatingCapacityToCoolingCapacitySizingRatio(double maximumHeatingCapacityToCoolingCapacitySizingRatio);

   protected:
    using ImplType = detail::SizingSystem_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SizingSystem(std::shared_ptr<detail::SizingSystem_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
