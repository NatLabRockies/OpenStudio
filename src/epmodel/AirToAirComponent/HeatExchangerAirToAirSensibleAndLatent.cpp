/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirToAirComponent/HeatExchangerAirToAirSensibleAndLatent.hpp"
#include "AirToAirComponent/HeatExchangerAirToAirSensibleAndLatent_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HeatExchanger_AirToAir_SensibleAndLatent_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  HeatExchangerAirToAirSensibleAndLatent::HeatExchangerAirToAirSensibleAndLatent(const Model& model)
    : AirToAirComponent(HeatExchangerAirToAirSensibleAndLatent::iddObjectType(), model) {
    auto schedule = model.alwaysOnDiscreteSchedule();
    OS_ASSERT(setAvailabilitySchedule(schedule));
  }

  HeatExchangerAirToAirSensibleAndLatent::HeatExchangerAirToAirSensibleAndLatent(
    std::shared_ptr<detail::HeatExchangerAirToAirSensibleAndLatent_Impl> impl)
    : AirToAirComponent(std::move(impl)) {}

  IddObjectType HeatExchangerAirToAirSensibleAndLatent::iddObjectType() {
    return IddObjectType::HeatExchanger_AirToAir_SensibleAndLatent;
  }

  std::vector<std::string> HeatExchangerAirToAirSensibleAndLatent::heatExchangerTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::HeatExchangerType);
  }

  std::vector<std::string> HeatExchangerAirToAirSensibleAndLatent::frostControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::FrostControlType);
  }

  Schedule HeatExchangerAirToAirSensibleAndLatent::availabilitySchedule() const {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->availabilitySchedule();
  }

  bool HeatExchangerAirToAirSensibleAndLatent::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->setAvailabilitySchedule(schedule);
  }

  boost::optional<Curve> HeatExchangerAirToAirSensibleAndLatent::sensibleEffectivenessofHeatingAirFlowCurve() const {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->sensibleEffectivenessofHeatingAirFlowCurve();
  }

  bool HeatExchangerAirToAirSensibleAndLatent::setSensibleEffectivenessofHeatingAirFlowCurve(const Curve& curve) {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->setSensibleEffectivenessofHeatingAirFlowCurve(curve);
  }

  void HeatExchangerAirToAirSensibleAndLatent::resetSensibleEffectivenessofHeatingAirFlowCurve() {
    getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->resetSensibleEffectivenessofHeatingAirFlowCurve();
  }

  boost::optional<Curve> HeatExchangerAirToAirSensibleAndLatent::latentEffectivenessofHeatingAirFlowCurve() const {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->latentEffectivenessofHeatingAirFlowCurve();
  }

  bool HeatExchangerAirToAirSensibleAndLatent::setLatentEffectivenessofHeatingAirFlowCurve(const Curve& curve) {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->setLatentEffectivenessofHeatingAirFlowCurve(curve);
  }

  void HeatExchangerAirToAirSensibleAndLatent::resetLatentEffectivenessofHeatingAirFlowCurve() {
    getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->resetLatentEffectivenessofHeatingAirFlowCurve();
  }

  boost::optional<Curve> HeatExchangerAirToAirSensibleAndLatent::sensibleEffectivenessofCoolingAirFlowCurve() const {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->sensibleEffectivenessofCoolingAirFlowCurve();
  }

  bool HeatExchangerAirToAirSensibleAndLatent::setSensibleEffectivenessofCoolingAirFlowCurve(const Curve& curve) {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->setSensibleEffectivenessofCoolingAirFlowCurve(curve);
  }

  void HeatExchangerAirToAirSensibleAndLatent::resetSensibleEffectivenessofCoolingAirFlowCurve() {
    getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->resetSensibleEffectivenessofCoolingAirFlowCurve();
  }

  boost::optional<Curve> HeatExchangerAirToAirSensibleAndLatent::latentEffectivenessofCoolingAirFlowCurve() const {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->latentEffectivenessofCoolingAirFlowCurve();
  }

  bool HeatExchangerAirToAirSensibleAndLatent::setLatentEffectivenessofCoolingAirFlowCurve(const Curve& curve) {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->setLatentEffectivenessofCoolingAirFlowCurve(curve);
  }

  void HeatExchangerAirToAirSensibleAndLatent::resetLatentEffectivenessofCoolingAirFlowCurve() {
    getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->resetLatentEffectivenessofCoolingAirFlowCurve();
  }

  boost::optional<double> HeatExchangerAirToAirSensibleAndLatent::nominalSupplyAirFlowRate() const {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->nominalSupplyAirFlowRate();
  }

  bool HeatExchangerAirToAirSensibleAndLatent::setNominalSupplyAirFlowRate(double nominalSupplyAirFlowRate) {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->setNominalSupplyAirFlowRate(nominalSupplyAirFlowRate);
  }

  bool HeatExchangerAirToAirSensibleAndLatent::isNominalSupplyAirFlowRateAutosized() const {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->isNominalSupplyAirFlowRateAutosized();
  }

  void HeatExchangerAirToAirSensibleAndLatent::autosizeNominalSupplyAirFlowRate() {
    getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->autosizeNominalSupplyAirFlowRate();
  }

  double HeatExchangerAirToAirSensibleAndLatent::sensibleEffectivenessat100HeatingAirFlow() const {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->sensibleEffectivenessat100HeatingAirFlow();
  }

  bool HeatExchangerAirToAirSensibleAndLatent::setSensibleEffectivenessat100HeatingAirFlow(double sensibleEffectivenessat100HeatingAirFlow) {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->setSensibleEffectivenessat100HeatingAirFlow(
      sensibleEffectivenessat100HeatingAirFlow);
  }

  double HeatExchangerAirToAirSensibleAndLatent::latentEffectivenessat100HeatingAirFlow() const {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->latentEffectivenessat100HeatingAirFlow();
  }

  bool HeatExchangerAirToAirSensibleAndLatent::setLatentEffectivenessat100HeatingAirFlow(double latentEffectivenessat100HeatingAirFlow) {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->setLatentEffectivenessat100HeatingAirFlow(
      latentEffectivenessat100HeatingAirFlow);
  }

  double HeatExchangerAirToAirSensibleAndLatent::sensibleEffectivenessat100CoolingAirFlow() const {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->sensibleEffectivenessat100CoolingAirFlow();
  }

  bool HeatExchangerAirToAirSensibleAndLatent::setSensibleEffectivenessat100CoolingAirFlow(double sensibleEffectivenessat100CoolingAirFlow) {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->setSensibleEffectivenessat100CoolingAirFlow(
      sensibleEffectivenessat100CoolingAirFlow);
  }

  double HeatExchangerAirToAirSensibleAndLatent::latentEffectivenessat100CoolingAirFlow() const {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->latentEffectivenessat100CoolingAirFlow();
  }

  bool HeatExchangerAirToAirSensibleAndLatent::setLatentEffectivenessat100CoolingAirFlow(double latentEffectivenessat100CoolingAirFlow) {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->setLatentEffectivenessat100CoolingAirFlow(
      latentEffectivenessat100CoolingAirFlow);
  }

  double HeatExchangerAirToAirSensibleAndLatent::nominalElectricPower() const {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->nominalElectricPower();
  }

  bool HeatExchangerAirToAirSensibleAndLatent::setNominalElectricPower(double nominalElectricPower) {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->setNominalElectricPower(nominalElectricPower);
  }

  bool HeatExchangerAirToAirSensibleAndLatent::supplyAirOutletTemperatureControl() const {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->supplyAirOutletTemperatureControl();
  }

  bool HeatExchangerAirToAirSensibleAndLatent::setSupplyAirOutletTemperatureControl(bool supplyAirOutletTemperatureControl) {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->setSupplyAirOutletTemperatureControl(supplyAirOutletTemperatureControl);
  }

  std::string HeatExchangerAirToAirSensibleAndLatent::heatExchangerType() const {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->heatExchangerType();
  }

  bool HeatExchangerAirToAirSensibleAndLatent::setHeatExchangerType(const std::string& heatExchangerType) {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->setHeatExchangerType(heatExchangerType);
  }

  std::string HeatExchangerAirToAirSensibleAndLatent::frostControlType() const {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->frostControlType();
  }

  bool HeatExchangerAirToAirSensibleAndLatent::setFrostControlType(const std::string& frostControlType) {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->setFrostControlType(frostControlType);
  }

  double HeatExchangerAirToAirSensibleAndLatent::thresholdTemperature() const {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->thresholdTemperature();
  }

  bool HeatExchangerAirToAirSensibleAndLatent::setThresholdTemperature(double thresholdTemperature) {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->setThresholdTemperature(thresholdTemperature);
  }

  bool HeatExchangerAirToAirSensibleAndLatent::isThresholdTemperatureDefaulted() const {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->isThresholdTemperatureDefaulted();
  }

  void HeatExchangerAirToAirSensibleAndLatent::resetThresholdTemperature() {
    getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->resetThresholdTemperature();
  }

  boost::optional<double> HeatExchangerAirToAirSensibleAndLatent::initialDefrostTimeFraction() const {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->initialDefrostTimeFraction();
  }

  bool HeatExchangerAirToAirSensibleAndLatent::setInitialDefrostTimeFraction(double initialDefrostTimeFraction) {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->setInitialDefrostTimeFraction(initialDefrostTimeFraction);
  }

  void HeatExchangerAirToAirSensibleAndLatent::resetInitialDefrostTimeFraction() {
    getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->resetInitialDefrostTimeFraction();
  }

  boost::optional<double> HeatExchangerAirToAirSensibleAndLatent::rateofDefrostTimeFractionIncrease() const {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->rateofDefrostTimeFractionIncrease();
  }

  bool HeatExchangerAirToAirSensibleAndLatent::setRateofDefrostTimeFractionIncrease(double rateofDefrostTimeFractionIncrease) {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->setRateofDefrostTimeFractionIncrease(rateofDefrostTimeFractionIncrease);
  }

  void HeatExchangerAirToAirSensibleAndLatent::resetRateofDefrostTimeFractionIncrease() {
    getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->resetRateofDefrostTimeFractionIncrease();
  }

  bool HeatExchangerAirToAirSensibleAndLatent::economizerLockout() const {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->economizerLockout();
  }

  bool HeatExchangerAirToAirSensibleAndLatent::setEconomizerLockout(bool economizerLockout) {
    return getImpl<detail::HeatExchangerAirToAirSensibleAndLatent_Impl>()->setEconomizerLockout(economizerLockout);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    HeatExchangerAirToAirSensibleAndLatent_Impl::HeatExchangerAirToAirSensibleAndLatent_Impl(const IdfObject& idfObject, Model_Impl* model,
                                                                                             bool keepHandle)
      : AirToAirComponent_Impl(idfObject, model, keepHandle) {}

    HeatExchangerAirToAirSensibleAndLatent_Impl::HeatExchangerAirToAirSensibleAndLatent_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                                                             Model_Impl* model, bool keepHandle)
      : AirToAirComponent_Impl(other, model, keepHandle) {}

    HeatExchangerAirToAirSensibleAndLatent_Impl::HeatExchangerAirToAirSensibleAndLatent_Impl(const HeatExchangerAirToAirSensibleAndLatent_Impl& other,
                                                                                             Model_Impl* model, bool keepHandle)
      : AirToAirComponent_Impl(other, model, keepHandle) {}

    Schedule HeatExchangerAirToAirSensibleAndLatent_Impl::availabilitySchedule() const {
      auto schedule =
        getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::AvailabilityScheduleName);
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool HeatExchangerAirToAirSensibleAndLatent_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::AvailabilityScheduleName,
                                           "HeatExchangerAirToAirSensibleAndLatent", "Availability", schedule);
    }

    boost::optional<Curve> HeatExchangerAirToAirSensibleAndLatent_Impl::sensibleEffectivenessofHeatingAirFlowCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        HeatExchanger_AirToAir_SensibleAndLatentFields::SensibleEffectivenessofHeatingAirFlowCurveName);
    }

    bool HeatExchangerAirToAirSensibleAndLatent_Impl::setSensibleEffectivenessofHeatingAirFlowCurve(const Curve& curve) {
      if (curve.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.HeatExchangerAirToAirSensibleAndLatent",
                 "Cannot set the sensible heating effectiveness curve because it belongs to a different model.");
        return false;
      }
      const auto field = openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::SensibleEffectivenessofHeatingAirFlowCurveName;
      if (!model().canBeTarget(curve.handle(), iddObject().objectLists(field))) {
        LOG_FREE(Warn, "openstudio.epmodel.HeatExchangerAirToAirSensibleAndLatent",
                 "Cannot set the sensible heating effectiveness curve because curve type '" << curve.iddObject().type().valueName()
                                                                                            << "' is not accepted by the heat exchanger field.");
        return false;
      }
      return setPointer(field, curve.handle(), false);
    }

    void HeatExchangerAirToAirSensibleAndLatent_Impl::resetSensibleEffectivenessofHeatingAirFlowCurve() {
      OS_ASSERT(
        setPointer(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::SensibleEffectivenessofHeatingAirFlowCurveName, Handle(), false));
    }

    boost::optional<Curve> HeatExchangerAirToAirSensibleAndLatent_Impl::latentEffectivenessofHeatingAirFlowCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        HeatExchanger_AirToAir_SensibleAndLatentFields::LatentEffectivenessofHeatingAirFlowCurveName);
    }

    bool HeatExchangerAirToAirSensibleAndLatent_Impl::setLatentEffectivenessofHeatingAirFlowCurve(const Curve& curve) {
      if (curve.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.HeatExchangerAirToAirSensibleAndLatent",
                 "Cannot set the latent heating effectiveness curve because it belongs to a different model.");
        return false;
      }
      const auto field = openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::LatentEffectivenessofHeatingAirFlowCurveName;
      if (!model().canBeTarget(curve.handle(), iddObject().objectLists(field))) {
        LOG_FREE(Warn, "openstudio.epmodel.HeatExchangerAirToAirSensibleAndLatent",
                 "Cannot set the latent heating effectiveness curve because curve type '" << curve.iddObject().type().valueName()
                                                                                          << "' is not accepted by the heat exchanger field.");
        return false;
      }
      return setPointer(field, curve.handle(), false);
    }

    void HeatExchangerAirToAirSensibleAndLatent_Impl::resetLatentEffectivenessofHeatingAirFlowCurve() {
      OS_ASSERT(
        setPointer(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::LatentEffectivenessofHeatingAirFlowCurveName, Handle(), false));
    }

    boost::optional<Curve> HeatExchangerAirToAirSensibleAndLatent_Impl::sensibleEffectivenessofCoolingAirFlowCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        HeatExchanger_AirToAir_SensibleAndLatentFields::SensibleEffectivenessofCoolingAirFlowCurveName);
    }

    bool HeatExchangerAirToAirSensibleAndLatent_Impl::setSensibleEffectivenessofCoolingAirFlowCurve(const Curve& curve) {
      if (curve.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.HeatExchangerAirToAirSensibleAndLatent",
                 "Cannot set the sensible cooling effectiveness curve because it belongs to a different model.");
        return false;
      }
      const auto field = openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::SensibleEffectivenessofCoolingAirFlowCurveName;
      if (!model().canBeTarget(curve.handle(), iddObject().objectLists(field))) {
        LOG_FREE(Warn, "openstudio.epmodel.HeatExchangerAirToAirSensibleAndLatent",
                 "Cannot set the sensible cooling effectiveness curve because curve type '" << curve.iddObject().type().valueName()
                                                                                            << "' is not accepted by the heat exchanger field.");
        return false;
      }
      return setPointer(field, curve.handle(), false);
    }

    void HeatExchangerAirToAirSensibleAndLatent_Impl::resetSensibleEffectivenessofCoolingAirFlowCurve() {
      OS_ASSERT(
        setPointer(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::SensibleEffectivenessofCoolingAirFlowCurveName, Handle(), false));
    }

    boost::optional<Curve> HeatExchangerAirToAirSensibleAndLatent_Impl::latentEffectivenessofCoolingAirFlowCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        HeatExchanger_AirToAir_SensibleAndLatentFields::LatentEffectivenessofCoolingAirFlowCurveName);
    }

    bool HeatExchangerAirToAirSensibleAndLatent_Impl::setLatentEffectivenessofCoolingAirFlowCurve(const Curve& curve) {
      if (curve.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.HeatExchangerAirToAirSensibleAndLatent",
                 "Cannot set the latent cooling effectiveness curve because it belongs to a different model.");
        return false;
      }
      const auto field = openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::LatentEffectivenessofCoolingAirFlowCurveName;
      if (!model().canBeTarget(curve.handle(), iddObject().objectLists(field))) {
        LOG_FREE(Warn, "openstudio.epmodel.HeatExchangerAirToAirSensibleAndLatent",
                 "Cannot set the latent cooling effectiveness curve because curve type '" << curve.iddObject().type().valueName()
                                                                                          << "' is not accepted by the heat exchanger field.");
        return false;
      }
      return setPointer(field, curve.handle(), false);
    }

    void HeatExchangerAirToAirSensibleAndLatent_Impl::resetLatentEffectivenessofCoolingAirFlowCurve() {
      OS_ASSERT(
        setPointer(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::LatentEffectivenessofCoolingAirFlowCurveName, Handle(), false));
    }

    boost::optional<double> HeatExchangerAirToAirSensibleAndLatent_Impl::nominalSupplyAirFlowRate() const {
      return getDouble(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::NominalSupplyAirFlowRate, true);
    }

    bool HeatExchangerAirToAirSensibleAndLatent_Impl::setNominalSupplyAirFlowRate(double nominalSupplyAirFlowRate) {
      return setDouble(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::NominalSupplyAirFlowRate, nominalSupplyAirFlowRate);
    }

    bool HeatExchangerAirToAirSensibleAndLatent_Impl::isNominalSupplyAirFlowRateAutosized() const {
      bool result = false;
      const auto value = getString(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::NominalSupplyAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(*value, "autosize");
      }
      return result;
    }

    void HeatExchangerAirToAirSensibleAndLatent_Impl::autosizeNominalSupplyAirFlowRate() {
      OS_ASSERT(setString(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::NominalSupplyAirFlowRate, "autosize"));
    }

    double HeatExchangerAirToAirSensibleAndLatent_Impl::sensibleEffectivenessat100HeatingAirFlow() const {
      const auto value = getDouble(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::SensibleEffectivenessat100_HeatingAirFlow, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HeatExchangerAirToAirSensibleAndLatent_Impl::setSensibleEffectivenessat100HeatingAirFlow(double sensibleEffectivenessat100HeatingAirFlow) {
      return setDouble(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::SensibleEffectivenessat100_HeatingAirFlow,
                       sensibleEffectivenessat100HeatingAirFlow);
    }

    double HeatExchangerAirToAirSensibleAndLatent_Impl::latentEffectivenessat100HeatingAirFlow() const {
      const auto value = getDouble(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::LatentEffectivenessat100_HeatingAirFlow, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HeatExchangerAirToAirSensibleAndLatent_Impl::setLatentEffectivenessat100HeatingAirFlow(double latentEffectivenessat100HeatingAirFlow) {
      return setDouble(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::LatentEffectivenessat100_HeatingAirFlow,
                       latentEffectivenessat100HeatingAirFlow);
    }

    double HeatExchangerAirToAirSensibleAndLatent_Impl::sensibleEffectivenessat100CoolingAirFlow() const {
      const auto value = getDouble(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::SensibleEffectivenessat100_CoolingAirFlow, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HeatExchangerAirToAirSensibleAndLatent_Impl::setSensibleEffectivenessat100CoolingAirFlow(double sensibleEffectivenessat100CoolingAirFlow) {
      return setDouble(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::SensibleEffectivenessat100_CoolingAirFlow,
                       sensibleEffectivenessat100CoolingAirFlow);
    }

    double HeatExchangerAirToAirSensibleAndLatent_Impl::latentEffectivenessat100CoolingAirFlow() const {
      const auto value = getDouble(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::LatentEffectivenessat100_CoolingAirFlow, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HeatExchangerAirToAirSensibleAndLatent_Impl::setLatentEffectivenessat100CoolingAirFlow(double latentEffectivenessat100CoolingAirFlow) {
      return setDouble(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::LatentEffectivenessat100_CoolingAirFlow,
                       latentEffectivenessat100CoolingAirFlow);
    }

    double HeatExchangerAirToAirSensibleAndLatent_Impl::nominalElectricPower() const {
      const auto value = getDouble(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::NominalElectricPower, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HeatExchangerAirToAirSensibleAndLatent_Impl::setNominalElectricPower(double nominalElectricPower) {
      return setDouble(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::NominalElectricPower, nominalElectricPower);
    }

    bool HeatExchangerAirToAirSensibleAndLatent_Impl::supplyAirOutletTemperatureControl() const {
      const auto value = getString(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::SupplyAirOutletTemperatureControl, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool HeatExchangerAirToAirSensibleAndLatent_Impl::setSupplyAirOutletTemperatureControl(bool supplyAirOutletTemperatureControl) {
      return setString(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::SupplyAirOutletTemperatureControl,
                       supplyAirOutletTemperatureControl ? "Yes" : "No");
    }

    std::string HeatExchangerAirToAirSensibleAndLatent_Impl::heatExchangerType() const {
      const auto value = getString(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::HeatExchangerType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HeatExchangerAirToAirSensibleAndLatent_Impl::setHeatExchangerType(const std::string& heatExchangerType) {
      return setString(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::HeatExchangerType, heatExchangerType);
    }

    std::string HeatExchangerAirToAirSensibleAndLatent_Impl::frostControlType() const {
      const auto value = getString(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::FrostControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HeatExchangerAirToAirSensibleAndLatent_Impl::setFrostControlType(const std::string& frostControlType) {
      return setString(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::FrostControlType, frostControlType);
    }

    double HeatExchangerAirToAirSensibleAndLatent_Impl::thresholdTemperature() const {
      const auto value = getDouble(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::ThresholdTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HeatExchangerAirToAirSensibleAndLatent_Impl::setThresholdTemperature(double thresholdTemperature) {
      const bool result = setDouble(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::ThresholdTemperature, thresholdTemperature);
      OS_ASSERT(result);
      return result;
    }

    bool HeatExchangerAirToAirSensibleAndLatent_Impl::isThresholdTemperatureDefaulted() const {
      return isEmpty(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::ThresholdTemperature);
    }

    void HeatExchangerAirToAirSensibleAndLatent_Impl::resetThresholdTemperature() {
      OS_ASSERT(setString(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::ThresholdTemperature, ""));
    }

    boost::optional<double> HeatExchangerAirToAirSensibleAndLatent_Impl::initialDefrostTimeFraction() const {
      return getDouble(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::InitialDefrostTimeFraction, true);
    }

    bool HeatExchangerAirToAirSensibleAndLatent_Impl::setInitialDefrostTimeFraction(double initialDefrostTimeFraction) {
      return setDouble(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::InitialDefrostTimeFraction, initialDefrostTimeFraction);
    }

    void HeatExchangerAirToAirSensibleAndLatent_Impl::resetInitialDefrostTimeFraction() {
      OS_ASSERT(setString(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::InitialDefrostTimeFraction, ""));
    }

    boost::optional<double> HeatExchangerAirToAirSensibleAndLatent_Impl::rateofDefrostTimeFractionIncrease() const {
      return getDouble(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::RateofDefrostTimeFractionIncrease, true);
    }

    bool HeatExchangerAirToAirSensibleAndLatent_Impl::setRateofDefrostTimeFractionIncrease(double rateofDefrostTimeFractionIncrease) {
      return setDouble(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::RateofDefrostTimeFractionIncrease,
                       rateofDefrostTimeFractionIncrease);
    }

    void HeatExchangerAirToAirSensibleAndLatent_Impl::resetRateofDefrostTimeFractionIncrease() {
      OS_ASSERT(setString(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::RateofDefrostTimeFractionIncrease, ""));
    }

    bool HeatExchangerAirToAirSensibleAndLatent_Impl::economizerLockout() const {
      const auto value = getString(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::EconomizerLockout, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool HeatExchangerAirToAirSensibleAndLatent_Impl::setEconomizerLockout(bool economizerLockout) {
      return setString(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::EconomizerLockout, economizerLockout ? "Yes" : "No");
    }

    unsigned HeatExchangerAirToAirSensibleAndLatent_Impl::primaryAirInletPort() const {
      return openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::SupplyAirInletNodeName;
    }

    unsigned HeatExchangerAirToAirSensibleAndLatent_Impl::primaryAirOutletPort() const {
      return openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::SupplyAirOutletNodeName;
    }

    unsigned HeatExchangerAirToAirSensibleAndLatent_Impl::secondaryAirInletPort() const {
      return openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::ExhaustAirInletNodeName;
    }

    unsigned HeatExchangerAirToAirSensibleAndLatent_Impl::secondaryAirOutletPort() const {
      return openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::ExhaustAirOutletNodeName;
    }

    std::vector<std::string> HeatExchangerAirToAirSensibleAndLatent_Impl::heatExchangerTypeValues() const {
      return openstudio::epmodel::HeatExchangerAirToAirSensibleAndLatent::heatExchangerTypeValues();
    }

    std::vector<std::string> HeatExchangerAirToAirSensibleAndLatent_Impl::frostControlTypeValues() const {
      return openstudio::epmodel::HeatExchangerAirToAirSensibleAndLatent::frostControlTypeValues();
    }

    void HeatExchangerAirToAirSensibleAndLatent_Impl::doCanonicalize(LoadContext& context) {
      AirToAirComponent_Impl::doCanonicalize(context);

      auto schedule =
        getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::AvailabilityScheduleName);
      if (!schedule) {
        auto alwaysOn = model().alwaysOnDiscreteSchedule();
        OS_ASSERT(setAvailabilitySchedule(alwaysOn));
        detail::addLoadInfo(context,
                            "Attached the always-on schedule to sensible and latent heat exchanger '" + getObject<ModelObject>().nameString() + "'.");
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
