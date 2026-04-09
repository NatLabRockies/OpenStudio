/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACWATERTOAIRHEATPUMP_IMPL_HPP
#define EPMODEL_ZONEHVACWATERTOAIRHEATPUMP_IMPL_HPP

#include "ZoneHVACComponent_Impl.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {

  class HVACComponent;
  class Node;
  class Schedule;
  class ThermalZone;

  namespace detail {
    struct LoadContext;

    class EPMODEL_API ZoneHVACWaterToAirHeatPump_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneHVACWaterToAirHeatPump_Impl() override = default;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      boost::optional<double> supplyAirFlowRateDuringCoolingOperation() const;
      bool isSupplyAirFlowRateDuringCoolingOperationAutosized() const;
      boost::optional<double> autosizedSupplyAirFlowRateDuringCoolingOperation() const;
      bool setSupplyAirFlowRateDuringCoolingOperation(boost::optional<double> supplyAirFlowRateDuringCoolingOperation);
      bool setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation);
      void resetSupplyAirFlowRateDuringCoolingOperation();
      void autosizeSupplyAirFlowRateDuringCoolingOperation();

      boost::optional<double> supplyAirFlowRateDuringHeatingOperation() const;
      bool isSupplyAirFlowRateDuringHeatingOperationAutosized() const;
      boost::optional<double> autosizedSupplyAirFlowRateDuringHeatingOperation() const;
      bool setSupplyAirFlowRateDuringHeatingOperation(boost::optional<double> supplyAirFlowRateDuringHeatingOperation);
      bool setSupplyAirFlowRateDuringHeatingOperation(double supplyAirFlowRateDuringHeatingOperation);
      void resetSupplyAirFlowRateDuringHeatingOperation();
      void autosizeSupplyAirFlowRateDuringHeatingOperation();

      boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
      bool isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
      boost::optional<double> autosizedSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
      bool setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
      bool setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
      void resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
      void autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();

      bool noLoadSupplyAirFlowRateControlSetToLowSpeed() const;
      bool setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool noLoadSupplyAirFlowRateControlSetToLowSpeed);

      boost::optional<double> outdoorAirFlowRateDuringCoolingOperation() const;
      bool isOutdoorAirFlowRateDuringCoolingOperationAutosized() const;
      boost::optional<double> autosizedOutdoorAirFlowRateDuringCoolingOperation() const;
      bool setOutdoorAirFlowRateDuringCoolingOperation(boost::optional<double> outdoorAirFlowRateDuringCoolingOperation);
      bool setOutdoorAirFlowRateDuringCoolingOperation(double outdoorAirFlowRateDuringCoolingOperation);
      void resetOutdoorAirFlowRateDuringCoolingOperation();
      void autosizeOutdoorAirFlowRateDuringCoolingOperation();

      boost::optional<double> outdoorAirFlowRateDuringHeatingOperation() const;
      bool isOutdoorAirFlowRateDuringHeatingOperationAutosized() const;
      boost::optional<double> autosizedOutdoorAirFlowRateDuringHeatingOperation() const;
      bool setOutdoorAirFlowRateDuringHeatingOperation(boost::optional<double> outdoorAirFlowRateDuringHeatingOperation);
      bool setOutdoorAirFlowRateDuringHeatingOperation(double outdoorAirFlowRateDuringHeatingOperation);
      void resetOutdoorAirFlowRateDuringHeatingOperation();
      void autosizeOutdoorAirFlowRateDuringHeatingOperation();

      boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
      bool isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
      boost::optional<double> autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
      bool setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
      bool setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(double outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
      void resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
      void autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();

      boost::optional<double> maximumSupplyAirTemperaturefromSupplementalHeater() const;
      bool isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const;
      boost::optional<double> autosizedMaximumSupplyAirTemperaturefromSupplementalHeater() const;
      bool setMaximumSupplyAirTemperaturefromSupplementalHeater(boost::optional<double> maximumSupplyAirTemperaturefromSupplementalHeater);
      bool setMaximumSupplyAirTemperaturefromSupplementalHeater(double maximumSupplyAirTemperaturefromSupplementalHeater);
      void resetMaximumSupplyAirTemperaturefromSupplementalHeater();
      void autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();

      double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const;
      bool isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const;
      bool setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
        boost::optional<double> maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
      bool setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
      void resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();

      std::string fanPlacement() const;
      bool isFanPlacementDefaulted() const;
      bool setFanPlacement(const std::string& fanPlacement);
      void resetFanPlacement();

      std::string heatPumpCoilWaterFlowMode() const;
      bool isHeatPumpCoilWaterFlowModeDefaulted() const;
      bool setHeatPumpCoilWaterFlowMode(const std::string& heatPumpCoilWaterFlowMode);
      void resetHeatPumpCoilWaterFlowMode();

      boost::optional<Schedule> supplyAirFanOperatingModeSchedule() const;
      bool setSupplyAirFanOperatingModeSchedule(Schedule& schedule);
      void resetSupplyAirFanOperatingModeSchedule();

      HVACComponent supplyAirFan() const;
      bool setSupplyAirFan(const HVACComponent& supplyAirFan);

      HVACComponent heatingCoil() const;
      bool setHeatingCoil(const HVACComponent& heatingCoil);

      HVACComponent coolingCoil() const;
      bool setCoolingCoil(const HVACComponent& coolingCoil);

      HVACComponent supplementalHeatingCoil() const;
      bool setSupplementalHeatingCoil(const HVACComponent& supplementalHeatingCoil);

      boost::optional<Node> fanOutletNode() const;
      boost::optional<Node> coolingCoilOutletNode() const;
      boost::optional<Node> heatingCoilOutletNode() const;

      std::vector<ModelObject> children() const override;
      unsigned inletPort() const override;
      unsigned outletPort() const override;

      bool addToThermalZone(ThermalZone& thermalZone) override;
      void removeFromThermalZone() override;
      void doCanonicalize(LoadContext& context) override;

      double dXHeatingCoilSizingRatio() const;
      bool setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio);

     private:
      bool maintainContainedAirPath();
      bool repairContainedAirPath(LoadContext& context);
      bool reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context = nullptr);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
