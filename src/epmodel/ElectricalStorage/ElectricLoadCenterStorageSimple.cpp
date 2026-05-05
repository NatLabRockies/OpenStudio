/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ElectricalStorage/ElectricLoadCenterStorageSimple.hpp"
#include "ElectricalStorage/ElectricLoadCenterStorageSimple_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ElectricLoadCenter_Storage_Simple_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ElectricLoadCenterStorageSimple::ElectricLoadCenterStorageSimple(const Model& model)
    : ModelObject(ElectricLoadCenterStorageSimple::iddObjectType(), model) {
    OS_ASSERT(setNominalEnergeticEfficiencyforCharging(0.8));
    OS_ASSERT(setNominalDischargingEnergeticEfficiency(0.8));
    OS_ASSERT(setMaximumStorageCapacity(1.0E13));
    OS_ASSERT(setMaximumPowerforDischarging(1.0E6));
    OS_ASSERT(setMaximumPowerforCharging(1.0E6));
  }

  ElectricLoadCenterStorageSimple::ElectricLoadCenterStorageSimple(std::shared_ptr<detail::ElectricLoadCenterStorageSimple_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ElectricLoadCenterStorageSimple::iddObjectType() {
    return IddObjectType::ElectricLoadCenter_Storage_Simple;
  }

  double ElectricLoadCenterStorageSimple::radiativeFractionforZoneHeatGains() const {
    return getImpl<detail::ElectricLoadCenterStorageSimple_Impl>()->radiativeFractionforZoneHeatGains();
  }

  bool ElectricLoadCenterStorageSimple::isRadiativeFractionforZoneHeatGainsDefaulted() const {
    return getImpl<detail::ElectricLoadCenterStorageSimple_Impl>()->isRadiativeFractionforZoneHeatGainsDefaulted();
  }

  bool ElectricLoadCenterStorageSimple::setRadiativeFractionforZoneHeatGains(double radiativeFractionforZoneHeatGains) {
    return getImpl<detail::ElectricLoadCenterStorageSimple_Impl>()->setRadiativeFractionforZoneHeatGains(radiativeFractionforZoneHeatGains);
  }

  void ElectricLoadCenterStorageSimple::resetRadiativeFractionforZoneHeatGains() {
    getImpl<detail::ElectricLoadCenterStorageSimple_Impl>()->resetRadiativeFractionforZoneHeatGains();
  }

  double ElectricLoadCenterStorageSimple::nominalEnergeticEfficiencyforCharging() const {
    return getImpl<detail::ElectricLoadCenterStorageSimple_Impl>()->nominalEnergeticEfficiencyforCharging();
  }

  bool ElectricLoadCenterStorageSimple::isNominalEnergeticEfficiencyforChargingDefaulted() const {
    return getImpl<detail::ElectricLoadCenterStorageSimple_Impl>()->isNominalEnergeticEfficiencyforChargingDefaulted();
  }

  bool ElectricLoadCenterStorageSimple::setNominalEnergeticEfficiencyforCharging(double nominalEnergeticEfficiencyforCharging) {
    return getImpl<detail::ElectricLoadCenterStorageSimple_Impl>()->setNominalEnergeticEfficiencyforCharging(nominalEnergeticEfficiencyforCharging);
  }

  void ElectricLoadCenterStorageSimple::resetNominalEnergeticEfficiencyforCharging() {
    getImpl<detail::ElectricLoadCenterStorageSimple_Impl>()->resetNominalEnergeticEfficiencyforCharging();
  }

  double ElectricLoadCenterStorageSimple::nominalDischargingEnergeticEfficiency() const {
    return getImpl<detail::ElectricLoadCenterStorageSimple_Impl>()->nominalDischargingEnergeticEfficiency();
  }

  bool ElectricLoadCenterStorageSimple::isNominalDischargingEnergeticEfficiencyDefaulted() const {
    return getImpl<detail::ElectricLoadCenterStorageSimple_Impl>()->isNominalDischargingEnergeticEfficiencyDefaulted();
  }

  bool ElectricLoadCenterStorageSimple::setNominalDischargingEnergeticEfficiency(double nominalDischargingEnergeticEfficiency) {
    return getImpl<detail::ElectricLoadCenterStorageSimple_Impl>()->setNominalDischargingEnergeticEfficiency(nominalDischargingEnergeticEfficiency);
  }

  void ElectricLoadCenterStorageSimple::resetNominalDischargingEnergeticEfficiency() {
    getImpl<detail::ElectricLoadCenterStorageSimple_Impl>()->resetNominalDischargingEnergeticEfficiency();
  }

  double ElectricLoadCenterStorageSimple::maximumStorageCapacity() const {
    return getImpl<detail::ElectricLoadCenterStorageSimple_Impl>()->maximumStorageCapacity();
  }

  bool ElectricLoadCenterStorageSimple::setMaximumStorageCapacity(double maximumStorageCapacity) {
    return getImpl<detail::ElectricLoadCenterStorageSimple_Impl>()->setMaximumStorageCapacity(maximumStorageCapacity);
  }

  double ElectricLoadCenterStorageSimple::maximumPowerforDischarging() const {
    return getImpl<detail::ElectricLoadCenterStorageSimple_Impl>()->maximumPowerforDischarging();
  }

  bool ElectricLoadCenterStorageSimple::setMaximumPowerforDischarging(double maximumPowerforDischarging) {
    return getImpl<detail::ElectricLoadCenterStorageSimple_Impl>()->setMaximumPowerforDischarging(maximumPowerforDischarging);
  }

  double ElectricLoadCenterStorageSimple::maximumPowerforCharging() const {
    return getImpl<detail::ElectricLoadCenterStorageSimple_Impl>()->maximumPowerforCharging();
  }

  bool ElectricLoadCenterStorageSimple::setMaximumPowerforCharging(double maximumPowerforCharging) {
    return getImpl<detail::ElectricLoadCenterStorageSimple_Impl>()->setMaximumPowerforCharging(maximumPowerforCharging);
  }

  double ElectricLoadCenterStorageSimple::initialStateofCharge() const {
    return getImpl<detail::ElectricLoadCenterStorageSimple_Impl>()->initialStateofCharge();
  }

  bool ElectricLoadCenterStorageSimple::isInitialStateofChargeDefaulted() const {
    return getImpl<detail::ElectricLoadCenterStorageSimple_Impl>()->isInitialStateofChargeDefaulted();
  }

  bool ElectricLoadCenterStorageSimple::setInitialStateofCharge(double initialStateofCharge) {
    return getImpl<detail::ElectricLoadCenterStorageSimple_Impl>()->setInitialStateofCharge(initialStateofCharge);
  }

  void ElectricLoadCenterStorageSimple::resetInitialStateofCharge() {
    getImpl<detail::ElectricLoadCenterStorageSimple_Impl>()->resetInitialStateofCharge();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double ElectricLoadCenterStorageSimple_Impl::radiativeFractionforZoneHeatGains() const {
      if (const auto value = getDouble(openstudio::ElectricLoadCenter_Storage_SimpleFields::RadiativeFractionforZoneHeatGains, true)) {
        return *value;
      }
      return 0.0;
    }

    bool ElectricLoadCenterStorageSimple_Impl::isRadiativeFractionforZoneHeatGainsDefaulted() const {
      return isEmpty(openstudio::ElectricLoadCenter_Storage_SimpleFields::RadiativeFractionforZoneHeatGains);
    }

    bool ElectricLoadCenterStorageSimple_Impl::setRadiativeFractionforZoneHeatGains(double radiativeFractionforZoneHeatGains) {
      return setDouble(openstudio::ElectricLoadCenter_Storage_SimpleFields::RadiativeFractionforZoneHeatGains, radiativeFractionforZoneHeatGains);
    }

    void ElectricLoadCenterStorageSimple_Impl::resetRadiativeFractionforZoneHeatGains() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Storage_SimpleFields::RadiativeFractionforZoneHeatGains, ""));
    }

    double ElectricLoadCenterStorageSimple_Impl::nominalEnergeticEfficiencyforCharging() const {
      const auto value = getDouble(openstudio::ElectricLoadCenter_Storage_SimpleFields::NominalEnergeticEfficiencyforCharging, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ElectricLoadCenterStorageSimple_Impl::isNominalEnergeticEfficiencyforChargingDefaulted() const {
      return isEmpty(openstudio::ElectricLoadCenter_Storage_SimpleFields::NominalEnergeticEfficiencyforCharging);
    }

    bool ElectricLoadCenterStorageSimple_Impl::setNominalEnergeticEfficiencyforCharging(double nominalEnergeticEfficiencyforCharging) {
      return setDouble(openstudio::ElectricLoadCenter_Storage_SimpleFields::NominalEnergeticEfficiencyforCharging,
                       nominalEnergeticEfficiencyforCharging);
    }

    void ElectricLoadCenterStorageSimple_Impl::resetNominalEnergeticEfficiencyforCharging() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Storage_SimpleFields::NominalEnergeticEfficiencyforCharging, ""));
    }

    double ElectricLoadCenterStorageSimple_Impl::nominalDischargingEnergeticEfficiency() const {
      const auto value = getDouble(openstudio::ElectricLoadCenter_Storage_SimpleFields::NominalDischargingEnergeticEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ElectricLoadCenterStorageSimple_Impl::isNominalDischargingEnergeticEfficiencyDefaulted() const {
      return isEmpty(openstudio::ElectricLoadCenter_Storage_SimpleFields::NominalDischargingEnergeticEfficiency);
    }

    bool ElectricLoadCenterStorageSimple_Impl::setNominalDischargingEnergeticEfficiency(double nominalDischargingEnergeticEfficiency) {
      return setDouble(openstudio::ElectricLoadCenter_Storage_SimpleFields::NominalDischargingEnergeticEfficiency,
                       nominalDischargingEnergeticEfficiency);
    }

    void ElectricLoadCenterStorageSimple_Impl::resetNominalDischargingEnergeticEfficiency() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Storage_SimpleFields::NominalDischargingEnergeticEfficiency, ""));
    }

    double ElectricLoadCenterStorageSimple_Impl::maximumStorageCapacity() const {
      const auto value = getDouble(openstudio::ElectricLoadCenter_Storage_SimpleFields::MaximumStorageCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ElectricLoadCenterStorageSimple_Impl::setMaximumStorageCapacity(double maximumStorageCapacity) {
      return setDouble(openstudio::ElectricLoadCenter_Storage_SimpleFields::MaximumStorageCapacity, maximumStorageCapacity);
    }

    double ElectricLoadCenterStorageSimple_Impl::maximumPowerforDischarging() const {
      const auto value = getDouble(openstudio::ElectricLoadCenter_Storage_SimpleFields::MaximumPowerforDischarging, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ElectricLoadCenterStorageSimple_Impl::setMaximumPowerforDischarging(double maximumPowerforDischarging) {
      return setDouble(openstudio::ElectricLoadCenter_Storage_SimpleFields::MaximumPowerforDischarging, maximumPowerforDischarging);
    }

    double ElectricLoadCenterStorageSimple_Impl::maximumPowerforCharging() const {
      const auto value = getDouble(openstudio::ElectricLoadCenter_Storage_SimpleFields::MaximumPowerforCharging, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ElectricLoadCenterStorageSimple_Impl::setMaximumPowerforCharging(double maximumPowerforCharging) {
      return setDouble(openstudio::ElectricLoadCenter_Storage_SimpleFields::MaximumPowerforCharging, maximumPowerforCharging);
    }

    double ElectricLoadCenterStorageSimple_Impl::initialStateofCharge() const {
      if (const auto value = getDouble(openstudio::ElectricLoadCenter_Storage_SimpleFields::InitialStateofCharge, true)) {
        return *value;
      }
      return maximumStorageCapacity() / 2.0;
    }

    bool ElectricLoadCenterStorageSimple_Impl::isInitialStateofChargeDefaulted() const {
      return isEmpty(openstudio::ElectricLoadCenter_Storage_SimpleFields::InitialStateofCharge);
    }

    bool ElectricLoadCenterStorageSimple_Impl::setInitialStateofCharge(double initialStateofCharge) {
      return setDouble(openstudio::ElectricLoadCenter_Storage_SimpleFields::InitialStateofCharge, initialStateofCharge);
    }

    void ElectricLoadCenterStorageSimple_Impl::resetInitialStateofCharge() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Storage_SimpleFields::InitialStateofCharge, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
