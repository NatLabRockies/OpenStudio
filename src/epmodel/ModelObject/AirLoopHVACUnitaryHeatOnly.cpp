/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirLoopHVACUnitaryHeatOnly.hpp"
#include "AirLoopHVACUnitaryHeatOnly_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirLoopHVAC_UnitaryHeatOnly_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

AirLoopHVACUnitaryHeatOnly::AirLoopHVACUnitaryHeatOnly(const Model& model)
  : ModelObject(AirLoopHVACUnitaryHeatOnly::iddObjectType(), model) {}

AirLoopHVACUnitaryHeatOnly::AirLoopHVACUnitaryHeatOnly(
  std::shared_ptr<detail::AirLoopHVACUnitaryHeatOnly_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirLoopHVACUnitaryHeatOnly::iddObjectType() {
  return IddObjectType::AirLoopHVAC_UnitaryHeatOnly;
}

std::vector<std::string> AirLoopHVACUnitaryHeatOnly::supplyFanObjectTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirLoopHVAC_UnitaryHeatOnlyFields::SupplyFanObjectType);
}

std::vector<std::string> AirLoopHVACUnitaryHeatOnly::fanPlacementValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirLoopHVAC_UnitaryHeatOnlyFields::FanPlacement);
}

std::vector<std::string> AirLoopHVACUnitaryHeatOnly::heatingCoilObjectTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirLoopHVAC_UnitaryHeatOnlyFields::HeatingCoilObjectType);
}

boost::optional<double> AirLoopHVACUnitaryHeatOnly::maximumSupplyAirTemperature() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatOnly_Impl>()->maximumSupplyAirTemperature();
}

bool AirLoopHVACUnitaryHeatOnly::isMaximumSupplyAirTemperatureDefaulted() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatOnly_Impl>()->isMaximumSupplyAirTemperatureDefaulted();
}

bool AirLoopHVACUnitaryHeatOnly::isMaximumSupplyAirTemperatureAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatOnly_Impl>()->isMaximumSupplyAirTemperatureAutosized();
}

bool AirLoopHVACUnitaryHeatOnly::setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature) {
  return getImpl<detail::AirLoopHVACUnitaryHeatOnly_Impl>()->setMaximumSupplyAirTemperature(maximumSupplyAirTemperature);
}

void AirLoopHVACUnitaryHeatOnly::resetMaximumSupplyAirTemperature() {
  getImpl<detail::AirLoopHVACUnitaryHeatOnly_Impl>()->resetMaximumSupplyAirTemperature();
}

void AirLoopHVACUnitaryHeatOnly::autosizeMaximumSupplyAirTemperature() {
  getImpl<detail::AirLoopHVACUnitaryHeatOnly_Impl>()->autosizeMaximumSupplyAirTemperature();
}

boost::optional<double> AirLoopHVACUnitaryHeatOnly::heatingSupplyAirFlowRate() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatOnly_Impl>()->heatingSupplyAirFlowRate();
}

bool AirLoopHVACUnitaryHeatOnly::isHeatingSupplyAirFlowRateAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatOnly_Impl>()->isHeatingSupplyAirFlowRateAutosized();
}

bool AirLoopHVACUnitaryHeatOnly::setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate) {
  return getImpl<detail::AirLoopHVACUnitaryHeatOnly_Impl>()->setHeatingSupplyAirFlowRate(heatingSupplyAirFlowRate);
}

void AirLoopHVACUnitaryHeatOnly::autosizeHeatingSupplyAirFlowRate() {
  getImpl<detail::AirLoopHVACUnitaryHeatOnly_Impl>()->autosizeHeatingSupplyAirFlowRate();
}

std::string AirLoopHVACUnitaryHeatOnly::supplyFanObjectType() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatOnly_Impl>()->supplyFanObjectType();
}

bool AirLoopHVACUnitaryHeatOnly::setSupplyFanObjectType(const std::string& supplyFanObjectType) {
  return getImpl<detail::AirLoopHVACUnitaryHeatOnly_Impl>()->setSupplyFanObjectType(supplyFanObjectType);
}

std::string AirLoopHVACUnitaryHeatOnly::fanPlacement() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatOnly_Impl>()->fanPlacement();
}

bool AirLoopHVACUnitaryHeatOnly::setFanPlacement(const std::string& fanPlacement) {
  return getImpl<detail::AirLoopHVACUnitaryHeatOnly_Impl>()->setFanPlacement(fanPlacement);
}

bool AirLoopHVACUnitaryHeatOnly::isFanPlacementDefaulted() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatOnly_Impl>()->isFanPlacementDefaulted();
}

void AirLoopHVACUnitaryHeatOnly::resetFanPlacement() {
  getImpl<detail::AirLoopHVACUnitaryHeatOnly_Impl>()->resetFanPlacement();
}

std::string AirLoopHVACUnitaryHeatOnly::heatingCoilObjectType() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatOnly_Impl>()->heatingCoilObjectType();
}

bool AirLoopHVACUnitaryHeatOnly::setHeatingCoilObjectType(const std::string& heatingCoilObjectType) {
  return getImpl<detail::AirLoopHVACUnitaryHeatOnly_Impl>()->setHeatingCoilObjectType(heatingCoilObjectType);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> AirLoopHVACUnitaryHeatOnly_Impl::maximumSupplyAirTemperature() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatOnlyFields::MaximumSupplyAirTemperature, true);
}

bool AirLoopHVACUnitaryHeatOnly_Impl::isMaximumSupplyAirTemperatureDefaulted() const {
  return isEmpty(openstudio::AirLoopHVAC_UnitaryHeatOnlyFields::MaximumSupplyAirTemperature);
}

bool AirLoopHVACUnitaryHeatOnly_Impl::isMaximumSupplyAirTemperatureAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatOnlyFields::MaximumSupplyAirTemperature, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatOnly_Impl::setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature) {
  const bool result = setDouble(openstudio::AirLoopHVAC_UnitaryHeatOnlyFields::MaximumSupplyAirTemperature, maximumSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

void AirLoopHVACUnitaryHeatOnly_Impl::resetMaximumSupplyAirTemperature() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatOnlyFields::MaximumSupplyAirTemperature, ""));
}

void AirLoopHVACUnitaryHeatOnly_Impl::autosizeMaximumSupplyAirTemperature() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatOnlyFields::MaximumSupplyAirTemperature, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatOnly_Impl::heatingSupplyAirFlowRate() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatOnlyFields::HeatingSupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatOnly_Impl::isHeatingSupplyAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatOnlyFields::HeatingSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatOnly_Impl::setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatOnlyFields::HeatingSupplyAirFlowRate, heatingSupplyAirFlowRate);
}

void AirLoopHVACUnitaryHeatOnly_Impl::autosizeHeatingSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatOnlyFields::HeatingSupplyAirFlowRate, "autosize"));
}

std::string AirLoopHVACUnitaryHeatOnly_Impl::supplyFanObjectType() const {
  const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatOnlyFields::SupplyFanObjectType, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatOnly_Impl::setSupplyFanObjectType(const std::string& supplyFanObjectType) {
  return setString(openstudio::AirLoopHVAC_UnitaryHeatOnlyFields::SupplyFanObjectType, supplyFanObjectType);
}

std::string AirLoopHVACUnitaryHeatOnly_Impl::fanPlacement() const {
  const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatOnlyFields::FanPlacement, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatOnly_Impl::setFanPlacement(const std::string& fanPlacement) {
  return setString(openstudio::AirLoopHVAC_UnitaryHeatOnlyFields::FanPlacement, fanPlacement);
}

bool AirLoopHVACUnitaryHeatOnly_Impl::isFanPlacementDefaulted() const {
  return isEmpty(openstudio::AirLoopHVAC_UnitaryHeatOnlyFields::FanPlacement);
}

void AirLoopHVACUnitaryHeatOnly_Impl::resetFanPlacement() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatOnlyFields::FanPlacement, ""));
}

std::string AirLoopHVACUnitaryHeatOnly_Impl::heatingCoilObjectType() const {
  const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatOnlyFields::HeatingCoilObjectType, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatOnly_Impl::setHeatingCoilObjectType(const std::string& heatingCoilObjectType) {
  return setString(openstudio::AirLoopHVAC_UnitaryHeatOnlyFields::HeatingCoilObjectType, heatingCoilObjectType);
}

std::vector<std::string> AirLoopHVACUnitaryHeatOnly_Impl::supplyFanObjectTypeValues() const {
  return openstudio::epmodel::AirLoopHVACUnitaryHeatOnly::supplyFanObjectTypeValues();
}

std::vector<std::string> AirLoopHVACUnitaryHeatOnly_Impl::fanPlacementValues() const {
  return openstudio::epmodel::AirLoopHVACUnitaryHeatOnly::fanPlacementValues();
}

std::vector<std::string> AirLoopHVACUnitaryHeatOnly_Impl::heatingCoilObjectTypeValues() const {
  return openstudio::epmodel::AirLoopHVACUnitaryHeatOnly::heatingCoilObjectTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
