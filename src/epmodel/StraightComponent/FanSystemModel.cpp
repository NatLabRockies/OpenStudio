/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/FanSystemModel.hpp"
#include "StraightComponent/FanSystemModel_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Model.hpp"
#include "Node.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Fan_SystemModel_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <stdexcept>

namespace openstudio {
namespace epmodel {

FanSystemModelSpeed::FanSystemModelSpeed(double flowFraction) : m_flowFraction(flowFraction) {
  if ((m_flowFraction < 0.0) || (m_flowFraction > 1.0)) {
    throw std::runtime_error("Unable to create FanSystemModelSpeed: flowFraction is outside the range [0, 1]");
  }
}

FanSystemModelSpeed::FanSystemModelSpeed(double flowFraction, double electricPowerFraction)
  : m_flowFraction(flowFraction), m_electricPowerFraction(electricPowerFraction) {
  if ((m_flowFraction < 0.0) || (m_flowFraction > 1.0)) {
    throw std::runtime_error("Unable to create FanSystemModelSpeed: flowFraction is outside the range [0, 1]");
  }
  if ((electricPowerFraction < 0.0) || (electricPowerFraction > 1.0)) {
    throw std::runtime_error("Unable to create FanSystemModelSpeed: electricPowerFraction is outside the range [0, 1]");
  }
}

double FanSystemModelSpeed::flowFraction() const {
  return m_flowFraction;
}

boost::optional<double> FanSystemModelSpeed::electricPowerFraction() const {
  return m_electricPowerFraction;
}

bool FanSystemModelSpeed::operator<(const FanSystemModelSpeed& other) const {
  return m_flowFraction < other.m_flowFraction;
}

std::ostream& operator<<(std::ostream& out, const FanSystemModelSpeed& speed) {
  out << "{flowFraction=" << speed.flowFraction();
  if (const auto electricPowerFraction = speed.electricPowerFraction()) {
    out << ", electricPowerFraction=" << *electricPowerFraction;
  }
  out << "}";
  return out;
}

FanSystemModel::FanSystemModel(const Model& model) : StraightComponent(FanSystemModel::iddObjectType(), model) {
  auto impl = getImpl<detail::FanSystemModel_Impl>();
  OS_ASSERT(impl);
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
  ScheduleConstant schedule(model);
  OS_ASSERT(schedule.setValue(1.0));
  OS_ASSERT(setAvailabilitySchedule(schedule));
  autosizeDesignMaximumAirFlowRate();
  OS_ASSERT(setDesignPressureRise(500.0));
  OS_ASSERT(setSpeedControlMethod("Discrete"));
  OS_ASSERT(setElectricPowerMinimumFlowRateFraction(0.2));
  OS_ASSERT(setMotorEfficiency(0.9));
  OS_ASSERT(setMotorInAirStreamFraction(1.0));
  autosizeDesignElectricPowerConsumption();
  OS_ASSERT(setElectricPowerPerUnitFlowRate(840.0));
  OS_ASSERT(setElectricPowerPerUnitFlowRatePerUnitPressure(1.66667));
  OS_ASSERT(setDesignPowerSizingMethod("PowerPerFlowPerPressure"));
  OS_ASSERT(setFanTotalEfficiency(0.7));
  OS_ASSERT(setMotorLossRadiativeFraction(0.0));
  OS_ASSERT(setEndUseSubcategory("General"));
}

FanSystemModel::FanSystemModel(std::shared_ptr<detail::FanSystemModel_Impl> impl) : StraightComponent(std::move(impl)) {}

IddObjectType FanSystemModel::iddObjectType() {
  return IddObjectType::Fan_SystemModel;
}

std::vector<std::string> FanSystemModel::speedControlMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Fan_SystemModelFields::SpeedControlMethod);
}

std::vector<std::string> FanSystemModel::designPowerSizingMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Fan_SystemModelFields::DesignPowerSizingMethod);
}

Schedule FanSystemModel::availabilitySchedule() const {
  return getImpl<detail::FanSystemModel_Impl>()->availabilitySchedule();
}

bool FanSystemModel::setAvailabilitySchedule(Schedule& schedule) {
  return getImpl<detail::FanSystemModel_Impl>()->setAvailabilitySchedule(schedule);
}

boost::optional<double> FanSystemModel::designMaximumAirFlowRate() const {
  return getImpl<detail::FanSystemModel_Impl>()->designMaximumAirFlowRate();
}

bool FanSystemModel::isDesignMaximumAirFlowRateAutosized() const {
  return getImpl<detail::FanSystemModel_Impl>()->isDesignMaximumAirFlowRateAutosized();
}

bool FanSystemModel::setDesignMaximumAirFlowRate(double designMaximumAirFlowRate) {
  return getImpl<detail::FanSystemModel_Impl>()->setDesignMaximumAirFlowRate(designMaximumAirFlowRate);
}

void FanSystemModel::autosizeDesignMaximumAirFlowRate() {
  getImpl<detail::FanSystemModel_Impl>()->autosizeDesignMaximumAirFlowRate();
}

std::string FanSystemModel::speedControlMethod() const {
  return getImpl<detail::FanSystemModel_Impl>()->speedControlMethod();
}

bool FanSystemModel::setSpeedControlMethod(const std::string& speedControlMethod) {
  return getImpl<detail::FanSystemModel_Impl>()->setSpeedControlMethod(speedControlMethod);
}

double FanSystemModel::electricPowerMinimumFlowRateFraction() const {
  return getImpl<detail::FanSystemModel_Impl>()->electricPowerMinimumFlowRateFraction();
}

bool FanSystemModel::setElectricPowerMinimumFlowRateFraction(double electricPowerMinimumFlowRateFraction) {
  return getImpl<detail::FanSystemModel_Impl>()->setElectricPowerMinimumFlowRateFraction(electricPowerMinimumFlowRateFraction);
}

double FanSystemModel::designPressureRise() const {
  return getImpl<detail::FanSystemModel_Impl>()->designPressureRise();
}

bool FanSystemModel::setDesignPressureRise(double designPressureRise) {
  return getImpl<detail::FanSystemModel_Impl>()->setDesignPressureRise(designPressureRise);
}

double FanSystemModel::motorEfficiency() const {
  return getImpl<detail::FanSystemModel_Impl>()->motorEfficiency();
}

bool FanSystemModel::setMotorEfficiency(double motorEfficiency) {
  return getImpl<detail::FanSystemModel_Impl>()->setMotorEfficiency(motorEfficiency);
}

double FanSystemModel::motorInAirStreamFraction() const {
  return getImpl<detail::FanSystemModel_Impl>()->motorInAirStreamFraction();
}

bool FanSystemModel::setMotorInAirStreamFraction(double motorInAirStreamFraction) {
  return getImpl<detail::FanSystemModel_Impl>()->setMotorInAirStreamFraction(motorInAirStreamFraction);
}

boost::optional<double> FanSystemModel::designElectricPowerConsumption() const {
  return getImpl<detail::FanSystemModel_Impl>()->designElectricPowerConsumption();
}

bool FanSystemModel::isDesignElectricPowerConsumptionAutosized() const {
  return getImpl<detail::FanSystemModel_Impl>()->isDesignElectricPowerConsumptionAutosized();
}

bool FanSystemModel::setDesignElectricPowerConsumption(double designElectricPowerConsumption) {
  return getImpl<detail::FanSystemModel_Impl>()->setDesignElectricPowerConsumption(designElectricPowerConsumption);
}

void FanSystemModel::autosizeDesignElectricPowerConsumption() {
  getImpl<detail::FanSystemModel_Impl>()->autosizeDesignElectricPowerConsumption();
}

std::string FanSystemModel::designPowerSizingMethod() const {
  return getImpl<detail::FanSystemModel_Impl>()->designPowerSizingMethod();
}

bool FanSystemModel::setDesignPowerSizingMethod(const std::string& designPowerSizingMethod) {
  return getImpl<detail::FanSystemModel_Impl>()->setDesignPowerSizingMethod(designPowerSizingMethod);
}

double FanSystemModel::electricPowerPerUnitFlowRate() const {
  return getImpl<detail::FanSystemModel_Impl>()->electricPowerPerUnitFlowRate();
}

bool FanSystemModel::setElectricPowerPerUnitFlowRate(double electricPowerPerUnitFlowRate) {
  return getImpl<detail::FanSystemModel_Impl>()->setElectricPowerPerUnitFlowRate(electricPowerPerUnitFlowRate);
}

double FanSystemModel::electricPowerPerUnitFlowRatePerUnitPressure() const {
  return getImpl<detail::FanSystemModel_Impl>()->electricPowerPerUnitFlowRatePerUnitPressure();
}

bool FanSystemModel::setElectricPowerPerUnitFlowRatePerUnitPressure(double electricPowerPerUnitFlowRatePerUnitPressure) {
  return getImpl<detail::FanSystemModel_Impl>()->setElectricPowerPerUnitFlowRatePerUnitPressure(electricPowerPerUnitFlowRatePerUnitPressure);
}

double FanSystemModel::fanTotalEfficiency() const {
  return getImpl<detail::FanSystemModel_Impl>()->fanTotalEfficiency();
}

bool FanSystemModel::setFanTotalEfficiency(double fanTotalEfficiency) {
  return getImpl<detail::FanSystemModel_Impl>()->setFanTotalEfficiency(fanTotalEfficiency);
}

boost::optional<Curve> FanSystemModel::electricPowerFunctionofFlowFractionCurve() const {
  return getImpl<detail::FanSystemModel_Impl>()->electricPowerFunctionofFlowFractionCurve();
}

bool FanSystemModel::setElectricPowerFunctionofFlowFractionCurve(const Curve& curve) {
  return getImpl<detail::FanSystemModel_Impl>()->setElectricPowerFunctionofFlowFractionCurve(curve);
}

void FanSystemModel::resetElectricPowerFunctionofFlowFractionCurve() {
  getImpl<detail::FanSystemModel_Impl>()->resetElectricPowerFunctionofFlowFractionCurve();
}

boost::optional<double> FanSystemModel::nightVentilationModePressureRise() const {
  return getImpl<detail::FanSystemModel_Impl>()->nightVentilationModePressureRise();
}

bool FanSystemModel::setNightVentilationModePressureRise(double nightVentilationModePressureRise) {
  return getImpl<detail::FanSystemModel_Impl>()->setNightVentilationModePressureRise(nightVentilationModePressureRise);
}

void FanSystemModel::resetNightVentilationModePressureRise() {
  getImpl<detail::FanSystemModel_Impl>()->resetNightVentilationModePressureRise();
}

boost::optional<double> FanSystemModel::nightVentilationModeFlowFraction() const {
  return getImpl<detail::FanSystemModel_Impl>()->nightVentilationModeFlowFraction();
}

bool FanSystemModel::setNightVentilationModeFlowFraction(double nightVentilationModeFlowFraction) {
  return getImpl<detail::FanSystemModel_Impl>()->setNightVentilationModeFlowFraction(nightVentilationModeFlowFraction);
}

void FanSystemModel::resetNightVentilationModeFlowFraction() {
  getImpl<detail::FanSystemModel_Impl>()->resetNightVentilationModeFlowFraction();
}

boost::optional<ThermalZone> FanSystemModel::motorLossZone() const {
  return getImpl<detail::FanSystemModel_Impl>()->motorLossZone();
}

bool FanSystemModel::setMotorLossZone(const ThermalZone& thermalZone) {
  return getImpl<detail::FanSystemModel_Impl>()->setMotorLossZone(thermalZone);
}

void FanSystemModel::resetMotorLossZone() {
  getImpl<detail::FanSystemModel_Impl>()->resetMotorLossZone();
}

double FanSystemModel::motorLossRadiativeFraction() const {
  return getImpl<detail::FanSystemModel_Impl>()->motorLossRadiativeFraction();
}

bool FanSystemModel::setMotorLossRadiativeFraction(double motorLossRadiativeFraction) {
  return getImpl<detail::FanSystemModel_Impl>()->setMotorLossRadiativeFraction(motorLossRadiativeFraction);
}

std::string FanSystemModel::endUseSubcategory() const {
  return getImpl<detail::FanSystemModel_Impl>()->endUseSubcategory();
}

bool FanSystemModel::setEndUseSubcategory(const std::string& endUseSubcategory) {
  return getImpl<detail::FanSystemModel_Impl>()->setEndUseSubcategory(endUseSubcategory);
}

unsigned FanSystemModel::numberofSpeeds() const {
  return getImpl<detail::FanSystemModel_Impl>()->numberofSpeeds();
}

std::vector<FanSystemModelSpeed> FanSystemModel::speeds() const {
  return getImpl<detail::FanSystemModel_Impl>()->speeds();
}

boost::optional<unsigned> FanSystemModel::speedIndex(const FanSystemModelSpeed& speed) const {
  return getImpl<detail::FanSystemModel_Impl>()->speedIndex(speed);
}

boost::optional<FanSystemModelSpeed> FanSystemModel::getSpeed(unsigned speedIndex) const {
  return getImpl<detail::FanSystemModel_Impl>()->getSpeed(speedIndex);
}

bool FanSystemModel::addSpeed(const FanSystemModelSpeed& speed) {
  return getImpl<detail::FanSystemModel_Impl>()->addSpeed(speed);
}

bool FanSystemModel::addSpeed(double flowFraction) {
  return getImpl<detail::FanSystemModel_Impl>()->addSpeed(flowFraction);
}

bool FanSystemModel::addSpeed(double flowFraction, double electricPowerFraction) {
  return getImpl<detail::FanSystemModel_Impl>()->addSpeed(flowFraction, electricPowerFraction);
}

bool FanSystemModel::removeSpeed(unsigned speedIndex) {
  return getImpl<detail::FanSystemModel_Impl>()->removeSpeed(speedIndex);
}

void FanSystemModel::removeAllSpeeds() {
  getImpl<detail::FanSystemModel_Impl>()->removeAllSpeeds();
}

bool FanSystemModel::setSpeeds(const std::vector<FanSystemModelSpeed>& speeds) {
  return getImpl<detail::FanSystemModel_Impl>()->setSpeeds(speeds);
}

bool FanSystemModel::addToNode(Node& node) {
  return getImpl<detail::FanSystemModel_Impl>()->addToNode(node);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned FanSystemModel_Impl::inletPort() const {
  return openstudio::Fan_SystemModelFields::AirInletNodeName;
}

unsigned FanSystemModel_Impl::outletPort() const {
  return openstudio::Fan_SystemModelFields::AirOutletNodeName;
}

bool FanSystemModel_Impl::addToNode(Node& node) {
  if (node.airLoopHVACOutdoorAirSystem()) {
    return StraightComponent_Impl::addToNode(node);
  }

  auto airLoop = node.airLoopHVAC();

  if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
    return false;
  }

  if (!StraightComponent_Impl::addToNode(node)) {
    return false;
  }

  auto airLoopImpl = airLoop->getImpl<detail::AirLoopHVAC_Impl>();
  OS_ASSERT(airLoopImpl);
  airLoopImpl->syncSetpointManagerMixedAirFanNodes();

  return true;
}

std::vector<std::string> FanSystemModel_Impl::speedControlMethodValues() const {
  return FanSystemModel::speedControlMethodValues();
}

std::vector<std::string> FanSystemModel_Impl::designPowerSizingMethodValues() const {
  return FanSystemModel::designPowerSizingMethodValues();
}

openstudio::epmodel::Schedule FanSystemModel_Impl::availabilitySchedule() const {
  auto value =
    getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Schedule>(openstudio::Fan_SystemModelFields::AvailabilityScheduleName);
  OS_ASSERT(value);
  return *value;
}

bool FanSystemModel_Impl::setAvailabilitySchedule(openstudio::epmodel::Schedule& schedule) {
  return ModelObject_Impl::setSchedule(openstudio::Fan_SystemModelFields::AvailabilityScheduleName, "FanSystemModel", "Availability",
                                       schedule);
}

boost::optional<double> FanSystemModel_Impl::designMaximumAirFlowRate() const {
  return getDouble(openstudio::Fan_SystemModelFields::DesignMaximumAirFlowRate, true);
}

bool FanSystemModel_Impl::isDesignMaximumAirFlowRateAutosized() const {
  if (const auto value = getString(openstudio::Fan_SystemModelFields::DesignMaximumAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool FanSystemModel_Impl::setDesignMaximumAirFlowRate(double designMaximumAirFlowRate) {
  return setDouble(openstudio::Fan_SystemModelFields::DesignMaximumAirFlowRate, designMaximumAirFlowRate);
}

void FanSystemModel_Impl::autosizeDesignMaximumAirFlowRate() {
  const bool result = setString(openstudio::Fan_SystemModelFields::DesignMaximumAirFlowRate, "autosize");
  OS_ASSERT(result);
}

std::string FanSystemModel_Impl::speedControlMethod() const {
  const auto value = getString(openstudio::Fan_SystemModelFields::SpeedControlMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool FanSystemModel_Impl::setSpeedControlMethod(const std::string& speedControlMethod) {
  return setString(openstudio::Fan_SystemModelFields::SpeedControlMethod, speedControlMethod);
}

double FanSystemModel_Impl::electricPowerMinimumFlowRateFraction() const {
  const auto value = getDouble(openstudio::Fan_SystemModelFields::ElectricPowerMinimumFlowRateFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool FanSystemModel_Impl::setElectricPowerMinimumFlowRateFraction(double electricPowerMinimumFlowRateFraction) {
  return setDouble(openstudio::Fan_SystemModelFields::ElectricPowerMinimumFlowRateFraction, electricPowerMinimumFlowRateFraction);
}

double FanSystemModel_Impl::designPressureRise() const {
  const auto value = getDouble(openstudio::Fan_SystemModelFields::DesignPressureRise, true);
  OS_ASSERT(value);
  return *value;
}

bool FanSystemModel_Impl::setDesignPressureRise(double designPressureRise) {
  return setDouble(openstudio::Fan_SystemModelFields::DesignPressureRise, designPressureRise);
}

double FanSystemModel_Impl::motorEfficiency() const {
  const auto value = getDouble(openstudio::Fan_SystemModelFields::MotorEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

bool FanSystemModel_Impl::setMotorEfficiency(double motorEfficiency) {
  return setDouble(openstudio::Fan_SystemModelFields::MotorEfficiency, motorEfficiency);
}

double FanSystemModel_Impl::motorInAirStreamFraction() const {
  const auto value = getDouble(openstudio::Fan_SystemModelFields::MotorInAirStreamFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool FanSystemModel_Impl::setMotorInAirStreamFraction(double motorInAirStreamFraction) {
  return setDouble(openstudio::Fan_SystemModelFields::MotorInAirStreamFraction, motorInAirStreamFraction);
}

boost::optional<double> FanSystemModel_Impl::designElectricPowerConsumption() const {
  return getDouble(openstudio::Fan_SystemModelFields::DesignElectricPowerConsumption, true);
}

bool FanSystemModel_Impl::isDesignElectricPowerConsumptionAutosized() const {
  if (const auto value = getString(openstudio::Fan_SystemModelFields::DesignElectricPowerConsumption, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool FanSystemModel_Impl::setDesignElectricPowerConsumption(double designElectricPowerConsumption) {
  return setDouble(openstudio::Fan_SystemModelFields::DesignElectricPowerConsumption, designElectricPowerConsumption);
}

void FanSystemModel_Impl::autosizeDesignElectricPowerConsumption() {
  const bool result = setString(openstudio::Fan_SystemModelFields::DesignElectricPowerConsumption, "autosize");
  OS_ASSERT(result);
}

std::string FanSystemModel_Impl::designPowerSizingMethod() const {
  const auto value = getString(openstudio::Fan_SystemModelFields::DesignPowerSizingMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool FanSystemModel_Impl::setDesignPowerSizingMethod(const std::string& designPowerSizingMethod) {
  return setString(openstudio::Fan_SystemModelFields::DesignPowerSizingMethod, designPowerSizingMethod);
}

double FanSystemModel_Impl::electricPowerPerUnitFlowRate() const {
  const auto value = getDouble(openstudio::Fan_SystemModelFields::ElectricPowerPerUnitFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

bool FanSystemModel_Impl::setElectricPowerPerUnitFlowRate(double electricPowerPerUnitFlowRate) {
  return setDouble(openstudio::Fan_SystemModelFields::ElectricPowerPerUnitFlowRate, electricPowerPerUnitFlowRate);
}

double FanSystemModel_Impl::electricPowerPerUnitFlowRatePerUnitPressure() const {
  const auto value = getDouble(openstudio::Fan_SystemModelFields::ElectricPowerPerUnitFlowRatePerUnitPressure, true);
  OS_ASSERT(value);
  return *value;
}

bool FanSystemModel_Impl::setElectricPowerPerUnitFlowRatePerUnitPressure(double electricPowerPerUnitFlowRatePerUnitPressure) {
  return setDouble(openstudio::Fan_SystemModelFields::ElectricPowerPerUnitFlowRatePerUnitPressure, electricPowerPerUnitFlowRatePerUnitPressure);
}

double FanSystemModel_Impl::fanTotalEfficiency() const {
  const auto value = getDouble(openstudio::Fan_SystemModelFields::FanTotalEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

bool FanSystemModel_Impl::setFanTotalEfficiency(double fanTotalEfficiency) {
  return setDouble(openstudio::Fan_SystemModelFields::FanTotalEfficiency, fanTotalEfficiency);
}

boost::optional<openstudio::epmodel::Curve> FanSystemModel_Impl::electricPowerFunctionofFlowFractionCurve() const {
  return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Curve>(
    openstudio::Fan_SystemModelFields::ElectricPowerFunctionofFlowFractionCurveName);
}

bool FanSystemModel_Impl::setElectricPowerFunctionofFlowFractionCurve(const openstudio::epmodel::Curve& curve) {
  return setPointer(openstudio::Fan_SystemModelFields::ElectricPowerFunctionofFlowFractionCurveName, curve.handle());
}

void FanSystemModel_Impl::resetElectricPowerFunctionofFlowFractionCurve() {
  const bool result = setString(openstudio::Fan_SystemModelFields::ElectricPowerFunctionofFlowFractionCurveName, "");
  OS_ASSERT(result);
}

boost::optional<double> FanSystemModel_Impl::nightVentilationModePressureRise() const {
  return getDouble(openstudio::Fan_SystemModelFields::NightVentilationModePressureRise, true);
}

bool FanSystemModel_Impl::setNightVentilationModePressureRise(double nightVentilationModePressureRise) {
  return setDouble(openstudio::Fan_SystemModelFields::NightVentilationModePressureRise, nightVentilationModePressureRise);
}

void FanSystemModel_Impl::resetNightVentilationModePressureRise() {
  const bool result = setString(openstudio::Fan_SystemModelFields::NightVentilationModePressureRise, "");
  OS_ASSERT(result);
}

boost::optional<double> FanSystemModel_Impl::nightVentilationModeFlowFraction() const {
  return getDouble(openstudio::Fan_SystemModelFields::NightVentilationModeFlowFraction, true);
}

bool FanSystemModel_Impl::setNightVentilationModeFlowFraction(double nightVentilationModeFlowFraction) {
  return setDouble(openstudio::Fan_SystemModelFields::NightVentilationModeFlowFraction, nightVentilationModeFlowFraction);
}

void FanSystemModel_Impl::resetNightVentilationModeFlowFraction() {
  const bool result = setString(openstudio::Fan_SystemModelFields::NightVentilationModeFlowFraction, "");
  OS_ASSERT(result);
}

boost::optional<openstudio::epmodel::ThermalZone> FanSystemModel_Impl::motorLossZone() const {
  return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::ThermalZone>(openstudio::Fan_SystemModelFields::MotorLossZoneName);
}

bool FanSystemModel_Impl::setMotorLossZone(const openstudio::epmodel::ThermalZone& thermalZone) {
  return setPointer(openstudio::Fan_SystemModelFields::MotorLossZoneName, thermalZone.handle());
}

void FanSystemModel_Impl::resetMotorLossZone() {
  const bool result = setString(openstudio::Fan_SystemModelFields::MotorLossZoneName, "");
  OS_ASSERT(result);
}

double FanSystemModel_Impl::motorLossRadiativeFraction() const {
  const auto value = getDouble(openstudio::Fan_SystemModelFields::MotorLossRadiativeFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool FanSystemModel_Impl::setMotorLossRadiativeFraction(double motorLossRadiativeFraction) {
  return setDouble(openstudio::Fan_SystemModelFields::MotorLossRadiativeFraction, motorLossRadiativeFraction);
}

std::string FanSystemModel_Impl::endUseSubcategory() const {
  const auto value = getString(openstudio::Fan_SystemModelFields::EndUseSubcategory, true);
  OS_ASSERT(value);
  return *value;
}

bool FanSystemModel_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
  const bool result = setString(openstudio::Fan_SystemModelFields::EndUseSubcategory, endUseSubcategory);
  OS_ASSERT(result);
  return result;
}

unsigned FanSystemModel_Impl::numberofSpeeds() const {
  return numExtensibleGroups();
}

boost::optional<unsigned> FanSystemModel_Impl::speedIndex(const openstudio::epmodel::FanSystemModelSpeed& speed) const {
  const auto flowFraction = openstudio::string_conversions::number(speed.flowFraction());
  for (unsigned i = 0; i < numExtensibleGroups(); ++i) {
    auto groups = extensibleGroups();
    if ((i < groups.size()) && (groups[i].getField(openstudio::Fan_SystemModelExtensibleFields::SpeedFlowFraction) == flowFraction)) {
      return i;
    }
  }
  return boost::none;
}

std::vector<openstudio::epmodel::FanSystemModelSpeed> FanSystemModel_Impl::speeds() const {
  std::vector<openstudio::epmodel::FanSystemModelSpeed> result;
  for (const auto& group : extensibleGroups()) {
    if (auto flowFraction = group.getDouble(openstudio::Fan_SystemModelExtensibleFields::SpeedFlowFraction)) {
      if (auto electricPowerFraction = group.getDouble(openstudio::Fan_SystemModelExtensibleFields::SpeedElectricPowerFraction)) {
        result.emplace_back(*flowFraction, *electricPowerFraction);
      } else {
        result.emplace_back(*flowFraction);
      }
    }
  }
  return result;
}

boost::optional<openstudio::epmodel::FanSystemModelSpeed> FanSystemModel_Impl::getSpeed(unsigned speedIndex) const {
  if (speedIndex >= numExtensibleGroups()) {
    return boost::none;
  }

  const auto groups = extensibleGroups();
  if (speedIndex >= groups.size()) {
    return boost::none;
  }

  auto flowFraction = groups[speedIndex].getDouble(openstudio::Fan_SystemModelExtensibleFields::SpeedFlowFraction);
  OS_ASSERT(flowFraction);
  if (auto electricPowerFraction = groups[speedIndex].getDouble(openstudio::Fan_SystemModelExtensibleFields::SpeedElectricPowerFraction)) {
    return openstudio::epmodel::FanSystemModelSpeed(*flowFraction, *electricPowerFraction);
  }
  return openstudio::epmodel::FanSystemModelSpeed(*flowFraction);
}

bool FanSystemModel_Impl::addSpeedPrivate(double flowFraction, boost::optional<double> electricPowerFraction) {
  auto group = getObject<ModelObject>().pushExtensibleGroup();
  const bool flowResult = group.setDouble(openstudio::Fan_SystemModelExtensibleFields::SpeedFlowFraction, flowFraction);
  const bool powerResult = electricPowerFraction
                             ? group.setDouble(openstudio::Fan_SystemModelExtensibleFields::SpeedElectricPowerFraction, *electricPowerFraction)
                             : group.setString(openstudio::Fan_SystemModelExtensibleFields::SpeedElectricPowerFraction, "");
  if (flowResult && powerResult) {
    return true;
  }
  getObject<ModelObject>().eraseExtensibleGroup(group.groupIndex());
  return false;
}

bool FanSystemModel_Impl::addSpeed(const openstudio::epmodel::FanSystemModelSpeed& speed) {
  auto currentSpeeds = speeds();
  currentSpeeds.push_back(speed);
  return setSpeeds(currentSpeeds);
}

bool FanSystemModel_Impl::addSpeed(double flowFraction) {
  return addSpeed(openstudio::epmodel::FanSystemModelSpeed(flowFraction));
}

bool FanSystemModel_Impl::addSpeed(double flowFraction, double electricPowerFraction) {
  return addSpeed(openstudio::epmodel::FanSystemModelSpeed(flowFraction, electricPowerFraction));
}

bool FanSystemModel_Impl::removeSpeed(unsigned speedIndex) {
  if (speedIndex >= numExtensibleGroups()) {
    return false;
  }
  return !getObject<ModelObject>().eraseExtensibleGroup(speedIndex).empty();
}

void FanSystemModel_Impl::removeAllSpeeds() {
  getObject<ModelObject>().clearExtensibleGroups();
}

bool FanSystemModel_Impl::setSpeeds(const std::vector<openstudio::epmodel::FanSystemModelSpeed>& speeds) {
  getObject<ModelObject>().clearExtensibleGroups();

  std::vector<std::pair<double, boost::optional<double>>> speedPairs;
  speedPairs.reserve(speeds.size());
  for (const auto& speed : speeds) {
    speedPairs.emplace_back(speed.flowFraction(), speed.electricPowerFraction());
  }
  std::sort(speedPairs.begin(), speedPairs.end());

  bool result = true;
  for (const auto& speedPair : speedPairs) {
    result = addSpeedPrivate(speedPair.first, speedPair.second) && result;
  }

  if (!electricPowerFunctionofFlowFractionCurve()) {
    for (const auto& group : extensibleGroups()) {
      if (group.isEmpty(openstudio::Fan_SystemModelExtensibleFields::SpeedElectricPowerFraction)) {
        LOG_FREE(Warn, "openstudio.epmodel.FanSystemModel",
                 "For " << briefDescription()
                        << ", you have speeds with blank ElectricPowerFraction but you did not assign an Electric Power Function of Flow Fraction Curve.");
        break;
      }
    }
  }

  return result;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
