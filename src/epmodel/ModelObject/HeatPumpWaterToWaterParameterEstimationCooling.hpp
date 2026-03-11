/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPWATERTOWATERPARAMETERESTIMATIONCOOLING_HPP
#define EPMODEL_HEATPUMPWATERTOWATERPARAMETERESTIMATIONCOOLING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HeatPumpWaterToWaterParameterEstimationCooling_Impl;
}

class EPMODEL_API HeatPumpWaterToWaterParameterEstimationCooling : public ModelObject
{
 public:
  explicit HeatPumpWaterToWaterParameterEstimationCooling(const Model& model);

  virtual ~HeatPumpWaterToWaterParameterEstimationCooling() override = default;
  HeatPumpWaterToWaterParameterEstimationCooling(const HeatPumpWaterToWaterParameterEstimationCooling& other) = default;
  HeatPumpWaterToWaterParameterEstimationCooling(HeatPumpWaterToWaterParameterEstimationCooling&& other) = default;
  HeatPumpWaterToWaterParameterEstimationCooling& operator=(const HeatPumpWaterToWaterParameterEstimationCooling&) = default;
  HeatPumpWaterToWaterParameterEstimationCooling& operator=(HeatPumpWaterToWaterParameterEstimationCooling&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to HeatPump:WaterToWater:ParameterEstimation:Cooling numeric fields.
  // - Field Mapping: Name and source/load-side node linkage fields remain excluded as relationship fields.
  // - TODO(parity): Add non-scalar relationship APIs after scalar saturation without changing scalar signatures.
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

 protected:
  using ImplType = detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HeatPumpWaterToWaterParameterEstimationCooling(std::shared_ptr<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
