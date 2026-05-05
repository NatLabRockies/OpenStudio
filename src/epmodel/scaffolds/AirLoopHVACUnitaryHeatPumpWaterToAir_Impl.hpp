/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACUNITARYHEATPUMPWATERTOAIR_IMPL_HPP
#define EPMODEL_AIRLOOPHVACUNITARYHEATPUMPWATERTOAIR_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AirLoopHVACUnitaryHeatPumpWaterToAir_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AirLoopHVACUnitaryHeatPumpWaterToAir_Impl() override = default;

      boost::optional<double> supplyAirFlowRate() const;
      bool isSupplyAirFlowRateAutosized() const;
      bool setSupplyAirFlowRate(double supplyAirFlowRate);
      void autosizeSupplyAirFlowRate();

      std::string supplyAirFanObjectType() const;
      bool setSupplyAirFanObjectType(const std::string& supplyAirFanObjectType);

      std::string heatingCoilObjectType() const;
      bool setHeatingCoilObjectType(const std::string& heatingCoilObjectType);

      double heatingConvergence() const;
      bool isHeatingConvergenceDefaulted() const;
      bool setHeatingConvergence(double heatingConvergence);
      void resetHeatingConvergence();

      std::string coolingCoilObjectType() const;
      bool setCoolingCoilObjectType(const std::string& coolingCoilObjectType);

      double coolingConvergence() const;
      bool isCoolingConvergenceDefaulted() const;
      bool setCoolingConvergence(double coolingConvergence);
      void resetCoolingConvergence();

      std::string supplementalHeatingCoilObjectType() const;
      bool setSupplementalHeatingCoilObjectType(const std::string& supplementalHeatingCoilObjectType);

      boost::optional<double> maximumSupplyAirTemperaturefromSupplementalHeater() const;
      bool isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const;
      bool setMaximumSupplyAirTemperaturefromSupplementalHeater(double maximumSupplyAirTemperaturefromSupplementalHeater);
      void autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();

      double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const;
      bool isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const;
      bool setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
      void resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();

      std::string fanPlacement() const;
      bool isFanPlacementDefaulted() const;
      bool setFanPlacement(const std::string& fanPlacement);
      void resetFanPlacement();

      std::string dehumidificationControlType() const;
      bool isDehumidificationControlTypeDefaulted() const;
      bool setDehumidificationControlType(const std::string& dehumidificationControlType);
      void resetDehumidificationControlType();

      std::string heatPumpCoilWaterFlowMode() const;
      bool isHeatPumpCoilWaterFlowModeDefaulted() const;
      bool setHeatPumpCoilWaterFlowMode(const std::string& heatPumpCoilWaterFlowMode);
      void resetHeatPumpCoilWaterFlowMode();

      double dXHeatingCoilSizingRatio() const;
      bool isDXHeatingCoilSizingRatioDefaulted() const;
      bool setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio);
      void resetDXHeatingCoilSizingRatio();

      std::vector<std::string> supplyAirFanObjectTypeValues() const;
      std::vector<std::string> heatingCoilObjectTypeValues() const;
      std::vector<std::string> coolingCoilObjectTypeValues() const;
      std::vector<std::string> supplementalHeatingCoilObjectTypeValues() const;
      std::vector<std::string> fanPlacementValues() const;
      std::vector<std::string> dehumidificationControlTypeValues() const;
      std::vector<std::string> heatPumpCoilWaterFlowModeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
