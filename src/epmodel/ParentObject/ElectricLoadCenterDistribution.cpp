/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/ElectricLoadCenterDistribution.hpp"
#include "ParentObject/ElectricLoadCenterDistribution_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ElectricLoadCenter_Distribution_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

ElectricLoadCenterDistribution::ElectricLoadCenterDistribution(const Model& model)
  : ParentObject(ElectricLoadCenterDistribution::iddObjectType(), model) {}

ElectricLoadCenterDistribution::ElectricLoadCenterDistribution(std::shared_ptr<detail::ElectricLoadCenterDistribution_Impl> impl)
  : ParentObject(std::move(impl)) {}

IddObjectType ElectricLoadCenterDistribution::iddObjectType() {
  return IddObjectType::ElectricLoadCenter_Distribution;
}

std::vector<std::string> ElectricLoadCenterDistribution::generatorOperationSchemeTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::ElectricLoadCenter_DistributionFields::GeneratorOperationSchemeType);
}

std::vector<std::string> ElectricLoadCenterDistribution::electricalBussTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::ElectricLoadCenter_DistributionFields::ElectricalBussType);
}

std::vector<std::string> ElectricLoadCenterDistribution::storageOperationSchemeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::ElectricLoadCenter_DistributionFields::StorageOperationScheme);
}

std::string ElectricLoadCenterDistribution::generatorOperationSchemeType() const {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->generatorOperationSchemeType();
}

bool ElectricLoadCenterDistribution::isGeneratorOperationSchemeTypeDefaulted() const {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->isGeneratorOperationSchemeTypeDefaulted();
}

bool ElectricLoadCenterDistribution::setGeneratorOperationSchemeType(const std::string& generatorOperationSchemeType) {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->setGeneratorOperationSchemeType(generatorOperationSchemeType);
}

void ElectricLoadCenterDistribution::resetGeneratorOperationSchemeType() {
  getImpl<detail::ElectricLoadCenterDistribution_Impl>()->resetGeneratorOperationSchemeType();
}

boost::optional<double> ElectricLoadCenterDistribution::demandLimitSchemePurchasedElectricDemandLimit() const {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->demandLimitSchemePurchasedElectricDemandLimit();
}

bool ElectricLoadCenterDistribution::setDemandLimitSchemePurchasedElectricDemandLimit(double demandLimitSchemePurchasedElectricDemandLimit) {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->setDemandLimitSchemePurchasedElectricDemandLimit(
    demandLimitSchemePurchasedElectricDemandLimit);
}

void ElectricLoadCenterDistribution::resetDemandLimitSchemePurchasedElectricDemandLimit() {
  getImpl<detail::ElectricLoadCenterDistribution_Impl>()->resetDemandLimitSchemePurchasedElectricDemandLimit();
}

boost::optional<std::string> ElectricLoadCenterDistribution::trackMeterSchemeMeterName() const {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->trackMeterSchemeMeterName();
}

bool ElectricLoadCenterDistribution::setTrackMeterSchemeMeterName(const std::string& trackMeterSchemeMeterName) {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->setTrackMeterSchemeMeterName(trackMeterSchemeMeterName);
}

void ElectricLoadCenterDistribution::resetTrackMeterSchemeMeterName() {
  getImpl<detail::ElectricLoadCenterDistribution_Impl>()->resetTrackMeterSchemeMeterName();
}

std::string ElectricLoadCenterDistribution::electricalBussType() const {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->electricalBussType();
}

bool ElectricLoadCenterDistribution::isElectricalBussTypeDefaulted() const {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->isElectricalBussTypeDefaulted();
}

bool ElectricLoadCenterDistribution::setElectricalBussType(const std::string& electricalBussType) {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->setElectricalBussType(electricalBussType);
}

void ElectricLoadCenterDistribution::resetElectricalBussType() {
  getImpl<detail::ElectricLoadCenterDistribution_Impl>()->resetElectricalBussType();
}

std::string ElectricLoadCenterDistribution::storageOperationScheme() const {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->storageOperationScheme();
}

bool ElectricLoadCenterDistribution::isStorageOperationSchemeDefaulted() const {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->isStorageOperationSchemeDefaulted();
}

bool ElectricLoadCenterDistribution::setStorageOperationScheme(const std::string& operationScheme) {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->setStorageOperationScheme(operationScheme);
}

void ElectricLoadCenterDistribution::resetStorageOperationScheme() {
  getImpl<detail::ElectricLoadCenterDistribution_Impl>()->resetStorageOperationScheme();
}

boost::optional<std::string> ElectricLoadCenterDistribution::storageControlTrackMeterName() const {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->storageControlTrackMeterName();
}

bool ElectricLoadCenterDistribution::setStorageControlTrackMeterName(const std::string& meterName) {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->setStorageControlTrackMeterName(meterName);
}

void ElectricLoadCenterDistribution::resetStorageControlTrackMeterName() {
  getImpl<detail::ElectricLoadCenterDistribution_Impl>()->resetStorageControlTrackMeterName();
}

double ElectricLoadCenterDistribution::maximumStorageStateofChargeFraction() const {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->maximumStorageStateofChargeFraction();
}

bool ElectricLoadCenterDistribution::isMaximumStorageStateofChargeFractionDefaulted() const {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->isMaximumStorageStateofChargeFractionDefaulted();
}

bool ElectricLoadCenterDistribution::setMaximumStorageStateofChargeFraction(double maxStateofCharge) {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->setMaximumStorageStateofChargeFraction(maxStateofCharge);
}

void ElectricLoadCenterDistribution::resetMaximumStorageStateofChargeFraction() {
  getImpl<detail::ElectricLoadCenterDistribution_Impl>()->resetMaximumStorageStateofChargeFraction();
}

double ElectricLoadCenterDistribution::minimumStorageStateofChargeFraction() const {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->minimumStorageStateofChargeFraction();
}

bool ElectricLoadCenterDistribution::isMinimumStorageStateofChargeFractionDefaulted() const {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->isMinimumStorageStateofChargeFractionDefaulted();
}

bool ElectricLoadCenterDistribution::setMinimumStorageStateofChargeFraction(double minStateofCharge) {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->setMinimumStorageStateofChargeFraction(minStateofCharge);
}

void ElectricLoadCenterDistribution::resetMinimumStorageStateofChargeFraction() {
  getImpl<detail::ElectricLoadCenterDistribution_Impl>()->resetMinimumStorageStateofChargeFraction();
}

boost::optional<double> ElectricLoadCenterDistribution::designStorageControlChargePower() const {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->designStorageControlChargePower();
}

bool ElectricLoadCenterDistribution::setDesignStorageControlChargePower(double designStorageControlChargePower) {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->setDesignStorageControlChargePower(designStorageControlChargePower);
}

void ElectricLoadCenterDistribution::resetDesignStorageControlChargePower() {
  getImpl<detail::ElectricLoadCenterDistribution_Impl>()->resetDesignStorageControlChargePower();
}

boost::optional<double> ElectricLoadCenterDistribution::designStorageControlDischargePower() const {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->designStorageControlDischargePower();
}

bool ElectricLoadCenterDistribution::setDesignStorageControlDischargePower(double designStorageControlDischargePower) {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->setDesignStorageControlDischargePower(designStorageControlDischargePower);
}

void ElectricLoadCenterDistribution::resetDesignStorageControlDischargePower() {
  getImpl<detail::ElectricLoadCenterDistribution_Impl>()->resetDesignStorageControlDischargePower();
}

boost::optional<double> ElectricLoadCenterDistribution::storageControlUtilityDemandTarget() const {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->storageControlUtilityDemandTarget();
}

bool ElectricLoadCenterDistribution::setStorageControlUtilityDemandTarget(double storageControlUtilityDemandTarget) {
  return getImpl<detail::ElectricLoadCenterDistribution_Impl>()->setStorageControlUtilityDemandTarget(storageControlUtilityDemandTarget);
}

void ElectricLoadCenterDistribution::resetStorageControlUtilityDemandTarget() {
  getImpl<detail::ElectricLoadCenterDistribution_Impl>()->resetStorageControlUtilityDemandTarget();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

// Schema Alignment Notes:
// - This implementation intentionally omits ElectricLoadCenter:Generators extensible-group field accessors.
// - Forward translation maps generator-list fields through Generator objects attached to ElectricLoadCenterDistribution.

std::string ElectricLoadCenterDistribution_Impl::generatorOperationSchemeType() const {
  const auto value = getString(openstudio::ElectricLoadCenter_DistributionFields::GeneratorOperationSchemeType, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricLoadCenterDistribution_Impl::isGeneratorOperationSchemeTypeDefaulted() const {
  return isEmpty(openstudio::ElectricLoadCenter_DistributionFields::GeneratorOperationSchemeType);
}

bool ElectricLoadCenterDistribution_Impl::setGeneratorOperationSchemeType(const std::string& generatorOperationSchemeType) {
  return setString(openstudio::ElectricLoadCenter_DistributionFields::GeneratorOperationSchemeType, generatorOperationSchemeType);
}

void ElectricLoadCenterDistribution_Impl::resetGeneratorOperationSchemeType() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_DistributionFields::GeneratorOperationSchemeType, ""));
}

boost::optional<double> ElectricLoadCenterDistribution_Impl::demandLimitSchemePurchasedElectricDemandLimit() const {
  return getDouble(openstudio::ElectricLoadCenter_DistributionFields::GeneratorDemandLimitSchemePurchasedElectricDemandLimit, true);
}

bool ElectricLoadCenterDistribution_Impl::setDemandLimitSchemePurchasedElectricDemandLimit(double demandLimitSchemePurchasedElectricDemandLimit) {
  const bool result = setDouble(openstudio::ElectricLoadCenter_DistributionFields::GeneratorDemandLimitSchemePurchasedElectricDemandLimit,
                                demandLimitSchemePurchasedElectricDemandLimit);
  OS_ASSERT(result);
  return result;
}

void ElectricLoadCenterDistribution_Impl::resetDemandLimitSchemePurchasedElectricDemandLimit() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_DistributionFields::GeneratorDemandLimitSchemePurchasedElectricDemandLimit, ""));
}

boost::optional<std::string> ElectricLoadCenterDistribution_Impl::trackMeterSchemeMeterName() const {
  return getString(openstudio::ElectricLoadCenter_DistributionFields::GeneratorTrackMeterSchemeMeterName, true, true);
}

bool ElectricLoadCenterDistribution_Impl::setTrackMeterSchemeMeterName(const std::string& trackMeterSchemeMeterName) {
  return setString(openstudio::ElectricLoadCenter_DistributionFields::GeneratorTrackMeterSchemeMeterName, trackMeterSchemeMeterName);
}

void ElectricLoadCenterDistribution_Impl::resetTrackMeterSchemeMeterName() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_DistributionFields::GeneratorTrackMeterSchemeMeterName, ""));
}

std::string ElectricLoadCenterDistribution_Impl::electricalBussType() const {
  const auto value = getString(openstudio::ElectricLoadCenter_DistributionFields::ElectricalBussType, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricLoadCenterDistribution_Impl::isElectricalBussTypeDefaulted() const {
  return isEmpty(openstudio::ElectricLoadCenter_DistributionFields::ElectricalBussType);
}

bool ElectricLoadCenterDistribution_Impl::setElectricalBussType(const std::string& electricalBussType) {
  return setString(openstudio::ElectricLoadCenter_DistributionFields::ElectricalBussType, electricalBussType);
}

void ElectricLoadCenterDistribution_Impl::resetElectricalBussType() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_DistributionFields::ElectricalBussType, ""));
}

std::string ElectricLoadCenterDistribution_Impl::storageOperationScheme() const {
  const auto value = getString(openstudio::ElectricLoadCenter_DistributionFields::StorageOperationScheme, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricLoadCenterDistribution_Impl::isStorageOperationSchemeDefaulted() const {
  return isEmpty(openstudio::ElectricLoadCenter_DistributionFields::StorageOperationScheme);
}

bool ElectricLoadCenterDistribution_Impl::setStorageOperationScheme(const std::string& operationScheme) {
  return setString(openstudio::ElectricLoadCenter_DistributionFields::StorageOperationScheme, operationScheme);
}

void ElectricLoadCenterDistribution_Impl::resetStorageOperationScheme() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_DistributionFields::StorageOperationScheme, ""));
}

boost::optional<std::string> ElectricLoadCenterDistribution_Impl::storageControlTrackMeterName() const {
  return getString(openstudio::ElectricLoadCenter_DistributionFields::StorageControlTrackMeterName, true, true);
}

bool ElectricLoadCenterDistribution_Impl::setStorageControlTrackMeterName(const std::string& meterName) {
  return setString(openstudio::ElectricLoadCenter_DistributionFields::StorageControlTrackMeterName, meterName);
}

void ElectricLoadCenterDistribution_Impl::resetStorageControlTrackMeterName() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_DistributionFields::StorageControlTrackMeterName, ""));
}

double ElectricLoadCenterDistribution_Impl::maximumStorageStateofChargeFraction() const {
  const auto value = getDouble(openstudio::ElectricLoadCenter_DistributionFields::MaximumStorageStateofChargeFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricLoadCenterDistribution_Impl::isMaximumStorageStateofChargeFractionDefaulted() const {
  return isEmpty(openstudio::ElectricLoadCenter_DistributionFields::MaximumStorageStateofChargeFraction);
}

bool ElectricLoadCenterDistribution_Impl::setMaximumStorageStateofChargeFraction(double maxStateofCharge) {
  const bool result = setDouble(openstudio::ElectricLoadCenter_DistributionFields::MaximumStorageStateofChargeFraction, maxStateofCharge);
  OS_ASSERT(result);
  return result;
}

void ElectricLoadCenterDistribution_Impl::resetMaximumStorageStateofChargeFraction() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_DistributionFields::MaximumStorageStateofChargeFraction, ""));
}

double ElectricLoadCenterDistribution_Impl::minimumStorageStateofChargeFraction() const {
  const auto value = getDouble(openstudio::ElectricLoadCenter_DistributionFields::MinimumStorageStateofChargeFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricLoadCenterDistribution_Impl::isMinimumStorageStateofChargeFractionDefaulted() const {
  return isEmpty(openstudio::ElectricLoadCenter_DistributionFields::MinimumStorageStateofChargeFraction);
}

bool ElectricLoadCenterDistribution_Impl::setMinimumStorageStateofChargeFraction(double minStateofCharge) {
  const bool result = setDouble(openstudio::ElectricLoadCenter_DistributionFields::MinimumStorageStateofChargeFraction, minStateofCharge);
  OS_ASSERT(result);
  return result;
}

void ElectricLoadCenterDistribution_Impl::resetMinimumStorageStateofChargeFraction() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_DistributionFields::MinimumStorageStateofChargeFraction, ""));
}

boost::optional<double> ElectricLoadCenterDistribution_Impl::designStorageControlChargePower() const {
  return getDouble(openstudio::ElectricLoadCenter_DistributionFields::DesignStorageControlChargePower, true);
}

bool ElectricLoadCenterDistribution_Impl::setDesignStorageControlChargePower(double designStorageControlChargePower) {
  const bool result = setDouble(openstudio::ElectricLoadCenter_DistributionFields::DesignStorageControlChargePower, designStorageControlChargePower);
  OS_ASSERT(result);
  return result;
}

void ElectricLoadCenterDistribution_Impl::resetDesignStorageControlChargePower() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_DistributionFields::DesignStorageControlChargePower, ""));
}

boost::optional<double> ElectricLoadCenterDistribution_Impl::designStorageControlDischargePower() const {
  return getDouble(openstudio::ElectricLoadCenter_DistributionFields::DesignStorageControlDischargePower, true);
}

bool ElectricLoadCenterDistribution_Impl::setDesignStorageControlDischargePower(double designStorageControlDischargePower) {
  const bool result =
    setDouble(openstudio::ElectricLoadCenter_DistributionFields::DesignStorageControlDischargePower, designStorageControlDischargePower);
  OS_ASSERT(result);
  return result;
}

void ElectricLoadCenterDistribution_Impl::resetDesignStorageControlDischargePower() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_DistributionFields::DesignStorageControlDischargePower, ""));
}

boost::optional<double> ElectricLoadCenterDistribution_Impl::storageControlUtilityDemandTarget() const {
  return getDouble(openstudio::ElectricLoadCenter_DistributionFields::StorageControlUtilityDemandTarget, true);
}

bool ElectricLoadCenterDistribution_Impl::setStorageControlUtilityDemandTarget(double storageControlUtilityDemandTarget) {
  const bool result =
    setDouble(openstudio::ElectricLoadCenter_DistributionFields::StorageControlUtilityDemandTarget, storageControlUtilityDemandTarget);
  OS_ASSERT(result);
  return result;
}

void ElectricLoadCenterDistribution_Impl::resetStorageControlUtilityDemandTarget() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_DistributionFields::StorageControlUtilityDemandTarget, ""));
}

std::vector<std::string> ElectricLoadCenterDistribution_Impl::generatorOperationSchemeTypeValues() const {
  return openstudio::epmodel::ElectricLoadCenterDistribution::generatorOperationSchemeTypeValues();
}

std::vector<std::string> ElectricLoadCenterDistribution_Impl::electricalBussTypeValues() const {
  return openstudio::epmodel::ElectricLoadCenterDistribution::electricalBussTypeValues();
}

std::vector<std::string> ElectricLoadCenterDistribution_Impl::storageOperationSchemeValues() const {
  return openstudio::epmodel::ElectricLoadCenterDistribution::storageOperationSchemeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
