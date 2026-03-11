/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/ThermalStorageIceDetailed.hpp"
#include "StraightComponent/ThermalStorageIceDetailed_Impl.hpp"

#include "Model.hpp"

#include <memory>
#include <utility>

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ThermalStorage_Ice_Detailed_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ThermalStorageIceDetailed::ThermalStorageIceDetailed(const Model& model) : StraightComponent(iddObjectType(), model) {}

  ThermalStorageIceDetailed::ThermalStorageIceDetailed(std::shared_ptr<detail::ThermalStorageIceDetailed_Impl> impl)
    : StraightComponent(std::static_pointer_cast<detail::StraightComponent_Impl>(std::move(impl))) {}

  IddObjectType ThermalStorageIceDetailed::iddObjectType() {
    return IddObjectType::ThermalStorage_Ice_Detailed;
  }

  std::vector<std::string> ThermalStorageIceDetailed::dischargingCurveVariableSpecificationsValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ThermalStorage_Ice_DetailedFields::DischargingCurveVariableSpecifications);
  }

  std::vector<std::string> ThermalStorageIceDetailed::chargingCurveVariableSpecificationsValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ThermalStorage_Ice_DetailedFields::ChargingCurveVariableSpecifications);
  }

  std::vector<std::string> ThermalStorageIceDetailed::thawProcessIndicatorValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ThermalStorage_Ice_DetailedFields::ThawProcessIndicator);
  }

  double ThermalStorageIceDetailed::capacity() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->capacity();
  }

  bool ThermalStorageIceDetailed::setCapacity(double capacity) {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->setCapacity(capacity);
  }

  bool ThermalStorageIceDetailed::isCapacityAutosized() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->isCapacityAutosized();
  }

  void ThermalStorageIceDetailed::autosizeCapacity() {
    getImpl<detail::ThermalStorageIceDetailed_Impl>()->autosizeCapacity();
  }

  std::string ThermalStorageIceDetailed::dischargingCurveVariableSpecifications() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->dischargingCurveVariableSpecifications();
  }

  bool ThermalStorageIceDetailed::setDischargingCurveVariableSpecifications(const std::string& dischargingCurveVariableSpecifications) {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->setDischargingCurveVariableSpecifications(dischargingCurveVariableSpecifications);
  }

  std::string ThermalStorageIceDetailed::chargingCurveVariableSpecifications() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->chargingCurveVariableSpecifications();
  }

  bool ThermalStorageIceDetailed::setChargingCurveVariableSpecifications(const std::string& chargingCurveVariableSpecifications) {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->setChargingCurveVariableSpecifications(chargingCurveVariableSpecifications);
  }

  boost::optional<double> ThermalStorageIceDetailed::timestepoftheCurveData() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->timestepoftheCurveData();
  }

  bool ThermalStorageIceDetailed::setTimestepoftheCurveData(double timestepoftheCurveData) {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->setTimestepoftheCurveData(timestepoftheCurveData);
  }

  void ThermalStorageIceDetailed::resetTimestepoftheCurveData() {
    getImpl<detail::ThermalStorageIceDetailed_Impl>()->resetTimestepoftheCurveData();
  }

  boost::optional<double> ThermalStorageIceDetailed::parasiticElectricLoadDuringDischarging() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->parasiticElectricLoadDuringDischarging();
  }

  bool ThermalStorageIceDetailed::setParasiticElectricLoadDuringDischarging(double parasiticElectricLoadDuringDischarging) {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->setParasiticElectricLoadDuringDischarging(parasiticElectricLoadDuringDischarging);
  }

  void ThermalStorageIceDetailed::resetParasiticElectricLoadDuringDischarging() {
    getImpl<detail::ThermalStorageIceDetailed_Impl>()->resetParasiticElectricLoadDuringDischarging();
  }

  boost::optional<double> ThermalStorageIceDetailed::parasiticElectricLoadDuringCharging() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->parasiticElectricLoadDuringCharging();
  }

  bool ThermalStorageIceDetailed::setParasiticElectricLoadDuringCharging(double parasiticElectricLoadDuringCharging) {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->setParasiticElectricLoadDuringCharging(parasiticElectricLoadDuringCharging);
  }

  void ThermalStorageIceDetailed::resetParasiticElectricLoadDuringCharging() {
    getImpl<detail::ThermalStorageIceDetailed_Impl>()->resetParasiticElectricLoadDuringCharging();
  }

  boost::optional<double> ThermalStorageIceDetailed::tankLossCoefficient() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->tankLossCoefficient();
  }

  bool ThermalStorageIceDetailed::setTankLossCoefficient(double tankLossCoefficient) {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->setTankLossCoefficient(tankLossCoefficient);
  }

  void ThermalStorageIceDetailed::resetTankLossCoefficient() {
    getImpl<detail::ThermalStorageIceDetailed_Impl>()->resetTankLossCoefficient();
  }

  double ThermalStorageIceDetailed::freezingTemperatureofStorageMedium() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->freezingTemperatureofStorageMedium();
  }

  bool ThermalStorageIceDetailed::setFreezingTemperatureofStorageMedium(double freezingTemperatureofStorageMedium) {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->setFreezingTemperatureofStorageMedium(freezingTemperatureofStorageMedium);
  }

  bool ThermalStorageIceDetailed::isFreezingTemperatureofStorageMediumDefaulted() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->isFreezingTemperatureofStorageMediumDefaulted();
  }

  void ThermalStorageIceDetailed::resetFreezingTemperatureofStorageMedium() {
    getImpl<detail::ThermalStorageIceDetailed_Impl>()->resetFreezingTemperatureofStorageMedium();
  }

  std::string ThermalStorageIceDetailed::thawProcessIndicator() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->thawProcessIndicator();
  }

  bool ThermalStorageIceDetailed::setThawProcessIndicator(const std::string& thawProcessIndicator) {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->setThawProcessIndicator(thawProcessIndicator);
  }

  bool ThermalStorageIceDetailed::isThawProcessIndicatorDefaulted() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->isThawProcessIndicatorDefaulted();
  }

  void ThermalStorageIceDetailed::resetThawProcessIndicator() {
    getImpl<detail::ThermalStorageIceDetailed_Impl>()->resetThawProcessIndicator();
  }

  namespace detail {

    unsigned ThermalStorageIceDetailed_Impl::inletPort() const {
      return openstudio::ThermalStorage_Ice_DetailedFields::InletNodeName;
    }

    unsigned ThermalStorageIceDetailed_Impl::outletPort() const {
      return openstudio::ThermalStorage_Ice_DetailedFields::OutletNodeName;
    }

    double ThermalStorageIceDetailed_Impl::capacity() const {
      auto value = getDouble(openstudio::ThermalStorage_Ice_DetailedFields::Capacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageIceDetailed_Impl::setCapacity(double capacity) {
      return setDouble(openstudio::ThermalStorage_Ice_DetailedFields::Capacity, capacity);
    }

    bool ThermalStorageIceDetailed_Impl::isCapacityAutosized() const {
      if (auto value = getString(openstudio::ThermalStorage_Ice_DetailedFields::Capacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    void ThermalStorageIceDetailed_Impl::autosizeCapacity() {
      OS_ASSERT(setString(openstudio::ThermalStorage_Ice_DetailedFields::Capacity, "autosize"));
    }

    std::string ThermalStorageIceDetailed_Impl::dischargingCurveVariableSpecifications() const {
      auto value = getString(openstudio::ThermalStorage_Ice_DetailedFields::DischargingCurveVariableSpecifications, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageIceDetailed_Impl::setDischargingCurveVariableSpecifications(const std::string& dischargingCurveVariableSpecifications) {
      return setString(openstudio::ThermalStorage_Ice_DetailedFields::DischargingCurveVariableSpecifications, dischargingCurveVariableSpecifications);
    }

    std::string ThermalStorageIceDetailed_Impl::chargingCurveVariableSpecifications() const {
      auto value = getString(openstudio::ThermalStorage_Ice_DetailedFields::ChargingCurveVariableSpecifications, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageIceDetailed_Impl::setChargingCurveVariableSpecifications(const std::string& chargingCurveVariableSpecifications) {
      return setString(openstudio::ThermalStorage_Ice_DetailedFields::ChargingCurveVariableSpecifications, chargingCurveVariableSpecifications);
    }

    boost::optional<double> ThermalStorageIceDetailed_Impl::timestepoftheCurveData() const {
      return getDouble(openstudio::ThermalStorage_Ice_DetailedFields::TimestepoftheCurveData, true);
    }

    bool ThermalStorageIceDetailed_Impl::setTimestepoftheCurveData(double timestepoftheCurveData) {
      return setDouble(openstudio::ThermalStorage_Ice_DetailedFields::TimestepoftheCurveData, timestepoftheCurveData);
    }

    void ThermalStorageIceDetailed_Impl::resetTimestepoftheCurveData() {
      OS_ASSERT(setString(openstudio::ThermalStorage_Ice_DetailedFields::TimestepoftheCurveData, ""));
    }

    boost::optional<double> ThermalStorageIceDetailed_Impl::parasiticElectricLoadDuringDischarging() const {
      return getDouble(openstudio::ThermalStorage_Ice_DetailedFields::ParasiticElectricLoadDuringDischarging, true);
    }

    bool ThermalStorageIceDetailed_Impl::setParasiticElectricLoadDuringDischarging(double parasiticElectricLoadDuringDischarging) {
      return setDouble(openstudio::ThermalStorage_Ice_DetailedFields::ParasiticElectricLoadDuringDischarging, parasiticElectricLoadDuringDischarging);
    }

    void ThermalStorageIceDetailed_Impl::resetParasiticElectricLoadDuringDischarging() {
      OS_ASSERT(setString(openstudio::ThermalStorage_Ice_DetailedFields::ParasiticElectricLoadDuringDischarging, ""));
    }

    boost::optional<double> ThermalStorageIceDetailed_Impl::parasiticElectricLoadDuringCharging() const {
      return getDouble(openstudio::ThermalStorage_Ice_DetailedFields::ParasiticElectricLoadDuringCharging, true);
    }

    bool ThermalStorageIceDetailed_Impl::setParasiticElectricLoadDuringCharging(double parasiticElectricLoadDuringCharging) {
      return setDouble(openstudio::ThermalStorage_Ice_DetailedFields::ParasiticElectricLoadDuringCharging, parasiticElectricLoadDuringCharging);
    }

    void ThermalStorageIceDetailed_Impl::resetParasiticElectricLoadDuringCharging() {
      OS_ASSERT(setString(openstudio::ThermalStorage_Ice_DetailedFields::ParasiticElectricLoadDuringCharging, ""));
    }

    boost::optional<double> ThermalStorageIceDetailed_Impl::tankLossCoefficient() const {
      return getDouble(openstudio::ThermalStorage_Ice_DetailedFields::TankLossCoefficient, true);
    }

    bool ThermalStorageIceDetailed_Impl::setTankLossCoefficient(double tankLossCoefficient) {
      return setDouble(openstudio::ThermalStorage_Ice_DetailedFields::TankLossCoefficient, tankLossCoefficient);
    }

    void ThermalStorageIceDetailed_Impl::resetTankLossCoefficient() {
      OS_ASSERT(setString(openstudio::ThermalStorage_Ice_DetailedFields::TankLossCoefficient, ""));
    }

    double ThermalStorageIceDetailed_Impl::freezingTemperatureofStorageMedium() const {
      auto value = getDouble(openstudio::ThermalStorage_Ice_DetailedFields::FreezingTemperatureofStorageMedium, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageIceDetailed_Impl::setFreezingTemperatureofStorageMedium(double freezingTemperatureofStorageMedium) {
      return setDouble(openstudio::ThermalStorage_Ice_DetailedFields::FreezingTemperatureofStorageMedium, freezingTemperatureofStorageMedium);
    }

    bool ThermalStorageIceDetailed_Impl::isFreezingTemperatureofStorageMediumDefaulted() const {
      return isEmpty(openstudio::ThermalStorage_Ice_DetailedFields::FreezingTemperatureofStorageMedium);
    }

    void ThermalStorageIceDetailed_Impl::resetFreezingTemperatureofStorageMedium() {
      OS_ASSERT(setString(openstudio::ThermalStorage_Ice_DetailedFields::FreezingTemperatureofStorageMedium, ""));
    }

    std::string ThermalStorageIceDetailed_Impl::thawProcessIndicator() const {
      auto value = getString(openstudio::ThermalStorage_Ice_DetailedFields::ThawProcessIndicator, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageIceDetailed_Impl::setThawProcessIndicator(const std::string& thawProcessIndicator) {
      return setString(openstudio::ThermalStorage_Ice_DetailedFields::ThawProcessIndicator, thawProcessIndicator);
    }

    bool ThermalStorageIceDetailed_Impl::isThawProcessIndicatorDefaulted() const {
      return isEmpty(openstudio::ThermalStorage_Ice_DetailedFields::ThawProcessIndicator);
    }

    void ThermalStorageIceDetailed_Impl::resetThawProcessIndicator() {
      OS_ASSERT(setString(openstudio::ThermalStorage_Ice_DetailedFields::ThawProcessIndicator, ""));
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
