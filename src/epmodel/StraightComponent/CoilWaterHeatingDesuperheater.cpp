/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilWaterHeatingDesuperheater.hpp"
#include "StraightComponent/CoilWaterHeatingDesuperheater_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Coil_WaterHeating_Desuperheater_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  CoilWaterHeatingDesuperheater::CoilWaterHeatingDesuperheater(const Model& model)
    : StraightComponent(CoilWaterHeatingDesuperheater::iddObjectType(), model) {
    bool ok = true;
    ok = setDeadBandTemperatureDifference(5.0);
    OS_ASSERT(ok);
    ok = setRatedInletWaterTemperature(50.0);
    OS_ASSERT(ok);
    ok = setRatedOutdoorAirTemperature(35.0);
    OS_ASSERT(ok);
    ok = setMaximumInletWaterTemperatureforHeatReclaim(60.0);
    OS_ASSERT(ok);
    ok = setWaterFlowRate(0.0001);
    OS_ASSERT(ok);
    ok = setWaterPumpPower(100.0);
    OS_ASSERT(ok);
    ok = setFractionofPumpHeattoWater(0.2);
    OS_ASSERT(ok);
    ok = setOnCycleParasiticElectricLoad(0.0);
    OS_ASSERT(ok);
    ok = setOffCycleParasiticElectricLoad(0.0);
    OS_ASSERT(ok);
  }

  CoilWaterHeatingDesuperheater::CoilWaterHeatingDesuperheater(std::shared_ptr<detail::CoilWaterHeatingDesuperheater_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType CoilWaterHeatingDesuperheater::iddObjectType() {
    return IddObjectType::Coil_WaterHeating_Desuperheater;
  }

  double CoilWaterHeatingDesuperheater::deadBandTemperatureDifference() const {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->deadBandTemperatureDifference();
  }

  bool CoilWaterHeatingDesuperheater::isDeadBandTemperatureDifferenceDefaulted() const {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->isDeadBandTemperatureDifferenceDefaulted();
  }

  boost::optional<double> CoilWaterHeatingDesuperheater::ratedHeatReclaimRecoveryEfficiency() const {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->ratedHeatReclaimRecoveryEfficiency();
  }

  double CoilWaterHeatingDesuperheater::ratedInletWaterTemperature() const {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->ratedInletWaterTemperature();
  }

  double CoilWaterHeatingDesuperheater::ratedOutdoorAirTemperature() const {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->ratedOutdoorAirTemperature();
  }

  double CoilWaterHeatingDesuperheater::maximumInletWaterTemperatureforHeatReclaim() const {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->maximumInletWaterTemperatureforHeatReclaim();
  }

  double CoilWaterHeatingDesuperheater::waterFlowRate() const {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->waterFlowRate();
  }

  double CoilWaterHeatingDesuperheater::waterPumpPower() const {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->waterPumpPower();
  }

  bool CoilWaterHeatingDesuperheater::isWaterPumpPowerDefaulted() const {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->isWaterPumpPowerDefaulted();
  }

  double CoilWaterHeatingDesuperheater::fractionofPumpHeattoWater() const {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->fractionofPumpHeattoWater();
  }

  bool CoilWaterHeatingDesuperheater::isFractionofPumpHeattoWaterDefaulted() const {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->isFractionofPumpHeattoWaterDefaulted();
  }

  double CoilWaterHeatingDesuperheater::onCycleParasiticElectricLoad() const {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->onCycleParasiticElectricLoad();
  }

  bool CoilWaterHeatingDesuperheater::isOnCycleParasiticElectricLoadDefaulted() const {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->isOnCycleParasiticElectricLoadDefaulted();
  }

  double CoilWaterHeatingDesuperheater::offCycleParasiticElectricLoad() const {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->offCycleParasiticElectricLoad();
  }

  bool CoilWaterHeatingDesuperheater::isOffCycleParasiticElectricLoadDefaulted() const {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->isOffCycleParasiticElectricLoadDefaulted();
  }

  bool CoilWaterHeatingDesuperheater::setDeadBandTemperatureDifference(double deadBandTemperatureDifference) {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->setDeadBandTemperatureDifference(deadBandTemperatureDifference);
  }

  void CoilWaterHeatingDesuperheater::resetDeadBandTemperatureDifference() {
    getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->resetDeadBandTemperatureDifference();
  }

  bool CoilWaterHeatingDesuperheater::setRatedHeatReclaimRecoveryEfficiency(double ratedHeatReclaimRecoveryEfficiency) {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->setRatedHeatReclaimRecoveryEfficiency(ratedHeatReclaimRecoveryEfficiency);
  }

  void CoilWaterHeatingDesuperheater::resetRatedHeatReclaimRecoveryEfficiency() {
    getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->resetRatedHeatReclaimRecoveryEfficiency();
  }

  bool CoilWaterHeatingDesuperheater::setRatedInletWaterTemperature(double ratedInletWaterTemperature) {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->setRatedInletWaterTemperature(ratedInletWaterTemperature);
  }

  bool CoilWaterHeatingDesuperheater::setRatedOutdoorAirTemperature(double ratedOutdoorAirTemperature) {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->setRatedOutdoorAirTemperature(ratedOutdoorAirTemperature);
  }

  bool CoilWaterHeatingDesuperheater::setMaximumInletWaterTemperatureforHeatReclaim(double maximumInletWaterTemperatureforHeatReclaim) {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->setMaximumInletWaterTemperatureforHeatReclaim(
      maximumInletWaterTemperatureforHeatReclaim);
  }

  bool CoilWaterHeatingDesuperheater::setWaterFlowRate(double waterFlowRate) {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->setWaterFlowRate(waterFlowRate);
  }

  bool CoilWaterHeatingDesuperheater::setWaterPumpPower(double waterPumpPower) {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->setWaterPumpPower(waterPumpPower);
  }

  void CoilWaterHeatingDesuperheater::resetWaterPumpPower() {
    getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->resetWaterPumpPower();
  }

  bool CoilWaterHeatingDesuperheater::setFractionofPumpHeattoWater(double fractionofPumpHeattoWater) {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->setFractionofPumpHeattoWater(fractionofPumpHeattoWater);
  }

  void CoilWaterHeatingDesuperheater::resetFractionofPumpHeattoWater() {
    getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->resetFractionofPumpHeattoWater();
  }

  bool CoilWaterHeatingDesuperheater::setOnCycleParasiticElectricLoad(double onCycleParasiticElectricLoad) {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->setOnCycleParasiticElectricLoad(onCycleParasiticElectricLoad);
  }

  void CoilWaterHeatingDesuperheater::resetOnCycleParasiticElectricLoad() {
    getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->resetOnCycleParasiticElectricLoad();
  }

  bool CoilWaterHeatingDesuperheater::setOffCycleParasiticElectricLoad(double offCycleParasiticElectricLoad) {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->setOffCycleParasiticElectricLoad(offCycleParasiticElectricLoad);
  }

  void CoilWaterHeatingDesuperheater::resetOffCycleParasiticElectricLoad() {
    getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->resetOffCycleParasiticElectricLoad();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned CoilWaterHeatingDesuperheater_Impl::inletPort() const {
      return openstudio::Coil_WaterHeating_DesuperheaterFields::WaterInletNodeName;
    }

    unsigned CoilWaterHeatingDesuperheater_Impl::outletPort() const {
      return openstudio::Coil_WaterHeating_DesuperheaterFields::WaterOutletNodeName;
    }

    double CoilWaterHeatingDesuperheater_Impl::deadBandTemperatureDifference() const {
      const auto value = getDouble(openstudio::Coil_WaterHeating_DesuperheaterFields::DeadBandTemperatureDifference, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingDesuperheater_Impl::isDeadBandTemperatureDifferenceDefaulted() const {
      return isEmpty(openstudio::Coil_WaterHeating_DesuperheaterFields::DeadBandTemperatureDifference);
    }

    bool CoilWaterHeatingDesuperheater_Impl::setDeadBandTemperatureDifference(double deadBandTemperatureDifference) {
      return setDouble(openstudio::Coil_WaterHeating_DesuperheaterFields::DeadBandTemperatureDifference, deadBandTemperatureDifference);
    }

    void CoilWaterHeatingDesuperheater_Impl::resetDeadBandTemperatureDifference() {
      OS_ASSERT(setString(openstudio::Coil_WaterHeating_DesuperheaterFields::DeadBandTemperatureDifference, ""));
    }

    boost::optional<double> CoilWaterHeatingDesuperheater_Impl::ratedHeatReclaimRecoveryEfficiency() const {
      return getDouble(openstudio::Coil_WaterHeating_DesuperheaterFields::RatedHeatReclaimRecoveryEfficiency, true);
    }

    bool CoilWaterHeatingDesuperheater_Impl::setRatedHeatReclaimRecoveryEfficiency(double ratedHeatReclaimRecoveryEfficiency) {
      return setDouble(openstudio::Coil_WaterHeating_DesuperheaterFields::RatedHeatReclaimRecoveryEfficiency, ratedHeatReclaimRecoveryEfficiency);
    }

    void CoilWaterHeatingDesuperheater_Impl::resetRatedHeatReclaimRecoveryEfficiency() {
      OS_ASSERT(setString(openstudio::Coil_WaterHeating_DesuperheaterFields::RatedHeatReclaimRecoveryEfficiency, ""));
    }

    double CoilWaterHeatingDesuperheater_Impl::ratedInletWaterTemperature() const {
      const auto value = getDouble(openstudio::Coil_WaterHeating_DesuperheaterFields::RatedInletWaterTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingDesuperheater_Impl::setRatedInletWaterTemperature(double ratedInletWaterTemperature) {
      const bool result = setDouble(openstudio::Coil_WaterHeating_DesuperheaterFields::RatedInletWaterTemperature, ratedInletWaterTemperature);
      OS_ASSERT(result);
      return result;
    }

    double CoilWaterHeatingDesuperheater_Impl::ratedOutdoorAirTemperature() const {
      const auto value = getDouble(openstudio::Coil_WaterHeating_DesuperheaterFields::RatedOutdoorAirTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingDesuperheater_Impl::setRatedOutdoorAirTemperature(double ratedOutdoorAirTemperature) {
      const bool result = setDouble(openstudio::Coil_WaterHeating_DesuperheaterFields::RatedOutdoorAirTemperature, ratedOutdoorAirTemperature);
      OS_ASSERT(result);
      return result;
    }

    double CoilWaterHeatingDesuperheater_Impl::maximumInletWaterTemperatureforHeatReclaim() const {
      const auto value = getDouble(openstudio::Coil_WaterHeating_DesuperheaterFields::MaximumInletWaterTemperatureforHeatReclaim, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingDesuperheater_Impl::setMaximumInletWaterTemperatureforHeatReclaim(double maximumInletWaterTemperatureforHeatReclaim) {
      const bool result = setDouble(openstudio::Coil_WaterHeating_DesuperheaterFields::MaximumInletWaterTemperatureforHeatReclaim,
                                    maximumInletWaterTemperatureforHeatReclaim);
      OS_ASSERT(result);
      return result;
    }

    double CoilWaterHeatingDesuperheater_Impl::waterFlowRate() const {
      const auto value = getDouble(openstudio::Coil_WaterHeating_DesuperheaterFields::WaterFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingDesuperheater_Impl::setWaterFlowRate(double waterFlowRate) {
      return setDouble(openstudio::Coil_WaterHeating_DesuperheaterFields::WaterFlowRate, waterFlowRate);
    }

    double CoilWaterHeatingDesuperheater_Impl::waterPumpPower() const {
      const auto value = getDouble(openstudio::Coil_WaterHeating_DesuperheaterFields::WaterPumpPower, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingDesuperheater_Impl::isWaterPumpPowerDefaulted() const {
      return isEmpty(openstudio::Coil_WaterHeating_DesuperheaterFields::WaterPumpPower);
    }

    bool CoilWaterHeatingDesuperheater_Impl::setWaterPumpPower(double waterPumpPower) {
      return setDouble(openstudio::Coil_WaterHeating_DesuperheaterFields::WaterPumpPower, waterPumpPower);
    }

    void CoilWaterHeatingDesuperheater_Impl::resetWaterPumpPower() {
      OS_ASSERT(setString(openstudio::Coil_WaterHeating_DesuperheaterFields::WaterPumpPower, ""));
    }

    double CoilWaterHeatingDesuperheater_Impl::fractionofPumpHeattoWater() const {
      const auto value = getDouble(openstudio::Coil_WaterHeating_DesuperheaterFields::FractionofPumpHeattoWater, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingDesuperheater_Impl::isFractionofPumpHeattoWaterDefaulted() const {
      return isEmpty(openstudio::Coil_WaterHeating_DesuperheaterFields::FractionofPumpHeattoWater);
    }

    bool CoilWaterHeatingDesuperheater_Impl::setFractionofPumpHeattoWater(double fractionofPumpHeattoWater) {
      return setDouble(openstudio::Coil_WaterHeating_DesuperheaterFields::FractionofPumpHeattoWater, fractionofPumpHeattoWater);
    }

    void CoilWaterHeatingDesuperheater_Impl::resetFractionofPumpHeattoWater() {
      OS_ASSERT(setString(openstudio::Coil_WaterHeating_DesuperheaterFields::FractionofPumpHeattoWater, ""));
    }

    double CoilWaterHeatingDesuperheater_Impl::onCycleParasiticElectricLoad() const {
      const auto value = getDouble(openstudio::Coil_WaterHeating_DesuperheaterFields::OnCycleParasiticElectricLoad, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingDesuperheater_Impl::isOnCycleParasiticElectricLoadDefaulted() const {
      return isEmpty(openstudio::Coil_WaterHeating_DesuperheaterFields::OnCycleParasiticElectricLoad);
    }

    bool CoilWaterHeatingDesuperheater_Impl::setOnCycleParasiticElectricLoad(double onCycleParasiticElectricLoad) {
      return setDouble(openstudio::Coil_WaterHeating_DesuperheaterFields::OnCycleParasiticElectricLoad, onCycleParasiticElectricLoad);
    }

    void CoilWaterHeatingDesuperheater_Impl::resetOnCycleParasiticElectricLoad() {
      OS_ASSERT(setString(openstudio::Coil_WaterHeating_DesuperheaterFields::OnCycleParasiticElectricLoad, ""));
    }

    double CoilWaterHeatingDesuperheater_Impl::offCycleParasiticElectricLoad() const {
      const auto value = getDouble(openstudio::Coil_WaterHeating_DesuperheaterFields::OffCycleParasiticElectricLoad, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingDesuperheater_Impl::isOffCycleParasiticElectricLoadDefaulted() const {
      return isEmpty(openstudio::Coil_WaterHeating_DesuperheaterFields::OffCycleParasiticElectricLoad);
    }

    bool CoilWaterHeatingDesuperheater_Impl::setOffCycleParasiticElectricLoad(double offCycleParasiticElectricLoad) {
      return setDouble(openstudio::Coil_WaterHeating_DesuperheaterFields::OffCycleParasiticElectricLoad, offCycleParasiticElectricLoad);
    }

    void CoilWaterHeatingDesuperheater_Impl::resetOffCycleParasiticElectricLoad() {
      OS_ASSERT(setString(openstudio::Coil_WaterHeating_DesuperheaterFields::OffCycleParasiticElectricLoad, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
