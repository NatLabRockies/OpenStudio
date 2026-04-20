/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEZONEFANCOIL_HPP
#define EPMODEL_HVACTEMPLATEZONEFANCOIL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HVACTemplateZoneFanCoil_Impl;
  }

  class EPMODEL_API HVACTemplateZoneFanCoil : public ModelObject
  {
   public:
    explicit HVACTemplateZoneFanCoil(const Model& model);

    virtual ~HVACTemplateZoneFanCoil() override = default;
    HVACTemplateZoneFanCoil(const HVACTemplateZoneFanCoil& other) = default;
    HVACTemplateZoneFanCoil(HVACTemplateZoneFanCoil&& other) = default;
    HVACTemplateZoneFanCoil& operator=(const HVACTemplateZoneFanCoil&) = default;
    HVACTemplateZoneFanCoil& operator=(HVACTemplateZoneFanCoil&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> outdoorAirMethodValues();
    static std::vector<std::string> coolingCoilTypeValues();
    static std::vector<std::string> heatingCoilTypeValues();
    static std::vector<std::string> zoneCoolingDesignSupplyAirTemperatureInputMethodValues();
    static std::vector<std::string> zoneHeatingDesignSupplyAirTemperatureInputMethodValues();
    static std::vector<std::string> capacityControlMethodValues();
    static std::vector<std::string> baseboardHeatingTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to HVACTemplate:Zone:FanCoil non-name, non-link scalar fields.
    // - Field Mapping: Zone/Thermostat/Schedule/DOAS/DesignSpecification object-list fields are relationship fields
    //   and are intentionally excluded from scalar-only scaffold.
    // - TODO(parity): Add relationship/object-link APIs in a later parity pass without changing scalar signatures.

    // supplyAirMaximumFlowRate
    boost::optional<double> supplyAirMaximumFlowRate() const;
    bool isSupplyAirMaximumFlowRateDefaulted() const;
    bool isSupplyAirMaximumFlowRateAutosized() const;
    bool setSupplyAirMaximumFlowRate(double supplyAirMaximumFlowRate);
    void resetSupplyAirMaximumFlowRate();
    void autosizeSupplyAirMaximumFlowRate();

    // zoneHeatingSizingFactor
    boost::optional<double> zoneHeatingSizingFactor() const;
    bool setZoneHeatingSizingFactor(double zoneHeatingSizingFactor);
    void resetZoneHeatingSizingFactor();

    // zoneCoolingSizingFactor
    boost::optional<double> zoneCoolingSizingFactor() const;
    bool setZoneCoolingSizingFactor(double zoneCoolingSizingFactor);
    void resetZoneCoolingSizingFactor();

    // outdoorAirMethod
    std::string outdoorAirMethod() const;
    bool isOutdoorAirMethodDefaulted() const;
    bool setOutdoorAirMethod(const std::string& outdoorAirMethod);
    void resetOutdoorAirMethod();

    // outdoorAirFlowRateperPerson
    double outdoorAirFlowRateperPerson() const;
    bool isOutdoorAirFlowRateperPersonDefaulted() const;
    bool setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson);
    void resetOutdoorAirFlowRateperPerson();

    // outdoorAirFlowRateperZoneFloorArea
    double outdoorAirFlowRateperZoneFloorArea() const;
    bool isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const;
    bool setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea);
    void resetOutdoorAirFlowRateperZoneFloorArea();

    // outdoorAirFlowRateperZone
    double outdoorAirFlowRateperZone() const;
    bool isOutdoorAirFlowRateperZoneDefaulted() const;
    bool setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone);
    void resetOutdoorAirFlowRateperZone();

    // supplyFanTotalEfficiency
    double supplyFanTotalEfficiency() const;
    bool isSupplyFanTotalEfficiencyDefaulted() const;
    bool setSupplyFanTotalEfficiency(double supplyFanTotalEfficiency);
    void resetSupplyFanTotalEfficiency();

    // supplyFanDeltaPressure
    double supplyFanDeltaPressure() const;
    bool isSupplyFanDeltaPressureDefaulted() const;
    bool setSupplyFanDeltaPressure(double supplyFanDeltaPressure);
    void resetSupplyFanDeltaPressure();

    // supplyFanMotorEfficiency
    double supplyFanMotorEfficiency() const;
    bool isSupplyFanMotorEfficiencyDefaulted() const;
    bool setSupplyFanMotorEfficiency(double supplyFanMotorEfficiency);
    void resetSupplyFanMotorEfficiency();

    // supplyFanMotorinAirStreamFraction
    double supplyFanMotorinAirStreamFraction() const;
    bool isSupplyFanMotorinAirStreamFractionDefaulted() const;
    bool setSupplyFanMotorinAirStreamFraction(double supplyFanMotorinAirStreamFraction);
    void resetSupplyFanMotorinAirStreamFraction();

    // coolingCoilType
    std::string coolingCoilType() const;
    bool isCoolingCoilTypeDefaulted() const;
    bool setCoolingCoilType(const std::string& coolingCoilType);
    void resetCoolingCoilType();

    // coolingCoilDesignSetpoint
    double coolingCoilDesignSetpoint() const;
    bool isCoolingCoilDesignSetpointDefaulted() const;
    bool setCoolingCoilDesignSetpoint(double coolingCoilDesignSetpoint);
    void resetCoolingCoilDesignSetpoint();

    // heatingCoilType
    std::string heatingCoilType() const;
    bool isHeatingCoilTypeDefaulted() const;
    bool setHeatingCoilType(const std::string& heatingCoilType);
    void resetHeatingCoilType();

    // heatingCoilDesignSetpoint
    double heatingCoilDesignSetpoint() const;
    bool isHeatingCoilDesignSetpointDefaulted() const;
    bool setHeatingCoilDesignSetpoint(double heatingCoilDesignSetpoint);
    void resetHeatingCoilDesignSetpoint();

    // zoneCoolingDesignSupplyAirTemperatureInputMethod
    std::string zoneCoolingDesignSupplyAirTemperatureInputMethod() const;
    bool isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const;
    bool setZoneCoolingDesignSupplyAirTemperatureInputMethod(const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod);
    void resetZoneCoolingDesignSupplyAirTemperatureInputMethod();

    // zoneCoolingDesignSupplyAirTemperatureDifference
    double zoneCoolingDesignSupplyAirTemperatureDifference() const;
    bool isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const;
    bool setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference);
    void resetZoneCoolingDesignSupplyAirTemperatureDifference();

    // zoneHeatingDesignSupplyAirTemperatureInputMethod
    std::string zoneHeatingDesignSupplyAirTemperatureInputMethod() const;
    bool isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const;
    bool setZoneHeatingDesignSupplyAirTemperatureInputMethod(const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod);
    void resetZoneHeatingDesignSupplyAirTemperatureInputMethod();

    // zoneHeatingDesignSupplyAirTemperatureDifference
    double zoneHeatingDesignSupplyAirTemperatureDifference() const;
    bool isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const;
    bool setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference);
    void resetZoneHeatingDesignSupplyAirTemperatureDifference();

    // capacityControlMethod
    boost::optional<std::string> capacityControlMethod() const;
    bool setCapacityControlMethod(const std::string& capacityControlMethod);
    void resetCapacityControlMethod();

    // lowSpeedSupplyAirFlowRatio
    double lowSpeedSupplyAirFlowRatio() const;
    bool isLowSpeedSupplyAirFlowRatioDefaulted() const;
    bool setLowSpeedSupplyAirFlowRatio(double lowSpeedSupplyAirFlowRatio);
    void resetLowSpeedSupplyAirFlowRatio();

    // mediumSpeedSupplyAirFlowRatio
    double mediumSpeedSupplyAirFlowRatio() const;
    bool isMediumSpeedSupplyAirFlowRatioDefaulted() const;
    bool setMediumSpeedSupplyAirFlowRatio(double mediumSpeedSupplyAirFlowRatio);
    void resetMediumSpeedSupplyAirFlowRatio();

    // baseboardHeatingType
    std::string baseboardHeatingType() const;
    bool isBaseboardHeatingTypeDefaulted() const;
    bool setBaseboardHeatingType(const std::string& baseboardHeatingType);
    void resetBaseboardHeatingType();

    // baseboardHeatingCapacity
    boost::optional<double> baseboardHeatingCapacity() const;
    bool isBaseboardHeatingCapacityDefaulted() const;
    bool isBaseboardHeatingCapacityAutosized() const;
    bool setBaseboardHeatingCapacity(double baseboardHeatingCapacity);
    void resetBaseboardHeatingCapacity();
    void autosizeBaseboardHeatingCapacity();

   protected:
    using ImplType = detail::HVACTemplateZoneFanCoil_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HVACTemplateZoneFanCoil(std::shared_ptr<detail::HVACTemplateZoneFanCoil_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
