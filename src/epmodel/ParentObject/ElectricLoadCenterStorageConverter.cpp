/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/ElectricLoadCenterStorageConverter.hpp"
#include "ParentObject/ElectricLoadCenterStorageConverter_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ElectricLoadCenter_Storage_Converter_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

ElectricLoadCenterStorageConverter::ElectricLoadCenterStorageConverter(const Model& model)
  : ParentObject(ElectricLoadCenterStorageConverter::iddObjectType(), model) {
  const bool ok = setSimpleFixedEfficiency(0.95);
  OS_ASSERT(ok);
}

ElectricLoadCenterStorageConverter::ElectricLoadCenterStorageConverter(
  std::shared_ptr<detail::ElectricLoadCenterStorageConverter_Impl> impl)
  : ParentObject(std::move(impl)) {}

IddObjectType ElectricLoadCenterStorageConverter::iddObjectType() {
  return IddObjectType::ElectricLoadCenter_Storage_Converter;
}

std::vector<std::string> ElectricLoadCenterStorageConverter::powerConversionEfficiencyMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::ElectricLoadCenter_Storage_ConverterFields::PowerConversionEfficiencyMethod);
}

std::string ElectricLoadCenterStorageConverter::powerConversionEfficiencyMethod() const {
  return getImpl<detail::ElectricLoadCenterStorageConverter_Impl>()->powerConversionEfficiencyMethod();
}

boost::optional<double> ElectricLoadCenterStorageConverter::simpleFixedEfficiency() const {
  return getImpl<detail::ElectricLoadCenterStorageConverter_Impl>()->simpleFixedEfficiency();
}

bool ElectricLoadCenterStorageConverter::setSimpleFixedEfficiency(double simpleFixedEfficiency) {
  return getImpl<detail::ElectricLoadCenterStorageConverter_Impl>()->setSimpleFixedEfficiency(simpleFixedEfficiency);
}

boost::optional<double> ElectricLoadCenterStorageConverter::designMaximumContinuousInputPower() const {
  return getImpl<detail::ElectricLoadCenterStorageConverter_Impl>()->designMaximumContinuousInputPower();
}

bool ElectricLoadCenterStorageConverter::setDesignMaximumContinuousInputPower(double designMaximumContinuousInputPower) {
  return getImpl<detail::ElectricLoadCenterStorageConverter_Impl>()->setDesignMaximumContinuousInputPower(designMaximumContinuousInputPower);
}

double ElectricLoadCenterStorageConverter::ancillaryPowerConsumedInStandby() const {
  return getImpl<detail::ElectricLoadCenterStorageConverter_Impl>()->ancillaryPowerConsumedInStandby();
}

bool ElectricLoadCenterStorageConverter::isAncillaryPowerConsumedInStandbyDefaulted() const {
  return getImpl<detail::ElectricLoadCenterStorageConverter_Impl>()->isAncillaryPowerConsumedInStandbyDefaulted();
}

bool ElectricLoadCenterStorageConverter::setAncillaryPowerConsumedInStandby(double ancillaryPowerConsumedInStandby) {
  return getImpl<detail::ElectricLoadCenterStorageConverter_Impl>()->setAncillaryPowerConsumedInStandby(ancillaryPowerConsumedInStandby);
}

void ElectricLoadCenterStorageConverter::resetAncillaryPowerConsumedInStandby() {
  getImpl<detail::ElectricLoadCenterStorageConverter_Impl>()->resetAncillaryPowerConsumedInStandby();
}

double ElectricLoadCenterStorageConverter::radiativeFraction() const {
  return getImpl<detail::ElectricLoadCenterStorageConverter_Impl>()->radiativeFraction();
}

bool ElectricLoadCenterStorageConverter::isRadiativeFractionDefaulted() const {
  return getImpl<detail::ElectricLoadCenterStorageConverter_Impl>()->isRadiativeFractionDefaulted();
}

bool ElectricLoadCenterStorageConverter::setRadiativeFraction(double radiativeFraction) {
  return getImpl<detail::ElectricLoadCenterStorageConverter_Impl>()->setRadiativeFraction(radiativeFraction);
}

void ElectricLoadCenterStorageConverter::resetRadiativeFraction() {
  getImpl<detail::ElectricLoadCenterStorageConverter_Impl>()->resetRadiativeFraction();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string ElectricLoadCenterStorageConverter_Impl::powerConversionEfficiencyMethod() const {
  const auto value = getString(openstudio::ElectricLoadCenter_Storage_ConverterFields::PowerConversionEfficiencyMethod, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> ElectricLoadCenterStorageConverter_Impl::simpleFixedEfficiency() const {
  return getDouble(openstudio::ElectricLoadCenter_Storage_ConverterFields::SimpleFixedEfficiency, false);
}

bool ElectricLoadCenterStorageConverter_Impl::setSimpleFixedEfficiency(double simpleFixedEfficiency) {
  bool result = setDouble(openstudio::ElectricLoadCenter_Storage_ConverterFields::SimpleFixedEfficiency, simpleFixedEfficiency);
  if (result) {
    result = setString(openstudio::ElectricLoadCenter_Storage_ConverterFields::PowerConversionEfficiencyMethod, "SimpleFixed");
    OS_ASSERT(result);
    result = setString(openstudio::ElectricLoadCenter_Storage_ConverterFields::DesignMaximumContinuousInputPower, "");
    OS_ASSERT(result);
    result = setString(openstudio::ElectricLoadCenter_Storage_ConverterFields::EfficiencyFunctionofPowerCurveName, "");
    OS_ASSERT(result);
  }
  return result;
}

boost::optional<double> ElectricLoadCenterStorageConverter_Impl::designMaximumContinuousInputPower() const {
  return getDouble(openstudio::ElectricLoadCenter_Storage_ConverterFields::DesignMaximumContinuousInputPower, true);
}

bool ElectricLoadCenterStorageConverter_Impl::setDesignMaximumContinuousInputPower(double designMaximumContinuousInputPower) {
  bool result = setDouble(openstudio::ElectricLoadCenter_Storage_ConverterFields::DesignMaximumContinuousInputPower,
                          designMaximumContinuousInputPower);
  if (result) {
    result = setString(openstudio::ElectricLoadCenter_Storage_ConverterFields::PowerConversionEfficiencyMethod, "FunctionOfPower");
    OS_ASSERT(result);
    result = setString(openstudio::ElectricLoadCenter_Storage_ConverterFields::SimpleFixedEfficiency, "");
    OS_ASSERT(result);
  }
  return result;
}

double ElectricLoadCenterStorageConverter_Impl::ancillaryPowerConsumedInStandby() const {
  const auto value = getDouble(openstudio::ElectricLoadCenter_Storage_ConverterFields::AncillaryPowerConsumedInStandby, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricLoadCenterStorageConverter_Impl::isAncillaryPowerConsumedInStandbyDefaulted() const {
  return isEmpty(openstudio::ElectricLoadCenter_Storage_ConverterFields::AncillaryPowerConsumedInStandby);
}

bool ElectricLoadCenterStorageConverter_Impl::setAncillaryPowerConsumedInStandby(double ancillaryPowerConsumedInStandby) {
  const bool result =
    setDouble(openstudio::ElectricLoadCenter_Storage_ConverterFields::AncillaryPowerConsumedInStandby, ancillaryPowerConsumedInStandby);
  OS_ASSERT(result);
  return result;
}

void ElectricLoadCenterStorageConverter_Impl::resetAncillaryPowerConsumedInStandby() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_Storage_ConverterFields::AncillaryPowerConsumedInStandby, ""));
}

double ElectricLoadCenterStorageConverter_Impl::radiativeFraction() const {
  const auto value = getDouble(openstudio::ElectricLoadCenter_Storage_ConverterFields::RadiativeFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricLoadCenterStorageConverter_Impl::isRadiativeFractionDefaulted() const {
  return isEmpty(openstudio::ElectricLoadCenter_Storage_ConverterFields::RadiativeFraction);
}

bool ElectricLoadCenterStorageConverter_Impl::setRadiativeFraction(double radiativeFraction) {
  const bool result = setDouble(openstudio::ElectricLoadCenter_Storage_ConverterFields::RadiativeFraction, radiativeFraction);
  OS_ASSERT(result);
  return result;
}

void ElectricLoadCenterStorageConverter_Impl::resetRadiativeFraction() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_Storage_ConverterFields::RadiativeFraction, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
