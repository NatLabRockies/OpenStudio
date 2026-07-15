/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ElectricLoadCenterStorageBattery.hpp"
#include "ElectricLoadCenterStorageBattery_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/ElectricLoadCenter_Storage_Battery_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ElectricLoadCenterStorageBattery::ElectricLoadCenterStorageBattery(const Model& model)
    : ModelObject(ElectricLoadCenterStorageBattery::iddObjectType(), model) {}

  ElectricLoadCenterStorageBattery::ElectricLoadCenterStorageBattery(std::shared_ptr<detail::ElectricLoadCenterStorageBattery_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ElectricLoadCenterStorageBattery::iddObjectType() {
    return IddObjectType::ElectricLoadCenter_Storage_Battery;
  }

  double ElectricLoadCenterStorageBattery::radiativeFraction() const {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->radiativeFraction();
  }

  bool ElectricLoadCenterStorageBattery::isRadiativeFractionDefaulted() const {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->isRadiativeFractionDefaulted();
  }

  bool ElectricLoadCenterStorageBattery::setRadiativeFraction(double radiativeFraction) {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->setRadiativeFraction(radiativeFraction);
  }

  void ElectricLoadCenterStorageBattery::resetRadiativeFraction() {
    getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->resetRadiativeFraction();
  }

  int ElectricLoadCenterStorageBattery::numberofBatteryModulesinParallel() const {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->numberofBatteryModulesinParallel();
  }

  bool ElectricLoadCenterStorageBattery::isNumberofBatteryModulesinParallelDefaulted() const {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->isNumberofBatteryModulesinParallelDefaulted();
  }

  bool ElectricLoadCenterStorageBattery::setNumberofBatteryModulesinParallel(int numberofBatteryModulesinParallel) {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->setNumberofBatteryModulesinParallel(numberofBatteryModulesinParallel);
  }

  void ElectricLoadCenterStorageBattery::resetNumberofBatteryModulesinParallel() {
    getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->resetNumberofBatteryModulesinParallel();
  }

  int ElectricLoadCenterStorageBattery::numberofBatteryModulesinSeries() const {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->numberofBatteryModulesinSeries();
  }

  bool ElectricLoadCenterStorageBattery::isNumberofBatteryModulesinSeriesDefaulted() const {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->isNumberofBatteryModulesinSeriesDefaulted();
  }

  bool ElectricLoadCenterStorageBattery::setNumberofBatteryModulesinSeries(int numberofBatteryModulesinSeries) {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->setNumberofBatteryModulesinSeries(numberofBatteryModulesinSeries);
  }

  void ElectricLoadCenterStorageBattery::resetNumberofBatteryModulesinSeries() {
    getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->resetNumberofBatteryModulesinSeries();
  }

  boost::optional<double> ElectricLoadCenterStorageBattery::maximumModuleCapacity() const {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->maximumModuleCapacity();
  }

  bool ElectricLoadCenterStorageBattery::setMaximumModuleCapacity(double maximumModuleCapacity) {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->setMaximumModuleCapacity(maximumModuleCapacity);
  }

  void ElectricLoadCenterStorageBattery::resetMaximumModuleCapacity() {
    getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->resetMaximumModuleCapacity();
  }

  double ElectricLoadCenterStorageBattery::initialFractionalStateofCharge() const {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->initialFractionalStateofCharge();
  }

  bool ElectricLoadCenterStorageBattery::isInitialFractionalStateofChargeDefaulted() const {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->isInitialFractionalStateofChargeDefaulted();
  }

  bool ElectricLoadCenterStorageBattery::setInitialFractionalStateofCharge(double initialFractionalStateofCharge) {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->setInitialFractionalStateofCharge(initialFractionalStateofCharge);
  }

  void ElectricLoadCenterStorageBattery::resetInitialFractionalStateofCharge() {
    getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->resetInitialFractionalStateofCharge();
  }

  boost::optional<double> ElectricLoadCenterStorageBattery::fractionofAvailableChargeCapacity() const {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->fractionofAvailableChargeCapacity();
  }

  bool ElectricLoadCenterStorageBattery::setFractionofAvailableChargeCapacity(double fractionofAvailableChargeCapacity) {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->setFractionofAvailableChargeCapacity(fractionofAvailableChargeCapacity);
  }

  void ElectricLoadCenterStorageBattery::resetFractionofAvailableChargeCapacity() {
    getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->resetFractionofAvailableChargeCapacity();
  }

  boost::optional<double> ElectricLoadCenterStorageBattery::changeRatefromBoundChargetoAvailableCharge() const {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->changeRatefromBoundChargetoAvailableCharge();
  }

  bool ElectricLoadCenterStorageBattery::setChangeRatefromBoundChargetoAvailableCharge(double changeRatefromBoundChargetoAvailableCharge) {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->setChangeRatefromBoundChargetoAvailableCharge(
      changeRatefromBoundChargetoAvailableCharge);
  }

  void ElectricLoadCenterStorageBattery::resetChangeRatefromBoundChargetoAvailableCharge() {
    getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->resetChangeRatefromBoundChargetoAvailableCharge();
  }

  boost::optional<double> ElectricLoadCenterStorageBattery::fullyChargedModuleOpenCircuitVoltage() const {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->fullyChargedModuleOpenCircuitVoltage();
  }

  bool ElectricLoadCenterStorageBattery::setFullyChargedModuleOpenCircuitVoltage(double fullyChargedModuleOpenCircuitVoltage) {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->setFullyChargedModuleOpenCircuitVoltage(fullyChargedModuleOpenCircuitVoltage);
  }

  void ElectricLoadCenterStorageBattery::resetFullyChargedModuleOpenCircuitVoltage() {
    getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->resetFullyChargedModuleOpenCircuitVoltage();
  }

  boost::optional<double> ElectricLoadCenterStorageBattery::fullyDischargedModuleOpenCircuitVoltage() const {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->fullyDischargedModuleOpenCircuitVoltage();
  }

  bool ElectricLoadCenterStorageBattery::setFullyDischargedModuleOpenCircuitVoltage(double fullyDischargedModuleOpenCircuitVoltage) {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->setFullyDischargedModuleOpenCircuitVoltage(
      fullyDischargedModuleOpenCircuitVoltage);
  }

  void ElectricLoadCenterStorageBattery::resetFullyDischargedModuleOpenCircuitVoltage() {
    getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->resetFullyDischargedModuleOpenCircuitVoltage();
  }

  boost::optional<double> ElectricLoadCenterStorageBattery::moduleInternalElectricalResistance() const {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->moduleInternalElectricalResistance();
  }

  bool ElectricLoadCenterStorageBattery::setModuleInternalElectricalResistance(double moduleInternalElectricalResistance) {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->setModuleInternalElectricalResistance(moduleInternalElectricalResistance);
  }

  void ElectricLoadCenterStorageBattery::resetModuleInternalElectricalResistance() {
    getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->resetModuleInternalElectricalResistance();
  }

  boost::optional<double> ElectricLoadCenterStorageBattery::maximumModuleDischargingCurrent() const {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->maximumModuleDischargingCurrent();
  }

  bool ElectricLoadCenterStorageBattery::setMaximumModuleDischargingCurrent(double maximumModuleDischargingCurrent) {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->setMaximumModuleDischargingCurrent(maximumModuleDischargingCurrent);
  }

  void ElectricLoadCenterStorageBattery::resetMaximumModuleDischargingCurrent() {
    getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->resetMaximumModuleDischargingCurrent();
  }

  boost::optional<double> ElectricLoadCenterStorageBattery::moduleCutoffVoltage() const {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->moduleCutoffVoltage();
  }

  bool ElectricLoadCenterStorageBattery::setModuleCutoffVoltage(double moduleCutoffVoltage) {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->setModuleCutoffVoltage(moduleCutoffVoltage);
  }

  void ElectricLoadCenterStorageBattery::resetModuleCutoffVoltage() {
    getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->resetModuleCutoffVoltage();
  }

  double ElectricLoadCenterStorageBattery::moduleChargeRateLimit() const {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->moduleChargeRateLimit();
  }

  bool ElectricLoadCenterStorageBattery::isModuleChargeRateLimitDefaulted() const {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->isModuleChargeRateLimitDefaulted();
  }

  bool ElectricLoadCenterStorageBattery::setModuleChargeRateLimit(double moduleChargeRateLimit) {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->setModuleChargeRateLimit(moduleChargeRateLimit);
  }

  void ElectricLoadCenterStorageBattery::resetModuleChargeRateLimit() {
    getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->resetModuleChargeRateLimit();
  }

  bool ElectricLoadCenterStorageBattery::batteryLifeCalculation() const {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->batteryLifeCalculation();
  }

  bool ElectricLoadCenterStorageBattery::isBatteryLifeCalculationDefaulted() const {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->isBatteryLifeCalculationDefaulted();
  }

  bool ElectricLoadCenterStorageBattery::setBatteryLifeCalculation(bool batteryLifeCalculation) {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->setBatteryLifeCalculation(batteryLifeCalculation);
  }

  void ElectricLoadCenterStorageBattery::resetBatteryLifeCalculation() {
    getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->resetBatteryLifeCalculation();
  }

  int ElectricLoadCenterStorageBattery::numberofCycleBins() const {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->numberofCycleBins();
  }

  bool ElectricLoadCenterStorageBattery::isNumberofCycleBinsDefaulted() const {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->isNumberofCycleBinsDefaulted();
  }

  bool ElectricLoadCenterStorageBattery::setNumberofCycleBins(int numberofCycleBins) {
    return getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->setNumberofCycleBins(numberofCycleBins);
  }

  void ElectricLoadCenterStorageBattery::resetNumberofCycleBins() {
    getImpl<detail::ElectricLoadCenterStorageBattery_Impl>()->resetNumberofCycleBins();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      bool getBooleanFieldValue(const ModelObject_Impl& impl, int fieldIndex) {
        const auto value = impl.getString(fieldIndex, true);
        OS_ASSERT(value);
        return openstudio::istringEqual(*value, "yes");
      }

      bool setBooleanFieldValue(ModelObject_Impl& impl, int fieldIndex, bool value) {
        return impl.setString(fieldIndex, value ? "Yes" : "No");
      }

    }  // namespace

    double ElectricLoadCenterStorageBattery_Impl::radiativeFraction() const {
      const auto value = getDouble(openstudio::ElectricLoadCenter_Storage_BatteryFields::RadiativeFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ElectricLoadCenterStorageBattery_Impl::isRadiativeFractionDefaulted() const {
      return isEmpty(openstudio::ElectricLoadCenter_Storage_BatteryFields::RadiativeFraction);
    }

    bool ElectricLoadCenterStorageBattery_Impl::setRadiativeFraction(double radiativeFraction) {
      return setDouble(openstudio::ElectricLoadCenter_Storage_BatteryFields::RadiativeFraction, radiativeFraction);
    }

    void ElectricLoadCenterStorageBattery_Impl::resetRadiativeFraction() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Storage_BatteryFields::RadiativeFraction, ""));
    }

    int ElectricLoadCenterStorageBattery_Impl::numberofBatteryModulesinParallel() const {
      const auto value = getInt(openstudio::ElectricLoadCenter_Storage_BatteryFields::NumberofBatteryModulesinParallel, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ElectricLoadCenterStorageBattery_Impl::isNumberofBatteryModulesinParallelDefaulted() const {
      return isEmpty(openstudio::ElectricLoadCenter_Storage_BatteryFields::NumberofBatteryModulesinParallel);
    }

    bool ElectricLoadCenterStorageBattery_Impl::setNumberofBatteryModulesinParallel(int numberofBatteryModulesinParallel) {
      return setInt(openstudio::ElectricLoadCenter_Storage_BatteryFields::NumberofBatteryModulesinParallel, numberofBatteryModulesinParallel);
    }

    void ElectricLoadCenterStorageBattery_Impl::resetNumberofBatteryModulesinParallel() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Storage_BatteryFields::NumberofBatteryModulesinParallel, ""));
    }

    int ElectricLoadCenterStorageBattery_Impl::numberofBatteryModulesinSeries() const {
      const auto value = getInt(openstudio::ElectricLoadCenter_Storage_BatteryFields::NumberofBatteryModulesinSeries, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ElectricLoadCenterStorageBattery_Impl::isNumberofBatteryModulesinSeriesDefaulted() const {
      return isEmpty(openstudio::ElectricLoadCenter_Storage_BatteryFields::NumberofBatteryModulesinSeries);
    }

    bool ElectricLoadCenterStorageBattery_Impl::setNumberofBatteryModulesinSeries(int numberofBatteryModulesinSeries) {
      return setInt(openstudio::ElectricLoadCenter_Storage_BatteryFields::NumberofBatteryModulesinSeries, numberofBatteryModulesinSeries);
    }

    void ElectricLoadCenterStorageBattery_Impl::resetNumberofBatteryModulesinSeries() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Storage_BatteryFields::NumberofBatteryModulesinSeries, ""));
    }

    boost::optional<double> ElectricLoadCenterStorageBattery_Impl::maximumModuleCapacity() const {
      return getDouble(openstudio::ElectricLoadCenter_Storage_BatteryFields::MaximumModuleCapacity, true);
    }

    bool ElectricLoadCenterStorageBattery_Impl::setMaximumModuleCapacity(double maximumModuleCapacity) {
      return setDouble(openstudio::ElectricLoadCenter_Storage_BatteryFields::MaximumModuleCapacity, maximumModuleCapacity);
    }

    void ElectricLoadCenterStorageBattery_Impl::resetMaximumModuleCapacity() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Storage_BatteryFields::MaximumModuleCapacity, ""));
    }

    double ElectricLoadCenterStorageBattery_Impl::initialFractionalStateofCharge() const {
      const auto value = getDouble(openstudio::ElectricLoadCenter_Storage_BatteryFields::InitialFractionalStateofCharge, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ElectricLoadCenterStorageBattery_Impl::isInitialFractionalStateofChargeDefaulted() const {
      return isEmpty(openstudio::ElectricLoadCenter_Storage_BatteryFields::InitialFractionalStateofCharge);
    }

    bool ElectricLoadCenterStorageBattery_Impl::setInitialFractionalStateofCharge(double initialFractionalStateofCharge) {
      return setDouble(openstudio::ElectricLoadCenter_Storage_BatteryFields::InitialFractionalStateofCharge, initialFractionalStateofCharge);
    }

    void ElectricLoadCenterStorageBattery_Impl::resetInitialFractionalStateofCharge() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Storage_BatteryFields::InitialFractionalStateofCharge, ""));
    }

    boost::optional<double> ElectricLoadCenterStorageBattery_Impl::fractionofAvailableChargeCapacity() const {
      return getDouble(openstudio::ElectricLoadCenter_Storage_BatteryFields::FractionofAvailableChargeCapacity, true);
    }

    bool ElectricLoadCenterStorageBattery_Impl::setFractionofAvailableChargeCapacity(double fractionofAvailableChargeCapacity) {
      return setDouble(openstudio::ElectricLoadCenter_Storage_BatteryFields::FractionofAvailableChargeCapacity, fractionofAvailableChargeCapacity);
    }

    void ElectricLoadCenterStorageBattery_Impl::resetFractionofAvailableChargeCapacity() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Storage_BatteryFields::FractionofAvailableChargeCapacity, ""));
    }

    boost::optional<double> ElectricLoadCenterStorageBattery_Impl::changeRatefromBoundChargetoAvailableCharge() const {
      return getDouble(openstudio::ElectricLoadCenter_Storage_BatteryFields::ChangeRatefromBoundChargetoAvailableCharge, true);
    }

    bool ElectricLoadCenterStorageBattery_Impl::setChangeRatefromBoundChargetoAvailableCharge(double changeRatefromBoundChargetoAvailableCharge) {
      return setDouble(openstudio::ElectricLoadCenter_Storage_BatteryFields::ChangeRatefromBoundChargetoAvailableCharge,
                       changeRatefromBoundChargetoAvailableCharge);
    }

    void ElectricLoadCenterStorageBattery_Impl::resetChangeRatefromBoundChargetoAvailableCharge() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Storage_BatteryFields::ChangeRatefromBoundChargetoAvailableCharge, ""));
    }

    boost::optional<double> ElectricLoadCenterStorageBattery_Impl::fullyChargedModuleOpenCircuitVoltage() const {
      return getDouble(openstudio::ElectricLoadCenter_Storage_BatteryFields::FullyChargedModuleOpenCircuitVoltage, true);
    }

    bool ElectricLoadCenterStorageBattery_Impl::setFullyChargedModuleOpenCircuitVoltage(double fullyChargedModuleOpenCircuitVoltage) {
      return setDouble(openstudio::ElectricLoadCenter_Storage_BatteryFields::FullyChargedModuleOpenCircuitVoltage,
                       fullyChargedModuleOpenCircuitVoltage);
    }

    void ElectricLoadCenterStorageBattery_Impl::resetFullyChargedModuleOpenCircuitVoltage() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Storage_BatteryFields::FullyChargedModuleOpenCircuitVoltage, ""));
    }

    boost::optional<double> ElectricLoadCenterStorageBattery_Impl::fullyDischargedModuleOpenCircuitVoltage() const {
      return getDouble(openstudio::ElectricLoadCenter_Storage_BatteryFields::FullyDischargedModuleOpenCircuitVoltage, true);
    }

    bool ElectricLoadCenterStorageBattery_Impl::setFullyDischargedModuleOpenCircuitVoltage(double fullyDischargedModuleOpenCircuitVoltage) {
      return setDouble(openstudio::ElectricLoadCenter_Storage_BatteryFields::FullyDischargedModuleOpenCircuitVoltage,
                       fullyDischargedModuleOpenCircuitVoltage);
    }

    void ElectricLoadCenterStorageBattery_Impl::resetFullyDischargedModuleOpenCircuitVoltage() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Storage_BatteryFields::FullyDischargedModuleOpenCircuitVoltage, ""));
    }

    boost::optional<double> ElectricLoadCenterStorageBattery_Impl::moduleInternalElectricalResistance() const {
      return getDouble(openstudio::ElectricLoadCenter_Storage_BatteryFields::ModuleInternalElectricalResistance, true);
    }

    bool ElectricLoadCenterStorageBattery_Impl::setModuleInternalElectricalResistance(double moduleInternalElectricalResistance) {
      return setDouble(openstudio::ElectricLoadCenter_Storage_BatteryFields::ModuleInternalElectricalResistance, moduleInternalElectricalResistance);
    }

    void ElectricLoadCenterStorageBattery_Impl::resetModuleInternalElectricalResistance() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Storage_BatteryFields::ModuleInternalElectricalResistance, ""));
    }

    boost::optional<double> ElectricLoadCenterStorageBattery_Impl::maximumModuleDischargingCurrent() const {
      return getDouble(openstudio::ElectricLoadCenter_Storage_BatteryFields::MaximumModuleDischargingCurrent, true);
    }

    bool ElectricLoadCenterStorageBattery_Impl::setMaximumModuleDischargingCurrent(double maximumModuleDischargingCurrent) {
      return setDouble(openstudio::ElectricLoadCenter_Storage_BatteryFields::MaximumModuleDischargingCurrent, maximumModuleDischargingCurrent);
    }

    void ElectricLoadCenterStorageBattery_Impl::resetMaximumModuleDischargingCurrent() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Storage_BatteryFields::MaximumModuleDischargingCurrent, ""));
    }

    boost::optional<double> ElectricLoadCenterStorageBattery_Impl::moduleCutoffVoltage() const {
      return getDouble(openstudio::ElectricLoadCenter_Storage_BatteryFields::ModuleCutoffVoltage, true);
    }

    bool ElectricLoadCenterStorageBattery_Impl::setModuleCutoffVoltage(double moduleCutoffVoltage) {
      return setDouble(openstudio::ElectricLoadCenter_Storage_BatteryFields::ModuleCutoffVoltage, moduleCutoffVoltage);
    }

    void ElectricLoadCenterStorageBattery_Impl::resetModuleCutoffVoltage() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Storage_BatteryFields::ModuleCutoffVoltage, ""));
    }

    double ElectricLoadCenterStorageBattery_Impl::moduleChargeRateLimit() const {
      const auto value = getDouble(openstudio::ElectricLoadCenter_Storage_BatteryFields::ModuleChargeRateLimit, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ElectricLoadCenterStorageBattery_Impl::isModuleChargeRateLimitDefaulted() const {
      return isEmpty(openstudio::ElectricLoadCenter_Storage_BatteryFields::ModuleChargeRateLimit);
    }

    bool ElectricLoadCenterStorageBattery_Impl::setModuleChargeRateLimit(double moduleChargeRateLimit) {
      return setDouble(openstudio::ElectricLoadCenter_Storage_BatteryFields::ModuleChargeRateLimit, moduleChargeRateLimit);
    }

    void ElectricLoadCenterStorageBattery_Impl::resetModuleChargeRateLimit() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Storage_BatteryFields::ModuleChargeRateLimit, ""));
    }

    bool ElectricLoadCenterStorageBattery_Impl::batteryLifeCalculation() const {
      return getBooleanFieldValue(*this, openstudio::ElectricLoadCenter_Storage_BatteryFields::BatteryLifeCalculation);
    }

    bool ElectricLoadCenterStorageBattery_Impl::isBatteryLifeCalculationDefaulted() const {
      return isEmpty(openstudio::ElectricLoadCenter_Storage_BatteryFields::BatteryLifeCalculation);
    }

    bool ElectricLoadCenterStorageBattery_Impl::setBatteryLifeCalculation(bool batteryLifeCalculation) {
      const bool result =
        setBooleanFieldValue(*this, openstudio::ElectricLoadCenter_Storage_BatteryFields::BatteryLifeCalculation, batteryLifeCalculation);
      OS_ASSERT(result);
      return result;
    }

    void ElectricLoadCenterStorageBattery_Impl::resetBatteryLifeCalculation() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Storage_BatteryFields::BatteryLifeCalculation, ""));
    }

    int ElectricLoadCenterStorageBattery_Impl::numberofCycleBins() const {
      const auto value = getInt(openstudio::ElectricLoadCenter_Storage_BatteryFields::NumberofCycleBins, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ElectricLoadCenterStorageBattery_Impl::isNumberofCycleBinsDefaulted() const {
      return isEmpty(openstudio::ElectricLoadCenter_Storage_BatteryFields::NumberofCycleBins);
    }

    bool ElectricLoadCenterStorageBattery_Impl::setNumberofCycleBins(int numberofCycleBins) {
      return setInt(openstudio::ElectricLoadCenter_Storage_BatteryFields::NumberofCycleBins, numberofCycleBins);
    }

    void ElectricLoadCenterStorageBattery_Impl::resetNumberofCycleBins() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Storage_BatteryFields::NumberofCycleBins, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
