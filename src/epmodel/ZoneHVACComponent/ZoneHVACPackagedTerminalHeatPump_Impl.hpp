/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACPACKAGEDTERMINALHEATPUMP_IMPL_HPP
#define EPMODEL_ZONEHVACPACKAGEDTERMINALHEATPUMP_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <utilities/idd/ZoneHVAC_PackagedTerminalHeatPump_FieldEnums.hxx>

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACPackagedTerminalHeatPump_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneHVACPackagedTerminalHeatPump_Impl() override = default;

      boost::optional<double> supplyAirFlowRateDuringCoolingOperation() const;
      bool isSupplyAirFlowRateDuringCoolingOperationAutosized() const;
      bool setSupplyAirFlowRateDuringCoolingOperation(boost::optional<double> supplyAirFlowRateDuringCoolingOperation);
      void autosizeSupplyAirFlowRateDuringCoolingOperation();
      boost::optional<double> autosizedSupplyAirFlowRateDuringCoolingOperation() const;

      boost::optional<double> supplyAirFlowRateDuringHeatingOperation() const;
      bool isSupplyAirFlowRateDuringHeatingOperationAutosized() const;
      bool setSupplyAirFlowRateDuringHeatingOperation(boost::optional<double> supplyAirFlowRateDuringHeatingOperation);
      void autosizeSupplyAirFlowRateDuringHeatingOperation();
      boost::optional<double> autosizedSupplyAirFlowRateDuringHeatingOperation() const;

      boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
      bool isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
      bool setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
      void resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
      void autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
      boost::optional<double> autosizedSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const;

      bool noLoadSupplyAirFlowRateControlSetToLowSpeed() const;
      bool setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool noLoadSupplyAirFlowRateControlSetToLowSpeed);

      boost::optional<double> outdoorAirFlowRateDuringCoolingOperation() const;
      bool isOutdoorAirFlowRateDuringCoolingOperationAutosized() const;
      bool setOutdoorAirFlowRateDuringCoolingOperation(boost::optional<double> outdoorAirFlowRateDuringCoolingOperation);
      void autosizeOutdoorAirFlowRateDuringCoolingOperation();
      boost::optional<double> autosizedOutdoorAirFlowRateDuringCoolingOperation() const;

      boost::optional<double> outdoorAirFlowRateDuringHeatingOperation() const;
      bool isOutdoorAirFlowRateDuringHeatingOperationAutosized() const;
      bool setOutdoorAirFlowRateDuringHeatingOperation(boost::optional<double> outdoorAirFlowRateDuringHeatingOperation);
      void autosizeOutdoorAirFlowRateDuringHeatingOperation();
      boost::optional<double> autosizedOutdoorAirFlowRateDuringHeatingOperation() const;

      boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
      bool isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
      bool setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
      void resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
      void autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
      boost::optional<double> autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const;

      double heatingConvergenceTolerance() const;
      bool isHeatingConvergenceToleranceDefaulted() const;
      bool setHeatingConvergenceTolerance(double heatingConvergenceTolerance);
      void resetHeatingConvergenceTolerance();

      double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
      bool isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted() const;
      bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);
      void resetMinimumOutdoorDryBulbTemperatureforCompressorOperation();

      double coolingConvergenceTolerance() const;
      bool isCoolingConvergenceToleranceDefaulted() const;
      bool setCoolingConvergenceTolerance(double coolingConvergenceTolerance);
      void resetCoolingConvergenceTolerance();

      boost::optional<double> maximumSupplyAirTemperaturefromSupplementalHeater() const;
      bool isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const;
      bool setMaximumSupplyAirTemperaturefromSupplementalHeater(boost::optional<double> maximumSupplyAirTemperaturefromSupplementalHeater);
      void autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
      boost::optional<double> autosizedMaximumSupplyAirTemperaturefromSupplementalHeater() const;

      double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const;
      bool isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const;
      bool setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
      void resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();

      std::string fanPlacement() const;
      bool isFanPlacementDefaulted() const;
      bool setFanPlacement(const std::string& fanPlacement);
      void resetFanPlacement();

      double dXHeatingCoilSizingRatio() const;
      bool setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
