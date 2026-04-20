/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPWATERTOWATEREQUATIONFITCOOLING_HPP
#define EPMODEL_HEATPUMPWATERTOWATEREQUATIONFITCOOLING_HPP

#include "EPModelAPI.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent.hpp"

#include <utilities/core/Deprecated.hpp>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class CurveQuadLinear;
  class HeatPumpWaterToWaterEquationFitHeating;

  namespace detail {
    class HeatPumpWaterToWaterEquationFitCooling_Impl;
  }

  class EPMODEL_API HeatPumpWaterToWaterEquationFitCooling : public WaterToWaterComponent
  {
   public:
    explicit HeatPumpWaterToWaterEquationFitCooling(const Model& model, const CurveQuadLinear& coolingCapacityCurve,
                                                    const CurveQuadLinear& coolingCompressorPowerCurve);
    explicit HeatPumpWaterToWaterEquationFitCooling(const Model& model);

    virtual ~HeatPumpWaterToWaterEquationFitCooling() override = default;
    HeatPumpWaterToWaterEquationFitCooling(const HeatPumpWaterToWaterEquationFitCooling& other) = default;
    HeatPumpWaterToWaterEquationFitCooling(HeatPumpWaterToWaterEquationFitCooling&& other) = default;
    HeatPumpWaterToWaterEquationFitCooling& operator=(const HeatPumpWaterToWaterEquationFitCooling&) = default;
    HeatPumpWaterToWaterEquationFitCooling& operator=(HeatPumpWaterToWaterEquationFitCooling&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Parity with documented deltas. The canonical curve, companion, constructor, scalar, and deprecated alias
    //   surface is preserved here.
    // - Canonical Counterpart: openstudio::model::HeatPumpWaterToWaterEquationFitCooling.
    // - Implemented Parity: The curve-taking constructor, default curve creation, load/source flow, capacity/power,
    //   coefficient of performance, sizing, required cooling curve relationships, companion heating heat-pump link, and
    //   deprecated coefficient aliases preserve the canonical model API shape.
    // - Documented Delta: Autosized-value query helpers still return `none` because epmodel does not yet resolve
    //   SQL-backed autosized results for this family.
    // - Field/Storage Mapping: The public wrapper preserves canonical openstudio::model load/source semantics while storing scalar values on the EnergyPlus equation-fit cooling fields directly; node-port topology intentionally maps supply ports to EnergyPlus load-side fields and demand ports to source-side fields.
    // - Evidence: `src/model/HeatPumpWaterToWaterEquationFitCooling.hpp`, `src/model/HeatPumpWaterToWaterEquationFitCooling.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateHeatPumpWaterToWaterEquationFitCooling.cpp`.
    // - Remaining Parity Work: Loop-coupling ergonomics remain inherited from the shared water-to-water base.

    // Reference load-side flow rate
    boost::optional<double> referenceLoadSideFlowRate() const;
    bool isReferenceLoadSideFlowRateAutosized() const;
    bool setReferenceLoadSideFlowRate(double referenceLoadSideFlowRate);
    void autosizeReferenceLoadSideFlowRate();
    boost::optional<double> autosizedReferenceLoadSideFlowRate() const;

    // Rated load-side flow rate
    double ratedLoadSideFlowRate() const;
    bool setRatedLoadSideFlowRate(double ratedLoadSideFlowRate);

    // Reference source-side flow rate
    boost::optional<double> referenceSourceSideFlowRate() const;
    bool isReferenceSourceSideFlowRateAutosized() const;
    bool setReferenceSourceSideFlowRate(double referenceSourceSideFlowRate);
    void autosizeReferenceSourceSideFlowRate();
    boost::optional<double> autosizedReferenceSourceSideFlowRate() const;

    // Rated source-side flow rate
    double ratedSourceSideFlowRate() const;
    bool setRatedSourceSideFlowRate(double ratedSourceSideFlowRate);

    // Rated cooling capacity
    boost::optional<double> ratedCoolingCapacity() const;
    bool isRatedCoolingCapacityAutosized() const;
    bool setRatedCoolingCapacity(double ratedCoolingCapacity);
    void autosizeRatedCoolingCapacity();
    boost::optional<double> autosizedRatedCoolingCapacity() const;

    // Rated cooling power consumption
    boost::optional<double> ratedCoolingPowerConsumption() const;
    bool isRatedCoolingPowerConsumptionAutosized() const;
    bool setRatedCoolingPowerConsumption(double ratedCoolingPowerConsumption);
    void autosizeRatedCoolingPowerConsumption();
    boost::optional<double> autosizedRatedCoolingPowerConsumption() const;

    CurveQuadLinear coolingCapacityCurve() const;
    bool setCoolingCapacityCurve(const CurveQuadLinear& coolingCapacityCurve);
    OS_DEPRECATED(3, 2, 0) double coolingCapacityCoefficient1() const;
    OS_DEPRECATED(3, 2, 0) bool setCoolingCapacityCoefficient1(double coolingCapacityCoefficient1);
    OS_DEPRECATED(3, 2, 0) double coolingCapacityCoefficient2() const;
    OS_DEPRECATED(3, 2, 0) bool setCoolingCapacityCoefficient2(double coolingCapacityCoefficient2);
    OS_DEPRECATED(3, 2, 0) double coolingCapacityCoefficient3() const;
    OS_DEPRECATED(3, 2, 0) bool setCoolingCapacityCoefficient3(double coolingCapacityCoefficient3);
    OS_DEPRECATED(3, 2, 0) double coolingCapacityCoefficient4() const;
    OS_DEPRECATED(3, 2, 0) bool setCoolingCapacityCoefficient4(double coolingCapacityCoefficient4);
    OS_DEPRECATED(3, 2, 0) double coolingCapacityCoefficient5() const;
    OS_DEPRECATED(3, 2, 0) bool setCoolingCapacityCoefficient5(double coolingCapacityCoefficient5);

    CurveQuadLinear coolingCompressorPowerCurve() const;
    bool setCoolingCompressorPowerCurve(const CurveQuadLinear& coolingCompressorPowerCurve);
    OS_DEPRECATED(3, 2, 0) double coolingCompressorPowerCoefficient1() const;
    OS_DEPRECATED(3, 2, 0) bool setCoolingCompressorPowerCoefficient1(double coolingCompressorPowerCoefficient1);
    OS_DEPRECATED(3, 2, 0) double coolingCompressorPowerCoefficient2() const;
    OS_DEPRECATED(3, 2, 0) bool setCoolingCompressorPowerCoefficient2(double coolingCompressorPowerCoefficient2);
    OS_DEPRECATED(3, 2, 0) double coolingCompressorPowerCoefficient3() const;
    OS_DEPRECATED(3, 2, 0) bool setCoolingCompressorPowerCoefficient3(double coolingCompressorPowerCoefficient3);
    OS_DEPRECATED(3, 2, 0) double coolingCompressorPowerCoefficient4() const;
    OS_DEPRECATED(3, 2, 0) bool setCoolingCompressorPowerCoefficient4(double coolingCompressorPowerCoefficient4);
    OS_DEPRECATED(3, 2, 0) double coolingCompressorPowerCoefficient5() const;
    OS_DEPRECATED(3, 2, 0) bool setCoolingCompressorPowerCoefficient5(double coolingCompressorPowerCoefficient5);

    // Performance tuning
    double referenceCoefficientofPerformance() const;
    bool setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance);

    double sizingFactor() const;
    bool setSizingFactor(double sizingFactor);

    boost::optional<HeatPumpWaterToWaterEquationFitHeating> companionHeatingHeatPump() const;
    bool setCompanionHeatingHeatPump(const HeatPumpWaterToWaterEquationFitHeating& companionHeatingHeatPump);

   protected:
    using ImplType = detail::HeatPumpWaterToWaterEquationFitCooling_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HeatPumpWaterToWaterEquationFitCooling(std::shared_ptr<detail::HeatPumpWaterToWaterEquationFitCooling_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
