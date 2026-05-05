/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGWATER_HPP
#define EPMODEL_COILCOOLINGWATER_HPP

#include "EPModelAPI.hpp"
#include "WaterToAirComponent/WaterToAirComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class ControllerWaterCoil;
  class AirflowNetworkDistributionComponentCoil;

  namespace detail {
    class CoilCoolingWater_Impl;
  }

  class EPMODEL_API CoilCoolingWater : public WaterToAirComponent
  {
   public:
    CoilCoolingWater(const Model& model, Schedule& availabilitySchedule);
    explicit CoilCoolingWater(const Model& model);

    virtual ~CoilCoolingWater() override = default;
    CoilCoolingWater(const CoilCoolingWater& other) = default;
    CoilCoolingWater(CoilCoolingWater&& other) = default;
    CoilCoolingWater& operator=(const CoilCoolingWater&) = default;
    CoilCoolingWater& operator=(CoilCoolingWater&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> typeOfAnalysisValues();
    static std::vector<std::string> heatExchangerConfigurationValues();

    // Schema Alignment Notes:
    // - Status: Parity with documented deltas. The scalar design fields, availability schedule surface, controller
    //   linkage, and equivalent-duct helper surface now align.
    // - Canonical Counterpart: openstudio::model::CoilCoolingWater.
    // - Implemented Parity: `setAvailabilitySchedule`, `setAvailableSchedule`, `controllerWaterCoil`,
    //   `designWaterFlowRate`, `designAirFlowRate`, `designInletWaterTemperature`,
    //   `designInletAirTemperature`, `designOutletAirTemperature`, `designInletAirHumidityRatio`,
    //   `designOutletAirHumidityRatio`, `typeOfAnalysis`, `heatExchangerConfiguration`,
    //   `getAirflowNetworkEquivalentDuct`, `airflowNetworkEquivalentDuct`, `children`, and their autosize/setter helpers
    //   preserve the canonical coil-facing API.
    // - Documented Delta: For malformed imported data with no persisted availability schedule, the getter repairs
    //   storage to the model always-on discrete schedule before returning it. When the coil is attached to multiple
    //   `AirflowNetwork:Distribution:Component:Coil` objects, `airflowNetworkEquivalentDuct()` warns and returns the
    //   first attached component. Autosized sizing-result accessors,
    //   including `autosizedDesignCoilLoad()`, still return `none` because epmodel does not resolve SQL-backed sizing
    //   outputs yet.
    // - Field/Storage Mapping: The availability schedule and scalar design fields map directly to EnergyPlus
    //   `Coil:Cooling:Water`. Controller linkage is inferred from the persisted `Controller:WaterCoil` sensor and actuator
    //   nodes because the EnergyPlus controller object does not store a direct back-reference to the coil. `addToNode()`
    //   also mirrors the canonical wrapper's parent-system protections by rejecting direct AirLoop insertion when the
    //   coil is the primary child of `CoilSystemCoolingWater` or any `CoilSystemCoolingWaterHeatExchangerAssisted`,
    //   and by suppressing/removing inferred controllers when the coil is used inside `CoilSystemCoolingWater`. The
    //   equivalent-duct helper surface persists the linked `AirflowNetwork:Distribution:Component:Coil` relationship and
    //   its scalar geometry fields; when reusing malformed imported data, the helper also repairs the stored
    //   `Coil Object Type` field back to `Coil:Cooling:Water`. If malformed imported data omits the required
    //   availability schedule, the getter repairs the persisted schedule reference to the model always-on discrete
    //   schedule.
    // - Evidence: `src/model/CoilCoolingWater.hpp`, `src/model/CoilCoolingWater.cpp`,
    //   `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingWater.cpp`,
    //   `src/energyplus/ForwardTranslator/ForwardTranslateAirflowNetwork.cpp`, and
    //   `src/model/test/CoilCoolingWater_GTest.cpp`.
    Schedule availabilitySchedule() const;

    /** \deprecated */
    Schedule availableSchedule() const;

    bool setAvailabilitySchedule(Schedule& schedule);

    /** \deprecated */
    bool setAvailableSchedule(Schedule& schedule);

    boost::optional<double> designWaterFlowRate() const;
    boost::optional<double> autosizedDesignWaterFlowRate() const;
    bool setDesignWaterFlowRate(double value);
    bool isDesignWaterFlowRateAutosized() const;
    void autosizeDesignWaterFlowRate();

    boost::optional<double> designAirFlowRate() const;
    boost::optional<double> autosizedDesignAirFlowRate() const;
    bool setDesignAirFlowRate(double value);
    bool isDesignAirFlowRateAutosized() const;
    void autosizeDesignAirFlowRate();

    boost::optional<double> designInletWaterTemperature() const;
    boost::optional<double> autosizedDesignInletWaterTemperature() const;
    bool setDesignInletWaterTemperature(double value);
    bool isDesignInletWaterTemperatureAutosized() const;
    void autosizeDesignInletWaterTemperature();

    boost::optional<double> designInletAirTemperature() const;
    boost::optional<double> autosizedDesignInletAirTemperature() const;
    bool setDesignInletAirTemperature(double value);
    bool isDesignInletAirTemperatureAutosized() const;
    void autosizeDesignInletAirTemperature();

    boost::optional<double> designOutletAirTemperature() const;
    boost::optional<double> autosizedDesignOutletAirTemperature() const;
    bool setDesignOutletAirTemperature(double value);
    bool isDesignOutletAirTemperatureAutosized() const;
    void autosizeDesignOutletAirTemperature();

    boost::optional<double> designInletAirHumidityRatio() const;
    boost::optional<double> autosizedDesignInletAirHumidityRatio() const;
    bool setDesignInletAirHumidityRatio(double value);
    bool isDesignInletAirHumidityRatioAutosized() const;
    void autosizeDesignInletAirHumidityRatio();

    boost::optional<double> designOutletAirHumidityRatio() const;
    boost::optional<double> autosizedDesignOutletAirHumidityRatio() const;
    bool setDesignOutletAirHumidityRatio(double value);
    bool isDesignOutletAirHumidityRatioAutosized() const;
    void autosizeDesignOutletAirHumidityRatio();

    std::string typeOfAnalysis() const;
    bool setTypeOfAnalysis(const std::string& value);

    std::string heatExchangerConfiguration() const;
    bool setHeatExchangerConfiguration(const std::string& value);

    boost::optional<ControllerWaterCoil> controllerWaterCoil() const;
    AirflowNetworkDistributionComponentCoil getAirflowNetworkEquivalentDuct(double length, double diameter);
    boost::optional<AirflowNetworkDistributionComponentCoil> airflowNetworkEquivalentDuct() const;
    boost::optional<double> autosizedDesignCoilLoad() const;

   protected:
    using ImplType = detail::CoilCoolingWater_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilCoolingWater(std::shared_ptr<detail::CoilCoolingWater_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
