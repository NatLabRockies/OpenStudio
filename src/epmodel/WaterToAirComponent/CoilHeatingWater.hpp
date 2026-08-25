/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGWATER_HPP
#define EPMODEL_COILHEATINGWATER_HPP

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
    class CoilHeatingWater_Impl;
  }

  /** \brief Represents a hot-water heating coil with separate air and water connections.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilheatingwater,Coil:Heating:Water}
   *
   * \par Important behavior
   * A missing availability-schedule target found while loading is repaired with
   * the model's always-on discrete schedule. The water-coil controller is
   * inferred from shared sensor and actuator node references. The airflow-
   * network helper stores an <code>AirflowNetwork:Distribution:Component:Coil</code>
   * companion and repairs its coil-object-type field when needed.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::CoilHeatingWater</code>.
   *
   * - <b>Changed:</b> The airflow-network equivalent-duct methods use
   *   <code>AirflowNetworkDistributionComponentCoil</code> instead of
   *   Model's <code>AirflowNetworkEquivalentDuct</code>.
   * - <b>Changed:</b> Autosized-value queries are present, but return no value
   *   because EPModel does not read SQL sizing results.
   * - <b>Added:</b> EPModel provides <code>performanceInputMethodValues()</code>
   *   for the EnergyPlus choice field; the Model header does not provide this
   *   helper.
   *
   * \par Known limitations
   * If more than one airflow-network coil component is attached, the getter
   * warns and returns the first component in the resolved source order.
   */
  class EPMODEL_API CoilHeatingWater : public WaterToAirComponent
  {
   public:
    CoilHeatingWater(const Model& model, Schedule& availabilitySchedule);
    explicit CoilHeatingWater(const Model& model);

    virtual ~CoilHeatingWater() override = default;
    CoilHeatingWater(const CoilHeatingWater& other) = default;
    CoilHeatingWater(CoilHeatingWater&& other) = default;
    CoilHeatingWater& operator=(const CoilHeatingWater&) = default;
    CoilHeatingWater& operator=(CoilHeatingWater&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> performanceInputMethodValues();

    Schedule availabilitySchedule() const;

    /** \deprecated */
    Schedule availableSchedule() const;

    bool setAvailabilitySchedule(Schedule& schedule);

    /** \deprecated */
    bool setAvailableSchedule(Schedule& schedule);

    boost::optional<double> uFactorTimesAreaValue() const;
    bool isUFactorTimesAreaValueAutosized() const;
    void autosizeUFactorTimesAreaValue();
    bool setUFactorTimesAreaValue(double value);
    boost::optional<double> autosizedUFactorTimesAreaValue() const;

    boost::optional<double> maximumWaterFlowRate() const;
    bool isMaximumWaterFlowRateAutosized() const;
    void autosizeMaximumWaterFlowRate();
    bool setMaximumWaterFlowRate(double value);
    boost::optional<double> autosizedMaximumWaterFlowRate() const;

    std::string performanceInputMethod() const;
    bool setPerformanceInputMethod(const std::string& value);

    boost::optional<double> ratedCapacity() const;
    bool isRatedCapacityAutosized() const;
    void autosizeRatedCapacity();
    bool setRatedCapacity(double value);
    boost::optional<double> autosizedRatedCapacity() const;

    double ratedInletWaterTemperature() const;
    bool setRatedInletWaterTemperature(double value);

    double ratedInletAirTemperature() const;
    bool setRatedInletAirTemperature(double value);

    double ratedOutletWaterTemperature() const;
    bool setRatedOutletWaterTemperature(double value);

    double ratedOutletAirTemperature() const;
    bool setRatedOutletAirTemperature(double value);

    double ratedRatioForAirAndWaterConvection() const;
    bool setRatedRatioForAirAndWaterConvection(double value);

    boost::optional<ControllerWaterCoil> controllerWaterCoil() const;
    AirflowNetworkDistributionComponentCoil getAirflowNetworkEquivalentDuct(double length, double diameter);
    boost::optional<AirflowNetworkDistributionComponentCoil> airflowNetworkEquivalentDuct() const;

   protected:
    using ImplType = detail::CoilHeatingWater_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilHeatingWater(std::shared_ptr<detail::CoilHeatingWater_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
