/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILSYSTEMINTEGRATEDHEATPUMPAIRSOURCE_HPP
#define EPMODEL_COILSYSTEMINTEGRATEDHEATPUMPAIRSOURCE_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CoilSystemIntegratedHeatPumpAirSource_Impl;
}

class EPMODEL_API CoilSystemIntegratedHeatPumpAirSource : public StraightComponent
{
 public:
  explicit CoilSystemIntegratedHeatPumpAirSource(const Model& model);

  virtual ~CoilSystemIntegratedHeatPumpAirSource() override = default;
  CoilSystemIntegratedHeatPumpAirSource(const CoilSystemIntegratedHeatPumpAirSource& other) = default;
  CoilSystemIntegratedHeatPumpAirSource(CoilSystemIntegratedHeatPumpAirSource&& other) = default;
  CoilSystemIntegratedHeatPumpAirSource& operator=(const CoilSystemIntegratedHeatPumpAirSource&) = default;
  CoilSystemIntegratedHeatPumpAirSource& operator=(CoilSystemIntegratedHeatPumpAirSource&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - Status: Partial Parity. The scalar control surface is present, but coil-reference and node-link helpers remain model-owned.
  // - Canonical Counterpart: openstudio::model::CoilSystemIntegratedHeatPumpAirSource.
  // - Implemented Parity: The temperature-limit, load-control, speed-level, and water-flow control scalars preserve the canonical API.
  // - Documented Delta: Coil references and node-link helpers from canonical `openstudio::model::CoilSystemIntegratedHeatPumpAirSource` are not exposed yet.
  // - Field/Storage Mapping: Preserved scalars map directly to EnergyPlus `CoilSystem:IntegratedHeatPump:AirSource` numeric fields.
  // - Evidence: `src/model/CoilSystemIntegratedHeatPumpAirSource.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilSystemIntegratedHeatPumpAirSource.cpp`, and `src/epmodel/test/CoilSystemIntegratedHeatPumpAirSource_GTest.cpp`.
  // - Remaining Parity Work: Add the omitted coil-reference and node-link helpers without changing the preserved scalar signatures.
  double indoorTemperatureLimitForSCWHMode() const;
  bool setIndoorTemperatureLimitForSCWHMode(double indoorTemperatureLimitForSCWHMode);

  double ambientTemperatureLimitForSCWHMode() const;
  bool setAmbientTemperatureLimitForSCWHMode(double ambientTemperatureLimitForSCWHMode);

  double indoorTemperatureAboveWhichWHHasHigherPriority() const;
  bool setIndoorTemperatureAboveWhichWHHasHigherPriority(double indoorTemperatureAboveWhichWHHasHigherPriority);

  double ambientTemperatureAboveWhichWHHasHigherPriority() const;
  bool setAmbientTemperatureAboveWhichWHHasHigherPriority(double ambientTemperatureAboveWhichWHHasHigherPriority);

  int flagtoIndicateLoadControlInSCWHMode() const;
  bool setFlagtoIndicateLoadControlInSCWHMode(int flagtoIndicateLoadControlInSCWHMode);

  int minimumSpeedLevelForSCWHMode() const;
  bool setMinimumSpeedLevelForSCWHMode(int minimumSpeedLevelForSCWHMode);

  double maximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode() const;
  bool setMaximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode(double maximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode);

  int minimumSpeedLevelForSCDWHMode() const;
  bool setMinimumSpeedLevelForSCDWHMode(int minimumSpeedLevelForSCDWHMode);

  double maximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode() const;
  bool setMaximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode(
    double maximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode);

  int minimumSpeedLevelForSHDWHMode() const;
  bool setMinimumSpeedLevelForSHDWHMode(int minimumSpeedLevelForSHDWHMode);

 protected:
  using ImplType = detail::CoilSystemIntegratedHeatPumpAirSource_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilSystemIntegratedHeatPumpAirSource(std::shared_ptr<detail::CoilSystemIntegratedHeatPumpAirSource_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
