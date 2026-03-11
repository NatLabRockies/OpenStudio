/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirLoopHVACUnitaryFurnaceHeatCool.hpp"
#include "AirLoopHVACUnitaryFurnaceHeatCool_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirLoopHVAC_Unitary_Furnace_HeatCool_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

AirLoopHVACUnitaryFurnaceHeatCool::AirLoopHVACUnitaryFurnaceHeatCool(const Model& model)
  : ModelObject(AirLoopHVACUnitaryFurnaceHeatCool::iddObjectType(), model) {}

AirLoopHVACUnitaryFurnaceHeatCool::AirLoopHVACUnitaryFurnaceHeatCool(
  std::shared_ptr<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirLoopHVACUnitaryFurnaceHeatCool::iddObjectType() {
  return IddObjectType::AirLoopHVAC_Unitary_Furnace_HeatCool;
}

std::vector<std::string> AirLoopHVACUnitaryFurnaceHeatCool::supplyFanObjectTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::SupplyFanObjectType);
}

std::vector<std::string> AirLoopHVACUnitaryFurnaceHeatCool::fanPlacementValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::FanPlacement);
}

std::vector<std::string> AirLoopHVACUnitaryFurnaceHeatCool::heatingCoilObjectTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::HeatingCoilObjectType);
}

std::vector<std::string> AirLoopHVACUnitaryFurnaceHeatCool::coolingCoilObjectTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::CoolingCoilObjectType);
}

std::vector<std::string> AirLoopHVACUnitaryFurnaceHeatCool::dehumidificationControlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::DehumidificationControlType);
}

std::vector<std::string> AirLoopHVACUnitaryFurnaceHeatCool::reheatCoilObjectTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::ReheatCoilObjectType);
}

boost::optional<double> AirLoopHVACUnitaryFurnaceHeatCool::maximumSupplyAirTemperature() const {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->maximumSupplyAirTemperature();
}

bool AirLoopHVACUnitaryFurnaceHeatCool::isMaximumSupplyAirTemperatureDefaulted() const {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->isMaximumSupplyAirTemperatureDefaulted();
}

bool AirLoopHVACUnitaryFurnaceHeatCool::isMaximumSupplyAirTemperatureAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->isMaximumSupplyAirTemperatureAutosized();
}

bool AirLoopHVACUnitaryFurnaceHeatCool::setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature) {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->setMaximumSupplyAirTemperature(maximumSupplyAirTemperature);
}

void AirLoopHVACUnitaryFurnaceHeatCool::resetMaximumSupplyAirTemperature() {
  getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->resetMaximumSupplyAirTemperature();
}

void AirLoopHVACUnitaryFurnaceHeatCool::autosizeMaximumSupplyAirTemperature() {
  getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->autosizeMaximumSupplyAirTemperature();
}

boost::optional<double> AirLoopHVACUnitaryFurnaceHeatCool::coolingSupplyAirFlowRate() const {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->coolingSupplyAirFlowRate();
}

bool AirLoopHVACUnitaryFurnaceHeatCool::isCoolingSupplyAirFlowRateAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->isCoolingSupplyAirFlowRateAutosized();
}

bool AirLoopHVACUnitaryFurnaceHeatCool::setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate) {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->setCoolingSupplyAirFlowRate(coolingSupplyAirFlowRate);
}

void AirLoopHVACUnitaryFurnaceHeatCool::autosizeCoolingSupplyAirFlowRate() {
  getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->autosizeCoolingSupplyAirFlowRate();
}

boost::optional<double> AirLoopHVACUnitaryFurnaceHeatCool::heatingSupplyAirFlowRate() const {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->heatingSupplyAirFlowRate();
}

bool AirLoopHVACUnitaryFurnaceHeatCool::isHeatingSupplyAirFlowRateAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->isHeatingSupplyAirFlowRateAutosized();
}

bool AirLoopHVACUnitaryFurnaceHeatCool::setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate) {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->setHeatingSupplyAirFlowRate(heatingSupplyAirFlowRate);
}

void AirLoopHVACUnitaryFurnaceHeatCool::autosizeHeatingSupplyAirFlowRate() {
  getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->autosizeHeatingSupplyAirFlowRate();
}

boost::optional<double> AirLoopHVACUnitaryFurnaceHeatCool::noLoadSupplyAirFlowRate() const {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->noLoadSupplyAirFlowRate();
}

bool AirLoopHVACUnitaryFurnaceHeatCool::isNoLoadSupplyAirFlowRateAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->isNoLoadSupplyAirFlowRateAutosized();
}

bool AirLoopHVACUnitaryFurnaceHeatCool::setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate) {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->setNoLoadSupplyAirFlowRate(noLoadSupplyAirFlowRate);
}

void AirLoopHVACUnitaryFurnaceHeatCool::resetNoLoadSupplyAirFlowRate() {
  getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->resetNoLoadSupplyAirFlowRate();
}

void AirLoopHVACUnitaryFurnaceHeatCool::autosizeNoLoadSupplyAirFlowRate() {
  getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->autosizeNoLoadSupplyAirFlowRate();
}

std::string AirLoopHVACUnitaryFurnaceHeatCool::supplyFanObjectType() const {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->supplyFanObjectType();
}

bool AirLoopHVACUnitaryFurnaceHeatCool::setSupplyFanObjectType(const std::string& supplyFanObjectType) {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->setSupplyFanObjectType(supplyFanObjectType);
}

std::string AirLoopHVACUnitaryFurnaceHeatCool::fanPlacement() const {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->fanPlacement();
}

bool AirLoopHVACUnitaryFurnaceHeatCool::setFanPlacement(const std::string& fanPlacement) {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->setFanPlacement(fanPlacement);
}

bool AirLoopHVACUnitaryFurnaceHeatCool::isFanPlacementDefaulted() const {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->isFanPlacementDefaulted();
}

void AirLoopHVACUnitaryFurnaceHeatCool::resetFanPlacement() {
  getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->resetFanPlacement();
}

std::string AirLoopHVACUnitaryFurnaceHeatCool::heatingCoilObjectType() const {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->heatingCoilObjectType();
}

bool AirLoopHVACUnitaryFurnaceHeatCool::setHeatingCoilObjectType(const std::string& heatingCoilObjectType) {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->setHeatingCoilObjectType(heatingCoilObjectType);
}

std::string AirLoopHVACUnitaryFurnaceHeatCool::coolingCoilObjectType() const {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->coolingCoilObjectType();
}

bool AirLoopHVACUnitaryFurnaceHeatCool::setCoolingCoilObjectType(const std::string& coolingCoilObjectType) {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->setCoolingCoilObjectType(coolingCoilObjectType);
}

std::string AirLoopHVACUnitaryFurnaceHeatCool::dehumidificationControlType() const {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->dehumidificationControlType();
}

bool AirLoopHVACUnitaryFurnaceHeatCool::setDehumidificationControlType(const std::string& dehumidificationControlType) {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->setDehumidificationControlType(dehumidificationControlType);
}

bool AirLoopHVACUnitaryFurnaceHeatCool::isDehumidificationControlTypeDefaulted() const {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->isDehumidificationControlTypeDefaulted();
}

void AirLoopHVACUnitaryFurnaceHeatCool::resetDehumidificationControlType() {
  getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->resetDehumidificationControlType();
}

boost::optional<std::string> AirLoopHVACUnitaryFurnaceHeatCool::reheatCoilObjectType() const {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->reheatCoilObjectType();
}

bool AirLoopHVACUnitaryFurnaceHeatCool::setReheatCoilObjectType(const std::string& reheatCoilObjectType) {
  return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->setReheatCoilObjectType(reheatCoilObjectType);
}

void AirLoopHVACUnitaryFurnaceHeatCool::resetReheatCoilObjectType() {
  getImpl<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl>()->resetReheatCoilObjectType();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> AirLoopHVACUnitaryFurnaceHeatCool_Impl::maximumSupplyAirTemperature() const {
  return getDouble(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::MaximumSupplyAirTemperature, true);
}

bool AirLoopHVACUnitaryFurnaceHeatCool_Impl::isMaximumSupplyAirTemperatureDefaulted() const {
  return isEmpty(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::MaximumSupplyAirTemperature);
}

bool AirLoopHVACUnitaryFurnaceHeatCool_Impl::isMaximumSupplyAirTemperatureAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::MaximumSupplyAirTemperature, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryFurnaceHeatCool_Impl::setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature) {
  const bool result = setDouble(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::MaximumSupplyAirTemperature, maximumSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

void AirLoopHVACUnitaryFurnaceHeatCool_Impl::resetMaximumSupplyAirTemperature() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::MaximumSupplyAirTemperature, ""));
}

void AirLoopHVACUnitaryFurnaceHeatCool_Impl::autosizeMaximumSupplyAirTemperature() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::MaximumSupplyAirTemperature, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryFurnaceHeatCool_Impl::coolingSupplyAirFlowRate() const {
  return getDouble(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::CoolingSupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryFurnaceHeatCool_Impl::isCoolingSupplyAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::CoolingSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryFurnaceHeatCool_Impl::setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate) {
  return setDouble(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::CoolingSupplyAirFlowRate, coolingSupplyAirFlowRate);
}

void AirLoopHVACUnitaryFurnaceHeatCool_Impl::autosizeCoolingSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::CoolingSupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryFurnaceHeatCool_Impl::heatingSupplyAirFlowRate() const {
  return getDouble(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::HeatingSupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryFurnaceHeatCool_Impl::isHeatingSupplyAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::HeatingSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryFurnaceHeatCool_Impl::setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate) {
  return setDouble(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::HeatingSupplyAirFlowRate, heatingSupplyAirFlowRate);
}

void AirLoopHVACUnitaryFurnaceHeatCool_Impl::autosizeHeatingSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::HeatingSupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryFurnaceHeatCool_Impl::noLoadSupplyAirFlowRate() const {
  return getDouble(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::NoLoadSupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryFurnaceHeatCool_Impl::isNoLoadSupplyAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::NoLoadSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryFurnaceHeatCool_Impl::setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate) {
  return setDouble(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::NoLoadSupplyAirFlowRate, noLoadSupplyAirFlowRate);
}

void AirLoopHVACUnitaryFurnaceHeatCool_Impl::resetNoLoadSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::NoLoadSupplyAirFlowRate, ""));
}

void AirLoopHVACUnitaryFurnaceHeatCool_Impl::autosizeNoLoadSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::NoLoadSupplyAirFlowRate, "autosize"));
}

std::string AirLoopHVACUnitaryFurnaceHeatCool_Impl::supplyFanObjectType() const {
  const auto value = getString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::SupplyFanObjectType, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryFurnaceHeatCool_Impl::setSupplyFanObjectType(const std::string& supplyFanObjectType) {
  return setString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::SupplyFanObjectType, supplyFanObjectType);
}

std::string AirLoopHVACUnitaryFurnaceHeatCool_Impl::fanPlacement() const {
  const auto value = getString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::FanPlacement, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryFurnaceHeatCool_Impl::setFanPlacement(const std::string& fanPlacement) {
  return setString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::FanPlacement, fanPlacement);
}

bool AirLoopHVACUnitaryFurnaceHeatCool_Impl::isFanPlacementDefaulted() const {
  return isEmpty(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::FanPlacement);
}

void AirLoopHVACUnitaryFurnaceHeatCool_Impl::resetFanPlacement() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::FanPlacement, ""));
}

std::string AirLoopHVACUnitaryFurnaceHeatCool_Impl::heatingCoilObjectType() const {
  const auto value = getString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::HeatingCoilObjectType, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryFurnaceHeatCool_Impl::setHeatingCoilObjectType(const std::string& heatingCoilObjectType) {
  return setString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::HeatingCoilObjectType, heatingCoilObjectType);
}

std::string AirLoopHVACUnitaryFurnaceHeatCool_Impl::coolingCoilObjectType() const {
  const auto value = getString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::CoolingCoilObjectType, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryFurnaceHeatCool_Impl::setCoolingCoilObjectType(const std::string& coolingCoilObjectType) {
  return setString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::CoolingCoilObjectType, coolingCoilObjectType);
}

std::string AirLoopHVACUnitaryFurnaceHeatCool_Impl::dehumidificationControlType() const {
  const auto value = getString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::DehumidificationControlType, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryFurnaceHeatCool_Impl::setDehumidificationControlType(const std::string& dehumidificationControlType) {
  return setString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::DehumidificationControlType, dehumidificationControlType);
}

bool AirLoopHVACUnitaryFurnaceHeatCool_Impl::isDehumidificationControlTypeDefaulted() const {
  return isEmpty(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::DehumidificationControlType);
}

void AirLoopHVACUnitaryFurnaceHeatCool_Impl::resetDehumidificationControlType() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::DehumidificationControlType, ""));
}

boost::optional<std::string> AirLoopHVACUnitaryFurnaceHeatCool_Impl::reheatCoilObjectType() const {
  return getString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::ReheatCoilObjectType, true);
}

bool AirLoopHVACUnitaryFurnaceHeatCool_Impl::setReheatCoilObjectType(const std::string& reheatCoilObjectType) {
  return setString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::ReheatCoilObjectType, reheatCoilObjectType);
}

void AirLoopHVACUnitaryFurnaceHeatCool_Impl::resetReheatCoilObjectType() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatCoolFields::ReheatCoilObjectType, ""));
}

std::vector<std::string> AirLoopHVACUnitaryFurnaceHeatCool_Impl::supplyFanObjectTypeValues() const {
  return openstudio::epmodel::AirLoopHVACUnitaryFurnaceHeatCool::supplyFanObjectTypeValues();
}

std::vector<std::string> AirLoopHVACUnitaryFurnaceHeatCool_Impl::fanPlacementValues() const {
  return openstudio::epmodel::AirLoopHVACUnitaryFurnaceHeatCool::fanPlacementValues();
}

std::vector<std::string> AirLoopHVACUnitaryFurnaceHeatCool_Impl::heatingCoilObjectTypeValues() const {
  return openstudio::epmodel::AirLoopHVACUnitaryFurnaceHeatCool::heatingCoilObjectTypeValues();
}

std::vector<std::string> AirLoopHVACUnitaryFurnaceHeatCool_Impl::coolingCoilObjectTypeValues() const {
  return openstudio::epmodel::AirLoopHVACUnitaryFurnaceHeatCool::coolingCoilObjectTypeValues();
}

std::vector<std::string> AirLoopHVACUnitaryFurnaceHeatCool_Impl::dehumidificationControlTypeValues() const {
  return openstudio::epmodel::AirLoopHVACUnitaryFurnaceHeatCool::dehumidificationControlTypeValues();
}

std::vector<std::string> AirLoopHVACUnitaryFurnaceHeatCool_Impl::reheatCoilObjectTypeValues() const {
  return openstudio::epmodel::AirLoopHVACUnitaryFurnaceHeatCool::reheatCoilObjectTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
