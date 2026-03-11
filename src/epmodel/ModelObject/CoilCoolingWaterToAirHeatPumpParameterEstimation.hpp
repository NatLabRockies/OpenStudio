/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPPARAMETERESTIMATION_HPP
#define EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPPARAMETERESTIMATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl;
}

class EPMODEL_API CoilCoolingWaterToAirHeatPumpParameterEstimation : public ModelObject
{
 public:
  explicit CoilCoolingWaterToAirHeatPumpParameterEstimation(const Model& model);

  virtual ~CoilCoolingWaterToAirHeatPumpParameterEstimation() override = default;
  CoilCoolingWaterToAirHeatPumpParameterEstimation(const CoilCoolingWaterToAirHeatPumpParameterEstimation& other) = default;
  CoilCoolingWaterToAirHeatPumpParameterEstimation(CoilCoolingWaterToAirHeatPumpParameterEstimation&& other) = default;
  CoilCoolingWaterToAirHeatPumpParameterEstimation& operator=(const CoilCoolingWaterToAirHeatPumpParameterEstimation&) = default;
  CoilCoolingWaterToAirHeatPumpParameterEstimation& operator=(CoilCoolingWaterToAirHeatPumpParameterEstimation&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> compressorTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class and accessor names.
  // - Field Mapping: Scalar APIs map directly to Coil:Cooling:WaterToAirHeatPump:ParameterEstimation scalar fields.
  // - Field Mapping: relationship-like fields (availability schedule, refrigerant type object-list, node names, and curve references) are excluded.
  // - TODO(parity): Add relationship APIs after scalar saturation without changing scalar signatures.
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

 protected:
  using ImplType = detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilCoolingWaterToAirHeatPumpParameterEstimation(std::shared_ptr<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
