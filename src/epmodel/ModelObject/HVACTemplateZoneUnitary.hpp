/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEZONEUNITARY_HPP
#define EPMODEL_HVACTEMPLATEZONEUNITARY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HVACTemplateZoneUnitary_Impl;
  }

  class EPMODEL_API HVACTemplateZoneUnitary : public ModelObject
  {
   public:
    explicit HVACTemplateZoneUnitary(const Model& model);

    virtual ~HVACTemplateZoneUnitary() override = default;
    HVACTemplateZoneUnitary(const HVACTemplateZoneUnitary& other) = default;
    HVACTemplateZoneUnitary(HVACTemplateZoneUnitary&& other) = default;
    HVACTemplateZoneUnitary& operator=(const HVACTemplateZoneUnitary&) = default;
    HVACTemplateZoneUnitary& operator=(HVACTemplateZoneUnitary&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> outdoorAirMethodValues();
    static std::vector<std::string> baseboardHeatingTypeValues();
    static std::vector<std::string> zoneCoolingDesignSupplyAirTemperatureInputMethodValues();
    static std::vector<std::string> zoneHeatingDesignSupplyAirTemperatureInputMethodValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to HVACTemplate:Zone:Unitary non-name, non-link scalar fields.
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
    using ImplType = detail::HVACTemplateZoneUnitary_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HVACTemplateZoneUnitary(std::shared_ptr<detail::HVACTemplateZoneUnitary_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
