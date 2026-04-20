/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGWATERTOAIRHEATPUMPPARAMETERESTIMATION_HPP
#define EPMODEL_COILHEATINGWATERTOAIRHEATPUMPPARAMETERESTIMATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl;
}

class EPMODEL_API CoilHeatingWaterToAirHeatPumpParameterEstimation : public ModelObject
{
 public:
  explicit CoilHeatingWaterToAirHeatPumpParameterEstimation(const Model& model);

  virtual ~CoilHeatingWaterToAirHeatPumpParameterEstimation() override = default;
  CoilHeatingWaterToAirHeatPumpParameterEstimation(const CoilHeatingWaterToAirHeatPumpParameterEstimation& other) = default;
  CoilHeatingWaterToAirHeatPumpParameterEstimation(CoilHeatingWaterToAirHeatPumpParameterEstimation&& other) = default;
  CoilHeatingWaterToAirHeatPumpParameterEstimation& operator=(const CoilHeatingWaterToAirHeatPumpParameterEstimation&) = default;
  CoilHeatingWaterToAirHeatPumpParameterEstimation& operator=(CoilHeatingWaterToAirHeatPumpParameterEstimation&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> compressorTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class and accessor names.
  // - Field Mapping: Scalar APIs map directly to Coil:Heating:WaterToAirHeatPump:ParameterEstimation scalar fields.
  // - Field Mapping: relationship-like fields (availability schedule, refrigerant type object-list, node names, and curve references) are excluded.
  // - TODO(parity): Add relationship APIs after scalar saturation without changing scalar signatures.
  std::string compressorType() const;
  bool setCompressorType(const std::string& compressorType);

  double designSourceSideFlowRate() const;
  bool setDesignSourceSideFlowRate(double designSourceSideFlowRate);

  double grossRatedHeatingCapacity() const;
  bool setGrossRatedHeatingCapacity(double grossRatedHeatingCapacity);

  double highPressureCutoff() const;
  bool setHighPressureCutoff(double highPressureCutoff);

  double lowPressureCutoff() const;
  bool setLowPressureCutoff(double lowPressureCutoff);

  double loadSideTotalHeatTransferCoefficient() const;
  bool setLoadSideTotalHeatTransferCoefficient(double loadSideTotalHeatTransferCoefficient);

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

 protected:
  using ImplType = detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilHeatingWaterToAirHeatPumpParameterEstimation(std::shared_ptr<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
