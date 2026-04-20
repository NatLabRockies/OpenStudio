/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEZONEVAVFANPOWERED_HPP
#define EPMODEL_HVACTEMPLATEZONEVAVFANPOWERED_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HVACTemplateZoneVAVFanPowered_Impl;
  }

  class EPMODEL_API HVACTemplateZoneVAVFanPowered : public ModelObject
  {
   public:
    explicit HVACTemplateZoneVAVFanPowered(const Model& model);

    virtual ~HVACTemplateZoneVAVFanPowered() override = default;
    HVACTemplateZoneVAVFanPowered(const HVACTemplateZoneVAVFanPowered& other) = default;
    HVACTemplateZoneVAVFanPowered(HVACTemplateZoneVAVFanPowered&& other) = default;
    HVACTemplateZoneVAVFanPowered& operator=(const HVACTemplateZoneVAVFanPowered&) = default;
    HVACTemplateZoneVAVFanPowered& operator=(HVACTemplateZoneVAVFanPowered&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> flowTypeValues();
    static std::vector<std::string> outdoorAirMethodValues();
    static std::vector<std::string> reheatCoilTypeValues();
    static std::vector<std::string> baseboardHeatingTypeValues();
    static std::vector<std::string> zoneCoolingDesignSupplyAirTemperatureInputMethodValues();
    static std::vector<std::string> zoneHeatingDesignSupplyAirTemperatureInputMethodValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to HVACTemplate:Zone:VAV:FanPowered non-name, non-link scalar fields.
    // - Field Mapping: Zone/System/Thermostat/Schedule/Plenum/DesignSpecification name fields are object-list relationship
    //   fields and are intentionally excluded from scalar-only scaffold.
    // - TODO(parity): Revisit only if a future parity pass introduces relationship/object-link APIs.

    boost::optional<double> primarySupplyAirMaximumFlowRate() const;
    bool isPrimarySupplyAirMaximumFlowRateDefaulted() const;
    bool isPrimarySupplyAirMaximumFlowRateAutosized() const;
    bool setPrimarySupplyAirMaximumFlowRate(double primarySupplyAirMaximumFlowRate);
    void resetPrimarySupplyAirMaximumFlowRate();
    void autosizePrimarySupplyAirMaximumFlowRate();

    boost::optional<double> zoneHeatingSizingFactor() const;
    bool isZoneHeatingSizingFactorDefaulted() const;
    bool setZoneHeatingSizingFactor(double zoneHeatingSizingFactor);
    void resetZoneHeatingSizingFactor();

    boost::optional<double> zoneCoolingSizingFactor() const;
    bool isZoneCoolingSizingFactorDefaulted() const;
    bool setZoneCoolingSizingFactor(double zoneCoolingSizingFactor);
    void resetZoneCoolingSizingFactor();

    boost::optional<double> primarySupplyAirMinimumFlowFraction() const;
    bool isPrimarySupplyAirMinimumFlowFractionDefaulted() const;
    bool isPrimarySupplyAirMinimumFlowFractionAutosized() const;
    bool setPrimarySupplyAirMinimumFlowFraction(double primarySupplyAirMinimumFlowFraction);
    void resetPrimarySupplyAirMinimumFlowFraction();
    void autosizePrimarySupplyAirMinimumFlowFraction();

    boost::optional<double> secondarySupplyAirMaximumFlowRate() const;
    bool isSecondarySupplyAirMaximumFlowRateDefaulted() const;
    bool isSecondarySupplyAirMaximumFlowRateAutosized() const;
    bool setSecondarySupplyAirMaximumFlowRate(double secondarySupplyAirMaximumFlowRate);
    void resetSecondarySupplyAirMaximumFlowRate();
    void autosizeSecondarySupplyAirMaximumFlowRate();

    std::string flowType() const;
    bool isFlowTypeDefaulted() const;
    bool setFlowType(const std::string& flowType);
    void resetFlowType();

    boost::optional<double> parallelFanOnFlowFraction() const;
    bool isParallelFanOnFlowFractionDefaulted() const;
    bool isParallelFanOnFlowFractionAutosized() const;
    bool setParallelFanOnFlowFraction(double parallelFanOnFlowFraction);
    void resetParallelFanOnFlowFraction();
    void autosizeParallelFanOnFlowFraction();

    std::string outdoorAirMethod() const;
    bool isOutdoorAirMethodDefaulted() const;
    bool setOutdoorAirMethod(const std::string& outdoorAirMethod);
    void resetOutdoorAirMethod();

    double outdoorAirFlowRateperPerson() const;
    bool isOutdoorAirFlowRateperPersonDefaulted() const;
    bool setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson);
    void resetOutdoorAirFlowRateperPerson();

    double outdoorAirFlowRateperZoneFloorArea() const;
    bool isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const;
    bool setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea);
    void resetOutdoorAirFlowRateperZoneFloorArea();

    double outdoorAirFlowRateperZone() const;
    bool isOutdoorAirFlowRateperZoneDefaulted() const;
    bool setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone);
    void resetOutdoorAirFlowRateperZone();

    std::string reheatCoilType() const;
    bool isReheatCoilTypeDefaulted() const;
    bool setReheatCoilType(const std::string& reheatCoilType);
    void resetReheatCoilType();

    double fanTotalEfficiency() const;
    bool isFanTotalEfficiencyDefaulted() const;
    bool setFanTotalEfficiency(double fanTotalEfficiency);
    void resetFanTotalEfficiency();

    double fanDeltaPressure() const;
    bool isFanDeltaPressureDefaulted() const;
    bool setFanDeltaPressure(double fanDeltaPressure);
    void resetFanDeltaPressure();

    double fanMotorEfficiency() const;
    bool isFanMotorEfficiencyDefaulted() const;
    bool setFanMotorEfficiency(double fanMotorEfficiency);
    void resetFanMotorEfficiency();

    std::string baseboardHeatingType() const;
    bool isBaseboardHeatingTypeDefaulted() const;
    bool setBaseboardHeatingType(const std::string& baseboardHeatingType);
    void resetBaseboardHeatingType();

    boost::optional<double> baseboardHeatingCapacity() const;
    bool isBaseboardHeatingCapacityDefaulted() const;
    bool isBaseboardHeatingCapacityAutosized() const;
    bool setBaseboardHeatingCapacity(double baseboardHeatingCapacity);
    void resetBaseboardHeatingCapacity();
    void autosizeBaseboardHeatingCapacity();

    std::string zoneCoolingDesignSupplyAirTemperatureInputMethod() const;
    bool isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const;
    bool setZoneCoolingDesignSupplyAirTemperatureInputMethod(const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod);
    void resetZoneCoolingDesignSupplyAirTemperatureInputMethod();

    double zoneCoolingDesignSupplyAirTemperature() const;
    bool isZoneCoolingDesignSupplyAirTemperatureDefaulted() const;
    bool setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature);
    void resetZoneCoolingDesignSupplyAirTemperature();

    double zoneCoolingDesignSupplyAirTemperatureDifference() const;
    bool isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const;
    bool setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference);
    void resetZoneCoolingDesignSupplyAirTemperatureDifference();

    std::string zoneHeatingDesignSupplyAirTemperatureInputMethod() const;
    bool isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const;
    bool setZoneHeatingDesignSupplyAirTemperatureInputMethod(const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod);
    void resetZoneHeatingDesignSupplyAirTemperatureInputMethod();

    double zoneHeatingDesignSupplyAirTemperature() const;
    bool isZoneHeatingDesignSupplyAirTemperatureDefaulted() const;
    bool setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature);
    void resetZoneHeatingDesignSupplyAirTemperature();

    double zoneHeatingDesignSupplyAirTemperatureDifference() const;
    bool isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const;
    bool setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference);
    void resetZoneHeatingDesignSupplyAirTemperatureDifference();

   protected:
    using ImplType = detail::HVACTemplateZoneVAVFanPowered_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HVACTemplateZoneVAVFanPowered(std::shared_ptr<detail::HVACTemplateZoneVAVFanPowered_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
