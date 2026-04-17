/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACUNITARYHEATPUMPAIRTOAIR_IMPL_HPP
#define EPMODEL_AIRLOOPHVACUNITARYHEATPUMPAIRTOAIR_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
  class Node;
  class HVACComponent;
  class Schedule;
  class ThermalZone;

  namespace detail {
    struct LoadContext;

    class EPMODEL_API AirLoopHVACUnitaryHeatPumpAirToAir_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~AirLoopHVACUnitaryHeatPumpAirToAir_Impl() override = default;
      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToNode(Node& node) override;
      void doCanonicalize(LoadContext& context) override;
      std::vector<ModelObject> children() const override;

	      std::vector<std::string> validFanPlacementValues() const;
	      std::vector<std::string> validDehumidificationControlTypeValues() const;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      // Cooling operation supply air flow rate
      boost::optional<double> supplyAirFlowRateDuringCoolingOperation() const;
      bool isSupplyAirFlowRateDuringCoolingOperationAutosized() const;
      bool setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation);
      void autosizeSupplyAirFlowRateDuringCoolingOperation();

      // Heating operation supply air flow rate
      boost::optional<double> supplyAirFlowRateDuringHeatingOperation() const;
      bool isSupplyAirFlowRateDuringHeatingOperationAutosized() const;
      bool setSupplyAirFlowRateDuringHeatingOperation(double n2);
      void autosizeSupplyAirFlowRateDuringHeatingOperation();

      // No-load supply air flow rate
      boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
      bool isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
      bool setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
	      void resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
	      void autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();

      boost::optional<ThermalZone> controllingZone() const;
      bool setControllingZone(ThermalZone& zone);
      void resetControllingZone();

      HVACComponent supplyAirFan() const;
      bool setSupplyAirFan(HVACComponent& hvacComponent);

      HVACComponent heatingCoil() const;
      bool setHeatingCoil(HVACComponent& hvacComponent);

      HVACComponent coolingCoil() const;
      bool setCoolingCoil(HVACComponent& hvacComponent);

      HVACComponent supplementalHeatingCoil() const;
      bool setSupplementalHeatingCoil(HVACComponent& hvacComponent);

      boost::optional<Node> fanOutletNode() const;
      boost::optional<Node> coolingCoilOutletNode() const;
      boost::optional<Node> heatingCoilOutletNode() const;

      // Supplemental heater supply air temperature
      boost::optional<double> maximumSupplyAirTemperaturefromSupplementalHeater() const;
      bool isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const;
      bool setMaximumSupplyAirTemperaturefromSupplementalHeater(double maximumSupplyAirTemperaturefromSupplementalHeater);
      void autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();

      // Supplemental heater outdoor dry-bulb temperature
      double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const;
      bool isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const;
      bool setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
      void resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();

      // Fan placement selection
      std::string fanPlacement() const;
      bool isFanPlacementDefaulted() const;
	      bool setFanPlacement(const std::string& fanPlacement);
	      void resetFanPlacement();

      boost::optional<Schedule> supplyAirFanOperatingModeSchedule() const;
      bool setSupplyAirFanOperatingModeSchedule(Schedule& schedule);
      void resetSupplyAirFanOperatingModeSchedule();

	      // Dehumidification control
      std::string dehumidificationControlType() const;
      bool isDehumidificationControlTypeDefaulted() const;
      bool setDehumidificationControlType(const std::string& dehumidificationControlType);
      void resetDehumidificationControlType();

      // Heating coil sizing ratio
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
