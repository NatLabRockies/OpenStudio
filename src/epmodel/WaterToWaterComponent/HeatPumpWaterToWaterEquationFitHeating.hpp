/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPWATERTOWATEREQUATIONFITHEATING_HPP
#define EPMODEL_HEATPUMPWATERTOWATEREQUATIONFITHEATING_HPP

#include "EPModelAPI.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent.hpp"

#include <utilities/core/Deprecated.hpp>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class CurveQuadLinear;
  class HeatPumpWaterToWaterEquationFitCooling;

  namespace detail {
    class HeatPumpWaterToWaterEquationFitHeating_Impl;
  }

  class EPMODEL_API HeatPumpWaterToWaterEquationFitHeating : public WaterToWaterComponent
  {
   public:
    explicit HeatPumpWaterToWaterEquationFitHeating(const Model& model, const CurveQuadLinear& heatingCapacityCurve,
                                                    const CurveQuadLinear& heatingCompressorPowerCurve);
    explicit HeatPumpWaterToWaterEquationFitHeating(const Model& model);

    virtual ~HeatPumpWaterToWaterEquationFitHeating() override = default;
    HeatPumpWaterToWaterEquationFitHeating(const HeatPumpWaterToWaterEquationFitHeating& other) = default;
    HeatPumpWaterToWaterEquationFitHeating(HeatPumpWaterToWaterEquationFitHeating&& other) = default;
    HeatPumpWaterToWaterEquationFitHeating& operator=(const HeatPumpWaterToWaterEquationFitHeating&) = default;
    HeatPumpWaterToWaterEquationFitHeating& operator=(HeatPumpWaterToWaterEquationFitHeating&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Parity with documented deltas. The canonical curve, companion, constructor, scalar, and deprecated alias
    //   surface is preserved here.
    // - Canonical Counterpart: openstudio::model::HeatPumpWaterToWaterEquationFitHeating.
    // - Implemented Parity: The curve-taking constructor, default curve creation, load/source flow, capacity/power,
    //   coefficient of performance, sizing, required heating curve relationships, companion cooling heat-pump link, and
    //   deprecated coefficient aliases preserve the canonical model API shape.
    // - Documented Delta: Autosized-value query helpers still return `none` because epmodel does not yet resolve
    //   SQL-backed autosized results for this family.
    // - Field/Storage Mapping: Scalar wrappers target the EnergyPlus `WaterToWater` equation-fit heating fields directly, with legacy rated/reference naming preserved where canonical model behavior expects it.
    // - Evidence: `src/model/HeatPumpWaterToWaterEquationFitHeating.hpp`, `src/model/HeatPumpWaterToWaterEquationFitHeating.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateHeatPumpWaterToWaterEquationFitHeating.cpp`.
    // - Remaining Parity Work: Loop-coupling ergonomics remain inherited from the shared water-to-water base.

    // Reference load-side flow rate
    boost::optional<double> referenceLoadSideFlowRate() const;
    bool setReferenceLoadSideFlowRate(double referenceLoadSideFlowRate);
    void autosizeReferenceLoadSideFlowRate();
    bool isReferenceLoadSideFlowRateAutosized() const;
    boost::optional<double> autosizedReferenceLoadSideFlowRate() const;

    double ratedLoadSideFlowRate() const;
    bool setRatedLoadSideFlowRate(double ratedLoadSideFlowRate);

    // Reference source-side flow rate
    boost::optional<double> referenceSourceSideFlowRate() const;
    bool setReferenceSourceSideFlowRate(double referenceSourceSideFlowRate);
    void autosizeReferenceSourceSideFlowRate();
    bool isReferenceSourceSideFlowRateAutosized() const;
    boost::optional<double> autosizedReferenceSourceSideFlowRate() const;

    double ratedSourceSideFlowRate() const;
    bool setRatedSourceSideFlowRate(double ratedSourceSideFlowRate);

    // Rated heating capacity
    boost::optional<double> ratedHeatingCapacity() const;
    bool setRatedHeatingCapacity(double ratedHeatingCapacity);
    void autosizeRatedHeatingCapacity();
    bool isRatedHeatingCapacityAutosized() const;
    boost::optional<double> autosizedRatedHeatingCapacity() const;

    // Rated heating power consumption
    boost::optional<double> ratedHeatingPowerConsumption() const;
    bool setRatedHeatingPowerConsumption(double ratedHeatingPowerConsumption);
    void autosizeRatedHeatingPowerConsumption();
    bool isRatedHeatingPowerConsumptionAutosized() const;
    boost::optional<double> autosizedRatedHeatingPowerConsumption() const;

    CurveQuadLinear heatingCapacityCurve() const;
    bool setHeatingCapacityCurve(const CurveQuadLinear& heatingCapacityCurve);
    OS_DEPRECATED(3, 2, 0) double heatingCapacityCoefficient1() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingCapacityCoefficient1(double heatingCapacityCoefficient1);
    OS_DEPRECATED(3, 2, 0) double heatingCapacityCoefficient2() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingCapacityCoefficient2(double heatingCapacityCoefficient2);
    OS_DEPRECATED(3, 2, 0) double heatingCapacityCoefficient3() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingCapacityCoefficient3(double heatingCapacityCoefficient3);
    OS_DEPRECATED(3, 2, 0) double heatingCapacityCoefficient4() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingCapacityCoefficient4(double heatingCapacityCoefficient4);
    OS_DEPRECATED(3, 2, 0) double heatingCapacityCoefficient5() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingCapacityCoefficient5(double heatingCapacityCoefficient5);

    CurveQuadLinear heatingCompressorPowerCurve() const;
    bool setHeatingCompressorPowerCurve(const CurveQuadLinear& heatingCompressorPowerCurve);
    OS_DEPRECATED(3, 2, 0) double heatingCompressorPowerCoefficient1() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingCompressorPowerCoefficient1(double heatingCompressorPowerCoefficient1);
    OS_DEPRECATED(3, 2, 0) double heatingCompressorPowerCoefficient2() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingCompressorPowerCoefficient2(double heatingCompressorPowerCoefficient2);
    OS_DEPRECATED(3, 2, 0) double heatingCompressorPowerCoefficient3() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingCompressorPowerCoefficient3(double heatingCompressorPowerCoefficient3);
    OS_DEPRECATED(3, 2, 0) double heatingCompressorPowerCoefficient4() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingCompressorPowerCoefficient4(double heatingCompressorPowerCoefficient4);
    OS_DEPRECATED(3, 2, 0) double heatingCompressorPowerCoefficient5() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingCompressorPowerCoefficient5(double heatingCompressorPowerCoefficient5);

    // Performance metadata
    double referenceCoefficientofPerformance() const;
    bool setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance);

    double sizingFactor() const;
    bool setSizingFactor(double sizingFactor);

    boost::optional<HeatPumpWaterToWaterEquationFitCooling> companionCoolingHeatPump() const;
    bool setCompanionCoolingHeatPump(const HeatPumpWaterToWaterEquationFitCooling& companionCoolingHeatPump);

   protected:
    using ImplType = detail::HeatPumpWaterToWaterEquationFitHeating_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HeatPumpWaterToWaterEquationFitHeating(std::shared_ptr<detail::HeatPumpWaterToWaterEquationFitHeating_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
