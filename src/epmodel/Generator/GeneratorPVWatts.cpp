/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GeneratorPVWatts.hpp"
#include "GeneratorPVWatts_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Generator_PVWatts_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

GeneratorPVWatts::GeneratorPVWatts(const Model& model) : ModelObject(GeneratorPVWatts::iddObjectType(), model) {}

GeneratorPVWatts::GeneratorPVWatts(std::shared_ptr<detail::GeneratorPVWatts_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType GeneratorPVWatts::iddObjectType() {
  return IddObjectType::Generator_PVWatts;
}

std::vector<std::string> GeneratorPVWatts::pvWattsVersionValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Generator_PVWattsFields::PVWattsVersion);
}

std::vector<std::string> GeneratorPVWatts::moduleTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Generator_PVWattsFields::ModuleType);
}

std::vector<std::string> GeneratorPVWatts::arrayTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Generator_PVWattsFields::ArrayType);
}

std::string GeneratorPVWatts::pvWattsVersion() const {
  return getImpl<detail::GeneratorPVWatts_Impl>()->pvWattsVersion();
}

double GeneratorPVWatts::dcSystemCapacity() const {
  return getImpl<detail::GeneratorPVWatts_Impl>()->dcSystemCapacity();
}

bool GeneratorPVWatts::setDCSystemCapacity(double dcSystemCapacity) {
  return getImpl<detail::GeneratorPVWatts_Impl>()->setDCSystemCapacity(dcSystemCapacity);
}

std::string GeneratorPVWatts::moduleType() const {
  return getImpl<detail::GeneratorPVWatts_Impl>()->moduleType();
}

bool GeneratorPVWatts::isModuleTypeDefaulted() const {
  return getImpl<detail::GeneratorPVWatts_Impl>()->isModuleTypeDefaulted();
}

bool GeneratorPVWatts::setModuleType(const std::string& moduleType) {
  return getImpl<detail::GeneratorPVWatts_Impl>()->setModuleType(moduleType);
}

void GeneratorPVWatts::resetModuleType() {
  getImpl<detail::GeneratorPVWatts_Impl>()->resetModuleType();
}

std::string GeneratorPVWatts::arrayType() const {
  return getImpl<detail::GeneratorPVWatts_Impl>()->arrayType();
}

bool GeneratorPVWatts::isArrayTypeDefaulted() const {
  return getImpl<detail::GeneratorPVWatts_Impl>()->isArrayTypeDefaulted();
}

bool GeneratorPVWatts::setArrayType(const std::string& arrayType) {
  return getImpl<detail::GeneratorPVWatts_Impl>()->setArrayType(arrayType);
}

void GeneratorPVWatts::resetArrayType() {
  getImpl<detail::GeneratorPVWatts_Impl>()->resetArrayType();
}

double GeneratorPVWatts::systemLosses() const {
  return getImpl<detail::GeneratorPVWatts_Impl>()->systemLosses();
}

bool GeneratorPVWatts::isSystemLossesDefaulted() const {
  return getImpl<detail::GeneratorPVWatts_Impl>()->isSystemLossesDefaulted();
}

bool GeneratorPVWatts::setSystemLosses(double systemLosses) {
  return getImpl<detail::GeneratorPVWatts_Impl>()->setSystemLosses(systemLosses);
}

void GeneratorPVWatts::resetSystemLosses() {
  getImpl<detail::GeneratorPVWatts_Impl>()->resetSystemLosses();
}

double GeneratorPVWatts::tiltAngle() const {
  return getImpl<detail::GeneratorPVWatts_Impl>()->tiltAngle();
}

bool GeneratorPVWatts::isTiltAngleDefaulted() const {
  return getImpl<detail::GeneratorPVWatts_Impl>()->isTiltAngleDefaulted();
}

bool GeneratorPVWatts::setTiltAngle(double tiltAngle) {
  return getImpl<detail::GeneratorPVWatts_Impl>()->setTiltAngle(tiltAngle);
}

void GeneratorPVWatts::resetTiltAngle() {
  getImpl<detail::GeneratorPVWatts_Impl>()->resetTiltAngle();
}

double GeneratorPVWatts::azimuthAngle() const {
  return getImpl<detail::GeneratorPVWatts_Impl>()->azimuthAngle();
}

bool GeneratorPVWatts::isAzimuthAngleDefaulted() const {
  return getImpl<detail::GeneratorPVWatts_Impl>()->isAzimuthAngleDefaulted();
}

bool GeneratorPVWatts::setAzimuthAngle(double azimuthAngle) {
  return getImpl<detail::GeneratorPVWatts_Impl>()->setAzimuthAngle(azimuthAngle);
}

void GeneratorPVWatts::resetAzimuthAngle() {
  getImpl<detail::GeneratorPVWatts_Impl>()->resetAzimuthAngle();
}

double GeneratorPVWatts::groundCoverageRatio() const {
  return getImpl<detail::GeneratorPVWatts_Impl>()->groundCoverageRatio();
}

bool GeneratorPVWatts::isGroundCoverageRatioDefaulted() const {
  return getImpl<detail::GeneratorPVWatts_Impl>()->isGroundCoverageRatioDefaulted();
}

bool GeneratorPVWatts::setGroundCoverageRatio(double groundCoverageRatio) {
  return getImpl<detail::GeneratorPVWatts_Impl>()->setGroundCoverageRatio(groundCoverageRatio);
}

void GeneratorPVWatts::resetGroundCoverageRatio() {
  getImpl<detail::GeneratorPVWatts_Impl>()->resetGroundCoverageRatio();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string GeneratorPVWatts_Impl::pvWattsVersion() const {
  const auto value = getString(openstudio::Generator_PVWattsFields::PVWattsVersion, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorPVWatts_Impl::dcSystemCapacity() const {
  const auto value = getDouble(openstudio::Generator_PVWattsFields::DCSystemCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool GeneratorPVWatts_Impl::setDCSystemCapacity(double dcSystemCapacity) {
  return setDouble(openstudio::Generator_PVWattsFields::DCSystemCapacity, dcSystemCapacity);
}

std::string GeneratorPVWatts_Impl::moduleType() const {
  const auto value = getString(openstudio::Generator_PVWattsFields::ModuleType, true);
  OS_ASSERT(value);
  return *value;
}

bool GeneratorPVWatts_Impl::isModuleTypeDefaulted() const {
  return isEmpty(openstudio::Generator_PVWattsFields::ModuleType);
}

bool GeneratorPVWatts_Impl::setModuleType(const std::string& moduleType) {
  return setString(openstudio::Generator_PVWattsFields::ModuleType, moduleType);
}

void GeneratorPVWatts_Impl::resetModuleType() {
  OS_ASSERT(setString(openstudio::Generator_PVWattsFields::ModuleType, ""));
}

std::string GeneratorPVWatts_Impl::arrayType() const {
  const auto value = getString(openstudio::Generator_PVWattsFields::ArrayType, true);
  OS_ASSERT(value);
  return *value;
}

bool GeneratorPVWatts_Impl::isArrayTypeDefaulted() const {
  return isEmpty(openstudio::Generator_PVWattsFields::ArrayType);
}

bool GeneratorPVWatts_Impl::setArrayType(const std::string& arrayType) {
  return setString(openstudio::Generator_PVWattsFields::ArrayType, arrayType);
}

void GeneratorPVWatts_Impl::resetArrayType() {
  OS_ASSERT(setString(openstudio::Generator_PVWattsFields::ArrayType, ""));
}

double GeneratorPVWatts_Impl::systemLosses() const {
  if (const auto value = getDouble(openstudio::Generator_PVWattsFields::SystemLosses, false)) {
    return *value;
  }
  return 0.14;
}

bool GeneratorPVWatts_Impl::isSystemLossesDefaulted() const {
  return isEmpty(openstudio::Generator_PVWattsFields::SystemLosses);
}

bool GeneratorPVWatts_Impl::setSystemLosses(double systemLosses) {
  return setDouble(openstudio::Generator_PVWattsFields::SystemLosses, systemLosses);
}

void GeneratorPVWatts_Impl::resetSystemLosses() {
  OS_ASSERT(setString(openstudio::Generator_PVWattsFields::SystemLosses, ""));
}

double GeneratorPVWatts_Impl::tiltAngle() const {
  if (const auto value = getDouble(openstudio::Generator_PVWattsFields::TiltAngle, false)) {
    return *value;
  }
  return 20.0;
}

bool GeneratorPVWatts_Impl::isTiltAngleDefaulted() const {
  return isEmpty(openstudio::Generator_PVWattsFields::TiltAngle);
}

bool GeneratorPVWatts_Impl::setTiltAngle(double tiltAngle) {
  return setDouble(openstudio::Generator_PVWattsFields::TiltAngle, tiltAngle);
}

void GeneratorPVWatts_Impl::resetTiltAngle() {
  OS_ASSERT(setString(openstudio::Generator_PVWattsFields::TiltAngle, ""));
}

double GeneratorPVWatts_Impl::azimuthAngle() const {
  if (const auto value = getDouble(openstudio::Generator_PVWattsFields::AzimuthAngle, false)) {
    return *value;
  }
  return 180.0;
}

bool GeneratorPVWatts_Impl::isAzimuthAngleDefaulted() const {
  return isEmpty(openstudio::Generator_PVWattsFields::AzimuthAngle);
}

bool GeneratorPVWatts_Impl::setAzimuthAngle(double azimuthAngle) {
  return setDouble(openstudio::Generator_PVWattsFields::AzimuthAngle, azimuthAngle);
}

void GeneratorPVWatts_Impl::resetAzimuthAngle() {
  OS_ASSERT(setString(openstudio::Generator_PVWattsFields::AzimuthAngle, ""));
}

double GeneratorPVWatts_Impl::groundCoverageRatio() const {
  if (const auto value = getDouble(openstudio::Generator_PVWattsFields::GroundCoverageRatio, false)) {
    return *value;
  }
  return 0.4;
}

bool GeneratorPVWatts_Impl::isGroundCoverageRatioDefaulted() const {
  return isEmpty(openstudio::Generator_PVWattsFields::GroundCoverageRatio);
}

bool GeneratorPVWatts_Impl::setGroundCoverageRatio(double groundCoverageRatio) {
  return setDouble(openstudio::Generator_PVWattsFields::GroundCoverageRatio, groundCoverageRatio);
}

void GeneratorPVWatts_Impl::resetGroundCoverageRatio() {
  OS_ASSERT(setString(openstudio::Generator_PVWattsFields::GroundCoverageRatio, ""));
}

std::vector<std::string> GeneratorPVWatts_Impl::pvWattsVersionValues() const {
  return GeneratorPVWatts::pvWattsVersionValues();
}

std::vector<std::string> GeneratorPVWatts_Impl::moduleTypeValues() const {
  return GeneratorPVWatts::moduleTypeValues();
}

std::vector<std::string> GeneratorPVWatts_Impl::arrayTypeValues() const {
  return GeneratorPVWatts::arrayTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
