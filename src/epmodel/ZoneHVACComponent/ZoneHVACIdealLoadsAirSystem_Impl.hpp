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
      bool setMaximumHeatingSupplyAirTemperature(double maximumHeatingSupplyAirTemperature);
      void resetMaximumHeatingSupplyAirTemperature();

      double minimumCoolingSupplyAirTemperature() const;
      bool isMinimumCoolingSupplyAirTemperatureDefaulted() const;
      bool setMinimumCoolingSupplyAirTemperature(double minimumCoolingSupplyAirTemperature);
      void resetMinimumCoolingSupplyAirTemperature();

      double maximumHeatingSupplyAirHumidityRatio() const;
      bool isMaximumHeatingSupplyAirHumidityRatioDefaulted() const;
      bool setMaximumHeatingSupplyAirHumidityRatio(double maximumHeatingSupplyAirHumidityRatio);
      void resetMaximumHeatingSupplyAirHumidityRatio();

      double minimumCoolingSupplyAirHumidityRatio() const;
      bool isMinimumCoolingSupplyAirHumidityRatioDefaulted() const;
      bool setMinimumCoolingSupplyAirHumidityRatio(double minimumCoolingSupplyAirHumidityRatio);
      void resetMinimumCoolingSupplyAirHumidityRatio();

      std::string heatingLimit() const;
      bool isHeatingLimitDefaulted() const;
      bool setHeatingLimit(const std::string& heatingLimit);
      void resetHeatingLimit();

      boost::optional<double> maximumHeatingAirFlowRate() const;
      bool isMaximumHeatingAirFlowRateAutosized() const;
      bool setMaximumHeatingAirFlowRate(double maximumHeatingAirFlowRate);
      void resetMaximumHeatingAirFlowRate();
      void autosizeMaximumHeatingAirFlowRate();
      boost::optional<double> autosizedMaximumHeatingAirFlowRate() const;

      boost::optional<double> maximumSensibleHeatingCapacity() const;
      bool isMaximumSensibleHeatingCapacityAutosized() const;
      bool setMaximumSensibleHeatingCapacity(double maximumSensibleHeatingCapacity);
      void resetMaximumSensibleHeatingCapacity();
      void autosizeMaximumSensibleHeatingCapacity();
      boost::optional<double> autosizedMaximumSensibleHeatingCapacity() const;

      std::string coolingLimit() const;
      bool isCoolingLimitDefaulted() const;
      bool setCoolingLimit(const std::string& coolingLimit);
      void resetCoolingLimit();

      boost::optional<double> maximumCoolingAirFlowRate() const;
      bool isMaximumCoolingAirFlowRateAutosized() const;
      bool setMaximumCoolingAirFlowRate(double maximumCoolingAirFlowRate);
      void resetMaximumCoolingAirFlowRate();
      void autosizeMaximumCoolingAirFlowRate();
      boost::optional<double> autosizedMaximumCoolingAirFlowRate() const;

      boost::optional<double> maximumTotalCoolingCapacity() const;
      bool isMaximumTotalCoolingCapacityAutosized() const;
      bool setMaximumTotalCoolingCapacity(double maximumTotalCoolingCapacity);
      void resetMaximumTotalCoolingCapacity();
      void autosizeMaximumTotalCoolingCapacity();
      boost::optional<double> autosizedMaximumTotalCoolingCapacity() const;

      std::string dehumidificationControlType() const;
      bool isDehumidificationControlTypeDefaulted() const;
      bool setDehumidificationControlType(const std::string& dehumidificationControlType);
      void resetDehumidificationControlType();

      double coolingSensibleHeatRatio() const;
      bool isCoolingSensibleHeatRatioDefaulted() const;
      bool setCoolingSensibleHeatRatio(double coolingSensibleHeatRatio);
      void resetCoolingSensibleHeatRatio();

      std::string humidificationControlType() const;
      bool isHumidificationControlTypeDefaulted() const;
      bool setHumidificationControlType(const std::string& humidificationControlType);
      void resetHumidificationControlType();

      std::string demandControlledVentilationType() const;
      bool isDemandControlledVentilationTypeDefaulted() const;
      bool setDemandControlledVentilationType(const std::string& demandControlledVentilationType);
      void resetDemandControlledVentilationType();

      std::string outdoorAirEconomizerType() const;
      bool isOutdoorAirEconomizerTypeDefaulted() const;
      bool setOutdoorAirEconomizerType(const std::string& outdoorAirEconomizerType);
      void resetOutdoorAirEconomizerType();

      std::string heatRecoveryType() const;
      bool isHeatRecoveryTypeDefaulted() const;
      bool setHeatRecoveryType(const std::string& heatRecoveryType);
      void resetHeatRecoveryType();

      double sensibleHeatRecoveryEffectiveness() const;
      bool isSensibleHeatRecoveryEffectivenessDefaulted() const;
      bool setSensibleHeatRecoveryEffectiveness(double sensibleHeatRecoveryEffectiveness);
      void resetSensibleHeatRecoveryEffectiveness();

      double latentHeatRecoveryEffectiveness() const;
      bool isLatentHeatRecoveryEffectivenessDefaulted() const;
      bool setLatentHeatRecoveryEffectiveness(double latentHeatRecoveryEffectiveness);
      void resetLatentHeatRecoveryEffectiveness();

      std::string heatingFuelType() const;
      bool setHeatingFuelType(const std::string& heatingFuelType);

      std::string coolingFuelType() const;
      bool setCoolingFuelType(const std::string& coolingFuelType);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
