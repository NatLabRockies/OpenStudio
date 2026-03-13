/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPWATERTOWATEREQUATIONFITHEATING_HPP
#define EPMODEL_HEATPUMPWATERTOWATEREQUATIONFITHEATING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HeatPumpWaterToWaterEquationFitHeating_Impl;
  }

  class EPMODEL_API HeatPumpWaterToWaterEquationFitHeating : public ModelObject
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
    // - API: Preserves existing openstudio::model scalar accessor names/signatures, including legacy rated/reference aliases.
    // - Field Mapping: ratedHeatingCapacity/ratedHeatingPowerConsumption map to E+ Reference Heating fields per ForwardTranslator behavior.
    // - Field Mapping: Relationship-like fields (nodes, curves, companion heat pump) are intentionally excluded in this scalar-only scaffold.
    // - TODO(parity): Add non-scalar curve/companion APIs and WaterToWater component behavior in a dedicated parity pass.

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
