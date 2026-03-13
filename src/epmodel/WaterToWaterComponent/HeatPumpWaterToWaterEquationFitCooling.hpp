/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPWATERTOWATEREQUATIONFITCOOLING_HPP
#define EPMODEL_HEATPUMPWATERTOWATEREQUATIONFITCOOLING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HeatPumpWaterToWaterEquationFitCooling_Impl;
  }

  class EPMODEL_API HeatPumpWaterToWaterEquationFitCooling : public ModelObject
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
    // - API: Preserves existing openstudio::model scalar accessor names/signatures, including legacy rated/reference aliases.
    // - Field Mapping: ratedCoolingCapacity/ratedCoolingPowerConsumption map to E+ Reference Cooling fields per ForwardTranslator behavior.
    // - Field Mapping: Relationship-like fields (nodes, curves, companion heat pump) are intentionally excluded in this scalar-only scaffold.
    // - TODO(parity): Add non-scalar curve/companion APIs and WaterToWater component behavior in a dedicated parity pass.

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
