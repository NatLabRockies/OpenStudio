/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPPLANTLOOPEIRCOOLING_IMPL_HPP
#define EPMODEL_HEATPUMPPLANTLOOPEIRCOOLING_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

  class EPMODEL_API HeatPumpPlantLoopEIRCooling_Impl : public ModelObject_Impl
  {
   public:
    using ModelObject_Impl::ModelObject_Impl;
    virtual ~HeatPumpPlantLoopEIRCooling_Impl() override = default;

    std::string condenserType() const;
    bool setCondenserType(const std::string& condenserType);
    std::vector<std::string> condenserTypeValues() const;

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

    double maximumHeatRecoveryOutletTemperature() const;
    bool setMaximumHeatRecoveryOutletTemperature(double maximumHeatRecoveryOutletTemperature);

    double thermosiphonMinimumTemperatureDifference() const;
    bool setThermosiphonMinimumTemperatureDifference(double thermosiphonMinimumTemperatureDifference);
  };

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
