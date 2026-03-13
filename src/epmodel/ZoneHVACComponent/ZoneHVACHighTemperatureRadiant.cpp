/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACHighTemperatureRadiant.hpp"
#include "ZoneHVACComponent/ZoneHVACHighTemperatureRadiant_Impl.hpp"

#include "Model.hpp"

#include "../utilities/core/Assert.hpp"
#include "../utilities/core/Compare.hpp"

#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_HighTemperatureRadiant_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACHighTemperatureRadiant::ZoneHVACHighTemperatureRadiant(const Model& model)
    : ModelObject(ZoneHVACHighTemperatureRadiant::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>());

    autosizeMaximumPowerInput();
    OS_ASSERT(setFuelType("NaturalGas"));
    OS_ASSERT(setCombustionEfficiency(0.90));
    OS_ASSERT(setFractionofInputConvertedtoRadiantEnergy(0.70));
    OS_ASSERT(setFractionofInputConvertedtoLatentEnergy(0.00));
    OS_ASSERT(setFractionofInputthatIsLost(0.00));
    OS_ASSERT(setTemperatureControlType("OperativeTemperature"));
    OS_ASSERT(setHeatingThrottlingRange(2.0));
    OS_ASSERT(setFractionofRadiantEnergyIncidentonPeople(0.04));
  }

  ZoneHVACHighTemperatureRadiant::ZoneHVACHighTemperatureRadiant(std::shared_ptr<detail::ZoneHVACHighTemperatureRadiant_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACHighTemperatureRadiant::iddObjectType() {
    return IddObjectType::ZoneHVAC_HighTemperatureRadiant;
  }

  std::vector<std::string> ZoneHVACHighTemperatureRadiant::fuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneHVAC_HighTemperatureRadiantFields::FuelType);
  }

  std::vector<std::string> ZoneHVACHighTemperatureRadiant::temperatureControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneHVAC_HighTemperatureRadiantFields::TemperatureControlType);
  }

  // -- MaximumPowerInput ---------------------------------------------------
  boost::optional<double> ZoneHVACHighTemperatureRadiant::maximumPowerInput() const {
    return getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->maximumPowerInput();
  }

  bool ZoneHVACHighTemperatureRadiant::isMaximumPowerInputAutosized() const {
    return getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->isMaximumPowerInputAutosized();
  }

  bool ZoneHVACHighTemperatureRadiant::setMaximumPowerInput(double maximumPowerInput) {
    return getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->setMaximumPowerInput(maximumPowerInput);
  }

  void ZoneHVACHighTemperatureRadiant::autosizeMaximumPowerInput() {
    getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->autosizeMaximumPowerInput();
  }

  namespace detail {

    boost::optional<double> ZoneHVACHighTemperatureRadiant_Impl::maximumPowerInput() const {
      return getDouble(ZoneHVAC_HighTemperatureRadiantFields::HeatingDesignCapacity, true);
    }

    bool ZoneHVACHighTemperatureRadiant_Impl::isMaximumPowerInputAutosized() const {
      if (auto value = getString(ZoneHVAC_HighTemperatureRadiantFields::HeatingDesignCapacity, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACHighTemperatureRadiant_Impl::setMaximumPowerInput(double maximumPowerInput) {
      const bool result = setDouble(ZoneHVAC_HighTemperatureRadiantFields::HeatingDesignCapacity, maximumPowerInput);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACHighTemperatureRadiant_Impl::autosizeMaximumPowerInput() {
      OS_ASSERT(setString(ZoneHVAC_HighTemperatureRadiantFields::HeatingDesignCapacity, "autosize"));
    }

  }  // namespace detail

  // -- FuelType ------------------------------------------------------------
  std::string ZoneHVACHighTemperatureRadiant::fuelType() const {
    return getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->fuelType();
  }

  bool ZoneHVACHighTemperatureRadiant::isFuelTypeDefaulted() const {
    return getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->isFuelTypeDefaulted();
  }

  bool ZoneHVACHighTemperatureRadiant::setFuelType(const std::string& fuelType) {
    return getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->setFuelType(fuelType);
  }

  void ZoneHVACHighTemperatureRadiant::resetFuelType() {
    getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->resetFuelType();
  }

  namespace detail {

    std::string ZoneHVACHighTemperatureRadiant_Impl::fuelType() const {
      auto value = getString(ZoneHVAC_HighTemperatureRadiantFields::FuelType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACHighTemperatureRadiant_Impl::isFuelTypeDefaulted() const {
      return isEmpty(ZoneHVAC_HighTemperatureRadiantFields::FuelType);
    }

    bool ZoneHVACHighTemperatureRadiant_Impl::setFuelType(const std::string& fuelType) {
      return setString(ZoneHVAC_HighTemperatureRadiantFields::FuelType, fuelType);
    }

    void ZoneHVACHighTemperatureRadiant_Impl::resetFuelType() {
      OS_ASSERT(setString(ZoneHVAC_HighTemperatureRadiantFields::FuelType, ""));
    }

  }  // namespace detail

  // -- CombustionEfficiency ------------------------------------------------
  double ZoneHVACHighTemperatureRadiant::combustionEfficiency() const {
    return getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->combustionEfficiency();
  }

  bool ZoneHVACHighTemperatureRadiant::isCombustionEfficiencyDefaulted() const {
    return getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->isCombustionEfficiencyDefaulted();
  }

  bool ZoneHVACHighTemperatureRadiant::setCombustionEfficiency(double combustionEfficiency) {
    return getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->setCombustionEfficiency(combustionEfficiency);
  }

  void ZoneHVACHighTemperatureRadiant::resetCombustionEfficiency() {
    getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->resetCombustionEfficiency();
  }

  namespace detail {

    double ZoneHVACHighTemperatureRadiant_Impl::combustionEfficiency() const {
      auto value = getDouble(ZoneHVAC_HighTemperatureRadiantFields::CombustionEfficiency, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACHighTemperatureRadiant_Impl::isCombustionEfficiencyDefaulted() const {
      return isEmpty(ZoneHVAC_HighTemperatureRadiantFields::CombustionEfficiency);
    }

    bool ZoneHVACHighTemperatureRadiant_Impl::setCombustionEfficiency(double combustionEfficiency) {
      const bool result = setDouble(ZoneHVAC_HighTemperatureRadiantFields::CombustionEfficiency, combustionEfficiency);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACHighTemperatureRadiant_Impl::resetCombustionEfficiency() {
      OS_ASSERT(setString(ZoneHVAC_HighTemperatureRadiantFields::CombustionEfficiency, ""));
    }

  }  // namespace detail

  // -- Fraction of Input Converted to Radiant Energy -----------------------
  double ZoneHVACHighTemperatureRadiant::fractionofInputConvertedtoRadiantEnergy() const {
    return getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->fractionofInputConvertedtoRadiantEnergy();
  }

  bool ZoneHVACHighTemperatureRadiant::isFractionofInputConvertedtoRadiantEnergyDefaulted() const {
    return getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->isFractionofInputConvertedtoRadiantEnergyDefaulted();
  }

  bool ZoneHVACHighTemperatureRadiant::setFractionofInputConvertedtoRadiantEnergy(double fractionofInputConvertedtoRadiantEnergy) {
    return getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->setFractionofInputConvertedtoRadiantEnergy(
      fractionofInputConvertedtoRadiantEnergy);
  }

  void ZoneHVACHighTemperatureRadiant::resetFractionofInputConvertedtoRadiantEnergy() {
    getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->resetFractionofInputConvertedtoRadiantEnergy();
  }

  namespace detail {

    double ZoneHVACHighTemperatureRadiant_Impl::fractionofInputConvertedtoRadiantEnergy() const {
      auto value = getDouble(ZoneHVAC_HighTemperatureRadiantFields::FractionofInputConvertedtoRadiantEnergy, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACHighTemperatureRadiant_Impl::isFractionofInputConvertedtoRadiantEnergyDefaulted() const {
      return isEmpty(ZoneHVAC_HighTemperatureRadiantFields::FractionofInputConvertedtoRadiantEnergy);
    }

    bool ZoneHVACHighTemperatureRadiant_Impl::setFractionofInputConvertedtoRadiantEnergy(double fractionofInputConvertedtoRadiantEnergy) {
      const bool result =
        setDouble(ZoneHVAC_HighTemperatureRadiantFields::FractionofInputConvertedtoRadiantEnergy, fractionofInputConvertedtoRadiantEnergy);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACHighTemperatureRadiant_Impl::resetFractionofInputConvertedtoRadiantEnergy() {
      OS_ASSERT(setString(ZoneHVAC_HighTemperatureRadiantFields::FractionofInputConvertedtoRadiantEnergy, ""));
    }

  }  // namespace detail

  // -- Fraction of Input Converted to Latent Energy -----------------------
  double ZoneHVACHighTemperatureRadiant::fractionofInputConvertedtoLatentEnergy() const {
    return getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->fractionofInputConvertedtoLatentEnergy();
  }

  bool ZoneHVACHighTemperatureRadiant::isFractionofInputConvertedtoLatentEnergyDefaulted() const {
    return getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->isFractionofInputConvertedtoLatentEnergyDefaulted();
  }

  bool ZoneHVACHighTemperatureRadiant::setFractionofInputConvertedtoLatentEnergy(double fractionofInputConvertedtoLatentEnergy) {
    return getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->setFractionofInputConvertedtoLatentEnergy(fractionofInputConvertedtoLatentEnergy);
  }

  void ZoneHVACHighTemperatureRadiant::resetFractionofInputConvertedtoLatentEnergy() {
    getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->resetFractionofInputConvertedtoLatentEnergy();
  }

  namespace detail {

    double ZoneHVACHighTemperatureRadiant_Impl::fractionofInputConvertedtoLatentEnergy() const {
      auto value = getDouble(ZoneHVAC_HighTemperatureRadiantFields::FractionofInputConvertedtoLatentEnergy, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACHighTemperatureRadiant_Impl::isFractionofInputConvertedtoLatentEnergyDefaulted() const {
      return isEmpty(ZoneHVAC_HighTemperatureRadiantFields::FractionofInputConvertedtoLatentEnergy);
    }

    bool ZoneHVACHighTemperatureRadiant_Impl::setFractionofInputConvertedtoLatentEnergy(double fractionofInputConvertedtoLatentEnergy) {
      const bool result =
        setDouble(ZoneHVAC_HighTemperatureRadiantFields::FractionofInputConvertedtoLatentEnergy, fractionofInputConvertedtoLatentEnergy);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACHighTemperatureRadiant_Impl::resetFractionofInputConvertedtoLatentEnergy() {
      OS_ASSERT(setString(ZoneHVAC_HighTemperatureRadiantFields::FractionofInputConvertedtoLatentEnergy, ""));
    }

  }  // namespace detail

  // -- Fraction of Input that is Lost ------------------------------------
  double ZoneHVACHighTemperatureRadiant::fractionofInputthatIsLost() const {
    return getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->fractionofInputthatIsLost();
  }

  bool ZoneHVACHighTemperatureRadiant::isFractionofInputthatIsLostDefaulted() const {
    return getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->isFractionofInputthatIsLostDefaulted();
  }

  bool ZoneHVACHighTemperatureRadiant::setFractionofInputthatIsLost(double fractionofInputthatIsLost) {
    return getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->setFractionofInputthatIsLost(fractionofInputthatIsLost);
  }

  void ZoneHVACHighTemperatureRadiant::resetFractionofInputthatIsLost() {
    getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->resetFractionofInputthatIsLost();
  }

  namespace detail {

    double ZoneHVACHighTemperatureRadiant_Impl::fractionofInputthatIsLost() const {
      auto value = getDouble(ZoneHVAC_HighTemperatureRadiantFields::FractionofInputthatIsLost, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACHighTemperatureRadiant_Impl::isFractionofInputthatIsLostDefaulted() const {
      return isEmpty(ZoneHVAC_HighTemperatureRadiantFields::FractionofInputthatIsLost);
    }

    bool ZoneHVACHighTemperatureRadiant_Impl::setFractionofInputthatIsLost(double fractionofInputthatIsLost) {
      const bool result = setDouble(ZoneHVAC_HighTemperatureRadiantFields::FractionofInputthatIsLost, fractionofInputthatIsLost);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACHighTemperatureRadiant_Impl::resetFractionofInputthatIsLost() {
      OS_ASSERT(setString(ZoneHVAC_HighTemperatureRadiantFields::FractionofInputthatIsLost, ""));
    }

  }  // namespace detail

  // -- Temperature Control Type -------------------------------------------
  std::string ZoneHVACHighTemperatureRadiant::temperatureControlType() const {
    return getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->temperatureControlType();
  }

  bool ZoneHVACHighTemperatureRadiant::isTemperatureControlTypeDefaulted() const {
    return getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->isTemperatureControlTypeDefaulted();
  }

  bool ZoneHVACHighTemperatureRadiant::setTemperatureControlType(const std::string& temperatureControlType) {
    return getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->setTemperatureControlType(temperatureControlType);
  }

  void ZoneHVACHighTemperatureRadiant::resetTemperatureControlType() {
    getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->resetTemperatureControlType();
  }

  namespace detail {

    std::string ZoneHVACHighTemperatureRadiant_Impl::temperatureControlType() const {
      auto value = getString(ZoneHVAC_HighTemperatureRadiantFields::TemperatureControlType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACHighTemperatureRadiant_Impl::isTemperatureControlTypeDefaulted() const {
      return isEmpty(ZoneHVAC_HighTemperatureRadiantFields::TemperatureControlType);
    }

    bool ZoneHVACHighTemperatureRadiant_Impl::setTemperatureControlType(const std::string& temperatureControlType) {
      return setString(ZoneHVAC_HighTemperatureRadiantFields::TemperatureControlType, temperatureControlType);
    }

    void ZoneHVACHighTemperatureRadiant_Impl::resetTemperatureControlType() {
      OS_ASSERT(setString(ZoneHVAC_HighTemperatureRadiantFields::TemperatureControlType, ""));
    }

  }  // namespace detail

  // -- Heating Throttling Range ------------------------------------------
  double ZoneHVACHighTemperatureRadiant::heatingThrottlingRange() const {
    return getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->heatingThrottlingRange();
  }

  bool ZoneHVACHighTemperatureRadiant::isHeatingThrottlingRangeDefaulted() const {
    return getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->isHeatingThrottlingRangeDefaulted();
  }

  bool ZoneHVACHighTemperatureRadiant::setHeatingThrottlingRange(double heatingThrottlingRange) {
    return getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->setHeatingThrottlingRange(heatingThrottlingRange);
  }

  void ZoneHVACHighTemperatureRadiant::resetHeatingThrottlingRange() {
    getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->resetHeatingThrottlingRange();
  }

  namespace detail {

    double ZoneHVACHighTemperatureRadiant_Impl::heatingThrottlingRange() const {
      auto value = getDouble(ZoneHVAC_HighTemperatureRadiantFields::HeatingThrottlingRange, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACHighTemperatureRadiant_Impl::isHeatingThrottlingRangeDefaulted() const {
      return isEmpty(ZoneHVAC_HighTemperatureRadiantFields::HeatingThrottlingRange);
    }

    bool ZoneHVACHighTemperatureRadiant_Impl::setHeatingThrottlingRange(double heatingThrottlingRange) {
      const bool result = setDouble(ZoneHVAC_HighTemperatureRadiantFields::HeatingThrottlingRange, heatingThrottlingRange);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACHighTemperatureRadiant_Impl::resetHeatingThrottlingRange() {
      OS_ASSERT(setString(ZoneHVAC_HighTemperatureRadiantFields::HeatingThrottlingRange, ""));
    }

  }  // namespace detail

  // -- Fraction of Radiant Energy Incident on People ----------------------
  double ZoneHVACHighTemperatureRadiant::fractionofRadiantEnergyIncidentonPeople() const {
    return getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->fractionofRadiantEnergyIncidentonPeople();
  }

  bool ZoneHVACHighTemperatureRadiant::setFractionofRadiantEnergyIncidentonPeople(double fractionofRadiantEnergyIncidentonPeople) {
    return getImpl<detail::ZoneHVACHighTemperatureRadiant_Impl>()->setFractionofRadiantEnergyIncidentonPeople(
      fractionofRadiantEnergyIncidentonPeople);
  }

  namespace detail {

    double ZoneHVACHighTemperatureRadiant_Impl::fractionofRadiantEnergyIncidentonPeople() const {
      auto value = getDouble(ZoneHVAC_HighTemperatureRadiantFields::FractionofRadiantEnergyIncidentonPeople, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACHighTemperatureRadiant_Impl::setFractionofRadiantEnergyIncidentonPeople(double fractionofRadiantEnergyIncidentonPeople) {
      const bool result =
        setDouble(ZoneHVAC_HighTemperatureRadiantFields::FractionofRadiantEnergyIncidentonPeople, fractionofRadiantEnergyIncidentonPeople);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
