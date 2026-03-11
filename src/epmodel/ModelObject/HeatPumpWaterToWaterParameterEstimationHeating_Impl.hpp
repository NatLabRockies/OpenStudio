/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPWATERTOWATERPARAMETERESTIMATIONHEATING_IMPL_HPP
#define EPMODEL_HEATPUMPWATERTOWATERPARAMETERESTIMATIONHEATING_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API HeatPumpWaterToWaterParameterEstimationHeating_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~HeatPumpWaterToWaterParameterEstimationHeating_Impl() override = default;

  boost::optional<double> nominalCOP() const;
  boost::optional<double> nominalCapacity() const;
  boost::optional<double> minimumPartLoadRatio() const;
  boost::optional<double> maximumPartLoadRatio() const;
  boost::optional<double> optimumPartLoadRatio() const;
  boost::optional<double> loadSideFlowRate() const;
  boost::optional<double> sourceSideFlowRate() const;
  boost::optional<double> loadSideHeatTransferCoefficient() const;
  boost::optional<double> sourceSideHeatTransferCoefficient() const;
  boost::optional<double> pistonDisplacement() const;
  boost::optional<double> compressorClearanceFactor() const;
  boost::optional<double> compressorSuctionandDischargePressureDrop() const;
  boost::optional<double> superheating() const;
  boost::optional<double> constantPartofElectromechanicalPowerLosses() const;
  boost::optional<double> lossFactor() const;
  double highPressureCutOff() const;
  bool isHighPressureCutOffDefaulted() const;
  double lowPressureCutOff() const;
  bool isLowPressureCutOffDefaulted() const;

  bool setNominalCOP(double nominalCOP);
  bool setNominalCapacity(double nominalCapacity);
  bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
  bool setMaximumPartLoadRatio(double maximumPartLoadRatio);
  bool setOptimumPartLoadRatio(double optimumPartLoadRatio);
  bool setLoadSideFlowRate(double loadSideFlowRate);
  bool setSourceSideFlowRate(double sourceSideFlowRate);
  bool setLoadSideHeatTransferCoefficient(double loadSideHeatTransferCoefficient);
  bool setSourceSideHeatTransferCoefficient(double sourceSideHeatTransferCoefficient);
  bool setPistonDisplacement(double pistonDisplacement);
  bool setCompressorClearanceFactor(double compressorClearanceFactor);
  bool setCompressorSuctionandDischargePressureDrop(double compressorSuctionandDischargePressureDrop);
  bool setSuperheating(double superheating);
  bool setConstantPartofElectromechanicalPowerLosses(double constantPartofElectromechanicalPowerLosses);
  bool setLossFactor(double lossFactor);
  bool setHighPressureCutOff(double highPressureCutOff);
  void resetHighPressureCutOff();
  bool setLowPressureCutOff(double lowPressureCutOff);
  void resetLowPressureCutOff();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
