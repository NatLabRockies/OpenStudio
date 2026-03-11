/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACTERMINALUNITVARIABLEREFRIGERANTFLOW_HPP
#define EPMODEL_ZONEHVACTERMINALUNITVARIABLEREFRIGERANTFLOW_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/ZoneHVAC_TerminalUnit_VariableRefrigerantFlow_FieldEnums.hxx>
#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl;
  }

  class EPMODEL_API ZoneHVACTerminalUnitVariableRefrigerantFlow : public ModelObject
  {
   public:
    explicit ZoneHVACTerminalUnitVariableRefrigerantFlow(const Model& model);

    virtual ~ZoneHVACTerminalUnitVariableRefrigerantFlow() override = default;
    ZoneHVACTerminalUnitVariableRefrigerantFlow(const ZoneHVACTerminalUnitVariableRefrigerantFlow& other) = default;
    ZoneHVACTerminalUnitVariableRefrigerantFlow(ZoneHVACTerminalUnitVariableRefrigerantFlow&& other) = default;
    ZoneHVACTerminalUnitVariableRefrigerantFlow& operator=(const ZoneHVACTerminalUnitVariableRefrigerantFlow&) = default;
    ZoneHVACTerminalUnitVariableRefrigerantFlow& operator=(ZoneHVACTerminalUnitVariableRefrigerantFlow&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> supplyAirFanPlacementValues();

    // Schema Alignment Notes:
    // - API: the supply/outdoor air flow setters, fan placement helpers, parasitic electric, rated heating ratio, and supplemental
    //   heater scalars map directly to the EnergyPlus ZoneHVAC:TerminalUnit:VariableRefrigerantFlow fields enumerated by
    //   ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields; ForwardTranslateZoneHVACTerminalUnitVariableRefrigerantFlow.cpp maps these
    //   scalars while the EnergyPlus translator and idf writer handle the coil, fan, schedule, and node relationships separately.
    // - Field Mapping: relationship-like fields (TerminalUnitAvailabilitySchedule, SupplyAirFanOperatingModeScheduleName, SupplyAirFan,
    //   CoolingCoil, HeatingCoil, SupplementalHeatingCoil, node names, and controlling zone references) remain outside this scalar-only API.

    boost::optional<double> supplyAirFlowRateDuringCoolingOperation() const;
    bool isSupplyAirFlowRateDuringCoolingOperationAutosized() const;
    bool setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation);
    void autosizeSupplyAirFlowRateDuringCoolingOperation();

    boost::optional<double> supplyAirFlowRateWhenNoCoolingisNeeded() const;
    bool isSupplyAirFlowRateWhenNoCoolingisNeededAutosized() const;
    bool setSupplyAirFlowRateWhenNoCoolingisNeeded(double supplyAirFlowRateWhenNoCoolingisNeeded);
    void resetSupplyAirFlowRateWhenNoCoolingisNeeded();
    void autosizeSupplyAirFlowRateWhenNoCoolingisNeeded();

    boost::optional<double> supplyAirFlowRateDuringHeatingOperation() const;
    bool isSupplyAirFlowRateDuringHeatingOperationAutosized() const;
    bool setSupplyAirFlowRateDuringHeatingOperation(double supplyAirFlowRateDuringHeatingOperation);
    void autosizeSupplyAirFlowRateDuringHeatingOperation();

    boost::optional<double> supplyAirFlowRateWhenNoHeatingisNeeded() const;
    bool isSupplyAirFlowRateWhenNoHeatingisNeededAutosized() const;
    bool setSupplyAirFlowRateWhenNoHeatingisNeeded(double supplyAirFlowRateWhenNoHeatingisNeeded);
    void resetSupplyAirFlowRateWhenNoHeatingisNeeded();
    void autosizeSupplyAirFlowRateWhenNoHeatingisNeeded();

    boost::optional<double> outdoorAirFlowRateDuringCoolingOperation() const;
    bool isOutdoorAirFlowRateDuringCoolingOperationAutosized() const;
    bool setOutdoorAirFlowRateDuringCoolingOperation(double outdoorAirFlowRateDuringCoolingOperation);
    void autosizeOutdoorAirFlowRateDuringCoolingOperation();

    boost::optional<double> outdoorAirFlowRateDuringHeatingOperation() const;
    bool isOutdoorAirFlowRateDuringHeatingOperationAutosized() const;
    bool setOutdoorAirFlowRateDuringHeatingOperation(double outdoorAirFlowRateDuringHeatingOperation);
    void autosizeOutdoorAirFlowRateDuringHeatingOperation();

    boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
    bool isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
    bool setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(double outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
    void resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
    void autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();

    double zoneTerminalUnitOnParasiticElectricEnergyUse() const;
    bool setZoneTerminalUnitOnParasiticElectricEnergyUse(double zoneTerminalUnitOnParasiticElectricEnergyUse);

    double zoneTerminalUnitOffParasiticElectricEnergyUse() const;
    bool setZoneTerminalUnitOffParasiticElectricEnergyUse(double zoneTerminalUnitOffParasiticElectricEnergyUse);

    double ratedTotalHeatingCapacitySizingRatio() const;
    bool setRatedTotalHeatingCapacitySizingRatio(double ratedTotalHeatingCapacitySizingRatio);

    boost::optional<double> maximumSupplyAirTemperaturefromSupplementalHeater() const;
    bool isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const;
    bool setMaximumSupplyAirTemperaturefromSupplementalHeater(double maximumSupplyAirTemperaturefromSupplementalHeater);
    void autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();

    double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const;
    bool isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const;
    bool setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
    void resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();

    std::string supplyAirFanPlacement() const;
    bool isSupplyAirFanPlacementDefaulted() const;
    bool setSupplyAirFanPlacement(const std::string& supplyAirFanPlacement);
    void resetSupplyAirFanPlacement();

    boost::optional<double> autosizedSupplyAirFlowRateDuringCoolingOperation() const;
    boost::optional<double> autosizedSupplyAirFlowRateWhenNoCoolingisNeeded() const;
    boost::optional<double> autosizedSupplyAirFlowRateDuringHeatingOperation() const;
    boost::optional<double> autosizedSupplyAirFlowRateWhenNoHeatingisNeeded() const;
    boost::optional<double> autosizedOutdoorAirFlowRateDuringCoolingOperation() const;
    boost::optional<double> autosizedOutdoorAirFlowRateDuringHeatingOperation() const;
    boost::optional<double> autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const;

   protected:
    using ImplType = detail::ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl;

    explicit ZoneHVACTerminalUnitVariableRefrigerantFlow(std::shared_ptr<detail::ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
