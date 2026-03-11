/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/HeatExchangerAirToAirFlatPlate.hpp"
#include "ModelObject/HeatExchangerAirToAirFlatPlate_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/HeatExchanger_AirToAir_FlatPlate_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

HeatExchangerAirToAirFlatPlate::HeatExchangerAirToAirFlatPlate(const Model& model)
  : ModelObject(HeatExchangerAirToAirFlatPlate::iddObjectType(), model) {}

HeatExchangerAirToAirFlatPlate::HeatExchangerAirToAirFlatPlate(std::shared_ptr<detail::HeatExchangerAirToAirFlatPlate_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType HeatExchangerAirToAirFlatPlate::iddObjectType() {
  return IddObjectType::HeatExchanger_AirToAir_FlatPlate;
}

std::vector<std::string> HeatExchangerAirToAirFlatPlate::flowArrangementTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HeatExchanger_AirToAir_FlatPlateFields::FlowArrangementType);
}

boost::optional<std::string> HeatExchangerAirToAirFlatPlate::flowArrangementType() const {
  return getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->flowArrangementType();
}

bool HeatExchangerAirToAirFlatPlate::economizerLockout() const {
  return getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->economizerLockout();
}

bool HeatExchangerAirToAirFlatPlate::isEconomizerLockoutDefaulted() const {
  return getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->isEconomizerLockoutDefaulted();
}

boost::optional<double> HeatExchangerAirToAirFlatPlate::ratioofSupplytoSecondaryhAValues() const {
  return getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->ratioofSupplytoSecondaryhAValues();
}

boost::optional<double> HeatExchangerAirToAirFlatPlate::nominalSupplyAirFlowRate() const {
  return getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->nominalSupplyAirFlowRate();
}

bool HeatExchangerAirToAirFlatPlate::isNominalSupplyAirFlowRateAutosized() const {
  return getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->isNominalSupplyAirFlowRateAutosized();
}

double HeatExchangerAirToAirFlatPlate::nominalSupplyAirInletTemperature() const {
  return getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->nominalSupplyAirInletTemperature();
}

double HeatExchangerAirToAirFlatPlate::nominalSupplyAirOutletTemperature() const {
  return getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->nominalSupplyAirOutletTemperature();
}

boost::optional<double> HeatExchangerAirToAirFlatPlate::nominalSecondaryAirFlowRate() const {
  return getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->nominalSecondaryAirFlowRate();
}

bool HeatExchangerAirToAirFlatPlate::isNominalSecondaryAirFlowRateAutosized() const {
  return getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->isNominalSecondaryAirFlowRateAutosized();
}

double HeatExchangerAirToAirFlatPlate::nominalSecondaryAirInletTemperature() const {
  return getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->nominalSecondaryAirInletTemperature();
}

boost::optional<double> HeatExchangerAirToAirFlatPlate::nominalElectricPower() const {
  return getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->nominalElectricPower();
}

bool HeatExchangerAirToAirFlatPlate::setFlowArrangementType(const std::string& flowArrangementType) {
  return getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->setFlowArrangementType(flowArrangementType);
}

void HeatExchangerAirToAirFlatPlate::resetFlowArrangementType() {
  getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->resetFlowArrangementType();
}

bool HeatExchangerAirToAirFlatPlate::setEconomizerLockout(bool economizerLockout) {
  return getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->setEconomizerLockout(economizerLockout);
}

void HeatExchangerAirToAirFlatPlate::resetEconomizerLockout() {
  getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->resetEconomizerLockout();
}

bool HeatExchangerAirToAirFlatPlate::setRatioofSupplytoSecondaryhAValues(double ratioofSupplytoSecondaryhAValues) {
  return getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->setRatioofSupplytoSecondaryhAValues(ratioofSupplytoSecondaryhAValues);
}

void HeatExchangerAirToAirFlatPlate::resetRatioofSupplytoSecondaryhAValues() {
  getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->resetRatioofSupplytoSecondaryhAValues();
}

bool HeatExchangerAirToAirFlatPlate::setNominalSupplyAirFlowRate(double nominalSupplyAirFlowRate) {
  return getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->setNominalSupplyAirFlowRate(nominalSupplyAirFlowRate);
}

void HeatExchangerAirToAirFlatPlate::resetNominalSupplyAirFlowRate() {
  getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->resetNominalSupplyAirFlowRate();
}

void HeatExchangerAirToAirFlatPlate::autosizeNominalSupplyAirFlowRate() {
  getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->autosizeNominalSupplyAirFlowRate();
}

bool HeatExchangerAirToAirFlatPlate::setNominalSupplyAirInletTemperature(double nominalSupplyAirInletTemperature) {
  return getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->setNominalSupplyAirInletTemperature(nominalSupplyAirInletTemperature);
}

bool HeatExchangerAirToAirFlatPlate::setNominalSupplyAirOutletTemperature(double nominalSupplyAirOutletTemperature) {
  return getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->setNominalSupplyAirOutletTemperature(nominalSupplyAirOutletTemperature);
}

bool HeatExchangerAirToAirFlatPlate::setNominalSecondaryAirFlowRate(double nominalSecondaryAirFlowRate) {
  return getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->setNominalSecondaryAirFlowRate(nominalSecondaryAirFlowRate);
}

void HeatExchangerAirToAirFlatPlate::autosizeNominalSecondaryAirFlowRate() {
  getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->autosizeNominalSecondaryAirFlowRate();
}

bool HeatExchangerAirToAirFlatPlate::setNominalSecondaryAirInletTemperature(double nominalSecondaryAirInletTemperature) {
  return getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->setNominalSecondaryAirInletTemperature(nominalSecondaryAirInletTemperature);
}

bool HeatExchangerAirToAirFlatPlate::setNominalElectricPower(double nominalElectricPower) {
  return getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->setNominalElectricPower(nominalElectricPower);
}

void HeatExchangerAirToAirFlatPlate::resetNominalElectricPower() {
  getImpl<detail::HeatExchangerAirToAirFlatPlate_Impl>()->resetNominalElectricPower();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<std::string> HeatExchangerAirToAirFlatPlate_Impl::flowArrangementType() const {
  return getString(openstudio::HeatExchanger_AirToAir_FlatPlateFields::FlowArrangementType, true);
}

bool HeatExchangerAirToAirFlatPlate_Impl::economizerLockout() const {
  const auto value = getString(openstudio::HeatExchanger_AirToAir_FlatPlateFields::EconomizerLockout, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool HeatExchangerAirToAirFlatPlate_Impl::isEconomizerLockoutDefaulted() const {
  return isEmpty(openstudio::HeatExchanger_AirToAir_FlatPlateFields::EconomizerLockout);
}

boost::optional<double> HeatExchangerAirToAirFlatPlate_Impl::ratioofSupplytoSecondaryhAValues() const {
  return getDouble(openstudio::HeatExchanger_AirToAir_FlatPlateFields::RatioofSupplytoSecondaryhAValues, true);
}

boost::optional<double> HeatExchangerAirToAirFlatPlate_Impl::nominalSupplyAirFlowRate() const {
  return getDouble(openstudio::HeatExchanger_AirToAir_FlatPlateFields::NominalSupplyAirFlowRate, true);
}

bool HeatExchangerAirToAirFlatPlate_Impl::isNominalSupplyAirFlowRateAutosized() const {
  bool result = false;
  const auto value = getString(openstudio::HeatExchanger_AirToAir_FlatPlateFields::NominalSupplyAirFlowRate, true);
  if (value) {
    result = openstudio::istringEqual(*value, "autosize");
  }
  return result;
}

double HeatExchangerAirToAirFlatPlate_Impl::nominalSupplyAirInletTemperature() const {
  const auto value = getDouble(openstudio::HeatExchanger_AirToAir_FlatPlateFields::NominalSupplyAirInletTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double HeatExchangerAirToAirFlatPlate_Impl::nominalSupplyAirOutletTemperature() const {
  const auto value = getDouble(openstudio::HeatExchanger_AirToAir_FlatPlateFields::NominalSupplyAirOutletTemperature, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> HeatExchangerAirToAirFlatPlate_Impl::nominalSecondaryAirFlowRate() const {
  return getDouble(openstudio::HeatExchanger_AirToAir_FlatPlateFields::NominalSecondaryAirFlowRate, true);
}

bool HeatExchangerAirToAirFlatPlate_Impl::isNominalSecondaryAirFlowRateAutosized() const {
  bool result = false;
  const auto value = getString(openstudio::HeatExchanger_AirToAir_FlatPlateFields::NominalSecondaryAirFlowRate, true);
  if (value) {
    result = openstudio::istringEqual(*value, "autosize");
  }
  return result;
}

double HeatExchangerAirToAirFlatPlate_Impl::nominalSecondaryAirInletTemperature() const {
  const auto value = getDouble(openstudio::HeatExchanger_AirToAir_FlatPlateFields::NominalSecondaryAirInletTemperature, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> HeatExchangerAirToAirFlatPlate_Impl::nominalElectricPower() const {
  return getDouble(openstudio::HeatExchanger_AirToAir_FlatPlateFields::NominalElectricPower, true);
}

bool HeatExchangerAirToAirFlatPlate_Impl::setFlowArrangementType(const std::string& flowArrangementType) {
  return setString(openstudio::HeatExchanger_AirToAir_FlatPlateFields::FlowArrangementType, flowArrangementType);
}

void HeatExchangerAirToAirFlatPlate_Impl::resetFlowArrangementType() {
  OS_ASSERT(setString(openstudio::HeatExchanger_AirToAir_FlatPlateFields::FlowArrangementType, ""));
}

bool HeatExchangerAirToAirFlatPlate_Impl::setEconomizerLockout(bool economizerLockout) {
  const bool result = setString(openstudio::HeatExchanger_AirToAir_FlatPlateFields::EconomizerLockout, economizerLockout ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

void HeatExchangerAirToAirFlatPlate_Impl::resetEconomizerLockout() {
  OS_ASSERT(setString(openstudio::HeatExchanger_AirToAir_FlatPlateFields::EconomizerLockout, ""));
}

bool HeatExchangerAirToAirFlatPlate_Impl::setRatioofSupplytoSecondaryhAValues(double ratioofSupplytoSecondaryhAValues) {
  return setDouble(openstudio::HeatExchanger_AirToAir_FlatPlateFields::RatioofSupplytoSecondaryhAValues, ratioofSupplytoSecondaryhAValues);
}

void HeatExchangerAirToAirFlatPlate_Impl::resetRatioofSupplytoSecondaryhAValues() {
  OS_ASSERT(setString(openstudio::HeatExchanger_AirToAir_FlatPlateFields::RatioofSupplytoSecondaryhAValues, ""));
}

bool HeatExchangerAirToAirFlatPlate_Impl::setNominalSupplyAirFlowRate(double nominalSupplyAirFlowRate) {
  return setDouble(openstudio::HeatExchanger_AirToAir_FlatPlateFields::NominalSupplyAirFlowRate, nominalSupplyAirFlowRate);
}

void HeatExchangerAirToAirFlatPlate_Impl::resetNominalSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::HeatExchanger_AirToAir_FlatPlateFields::NominalSupplyAirFlowRate, ""));
}

void HeatExchangerAirToAirFlatPlate_Impl::autosizeNominalSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::HeatExchanger_AirToAir_FlatPlateFields::NominalSupplyAirFlowRate, "autosize"));
}

bool HeatExchangerAirToAirFlatPlate_Impl::setNominalSupplyAirInletTemperature(double nominalSupplyAirInletTemperature) {
  const bool result = setDouble(openstudio::HeatExchanger_AirToAir_FlatPlateFields::NominalSupplyAirInletTemperature,
                                nominalSupplyAirInletTemperature);
  OS_ASSERT(result);
  return result;
}

bool HeatExchangerAirToAirFlatPlate_Impl::setNominalSupplyAirOutletTemperature(double nominalSupplyAirOutletTemperature) {
  const bool result = setDouble(openstudio::HeatExchanger_AirToAir_FlatPlateFields::NominalSupplyAirOutletTemperature,
                                nominalSupplyAirOutletTemperature);
  OS_ASSERT(result);
  return result;
}

bool HeatExchangerAirToAirFlatPlate_Impl::setNominalSecondaryAirFlowRate(double nominalSecondaryAirFlowRate) {
  return setDouble(openstudio::HeatExchanger_AirToAir_FlatPlateFields::NominalSecondaryAirFlowRate, nominalSecondaryAirFlowRate);
}

void HeatExchangerAirToAirFlatPlate_Impl::autosizeNominalSecondaryAirFlowRate() {
  OS_ASSERT(setString(openstudio::HeatExchanger_AirToAir_FlatPlateFields::NominalSecondaryAirFlowRate, "autosize"));
}

bool HeatExchangerAirToAirFlatPlate_Impl::setNominalSecondaryAirInletTemperature(double nominalSecondaryAirInletTemperature) {
  const bool result = setDouble(openstudio::HeatExchanger_AirToAir_FlatPlateFields::NominalSecondaryAirInletTemperature,
                                nominalSecondaryAirInletTemperature);
  OS_ASSERT(result);
  return result;
}

bool HeatExchangerAirToAirFlatPlate_Impl::setNominalElectricPower(double nominalElectricPower) {
  const bool result = setDouble(openstudio::HeatExchanger_AirToAir_FlatPlateFields::NominalElectricPower, nominalElectricPower);
  OS_ASSERT(result);
  return result;
}

void HeatExchangerAirToAirFlatPlate_Impl::resetNominalElectricPower() {
  OS_ASSERT(setString(openstudio::HeatExchanger_AirToAir_FlatPlateFields::NominalElectricPower, ""));
}

std::vector<std::string> HeatExchangerAirToAirFlatPlate_Impl::flowArrangementTypeValues() const {
  return openstudio::epmodel::HeatExchangerAirToAirFlatPlate::flowArrangementTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
