/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACIDEALLOADSAIRSYSTEM_HPP
#define EPMODEL_ZONEHVACIDEALLOADSAIRSYSTEM_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneHVACIdealLoadsAirSystem_Impl;
  }

  class EPMODEL_API ZoneHVACIdealLoadsAirSystem : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACIdealLoadsAirSystem(const Model& model);

    virtual ~ZoneHVACIdealLoadsAirSystem() override = default;
    ZoneHVACIdealLoadsAirSystem(const ZoneHVACIdealLoadsAirSystem& other) = default;
    ZoneHVACIdealLoadsAirSystem(ZoneHVACIdealLoadsAirSystem&& other) = default;
    ZoneHVACIdealLoadsAirSystem& operator=(const ZoneHVACIdealLoadsAirSystem&) = default;
    ZoneHVACIdealLoadsAirSystem& operator=(ZoneHVACIdealLoadsAirSystem&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: these getters/setters expose numeric and choice fields sourced from the EnergyPlus ZoneHVAC:IdealLoadsAirSystem fields enumerated in ZoneHVAC_IdealLoadsAirSystem_FieldEnums.hxx (see ForwardTranslateZoneHVACIdealLoadsAirSystem.cpp for mapping evidence).
    // - Relationship-like fields (AvailabilityScheduleName, Zone/OutdoorAir node names, DesignSpecificationOutdoorAirObjectName, Outdoor Air Method nodes/schedules, and fuel efficiency schedule names) remain outside this scalar surface.
    static std::vector<std::string> heatingLimitValues();
    static std::vector<std::string> coolingLimitValues();
    static std::vector<std::string> dehumidificationControlTypeValues();
    static std::vector<std::string> humidificationControlTypeValues();
    static std::vector<std::string> demandControlledVentilationTypeValues();
    static std::vector<std::string> outdoorAirEconomizerTypeValues();
    static std::vector<std::string> heatRecoveryTypeValues();
    static std::vector<std::string> heatingFuelTypeValues();
    static std::vector<std::string> coolingFuelTypeValues();

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

   protected:
    using ImplType = detail::ZoneHVACIdealLoadsAirSystem_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACIdealLoadsAirSystem(std::shared_ptr<detail::ZoneHVACIdealLoadsAirSystem_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
