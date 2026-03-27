/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACUNITARYHEATPUMPAIRTOAIR_HPP
#define EPMODEL_AIRLOOPHVACUNITARYHEATPUMPAIRTOAIR_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;
class Node;

namespace detail {
class AirLoopHVACUnitaryHeatPumpAirToAir_Impl;
}

class EPMODEL_API AirLoopHVACUnitaryHeatPumpAirToAir : public StraightComponent
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
  // - Status: Partial Parity. The scalar unitary heat-pump controls are aligned, but the schedule, fan, coil, and zone-link surface is still intentionally narrower.
  // - Canonical Counterpart: openstudio::model::AirLoopHVACUnitaryHeatPumpAirToAir.
  // - Implemented Parity: `supplyAirFlowRateDuringCoolingOperation`, `supplyAirFlowRateDuringHeatingOperation`, `supplyAirFlowRateWhenNoCoolingorHeatingisNeeded`, `maximumSupplyAirTemperaturefromSupplementalHeater`, `maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation`, `fanPlacement`, `dehumidificationControlType`, and `dXHeatingCoilSizingRatio` preserve the canonical scalar contract.
  // - Documented Delta: Schedule, fan, coil, and zone reference fields are not exposed as public accessors yet.
  // - Field/Storage Mapping: The preserved scalars map directly to EnergyPlus unitary heat-pump fields; the forward translator wires the equipment graph separately.
  // - Evidence: `src/model/AirLoopHVACUnitaryHeatPumpAirToAir.hpp`, `src/model/AirLoopHVACUnitaryHeatPumpAirToAir.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirLoopHVACUnitaryHeatPumpAirToAir.cpp`, and `src/epmodel/test/AirLoopHVACUnitaryHeatPumpAirToAir_GTest.cpp`.
  // - Remaining Parity Work: Add the omitted schedule, fan, coil, and zone-link helpers when relationship parity expands.
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

  bool addToNode(Node& node);

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
