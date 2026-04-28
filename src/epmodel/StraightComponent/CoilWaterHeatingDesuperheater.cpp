/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilWaterHeatingDesuperheater.hpp"
#include "StraightComponent/CoilWaterHeatingDesuperheater_Impl.hpp"

#include "Curve/CurveBiquadratic.hpp"
#include "Curve/CurveBiquadratic_Impl.hpp"
#include "Model.hpp"
#include "ModelObject/ModelObject.hpp"
#include "StraightComponent/Node.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Coil_WaterHeating_Desuperheater_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  CoilWaterHeatingDesuperheater::CoilWaterHeatingDesuperheater(const Model& model)
    : StraightComponent(CoilWaterHeatingDesuperheater::iddObjectType(), model) {
    bool ok = true;
    auto alwaysOn = const_cast<Model&>(model).alwaysOnDiscreteSchedule();
    ok = setAvailabilitySchedule(alwaysOn);
    OS_ASSERT(ok);
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

  Schedule CoilWaterHeatingDesuperheater::availabilitySchedule() const {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->availabilitySchedule();
  }

  bool CoilWaterHeatingDesuperheater::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->setAvailabilitySchedule(schedule);
  }

  boost::optional<CurveBiquadratic> CoilWaterHeatingDesuperheater::heatReclaimEfficiencyFunctionofTemperatureCurve() const {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->heatReclaimEfficiencyFunctionofTemperatureCurve();
  }

  bool CoilWaterHeatingDesuperheater::setHeatReclaimEfficiencyFunctionofTemperatureCurve(const CurveBiquadratic& curveBiquadratic) {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->setHeatReclaimEfficiencyFunctionofTemperatureCurve(curveBiquadratic);
  }

  void CoilWaterHeatingDesuperheater::resetHeatReclaimEfficiencyFunctionofTemperatureCurve() {
    getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->resetHeatReclaimEfficiencyFunctionofTemperatureCurve();
  }

  boost::optional<ModelObject> CoilWaterHeatingDesuperheater::heatingSource() const {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->heatingSource();
  }

  bool CoilWaterHeatingDesuperheater::setHeatingSource(const ModelObject& heatingSource) {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->setHeatingSource(heatingSource);
  }

  void CoilWaterHeatingDesuperheater::resetHeatingSource() {
    getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->resetHeatingSource();
  }

  bool CoilWaterHeatingDesuperheater::addToNode(Node& node) {
    return getImpl<detail::CoilWaterHeatingDesuperheater_Impl>()->addToNode(node);
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

    std::vector<ModelObject> CoilWaterHeatingDesuperheater_Impl::children() const {
      std::vector<ModelObject> result;
      if (auto curve = heatReclaimEfficiencyFunctionofTemperatureCurve()) {
        result.push_back(*curve);
      }
      return result;
    }

    Schedule CoilWaterHeatingDesuperheater_Impl::availabilitySchedule() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Coil_WaterHeating_DesuperheaterFields::AvailabilityScheduleName);
      if (!value) {
        value = this->model().alwaysOnDiscreteSchedule();
        OS_ASSERT(value);
        const_cast<CoilWaterHeatingDesuperheater_Impl*>(this)->setAvailabilitySchedule(*value);
        value = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Coil_WaterHeating_DesuperheaterFields::AvailabilityScheduleName);
      }
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingDesuperheater_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setPointer(openstudio::Coil_WaterHeating_DesuperheaterFields::AvailabilityScheduleName, schedule.handle(), false);
    }

    boost::optional<CurveBiquadratic> CoilWaterHeatingDesuperheater_Impl::heatReclaimEfficiencyFunctionofTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<CurveBiquadratic>(
        openstudio::Coil_WaterHeating_DesuperheaterFields::HeatReclaimEfficiencyFunctionofTemperatureCurveName);
    }

    bool CoilWaterHeatingDesuperheater_Impl::setHeatReclaimEfficiencyFunctionofTemperatureCurve(const CurveBiquadratic& curveBiquadratic) {
      return setPointer(openstudio::Coil_WaterHeating_DesuperheaterFields::HeatReclaimEfficiencyFunctionofTemperatureCurveName,
                        curveBiquadratic.handle(), false);
    }

    void CoilWaterHeatingDesuperheater_Impl::resetHeatReclaimEfficiencyFunctionofTemperatureCurve() {
      OS_ASSERT(setPointer(openstudio::Coil_WaterHeating_DesuperheaterFields::HeatReclaimEfficiencyFunctionofTemperatureCurveName,
                           openstudio::Handle(), false));
    }

    boost::optional<ModelObject> CoilWaterHeatingDesuperheater_Impl::heatingSource() const {
      return getObject<ModelObject>().getModelObjectTarget<ModelObject>(openstudio::Coil_WaterHeating_DesuperheaterFields::HeatingSourceName);
    }

    bool CoilWaterHeatingDesuperheater_Impl::setHeatingSource(const ModelObject& heatingSource) {
      const bool result = setPointer(openstudio::Coil_WaterHeating_DesuperheaterFields::HeatingSourceName, heatingSource.handle(), false);

      if (auto rated = ratedHeatReclaimRecoveryEfficiency()) {
        const auto heatingSourceIddObjectType = heatingSource.iddObject().type();
        if ((heatingSourceIddObjectType == IddObjectType::Refrigeration_Condenser_AirCooled)
            || (heatingSourceIddObjectType == IddObjectType::Refrigeration_Condenser_EvaporativeCooled)
            || (heatingSourceIddObjectType == IddObjectType::Refrigeration_Condenser_WaterCooled)) {
          if (*rated > 0.9) {
            setDouble(openstudio::Coil_WaterHeating_DesuperheaterFields::RatedHeatReclaimRecoveryEfficiency, 0.8);
          }
        } else if (*rated > 0.3) {
          setDouble(openstudio::Coil_WaterHeating_DesuperheaterFields::RatedHeatReclaimRecoveryEfficiency, 0.25);
        }
      }

      return result;
    }

    void CoilWaterHeatingDesuperheater_Impl::resetHeatingSource() {
      OS_ASSERT(setPointer(openstudio::Coil_WaterHeating_DesuperheaterFields::HeatingSourceName, openstudio::Handle(), false));
    }

    bool CoilWaterHeatingDesuperheater_Impl::addToNode(Node& /*node*/) {
      return false;
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
