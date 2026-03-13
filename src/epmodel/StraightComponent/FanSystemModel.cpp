/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/FanSystemModel.hpp"
#include "StraightComponent/FanSystemModel_Impl.hpp"

#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Model.hpp"
#include "Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Fan_SystemModel_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

FanSystemModel::FanSystemModel(const Model& model) : StraightComponent(FanSystemModel::iddObjectType(), model) {
  auto impl = getImpl<detail::FanSystemModel_Impl>();
  OS_ASSERT(impl);
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
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

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
