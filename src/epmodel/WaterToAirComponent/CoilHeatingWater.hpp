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

  namespace detail {
    class CoilHeatingWater_Impl;
  }

  class EPMODEL_API CoilHeatingWater : public WaterToAirComponent
  {
   public:
    explicit CoilHeatingWater(const Model& model);

    virtual ~CoilHeatingWater() override = default;
    CoilHeatingWater(const CoilHeatingWater& other) = default;
    CoilHeatingWater(CoilHeatingWater&& other) = default;
    CoilHeatingWater& operator=(const CoilHeatingWater&) = default;
    CoilHeatingWater& operator=(CoilHeatingWater&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> performanceInputMethodValues();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
    // - Field Mapping: uFactorTimesAreaValue, maximumWaterFlowRate, ratedCapacity, and rated* temperature/ratio APIs map directly to EnergyPlus Coil:Heating:Water fields.
    // - Field Mapping: performanceInputMethod maps directly to EnergyPlus PerformanceInputMethod.
    // - ForwardTranslator evidence: ForwardTranslateCoilHeatingWater.cpp writes these exact scalar fields and autosize semantics.
    // - Field Mapping: availability schedule, water/air node names, and controller linkage are relationship-like and intentionally excluded in this scalar scaffold phase.
    boost::optional<double> uFactorTimesAreaValue() const;
    bool isUFactorTimesAreaValueAutosized() const;
    void autosizeUFactorTimesAreaValue();
    bool setUFactorTimesAreaValue(double value);

    boost::optional<double> maximumWaterFlowRate() const;
    bool isMaximumWaterFlowRateAutosized() const;
    void autosizeMaximumWaterFlowRate();
    bool setMaximumWaterFlowRate(double value);

    std::string performanceInputMethod() const;
    bool setPerformanceInputMethod(const std::string& value);

    boost::optional<double> ratedCapacity() const;
    bool isRatedCapacityAutosized() const;
    void autosizeRatedCapacity();
    bool setRatedCapacity(double value);

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
