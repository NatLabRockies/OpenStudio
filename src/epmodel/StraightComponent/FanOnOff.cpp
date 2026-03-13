/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/FanOnOff.hpp"
#include "StraightComponent/FanOnOff_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Model.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Fan_OnOff_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

FanOnOff::FanOnOff(const Model& model) : StraightComponent(FanOnOff::iddObjectType(), model) {
  auto impl = getImpl<detail::FanOnOff_Impl>();
  OS_ASSERT(impl);
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

FanOnOff::FanOnOff(std::shared_ptr<detail::FanOnOff_Impl> impl) : StraightComponent(std::move(impl)) {}

IddObjectType FanOnOff::iddObjectType() {
  return IddObjectType::Fan_OnOff;
}

bool FanOnOff::addToNode(Node& node) {
  return getImpl<detail::FanOnOff_Impl>()->addToNode(node);
}

double FanOnOff::fanTotalEfficiency() const {
  return getImpl<detail::FanOnOff_Impl>()->fanTotalEfficiency();
}

bool FanOnOff::isFanTotalEfficiencyDefaulted() const {
  return getImpl<detail::FanOnOff_Impl>()->isFanTotalEfficiencyDefaulted();
}

bool FanOnOff::setFanTotalEfficiency(double fanTotalEfficiency) {
  return getImpl<detail::FanOnOff_Impl>()->setFanTotalEfficiency(fanTotalEfficiency);
}

void FanOnOff::resetFanTotalEfficiency() {
  getImpl<detail::FanOnOff_Impl>()->resetFanTotalEfficiency();
}

double FanOnOff::fanEfficiency() const {
  return getImpl<detail::FanOnOff_Impl>()->fanTotalEfficiency();
}

bool FanOnOff::isFanEfficiencyDefaulted() const {
  return getImpl<detail::FanOnOff_Impl>()->isFanTotalEfficiencyDefaulted();
}

bool FanOnOff::setFanEfficiency(double fanTotalEfficiency) {
  return getImpl<detail::FanOnOff_Impl>()->setFanTotalEfficiency(fanTotalEfficiency);
}

void FanOnOff::resetFanEfficiency() {
  getImpl<detail::FanOnOff_Impl>()->resetFanTotalEfficiency();
}

double FanOnOff::pressureRise() const {
  return getImpl<detail::FanOnOff_Impl>()->pressureRise();
}

bool FanOnOff::setPressureRise(double pressureRise) {
  return getImpl<detail::FanOnOff_Impl>()->setPressureRise(pressureRise);
}

boost::optional<double> FanOnOff::maximumFlowRate() const {
  return getImpl<detail::FanOnOff_Impl>()->maximumFlowRate();
}

bool FanOnOff::setMaximumFlowRate(double maximumFlowRate) {
  return getImpl<detail::FanOnOff_Impl>()->setMaximumFlowRate(maximumFlowRate);
}

void FanOnOff::resetMaximumFlowRate() {
  getImpl<detail::FanOnOff_Impl>()->resetMaximumFlowRate();
}

void FanOnOff::autosizeMaximumFlowRate() {
  getImpl<detail::FanOnOff_Impl>()->autosizeMaximumFlowRate();
}

bool FanOnOff::isMaximumFlowRateAutosized() const {
  return getImpl<detail::FanOnOff_Impl>()->isMaximumFlowRateAutosized();
}

double FanOnOff::motorEfficiency() const {
  return getImpl<detail::FanOnOff_Impl>()->motorEfficiency();
}

bool FanOnOff::isMotorEfficiencyDefaulted() const {
  return getImpl<detail::FanOnOff_Impl>()->isMotorEfficiencyDefaulted();
}

bool FanOnOff::setMotorEfficiency(double motorEfficiency) {
  return getImpl<detail::FanOnOff_Impl>()->setMotorEfficiency(motorEfficiency);
}

void FanOnOff::resetMotorEfficiency() {
  getImpl<detail::FanOnOff_Impl>()->resetMotorEfficiency();
}

boost::optional<double> FanOnOff::motorInAirstreamFraction() const {
  return getImpl<detail::FanOnOff_Impl>()->motorInAirstreamFraction();
}

bool FanOnOff::setMotorInAirstreamFraction(double motorInAirstreamFraction) {
  return getImpl<detail::FanOnOff_Impl>()->setMotorInAirstreamFraction(motorInAirstreamFraction);
}

void FanOnOff::resetMotorInAirstreamFraction() {
  getImpl<detail::FanOnOff_Impl>()->resetMotorInAirstreamFraction();
}

std::string FanOnOff::endUseSubcategory() const {
  return getImpl<detail::FanOnOff_Impl>()->endUseSubcategory();
}

bool FanOnOff::isEndUseSubcategoryDefaulted() const {
  return getImpl<detail::FanOnOff_Impl>()->isEndUseSubcategoryDefaulted();
}

bool FanOnOff::setEndUseSubcategory(const std::string& endUseSubcategory) {
  return getImpl<detail::FanOnOff_Impl>()->setEndUseSubcategory(endUseSubcategory);
}

void FanOnOff::resetEndUseSubcategory() {
  getImpl<detail::FanOnOff_Impl>()->resetEndUseSubcategory();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned FanOnOff_Impl::inletPort() const {
  return openstudio::Fan_OnOffFields::AirInletNodeName;
}

unsigned FanOnOff_Impl::outletPort() const {
  return openstudio::Fan_OnOffFields::AirOutletNodeName;
}

bool FanOnOff_Impl::addToNode(Node& node) {
  auto airLoop = node.airLoopHVAC();

  if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
    return false;
  }

  return StraightComponent_Impl::addToNode(node);
}

double FanOnOff_Impl::fanTotalEfficiency() const {
  const auto value = getDouble(openstudio::Fan_OnOffFields::FanTotalEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

bool FanOnOff_Impl::isFanTotalEfficiencyDefaulted() const {
  return isEmpty(openstudio::Fan_OnOffFields::FanTotalEfficiency);
}

bool FanOnOff_Impl::setFanTotalEfficiency(double fanTotalEfficiency) {
  return setDouble(openstudio::Fan_OnOffFields::FanTotalEfficiency, fanTotalEfficiency);
}

void FanOnOff_Impl::resetFanTotalEfficiency() {
  const bool result = setString(openstudio::Fan_OnOffFields::FanTotalEfficiency, "");
  OS_ASSERT(result);
}

double FanOnOff_Impl::pressureRise() const {
  const auto value = getDouble(openstudio::Fan_OnOffFields::PressureRise, true);
  OS_ASSERT(value);
  return *value;
}

bool FanOnOff_Impl::setPressureRise(double pressureRise) {
  return setDouble(openstudio::Fan_OnOffFields::PressureRise, pressureRise);
}

boost::optional<double> FanOnOff_Impl::maximumFlowRate() const {
  return getDouble(openstudio::Fan_OnOffFields::MaximumFlowRate, true);
}

bool FanOnOff_Impl::setMaximumFlowRate(double maximumFlowRate) {
  return setDouble(openstudio::Fan_OnOffFields::MaximumFlowRate, maximumFlowRate);
}

void FanOnOff_Impl::resetMaximumFlowRate() {
  const bool result = setString(openstudio::Fan_OnOffFields::MaximumFlowRate, "");
  OS_ASSERT(result);
}

void FanOnOff_Impl::autosizeMaximumFlowRate() {
  const bool result = setString(openstudio::Fan_OnOffFields::MaximumFlowRate, "autosize");
  OS_ASSERT(result);
}

bool FanOnOff_Impl::isMaximumFlowRateAutosized() const {
  if (const auto value = getString(openstudio::Fan_OnOffFields::MaximumFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

double FanOnOff_Impl::motorEfficiency() const {
  const auto value = getDouble(openstudio::Fan_OnOffFields::MotorEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

bool FanOnOff_Impl::isMotorEfficiencyDefaulted() const {
  return isEmpty(openstudio::Fan_OnOffFields::MotorEfficiency);
}

bool FanOnOff_Impl::setMotorEfficiency(double motorEfficiency) {
  return setDouble(openstudio::Fan_OnOffFields::MotorEfficiency, motorEfficiency);
}

void FanOnOff_Impl::resetMotorEfficiency() {
  const bool result = setString(openstudio::Fan_OnOffFields::MotorEfficiency, "");
  OS_ASSERT(result);
}

boost::optional<double> FanOnOff_Impl::motorInAirstreamFraction() const {
  return getDouble(openstudio::Fan_OnOffFields::MotorInAirstreamFraction, true);
}

bool FanOnOff_Impl::setMotorInAirstreamFraction(double motorInAirstreamFraction) {
  return setDouble(openstudio::Fan_OnOffFields::MotorInAirstreamFraction, motorInAirstreamFraction);
}

void FanOnOff_Impl::resetMotorInAirstreamFraction() {
  const bool result = setString(openstudio::Fan_OnOffFields::MotorInAirstreamFraction, "");
  OS_ASSERT(result);
}

std::string FanOnOff_Impl::endUseSubcategory() const {
  const auto value = getString(openstudio::Fan_OnOffFields::EndUseSubcategory, true);
  OS_ASSERT(value);
  return *value;
}

bool FanOnOff_Impl::isEndUseSubcategoryDefaulted() const {
  return isEmpty(openstudio::Fan_OnOffFields::EndUseSubcategory);
}

bool FanOnOff_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
  const bool result = setString(openstudio::Fan_OnOffFields::EndUseSubcategory, endUseSubcategory);
  OS_ASSERT(result);
  return result;
}

void FanOnOff_Impl::resetEndUseSubcategory() {
  const bool result = setString(openstudio::Fan_OnOffFields::EndUseSubcategory, "");
  OS_ASSERT(result);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
