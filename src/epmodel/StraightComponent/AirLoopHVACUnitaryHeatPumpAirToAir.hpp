/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACUNITARYHEATPUMPAIRTOAIR_HPP
#define EPMODEL_AIRLOOPHVACUNITARYHEATPUMPAIRTOAIR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirLoopHVACUnitaryHeatPumpAirToAir_Impl;
}

class EPMODEL_API AirLoopHVACUnitaryHeatPumpAirToAir : public ModelObject
{
 public:
  explicit AirLoopHVACUnitaryHeatPumpAirToAir(const Model& model);

  virtual ~AirLoopHVACUnitaryHeatPumpAirToAir() override = default;
  AirLoopHVACUnitaryHeatPumpAirToAir(const AirLoopHVACUnitaryHeatPumpAirToAir& other) = default;
  AirLoopHVACUnitaryHeatPumpAirToAir(AirLoopHVACUnitaryHeatPumpAirToAir&& other) = default;
  AirLoopHVACUnitaryHeatPumpAirToAir& operator=(const AirLoopHVACUnitaryHeatPumpAirToAir&) = default;
  AirLoopHVACUnitaryHeatPumpAirToAir& operator=(AirLoopHVACUnitaryHeatPumpAirToAir&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> validFanPlacementValues();
  static std::vector<std::string> validDehumidificationControlTypeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model scalar accessor names/signatures for this model-counterpart class.
  // - Field Mapping: supplyAirFlowRateDuring* APIs map to E+ Cooling/Heating/NoLoad Supply Air Flow Rate fields.
  // - Field Mapping: maximumSupplyAirTemperaturefromSupplementalHeater, maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation,
  //   fanPlacement, dehumidificationControlType, and dXHeatingCoilSizingRatio map directly to same-name E+ fields.
  // - Field Mapping: schedule/node/coil/fan/zone reference fields remain excluded as relationship fields.
  // - TODO(parity): Add relationship APIs incrementally without changing preserved scalar signatures.
  boost::optional<double> supplyAirFlowRateDuringCoolingOperation() const;
  bool isSupplyAirFlowRateDuringCoolingOperationAutosized() const;
  bool setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation);
  void autosizeSupplyAirFlowRateDuringCoolingOperation();

  boost::optional<double> supplyAirFlowRateDuringHeatingOperation() const;
  bool isSupplyAirFlowRateDuringHeatingOperationAutosized() const;
  bool setSupplyAirFlowRateDuringHeatingOperation(double n2);
  void autosizeSupplyAirFlowRateDuringHeatingOperation();

  boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
  bool isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
  bool setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
  void resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  void autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();

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

  double dXHeatingCoilSizingRatio() const;
  bool setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio);

 protected:
  using ImplType = detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirLoopHVACUnitaryHeatPumpAirToAir(std::shared_ptr<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
