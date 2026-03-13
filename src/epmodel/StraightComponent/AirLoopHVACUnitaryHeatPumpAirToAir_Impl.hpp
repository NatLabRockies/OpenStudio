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

  namespace detail {

    class EPMODEL_API AirLoopHVACUnitaryHeatPumpAirToAir_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~AirLoopHVACUnitaryHeatPumpAirToAir_Impl() override = default;
      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToNode(Node& node) override;

      std::vector<std::string> validFanPlacementValues() const;
      std::vector<std::string> validDehumidificationControlTypeValues() const;

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

      // Dehumidification control
      std::string dehumidificationControlType() const;
      bool isDehumidificationControlTypeDefaulted() const;
      bool setDehumidificationControlType(const std::string& dehumidificationControlType);
      void resetDehumidificationControlType();

      // Heating coil sizing ratio
      double dXHeatingCoilSizingRatio() const;
      bool setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
