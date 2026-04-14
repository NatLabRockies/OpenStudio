/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToAirComponent/CoilHeatingWater.hpp"
#include "WaterToAirComponent/CoilHeatingWater_Impl.hpp"

#include "HVACComponent/ControllerWaterCoil.hpp"
#include "HVACComponent/ControllerWaterCoil_Impl.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Heating_Water_FieldEnums.hxx>
#include <utilities/idd/Controller_WaterCoil_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

namespace {

// EnergyPlus stores the heating-coil controller relationship only through the
// shared actuator and sensor nodes. Matching those nodes back to the coil gives
// us the same user-facing association without inventing an epmodel-only link.
boost::optional<ControllerWaterCoil> inferControllerForCoil(const CoilHeatingWater& coil) {
  const auto waterInlet = coil.waterInletModelObject();
  const auto airOutlet = coil.airOutletModelObject();
  if (!waterInlet || !airOutlet) {
    return boost::none;
  }

  for (const auto& controller : coil.model().getConcreteModelObjects<ControllerWaterCoil>()) {
    const auto actuatorNode = controller.getModelObjectTarget<Node>(openstudio::Controller_WaterCoilFields::ActuatorNodeName);
    const auto sensorNode = controller.getModelObjectTarget<Node>(openstudio::Controller_WaterCoilFields::SensorNodeName);
    if (actuatorNode && sensorNode && actuatorNode->handle() == waterInlet->handle() && sensorNode->handle() == airOutlet->handle()) {
      return controller;
    }
  }

  return boost::none;
}

}  // namespace

CoilHeatingWater::CoilHeatingWater(const Model& model, Schedule& availabilitySchedule)
  : WaterToAirComponent(CoilHeatingWater::iddObjectType(), model) {
  OS_ASSERT(setAvailabilitySchedule(availabilitySchedule));
}

CoilHeatingWater::CoilHeatingWater(const Model& model) : WaterToAirComponent(CoilHeatingWater::iddObjectType(), model) {
  auto schedule = model.alwaysOnDiscreteSchedule();
  OS_ASSERT(setAvailabilitySchedule(schedule));
}

CoilHeatingWater::CoilHeatingWater(std::shared_ptr<detail::CoilHeatingWater_Impl> impl) : WaterToAirComponent(std::move(impl)) {}

IddObjectType CoilHeatingWater::iddObjectType() {
  return IddObjectType::Coil_Heating_Water;
}

std::vector<std::string> CoilHeatingWater::performanceInputMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Coil_Heating_WaterFields::PerformanceInputMethod);
}

Schedule CoilHeatingWater::availabilitySchedule() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->availabilitySchedule();
}

Schedule CoilHeatingWater::availableSchedule() const {
  return availabilitySchedule();
}

bool CoilHeatingWater::setAvailabilitySchedule(Schedule& schedule) {
  return getImpl<detail::CoilHeatingWater_Impl>()->setAvailabilitySchedule(schedule);
}

bool CoilHeatingWater::setAvailableSchedule(Schedule& schedule) {
  return setAvailabilitySchedule(schedule);
}

boost::optional<double> CoilHeatingWater::uFactorTimesAreaValue() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->uFactorTimesAreaValue();
}

bool CoilHeatingWater::setUFactorTimesAreaValue(double value) {
  return getImpl<detail::CoilHeatingWater_Impl>()->setUFactorTimesAreaValue(value);
}

bool CoilHeatingWater::isUFactorTimesAreaValueAutosized() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->isUFactorTimesAreaValueAutosized();
}

void CoilHeatingWater::autosizeUFactorTimesAreaValue() {
  getImpl<detail::CoilHeatingWater_Impl>()->autosizeUFactorTimesAreaValue();
}

boost::optional<double> CoilHeatingWater::autosizedUFactorTimesAreaValue() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->autosizedUFactorTimesAreaValue();
}

boost::optional<double> CoilHeatingWater::maximumWaterFlowRate() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->maximumWaterFlowRate();
}

bool CoilHeatingWater::setMaximumWaterFlowRate(double value) {
  return getImpl<detail::CoilHeatingWater_Impl>()->setMaximumWaterFlowRate(value);
}

bool CoilHeatingWater::isMaximumWaterFlowRateAutosized() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->isMaximumWaterFlowRateAutosized();
}

void CoilHeatingWater::autosizeMaximumWaterFlowRate() {
  getImpl<detail::CoilHeatingWater_Impl>()->autosizeMaximumWaterFlowRate();
}

boost::optional<double> CoilHeatingWater::autosizedMaximumWaterFlowRate() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->autosizedMaximumWaterFlowRate();
}

std::string CoilHeatingWater::performanceInputMethod() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->performanceInputMethod();
}

bool CoilHeatingWater::setPerformanceInputMethod(const std::string& value) {
  return getImpl<detail::CoilHeatingWater_Impl>()->setPerformanceInputMethod(value);
}

boost::optional<double> CoilHeatingWater::ratedCapacity() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->ratedCapacity();
}

bool CoilHeatingWater::setRatedCapacity(double value) {
  return getImpl<detail::CoilHeatingWater_Impl>()->setRatedCapacity(value);
}

bool CoilHeatingWater::isRatedCapacityAutosized() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->isRatedCapacityAutosized();
}

void CoilHeatingWater::autosizeRatedCapacity() {
  getImpl<detail::CoilHeatingWater_Impl>()->autosizeRatedCapacity();
}

boost::optional<double> CoilHeatingWater::autosizedRatedCapacity() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->autosizedRatedCapacity();
}

double CoilHeatingWater::ratedInletWaterTemperature() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->ratedInletWaterTemperature();
}

bool CoilHeatingWater::setRatedInletWaterTemperature(double value) {
  return getImpl<detail::CoilHeatingWater_Impl>()->setRatedInletWaterTemperature(value);
}

double CoilHeatingWater::ratedInletAirTemperature() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->ratedInletAirTemperature();
}

bool CoilHeatingWater::setRatedInletAirTemperature(double value) {
  return getImpl<detail::CoilHeatingWater_Impl>()->setRatedInletAirTemperature(value);
}

double CoilHeatingWater::ratedOutletWaterTemperature() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->ratedOutletWaterTemperature();
}

bool CoilHeatingWater::setRatedOutletWaterTemperature(double value) {
  return getImpl<detail::CoilHeatingWater_Impl>()->setRatedOutletWaterTemperature(value);
}

double CoilHeatingWater::ratedOutletAirTemperature() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->ratedOutletAirTemperature();
}

bool CoilHeatingWater::setRatedOutletAirTemperature(double value) {
  return getImpl<detail::CoilHeatingWater_Impl>()->setRatedOutletAirTemperature(value);
}

double CoilHeatingWater::ratedRatioForAirAndWaterConvection() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->ratedRatioForAirAndWaterConvection();
}

bool CoilHeatingWater::setRatedRatioForAirAndWaterConvection(double value) {
  return getImpl<detail::CoilHeatingWater_Impl>()->setRatedRatioForAirAndWaterConvection(value);
}

boost::optional<ControllerWaterCoil> CoilHeatingWater::controllerWaterCoil() const {
  return inferControllerForCoil(*this);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned CoilHeatingWater_Impl::airInletPort() const {
  return openstudio::Coil_Heating_WaterFields::AirInletNodeName;
}

unsigned CoilHeatingWater_Impl::airOutletPort() const {
  return openstudio::Coil_Heating_WaterFields::AirOutletNodeName;
}

unsigned CoilHeatingWater_Impl::waterInletPort() const {
  return openstudio::Coil_Heating_WaterFields::WaterInletNodeName;
}

unsigned CoilHeatingWater_Impl::waterOutletPort() const {
  return openstudio::Coil_Heating_WaterFields::WaterOutletNodeName;
}

bool CoilHeatingWater_Impl::addToNode(Node& node) {
  const bool success = WaterToAirComponent_Impl::addToNode(node);
  if (!success) {
    return false;
  }

  if (containingZoneHVACComponent()) {
    return true;
  }

  auto thisCoil = getObject<openstudio::epmodel::CoilHeatingWater>();
  const auto waterInlet = thisCoil.waterInletModelObject();
  const auto airOutlet = thisCoil.airOutletModelObject();
  if (!waterInlet || !airOutlet) {
    return true;
  }

  if (auto controller = inferControllerForCoil(thisCoil)) {
    if (auto action = controller->action(); action && !openstudio::istringEqual(*action, "Normal")) {
      LOG_FREE(Warn, "openstudio.epmodel.CoilHeatingWater",
               thisCoil.briefDescription() << " has an existing ControllerWaterCoil with action set to something other than 'Normal'.");
    }
    OS_ASSERT(controller->setPointer(openstudio::Controller_WaterCoilFields::ActuatorNodeName, waterInlet->handle()));
    OS_ASSERT(controller->setPointer(openstudio::Controller_WaterCoilFields::SensorNodeName, airOutlet->handle()));
    return true;
  }

  ControllerWaterCoil controller(model());
  OS_ASSERT(controller.setAction("Normal"));
  OS_ASSERT(controller.setPointer(openstudio::Controller_WaterCoilFields::ActuatorNodeName, waterInlet->handle()));
  OS_ASSERT(controller.setPointer(openstudio::Controller_WaterCoilFields::SensorNodeName, airOutlet->handle()));
  return true;
}

bool CoilHeatingWater_Impl::removeFromPlantLoop() {
  if (auto controller = inferControllerForCoil(getObject<openstudio::epmodel::CoilHeatingWater>())) {
    controller->remove();
  }
  return WaterToAirComponent_Impl::removeFromPlantLoop();
}

Schedule CoilHeatingWater_Impl::availabilitySchedule() const {
  auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Coil_Heating_WaterFields::AvailabilityScheduleName);
  if (!schedule) {
    LOG_FREE(Error, "openstudio.epmodel.CoilHeatingWater",
             "Required availability schedule not set, returning the model always-on discrete schedule without repairing persisted state");
    schedule = model().alwaysOnDiscreteSchedule();
  }
  OS_ASSERT(schedule);
  return *schedule;
}

bool CoilHeatingWater_Impl::setAvailabilitySchedule(Schedule& schedule) {
  return setSchedule(openstudio::Coil_Heating_WaterFields::AvailabilityScheduleName, "CoilHeatingWater", "Availability", schedule);
}

boost::optional<double> CoilHeatingWater_Impl::uFactorTimesAreaValue() const {
  return getDouble(openstudio::Coil_Heating_WaterFields::UFactorTimesAreaValue, true);
}

bool CoilHeatingWater_Impl::setUFactorTimesAreaValue(double value) {
  return setDouble(openstudio::Coil_Heating_WaterFields::UFactorTimesAreaValue, value);
}

bool CoilHeatingWater_Impl::isUFactorTimesAreaValueAutosized() const {
  if (const auto value = getString(openstudio::Coil_Heating_WaterFields::UFactorTimesAreaValue, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

void CoilHeatingWater_Impl::autosizeUFactorTimesAreaValue() {
  OS_ASSERT(setString(openstudio::Coil_Heating_WaterFields::UFactorTimesAreaValue, "autosize"));
}

boost::optional<double> CoilHeatingWater_Impl::autosizedUFactorTimesAreaValue() const {
  return boost::none;
}

boost::optional<double> CoilHeatingWater_Impl::maximumWaterFlowRate() const {
  return getDouble(openstudio::Coil_Heating_WaterFields::MaximumWaterFlowRate, true);
}

bool CoilHeatingWater_Impl::setMaximumWaterFlowRate(double value) {
  return setDouble(openstudio::Coil_Heating_WaterFields::MaximumWaterFlowRate, value);
}

bool CoilHeatingWater_Impl::isMaximumWaterFlowRateAutosized() const {
  if (const auto value = getString(openstudio::Coil_Heating_WaterFields::MaximumWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

void CoilHeatingWater_Impl::autosizeMaximumWaterFlowRate() {
  OS_ASSERT(setString(openstudio::Coil_Heating_WaterFields::MaximumWaterFlowRate, "autosize"));
}

boost::optional<double> CoilHeatingWater_Impl::autosizedMaximumWaterFlowRate() const {
  return boost::none;
}

std::string CoilHeatingWater_Impl::performanceInputMethod() const {
  const auto value = getString(openstudio::Coil_Heating_WaterFields::PerformanceInputMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWater_Impl::setPerformanceInputMethod(const std::string& value) {
  return setString(openstudio::Coil_Heating_WaterFields::PerformanceInputMethod, value);
}

boost::optional<double> CoilHeatingWater_Impl::ratedCapacity() const {
  return getDouble(openstudio::Coil_Heating_WaterFields::RatedCapacity, true);
}

bool CoilHeatingWater_Impl::setRatedCapacity(double value) {
  return setDouble(openstudio::Coil_Heating_WaterFields::RatedCapacity, value);
}

bool CoilHeatingWater_Impl::isRatedCapacityAutosized() const {
  if (const auto value = getString(openstudio::Coil_Heating_WaterFields::RatedCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

void CoilHeatingWater_Impl::autosizeRatedCapacity() {
  OS_ASSERT(setString(openstudio::Coil_Heating_WaterFields::RatedCapacity, "autosize"));
}

boost::optional<double> CoilHeatingWater_Impl::autosizedRatedCapacity() const {
  return boost::none;
}

double CoilHeatingWater_Impl::ratedInletWaterTemperature() const {
  const auto value = getDouble(openstudio::Coil_Heating_WaterFields::RatedInletWaterTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWater_Impl::setRatedInletWaterTemperature(double value) {
  return setDouble(openstudio::Coil_Heating_WaterFields::RatedInletWaterTemperature, value);
}

double CoilHeatingWater_Impl::ratedInletAirTemperature() const {
  const auto value = getDouble(openstudio::Coil_Heating_WaterFields::RatedInletAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWater_Impl::setRatedInletAirTemperature(double value) {
  return setDouble(openstudio::Coil_Heating_WaterFields::RatedInletAirTemperature, value);
}

double CoilHeatingWater_Impl::ratedOutletWaterTemperature() const {
  const auto value = getDouble(openstudio::Coil_Heating_WaterFields::RatedOutletWaterTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWater_Impl::setRatedOutletWaterTemperature(double value) {
  return setDouble(openstudio::Coil_Heating_WaterFields::RatedOutletWaterTemperature, value);
}

double CoilHeatingWater_Impl::ratedOutletAirTemperature() const {
  const auto value = getDouble(openstudio::Coil_Heating_WaterFields::RatedOutletAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWater_Impl::setRatedOutletAirTemperature(double value) {
  return setDouble(openstudio::Coil_Heating_WaterFields::RatedOutletAirTemperature, value);
}

double CoilHeatingWater_Impl::ratedRatioForAirAndWaterConvection() const {
  const auto value = getDouble(openstudio::Coil_Heating_WaterFields::RatedRatioforAirandWaterConvection, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWater_Impl::setRatedRatioForAirAndWaterConvection(double value) {
  return setDouble(openstudio::Coil_Heating_WaterFields::RatedRatioforAirandWaterConvection, value);
}

std::vector<std::string> CoilHeatingWater_Impl::performanceInputMethodValues() const {
  return CoilHeatingWater::performanceInputMethodValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
