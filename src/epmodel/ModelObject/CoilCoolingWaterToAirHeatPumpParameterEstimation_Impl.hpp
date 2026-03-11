/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPPARAMETERESTIMATION_IMPL_HPP
#define EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPPARAMETERESTIMATION_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl : public ModelObject_Impl
{
 public:
  // Scalar-only scaffold: relationship-like fields are intentionally excluded for this cycle.
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl() override = default;

  std::string compressorType() const;
  bool setCompressorType(const std::string& compressorType);

  double designSourceSideFlowRate() const;
  bool setDesignSourceSideFlowRate(double designSourceSideFlowRate);

  double nominalCoolingCoilCapacity() const;
  bool setNominalCoolingCoilCapacity(double nominalCoolingCoilCapacity);

  double nominalTimeforCondensateRemovaltoBegin() const;
  bool isNominalTimeforCondensateRemovaltoBeginDefaulted() const;
  bool setNominalTimeforCondensateRemovaltoBegin(double nominalTimeforCondensateRemovaltoBegin);
  void resetNominalTimeforCondensateRemovaltoBegin();

  double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity() const;
  bool isRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacityDefaulted() const;
  bool setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(
    double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity);
  void resetRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity();

  double highPressureCutoff() const;
  bool setHighPressureCutoff(double highPressureCutoff);

  double lowPressureCutoff() const;
  bool setLowPressureCutoff(double lowPressureCutoff);

  double loadSideTotalHeatTransferCoefficient() const;
  bool setLoadSideTotalHeatTransferCoefficient(double loadSideTotalHeatTransferCoefficient);

  double loadSideOutsideSurfaceHeatTransferCoefficient() const;
  bool setLoadSideOutsideSurfaceHeatTransferCoefficient(double loadSideOutsideSurfaceHeatTransferCoefficient);

  double superheatTemperatureattheEvaporatorOutlet() const;
  bool setSuperheatTemperatureattheEvaporatorOutlet(double superheatTemperatureattheEvaporatorOutlet);

  double compressorPowerLosses() const;
  bool setCompressorPowerLosses(double compressorPowerLosses);

  double compressorEfficiency() const;
  bool setCompressorEfficiency(double compressorEfficiency);

  boost::optional<double> compressorPistonDisplacement() const;
  bool setCompressorPistonDisplacement(double compressorPistonDisplacement);
  void resetCompressorPistonDisplacement();

  boost::optional<double> compressorSuctionDischargePressureDrop() const;
  bool setCompressorSuctionDischargePressureDrop(double compressorSuctionDischargePressureDrop);
  void resetCompressorSuctionDischargePressureDrop();

  boost::optional<double> compressorClearanceFactor() const;
  bool setCompressorClearanceFactor(double compressorClearanceFactor);
  void resetCompressorClearanceFactor();

  boost::optional<double> refrigerantVolumeFlowRate() const;
  bool setRefrigerantVolumeFlowRate(double refrigerantVolumeFlowRate);
  void resetRefrigerantVolumeFlowRate();

  boost::optional<double> volumeRatio() const;
  bool setVolumeRatio(double volumeRatio);
  void resetVolumeRatio();

  boost::optional<double> leakRateCoefficient() const;
  bool setLeakRateCoefficient(double leakRateCoefficient);
  void resetLeakRateCoefficient();

  boost::optional<double> sourceSideHeatTransferCoefficient() const;
  bool setSourceSideHeatTransferCoefficient(double sourceSideHeatTransferCoefficient);
  void resetSourceSideHeatTransferCoefficient();

  boost::optional<double> sourceSideHeatTransferResistance1() const;
  bool setSourceSideHeatTransferResistance1(double sourceSideHeatTransferResistance1);
  void resetSourceSideHeatTransferResistance1();

  boost::optional<double> sourceSideHeatTransferResistance2() const;
  bool setSourceSideHeatTransferResistance2(double sourceSideHeatTransferResistance2);
  void resetSourceSideHeatTransferResistance2();

  double maximumCyclingRate() const;
  bool isMaximumCyclingRateDefaulted() const;
  bool setMaximumCyclingRate(double maximumCyclingRate);
  void resetMaximumCyclingRate();

  double latentCapacityTimeConstant() const;
  bool isLatentCapacityTimeConstantDefaulted() const;
  bool setLatentCapacityTimeConstant(double latentCapacityTimeConstant);
  void resetLatentCapacityTimeConstant();

  double fanDelayTime() const;
  bool isFanDelayTimeDefaulted() const;
  bool setFanDelayTime(double fanDelayTime);
  void resetFanDelayTime();

  std::vector<std::string> compressorTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
