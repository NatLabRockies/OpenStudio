/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACUNITARYHEATPUMPWATERTOAIR_HPP
#define EPMODEL_AIRLOOPHVACUNITARYHEATPUMPWATERTOAIR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirLoopHVACUnitaryHeatPumpWaterToAir_Impl;
}

class EPMODEL_API AirLoopHVACUnitaryHeatPumpWaterToAir : public ModelObject
{
 public:
  explicit AirLoopHVACUnitaryHeatPumpWaterToAir(const Model& model);

  virtual ~AirLoopHVACUnitaryHeatPumpWaterToAir() override = default;
  AirLoopHVACUnitaryHeatPumpWaterToAir(const AirLoopHVACUnitaryHeatPumpWaterToAir& other) = default;
  AirLoopHVACUnitaryHeatPumpWaterToAir(AirLoopHVACUnitaryHeatPumpWaterToAir&& other) = default;
  AirLoopHVACUnitaryHeatPumpWaterToAir& operator=(const AirLoopHVACUnitaryHeatPumpWaterToAir&) = default;
  AirLoopHVACUnitaryHeatPumpWaterToAir& operator=(AirLoopHVACUnitaryHeatPumpWaterToAir&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> supplyAirFanObjectTypeValues();
  static std::vector<std::string> heatingCoilObjectTypeValues();
  static std::vector<std::string> coolingCoilObjectTypeValues();
  static std::vector<std::string> supplementalHeatingCoilObjectTypeValues();
  static std::vector<std::string> fanPlacementValues();
  static std::vector<std::string> dehumidificationControlTypeValues();
  static std::vector<std::string> heatPumpCoilWaterFlowModeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to AirLoopHVAC:UnitaryHeatPump:WaterToAir numeric/choice fields.
  // - Field Mapping: Availability schedule, node fields, controlling zone, and *Name linkage fields remain excluded as relationship fields.
  // - TODO(parity): Add relationship APIs after scalar saturation without changing scalar signatures.
  boost::optional<double> supplyAirFlowRate() const;
  bool isSupplyAirFlowRateAutosized() const;
  bool setSupplyAirFlowRate(double supplyAirFlowRate);
  void autosizeSupplyAirFlowRate();

  std::string supplyAirFanObjectType() const;
  bool setSupplyAirFanObjectType(const std::string& supplyAirFanObjectType);

  std::string heatingCoilObjectType() const;
  bool setHeatingCoilObjectType(const std::string& heatingCoilObjectType);

  double heatingConvergence() const;
  bool isHeatingConvergenceDefaulted() const;
  bool setHeatingConvergence(double heatingConvergence);
  void resetHeatingConvergence();

  std::string coolingCoilObjectType() const;
  bool setCoolingCoilObjectType(const std::string& coolingCoilObjectType);

  double coolingConvergence() const;
  bool isCoolingConvergenceDefaulted() const;
  bool setCoolingConvergence(double coolingConvergence);
  void resetCoolingConvergence();

  std::string supplementalHeatingCoilObjectType() const;
  bool setSupplementalHeatingCoilObjectType(const std::string& supplementalHeatingCoilObjectType);

  boost::optional<double> maximumSupplyAirTemperaturefromSupplementalHeater() const;
  bool isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const;
  bool setMaximumSupplyAirTemperaturefromSupplementalHeater(double maximumSupplyAirTemperaturefromSupplementalHeater);
  void autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();

  double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const;
  bool isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const;
  bool setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
  void resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();

  std::string fanPlacement() const;
  bool isFanPlacementDefaulted() const;
  bool setFanPlacement(const std::string& fanPlacement);
  void resetFanPlacement();

  std::string dehumidificationControlType() const;
  bool isDehumidificationControlTypeDefaulted() const;
  bool setDehumidificationControlType(const std::string& dehumidificationControlType);
  void resetDehumidificationControlType();

  std::string heatPumpCoilWaterFlowMode() const;
  bool isHeatPumpCoilWaterFlowModeDefaulted() const;
  bool setHeatPumpCoilWaterFlowMode(const std::string& heatPumpCoilWaterFlowMode);
  void resetHeatPumpCoilWaterFlowMode();

  double dXHeatingCoilSizingRatio() const;
  bool isDXHeatingCoilSizingRatioDefaulted() const;
  bool setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio);
  void resetDXHeatingCoilSizingRatio();

 protected:
  using ImplType = detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirLoopHVACUnitaryHeatPumpWaterToAir(std::shared_ptr<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
