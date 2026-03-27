/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACTERMINALUNITVARIABLEREFRIGERANTFLOW_HPP
#define EPMODEL_ZONEHVACTERMINALUNITVARIABLEREFRIGERANTFLOW_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent.hpp"

#include <utilities/idd/ZoneHVAC_TerminalUnit_VariableRefrigerantFlow_FieldEnums.hxx>
#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class HVACComponent;
  class ModelObject;

  namespace detail {
    class ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl;
  }

  class EPMODEL_API ZoneHVACTerminalUnitVariableRefrigerantFlow : public ZoneHVACComponent
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
    // - Status: Partial Parity. The scalar VRF terminal fields are aligned, but the fan/coil/schedule/node relationships remain separate.
    // - Canonical Counterpart: openstudio::model::ZoneHVACTerminalUnitVariableRefrigerantFlow.
    // - Implemented Parity: Supply-air and outdoor-air flow scalars, parasitic electric loads, rated heating ratio, supplemental-heater limits, and fan-placement helpers map directly to the EnergyPlus object.
    // - Documented Delta: Availability schedules, fan operating-mode schedules, child fan/coil links, node names, and controlling-zone references remain relationship-only.
    // - Field/Storage Mapping: Scalar values live directly on the EnergyPlus object while the fan/coil/schedule/node topology is represented through explicit child and topology state.
    // - Evidence: `src/model/ZoneHVACTerminalUnitVariableRefrigerantFlow.hpp`, `src/model/ZoneHVACTerminalUnitVariableRefrigerantFlow.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACTerminalUnitVariableRefrigerantFlow.cpp`, and `src/epmodel/test/ZoneHVACTerminalUnitVariableRefrigerantFlow_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted relationship helpers only if the canonical wrapper still exposes them directly.

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

    HVACComponent supplyAirFan() const;
    bool setSupplyAirFan(HVACComponent& fan);

    boost::optional<HVACComponent> coolingCoil() const;
    bool setCoolingCoil(HVACComponent& coil);

    boost::optional<HVACComponent> heatingCoil() const;
    bool setHeatingCoil(HVACComponent& coil);

    boost::optional<HVACComponent> supplementalHeatingCoil() const;
    bool setSupplementalHeatingCoil(HVACComponent& coil);
    void resetSupplementalHeatingCoil();

    std::vector<ModelObject> children() const;

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
