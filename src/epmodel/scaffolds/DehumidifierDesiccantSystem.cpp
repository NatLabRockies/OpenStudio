/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "DehumidifierDesiccantSystem.hpp"
#include "DehumidifierDesiccantSystem_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Dehumidifier_Desiccant_System_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

DehumidifierDesiccantSystem::DehumidifierDesiccantSystem(const Model& model)
  : ModelObject(DehumidifierDesiccantSystem::iddObjectType(), model) {}

DehumidifierDesiccantSystem::DehumidifierDesiccantSystem(std::shared_ptr<detail::DehumidifierDesiccantSystem_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType DehumidifierDesiccantSystem::iddObjectType() {
  return IddObjectType::Dehumidifier_Desiccant_System;
}

std::vector<std::string> DehumidifierDesiccantSystem::desiccantHeatExchangerObjectTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Dehumidifier_Desiccant_SystemFields::DesiccantHeatExchangerObjectType);
}

std::vector<std::string> DehumidifierDesiccantSystem::regenerationAirFanObjectTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Dehumidifier_Desiccant_SystemFields::RegenerationAirFanObjectType);
}

std::vector<std::string> DehumidifierDesiccantSystem::regenerationAirFanPlacementValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Dehumidifier_Desiccant_SystemFields::RegenerationAirFanPlacement);
}

std::vector<std::string> DehumidifierDesiccantSystem::regenerationAirHeaterObjectTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Dehumidifier_Desiccant_SystemFields::RegenerationAirHeaterObjectType);
}

std::vector<std::string> DehumidifierDesiccantSystem::companionCoolingCoilObjectTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Dehumidifier_Desiccant_SystemFields::CompanionCoolingCoilObjectType);
}

std::string DehumidifierDesiccantSystem::desiccantHeatExchangerObjectType() const {
  return getImpl<detail::DehumidifierDesiccantSystem_Impl>()->desiccantHeatExchangerObjectType();
}

bool DehumidifierDesiccantSystem::setDesiccantHeatExchangerObjectType(const std::string& desiccantHeatExchangerObjectType) {
  return getImpl<detail::DehumidifierDesiccantSystem_Impl>()->setDesiccantHeatExchangerObjectType(desiccantHeatExchangerObjectType);
}

std::string DehumidifierDesiccantSystem::regenerationAirFanObjectType() const {
  return getImpl<detail::DehumidifierDesiccantSystem_Impl>()->regenerationAirFanObjectType();
}

bool DehumidifierDesiccantSystem::setRegenerationAirFanObjectType(const std::string& regenerationAirFanObjectType) {
  return getImpl<detail::DehumidifierDesiccantSystem_Impl>()->setRegenerationAirFanObjectType(regenerationAirFanObjectType);
}

std::string DehumidifierDesiccantSystem::regenerationAirFanPlacement() const {
  return getImpl<detail::DehumidifierDesiccantSystem_Impl>()->regenerationAirFanPlacement();
}

bool DehumidifierDesiccantSystem::isRegenerationAirFanPlacementDefaulted() const {
  return getImpl<detail::DehumidifierDesiccantSystem_Impl>()->isRegenerationAirFanPlacementDefaulted();
}

bool DehumidifierDesiccantSystem::setRegenerationAirFanPlacement(const std::string& regenerationAirFanPlacement) {
  return getImpl<detail::DehumidifierDesiccantSystem_Impl>()->setRegenerationAirFanPlacement(regenerationAirFanPlacement);
}

void DehumidifierDesiccantSystem::resetRegenerationAirFanPlacement() {
  getImpl<detail::DehumidifierDesiccantSystem_Impl>()->resetRegenerationAirFanPlacement();
}

boost::optional<std::string> DehumidifierDesiccantSystem::regenerationAirHeaterObjectType() const {
  return getImpl<detail::DehumidifierDesiccantSystem_Impl>()->regenerationAirHeaterObjectType();
}

bool DehumidifierDesiccantSystem::setRegenerationAirHeaterObjectType(const std::string& regenerationAirHeaterObjectType) {
  return getImpl<detail::DehumidifierDesiccantSystem_Impl>()->setRegenerationAirHeaterObjectType(regenerationAirHeaterObjectType);
}

void DehumidifierDesiccantSystem::resetRegenerationAirHeaterObjectType() {
  getImpl<detail::DehumidifierDesiccantSystem_Impl>()->resetRegenerationAirHeaterObjectType();
}

double DehumidifierDesiccantSystem::regenerationInletAirSetpointTemperature() const {
  return getImpl<detail::DehumidifierDesiccantSystem_Impl>()->regenerationInletAirSetpointTemperature();
}

bool DehumidifierDesiccantSystem::isRegenerationInletAirSetpointTemperatureDefaulted() const {
  return getImpl<detail::DehumidifierDesiccantSystem_Impl>()->isRegenerationInletAirSetpointTemperatureDefaulted();
}

bool DehumidifierDesiccantSystem::setRegenerationInletAirSetpointTemperature(double regenerationInletAirSetpointTemperature) {
  return getImpl<detail::DehumidifierDesiccantSystem_Impl>()->setRegenerationInletAirSetpointTemperature(regenerationInletAirSetpointTemperature);
}

void DehumidifierDesiccantSystem::resetRegenerationInletAirSetpointTemperature() {
  getImpl<detail::DehumidifierDesiccantSystem_Impl>()->resetRegenerationInletAirSetpointTemperature();
}

boost::optional<std::string> DehumidifierDesiccantSystem::companionCoolingCoilObjectType() const {
  return getImpl<detail::DehumidifierDesiccantSystem_Impl>()->companionCoolingCoilObjectType();
}

bool DehumidifierDesiccantSystem::setCompanionCoolingCoilObjectType(const std::string& companionCoolingCoilObjectType) {
  return getImpl<detail::DehumidifierDesiccantSystem_Impl>()->setCompanionCoolingCoilObjectType(companionCoolingCoilObjectType);
}

void DehumidifierDesiccantSystem::resetCompanionCoolingCoilObjectType() {
  getImpl<detail::DehumidifierDesiccantSystem_Impl>()->resetCompanionCoolingCoilObjectType();
}

bool DehumidifierDesiccantSystem::companionCoolingCoilUpstreamofDehumidifierProcessInlet() const {
  return getImpl<detail::DehumidifierDesiccantSystem_Impl>()->companionCoolingCoilUpstreamofDehumidifierProcessInlet();
}

bool DehumidifierDesiccantSystem::isCompanionCoolingCoilUpstreamofDehumidifierProcessInletDefaulted() const {
  return getImpl<detail::DehumidifierDesiccantSystem_Impl>()->isCompanionCoolingCoilUpstreamofDehumidifierProcessInletDefaulted();
}

bool DehumidifierDesiccantSystem::setCompanionCoolingCoilUpstreamofDehumidifierProcessInlet(
  bool companionCoolingCoilUpstreamofDehumidifierProcessInlet) {
  return getImpl<detail::DehumidifierDesiccantSystem_Impl>()->setCompanionCoolingCoilUpstreamofDehumidifierProcessInlet(
    companionCoolingCoilUpstreamofDehumidifierProcessInlet);
}

void DehumidifierDesiccantSystem::resetCompanionCoolingCoilUpstreamofDehumidifierProcessInlet() {
  getImpl<detail::DehumidifierDesiccantSystem_Impl>()->resetCompanionCoolingCoilUpstreamofDehumidifierProcessInlet();
}

bool DehumidifierDesiccantSystem::companionCoilRegenerationAirHeating() const {
  return getImpl<detail::DehumidifierDesiccantSystem_Impl>()->companionCoilRegenerationAirHeating();
}

bool DehumidifierDesiccantSystem::isCompanionCoilRegenerationAirHeatingDefaulted() const {
  return getImpl<detail::DehumidifierDesiccantSystem_Impl>()->isCompanionCoilRegenerationAirHeatingDefaulted();
}

bool DehumidifierDesiccantSystem::setCompanionCoilRegenerationAirHeating(bool companionCoilRegenerationAirHeating) {
  return getImpl<detail::DehumidifierDesiccantSystem_Impl>()->setCompanionCoilRegenerationAirHeating(companionCoilRegenerationAirHeating);
}

void DehumidifierDesiccantSystem::resetCompanionCoilRegenerationAirHeating() {
  getImpl<detail::DehumidifierDesiccantSystem_Impl>()->resetCompanionCoilRegenerationAirHeating();
}

boost::optional<double> DehumidifierDesiccantSystem::exhaustFanMaximumFlowRate() const {
  return getImpl<detail::DehumidifierDesiccantSystem_Impl>()->exhaustFanMaximumFlowRate();
}

bool DehumidifierDesiccantSystem::setExhaustFanMaximumFlowRate(double exhaustFanMaximumFlowRate) {
  return getImpl<detail::DehumidifierDesiccantSystem_Impl>()->setExhaustFanMaximumFlowRate(exhaustFanMaximumFlowRate);
}

void DehumidifierDesiccantSystem::resetExhaustFanMaximumFlowRate() {
  getImpl<detail::DehumidifierDesiccantSystem_Impl>()->resetExhaustFanMaximumFlowRate();
}

boost::optional<double> DehumidifierDesiccantSystem::exhaustFanMaximumPower() const {
  return getImpl<detail::DehumidifierDesiccantSystem_Impl>()->exhaustFanMaximumPower();
}

bool DehumidifierDesiccantSystem::setExhaustFanMaximumPower(double exhaustFanMaximumPower) {
  return getImpl<detail::DehumidifierDesiccantSystem_Impl>()->setExhaustFanMaximumPower(exhaustFanMaximumPower);
}

void DehumidifierDesiccantSystem::resetExhaustFanMaximumPower() {
  getImpl<detail::DehumidifierDesiccantSystem_Impl>()->resetExhaustFanMaximumPower();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

namespace {

bool getBooleanFieldValue(const ModelObject_Impl& impl, int fieldIndex) {
  const auto value = impl.getString(fieldIndex, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "yes");
}

bool setBooleanFieldValue(ModelObject_Impl& impl, int fieldIndex, bool value) {
  return impl.setString(fieldIndex, value ? "Yes" : "No");
}

}  // namespace

std::string DehumidifierDesiccantSystem_Impl::desiccantHeatExchangerObjectType() const {
  const auto value = getString(openstudio::Dehumidifier_Desiccant_SystemFields::DesiccantHeatExchangerObjectType, true);
  OS_ASSERT(value);
  return *value;
}

bool DehumidifierDesiccantSystem_Impl::setDesiccantHeatExchangerObjectType(const std::string& desiccantHeatExchangerObjectType) {
  return setString(openstudio::Dehumidifier_Desiccant_SystemFields::DesiccantHeatExchangerObjectType, desiccantHeatExchangerObjectType);
}

std::string DehumidifierDesiccantSystem_Impl::regenerationAirFanObjectType() const {
  const auto value = getString(openstudio::Dehumidifier_Desiccant_SystemFields::RegenerationAirFanObjectType, true);
  OS_ASSERT(value);
  return *value;
}

bool DehumidifierDesiccantSystem_Impl::setRegenerationAirFanObjectType(const std::string& regenerationAirFanObjectType) {
  return setString(openstudio::Dehumidifier_Desiccant_SystemFields::RegenerationAirFanObjectType, regenerationAirFanObjectType);
}

std::string DehumidifierDesiccantSystem_Impl::regenerationAirFanPlacement() const {
  const auto value = getString(openstudio::Dehumidifier_Desiccant_SystemFields::RegenerationAirFanPlacement, true);
  OS_ASSERT(value);
  return *value;
}

bool DehumidifierDesiccantSystem_Impl::isRegenerationAirFanPlacementDefaulted() const {
  return isEmpty(openstudio::Dehumidifier_Desiccant_SystemFields::RegenerationAirFanPlacement);
}

bool DehumidifierDesiccantSystem_Impl::setRegenerationAirFanPlacement(const std::string& regenerationAirFanPlacement) {
  return setString(openstudio::Dehumidifier_Desiccant_SystemFields::RegenerationAirFanPlacement, regenerationAirFanPlacement);
}

void DehumidifierDesiccantSystem_Impl::resetRegenerationAirFanPlacement() {
  OS_ASSERT(setString(openstudio::Dehumidifier_Desiccant_SystemFields::RegenerationAirFanPlacement, ""));
}

boost::optional<std::string> DehumidifierDesiccantSystem_Impl::regenerationAirHeaterObjectType() const {
  return getString(openstudio::Dehumidifier_Desiccant_SystemFields::RegenerationAirHeaterObjectType, true);
}

bool DehumidifierDesiccantSystem_Impl::setRegenerationAirHeaterObjectType(const std::string& regenerationAirHeaterObjectType) {
  return setString(openstudio::Dehumidifier_Desiccant_SystemFields::RegenerationAirHeaterObjectType, regenerationAirHeaterObjectType);
}

void DehumidifierDesiccantSystem_Impl::resetRegenerationAirHeaterObjectType() {
  OS_ASSERT(setString(openstudio::Dehumidifier_Desiccant_SystemFields::RegenerationAirHeaterObjectType, ""));
}

double DehumidifierDesiccantSystem_Impl::regenerationInletAirSetpointTemperature() const {
  const auto value = getDouble(openstudio::Dehumidifier_Desiccant_SystemFields::RegenerationInletAirSetpointTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool DehumidifierDesiccantSystem_Impl::isRegenerationInletAirSetpointTemperatureDefaulted() const {
  return isEmpty(openstudio::Dehumidifier_Desiccant_SystemFields::RegenerationInletAirSetpointTemperature);
}

bool DehumidifierDesiccantSystem_Impl::setRegenerationInletAirSetpointTemperature(double regenerationInletAirSetpointTemperature) {
  return setDouble(openstudio::Dehumidifier_Desiccant_SystemFields::RegenerationInletAirSetpointTemperature, regenerationInletAirSetpointTemperature);
}

void DehumidifierDesiccantSystem_Impl::resetRegenerationInletAirSetpointTemperature() {
  OS_ASSERT(setString(openstudio::Dehumidifier_Desiccant_SystemFields::RegenerationInletAirSetpointTemperature, ""));
}

boost::optional<std::string> DehumidifierDesiccantSystem_Impl::companionCoolingCoilObjectType() const {
  return getString(openstudio::Dehumidifier_Desiccant_SystemFields::CompanionCoolingCoilObjectType, true);
}

bool DehumidifierDesiccantSystem_Impl::setCompanionCoolingCoilObjectType(const std::string& companionCoolingCoilObjectType) {
  return setString(openstudio::Dehumidifier_Desiccant_SystemFields::CompanionCoolingCoilObjectType, companionCoolingCoilObjectType);
}

void DehumidifierDesiccantSystem_Impl::resetCompanionCoolingCoilObjectType() {
  OS_ASSERT(setString(openstudio::Dehumidifier_Desiccant_SystemFields::CompanionCoolingCoilObjectType, ""));
}

bool DehumidifierDesiccantSystem_Impl::companionCoolingCoilUpstreamofDehumidifierProcessInlet() const {
  return getBooleanFieldValue(*this, openstudio::Dehumidifier_Desiccant_SystemFields::CompanionCoolingCoilUpstreamofDehumidifierProcessInlet);
}

bool DehumidifierDesiccantSystem_Impl::isCompanionCoolingCoilUpstreamofDehumidifierProcessInletDefaulted() const {
  return isEmpty(openstudio::Dehumidifier_Desiccant_SystemFields::CompanionCoolingCoilUpstreamofDehumidifierProcessInlet);
}

bool DehumidifierDesiccantSystem_Impl::setCompanionCoolingCoilUpstreamofDehumidifierProcessInlet(
  bool companionCoolingCoilUpstreamofDehumidifierProcessInlet) {
  const bool result = setBooleanFieldValue(*this, openstudio::Dehumidifier_Desiccant_SystemFields::CompanionCoolingCoilUpstreamofDehumidifierProcessInlet,
                                           companionCoolingCoilUpstreamofDehumidifierProcessInlet);
  OS_ASSERT(result);
  return result;
}

void DehumidifierDesiccantSystem_Impl::resetCompanionCoolingCoilUpstreamofDehumidifierProcessInlet() {
  OS_ASSERT(setString(openstudio::Dehumidifier_Desiccant_SystemFields::CompanionCoolingCoilUpstreamofDehumidifierProcessInlet, ""));
}

bool DehumidifierDesiccantSystem_Impl::companionCoilRegenerationAirHeating() const {
  return getBooleanFieldValue(*this, openstudio::Dehumidifier_Desiccant_SystemFields::CompanionCoilRegenerationAirHeating);
}

bool DehumidifierDesiccantSystem_Impl::isCompanionCoilRegenerationAirHeatingDefaulted() const {
  return isEmpty(openstudio::Dehumidifier_Desiccant_SystemFields::CompanionCoilRegenerationAirHeating);
}

bool DehumidifierDesiccantSystem_Impl::setCompanionCoilRegenerationAirHeating(bool companionCoilRegenerationAirHeating) {
  const bool result =
    setBooleanFieldValue(*this, openstudio::Dehumidifier_Desiccant_SystemFields::CompanionCoilRegenerationAirHeating, companionCoilRegenerationAirHeating);
  OS_ASSERT(result);
  return result;
}

void DehumidifierDesiccantSystem_Impl::resetCompanionCoilRegenerationAirHeating() {
  OS_ASSERT(setString(openstudio::Dehumidifier_Desiccant_SystemFields::CompanionCoilRegenerationAirHeating, ""));
}

boost::optional<double> DehumidifierDesiccantSystem_Impl::exhaustFanMaximumFlowRate() const {
  return getDouble(openstudio::Dehumidifier_Desiccant_SystemFields::ExhaustFanMaximumFlowRate, true);
}

bool DehumidifierDesiccantSystem_Impl::setExhaustFanMaximumFlowRate(double exhaustFanMaximumFlowRate) {
  return setDouble(openstudio::Dehumidifier_Desiccant_SystemFields::ExhaustFanMaximumFlowRate, exhaustFanMaximumFlowRate);
}

void DehumidifierDesiccantSystem_Impl::resetExhaustFanMaximumFlowRate() {
  OS_ASSERT(setString(openstudio::Dehumidifier_Desiccant_SystemFields::ExhaustFanMaximumFlowRate, ""));
}

boost::optional<double> DehumidifierDesiccantSystem_Impl::exhaustFanMaximumPower() const {
  return getDouble(openstudio::Dehumidifier_Desiccant_SystemFields::ExhaustFanMaximumPower, true);
}

bool DehumidifierDesiccantSystem_Impl::setExhaustFanMaximumPower(double exhaustFanMaximumPower) {
  return setDouble(openstudio::Dehumidifier_Desiccant_SystemFields::ExhaustFanMaximumPower, exhaustFanMaximumPower);
}

void DehumidifierDesiccantSystem_Impl::resetExhaustFanMaximumPower() {
  OS_ASSERT(setString(openstudio::Dehumidifier_Desiccant_SystemFields::ExhaustFanMaximumPower, ""));
}

std::vector<std::string> DehumidifierDesiccantSystem_Impl::desiccantHeatExchangerObjectTypeValues() const {
  return openstudio::epmodel::DehumidifierDesiccantSystem::desiccantHeatExchangerObjectTypeValues();
}

std::vector<std::string> DehumidifierDesiccantSystem_Impl::regenerationAirFanObjectTypeValues() const {
  return openstudio::epmodel::DehumidifierDesiccantSystem::regenerationAirFanObjectTypeValues();
}

std::vector<std::string> DehumidifierDesiccantSystem_Impl::regenerationAirFanPlacementValues() const {
  return openstudio::epmodel::DehumidifierDesiccantSystem::regenerationAirFanPlacementValues();
}

std::vector<std::string> DehumidifierDesiccantSystem_Impl::regenerationAirHeaterObjectTypeValues() const {
  return openstudio::epmodel::DehumidifierDesiccantSystem::regenerationAirHeaterObjectTypeValues();
}

std::vector<std::string> DehumidifierDesiccantSystem_Impl::companionCoolingCoilObjectTypeValues() const {
  return openstudio::epmodel::DehumidifierDesiccantSystem::companionCoolingCoilObjectTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
