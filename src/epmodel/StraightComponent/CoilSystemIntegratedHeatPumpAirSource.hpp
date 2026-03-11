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
  // - API: Preserve openstudio::model::CoilSystemIntegratedHeatPumpAirSource scalar accessor names/signatures.
  // - Field Mapping: Scalar APIs map directly to EnergyPlus CoilSystem:IntegratedHeatPump:AirSource numeric fields.
  // - ForwardTranslator evidence: ForwardTranslateCoilSystemIntegratedHeatPumpAirSource writes these scalar fields directly.
  // - Field Mapping: coil references and node-link fields (including Supply Hot Water Flow Sensor Node Name) are relationship-like and excluded here.
  // - TODO(parity): Add relationship APIs in a dedicated parity pass without changing scalar signatures.
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
