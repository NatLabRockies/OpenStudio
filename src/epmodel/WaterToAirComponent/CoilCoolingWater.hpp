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

  /** \brief Represents a chilled-water cooling coil with separate air and water connections.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilcoolingwater,Coil:Cooling:Water}
   *
   * \par Important behavior
   * A missing availability-schedule target found while loading is repaired with
   * the model's always-on discrete schedule. The water-coil controller is
   * inferred from its persisted sensor and actuator node references. The
   * airflow-network helper stores an
   * <code>AirflowNetwork:Distribution:Component:Coil</code> object and repairs
   * its coil-object-type field when needed.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::CoilCoolingWater</code>.
   *
   * - <b>Changed:</b> <code>getAirflowNetworkEquivalentDuct(...)</code> and
   *   <code>airflowNetworkEquivalentDuct()</code> use
   *   <code>AirflowNetworkDistributionComponentCoil</code>, the EnergyPlus
   *   companion wrapper, instead of Model's
   *   <code>AirflowNetworkEquivalentDuct</code>.
   * - <b>Changed:</b> The autosized design-value queries are present, but
   *   return no value because EPModel does not read SQL sizing results.
   * - <b>Added:</b> EPModel provides <code>typeOfAnalysisValues()</code> and
   *   <code>heatExchangerConfigurationValues()</code> for the EnergyPlus
   *   choice fields; the Model header does not provide these helpers.
   *
   * \par Known limitations
   * If more than one airflow-network coil component is attached, the getter
   * warns and returns the first component in the resolved source order.
   */
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
