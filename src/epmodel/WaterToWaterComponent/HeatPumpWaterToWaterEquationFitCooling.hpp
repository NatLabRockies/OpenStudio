/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPWATERTOWATEREQUATIONFITCOOLING_HPP
#define EPMODEL_HEATPUMPWATERTOWATEREQUATIONFITCOOLING_HPP

#include "EPModelAPI.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HeatPumpWaterToWaterEquationFitCooling_Impl;
  }

  class EPMODEL_API HeatPumpWaterToWaterEquationFitCooling : public WaterToWaterComponent
  {
   public:
    explicit HeatPumpWaterToWaterEquationFitCooling(const Model& model);

    virtual ~HeatPumpWaterToWaterEquationFitCooling() override = default;
    HeatPumpWaterToWaterEquationFitCooling(const HeatPumpWaterToWaterEquationFitCooling& other) = default;
    HeatPumpWaterToWaterEquationFitCooling(HeatPumpWaterToWaterEquationFitCooling&& other) = default;
    HeatPumpWaterToWaterEquationFitCooling& operator=(const HeatPumpWaterToWaterEquationFitCooling&) = default;
    HeatPumpWaterToWaterEquationFitCooling& operator=(HeatPumpWaterToWaterEquationFitCooling&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Scalar Parity. The equation-fit cooling surface is aligned, while nodes, curves, and companion heat-pump behavior remains excluded.
    // - Canonical Counterpart: openstudio::model::HeatPumpWaterToWaterEquationFitCooling.
    // - Implemented Parity: Scalar accessors for load/source flow rates, rated cooling capacity, power consumption, coefficient of performance, and sizing preserve the canonical model API shape.
    // - Documented Delta: Node, curve, and companion-heat-pump APIs are intentionally excluded in this pass.
    // - Field/Storage Mapping: Scalar wrappers target the EnergyPlus `WaterToWater` equation-fit cooling fields directly, with legacy rated/reference naming preserved where canonical model behavior expects it.
    // - Evidence: `src/model/HeatPumpWaterToWaterEquationFitCooling.hpp`, `src/model/HeatPumpWaterToWaterEquationFitCooling.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateHeatPumpWaterToWaterEquationFitCooling.cpp`.
    // - Remaining Parity Work: Add the excluded curve, companion, and loop-coupling APIs only if the family moves beyond scalar parity.

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

    // Performance tuning
    double referenceCoefficientofPerformance() const;
    bool setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance);

    double sizingFactor() const;
    bool setSizingFactor(double sizingFactor);

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
