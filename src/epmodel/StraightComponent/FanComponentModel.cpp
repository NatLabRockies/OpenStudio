/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/FanComponentModel.hpp"
#include "StraightComponent/FanComponentModel_Impl.hpp"

#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Model.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Fan_ComponentModel_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

FanComponentModel::FanComponentModel(const Model& model) : StraightComponent(FanComponentModel::iddObjectType(), model) {
  auto impl = getImpl<detail::FanComponentModel_Impl>();
  OS_ASSERT(impl);
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

FanComponentModel::FanComponentModel(std::shared_ptr<detail::FanComponentModel_Impl> impl) : StraightComponent(std::move(impl)) {}

IddObjectType FanComponentModel::iddObjectType() {
  return IddObjectType::Fan_ComponentModel;
}

bool FanComponentModel::addToNode(Node& node) {
  return getImpl<detail::FanComponentModel_Impl>()->addToNode(node);
}

std::vector<std::string> FanComponentModel::vFDEfficiencyTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Fan_ComponentModelFields::VFDEfficiencyType);
}

boost::optional<double> FanComponentModel::maximumFlowRate() const {
  return getImpl<detail::FanComponentModel_Impl>()->maximumFlowRate();
}

bool FanComponentModel::isMaximumFlowRateAutosized() const {
  return getImpl<detail::FanComponentModel_Impl>()->isMaximumFlowRateAutosized();
}

bool FanComponentModel::setMaximumFlowRate(double maximumFlowRate) {
  return getImpl<detail::FanComponentModel_Impl>()->setMaximumFlowRate(maximumFlowRate);
}

void FanComponentModel::autosizeMaximumFlowRate() {
  getImpl<detail::FanComponentModel_Impl>()->autosizeMaximumFlowRate();
}

boost::optional<double> FanComponentModel::minimumFlowRate() const {
  return getImpl<detail::FanComponentModel_Impl>()->minimumFlowRate();
}

bool FanComponentModel::isMinimumFlowRateAutosized() const {
  return getImpl<detail::FanComponentModel_Impl>()->isMinimumFlowRateAutosized();
}

bool FanComponentModel::setMinimumFlowRate(double minimumFlowRate) {
  return getImpl<detail::FanComponentModel_Impl>()->setMinimumFlowRate(minimumFlowRate);
}

void FanComponentModel::autosizeMinimumFlowRate() {
  getImpl<detail::FanComponentModel_Impl>()->autosizeMinimumFlowRate();
}

double FanComponentModel::fanSizingFactor() const {
  return getImpl<detail::FanComponentModel_Impl>()->fanSizingFactor();
}

bool FanComponentModel::setFanSizingFactor(double fanSizingFactor) {
  return getImpl<detail::FanComponentModel_Impl>()->setFanSizingFactor(fanSizingFactor);
}

double FanComponentModel::fanWheelDiameter() const {
  return getImpl<detail::FanComponentModel_Impl>()->fanWheelDiameter();
}

bool FanComponentModel::setFanWheelDiameter(double fanWheelDiameter) {
  return getImpl<detail::FanComponentModel_Impl>()->setFanWheelDiameter(fanWheelDiameter);
}

double FanComponentModel::fanOutletArea() const {
  return getImpl<detail::FanComponentModel_Impl>()->fanOutletArea();
}

bool FanComponentModel::setFanOutletArea(double fanOutletArea) {
  return getImpl<detail::FanComponentModel_Impl>()->setFanOutletArea(fanOutletArea);
}

double FanComponentModel::maximumFanStaticEfficiency() const {
  return getImpl<detail::FanComponentModel_Impl>()->maximumFanStaticEfficiency();
}

bool FanComponentModel::setMaximumFanStaticEfficiency(double maximumFanStaticEfficiency) {
  return getImpl<detail::FanComponentModel_Impl>()->setMaximumFanStaticEfficiency(maximumFanStaticEfficiency);
}

double FanComponentModel::eulerNumberatMaximumFanStaticEfficiency() const {
  return getImpl<detail::FanComponentModel_Impl>()->eulerNumberatMaximumFanStaticEfficiency();
}

bool FanComponentModel::setEulerNumberatMaximumFanStaticEfficiency(double eulerNumberatMaximumFanStaticEfficiency) {
  return getImpl<detail::FanComponentModel_Impl>()->setEulerNumberatMaximumFanStaticEfficiency(eulerNumberatMaximumFanStaticEfficiency);
}

double FanComponentModel::maximumDimensionlessFanAirflow() const {
  return getImpl<detail::FanComponentModel_Impl>()->maximumDimensionlessFanAirflow();
}

bool FanComponentModel::setMaximumDimensionlessFanAirflow(double maximumDimensionlessFanAirflow) {
  return getImpl<detail::FanComponentModel_Impl>()->setMaximumDimensionlessFanAirflow(maximumDimensionlessFanAirflow);
}

boost::optional<double> FanComponentModel::motorFanPulleyRatio() const {
  return getImpl<detail::FanComponentModel_Impl>()->motorFanPulleyRatio();
}

bool FanComponentModel::isMotorFanPulleyRatioAutosized() const {
  return getImpl<detail::FanComponentModel_Impl>()->isMotorFanPulleyRatioAutosized();
}

bool FanComponentModel::setMotorFanPulleyRatio(double motorFanPulleyRatio) {
  return getImpl<detail::FanComponentModel_Impl>()->setMotorFanPulleyRatio(motorFanPulleyRatio);
}

void FanComponentModel::autosizeMotorFanPulleyRatio() {
  getImpl<detail::FanComponentModel_Impl>()->autosizeMotorFanPulleyRatio();
}

boost::optional<double> FanComponentModel::beltMaximumTorque() const {
  return getImpl<detail::FanComponentModel_Impl>()->beltMaximumTorque();
}

bool FanComponentModel::isBeltMaximumTorqueAutosized() const {
  return getImpl<detail::FanComponentModel_Impl>()->isBeltMaximumTorqueAutosized();
}

bool FanComponentModel::setBeltMaximumTorque(double beltMaximumTorque) {
  return getImpl<detail::FanComponentModel_Impl>()->setBeltMaximumTorque(beltMaximumTorque);
}

void FanComponentModel::autosizeBeltMaximumTorque() {
  getImpl<detail::FanComponentModel_Impl>()->autosizeBeltMaximumTorque();
}

double FanComponentModel::beltSizingFactor() const {
  return getImpl<detail::FanComponentModel_Impl>()->beltSizingFactor();
}

bool FanComponentModel::setBeltSizingFactor(double beltSizingFactor) {
  return getImpl<detail::FanComponentModel_Impl>()->setBeltSizingFactor(beltSizingFactor);
}

double FanComponentModel::beltFractionalTorqueTransition() const {
  return getImpl<detail::FanComponentModel_Impl>()->beltFractionalTorqueTransition();
}

bool FanComponentModel::setBeltFractionalTorqueTransition(double beltFractionalTorqueTransition) {
  return getImpl<detail::FanComponentModel_Impl>()->setBeltFractionalTorqueTransition(beltFractionalTorqueTransition);
}

double FanComponentModel::motorMaximumSpeed() const {
  return getImpl<detail::FanComponentModel_Impl>()->motorMaximumSpeed();
}

bool FanComponentModel::setMotorMaximumSpeed(double motorMaximumSpeed) {
  return getImpl<detail::FanComponentModel_Impl>()->setMotorMaximumSpeed(motorMaximumSpeed);
}

boost::optional<double> FanComponentModel::maximumMotorOutputPower() const {
  return getImpl<detail::FanComponentModel_Impl>()->maximumMotorOutputPower();
}

bool FanComponentModel::isMaximumMotorOutputPowerAutosized() const {
  return getImpl<detail::FanComponentModel_Impl>()->isMaximumMotorOutputPowerAutosized();
}

bool FanComponentModel::setMaximumMotorOutputPower(double maximumMotorOutputPower) {
  return getImpl<detail::FanComponentModel_Impl>()->setMaximumMotorOutputPower(maximumMotorOutputPower);
}

void FanComponentModel::autosizeMaximumMotorOutputPower() {
  getImpl<detail::FanComponentModel_Impl>()->autosizeMaximumMotorOutputPower();
}

double FanComponentModel::motorSizingFactor() const {
  return getImpl<detail::FanComponentModel_Impl>()->motorSizingFactor();
}

bool FanComponentModel::setMotorSizingFactor(double motorSizingFactor) {
  return getImpl<detail::FanComponentModel_Impl>()->setMotorSizingFactor(motorSizingFactor);
}

double FanComponentModel::motorInAirstreamFraction() const {
  return getImpl<detail::FanComponentModel_Impl>()->motorInAirstreamFraction();
}

bool FanComponentModel::setMotorInAirstreamFraction(double motorInAirstreamFraction) {
  return getImpl<detail::FanComponentModel_Impl>()->setMotorInAirstreamFraction(motorInAirstreamFraction);
}

std::string FanComponentModel::vFDEfficiencyType() const {
  return getImpl<detail::FanComponentModel_Impl>()->vFDEfficiencyType();
}

bool FanComponentModel::setVFDEfficiencyType(const std::string& vFDEfficiencyType) {
  return getImpl<detail::FanComponentModel_Impl>()->setVFDEfficiencyType(vFDEfficiencyType);
}

boost::optional<double> FanComponentModel::maximumVFDOutputPower() const {
  return getImpl<detail::FanComponentModel_Impl>()->maximumVFDOutputPower();
}

bool FanComponentModel::isMaximumVFDOutputPowerAutosized() const {
  return getImpl<detail::FanComponentModel_Impl>()->isMaximumVFDOutputPowerAutosized();
}

bool FanComponentModel::setMaximumVFDOutputPower(double maximumVFDOutputPower) {
  return getImpl<detail::FanComponentModel_Impl>()->setMaximumVFDOutputPower(maximumVFDOutputPower);
}

void FanComponentModel::autosizeMaximumVFDOutputPower() {
  getImpl<detail::FanComponentModel_Impl>()->autosizeMaximumVFDOutputPower();
}

double FanComponentModel::vFDSizingFactor() const {
  return getImpl<detail::FanComponentModel_Impl>()->vFDSizingFactor();
}

bool FanComponentModel::setVFDSizingFactor(double vFDSizingFactor) {
  return getImpl<detail::FanComponentModel_Impl>()->setVFDSizingFactor(vFDSizingFactor);
}

std::string FanComponentModel::endUseSubcategory() const {
  return getImpl<detail::FanComponentModel_Impl>()->endUseSubcategory();
}

bool FanComponentModel::setEndUseSubcategory(const std::string& endUseSubcategory) {
  return getImpl<detail::FanComponentModel_Impl>()->setEndUseSubcategory(endUseSubcategory);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned FanComponentModel_Impl::inletPort() const {
  return openstudio::Fan_ComponentModelFields::AirInletNodeName;
}

unsigned FanComponentModel_Impl::outletPort() const {
  return openstudio::Fan_ComponentModelFields::AirOutletNodeName;
}

bool FanComponentModel_Impl::addToNode(Node& node) {
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

std::vector<std::string> FanComponentModel_Impl::vFDEfficiencyTypeValues() const {
  return FanComponentModel::vFDEfficiencyTypeValues();
}

boost::optional<double> FanComponentModel_Impl::maximumFlowRate() const {
  return getDouble(openstudio::Fan_ComponentModelFields::MaximumFlowRate, true);
}

bool FanComponentModel_Impl::isMaximumFlowRateAutosized() const {
  if (const auto value = getString(openstudio::Fan_ComponentModelFields::MaximumFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool FanComponentModel_Impl::setMaximumFlowRate(double maximumFlowRate) {
  return setDouble(openstudio::Fan_ComponentModelFields::MaximumFlowRate, maximumFlowRate);
}

void FanComponentModel_Impl::autosizeMaximumFlowRate() {
  const bool result = setString(openstudio::Fan_ComponentModelFields::MaximumFlowRate, "autosize");
  OS_ASSERT(result);
}

boost::optional<double> FanComponentModel_Impl::minimumFlowRate() const {
  return getDouble(openstudio::Fan_ComponentModelFields::MinimumFlowRate, true);
}

bool FanComponentModel_Impl::isMinimumFlowRateAutosized() const {
  if (const auto value = getString(openstudio::Fan_ComponentModelFields::MinimumFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool FanComponentModel_Impl::setMinimumFlowRate(double minimumFlowRate) {
  return setDouble(openstudio::Fan_ComponentModelFields::MinimumFlowRate, minimumFlowRate);
}

void FanComponentModel_Impl::autosizeMinimumFlowRate() {
  const bool result = setString(openstudio::Fan_ComponentModelFields::MinimumFlowRate, "autosize");
  OS_ASSERT(result);
}

double FanComponentModel_Impl::fanSizingFactor() const {
  const auto value = getDouble(openstudio::Fan_ComponentModelFields::FanSizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool FanComponentModel_Impl::setFanSizingFactor(double fanSizingFactor) {
  return setDouble(openstudio::Fan_ComponentModelFields::FanSizingFactor, fanSizingFactor);
}

double FanComponentModel_Impl::fanWheelDiameter() const {
  const auto value = getDouble(openstudio::Fan_ComponentModelFields::FanWheelDiameter, true);
  OS_ASSERT(value);
  return *value;
}

bool FanComponentModel_Impl::setFanWheelDiameter(double fanWheelDiameter) {
  return setDouble(openstudio::Fan_ComponentModelFields::FanWheelDiameter, fanWheelDiameter);
}

double FanComponentModel_Impl::fanOutletArea() const {
  const auto value = getDouble(openstudio::Fan_ComponentModelFields::FanOutletArea, true);
  OS_ASSERT(value);
  return *value;
}

bool FanComponentModel_Impl::setFanOutletArea(double fanOutletArea) {
  return setDouble(openstudio::Fan_ComponentModelFields::FanOutletArea, fanOutletArea);
}

double FanComponentModel_Impl::maximumFanStaticEfficiency() const {
  const auto value = getDouble(openstudio::Fan_ComponentModelFields::MaximumFanStaticEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

bool FanComponentModel_Impl::setMaximumFanStaticEfficiency(double maximumFanStaticEfficiency) {
  return setDouble(openstudio::Fan_ComponentModelFields::MaximumFanStaticEfficiency, maximumFanStaticEfficiency);
}

double FanComponentModel_Impl::eulerNumberatMaximumFanStaticEfficiency() const {
  const auto value = getDouble(openstudio::Fan_ComponentModelFields::EulerNumberatMaximumFanStaticEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

bool FanComponentModel_Impl::setEulerNumberatMaximumFanStaticEfficiency(double eulerNumberatMaximumFanStaticEfficiency) {
  return setDouble(openstudio::Fan_ComponentModelFields::EulerNumberatMaximumFanStaticEfficiency, eulerNumberatMaximumFanStaticEfficiency);
}

double FanComponentModel_Impl::maximumDimensionlessFanAirflow() const {
  const auto value = getDouble(openstudio::Fan_ComponentModelFields::MaximumDimensionlessFanAirflow, true);
  OS_ASSERT(value);
  return *value;
}

bool FanComponentModel_Impl::setMaximumDimensionlessFanAirflow(double maximumDimensionlessFanAirflow) {
  return setDouble(openstudio::Fan_ComponentModelFields::MaximumDimensionlessFanAirflow, maximumDimensionlessFanAirflow);
}

boost::optional<double> FanComponentModel_Impl::motorFanPulleyRatio() const {
  return getDouble(openstudio::Fan_ComponentModelFields::MotorFanPulleyRatio, true);
}

bool FanComponentModel_Impl::isMotorFanPulleyRatioAutosized() const {
  if (const auto value = getString(openstudio::Fan_ComponentModelFields::MotorFanPulleyRatio, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool FanComponentModel_Impl::setMotorFanPulleyRatio(double motorFanPulleyRatio) {
  return setDouble(openstudio::Fan_ComponentModelFields::MotorFanPulleyRatio, motorFanPulleyRatio);
}

void FanComponentModel_Impl::autosizeMotorFanPulleyRatio() {
  const bool result = setString(openstudio::Fan_ComponentModelFields::MotorFanPulleyRatio, "autosize");
  OS_ASSERT(result);
}

boost::optional<double> FanComponentModel_Impl::beltMaximumTorque() const {
  return getDouble(openstudio::Fan_ComponentModelFields::BeltMaximumTorque, true);
}

bool FanComponentModel_Impl::isBeltMaximumTorqueAutosized() const {
  if (const auto value = getString(openstudio::Fan_ComponentModelFields::BeltMaximumTorque, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool FanComponentModel_Impl::setBeltMaximumTorque(double beltMaximumTorque) {
  return setDouble(openstudio::Fan_ComponentModelFields::BeltMaximumTorque, beltMaximumTorque);
}

void FanComponentModel_Impl::autosizeBeltMaximumTorque() {
  const bool result = setString(openstudio::Fan_ComponentModelFields::BeltMaximumTorque, "autosize");
  OS_ASSERT(result);
}

double FanComponentModel_Impl::beltSizingFactor() const {
  const auto value = getDouble(openstudio::Fan_ComponentModelFields::BeltSizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool FanComponentModel_Impl::setBeltSizingFactor(double beltSizingFactor) {
  return setDouble(openstudio::Fan_ComponentModelFields::BeltSizingFactor, beltSizingFactor);
}

double FanComponentModel_Impl::beltFractionalTorqueTransition() const {
  const auto value = getDouble(openstudio::Fan_ComponentModelFields::BeltFractionalTorqueTransition, true);
  OS_ASSERT(value);
  return *value;
}

bool FanComponentModel_Impl::setBeltFractionalTorqueTransition(double beltFractionalTorqueTransition) {
  return setDouble(openstudio::Fan_ComponentModelFields::BeltFractionalTorqueTransition, beltFractionalTorqueTransition);
}

double FanComponentModel_Impl::motorMaximumSpeed() const {
  const auto value = getDouble(openstudio::Fan_ComponentModelFields::MotorMaximumSpeed, true);
  OS_ASSERT(value);
  return *value;
}

bool FanComponentModel_Impl::setMotorMaximumSpeed(double motorMaximumSpeed) {
  return setDouble(openstudio::Fan_ComponentModelFields::MotorMaximumSpeed, motorMaximumSpeed);
}

boost::optional<double> FanComponentModel_Impl::maximumMotorOutputPower() const {
  return getDouble(openstudio::Fan_ComponentModelFields::MaximumMotorOutputPower, true);
}

bool FanComponentModel_Impl::isMaximumMotorOutputPowerAutosized() const {
  if (const auto value = getString(openstudio::Fan_ComponentModelFields::MaximumMotorOutputPower, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool FanComponentModel_Impl::setMaximumMotorOutputPower(double maximumMotorOutputPower) {
  return setDouble(openstudio::Fan_ComponentModelFields::MaximumMotorOutputPower, maximumMotorOutputPower);
}

void FanComponentModel_Impl::autosizeMaximumMotorOutputPower() {
  const bool result = setString(openstudio::Fan_ComponentModelFields::MaximumMotorOutputPower, "autosize");
  OS_ASSERT(result);
}

double FanComponentModel_Impl::motorSizingFactor() const {
  const auto value = getDouble(openstudio::Fan_ComponentModelFields::MotorSizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool FanComponentModel_Impl::setMotorSizingFactor(double motorSizingFactor) {
  return setDouble(openstudio::Fan_ComponentModelFields::MotorSizingFactor, motorSizingFactor);
}

double FanComponentModel_Impl::motorInAirstreamFraction() const {
  const auto value = getDouble(openstudio::Fan_ComponentModelFields::MotorInAirstreamFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool FanComponentModel_Impl::setMotorInAirstreamFraction(double motorInAirstreamFraction) {
  return setDouble(openstudio::Fan_ComponentModelFields::MotorInAirstreamFraction, motorInAirstreamFraction);
}

std::string FanComponentModel_Impl::vFDEfficiencyType() const {
  const auto value = getString(openstudio::Fan_ComponentModelFields::VFDEfficiencyType, true);
  OS_ASSERT(value);
  return *value;
}

bool FanComponentModel_Impl::setVFDEfficiencyType(const std::string& vFDEfficiencyType) {
  return setString(openstudio::Fan_ComponentModelFields::VFDEfficiencyType, vFDEfficiencyType);
}

boost::optional<double> FanComponentModel_Impl::maximumVFDOutputPower() const {
  return getDouble(openstudio::Fan_ComponentModelFields::MaximumVFDOutputPower, true);
}

bool FanComponentModel_Impl::isMaximumVFDOutputPowerAutosized() const {
  if (const auto value = getString(openstudio::Fan_ComponentModelFields::MaximumVFDOutputPower, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool FanComponentModel_Impl::setMaximumVFDOutputPower(double maximumVFDOutputPower) {
  return setDouble(openstudio::Fan_ComponentModelFields::MaximumVFDOutputPower, maximumVFDOutputPower);
}

void FanComponentModel_Impl::autosizeMaximumVFDOutputPower() {
  const bool result = setString(openstudio::Fan_ComponentModelFields::MaximumVFDOutputPower, "autosize");
  OS_ASSERT(result);
}

double FanComponentModel_Impl::vFDSizingFactor() const {
  const auto value = getDouble(openstudio::Fan_ComponentModelFields::VFDSizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool FanComponentModel_Impl::setVFDSizingFactor(double vFDSizingFactor) {
  return setDouble(openstudio::Fan_ComponentModelFields::VFDSizingFactor, vFDSizingFactor);
}

std::string FanComponentModel_Impl::endUseSubcategory() const {
  const auto value = getString(openstudio::Fan_ComponentModelFields::EndUseSubcategory, true);
  OS_ASSERT(value);
  return *value;
}

bool FanComponentModel_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
  const bool result = setString(openstudio::Fan_ComponentModelFields::EndUseSubcategory, endUseSubcategory);
  OS_ASSERT(result);
  return result;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
