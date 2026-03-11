/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACIDEALLOADSAIRSYSTEM_IMPL_HPP
#define EPMODEL_ZONEHVACIDEALLOADSAIRSYSTEM_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACIdealLoadsAirSystem_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneHVACIdealLoadsAirSystem_Impl() override = default;

      double maximumHeatingSupplyAirTemperature() const;
      bool isMaximumHeatingSupplyAirTemperatureDefaulted() const;
      double minimumCoolingSupplyAirTemperature() const;
      bool isMinimumCoolingSupplyAirTemperatureDefaulted() const;
      double maximumHeatingSupplyAirHumidityRatio() const;
      bool isMaximumHeatingSupplyAirHumidityRatioDefaulted() const;
      double minimumCoolingSupplyAirHumidityRatio() const;
      bool isMinimumCoolingSupplyAirHumidityRatioDefaulted() const;
      std::string heatingLimit() const;
      bool isHeatingLimitDefaulted() const;
      boost::optional<double> maximumHeatingAirFlowRate() const;
      bool isMaximumHeatingAirFlowRateAutosized() const;
      boost::optional<double> maximumSensibleHeatingCapacity() const;
      bool isMaximumSensibleHeatingCapacityAutosized() const;
      std::string coolingLimit() const;
      bool isCoolingLimitDefaulted() const;
      boost::optional<double> maximumCoolingAirFlowRate() const;
      bool isMaximumCoolingAirFlowRateAutosized() const;
      boost::optional<double> maximumTotalCoolingCapacity() const;
      bool isMaximumTotalCoolingCapacityAutosized() const;
      std::string dehumidificationControlType() const;
      bool isDehumidificationControlTypeDefaulted() const;
      double coolingSensibleHeatRatio() const;
      bool isCoolingSensibleHeatRatioDefaulted() const;
      std::string humidificationControlType() const;
      bool isHumidificationControlTypeDefaulted() const;
      std::string demandControlledVentilationType() const;
      bool isDemandControlledVentilationTypeDefaulted() const;
      std::string outdoorAirEconomizerType() const;
      bool isOutdoorAirEconomizerTypeDefaulted() const;
      std::string heatRecoveryType() const;
      bool isHeatRecoveryTypeDefaulted() const;
      double sensibleHeatRecoveryEffectiveness() const;
      bool isSensibleHeatRecoveryEffectivenessDefaulted() const;
      double latentHeatRecoveryEffectiveness() const;
      bool isLatentHeatRecoveryEffectivenessDefaulted() const;
      std::string heatingFuelType() const;
      std::string coolingFuelType() const;
      boost::optional<double> autosizedMaximumHeatingAirFlowRate() const;
      boost::optional<double> autosizedMaximumSensibleHeatingCapacity() const;
      boost::optional<double> autosizedMaximumCoolingAirFlowRate() const;
      boost::optional<double> autosizedMaximumTotalCoolingCapacity() const;

      bool setMaximumHeatingSupplyAirTemperature(double maximumHeatingSupplyAirTemperature);
      void resetMaximumHeatingSupplyAirTemperature();
      bool setMinimumCoolingSupplyAirTemperature(double minimumCoolingSupplyAirTemperature);
      void resetMinimumCoolingSupplyAirTemperature();
      bool setMaximumHeatingSupplyAirHumidityRatio(double maximumHeatingSupplyAirHumidityRatio);
      void resetMaximumHeatingSupplyAirHumidityRatio();
      bool setMinimumCoolingSupplyAirHumidityRatio(double minimumCoolingSupplyAirHumidityRatio);
      void resetMinimumCoolingSupplyAirHumidityRatio();
      bool setHeatingLimit(const std::string& heatingLimit);
      void resetHeatingLimit();
      bool setMaximumHeatingAirFlowRate(double maximumHeatingAirFlowRate);
      void resetMaximumHeatingAirFlowRate();
      void autosizeMaximumHeatingAirFlowRate();
      bool setMaximumSensibleHeatingCapacity(double maximumSensibleHeatingCapacity);
      void resetMaximumSensibleHeatingCapacity();
      void autosizeMaximumSensibleHeatingCapacity();
      bool setCoolingLimit(const std::string& coolingLimit);
      void resetCoolingLimit();
      bool setMaximumCoolingAirFlowRate(double maximumCoolingAirFlowRate);
      void resetMaximumCoolingAirFlowRate();
      void autosizeMaximumCoolingAirFlowRate();
      bool setMaximumTotalCoolingCapacity(double maximumTotalCoolingCapacity);
      void resetMaximumTotalCoolingCapacity();
      void autosizeMaximumTotalCoolingCapacity();
      bool setDehumidificationControlType(const std::string& dehumidificationControlType);
      void resetDehumidificationControlType();
      bool setCoolingSensibleHeatRatio(double coolingSensibleHeatRatio);
      void resetCoolingSensibleHeatRatio();
      bool setHumidificationControlType(const std::string& humidificationControlType);
      void resetHumidificationControlType();
      bool setDemandControlledVentilationType(const std::string& demandControlledVentilationType);
      void resetDemandControlledVentilationType();
      bool setOutdoorAirEconomizerType(const std::string& outdoorAirEconomizerType);
      void resetOutdoorAirEconomizerType();
      bool setHeatRecoveryType(const std::string& heatRecoveryType);
      void resetHeatRecoveryType();
      bool setSensibleHeatRecoveryEffectiveness(double sensibleHeatRecoveryEffectiveness);
      void resetSensibleHeatRecoveryEffectiveness();
      bool setLatentHeatRecoveryEffectiveness(double latentHeatRecoveryEffectiveness);
      void resetLatentHeatRecoveryEffectiveness();
      bool setHeatingFuelType(const std::string& heatingFuelType);
      bool setCoolingFuelType(const std::string& coolingFuelType);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
