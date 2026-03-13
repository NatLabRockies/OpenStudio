/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPPLANTLOOPEIRHEATING_HPP
#define EPMODEL_HEATPUMPPLANTLOOPEIRHEATING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HeatPumpPlantLoopEIRHeating_Impl;
  }

  class EPMODEL_API HeatPumpPlantLoopEIRHeating : public ModelObject
  {
   public:
    explicit HeatPumpPlantLoopEIRHeating(const Model& model);

    virtual ~HeatPumpPlantLoopEIRHeating() override = default;
    HeatPumpPlantLoopEIRHeating(const HeatPumpPlantLoopEIRHeating& other) = default;
    HeatPumpPlantLoopEIRHeating(HeatPumpPlantLoopEIRHeating&& other) = default;
    HeatPumpPlantLoopEIRHeating& operator=(const HeatPumpPlantLoopEIRHeating&) = default;
    HeatPumpPlantLoopEIRHeating& operator=(HeatPumpPlantLoopEIRHeating&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validCondenserTypeValues();
    static std::vector<std::string> condenserTypeValues();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor names/signatures for this model-counterpart class.
    // - Field Mapping: Preserved scalar APIs map directly to E+ HeatPump:PlantLoop:EIR:Heating scalar fields.
    // - Field Mapping: Relationship-like fields (companion object, curves, node/link targets) are intentionally excluded.
    // - Field Mapping: ForwardTranslator evidence confirms direct scalar mapping and Autosize string behavior for flow/capacity fields.
    // - TODO(parity): Add excluded non-scalar APIs and loop-coupling behavior in a dedicated parity pass.
    std::string condenserType() const;
    bool setCondenserType(const std::string& condenserType);

    boost::optional<double> loadSideReferenceFlowRate() const;
    bool isLoadSideReferenceFlowRateAutosized() const;
    bool setLoadSideReferenceFlowRate(double loadSideReferenceFlowRate);
    void autosizeLoadSideReferenceFlowRate();
    boost::optional<double> autosizedLoadSideReferenceFlowRate() const;

    boost::optional<double> sourceSideReferenceFlowRate() const;
    bool isSourceSideReferenceFlowRateAutosized() const;
    bool setSourceSideReferenceFlowRate(double sourceSideReferenceFlowRate);
    void autosizeSourceSideReferenceFlowRate();
    boost::optional<double> autosizedSourceSideReferenceFlowRate() const;

    boost::optional<double> heatRecoveryReferenceFlowRate() const;
    bool isHeatRecoveryReferenceFlowRateAutosized() const;
    bool setHeatRecoveryReferenceFlowRate(double heatRecoveryReferenceFlowRate);
    void autosizeHeatRecoveryReferenceFlowRate();
    boost::optional<double> autosizedHeatRecoveryReferenceFlowRate() const;

    boost::optional<double> referenceCapacity() const;
    bool isReferenceCapacityAutosized() const;
    bool setReferenceCapacity(double referenceCapacity);
    void autosizeReferenceCapacity();
    boost::optional<double> autosizedReferenceCapacity() const;

    double referenceCoefficientofPerformance() const;
    bool setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance);

    double sizingFactor() const;
    bool setSizingFactor(double sizingFactor);

    double heatingToCoolingCapacitySizingRatio() const;
    bool setHeatingToCoolingCapacitySizingRatio(double heatingToCoolingCapacitySizingRatio);

    std::string heatPumpSizingMethod() const;
    bool setHeatPumpSizingMethod(const std::string& heatPumpSizingMethod);

    std::string controlType() const;
    bool setControlType(const std::string& controlType);

    std::string flowMode() const;
    bool setFlowMode(const std::string& flowMode);

    double minimumPartLoadRatio() const;
    bool setMinimumPartLoadRatio(double minimumPartLoadRatio);

    double minimumSourceInletTemperature() const;
    bool setMinimumSourceInletTemperature(double minimumSourceInletTemperature);

    double maximumSourceInletTemperature() const;
    bool setMaximumSourceInletTemperature(double maximumSourceInletTemperature);

    double maximumOutdoorDryBulbTemperatureForDefrostOperation() const;
    bool setMaximumOutdoorDryBulbTemperatureForDefrostOperation(double maximumOutdoorDryBulbTemperatureForDefrostOperation);

    std::string heatPumpDefrostControl() const;
    bool setHeatPumpDefrostControl(const std::string& heatPumpDefrostControl);

    double heatPumpDefrostTimePeriodFraction() const;
    bool setHeatPumpDefrostTimePeriodFraction(double heatPumpDefrostTimePeriodFraction);

    double minimumHeatRecoveryOutletTemperature() const;
    bool setMinimumHeatRecoveryOutletTemperature(double minimumHeatRecoveryOutletTemperature);

   protected:
    using ImplType = detail::HeatPumpPlantLoopEIRHeating_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HeatPumpPlantLoopEIRHeating(std::shared_ptr<detail::HeatPumpPlantLoopEIRHeating_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
