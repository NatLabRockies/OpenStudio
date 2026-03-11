/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "CoilSystemCoolingDX.hpp"
#include "CoilSystemCoolingDX_Impl.hpp"

#include "Model.hpp"
#include "ModelObject.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/CoilSystem_Cooling_DX_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

CoilSystemCoolingDX::CoilSystemCoolingDX(const Model& model) : ModelObject(CoilSystemCoolingDX::iddObjectType(), model) {}

CoilSystemCoolingDX::CoilSystemCoolingDX(std::shared_ptr<detail::CoilSystemCoolingDX_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType CoilSystemCoolingDX::iddObjectType() {
  return IddObjectType::CoilSystem_Cooling_DX;
}

std::vector<std::string> CoilSystemCoolingDX::coolingCoilObjectTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::CoilSystem_Cooling_DXFields::CoolingCoilObjectType);
}

std::vector<std::string> CoilSystemCoolingDX::dehumidificationControlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::CoilSystem_Cooling_DXFields::DehumidificationControlType);
}

std::string CoilSystemCoolingDX::coolingCoilObjectType() const {
  return getImpl<detail::CoilSystemCoolingDX_Impl>()->coolingCoilObjectType();
}

bool CoilSystemCoolingDX::setCoolingCoilObjectType(const std::string& coolingCoilObjectType) {
  return getImpl<detail::CoilSystemCoolingDX_Impl>()->setCoolingCoilObjectType(coolingCoilObjectType);
}

std::string CoilSystemCoolingDX::dehumidificationControlType() const {
  return getImpl<detail::CoilSystemCoolingDX_Impl>()->dehumidificationControlType();
}

bool CoilSystemCoolingDX::isDehumidificationControlTypeDefaulted() const {
  return getImpl<detail::CoilSystemCoolingDX_Impl>()->isDehumidificationControlTypeDefaulted();
}

bool CoilSystemCoolingDX::setDehumidificationControlType(const std::string& dehumidificationControlType) {
  return getImpl<detail::CoilSystemCoolingDX_Impl>()->setDehumidificationControlType(dehumidificationControlType);
}

void CoilSystemCoolingDX::resetDehumidificationControlType() {
  getImpl<detail::CoilSystemCoolingDX_Impl>()->resetDehumidificationControlType();
}

bool CoilSystemCoolingDX::runonSensibleLoad() const {
  return getImpl<detail::CoilSystemCoolingDX_Impl>()->runonSensibleLoad();
}

bool CoilSystemCoolingDX::isRunonSensibleLoadDefaulted() const {
  return getImpl<detail::CoilSystemCoolingDX_Impl>()->isRunonSensibleLoadDefaulted();
}

bool CoilSystemCoolingDX::setRunonSensibleLoad(bool runonSensibleLoad) {
  return getImpl<detail::CoilSystemCoolingDX_Impl>()->setRunonSensibleLoad(runonSensibleLoad);
}

void CoilSystemCoolingDX::resetRunonSensibleLoad() {
  getImpl<detail::CoilSystemCoolingDX_Impl>()->resetRunonSensibleLoad();
}

bool CoilSystemCoolingDX::runonLatentLoad() const {
  return getImpl<detail::CoilSystemCoolingDX_Impl>()->runonLatentLoad();
}

bool CoilSystemCoolingDX::isRunonLatentLoadDefaulted() const {
  return getImpl<detail::CoilSystemCoolingDX_Impl>()->isRunonLatentLoadDefaulted();
}

bool CoilSystemCoolingDX::setRunonLatentLoad(bool runonLatentLoad) {
  return getImpl<detail::CoilSystemCoolingDX_Impl>()->setRunonLatentLoad(runonLatentLoad);
}

void CoilSystemCoolingDX::resetRunonLatentLoad() {
  getImpl<detail::CoilSystemCoolingDX_Impl>()->resetRunonLatentLoad();
}

bool CoilSystemCoolingDX::useOutdoorAirDXCoolingCoil() const {
  return getImpl<detail::CoilSystemCoolingDX_Impl>()->useOutdoorAirDXCoolingCoil();
}

bool CoilSystemCoolingDX::isUseOutdoorAirDXCoolingCoilDefaulted() const {
  return getImpl<detail::CoilSystemCoolingDX_Impl>()->isUseOutdoorAirDXCoolingCoilDefaulted();
}

bool CoilSystemCoolingDX::setUseOutdoorAirDXCoolingCoil(bool useOutdoorAirDXCoolingCoil) {
  return getImpl<detail::CoilSystemCoolingDX_Impl>()->setUseOutdoorAirDXCoolingCoil(useOutdoorAirDXCoolingCoil);
}

void CoilSystemCoolingDX::resetUseOutdoorAirDXCoolingCoil() {
  getImpl<detail::CoilSystemCoolingDX_Impl>()->resetUseOutdoorAirDXCoolingCoil();
}

double CoilSystemCoolingDX::outdoorAirDXCoolingCoilLeavingMinimumAirTemperature() const {
  return getImpl<detail::CoilSystemCoolingDX_Impl>()->outdoorAirDXCoolingCoilLeavingMinimumAirTemperature();
}

bool CoilSystemCoolingDX::isOutdoorAirDXCoolingCoilLeavingMinimumAirTemperatureDefaulted() const {
  return getImpl<detail::CoilSystemCoolingDX_Impl>()->isOutdoorAirDXCoolingCoilLeavingMinimumAirTemperatureDefaulted();
}

bool CoilSystemCoolingDX::setOutdoorAirDXCoolingCoilLeavingMinimumAirTemperature(
  double outdoorAirDXCoolingCoilLeavingMinimumAirTemperature) {
  return getImpl<detail::CoilSystemCoolingDX_Impl>()->setOutdoorAirDXCoolingCoilLeavingMinimumAirTemperature(
    outdoorAirDXCoolingCoilLeavingMinimumAirTemperature);
}

void CoilSystemCoolingDX::resetOutdoorAirDXCoolingCoilLeavingMinimumAirTemperature() {
  getImpl<detail::CoilSystemCoolingDX_Impl>()->resetOutdoorAirDXCoolingCoilLeavingMinimumAirTemperature();
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

std::string CoilSystemCoolingDX_Impl::coolingCoilObjectType() const {
  const auto value = getString(openstudio::CoilSystem_Cooling_DXFields::CoolingCoilObjectType, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilSystemCoolingDX_Impl::setCoolingCoilObjectType(const std::string& coolingCoilObjectType) {
  return setString(openstudio::CoilSystem_Cooling_DXFields::CoolingCoilObjectType, coolingCoilObjectType);
}

std::string CoilSystemCoolingDX_Impl::dehumidificationControlType() const {
  const auto value = getString(openstudio::CoilSystem_Cooling_DXFields::DehumidificationControlType, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilSystemCoolingDX_Impl::isDehumidificationControlTypeDefaulted() const {
  return isEmpty(openstudio::CoilSystem_Cooling_DXFields::DehumidificationControlType);
}

bool CoilSystemCoolingDX_Impl::setDehumidificationControlType(const std::string& dehumidificationControlType) {
  return setString(openstudio::CoilSystem_Cooling_DXFields::DehumidificationControlType, dehumidificationControlType);
}

void CoilSystemCoolingDX_Impl::resetDehumidificationControlType() {
  OS_ASSERT(setString(openstudio::CoilSystem_Cooling_DXFields::DehumidificationControlType, ""));
}

bool CoilSystemCoolingDX_Impl::runonSensibleLoad() const {
  return getBooleanFieldValue(*this, openstudio::CoilSystem_Cooling_DXFields::RunonSensibleLoad);
}

bool CoilSystemCoolingDX_Impl::isRunonSensibleLoadDefaulted() const {
  return isEmpty(openstudio::CoilSystem_Cooling_DXFields::RunonSensibleLoad);
}

bool CoilSystemCoolingDX_Impl::setRunonSensibleLoad(bool runonSensibleLoad) {
  const bool result = setBooleanFieldValue(*this, openstudio::CoilSystem_Cooling_DXFields::RunonSensibleLoad, runonSensibleLoad);
  OS_ASSERT(result);
  return result;
}

void CoilSystemCoolingDX_Impl::resetRunonSensibleLoad() {
  OS_ASSERT(setString(openstudio::CoilSystem_Cooling_DXFields::RunonSensibleLoad, ""));
}

bool CoilSystemCoolingDX_Impl::runonLatentLoad() const {
  return getBooleanFieldValue(*this, openstudio::CoilSystem_Cooling_DXFields::RunonLatentLoad);
}

bool CoilSystemCoolingDX_Impl::isRunonLatentLoadDefaulted() const {
  return isEmpty(openstudio::CoilSystem_Cooling_DXFields::RunonLatentLoad);
}

bool CoilSystemCoolingDX_Impl::setRunonLatentLoad(bool runonLatentLoad) {
  const bool result = setBooleanFieldValue(*this, openstudio::CoilSystem_Cooling_DXFields::RunonLatentLoad, runonLatentLoad);
  OS_ASSERT(result);
  return result;
}

void CoilSystemCoolingDX_Impl::resetRunonLatentLoad() {
  OS_ASSERT(setString(openstudio::CoilSystem_Cooling_DXFields::RunonLatentLoad, ""));
}

bool CoilSystemCoolingDX_Impl::useOutdoorAirDXCoolingCoil() const {
  return getBooleanFieldValue(*this, openstudio::CoilSystem_Cooling_DXFields::UseOutdoorAirDXCoolingCoil);
}

bool CoilSystemCoolingDX_Impl::isUseOutdoorAirDXCoolingCoilDefaulted() const {
  return isEmpty(openstudio::CoilSystem_Cooling_DXFields::UseOutdoorAirDXCoolingCoil);
}

bool CoilSystemCoolingDX_Impl::setUseOutdoorAirDXCoolingCoil(bool useOutdoorAirDXCoolingCoil) {
  const bool result =
    setBooleanFieldValue(*this, openstudio::CoilSystem_Cooling_DXFields::UseOutdoorAirDXCoolingCoil, useOutdoorAirDXCoolingCoil);
  OS_ASSERT(result);
  return result;
}

void CoilSystemCoolingDX_Impl::resetUseOutdoorAirDXCoolingCoil() {
  OS_ASSERT(setString(openstudio::CoilSystem_Cooling_DXFields::UseOutdoorAirDXCoolingCoil, ""));
}

double CoilSystemCoolingDX_Impl::outdoorAirDXCoolingCoilLeavingMinimumAirTemperature() const {
  const auto value = getDouble(openstudio::CoilSystem_Cooling_DXFields::OutdoorAirDXCoolingCoilLeavingMinimumAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilSystemCoolingDX_Impl::isOutdoorAirDXCoolingCoilLeavingMinimumAirTemperatureDefaulted() const {
  return isEmpty(openstudio::CoilSystem_Cooling_DXFields::OutdoorAirDXCoolingCoilLeavingMinimumAirTemperature);
}

bool CoilSystemCoolingDX_Impl::setOutdoorAirDXCoolingCoilLeavingMinimumAirTemperature(
  double outdoorAirDXCoolingCoilLeavingMinimumAirTemperature) {
  return setDouble(openstudio::CoilSystem_Cooling_DXFields::OutdoorAirDXCoolingCoilLeavingMinimumAirTemperature,
                   outdoorAirDXCoolingCoilLeavingMinimumAirTemperature);
}

void CoilSystemCoolingDX_Impl::resetOutdoorAirDXCoolingCoilLeavingMinimumAirTemperature() {
  OS_ASSERT(setString(openstudio::CoilSystem_Cooling_DXFields::OutdoorAirDXCoolingCoilLeavingMinimumAirTemperature, ""));
}

std::vector<std::string> CoilSystemCoolingDX_Impl::coolingCoilObjectTypeValues() const {
  return openstudio::epmodel::CoilSystemCoolingDX::coolingCoilObjectTypeValues();
}

std::vector<std::string> CoilSystemCoolingDX_Impl::dehumidificationControlTypeValues() const {
  return openstudio::epmodel::CoilSystemCoolingDX::dehumidificationControlTypeValues();
}

boost::optional<ModelObject> CoilSystemCoolingDX_Impl::coolingCoil() const {
  return getObject<ModelObject>().getModelObjectTarget<ModelObject>(openstudio::CoilSystem_Cooling_DXFields::CoolingCoilName);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
