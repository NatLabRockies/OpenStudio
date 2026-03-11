/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICLOADCENTERSTORAGEBATTERY_HPP
#define EPMODEL_ELECTRICLOADCENTERSTORAGEBATTERY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ElectricLoadCenterStorageBattery_Impl;
}

class EPMODEL_API ElectricLoadCenterStorageBattery : public ModelObject
{
 public:
  explicit ElectricLoadCenterStorageBattery(const Model& model);

  virtual ~ElectricLoadCenterStorageBattery() override = default;
  ElectricLoadCenterStorageBattery(const ElectricLoadCenterStorageBattery& other) = default;
  ElectricLoadCenterStorageBattery(ElectricLoadCenterStorageBattery&& other) = default;
  ElectricLoadCenterStorageBattery& operator=(const ElectricLoadCenterStorageBattery&) = default;
  ElectricLoadCenterStorageBattery& operator=(ElectricLoadCenterStorageBattery&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar accessors map directly to ElectricLoadCenter:Storage:Battery numeric and boolean choice fields.
  // - Field Mapping: Availability Schedule Name, Zone Name, Voltage Change Curve Name for Charging,
  //   Voltage Change Curve Name for Discharging, and Battery Life Curve Name are relationship-like link fields and
  //   intentionally excluded from scalar accessor scope.
  // - ForwardTranslator evidence: no openstudio::model counterpart exists; IDD-derived naming is used for this EP-only type.
  // - TODO(parity): Add relationship APIs incrementally without breaking scalar signatures.
  double radiativeFraction() const;
  bool isRadiativeFractionDefaulted() const;
  bool setRadiativeFraction(double radiativeFraction);
  void resetRadiativeFraction();

  int numberofBatteryModulesinParallel() const;
  bool isNumberofBatteryModulesinParallelDefaulted() const;
  bool setNumberofBatteryModulesinParallel(int numberofBatteryModulesinParallel);
  void resetNumberofBatteryModulesinParallel();

  int numberofBatteryModulesinSeries() const;
  bool isNumberofBatteryModulesinSeriesDefaulted() const;
  bool setNumberofBatteryModulesinSeries(int numberofBatteryModulesinSeries);
  void resetNumberofBatteryModulesinSeries();

  boost::optional<double> maximumModuleCapacity() const;
  bool setMaximumModuleCapacity(double maximumModuleCapacity);
  void resetMaximumModuleCapacity();

  double initialFractionalStateofCharge() const;
  bool isInitialFractionalStateofChargeDefaulted() const;
  bool setInitialFractionalStateofCharge(double initialFractionalStateofCharge);
  void resetInitialFractionalStateofCharge();

  boost::optional<double> fractionofAvailableChargeCapacity() const;
  bool setFractionofAvailableChargeCapacity(double fractionofAvailableChargeCapacity);
  void resetFractionofAvailableChargeCapacity();

  boost::optional<double> changeRatefromBoundChargetoAvailableCharge() const;
  bool setChangeRatefromBoundChargetoAvailableCharge(double changeRatefromBoundChargetoAvailableCharge);
  void resetChangeRatefromBoundChargetoAvailableCharge();

  boost::optional<double> fullyChargedModuleOpenCircuitVoltage() const;
  bool setFullyChargedModuleOpenCircuitVoltage(double fullyChargedModuleOpenCircuitVoltage);
  void resetFullyChargedModuleOpenCircuitVoltage();

  boost::optional<double> fullyDischargedModuleOpenCircuitVoltage() const;
  bool setFullyDischargedModuleOpenCircuitVoltage(double fullyDischargedModuleOpenCircuitVoltage);
  void resetFullyDischargedModuleOpenCircuitVoltage();

  boost::optional<double> moduleInternalElectricalResistance() const;
  bool setModuleInternalElectricalResistance(double moduleInternalElectricalResistance);
  void resetModuleInternalElectricalResistance();

  boost::optional<double> maximumModuleDischargingCurrent() const;
  bool setMaximumModuleDischargingCurrent(double maximumModuleDischargingCurrent);
  void resetMaximumModuleDischargingCurrent();

  boost::optional<double> moduleCutoffVoltage() const;
  bool setModuleCutoffVoltage(double moduleCutoffVoltage);
  void resetModuleCutoffVoltage();

  double moduleChargeRateLimit() const;
  bool isModuleChargeRateLimitDefaulted() const;
  bool setModuleChargeRateLimit(double moduleChargeRateLimit);
  void resetModuleChargeRateLimit();

  bool batteryLifeCalculation() const;
  bool isBatteryLifeCalculationDefaulted() const;
  bool setBatteryLifeCalculation(bool batteryLifeCalculation);
  void resetBatteryLifeCalculation();

  int numberofCycleBins() const;
  bool isNumberofCycleBinsDefaulted() const;
  bool setNumberofCycleBins(int numberofCycleBins);
  void resetNumberofCycleBins();

 protected:
  using ImplType = detail::ElectricLoadCenterStorageBattery_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ElectricLoadCenterStorageBattery(std::shared_ptr<detail::ElectricLoadCenterStorageBattery_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
