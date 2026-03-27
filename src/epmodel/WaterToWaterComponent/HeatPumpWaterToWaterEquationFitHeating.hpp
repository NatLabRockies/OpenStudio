/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPWATERTOWATEREQUATIONFITHEATING_HPP
#define EPMODEL_HEATPUMPWATERTOWATEREQUATIONFITHEATING_HPP

#include "EPModelAPI.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HeatPumpWaterToWaterEquationFitHeating_Impl;
  }

  class EPMODEL_API HeatPumpWaterToWaterEquationFitHeating : public WaterToWaterComponent
  {
   public:
    explicit HeatPumpWaterToWaterEquationFitHeating(const Model& model);

    virtual ~HeatPumpWaterToWaterEquationFitHeating() override = default;
    HeatPumpWaterToWaterEquationFitHeating(const HeatPumpWaterToWaterEquationFitHeating& other) = default;
    HeatPumpWaterToWaterEquationFitHeating(HeatPumpWaterToWaterEquationFitHeating&& other) = default;
    HeatPumpWaterToWaterEquationFitHeating& operator=(const HeatPumpWaterToWaterEquationFitHeating&) = default;
    HeatPumpWaterToWaterEquationFitHeating& operator=(HeatPumpWaterToWaterEquationFitHeating&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Scalar Parity. The equation-fit heating surface is aligned, while nodes, curves, and companion-heat-pump behavior remains excluded.
    // - Canonical Counterpart: openstudio::model::HeatPumpWaterToWaterEquationFitHeating.
    // - Implemented Parity: Scalar accessors for load/source flow rates, rated heating capacity, power consumption, coefficient of performance, and sizing preserve the canonical model API shape.
    // - Documented Delta: Node, curve, and companion-heat-pump APIs are intentionally excluded in this pass.
    // - Field/Storage Mapping: Scalar wrappers target the EnergyPlus `WaterToWater` equation-fit heating fields directly, with legacy rated/reference naming preserved where canonical model behavior expects it.
    // - Evidence: `src/model/HeatPumpWaterToWaterEquationFitHeating.hpp`, `src/model/HeatPumpWaterToWaterEquationFitHeating.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateHeatPumpWaterToWaterEquationFitHeating.cpp`.
    // - Remaining Parity Work: Add the excluded curve, companion, and loop-coupling APIs only if the family moves beyond scalar parity.

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

    // Performance metadata
    double referenceCoefficientofPerformance() const;
    bool setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance);

    double sizingFactor() const;
    bool setSizingFactor(double sizingFactor);

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
