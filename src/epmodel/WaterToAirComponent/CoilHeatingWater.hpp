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

  namespace detail {
    class CoilHeatingWater_Impl;
  }

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

    // Schema Alignment Notes:
    // - Status: Partial Parity. The scalar design fields, availability schedule surface, and inferred controller
    //   linkage now align, while AFN/equivalent-duct helpers remain outside this wrapper surface.
    // - Canonical Counterpart: openstudio::model::CoilHeatingWater.
    // - Implemented Parity: `availabilitySchedule`, `setAvailabilitySchedule`, deprecated availability aliases,
    //   `controllerWaterCoil`, `uFactorTimesAreaValue`, `maximumWaterFlowRate`, `performanceInputMethod`,
    //   `ratedCapacity`, `ratedInletWaterTemperature`, `ratedInletAirTemperature`, `ratedOutletWaterTemperature`,
    //   `ratedOutletAirTemperature`, `ratedRatioForAirAndWaterConvection`, and the related autosize helpers preserve
    //   the canonical coil-facing API.
    // - Documented Delta: Node-name convenience helpers and AFN/equivalent-duct helpers are still not exposed here.
    //   For malformed imported data with no persisted availability schedule, the getter returns the model always-on
    //   discrete schedule without repairing storage. Autosized-value query accessors currently return `none` because
    //   epmodel does not yet expose canonical SQL-backed autosized results.
    // - Field/Storage Mapping: The availability schedule and scalar design fields map directly to EnergyPlus
    //   `Coil:Heating:Water`. Controller linkage is inferred from the persisted `Controller:WaterCoil` actuator and
    //   sensor nodes because EnergyPlus stores the relationship through shared nodes rather than a direct back-reference.
    // - Evidence: `src/model/CoilHeatingWater.hpp`, `src/model/CoilHeatingWater.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingWater.cpp`, and `src/model/test/CoilHeatingWater_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted node-name and AFN/equivalent-duct helpers only if the supporting
    //   epmodel wrappers are developed.
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
