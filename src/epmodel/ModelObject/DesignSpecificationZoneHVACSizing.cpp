/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "DesignSpecificationZoneHVACSizing.hpp"
#include "DesignSpecificationZoneHVACSizing_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/DesignSpecification_ZoneHVAC_Sizing_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

DesignSpecificationZoneHVACSizing::DesignSpecificationZoneHVACSizing(const Model& model)
  : ModelObject(DesignSpecificationZoneHVACSizing::iddObjectType(), model) {}

DesignSpecificationZoneHVACSizing::DesignSpecificationZoneHVACSizing(std::shared_ptr<detail::DesignSpecificationZoneHVACSizing_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType DesignSpecificationZoneHVACSizing::iddObjectType() {
  return IddObjectType::DesignSpecification_ZoneHVAC_Sizing;
}

std::vector<std::string> DesignSpecificationZoneHVACSizing::coolingSupplyAirFlowRateMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingSupplyAirFlowRateMethod);
}

std::vector<std::string> DesignSpecificationZoneHVACSizing::noLoadSupplyAirFlowRateMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::DesignSpecification_ZoneHVAC_SizingFields::NoLoadSupplyAirFlowRateMethod);
}

std::vector<std::string> DesignSpecificationZoneHVACSizing::heatingSupplyAirFlowRateMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingSupplyAirFlowRateMethod);
}

std::vector<std::string> DesignSpecificationZoneHVACSizing::coolingDesignCapacityMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingDesignCapacityMethod);
}

std::vector<std::string> DesignSpecificationZoneHVACSizing::heatingDesignCapacityMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingDesignCapacityMethod);
}

std::string DesignSpecificationZoneHVACSizing::coolingSupplyAirFlowRateMethod() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->coolingSupplyAirFlowRateMethod();
}

bool DesignSpecificationZoneHVACSizing::isCoolingSupplyAirFlowRateMethodDefaulted() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->isCoolingSupplyAirFlowRateMethodDefaulted();
}

bool DesignSpecificationZoneHVACSizing::setCoolingSupplyAirFlowRateMethod(const std::string& coolingSupplyAirFlowRateMethod) {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->setCoolingSupplyAirFlowRateMethod(coolingSupplyAirFlowRateMethod);
}

void DesignSpecificationZoneHVACSizing::resetCoolingSupplyAirFlowRateMethod() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->resetCoolingSupplyAirFlowRateMethod();
}

boost::optional<double> DesignSpecificationZoneHVACSizing::coolingSupplyAirFlowRate() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->coolingSupplyAirFlowRate();
}

bool DesignSpecificationZoneHVACSizing::isCoolingSupplyAirFlowRateAutosized() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->isCoolingSupplyAirFlowRateAutosized();
}

bool DesignSpecificationZoneHVACSizing::setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate) {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->setCoolingSupplyAirFlowRate(coolingSupplyAirFlowRate);
}

void DesignSpecificationZoneHVACSizing::resetCoolingSupplyAirFlowRate() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->resetCoolingSupplyAirFlowRate();
}

void DesignSpecificationZoneHVACSizing::autosizeCoolingSupplyAirFlowRate() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->autosizeCoolingSupplyAirFlowRate();
}

boost::optional<double> DesignSpecificationZoneHVACSizing::coolingSupplyAirFlowRatePerFloorArea() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->coolingSupplyAirFlowRatePerFloorArea();
}

bool DesignSpecificationZoneHVACSizing::setCoolingSupplyAirFlowRatePerFloorArea(double coolingSupplyAirFlowRatePerFloorArea) {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->setCoolingSupplyAirFlowRatePerFloorArea(coolingSupplyAirFlowRatePerFloorArea);
}

void DesignSpecificationZoneHVACSizing::resetCoolingSupplyAirFlowRatePerFloorArea() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->resetCoolingSupplyAirFlowRatePerFloorArea();
}

boost::optional<double> DesignSpecificationZoneHVACSizing::coolingFractionofAutosizedCoolingSupplyAirFlowRate() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->coolingFractionofAutosizedCoolingSupplyAirFlowRate();
}

bool DesignSpecificationZoneHVACSizing::setCoolingFractionofAutosizedCoolingSupplyAirFlowRate(double coolingFractionofAutosizedCoolingSupplyAirFlowRate) {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->setCoolingFractionofAutosizedCoolingSupplyAirFlowRate(
    coolingFractionofAutosizedCoolingSupplyAirFlowRate);
}

void DesignSpecificationZoneHVACSizing::resetCoolingFractionofAutosizedCoolingSupplyAirFlowRate() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->resetCoolingFractionofAutosizedCoolingSupplyAirFlowRate();
}

boost::optional<double> DesignSpecificationZoneHVACSizing::coolingSupplyAirFlowRatePerUnitCoolingCapacity() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->coolingSupplyAirFlowRatePerUnitCoolingCapacity();
}

bool DesignSpecificationZoneHVACSizing::setCoolingSupplyAirFlowRatePerUnitCoolingCapacity(double coolingSupplyAirFlowRatePerUnitCoolingCapacity) {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->setCoolingSupplyAirFlowRatePerUnitCoolingCapacity(
    coolingSupplyAirFlowRatePerUnitCoolingCapacity);
}

void DesignSpecificationZoneHVACSizing::resetCoolingSupplyAirFlowRatePerUnitCoolingCapacity() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->resetCoolingSupplyAirFlowRatePerUnitCoolingCapacity();
}

std::string DesignSpecificationZoneHVACSizing::noLoadSupplyAirFlowRateMethod() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->noLoadSupplyAirFlowRateMethod();
}

bool DesignSpecificationZoneHVACSizing::isNoLoadSupplyAirFlowRateMethodDefaulted() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->isNoLoadSupplyAirFlowRateMethodDefaulted();
}

bool DesignSpecificationZoneHVACSizing::setNoLoadSupplyAirFlowRateMethod(const std::string& noLoadSupplyAirFlowRateMethod) {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->setNoLoadSupplyAirFlowRateMethod(noLoadSupplyAirFlowRateMethod);
}

void DesignSpecificationZoneHVACSizing::resetNoLoadSupplyAirFlowRateMethod() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->resetNoLoadSupplyAirFlowRateMethod();
}

boost::optional<double> DesignSpecificationZoneHVACSizing::noLoadSupplyAirFlowRate() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->noLoadSupplyAirFlowRate();
}

bool DesignSpecificationZoneHVACSizing::isNoLoadSupplyAirFlowRateAutosized() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->isNoLoadSupplyAirFlowRateAutosized();
}

bool DesignSpecificationZoneHVACSizing::setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate) {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->setNoLoadSupplyAirFlowRate(noLoadSupplyAirFlowRate);
}

void DesignSpecificationZoneHVACSizing::resetNoLoadSupplyAirFlowRate() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->resetNoLoadSupplyAirFlowRate();
}

void DesignSpecificationZoneHVACSizing::autosizeNoLoadSupplyAirFlowRate() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->autosizeNoLoadSupplyAirFlowRate();
}

boost::optional<double> DesignSpecificationZoneHVACSizing::noLoadSupplyAirFlowRatePerFloorArea() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->noLoadSupplyAirFlowRatePerFloorArea();
}

bool DesignSpecificationZoneHVACSizing::setNoLoadSupplyAirFlowRatePerFloorArea(double noLoadSupplyAirFlowRatePerFloorArea) {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->setNoLoadSupplyAirFlowRatePerFloorArea(noLoadSupplyAirFlowRatePerFloorArea);
}

void DesignSpecificationZoneHVACSizing::resetNoLoadSupplyAirFlowRatePerFloorArea() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->resetNoLoadSupplyAirFlowRatePerFloorArea();
}

boost::optional<double> DesignSpecificationZoneHVACSizing::noLoadFractionofCoolingSupplyAirFlowRate() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->noLoadFractionofCoolingSupplyAirFlowRate();
}

bool DesignSpecificationZoneHVACSizing::setNoLoadFractionofCoolingSupplyAirFlowRate(double noLoadFractionofCoolingSupplyAirFlowRate) {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->setNoLoadFractionofCoolingSupplyAirFlowRate(noLoadFractionofCoolingSupplyAirFlowRate);
}

void DesignSpecificationZoneHVACSizing::resetNoLoadFractionofCoolingSupplyAirFlowRate() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->resetNoLoadFractionofCoolingSupplyAirFlowRate();
}

boost::optional<double> DesignSpecificationZoneHVACSizing::noLoadFractionofHeatingSupplyAirFlowRate() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->noLoadFractionofHeatingSupplyAirFlowRate();
}

bool DesignSpecificationZoneHVACSizing::setNoLoadFractionofHeatingSupplyAirFlowRate(double noLoadFractionofHeatingSupplyAirFlowRate) {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->setNoLoadFractionofHeatingSupplyAirFlowRate(noLoadFractionofHeatingSupplyAirFlowRate);
}

void DesignSpecificationZoneHVACSizing::resetNoLoadFractionofHeatingSupplyAirFlowRate() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->resetNoLoadFractionofHeatingSupplyAirFlowRate();
}

std::string DesignSpecificationZoneHVACSizing::heatingSupplyAirFlowRateMethod() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->heatingSupplyAirFlowRateMethod();
}

bool DesignSpecificationZoneHVACSizing::isHeatingSupplyAirFlowRateMethodDefaulted() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->isHeatingSupplyAirFlowRateMethodDefaulted();
}

bool DesignSpecificationZoneHVACSizing::setHeatingSupplyAirFlowRateMethod(const std::string& heatingSupplyAirFlowRateMethod) {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->setHeatingSupplyAirFlowRateMethod(heatingSupplyAirFlowRateMethod);
}

void DesignSpecificationZoneHVACSizing::resetHeatingSupplyAirFlowRateMethod() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->resetHeatingSupplyAirFlowRateMethod();
}

boost::optional<double> DesignSpecificationZoneHVACSizing::heatingSupplyAirFlowRate() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->heatingSupplyAirFlowRate();
}

bool DesignSpecificationZoneHVACSizing::isHeatingSupplyAirFlowRateAutosized() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->isHeatingSupplyAirFlowRateAutosized();
}

bool DesignSpecificationZoneHVACSizing::setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate) {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->setHeatingSupplyAirFlowRate(heatingSupplyAirFlowRate);
}

void DesignSpecificationZoneHVACSizing::resetHeatingSupplyAirFlowRate() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->resetHeatingSupplyAirFlowRate();
}

void DesignSpecificationZoneHVACSizing::autosizeHeatingSupplyAirFlowRate() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->autosizeHeatingSupplyAirFlowRate();
}

boost::optional<double> DesignSpecificationZoneHVACSizing::heatingSupplyAirFlowRatePerFloorArea() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->heatingSupplyAirFlowRatePerFloorArea();
}

bool DesignSpecificationZoneHVACSizing::setHeatingSupplyAirFlowRatePerFloorArea(double heatingSupplyAirFlowRatePerFloorArea) {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->setHeatingSupplyAirFlowRatePerFloorArea(heatingSupplyAirFlowRatePerFloorArea);
}

void DesignSpecificationZoneHVACSizing::resetHeatingSupplyAirFlowRatePerFloorArea() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->resetHeatingSupplyAirFlowRatePerFloorArea();
}

boost::optional<double> DesignSpecificationZoneHVACSizing::heatingFractionofHeatingSupplyAirFlowRate() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->heatingFractionofHeatingSupplyAirFlowRate();
}

bool DesignSpecificationZoneHVACSizing::setHeatingFractionofHeatingSupplyAirFlowRate(double heatingFractionofHeatingSupplyAirFlowRate) {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->setHeatingFractionofHeatingSupplyAirFlowRate(heatingFractionofHeatingSupplyAirFlowRate);
}

void DesignSpecificationZoneHVACSizing::resetHeatingFractionofHeatingSupplyAirFlowRate() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->resetHeatingFractionofHeatingSupplyAirFlowRate();
}

boost::optional<double> DesignSpecificationZoneHVACSizing::heatingSupplyAirFlowRatePerUnitHeatingCapacity() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->heatingSupplyAirFlowRatePerUnitHeatingCapacity();
}

bool DesignSpecificationZoneHVACSizing::setHeatingSupplyAirFlowRatePerUnitHeatingCapacity(double heatingSupplyAirFlowRatePerUnitHeatingCapacity) {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->setHeatingSupplyAirFlowRatePerUnitHeatingCapacity(
    heatingSupplyAirFlowRatePerUnitHeatingCapacity);
}

void DesignSpecificationZoneHVACSizing::resetHeatingSupplyAirFlowRatePerUnitHeatingCapacity() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->resetHeatingSupplyAirFlowRatePerUnitHeatingCapacity();
}

std::string DesignSpecificationZoneHVACSizing::coolingDesignCapacityMethod() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->coolingDesignCapacityMethod();
}

bool DesignSpecificationZoneHVACSizing::isCoolingDesignCapacityMethodDefaulted() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->isCoolingDesignCapacityMethodDefaulted();
}

bool DesignSpecificationZoneHVACSizing::setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod) {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->setCoolingDesignCapacityMethod(coolingDesignCapacityMethod);
}

void DesignSpecificationZoneHVACSizing::resetCoolingDesignCapacityMethod() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->resetCoolingDesignCapacityMethod();
}

boost::optional<double> DesignSpecificationZoneHVACSizing::coolingDesignCapacity() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->coolingDesignCapacity();
}

bool DesignSpecificationZoneHVACSizing::isCoolingDesignCapacityAutosized() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->isCoolingDesignCapacityAutosized();
}

bool DesignSpecificationZoneHVACSizing::setCoolingDesignCapacity(double coolingDesignCapacity) {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->setCoolingDesignCapacity(coolingDesignCapacity);
}

void DesignSpecificationZoneHVACSizing::resetCoolingDesignCapacity() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->resetCoolingDesignCapacity();
}

void DesignSpecificationZoneHVACSizing::autosizeCoolingDesignCapacity() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->autosizeCoolingDesignCapacity();
}

boost::optional<double> DesignSpecificationZoneHVACSizing::coolingDesignCapacityPerFloorArea() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->coolingDesignCapacityPerFloorArea();
}

bool DesignSpecificationZoneHVACSizing::setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea) {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->setCoolingDesignCapacityPerFloorArea(coolingDesignCapacityPerFloorArea);
}

void DesignSpecificationZoneHVACSizing::resetCoolingDesignCapacityPerFloorArea() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->resetCoolingDesignCapacityPerFloorArea();
}

boost::optional<double> DesignSpecificationZoneHVACSizing::fractionofAutosizedCoolingDesignCapacity() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->fractionofAutosizedCoolingDesignCapacity();
}

bool DesignSpecificationZoneHVACSizing::setFractionofAutosizedCoolingDesignCapacity(double fractionofAutosizedCoolingDesignCapacity) {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->setFractionofAutosizedCoolingDesignCapacity(
    fractionofAutosizedCoolingDesignCapacity);
}

void DesignSpecificationZoneHVACSizing::resetFractionofAutosizedCoolingDesignCapacity() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->resetFractionofAutosizedCoolingDesignCapacity();
}

std::string DesignSpecificationZoneHVACSizing::heatingDesignCapacityMethod() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->heatingDesignCapacityMethod();
}

bool DesignSpecificationZoneHVACSizing::isHeatingDesignCapacityMethodDefaulted() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->isHeatingDesignCapacityMethodDefaulted();
}

bool DesignSpecificationZoneHVACSizing::setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod) {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->setHeatingDesignCapacityMethod(heatingDesignCapacityMethod);
}

void DesignSpecificationZoneHVACSizing::resetHeatingDesignCapacityMethod() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->resetHeatingDesignCapacityMethod();
}

boost::optional<double> DesignSpecificationZoneHVACSizing::heatingDesignCapacity() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->heatingDesignCapacity();
}

bool DesignSpecificationZoneHVACSizing::isHeatingDesignCapacityAutosized() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->isHeatingDesignCapacityAutosized();
}

bool DesignSpecificationZoneHVACSizing::setHeatingDesignCapacity(double heatingDesignCapacity) {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->setHeatingDesignCapacity(heatingDesignCapacity);
}

void DesignSpecificationZoneHVACSizing::resetHeatingDesignCapacity() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->resetHeatingDesignCapacity();
}

void DesignSpecificationZoneHVACSizing::autosizeHeatingDesignCapacity() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->autosizeHeatingDesignCapacity();
}

boost::optional<double> DesignSpecificationZoneHVACSizing::heatingDesignCapacityPerFloorArea() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->heatingDesignCapacityPerFloorArea();
}

bool DesignSpecificationZoneHVACSizing::setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea) {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->setHeatingDesignCapacityPerFloorArea(heatingDesignCapacityPerFloorArea);
}

void DesignSpecificationZoneHVACSizing::resetHeatingDesignCapacityPerFloorArea() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->resetHeatingDesignCapacityPerFloorArea();
}

boost::optional<double> DesignSpecificationZoneHVACSizing::fractionofAutosizedHeatingDesignCapacity() const {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->fractionofAutosizedHeatingDesignCapacity();
}

bool DesignSpecificationZoneHVACSizing::setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity) {
  return getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->setFractionofAutosizedHeatingDesignCapacity(
    fractionofAutosizedHeatingDesignCapacity);
}

void DesignSpecificationZoneHVACSizing::resetFractionofAutosizedHeatingDesignCapacity() {
  getImpl<detail::DesignSpecificationZoneHVACSizing_Impl>()->resetFractionofAutosizedHeatingDesignCapacity();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string DesignSpecificationZoneHVACSizing_Impl::coolingSupplyAirFlowRateMethod() const {
  const auto value = getString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingSupplyAirFlowRateMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool DesignSpecificationZoneHVACSizing_Impl::isCoolingSupplyAirFlowRateMethodDefaulted() const {
  return isEmpty(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingSupplyAirFlowRateMethod);
}

bool DesignSpecificationZoneHVACSizing_Impl::setCoolingSupplyAirFlowRateMethod(const std::string& coolingSupplyAirFlowRateMethod) {
  return setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingSupplyAirFlowRateMethod, coolingSupplyAirFlowRateMethod);
}

void DesignSpecificationZoneHVACSizing_Impl::resetCoolingSupplyAirFlowRateMethod() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingSupplyAirFlowRateMethod, ""));
}

boost::optional<double> DesignSpecificationZoneHVACSizing_Impl::coolingSupplyAirFlowRate() const {
  return getDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingSupplyAirFlowRate, true);
}

bool DesignSpecificationZoneHVACSizing_Impl::isCoolingSupplyAirFlowRateAutosized() const {
  const auto value = getString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingSupplyAirFlowRate, true);
  return value && openstudio::istringEqual(*value, "autosize");
}

bool DesignSpecificationZoneHVACSizing_Impl::setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate) {
  return setDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingSupplyAirFlowRate, coolingSupplyAirFlowRate);
}

void DesignSpecificationZoneHVACSizing_Impl::resetCoolingSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingSupplyAirFlowRate, ""));
}

void DesignSpecificationZoneHVACSizing_Impl::autosizeCoolingSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingSupplyAirFlowRate, "autosize"));
}

boost::optional<double> DesignSpecificationZoneHVACSizing_Impl::coolingSupplyAirFlowRatePerFloorArea() const {
  return getDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingSupplyAirFlowRatePerFloorArea, true);
}

bool DesignSpecificationZoneHVACSizing_Impl::setCoolingSupplyAirFlowRatePerFloorArea(double coolingSupplyAirFlowRatePerFloorArea) {
  return setDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingSupplyAirFlowRatePerFloorArea,
                   coolingSupplyAirFlowRatePerFloorArea);
}

void DesignSpecificationZoneHVACSizing_Impl::resetCoolingSupplyAirFlowRatePerFloorArea() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingSupplyAirFlowRatePerFloorArea, ""));
}

boost::optional<double> DesignSpecificationZoneHVACSizing_Impl::coolingFractionofAutosizedCoolingSupplyAirFlowRate() const {
  return getDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingFractionofAutosizedCoolingSupplyAirFlowRate, true);
}

bool DesignSpecificationZoneHVACSizing_Impl::setCoolingFractionofAutosizedCoolingSupplyAirFlowRate(
  double coolingFractionofAutosizedCoolingSupplyAirFlowRate) {
  return setDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingFractionofAutosizedCoolingSupplyAirFlowRate,
                   coolingFractionofAutosizedCoolingSupplyAirFlowRate);
}

void DesignSpecificationZoneHVACSizing_Impl::resetCoolingFractionofAutosizedCoolingSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingFractionofAutosizedCoolingSupplyAirFlowRate, ""));
}

boost::optional<double> DesignSpecificationZoneHVACSizing_Impl::coolingSupplyAirFlowRatePerUnitCoolingCapacity() const {
  return getDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingSupplyAirFlowRatePerUnitCoolingCapacity, true);
}

bool DesignSpecificationZoneHVACSizing_Impl::setCoolingSupplyAirFlowRatePerUnitCoolingCapacity(double coolingSupplyAirFlowRatePerUnitCoolingCapacity) {
  return setDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingSupplyAirFlowRatePerUnitCoolingCapacity,
                   coolingSupplyAirFlowRatePerUnitCoolingCapacity);
}

void DesignSpecificationZoneHVACSizing_Impl::resetCoolingSupplyAirFlowRatePerUnitCoolingCapacity() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingSupplyAirFlowRatePerUnitCoolingCapacity, ""));
}

std::string DesignSpecificationZoneHVACSizing_Impl::noLoadSupplyAirFlowRateMethod() const {
  const auto value = getString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::NoLoadSupplyAirFlowRateMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool DesignSpecificationZoneHVACSizing_Impl::isNoLoadSupplyAirFlowRateMethodDefaulted() const {
  return isEmpty(openstudio::DesignSpecification_ZoneHVAC_SizingFields::NoLoadSupplyAirFlowRateMethod);
}

bool DesignSpecificationZoneHVACSizing_Impl::setNoLoadSupplyAirFlowRateMethod(const std::string& noLoadSupplyAirFlowRateMethod) {
  return setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::NoLoadSupplyAirFlowRateMethod, noLoadSupplyAirFlowRateMethod);
}

void DesignSpecificationZoneHVACSizing_Impl::resetNoLoadSupplyAirFlowRateMethod() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::NoLoadSupplyAirFlowRateMethod, ""));
}

boost::optional<double> DesignSpecificationZoneHVACSizing_Impl::noLoadSupplyAirFlowRate() const {
  return getDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::NoLoadSupplyAirFlowRate, true);
}

bool DesignSpecificationZoneHVACSizing_Impl::isNoLoadSupplyAirFlowRateAutosized() const {
  const auto value = getString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::NoLoadSupplyAirFlowRate, true);
  return value && openstudio::istringEqual(*value, "autosize");
}

bool DesignSpecificationZoneHVACSizing_Impl::setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate) {
  return setDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::NoLoadSupplyAirFlowRate, noLoadSupplyAirFlowRate);
}

void DesignSpecificationZoneHVACSizing_Impl::resetNoLoadSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::NoLoadSupplyAirFlowRate, ""));
}

void DesignSpecificationZoneHVACSizing_Impl::autosizeNoLoadSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::NoLoadSupplyAirFlowRate, "autosize"));
}

boost::optional<double> DesignSpecificationZoneHVACSizing_Impl::noLoadSupplyAirFlowRatePerFloorArea() const {
  return getDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::NoLoadSupplyAirFlowRatePerFloorArea, true);
}

bool DesignSpecificationZoneHVACSizing_Impl::setNoLoadSupplyAirFlowRatePerFloorArea(double noLoadSupplyAirFlowRatePerFloorArea) {
  return setDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::NoLoadSupplyAirFlowRatePerFloorArea,
                   noLoadSupplyAirFlowRatePerFloorArea);
}

void DesignSpecificationZoneHVACSizing_Impl::resetNoLoadSupplyAirFlowRatePerFloorArea() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::NoLoadSupplyAirFlowRatePerFloorArea, ""));
}

boost::optional<double> DesignSpecificationZoneHVACSizing_Impl::noLoadFractionofCoolingSupplyAirFlowRate() const {
  return getDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::NoLoadFractionofCoolingSupplyAirFlowRate, true);
}

bool DesignSpecificationZoneHVACSizing_Impl::setNoLoadFractionofCoolingSupplyAirFlowRate(double noLoadFractionofCoolingSupplyAirFlowRate) {
  return setDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::NoLoadFractionofCoolingSupplyAirFlowRate,
                   noLoadFractionofCoolingSupplyAirFlowRate);
}

void DesignSpecificationZoneHVACSizing_Impl::resetNoLoadFractionofCoolingSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::NoLoadFractionofCoolingSupplyAirFlowRate, ""));
}

boost::optional<double> DesignSpecificationZoneHVACSizing_Impl::noLoadFractionofHeatingSupplyAirFlowRate() const {
  return getDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::NoLoadFractionofHeatingSupplyAirFlowRate, true);
}

bool DesignSpecificationZoneHVACSizing_Impl::setNoLoadFractionofHeatingSupplyAirFlowRate(double noLoadFractionofHeatingSupplyAirFlowRate) {
  return setDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::NoLoadFractionofHeatingSupplyAirFlowRate,
                   noLoadFractionofHeatingSupplyAirFlowRate);
}

void DesignSpecificationZoneHVACSizing_Impl::resetNoLoadFractionofHeatingSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::NoLoadFractionofHeatingSupplyAirFlowRate, ""));
}

std::string DesignSpecificationZoneHVACSizing_Impl::heatingSupplyAirFlowRateMethod() const {
  const auto value = getString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingSupplyAirFlowRateMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool DesignSpecificationZoneHVACSizing_Impl::isHeatingSupplyAirFlowRateMethodDefaulted() const {
  return isEmpty(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingSupplyAirFlowRateMethod);
}

bool DesignSpecificationZoneHVACSizing_Impl::setHeatingSupplyAirFlowRateMethod(const std::string& heatingSupplyAirFlowRateMethod) {
  return setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingSupplyAirFlowRateMethod, heatingSupplyAirFlowRateMethod);
}

void DesignSpecificationZoneHVACSizing_Impl::resetHeatingSupplyAirFlowRateMethod() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingSupplyAirFlowRateMethod, ""));
}

boost::optional<double> DesignSpecificationZoneHVACSizing_Impl::heatingSupplyAirFlowRate() const {
  return getDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingSupplyAirFlowRate, true);
}

bool DesignSpecificationZoneHVACSizing_Impl::isHeatingSupplyAirFlowRateAutosized() const {
  const auto value = getString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingSupplyAirFlowRate, true);
  return value && openstudio::istringEqual(*value, "autosize");
}

bool DesignSpecificationZoneHVACSizing_Impl::setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate) {
  return setDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingSupplyAirFlowRate, heatingSupplyAirFlowRate);
}

void DesignSpecificationZoneHVACSizing_Impl::resetHeatingSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingSupplyAirFlowRate, ""));
}

void DesignSpecificationZoneHVACSizing_Impl::autosizeHeatingSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingSupplyAirFlowRate, "autosize"));
}

boost::optional<double> DesignSpecificationZoneHVACSizing_Impl::heatingSupplyAirFlowRatePerFloorArea() const {
  return getDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingSupplyAirFlowRatePerFloorArea, true);
}

bool DesignSpecificationZoneHVACSizing_Impl::setHeatingSupplyAirFlowRatePerFloorArea(double heatingSupplyAirFlowRatePerFloorArea) {
  return setDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingSupplyAirFlowRatePerFloorArea,
                   heatingSupplyAirFlowRatePerFloorArea);
}

void DesignSpecificationZoneHVACSizing_Impl::resetHeatingSupplyAirFlowRatePerFloorArea() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingSupplyAirFlowRatePerFloorArea, ""));
}

boost::optional<double> DesignSpecificationZoneHVACSizing_Impl::heatingFractionofHeatingSupplyAirFlowRate() const {
  return getDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingFractionofHeatingSupplyAirFlowRate, true);
}

bool DesignSpecificationZoneHVACSizing_Impl::setHeatingFractionofHeatingSupplyAirFlowRate(double heatingFractionofHeatingSupplyAirFlowRate) {
  return setDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingFractionofHeatingSupplyAirFlowRate,
                   heatingFractionofHeatingSupplyAirFlowRate);
}

void DesignSpecificationZoneHVACSizing_Impl::resetHeatingFractionofHeatingSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingFractionofHeatingSupplyAirFlowRate, ""));
}

boost::optional<double> DesignSpecificationZoneHVACSizing_Impl::heatingSupplyAirFlowRatePerUnitHeatingCapacity() const {
  return getDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingSupplyAirFlowRatePerUnitHeatingCapacity, true);
}

bool DesignSpecificationZoneHVACSizing_Impl::setHeatingSupplyAirFlowRatePerUnitHeatingCapacity(
  double heatingSupplyAirFlowRatePerUnitHeatingCapacity) {
  return setDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingSupplyAirFlowRatePerUnitHeatingCapacity,
                   heatingSupplyAirFlowRatePerUnitHeatingCapacity);
}

void DesignSpecificationZoneHVACSizing_Impl::resetHeatingSupplyAirFlowRatePerUnitHeatingCapacity() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingSupplyAirFlowRatePerUnitHeatingCapacity, ""));
}

std::string DesignSpecificationZoneHVACSizing_Impl::coolingDesignCapacityMethod() const {
  const auto value = getString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingDesignCapacityMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool DesignSpecificationZoneHVACSizing_Impl::isCoolingDesignCapacityMethodDefaulted() const {
  return isEmpty(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingDesignCapacityMethod);
}

bool DesignSpecificationZoneHVACSizing_Impl::setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod) {
  return setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingDesignCapacityMethod, coolingDesignCapacityMethod);
}

void DesignSpecificationZoneHVACSizing_Impl::resetCoolingDesignCapacityMethod() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingDesignCapacityMethod, ""));
}

boost::optional<double> DesignSpecificationZoneHVACSizing_Impl::coolingDesignCapacity() const {
  return getDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingDesignCapacity, true);
}

bool DesignSpecificationZoneHVACSizing_Impl::isCoolingDesignCapacityAutosized() const {
  const auto value = getString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingDesignCapacity, true);
  return value && openstudio::istringEqual(*value, "autosize");
}

bool DesignSpecificationZoneHVACSizing_Impl::setCoolingDesignCapacity(double coolingDesignCapacity) {
  return setDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingDesignCapacity, coolingDesignCapacity);
}

void DesignSpecificationZoneHVACSizing_Impl::resetCoolingDesignCapacity() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingDesignCapacity, ""));
}

void DesignSpecificationZoneHVACSizing_Impl::autosizeCoolingDesignCapacity() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingDesignCapacity, "autosize"));
}

boost::optional<double> DesignSpecificationZoneHVACSizing_Impl::coolingDesignCapacityPerFloorArea() const {
  return getDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingDesignCapacityPerFloorArea, true);
}

bool DesignSpecificationZoneHVACSizing_Impl::setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea) {
  return setDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingDesignCapacityPerFloorArea, coolingDesignCapacityPerFloorArea);
}

void DesignSpecificationZoneHVACSizing_Impl::resetCoolingDesignCapacityPerFloorArea() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::CoolingDesignCapacityPerFloorArea, ""));
}

boost::optional<double> DesignSpecificationZoneHVACSizing_Impl::fractionofAutosizedCoolingDesignCapacity() const {
  return getDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::FractionofAutosizedCoolingDesignCapacity, true);
}

bool DesignSpecificationZoneHVACSizing_Impl::setFractionofAutosizedCoolingDesignCapacity(double fractionofAutosizedCoolingDesignCapacity) {
  return setDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::FractionofAutosizedCoolingDesignCapacity,
                   fractionofAutosizedCoolingDesignCapacity);
}

void DesignSpecificationZoneHVACSizing_Impl::resetFractionofAutosizedCoolingDesignCapacity() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::FractionofAutosizedCoolingDesignCapacity, ""));
}

std::string DesignSpecificationZoneHVACSizing_Impl::heatingDesignCapacityMethod() const {
  const auto value = getString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingDesignCapacityMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool DesignSpecificationZoneHVACSizing_Impl::isHeatingDesignCapacityMethodDefaulted() const {
  return isEmpty(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingDesignCapacityMethod);
}

bool DesignSpecificationZoneHVACSizing_Impl::setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod) {
  return setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingDesignCapacityMethod, heatingDesignCapacityMethod);
}

void DesignSpecificationZoneHVACSizing_Impl::resetHeatingDesignCapacityMethod() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingDesignCapacityMethod, ""));
}

boost::optional<double> DesignSpecificationZoneHVACSizing_Impl::heatingDesignCapacity() const {
  return getDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingDesignCapacity, true);
}

bool DesignSpecificationZoneHVACSizing_Impl::isHeatingDesignCapacityAutosized() const {
  const auto value = getString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingDesignCapacity, true);
  return value && openstudio::istringEqual(*value, "autosize");
}

bool DesignSpecificationZoneHVACSizing_Impl::setHeatingDesignCapacity(double heatingDesignCapacity) {
  return setDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingDesignCapacity, heatingDesignCapacity);
}

void DesignSpecificationZoneHVACSizing_Impl::resetHeatingDesignCapacity() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingDesignCapacity, ""));
}

void DesignSpecificationZoneHVACSizing_Impl::autosizeHeatingDesignCapacity() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingDesignCapacity, "autosize"));
}

boost::optional<double> DesignSpecificationZoneHVACSizing_Impl::heatingDesignCapacityPerFloorArea() const {
  return getDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingDesignCapacityPerFloorArea, true);
}

bool DesignSpecificationZoneHVACSizing_Impl::setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea) {
  return setDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingDesignCapacityPerFloorArea, heatingDesignCapacityPerFloorArea);
}

void DesignSpecificationZoneHVACSizing_Impl::resetHeatingDesignCapacityPerFloorArea() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::HeatingDesignCapacityPerFloorArea, ""));
}

boost::optional<double> DesignSpecificationZoneHVACSizing_Impl::fractionofAutosizedHeatingDesignCapacity() const {
  return getDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::FractionofAutosizedHeatingDesignCapacity, true);
}

bool DesignSpecificationZoneHVACSizing_Impl::setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity) {
  return setDouble(openstudio::DesignSpecification_ZoneHVAC_SizingFields::FractionofAutosizedHeatingDesignCapacity,
                   fractionofAutosizedHeatingDesignCapacity);
}

void DesignSpecificationZoneHVACSizing_Impl::resetFractionofAutosizedHeatingDesignCapacity() {
  OS_ASSERT(setString(openstudio::DesignSpecification_ZoneHVAC_SizingFields::FractionofAutosizedHeatingDesignCapacity, ""));
}

std::vector<std::string> DesignSpecificationZoneHVACSizing_Impl::coolingSupplyAirFlowRateMethodValues() const {
  return openstudio::epmodel::DesignSpecificationZoneHVACSizing::coolingSupplyAirFlowRateMethodValues();
}

std::vector<std::string> DesignSpecificationZoneHVACSizing_Impl::noLoadSupplyAirFlowRateMethodValues() const {
  return openstudio::epmodel::DesignSpecificationZoneHVACSizing::noLoadSupplyAirFlowRateMethodValues();
}

std::vector<std::string> DesignSpecificationZoneHVACSizing_Impl::heatingSupplyAirFlowRateMethodValues() const {
  return openstudio::epmodel::DesignSpecificationZoneHVACSizing::heatingSupplyAirFlowRateMethodValues();
}

std::vector<std::string> DesignSpecificationZoneHVACSizing_Impl::coolingDesignCapacityMethodValues() const {
  return openstudio::epmodel::DesignSpecificationZoneHVACSizing::coolingDesignCapacityMethodValues();
}

std::vector<std::string> DesignSpecificationZoneHVACSizing_Impl::heatingDesignCapacityMethodValues() const {
  return openstudio::epmodel::DesignSpecificationZoneHVACSizing::heatingDesignCapacityMethodValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
