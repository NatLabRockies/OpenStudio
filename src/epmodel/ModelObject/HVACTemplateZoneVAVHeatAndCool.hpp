/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEZONEVAVHEATANDCOOL_HPP
#define EPMODEL_HVACTEMPLATEZONEVAVHEATANDCOOL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HVACTemplateZoneVAVHeatAndCool_Impl;
  }

  class EPMODEL_API HVACTemplateZoneVAVHeatAndCool : public ModelObject
  {
   public:
    explicit HVACTemplateZoneVAVHeatAndCool(const Model& model);

    virtual ~HVACTemplateZoneVAVHeatAndCool() override = default;
    HVACTemplateZoneVAVHeatAndCool(const HVACTemplateZoneVAVHeatAndCool& other) = default;
    HVACTemplateZoneVAVHeatAndCool(HVACTemplateZoneVAVHeatAndCool&& other) = default;
    HVACTemplateZoneVAVHeatAndCool& operator=(const HVACTemplateZoneVAVHeatAndCool&) = default;
    HVACTemplateZoneVAVHeatAndCool& operator=(HVACTemplateZoneVAVHeatAndCool&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> outdoorAirMethodValues();
    static std::vector<std::string> reheatCoilTypeValues();
    static std::vector<std::string> baseboardHeatingTypeValues();
    static std::vector<std::string> zoneCoolingDesignSupplyAirTemperatureInputMethodValues();
    static std::vector<std::string> zoneHeatingDesignSupplyAirTemperatureInputMethodValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to HVACTemplate:Zone:VAV:HeatAndCool non-link scalar fields.
    // - Field Mapping: Zone/System/Thermostat/Schedule/Plenum/DesignSpecification name fields are object-list relationship
    //   fields and are intentionally excluded from scalar-only scaffold.
    // - TODO(parity): Revisit only if a future parity pass introduces relationship/object-link APIs.
    boost::optional<double> supplyAirMaximumFlowRate() const;
    bool isSupplyAirMaximumFlowRateDefaulted() const;
    bool isSupplyAirMaximumFlowRateAutosized() const;
    bool setSupplyAirMaximumFlowRate(double supplyAirMaximumFlowRate);
    void resetSupplyAirMaximumFlowRate();
    void autosizeSupplyAirMaximumFlowRate();

    boost::optional<double> zoneHeatingSizingFactor() const;
    bool setZoneHeatingSizingFactor(double zoneHeatingSizingFactor);
    void resetZoneHeatingSizingFactor();

    boost::optional<double> zoneCoolingSizingFactor() const;
    bool setZoneCoolingSizingFactor(double zoneCoolingSizingFactor);
    void resetZoneCoolingSizingFactor();

    double constantMinimumAirFlowFraction() const;
    bool isConstantMinimumAirFlowFractionDefaulted() const;
    bool setConstantMinimumAirFlowFraction(double constantMinimumAirFlowFraction);
    void resetConstantMinimumAirFlowFraction();

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

    boost::optional<double> maximumReheatAirTemperature() const;
    bool setMaximumReheatAirTemperature(double maximumReheatAirTemperature);
    void resetMaximumReheatAirTemperature();

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
    using ImplType = detail::HVACTemplateZoneVAVHeatAndCool_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HVACTemplateZoneVAVHeatAndCool(std::shared_ptr<detail::HVACTemplateZoneVAVHeatAndCool_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
