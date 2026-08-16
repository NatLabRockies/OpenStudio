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

  class DesignSpecificationOutdoorAir;
  class Model;
  class Schedule;

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
    // - Status: Partial Parity. The ideal-loads scalar, schedule, and direct DesignSpecification:OutdoorAir fields are aligned, while broader
    //   zone relationships remain topology-driven.
    // - Canonical Counterpart: openstudio::model::ZoneHVACIdealLoadsAirSystem.
    // - Implemented Parity: The cooling/heating/dehumidification scalar groups, flow limits, five optional schedule relationships, and the direct
    //   DesignSpecification:OutdoorAir relationship map directly to the EnergyPlus object.
    // - Documented Delta: Zone and node references remain relationship-only links and are intentionally not exposed as scalar fields.
    // - Field/Storage Mapping: Scalars, schedules, and the direct DesignSpecification:OutdoorAir reference live on the EnergyPlus object while
    //   zone membership is maintained through thermal-zone topology. The EnergyPlus Zone Supply Air Node is the component outlet and belongs to
    //   the zone inlet list; Zone Exhaust Air Node is the component inlet and belongs to the zone exhaust list.
    // - Evidence: `src/model/ZoneHVACIdealLoadsAirSystem.hpp`, `src/model/ZoneHVACIdealLoadsAirSystem.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACIdealLoadsAirSystem.cpp`, `src/energyplus/ReverseTranslator/ReverseTranslateZoneHVACIdealLoadsAirSystem.cpp`, and `src/epmodel/test/ZoneHVACIdealLoadsAirSystem_GTest.cpp`.
    // - Remaining Parity Work: Add the remaining canonical non-schedule relationship helpers when their ownership semantics are implemented.
    static std::vector<std::string> heatingLimitValues();
    static std::vector<std::string> coolingLimitValues();
    static std::vector<std::string> dehumidificationControlTypeValues();
    static std::vector<std::string> humidificationControlTypeValues();
    static std::vector<std::string> demandControlledVentilationTypeValues();
    static std::vector<std::string> outdoorAirEconomizerTypeValues();
    static std::vector<std::string> heatRecoveryTypeValues();
    static std::vector<std::string> heatingFuelTypeValues();
    static std::vector<std::string> coolingFuelTypeValues();

    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& availabilitySchedule);
    void resetAvailabilitySchedule();

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

    boost::optional<Schedule> heatingAvailabilitySchedule() const;
    bool setHeatingAvailabilitySchedule(Schedule& heatingAvailabilitySchedule);
    void resetHeatingAvailabilitySchedule();

    boost::optional<Schedule> coolingAvailabilitySchedule() const;
    bool setCoolingAvailabilitySchedule(Schedule& coolingAvailabilitySchedule);
    void resetCoolingAvailabilitySchedule();

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

    boost::optional<DesignSpecificationOutdoorAir> designSpecificationOutdoorAirObject() const;
    bool setDesignSpecificationOutdoorAirObject(const DesignSpecificationOutdoorAir& designSpecificationOutdoorAir);
    void resetDesignSpecificationOutdoorAirObject();

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

    boost::optional<Schedule> heatingFuelEfficiencySchedule() const;
    bool setHeatingFuelEfficiencySchedule(Schedule& heatingFuelEfficiencySchedule);
    void resetHeatingFuelEfficiencySchedule();

    std::string heatingFuelType() const;
    bool setHeatingFuelType(const std::string& heatingFuelType);

    boost::optional<Schedule> coolingFuelEfficiencySchedule() const;
    bool setCoolingFuelEfficiencySchedule(Schedule& coolingFuelEfficiencySchedule);
    void resetCoolingFuelEfficiencySchedule();

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
