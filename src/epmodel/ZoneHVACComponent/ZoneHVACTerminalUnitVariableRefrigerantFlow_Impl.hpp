/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACTERMINALUNITVARIABLEREFRIGERANTFLOW_IMPL_HPP
#define EPMODEL_ZONEHVACTERMINALUNITVARIABLEREFRIGERANTFLOW_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <utilities/idd/OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlow_FieldEnums.hxx>

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl() override = default;

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

      boost::optional<double> autosizedSupplyAirFlowRateDuringCoolingOperation() const;
      boost::optional<double> autosizedSupplyAirFlowRateWhenNoCoolingisNeeded() const;
      boost::optional<double> autosizedSupplyAirFlowRateDuringHeatingOperation() const;
      boost::optional<double> autosizedSupplyAirFlowRateWhenNoHeatingisNeeded() const;
      boost::optional<double> autosizedOutdoorAirFlowRateDuringCoolingOperation() const;
      boost::optional<double> autosizedOutdoorAirFlowRateDuringHeatingOperation() const;
      boost::optional<double> autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
