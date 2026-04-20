/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "RoomAirSettingsUnderFloorAirDistributionExterior.hpp"
#include "RoomAirSettingsUnderFloorAirDistributionExterior_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/RoomAirSettings_UnderFloorAirDistributionExterior_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

RoomAirSettingsUnderFloorAirDistributionExterior::RoomAirSettingsUnderFloorAirDistributionExterior(const Model& model)
  : ModelObject(RoomAirSettingsUnderFloorAirDistributionExterior::iddObjectType(), model) {}

RoomAirSettingsUnderFloorAirDistributionExterior::RoomAirSettingsUnderFloorAirDistributionExterior(
  std::shared_ptr<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType RoomAirSettingsUnderFloorAirDistributionExterior::iddObjectType() {
  return IddObjectType::RoomAirSettings_UnderFloorAirDistributionExterior;
}

std::vector<std::string> RoomAirSettingsUnderFloorAirDistributionExterior::floorDiffuserTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::FloorDiffuserType);
}

boost::optional<double> RoomAirSettingsUnderFloorAirDistributionExterior::numberofDiffusersperZone() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->numberofDiffusersperZone();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::isNumberofDiffusersperZoneDefaulted() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->isNumberofDiffusersperZoneDefaulted();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::isNumberofDiffusersperZoneAutocalculated() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->isNumberofDiffusersperZoneAutocalculated();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::setNumberofDiffusersperZone(double numberofDiffusersperZone) {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->setNumberofDiffusersperZone(numberofDiffusersperZone);
}

void RoomAirSettingsUnderFloorAirDistributionExterior::resetNumberofDiffusersperZone() {
  getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->resetNumberofDiffusersperZone();
}

void RoomAirSettingsUnderFloorAirDistributionExterior::autocalculateNumberofDiffusersperZone() {
  getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->autocalculateNumberofDiffusersperZone();
}

boost::optional<double> RoomAirSettingsUnderFloorAirDistributionExterior::powerperPlume() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->powerperPlume();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::isPowerperPlumeDefaulted() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->isPowerperPlumeDefaulted();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::isPowerperPlumeAutocalculated() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->isPowerperPlumeAutocalculated();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::setPowerperPlume(double powerperPlume) {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->setPowerperPlume(powerperPlume);
}

void RoomAirSettingsUnderFloorAirDistributionExterior::resetPowerperPlume() {
  getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->resetPowerperPlume();
}

void RoomAirSettingsUnderFloorAirDistributionExterior::autocalculatePowerperPlume() {
  getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->autocalculatePowerperPlume();
}

boost::optional<double> RoomAirSettingsUnderFloorAirDistributionExterior::designEffectiveAreaofDiffuser() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->designEffectiveAreaofDiffuser();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::isDesignEffectiveAreaofDiffuserDefaulted() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->isDesignEffectiveAreaofDiffuserDefaulted();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::isDesignEffectiveAreaofDiffuserAutocalculated() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->isDesignEffectiveAreaofDiffuserAutocalculated();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::setDesignEffectiveAreaofDiffuser(double designEffectiveAreaofDiffuser) {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->setDesignEffectiveAreaofDiffuser(designEffectiveAreaofDiffuser);
}

void RoomAirSettingsUnderFloorAirDistributionExterior::resetDesignEffectiveAreaofDiffuser() {
  getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->resetDesignEffectiveAreaofDiffuser();
}

void RoomAirSettingsUnderFloorAirDistributionExterior::autocalculateDesignEffectiveAreaofDiffuser() {
  getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->autocalculateDesignEffectiveAreaofDiffuser();
}

boost::optional<double> RoomAirSettingsUnderFloorAirDistributionExterior::diffuserSlotAnglefromVertical() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->diffuserSlotAnglefromVertical();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::isDiffuserSlotAnglefromVerticalDefaulted() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->isDiffuserSlotAnglefromVerticalDefaulted();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::isDiffuserSlotAnglefromVerticalAutocalculated() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->isDiffuserSlotAnglefromVerticalAutocalculated();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::setDiffuserSlotAnglefromVertical(double diffuserSlotAnglefromVertical) {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->setDiffuserSlotAnglefromVertical(diffuserSlotAnglefromVertical);
}

void RoomAirSettingsUnderFloorAirDistributionExterior::resetDiffuserSlotAnglefromVertical() {
  getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->resetDiffuserSlotAnglefromVertical();
}

void RoomAirSettingsUnderFloorAirDistributionExterior::autocalculateDiffuserSlotAnglefromVertical() {
  getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->autocalculateDiffuserSlotAnglefromVertical();
}

double RoomAirSettingsUnderFloorAirDistributionExterior::thermostatHeight() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->thermostatHeight();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::isThermostatHeightDefaulted() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->isThermostatHeightDefaulted();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::setThermostatHeight(double thermostatHeight) {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->setThermostatHeight(thermostatHeight);
}

void RoomAirSettingsUnderFloorAirDistributionExterior::resetThermostatHeight() {
  getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->resetThermostatHeight();
}

double RoomAirSettingsUnderFloorAirDistributionExterior::comfortHeight() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->comfortHeight();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::isComfortHeightDefaulted() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->isComfortHeightDefaulted();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::setComfortHeight(double comfortHeight) {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->setComfortHeight(comfortHeight);
}

void RoomAirSettingsUnderFloorAirDistributionExterior::resetComfortHeight() {
  getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->resetComfortHeight();
}

double RoomAirSettingsUnderFloorAirDistributionExterior::temperatureDifferenceThresholdforReporting() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->temperatureDifferenceThresholdforReporting();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::isTemperatureDifferenceThresholdforReportingDefaulted() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->isTemperatureDifferenceThresholdforReportingDefaulted();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::setTemperatureDifferenceThresholdforReporting(double temperatureDifferenceThresholdforReporting) {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->setTemperatureDifferenceThresholdforReporting(
    temperatureDifferenceThresholdforReporting);
}

void RoomAirSettingsUnderFloorAirDistributionExterior::resetTemperatureDifferenceThresholdforReporting() {
  getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->resetTemperatureDifferenceThresholdforReporting();
}

std::string RoomAirSettingsUnderFloorAirDistributionExterior::floorDiffuserType() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->floorDiffuserType();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::isFloorDiffuserTypeDefaulted() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->isFloorDiffuserTypeDefaulted();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::setFloorDiffuserType(const std::string& floorDiffuserType) {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->setFloorDiffuserType(floorDiffuserType);
}

void RoomAirSettingsUnderFloorAirDistributionExterior::resetFloorDiffuserType() {
  getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->resetFloorDiffuserType();
}

boost::optional<double> RoomAirSettingsUnderFloorAirDistributionExterior::transitionHeight() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->transitionHeight();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::isTransitionHeightDefaulted() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->isTransitionHeightDefaulted();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::isTransitionHeightAutocalculated() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->isTransitionHeightAutocalculated();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::setTransitionHeight(double transitionHeight) {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->setTransitionHeight(transitionHeight);
}

void RoomAirSettingsUnderFloorAirDistributionExterior::resetTransitionHeight() {
  getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->resetTransitionHeight();
}

void RoomAirSettingsUnderFloorAirDistributionExterior::autocalculateTransitionHeight() {
  getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()->autocalculateTransitionHeight();
}

boost::optional<double>
RoomAirSettingsUnderFloorAirDistributionExterior::coefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->coefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::isCoefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Defaulted()
  const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->isCoefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Defaulted();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::isCoefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Autocalculated()
  const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->isCoefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Autocalculated();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::setCoefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2(
  double coefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2) {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->setCoefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2(
      coefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2);
}

void RoomAirSettingsUnderFloorAirDistributionExterior::resetCoefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() {
  getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->resetCoefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2();
}

void RoomAirSettingsUnderFloorAirDistributionExterior::autocalculateCoefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() {
  getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->autocalculateCoefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2();
}

boost::optional<double>
RoomAirSettingsUnderFloorAirDistributionExterior::coefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->coefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::isCoefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Defaulted()
  const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->isCoefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Defaulted();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::isCoefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Autocalculated()
  const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->isCoefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Autocalculated();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::setCoefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2(
  double coefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2) {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->setCoefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2(
      coefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2);
}

void RoomAirSettingsUnderFloorAirDistributionExterior::resetCoefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() {
  getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->resetCoefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2();
}

void RoomAirSettingsUnderFloorAirDistributionExterior::autocalculateCoefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() {
  getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->autocalculateCoefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2();
}

boost::optional<double>
RoomAirSettingsUnderFloorAirDistributionExterior::coefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->coefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::isCoefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Defaulted()
  const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->isCoefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Defaulted();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::isCoefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Autocalculated()
  const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->isCoefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Autocalculated();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::setCoefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2(
  double coefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2) {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->setCoefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2(
      coefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2);
}

void RoomAirSettingsUnderFloorAirDistributionExterior::resetCoefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() {
  getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->resetCoefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2();
}

void RoomAirSettingsUnderFloorAirDistributionExterior::autocalculateCoefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() {
  getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->autocalculateCoefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2();
}

boost::optional<double>
RoomAirSettingsUnderFloorAirDistributionExterior::coefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->coefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::isCoefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Defaulted()
  const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->isCoefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Defaulted();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::isCoefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Autocalculated()
  const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->isCoefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Autocalculated();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::setCoefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2(
  double coefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2) {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->setCoefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2(
      coefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2);
}

void RoomAirSettingsUnderFloorAirDistributionExterior::resetCoefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() {
  getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->resetCoefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2();
}

void RoomAirSettingsUnderFloorAirDistributionExterior::autocalculateCoefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() {
  getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->autocalculateCoefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2();
}

boost::optional<double>
RoomAirSettingsUnderFloorAirDistributionExterior::coefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->coefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::isCoefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Defaulted()
  const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->isCoefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Defaulted();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::isCoefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Autocalculated()
  const {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->isCoefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Autocalculated();
}

bool RoomAirSettingsUnderFloorAirDistributionExterior::setCoefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2(
  double coefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2) {
  return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->setCoefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2(
      coefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2);
}

void RoomAirSettingsUnderFloorAirDistributionExterior::resetCoefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() {
  getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->resetCoefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2();
}

void RoomAirSettingsUnderFloorAirDistributionExterior::autocalculateCoefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() {
  getImpl<detail::RoomAirSettingsUnderFloorAirDistributionExterior_Impl>()
    ->autocalculateCoefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> RoomAirSettingsUnderFloorAirDistributionExterior_Impl::numberofDiffusersperZone() const {
  return getDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::NumberofDiffusersperZone, true);
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::isNumberofDiffusersperZoneDefaulted() const {
  return isEmpty(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::NumberofDiffusersperZone);
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::isNumberofDiffusersperZoneAutocalculated() const {
  if (const auto value = getString(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::NumberofDiffusersperZone, true)) {
    return openstudio::istringEqual(*value, "autocalculate");
  }
  return false;
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::setNumberofDiffusersperZone(double numberofDiffusersperZone) {
  return setDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::NumberofDiffusersperZone, numberofDiffusersperZone);
}

void RoomAirSettingsUnderFloorAirDistributionExterior_Impl::resetNumberofDiffusersperZone() {
  OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::NumberofDiffusersperZone, ""));
}

void RoomAirSettingsUnderFloorAirDistributionExterior_Impl::autocalculateNumberofDiffusersperZone() {
  OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::NumberofDiffusersperZone, "autocalculate"));
}

boost::optional<double> RoomAirSettingsUnderFloorAirDistributionExterior_Impl::powerperPlume() const {
  return getDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::PowerperPlume, true);
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::isPowerperPlumeDefaulted() const {
  return isEmpty(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::PowerperPlume);
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::isPowerperPlumeAutocalculated() const {
  if (const auto value = getString(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::PowerperPlume, true)) {
    return openstudio::istringEqual(*value, "autocalculate");
  }
  return false;
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::setPowerperPlume(double powerperPlume) {
  return setDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::PowerperPlume, powerperPlume);
}

void RoomAirSettingsUnderFloorAirDistributionExterior_Impl::resetPowerperPlume() {
  OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::PowerperPlume, ""));
}

void RoomAirSettingsUnderFloorAirDistributionExterior_Impl::autocalculatePowerperPlume() {
  OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::PowerperPlume, "autocalculate"));
}

boost::optional<double> RoomAirSettingsUnderFloorAirDistributionExterior_Impl::designEffectiveAreaofDiffuser() const {
  return getDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::DesignEffectiveAreaofDiffuser, true);
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::isDesignEffectiveAreaofDiffuserDefaulted() const {
  return isEmpty(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::DesignEffectiveAreaofDiffuser);
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::isDesignEffectiveAreaofDiffuserAutocalculated() const {
  if (const auto value = getString(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::DesignEffectiveAreaofDiffuser, true)) {
    return openstudio::istringEqual(*value, "autocalculate");
  }
  return false;
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::setDesignEffectiveAreaofDiffuser(double designEffectiveAreaofDiffuser) {
  return setDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::DesignEffectiveAreaofDiffuser,
                   designEffectiveAreaofDiffuser);
}

void RoomAirSettingsUnderFloorAirDistributionExterior_Impl::resetDesignEffectiveAreaofDiffuser() {
  OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::DesignEffectiveAreaofDiffuser, ""));
}

void RoomAirSettingsUnderFloorAirDistributionExterior_Impl::autocalculateDesignEffectiveAreaofDiffuser() {
  OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::DesignEffectiveAreaofDiffuser, "autocalculate"));
}

boost::optional<double> RoomAirSettingsUnderFloorAirDistributionExterior_Impl::diffuserSlotAnglefromVertical() const {
  return getDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::DiffuserSlotAnglefromVertical, true);
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::isDiffuserSlotAnglefromVerticalDefaulted() const {
  return isEmpty(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::DiffuserSlotAnglefromVertical);
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::isDiffuserSlotAnglefromVerticalAutocalculated() const {
  if (const auto value = getString(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::DiffuserSlotAnglefromVertical, true)) {
    return openstudio::istringEqual(*value, "autocalculate");
  }
  return false;
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::setDiffuserSlotAnglefromVertical(double diffuserSlotAnglefromVertical) {
  return setDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::DiffuserSlotAnglefromVertical, diffuserSlotAnglefromVertical);
}

void RoomAirSettingsUnderFloorAirDistributionExterior_Impl::resetDiffuserSlotAnglefromVertical() {
  OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::DiffuserSlotAnglefromVertical, ""));
}

void RoomAirSettingsUnderFloorAirDistributionExterior_Impl::autocalculateDiffuserSlotAnglefromVertical() {
  OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::DiffuserSlotAnglefromVertical, "autocalculate"));
}

double RoomAirSettingsUnderFloorAirDistributionExterior_Impl::thermostatHeight() const {
  const auto value = getDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::ThermostatHeight, true);
  OS_ASSERT(value);
  return *value;
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::isThermostatHeightDefaulted() const {
  return isEmpty(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::ThermostatHeight);
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::setThermostatHeight(double thermostatHeight) {
  return setDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::ThermostatHeight, thermostatHeight);
}

void RoomAirSettingsUnderFloorAirDistributionExterior_Impl::resetThermostatHeight() {
  OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::ThermostatHeight, ""));
}

double RoomAirSettingsUnderFloorAirDistributionExterior_Impl::comfortHeight() const {
  const auto value = getDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::ComfortHeight, true);
  OS_ASSERT(value);
  return *value;
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::isComfortHeightDefaulted() const {
  return isEmpty(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::ComfortHeight);
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::setComfortHeight(double comfortHeight) {
  return setDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::ComfortHeight, comfortHeight);
}

void RoomAirSettingsUnderFloorAirDistributionExterior_Impl::resetComfortHeight() {
  OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::ComfortHeight, ""));
}

double RoomAirSettingsUnderFloorAirDistributionExterior_Impl::temperatureDifferenceThresholdforReporting() const {
  const auto value =
    getDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::TemperatureDifferenceThresholdforReporting, true);
  OS_ASSERT(value);
  return *value;
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::isTemperatureDifferenceThresholdforReportingDefaulted() const {
  return isEmpty(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::TemperatureDifferenceThresholdforReporting);
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::setTemperatureDifferenceThresholdforReporting(double temperatureDifferenceThresholdforReporting) {
  return setDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::TemperatureDifferenceThresholdforReporting,
                   temperatureDifferenceThresholdforReporting);
}

void RoomAirSettingsUnderFloorAirDistributionExterior_Impl::resetTemperatureDifferenceThresholdforReporting() {
  OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::TemperatureDifferenceThresholdforReporting, ""));
}

std::string RoomAirSettingsUnderFloorAirDistributionExterior_Impl::floorDiffuserType() const {
  const auto value = getString(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::FloorDiffuserType, true);
  OS_ASSERT(value);
  return *value;
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::isFloorDiffuserTypeDefaulted() const {
  return isEmpty(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::FloorDiffuserType);
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::setFloorDiffuserType(const std::string& floorDiffuserType) {
  return setString(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::FloorDiffuserType, floorDiffuserType);
}

void RoomAirSettingsUnderFloorAirDistributionExterior_Impl::resetFloorDiffuserType() {
  OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::FloorDiffuserType, ""));
}

boost::optional<double> RoomAirSettingsUnderFloorAirDistributionExterior_Impl::transitionHeight() const {
  return getDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::TransitionHeight, true);
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::isTransitionHeightDefaulted() const {
  return isEmpty(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::TransitionHeight);
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::isTransitionHeightAutocalculated() const {
  if (const auto value = getString(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::TransitionHeight, true)) {
    return openstudio::istringEqual(*value, "autocalculate");
  }
  return false;
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::setTransitionHeight(double transitionHeight) {
  return setDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::TransitionHeight, transitionHeight);
}

void RoomAirSettingsUnderFloorAirDistributionExterior_Impl::resetTransitionHeight() {
  OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::TransitionHeight, ""));
}

void RoomAirSettingsUnderFloorAirDistributionExterior_Impl::autocalculateTransitionHeight() {
  OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::TransitionHeight, "autocalculate"));
}

boost::optional<double>
RoomAirSettingsUnderFloorAirDistributionExterior_Impl::coefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() const {
  return getDouble(
    openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
      CoefficientAinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2,
    true);
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::isCoefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Defaulted()
  const {
  return isEmpty(
    openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
      CoefficientAinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2);
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::isCoefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Autocalculated()
  const {
  if (const auto value = getString(
        openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
          CoefficientAinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2,
        true)) {
    return openstudio::istringEqual(*value, "autocalculate");
  }
  return false;
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::setCoefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2(
  double coefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2) {
  const bool result = setDouble(
    openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
      CoefficientAinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2,
    coefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2);
  OS_ASSERT(result);
  return result;
}

void RoomAirSettingsUnderFloorAirDistributionExterior_Impl::resetCoefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() {
  OS_ASSERT(setString(
    openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
      CoefficientAinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2,
    ""));
}

void RoomAirSettingsUnderFloorAirDistributionExterior_Impl::autocalculateCoefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() {
  OS_ASSERT(setString(
    openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
      CoefficientAinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2,
    "autocalculate"));
}

boost::optional<double>
RoomAirSettingsUnderFloorAirDistributionExterior_Impl::coefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() const {
  return getDouble(
    openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
      CoefficientBinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2,
    true);
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::isCoefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Defaulted()
  const {
  return isEmpty(
    openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
      CoefficientBinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2);
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::isCoefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Autocalculated()
  const {
  if (const auto value = getString(
        openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
          CoefficientBinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2,
        true)) {
    return openstudio::istringEqual(*value, "autocalculate");
  }
  return false;
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::setCoefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2(
  double coefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2) {
  const bool result = setDouble(
    openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
      CoefficientBinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2,
    coefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2);
  OS_ASSERT(result);
  return result;
}

void RoomAirSettingsUnderFloorAirDistributionExterior_Impl::resetCoefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() {
  OS_ASSERT(setString(
    openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
      CoefficientBinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2,
    ""));
}

void RoomAirSettingsUnderFloorAirDistributionExterior_Impl::autocalculateCoefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() {
  OS_ASSERT(setString(
    openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
      CoefficientBinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2,
    "autocalculate"));
}

boost::optional<double>
RoomAirSettingsUnderFloorAirDistributionExterior_Impl::coefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() const {
  return getDouble(
    openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
      CoefficientCinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2,
    true);
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::isCoefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Defaulted()
  const {
  return isEmpty(
    openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
      CoefficientCinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2);
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::isCoefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Autocalculated()
  const {
  if (const auto value = getString(
        openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
          CoefficientCinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2,
        true)) {
    return openstudio::istringEqual(*value, "autocalculate");
  }
  return false;
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::setCoefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2(
  double coefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2) {
  const bool result = setDouble(
    openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
      CoefficientCinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2,
    coefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2);
  OS_ASSERT(result);
  return result;
}

void RoomAirSettingsUnderFloorAirDistributionExterior_Impl::resetCoefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() {
  OS_ASSERT(setString(
    openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
      CoefficientCinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2,
    ""));
}

void RoomAirSettingsUnderFloorAirDistributionExterior_Impl::autocalculateCoefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() {
  OS_ASSERT(setString(
    openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
      CoefficientCinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2,
    "autocalculate"));
}

boost::optional<double>
RoomAirSettingsUnderFloorAirDistributionExterior_Impl::coefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() const {
  return getDouble(
    openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
      CoefficientDinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2,
    true);
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::isCoefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Defaulted()
  const {
  return isEmpty(
    openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
      CoefficientDinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2);
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::isCoefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Autocalculated()
  const {
  if (const auto value = getString(
        openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
          CoefficientDinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2,
        true)) {
    return openstudio::istringEqual(*value, "autocalculate");
  }
  return false;
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::setCoefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2(
  double coefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2) {
  const bool result = setDouble(
    openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
      CoefficientDinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2,
    coefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2);
  OS_ASSERT(result);
  return result;
}

void RoomAirSettingsUnderFloorAirDistributionExterior_Impl::resetCoefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() {
  OS_ASSERT(setString(
    openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
      CoefficientDinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2,
    ""));
}

void RoomAirSettingsUnderFloorAirDistributionExterior_Impl::autocalculateCoefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() {
  OS_ASSERT(setString(
    openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
      CoefficientDinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2,
    "autocalculate"));
}

boost::optional<double>
RoomAirSettingsUnderFloorAirDistributionExterior_Impl::coefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() const {
  return getDouble(
    openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
      CoefficientEinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2,
    true);
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::isCoefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Defaulted()
  const {
  return isEmpty(
    openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
      CoefficientEinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2);
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::isCoefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Autocalculated()
  const {
  if (const auto value = getString(
        openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
          CoefficientEinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2,
        true)) {
    return openstudio::istringEqual(*value, "autocalculate");
  }
  return false;
}

bool RoomAirSettingsUnderFloorAirDistributionExterior_Impl::setCoefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2(
  double coefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2) {
  const bool result = setDouble(
    openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
      CoefficientEinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2,
    coefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2);
  OS_ASSERT(result);
  return result;
}

void RoomAirSettingsUnderFloorAirDistributionExterior_Impl::resetCoefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() {
  OS_ASSERT(setString(
    openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
      CoefficientEinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2,
    ""));
}

void RoomAirSettingsUnderFloorAirDistributionExterior_Impl::autocalculateCoefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() {
  OS_ASSERT(setString(
    openstudio::RoomAirSettings_UnderFloorAirDistributionExteriorFields::
      CoefficientEinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2,
    "autocalculate"));
}

std::vector<std::string> RoomAirSettingsUnderFloorAirDistributionExterior_Impl::floorDiffuserTypeValues() const {
  return openstudio::epmodel::RoomAirSettingsUnderFloorAirDistributionExterior::floorDiffuserTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
