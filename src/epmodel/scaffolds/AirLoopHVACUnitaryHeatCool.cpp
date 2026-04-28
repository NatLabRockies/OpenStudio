/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirLoopHVACUnitaryHeatCool.hpp"
#include "AirLoopHVACUnitaryHeatCool_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirLoopHVAC_UnitaryHeatCool_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

AirLoopHVACUnitaryHeatCool::AirLoopHVACUnitaryHeatCool(const Model& model) : ModelObject(AirLoopHVACUnitaryHeatCool::iddObjectType(), model) {}

AirLoopHVACUnitaryHeatCool::AirLoopHVACUnitaryHeatCool(std::shared_ptr<detail::AirLoopHVACUnitaryHeatCool_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirLoopHVACUnitaryHeatCool::iddObjectType() {
  return IddObjectType::AirLoopHVAC_UnitaryHeatCool;
}

std::vector<std::string> AirLoopHVACUnitaryHeatCool::supplyFanObjectTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::AirLoopHVAC_UnitaryHeatCoolFields::SupplyFanObjectType);
}

std::vector<std::string> AirLoopHVACUnitaryHeatCool::fanPlacementValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::AirLoopHVAC_UnitaryHeatCoolFields::FanPlacement);
}

std::vector<std::string> AirLoopHVACUnitaryHeatCool::heatingCoilObjectTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::AirLoopHVAC_UnitaryHeatCoolFields::HeatingCoilObjectType);
}

std::vector<std::string> AirLoopHVACUnitaryHeatCool::coolingCoilObjectTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::AirLoopHVAC_UnitaryHeatCoolFields::CoolingCoilObjectType);
}

std::vector<std::string> AirLoopHVACUnitaryHeatCool::dehumidificationControlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirLoopHVAC_UnitaryHeatCoolFields::DehumidificationControlType);
}

std::vector<std::string> AirLoopHVACUnitaryHeatCool::reheatCoilObjectTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::AirLoopHVAC_UnitaryHeatCoolFields::ReheatCoilObjectType);
}

boost::optional<double> AirLoopHVACUnitaryHeatCool::maximumSupplyAirTemperature() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->maximumSupplyAirTemperature();
}

bool AirLoopHVACUnitaryHeatCool::isMaximumSupplyAirTemperatureDefaulted() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->isMaximumSupplyAirTemperatureDefaulted();
}

bool AirLoopHVACUnitaryHeatCool::isMaximumSupplyAirTemperatureAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->isMaximumSupplyAirTemperatureAutosized();
}

bool AirLoopHVACUnitaryHeatCool::setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature) {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setMaximumSupplyAirTemperature(maximumSupplyAirTemperature);
}

void AirLoopHVACUnitaryHeatCool::resetMaximumSupplyAirTemperature() {
  getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->resetMaximumSupplyAirTemperature();
}

void AirLoopHVACUnitaryHeatCool::autosizeMaximumSupplyAirTemperature() {
  getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->autosizeMaximumSupplyAirTemperature();
}

boost::optional<double> AirLoopHVACUnitaryHeatCool::coolingSupplyAirFlowRate() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->coolingSupplyAirFlowRate();
}

bool AirLoopHVACUnitaryHeatCool::isCoolingSupplyAirFlowRateAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->isCoolingSupplyAirFlowRateAutosized();
}

bool AirLoopHVACUnitaryHeatCool::setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate) {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setCoolingSupplyAirFlowRate(coolingSupplyAirFlowRate);
}

void AirLoopHVACUnitaryHeatCool::autosizeCoolingSupplyAirFlowRate() {
  getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->autosizeCoolingSupplyAirFlowRate();
}

boost::optional<double> AirLoopHVACUnitaryHeatCool::heatingSupplyAirFlowRate() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->heatingSupplyAirFlowRate();
}

bool AirLoopHVACUnitaryHeatCool::isHeatingSupplyAirFlowRateAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->isHeatingSupplyAirFlowRateAutosized();
}

bool AirLoopHVACUnitaryHeatCool::setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate) {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setHeatingSupplyAirFlowRate(heatingSupplyAirFlowRate);
}

void AirLoopHVACUnitaryHeatCool::autosizeHeatingSupplyAirFlowRate() {
  getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->autosizeHeatingSupplyAirFlowRate();
}

boost::optional<double> AirLoopHVACUnitaryHeatCool::noLoadSupplyAirFlowRate() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->noLoadSupplyAirFlowRate();
}

bool AirLoopHVACUnitaryHeatCool::isNoLoadSupplyAirFlowRateAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->isNoLoadSupplyAirFlowRateAutosized();
}

bool AirLoopHVACUnitaryHeatCool::setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate) {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setNoLoadSupplyAirFlowRate(noLoadSupplyAirFlowRate);
}

void AirLoopHVACUnitaryHeatCool::resetNoLoadSupplyAirFlowRate() {
  getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->resetNoLoadSupplyAirFlowRate();
}

void AirLoopHVACUnitaryHeatCool::autosizeNoLoadSupplyAirFlowRate() {
  getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->autosizeNoLoadSupplyAirFlowRate();
}

std::string AirLoopHVACUnitaryHeatCool::supplyFanObjectType() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->supplyFanObjectType();
}

bool AirLoopHVACUnitaryHeatCool::setSupplyFanObjectType(const std::string& supplyFanObjectType) {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setSupplyFanObjectType(supplyFanObjectType);
}

std::string AirLoopHVACUnitaryHeatCool::fanPlacement() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->fanPlacement();
}

bool AirLoopHVACUnitaryHeatCool::setFanPlacement(const std::string& fanPlacement) {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setFanPlacement(fanPlacement);
}

bool AirLoopHVACUnitaryHeatCool::isFanPlacementDefaulted() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->isFanPlacementDefaulted();
}

void AirLoopHVACUnitaryHeatCool::resetFanPlacement() {
  getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->resetFanPlacement();
}

std::string AirLoopHVACUnitaryHeatCool::heatingCoilObjectType() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->heatingCoilObjectType();
}

bool AirLoopHVACUnitaryHeatCool::setHeatingCoilObjectType(const std::string& heatingCoilObjectType) {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setHeatingCoilObjectType(heatingCoilObjectType);
}

std::string AirLoopHVACUnitaryHeatCool::coolingCoilObjectType() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->coolingCoilObjectType();
}

bool AirLoopHVACUnitaryHeatCool::setCoolingCoilObjectType(const std::string& coolingCoilObjectType) {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setCoolingCoilObjectType(coolingCoilObjectType);
}

std::string AirLoopHVACUnitaryHeatCool::dehumidificationControlType() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->dehumidificationControlType();
}

bool AirLoopHVACUnitaryHeatCool::setDehumidificationControlType(const std::string& dehumidificationControlType) {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setDehumidificationControlType(dehumidificationControlType);
}

bool AirLoopHVACUnitaryHeatCool::isDehumidificationControlTypeDefaulted() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->isDehumidificationControlTypeDefaulted();
}

void AirLoopHVACUnitaryHeatCool::resetDehumidificationControlType() {
  getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->resetDehumidificationControlType();
}

boost::optional<std::string> AirLoopHVACUnitaryHeatCool::reheatCoilObjectType() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->reheatCoilObjectType();
}

bool AirLoopHVACUnitaryHeatCool::setReheatCoilObjectType(const std::string& reheatCoilObjectType) {
  return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setReheatCoilObjectType(reheatCoilObjectType);
}

void AirLoopHVACUnitaryHeatCool::resetReheatCoilObjectType() {
  getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->resetReheatCoilObjectType();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> AirLoopHVACUnitaryHeatCool_Impl::maximumSupplyAirTemperature() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::MaximumSupplyAirTemperature, true);
}

bool AirLoopHVACUnitaryHeatCool_Impl::isMaximumSupplyAirTemperatureDefaulted() const {
  return isEmpty(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::MaximumSupplyAirTemperature);
}

bool AirLoopHVACUnitaryHeatCool_Impl::isMaximumSupplyAirTemperatureAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::MaximumSupplyAirTemperature, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatCool_Impl::setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature) {
  const bool result = setDouble(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::MaximumSupplyAirTemperature, maximumSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

void AirLoopHVACUnitaryHeatCool_Impl::resetMaximumSupplyAirTemperature() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::MaximumSupplyAirTemperature, ""));
}

void AirLoopHVACUnitaryHeatCool_Impl::autosizeMaximumSupplyAirTemperature() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::MaximumSupplyAirTemperature, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatCool_Impl::coolingSupplyAirFlowRate() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::CoolingSupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatCool_Impl::isCoolingSupplyAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::CoolingSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatCool_Impl::setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::CoolingSupplyAirFlowRate, coolingSupplyAirFlowRate);
}

void AirLoopHVACUnitaryHeatCool_Impl::autosizeCoolingSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::CoolingSupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatCool_Impl::heatingSupplyAirFlowRate() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::HeatingSupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatCool_Impl::isHeatingSupplyAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::HeatingSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatCool_Impl::setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::HeatingSupplyAirFlowRate, heatingSupplyAirFlowRate);
}

void AirLoopHVACUnitaryHeatCool_Impl::autosizeHeatingSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::HeatingSupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatCool_Impl::noLoadSupplyAirFlowRate() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::NoLoadSupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatCool_Impl::isNoLoadSupplyAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::NoLoadSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatCool_Impl::setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::NoLoadSupplyAirFlowRate, noLoadSupplyAirFlowRate);
}

void AirLoopHVACUnitaryHeatCool_Impl::resetNoLoadSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::NoLoadSupplyAirFlowRate, ""));
}

void AirLoopHVACUnitaryHeatCool_Impl::autosizeNoLoadSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::NoLoadSupplyAirFlowRate, "autosize"));
}

std::string AirLoopHVACUnitaryHeatCool_Impl::supplyFanObjectType() const {
  const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::SupplyFanObjectType, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatCool_Impl::setSupplyFanObjectType(const std::string& supplyFanObjectType) {
  return setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::SupplyFanObjectType, supplyFanObjectType);
}

std::string AirLoopHVACUnitaryHeatCool_Impl::fanPlacement() const {
  const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::FanPlacement, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatCool_Impl::setFanPlacement(const std::string& fanPlacement) {
  return setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::FanPlacement, fanPlacement);
}

bool AirLoopHVACUnitaryHeatCool_Impl::isFanPlacementDefaulted() const {
  return isEmpty(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::FanPlacement);
}

void AirLoopHVACUnitaryHeatCool_Impl::resetFanPlacement() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::FanPlacement, ""));
}

std::string AirLoopHVACUnitaryHeatCool_Impl::heatingCoilObjectType() const {
  const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::HeatingCoilObjectType, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatCool_Impl::setHeatingCoilObjectType(const std::string& heatingCoilObjectType) {
  return setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::HeatingCoilObjectType, heatingCoilObjectType);
}

std::string AirLoopHVACUnitaryHeatCool_Impl::coolingCoilObjectType() const {
  const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::CoolingCoilObjectType, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatCool_Impl::setCoolingCoilObjectType(const std::string& coolingCoilObjectType) {
  return setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::CoolingCoilObjectType, coolingCoilObjectType);
}

std::string AirLoopHVACUnitaryHeatCool_Impl::dehumidificationControlType() const {
  const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::DehumidificationControlType, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatCool_Impl::setDehumidificationControlType(const std::string& dehumidificationControlType) {
  return setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::DehumidificationControlType, dehumidificationControlType);
}

bool AirLoopHVACUnitaryHeatCool_Impl::isDehumidificationControlTypeDefaulted() const {
  return isEmpty(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::DehumidificationControlType);
}

void AirLoopHVACUnitaryHeatCool_Impl::resetDehumidificationControlType() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::DehumidificationControlType, ""));
}

boost::optional<std::string> AirLoopHVACUnitaryHeatCool_Impl::reheatCoilObjectType() const {
  return getString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::ReheatCoilObjectType, true);
}

bool AirLoopHVACUnitaryHeatCool_Impl::setReheatCoilObjectType(const std::string& reheatCoilObjectType) {
  return setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::ReheatCoilObjectType, reheatCoilObjectType);
}

void AirLoopHVACUnitaryHeatCool_Impl::resetReheatCoilObjectType() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::ReheatCoilObjectType, ""));
}

std::vector<std::string> AirLoopHVACUnitaryHeatCool_Impl::supplyFanObjectTypeValues() const {
  return openstudio::epmodel::AirLoopHVACUnitaryHeatCool::supplyFanObjectTypeValues();
}

std::vector<std::string> AirLoopHVACUnitaryHeatCool_Impl::fanPlacementValues() const {
  return openstudio::epmodel::AirLoopHVACUnitaryHeatCool::fanPlacementValues();
}

std::vector<std::string> AirLoopHVACUnitaryHeatCool_Impl::heatingCoilObjectTypeValues() const {
  return openstudio::epmodel::AirLoopHVACUnitaryHeatCool::heatingCoilObjectTypeValues();
}

std::vector<std::string> AirLoopHVACUnitaryHeatCool_Impl::coolingCoilObjectTypeValues() const {
  return openstudio::epmodel::AirLoopHVACUnitaryHeatCool::coolingCoilObjectTypeValues();
}

std::vector<std::string> AirLoopHVACUnitaryHeatCool_Impl::dehumidificationControlTypeValues() const {
  return openstudio::epmodel::AirLoopHVACUnitaryHeatCool::dehumidificationControlTypeValues();
}

std::vector<std::string> AirLoopHVACUnitaryHeatCool_Impl::reheatCoilObjectTypeValues() const {
  return openstudio::epmodel::AirLoopHVACUnitaryHeatCool::reheatCoilObjectTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
