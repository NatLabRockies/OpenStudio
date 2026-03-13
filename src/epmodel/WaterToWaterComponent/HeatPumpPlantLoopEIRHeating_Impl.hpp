/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPPLANTLOOPEIRHEATING_IMPL_HPP
#define EPMODEL_HEATPUMPPLANTLOOPEIRHEATING_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API HeatPumpPlantLoopEIRHeating_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~HeatPumpPlantLoopEIRHeating_Impl() override = default;

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

      std::vector<std::string> condenserTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
