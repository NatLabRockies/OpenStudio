/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToAirComponent/CoilCoolingWater.hpp"
#include "WaterToAirComponent/CoilCoolingWater_Impl.hpp"

#include "HVACComponent/ControllerWaterCoil.hpp"
#include "HVACComponent/ControllerWaterCoil_Impl.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/CoilSystemCoolingWater.hpp"
#include "StraightComponent/CoilSystemCoolingWater_Impl.hpp"
#include "StraightComponent/CoilSystemCoolingWaterHeatExchangerAssisted.hpp"
#include "StraightComponent/CoilSystemCoolingWaterHeatExchangerAssisted_Impl.hpp"
#include "StraightComponent/Node.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/CoilSystem_Cooling_Water_FieldEnums.hxx>
#include <utilities/idd/CoilSystem_Cooling_Water_HeatExchangerAssisted_FieldEnums.hxx>
#include <utilities/idd/Coil_Cooling_Water_FieldEnums.hxx>
#include <utilities/idd/Controller_WaterCoil_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

namespace {

// EnergyPlus stores the controller-side relationship only through nodes.
// Matching the controller's actuator and sensor nodes against the coil's
// water inlet and air outlet gives us the same user-facing association
// without inventing a separate epmodel-only back-reference.
boost::optional<ControllerWaterCoil> inferControllerForCoil(const CoilCoolingWater& coil) {
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

// Canonical OpenStudio suppresses a dedicated ControllerWaterCoil when the
// cooling coil is already contained by CoilSystemCoolingWater, either directly
// or through CoilSystemCoolingWaterHeatExchangerAssisted. Epmodel does not yet
// expose those child relationships as first-class wrapper APIs, so the
// contained-system check follows the persisted EnergyPlus references instead.
bool isContainedByCoolingWaterSystem(const CoilCoolingWater& coil) {
  for (const auto& system : coil.model().getConcreteModelObjects<CoilSystemCoolingWater>()) {
    const auto directTarget =
      system.getModelObjectTarget<ModelObject>(openstudio::CoilSystem_Cooling_WaterFields::CoolingCoilName);
    if (directTarget && directTarget->handle() == coil.handle()) {
      return true;
    }

    const auto hxAssisted =
      system.getModelObjectTarget<CoilSystemCoolingWaterHeatExchangerAssisted>(openstudio::CoilSystem_Cooling_WaterFields::CoolingCoilName);
    if (!hxAssisted) {
      continue;
    }

    const auto nestedTarget = hxAssisted->getModelObjectTarget<ModelObject>(
      openstudio::CoilSystem_Cooling_Water_HeatExchangerAssistedFields::CoolingCoilName);
    if (nestedTarget && nestedTarget->handle() == coil.handle()) {
      return true;
    }
  }

  return false;
}

}  // namespace

CoilCoolingWater::CoilCoolingWater(const Model& model, Schedule& availabilitySchedule)
  : WaterToAirComponent(CoilCoolingWater::iddObjectType(), model) {
  OS_ASSERT(setAvailabilitySchedule(availabilitySchedule));
}

CoilCoolingWater::CoilCoolingWater(const Model& model) : WaterToAirComponent(CoilCoolingWater::iddObjectType(), model) {
  auto schedule = model.alwaysOnDiscreteSchedule();
  OS_ASSERT(setAvailabilitySchedule(schedule));
}

CoilCoolingWater::CoilCoolingWater(std::shared_ptr<detail::CoilCoolingWater_Impl> impl) : WaterToAirComponent(std::move(impl)) {}

IddObjectType CoilCoolingWater::iddObjectType() {
  return IddObjectType::Coil_Cooling_Water;
}

std::vector<std::string> CoilCoolingWater::typeOfAnalysisValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Coil_Cooling_WaterFields::TypeofAnalysis);
}

std::vector<std::string> CoilCoolingWater::heatExchangerConfigurationValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Coil_Cooling_WaterFields::HeatExchangerConfiguration);
}

Schedule CoilCoolingWater::availabilitySchedule() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->availabilitySchedule();
}

Schedule CoilCoolingWater::availableSchedule() const {
  return availabilitySchedule();
}

bool CoilCoolingWater::setAvailabilitySchedule(Schedule& schedule) {
  return getImpl<detail::CoilCoolingWater_Impl>()->setAvailabilitySchedule(schedule);
}

bool CoilCoolingWater::setAvailableSchedule(Schedule& schedule) {
  return setAvailabilitySchedule(schedule);
}

boost::optional<double> CoilCoolingWater::designWaterFlowRate() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->designWaterFlowRate();
}

boost::optional<double> CoilCoolingWater::autosizedDesignWaterFlowRate() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->autosizedDesignWaterFlowRate();
}

bool CoilCoolingWater::setDesignWaterFlowRate(double value) {
  return getImpl<detail::CoilCoolingWater_Impl>()->setDesignWaterFlowRate(value);
}

bool CoilCoolingWater::isDesignWaterFlowRateAutosized() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->isDesignWaterFlowRateAutosized();
}

void CoilCoolingWater::autosizeDesignWaterFlowRate() {
  getImpl<detail::CoilCoolingWater_Impl>()->autosizeDesignWaterFlowRate();
}

boost::optional<double> CoilCoolingWater::designAirFlowRate() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->designAirFlowRate();
}

boost::optional<double> CoilCoolingWater::autosizedDesignAirFlowRate() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->autosizedDesignAirFlowRate();
}

bool CoilCoolingWater::setDesignAirFlowRate(double value) {
  return getImpl<detail::CoilCoolingWater_Impl>()->setDesignAirFlowRate(value);
}

bool CoilCoolingWater::isDesignAirFlowRateAutosized() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->isDesignAirFlowRateAutosized();
}

void CoilCoolingWater::autosizeDesignAirFlowRate() {
  getImpl<detail::CoilCoolingWater_Impl>()->autosizeDesignAirFlowRate();
}

boost::optional<double> CoilCoolingWater::designInletWaterTemperature() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->designInletWaterTemperature();
}

boost::optional<double> CoilCoolingWater::autosizedDesignInletWaterTemperature() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->autosizedDesignInletWaterTemperature();
}

bool CoilCoolingWater::setDesignInletWaterTemperature(double value) {
  return getImpl<detail::CoilCoolingWater_Impl>()->setDesignInletWaterTemperature(value);
}

bool CoilCoolingWater::isDesignInletWaterTemperatureAutosized() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->isDesignInletWaterTemperatureAutosized();
}

void CoilCoolingWater::autosizeDesignInletWaterTemperature() {
  getImpl<detail::CoilCoolingWater_Impl>()->autosizeDesignInletWaterTemperature();
}

boost::optional<double> CoilCoolingWater::designInletAirTemperature() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->designInletAirTemperature();
}

boost::optional<double> CoilCoolingWater::autosizedDesignInletAirTemperature() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->autosizedDesignInletAirTemperature();
}

bool CoilCoolingWater::setDesignInletAirTemperature(double value) {
  return getImpl<detail::CoilCoolingWater_Impl>()->setDesignInletAirTemperature(value);
}

bool CoilCoolingWater::isDesignInletAirTemperatureAutosized() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->isDesignInletAirTemperatureAutosized();
}

void CoilCoolingWater::autosizeDesignInletAirTemperature() {
  getImpl<detail::CoilCoolingWater_Impl>()->autosizeDesignInletAirTemperature();
}

boost::optional<double> CoilCoolingWater::designOutletAirTemperature() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->designOutletAirTemperature();
}

boost::optional<double> CoilCoolingWater::autosizedDesignOutletAirTemperature() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->autosizedDesignOutletAirTemperature();
}

bool CoilCoolingWater::setDesignOutletAirTemperature(double value) {
  return getImpl<detail::CoilCoolingWater_Impl>()->setDesignOutletAirTemperature(value);
}

bool CoilCoolingWater::isDesignOutletAirTemperatureAutosized() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->isDesignOutletAirTemperatureAutosized();
}

void CoilCoolingWater::autosizeDesignOutletAirTemperature() {
  getImpl<detail::CoilCoolingWater_Impl>()->autosizeDesignOutletAirTemperature();
}

boost::optional<double> CoilCoolingWater::designInletAirHumidityRatio() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->designInletAirHumidityRatio();
}

boost::optional<double> CoilCoolingWater::autosizedDesignInletAirHumidityRatio() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->autosizedDesignInletAirHumidityRatio();
}

bool CoilCoolingWater::setDesignInletAirHumidityRatio(double value) {
  return getImpl<detail::CoilCoolingWater_Impl>()->setDesignInletAirHumidityRatio(value);
}

bool CoilCoolingWater::isDesignInletAirHumidityRatioAutosized() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->isDesignInletAirHumidityRatioAutosized();
}

void CoilCoolingWater::autosizeDesignInletAirHumidityRatio() {
  getImpl<detail::CoilCoolingWater_Impl>()->autosizeDesignInletAirHumidityRatio();
}

boost::optional<double> CoilCoolingWater::designOutletAirHumidityRatio() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->designOutletAirHumidityRatio();
}

boost::optional<double> CoilCoolingWater::autosizedDesignOutletAirHumidityRatio() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->autosizedDesignOutletAirHumidityRatio();
}

bool CoilCoolingWater::setDesignOutletAirHumidityRatio(double value) {
  return getImpl<detail::CoilCoolingWater_Impl>()->setDesignOutletAirHumidityRatio(value);
}

bool CoilCoolingWater::isDesignOutletAirHumidityRatioAutosized() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->isDesignOutletAirHumidityRatioAutosized();
}

void CoilCoolingWater::autosizeDesignOutletAirHumidityRatio() {
  getImpl<detail::CoilCoolingWater_Impl>()->autosizeDesignOutletAirHumidityRatio();
}

std::string CoilCoolingWater::typeOfAnalysis() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->typeOfAnalysis();
}

bool CoilCoolingWater::setTypeOfAnalysis(const std::string& value) {
  return getImpl<detail::CoilCoolingWater_Impl>()->setTypeOfAnalysis(value);
}

std::string CoilCoolingWater::heatExchangerConfiguration() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->heatExchangerConfiguration();
}

bool CoilCoolingWater::setHeatExchangerConfiguration(const std::string& value) {
  return getImpl<detail::CoilCoolingWater_Impl>()->setHeatExchangerConfiguration(value);
}

boost::optional<ControllerWaterCoil> CoilCoolingWater::controllerWaterCoil() const {
  return inferControllerForCoil(*this);
}

boost::optional<double> CoilCoolingWater::autosizedDesignCoilLoad() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->autosizedDesignCoilLoad();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned CoilCoolingWater_Impl::airInletPort() const {
  return openstudio::Coil_Cooling_WaterFields::AirInletNodeName;
}

unsigned CoilCoolingWater_Impl::airOutletPort() const {
  return openstudio::Coil_Cooling_WaterFields::AirOutletNodeName;
}

unsigned CoilCoolingWater_Impl::waterInletPort() const {
  return openstudio::Coil_Cooling_WaterFields::WaterInletNodeName;
}

unsigned CoilCoolingWater_Impl::waterOutletPort() const {
  return openstudio::Coil_Cooling_WaterFields::WaterOutletNodeName;
}

bool CoilCoolingWater_Impl::addToNode(Node& node) {
  const bool success = WaterToAirComponent_Impl::addToNode(node);
  if (!success) {
    return false;
  }

  if (containingZoneHVACComponent()) {
    return true;
  }

  auto thisCoil = getObject<openstudio::epmodel::CoilCoolingWater>();
  if (isContainedByCoolingWaterSystem(thisCoil)) {
    if (auto controller = inferControllerForCoil(thisCoil)) {
      controller->remove();
    }
    return true;
  }

  const auto waterInlet = thisCoil.waterInletModelObject();
  const auto airOutlet = thisCoil.airOutletModelObject();
  if (!waterInlet || !airOutlet) {
    return true;
  }

  if (auto controller = inferControllerForCoil(thisCoil)) {
    if (auto action = controller->action(); action && !openstudio::istringEqual(*action, "Reverse")) {
      LOG_FREE(Warn, "openstudio.epmodel.CoilCoolingWater",
               thisCoil.briefDescription() << " has an existing ControllerWaterCoil with action set to something other than 'Reverse'.");
    }
    OS_ASSERT(controller->setPointer(openstudio::Controller_WaterCoilFields::ActuatorNodeName, waterInlet->handle()));
    OS_ASSERT(controller->setPointer(openstudio::Controller_WaterCoilFields::SensorNodeName, airOutlet->handle()));
    return true;
  }

  ControllerWaterCoil controller(model());
  OS_ASSERT(controller.setAction("Reverse"));
  OS_ASSERT(controller.setPointer(openstudio::Controller_WaterCoilFields::ActuatorNodeName, waterInlet->handle()));
  OS_ASSERT(controller.setPointer(openstudio::Controller_WaterCoilFields::SensorNodeName, airOutlet->handle()));
  return true;
}

bool CoilCoolingWater_Impl::removeFromPlantLoop() {
  if (auto controller = inferControllerForCoil(getObject<openstudio::epmodel::CoilCoolingWater>())) {
    controller->remove();
  }
  return WaterToAirComponent_Impl::removeFromPlantLoop();
}

Schedule CoilCoolingWater_Impl::availabilitySchedule() const {
  auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Coil_Cooling_WaterFields::AvailabilityScheduleName);
  if (!schedule) {
    LOG_FREE(Error, "openstudio.epmodel.CoilCoolingWater",
             "Required availability schedule not set, returning the model always-on discrete schedule without repairing persisted state");
    schedule = model().alwaysOnDiscreteSchedule();
  }
  OS_ASSERT(schedule);
  return *schedule;
}

bool CoilCoolingWater_Impl::setAvailabilitySchedule(Schedule& schedule) {
  return setSchedule(openstudio::Coil_Cooling_WaterFields::AvailabilityScheduleName, "CoilCoolingWater", "Availability", schedule);
}

boost::optional<double> CoilCoolingWater_Impl::designWaterFlowRate() const {
  return getDouble(openstudio::Coil_Cooling_WaterFields::DesignWaterFlowRate, true);
}

boost::optional<double> CoilCoolingWater_Impl::autosizedDesignWaterFlowRate() const {
  return boost::none;
}

bool CoilCoolingWater_Impl::setDesignWaterFlowRate(double value) {
  return setDouble(openstudio::Coil_Cooling_WaterFields::DesignWaterFlowRate, value);
}

bool CoilCoolingWater_Impl::isDesignWaterFlowRateAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_WaterFields::DesignWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

void CoilCoolingWater_Impl::autosizeDesignWaterFlowRate() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterFields::DesignWaterFlowRate, "autosize"));
}

boost::optional<double> CoilCoolingWater_Impl::designAirFlowRate() const {
  return getDouble(openstudio::Coil_Cooling_WaterFields::DesignAirFlowRate, true);
}

boost::optional<double> CoilCoolingWater_Impl::autosizedDesignAirFlowRate() const {
  return boost::none;
}

bool CoilCoolingWater_Impl::setDesignAirFlowRate(double value) {
  return setDouble(openstudio::Coil_Cooling_WaterFields::DesignAirFlowRate, value);
}

bool CoilCoolingWater_Impl::isDesignAirFlowRateAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_WaterFields::DesignAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

void CoilCoolingWater_Impl::autosizeDesignAirFlowRate() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterFields::DesignAirFlowRate, "autosize"));
}

boost::optional<double> CoilCoolingWater_Impl::designInletWaterTemperature() const {
  return getDouble(openstudio::Coil_Cooling_WaterFields::DesignInletWaterTemperature, true);
}

boost::optional<double> CoilCoolingWater_Impl::autosizedDesignInletWaterTemperature() const {
  return boost::none;
}

bool CoilCoolingWater_Impl::setDesignInletWaterTemperature(double value) {
  return setDouble(openstudio::Coil_Cooling_WaterFields::DesignInletWaterTemperature, value);
}

bool CoilCoolingWater_Impl::isDesignInletWaterTemperatureAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_WaterFields::DesignInletWaterTemperature, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

void CoilCoolingWater_Impl::autosizeDesignInletWaterTemperature() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterFields::DesignInletWaterTemperature, "autosize"));
}

boost::optional<double> CoilCoolingWater_Impl::designInletAirTemperature() const {
  return getDouble(openstudio::Coil_Cooling_WaterFields::DesignInletAirTemperature, true);
}

boost::optional<double> CoilCoolingWater_Impl::autosizedDesignInletAirTemperature() const {
  return boost::none;
}

bool CoilCoolingWater_Impl::setDesignInletAirTemperature(double value) {
  return setDouble(openstudio::Coil_Cooling_WaterFields::DesignInletAirTemperature, value);
}

bool CoilCoolingWater_Impl::isDesignInletAirTemperatureAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_WaterFields::DesignInletAirTemperature, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

void CoilCoolingWater_Impl::autosizeDesignInletAirTemperature() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterFields::DesignInletAirTemperature, "autosize"));
}

boost::optional<double> CoilCoolingWater_Impl::designOutletAirTemperature() const {
  return getDouble(openstudio::Coil_Cooling_WaterFields::DesignOutletAirTemperature, true);
}

boost::optional<double> CoilCoolingWater_Impl::autosizedDesignOutletAirTemperature() const {
  return boost::none;
}

bool CoilCoolingWater_Impl::setDesignOutletAirTemperature(double value) {
  return setDouble(openstudio::Coil_Cooling_WaterFields::DesignOutletAirTemperature, value);
}

bool CoilCoolingWater_Impl::isDesignOutletAirTemperatureAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_WaterFields::DesignOutletAirTemperature, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

void CoilCoolingWater_Impl::autosizeDesignOutletAirTemperature() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterFields::DesignOutletAirTemperature, "autosize"));
}

boost::optional<double> CoilCoolingWater_Impl::designInletAirHumidityRatio() const {
  return getDouble(openstudio::Coil_Cooling_WaterFields::DesignInletAirHumidityRatio, true);
}

boost::optional<double> CoilCoolingWater_Impl::autosizedDesignInletAirHumidityRatio() const {
  return boost::none;
}

bool CoilCoolingWater_Impl::setDesignInletAirHumidityRatio(double value) {
  return setDouble(openstudio::Coil_Cooling_WaterFields::DesignInletAirHumidityRatio, value);
}

bool CoilCoolingWater_Impl::isDesignInletAirHumidityRatioAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_WaterFields::DesignInletAirHumidityRatio, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

void CoilCoolingWater_Impl::autosizeDesignInletAirHumidityRatio() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterFields::DesignInletAirHumidityRatio, "autosize"));
}

boost::optional<double> CoilCoolingWater_Impl::designOutletAirHumidityRatio() const {
  return getDouble(openstudio::Coil_Cooling_WaterFields::DesignOutletAirHumidityRatio, true);
}

boost::optional<double> CoilCoolingWater_Impl::autosizedDesignOutletAirHumidityRatio() const {
  return boost::none;
}

bool CoilCoolingWater_Impl::setDesignOutletAirHumidityRatio(double value) {
  return setDouble(openstudio::Coil_Cooling_WaterFields::DesignOutletAirHumidityRatio, value);
}

bool CoilCoolingWater_Impl::isDesignOutletAirHumidityRatioAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_WaterFields::DesignOutletAirHumidityRatio, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

void CoilCoolingWater_Impl::autosizeDesignOutletAirHumidityRatio() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterFields::DesignOutletAirHumidityRatio, "autosize"));
}

std::string CoilCoolingWater_Impl::typeOfAnalysis() const {
  const auto value = getString(openstudio::Coil_Cooling_WaterFields::TypeofAnalysis, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWater_Impl::setTypeOfAnalysis(const std::string& value) {
  return setString(openstudio::Coil_Cooling_WaterFields::TypeofAnalysis, value);
}

std::string CoilCoolingWater_Impl::heatExchangerConfiguration() const {
  const auto value = getString(openstudio::Coil_Cooling_WaterFields::HeatExchangerConfiguration, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWater_Impl::setHeatExchangerConfiguration(const std::string& value) {
  return setString(openstudio::Coil_Cooling_WaterFields::HeatExchangerConfiguration, value);
}

std::vector<std::string> CoilCoolingWater_Impl::typeOfAnalysisValues() const {
  return CoilCoolingWater::typeOfAnalysisValues();
}

std::vector<std::string> CoilCoolingWater_Impl::heatExchangerConfigurationValues() const {
  return CoilCoolingWater::heatExchangerConfigurationValues();
}

boost::optional<double> CoilCoolingWater_Impl::autosizedDesignCoilLoad() const {
  return boost::none;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
