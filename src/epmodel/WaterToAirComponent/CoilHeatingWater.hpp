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
    // - Status: Scalar Parity. The scalar design fields and operating-mode choice are aligned, while canonical relationship behavior remains outside this wrapper surface.
    // - Canonical Counterpart: openstudio::model::CoilHeatingWater.
    // - Implemented Parity: `uFactorTimesAreaValue`, `maximumWaterFlowRate`, `performanceInputMethod`, `ratedCapacity`, `ratedInletWaterTemperature`, `ratedInletAirTemperature`, `ratedOutletWaterTemperature`, `ratedOutletAirTemperature`, `ratedRatioForAirAndWaterConvection`, and autosize helpers preserve the canonical scalar contract.
    // - Documented Delta: Availability schedule, controller linkage, node-name accessors, and AFN/equivalent-duct helpers are not exposed here even though the canonical model type owns them.
    // - Field/Storage Mapping: Scalar design and choice fields map directly to the corresponding EnergyPlus `Coil:Heating:Water` fields.
    // - Evidence: `src/model/CoilHeatingWater.hpp`, `src/model/CoilHeatingWater.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingWater.cpp`, and `src/model/test/CoilHeatingWater_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted relationship and helper APIs only if this family is brought beyond scalar parity.
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
