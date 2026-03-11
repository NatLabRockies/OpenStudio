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

  boost::optional<double> loadSideReferenceFlowRate() const;
  bool isLoadSideReferenceFlowRateAutosized() const;

  boost::optional<double> sourceSideReferenceFlowRate() const;
  bool isSourceSideReferenceFlowRateAutosized() const;

  boost::optional<double> heatRecoveryReferenceFlowRate() const;
  bool isHeatRecoveryReferenceFlowRateAutosized() const;

  boost::optional<double> referenceCapacity() const;
  bool isReferenceCapacityAutosized() const;

  double referenceCoefficientofPerformance() const;
  double sizingFactor() const;

  std::string controlType() const;
  std::string flowMode() const;

  double minimumPartLoadRatio() const;
  double minimumSourceInletTemperature() const;
  double maximumSourceInletTemperature() const;

  double maximumHeatRecoveryOutletTemperature() const;
  double thermosiphonMinimumTemperatureDifference() const;

  bool setCondenserType(const std::string& condenserType);

  bool setLoadSideReferenceFlowRate(double loadSideReferenceFlowRate);
  void autosizeLoadSideReferenceFlowRate();

  bool setSourceSideReferenceFlowRate(double sourceSideReferenceFlowRate);
  void autosizeSourceSideReferenceFlowRate();

  bool setHeatRecoveryReferenceFlowRate(double heatRecoveryReferenceFlowRate);
  void autosizeHeatRecoveryReferenceFlowRate();

  bool setReferenceCapacity(double referenceCapacity);
  void autosizeReferenceCapacity();

  bool setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance);
  bool setSizingFactor(double sizingFactor);

  bool setControlType(const std::string& controlType);
  bool setFlowMode(const std::string& flowMode);

  bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
  bool setMinimumSourceInletTemperature(double minimumSourceInletTemperature);
  bool setMaximumSourceInletTemperature(double maximumSourceInletTemperature);

  bool setMaximumHeatRecoveryOutletTemperature(double maximumHeatRecoveryOutletTemperature);
  bool setThermosiphonMinimumTemperatureDifference(double thermosiphonMinimumTemperatureDifference);

  boost::optional<double> autosizedLoadSideReferenceFlowRate() const;
  boost::optional<double> autosizedSourceSideReferenceFlowRate() const;
  boost::optional<double> autosizedHeatRecoveryReferenceFlowRate() const;
  boost::optional<double> autosizedReferenceCapacity() const;

  std::vector<std::string> condenserTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
