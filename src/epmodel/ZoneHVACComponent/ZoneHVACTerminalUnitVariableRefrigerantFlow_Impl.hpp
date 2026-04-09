/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACTERMINALUNITVARIABLEREFRIGERANTFLOW_IMPL_HPP
#define EPMODEL_ZONEHVACTERMINALUNITVARIABLEREFRIGERANTFLOW_IMPL_HPP

#include "ZoneHVACComponent_Impl.hpp"

#include <utilities/idd/ZoneHVAC_TerminalUnit_VariableRefrigerantFlow_FieldEnums.hxx>

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  class HVACComponent;
  class Node;
  class Schedule;
  class ThermalZone;

  namespace detail {
    struct LoadContext;

    class EPMODEL_API ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl() override = default;

      Schedule terminalUnitAvailabilityschedule() const;
      bool setTerminalUnitAvailabilityschedule(Schedule& schedule);

      boost::optional<double> supplyAirFlowRateDuringCoolingOperation() const;
      bool isSupplyAirFlowRateDuringCoolingOperationAutosized() const;
      bool setSupplyAirFlowRateDuringCoolingOperation(boost::optional<double> supplyAirFlowRateDuringCoolingOperation);
      void autosizeSupplyAirFlowRateDuringCoolingOperation();

      boost::optional<double> supplyAirFlowRateWhenNoCoolingisNeeded() const;
      bool isSupplyAirFlowRateWhenNoCoolingisNeededAutosized() const;
      bool setSupplyAirFlowRateWhenNoCoolingisNeeded(boost::optional<double> supplyAirFlowRateWhenNoCoolingisNeeded);
      void resetSupplyAirFlowRateWhenNoCoolingisNeeded();
      void autosizeSupplyAirFlowRateWhenNoCoolingisNeeded();

      boost::optional<double> supplyAirFlowRateDuringHeatingOperation() const;
      bool isSupplyAirFlowRateDuringHeatingOperationAutosized() const;
      bool setSupplyAirFlowRateDuringHeatingOperation(boost::optional<double> supplyAirFlowRateDuringHeatingOperation);
      void autosizeSupplyAirFlowRateDuringHeatingOperation();

      boost::optional<double> supplyAirFlowRateWhenNoHeatingisNeeded() const;
      bool isSupplyAirFlowRateWhenNoHeatingisNeededAutosized() const;
      bool setSupplyAirFlowRateWhenNoHeatingisNeeded(boost::optional<double> supplyAirFlowRateWhenNoHeatingisNeeded);
      void resetSupplyAirFlowRateWhenNoHeatingisNeeded();
      void autosizeSupplyAirFlowRateWhenNoHeatingisNeeded();

      boost::optional<double> outdoorAirFlowRateDuringCoolingOperation() const;
      bool isOutdoorAirFlowRateDuringCoolingOperationAutosized() const;
      bool setOutdoorAirFlowRateDuringCoolingOperation(boost::optional<double> outdoorAirFlowRateDuringCoolingOperation);
      void autosizeOutdoorAirFlowRateDuringCoolingOperation();

      boost::optional<double> outdoorAirFlowRateDuringHeatingOperation() const;
      bool isOutdoorAirFlowRateDuringHeatingOperationAutosized() const;
      bool setOutdoorAirFlowRateDuringHeatingOperation(boost::optional<double> outdoorAirFlowRateDuringHeatingOperation);
      void autosizeOutdoorAirFlowRateDuringHeatingOperation();

      boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
      bool isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
      bool setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
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
      bool setSupplyAirFan(const HVACComponent& fan);

      Schedule supplyAirFanOperatingModeSchedule() const;
      bool setSupplyAirFanOperatingModeSchedule(Schedule& schedule);

      boost::optional<HVACComponent> coolingCoil() const;
      bool setCoolingCoil(const HVACComponent& coil);

      boost::optional<HVACComponent> heatingCoil() const;
      bool setHeatingCoil(const HVACComponent& coil);

      boost::optional<HVACComponent> supplementalHeatingCoil() const;
      bool setSupplementalHeatingCoil(const HVACComponent& coil);
      void resetSupplementalHeatingCoil();

      boost::optional<Node> fanOutletNode() const;
      boost::optional<Node> coolingCoilOutletNode() const;
      boost::optional<Node> heatingCoilOutletNode() const;

      boost::optional<ThermalZone> controllingZoneorThermostatLocation() const;
      bool setControllingZoneorThermostatLocation(const ThermalZone& thermalZone);
      void resetControllingZoneorThermostatLocation();

      std::vector<ModelObject> children() const override;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToThermalZone(ThermalZone& thermalZone) override;
      void removeFromThermalZone() override;
      void doCanonicalize(LoadContext& context) override;

      bool isFluidTemperatureControl() const;

      boost::optional<double> autosizedSupplyAirFlowRateDuringCoolingOperation() const;
      boost::optional<double> autosizedSupplyAirFlowRateWhenNoCoolingisNeeded() const;
      boost::optional<double> autosizedSupplyAirFlowRateDuringHeatingOperation() const;
      boost::optional<double> autosizedSupplyAirFlowRateWhenNoHeatingisNeeded() const;
      boost::optional<double> autosizedOutdoorAirFlowRateDuringCoolingOperation() const;
      boost::optional<double> autosizedOutdoorAirFlowRateDuringHeatingOperation() const;
      boost::optional<double> autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const;

     private:
      bool maintainContainedAirPath();
      bool repairContainedAirPath(LoadContext& context);
      bool reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context = nullptr);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
