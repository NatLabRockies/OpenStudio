/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ExternalInterfaceFunctionalMockupUnitImport.hpp"
#include "ExternalInterfaceFunctionalMockupUnitImport_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ExternalInterface_FunctionalMockupUnitImport_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

#include <stdexcept>

namespace openstudio {
namespace epmodel {

ExternalInterfaceFunctionalMockupUnitImport::ExternalInterfaceFunctionalMockupUnitImport(const Model& model, const std::string& fmuName)
  : ModelObject(ExternalInterfaceFunctionalMockupUnitImport::iddObjectType(), model) {
  const bool ok = setFMUFileName(fmuName);
  if (!ok) {
    remove();
    throw std::runtime_error("Unable to set FMU File Name for ExternalInterfaceFunctionalMockupUnitImport.");
  }
}

ExternalInterfaceFunctionalMockupUnitImport::ExternalInterfaceFunctionalMockupUnitImport(
  std::shared_ptr<detail::ExternalInterfaceFunctionalMockupUnitImport_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType ExternalInterfaceFunctionalMockupUnitImport::iddObjectType() {
  return IddObjectType::ExternalInterface_FunctionalMockupUnitImport;
}

double ExternalInterfaceFunctionalMockupUnitImport::fMUTimeout() const {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImport_Impl>()->fMUTimeout();
}

bool ExternalInterfaceFunctionalMockupUnitImport::isFMUTimeoutDefaulted() const {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImport_Impl>()->isFMUTimeoutDefaulted();
}

int ExternalInterfaceFunctionalMockupUnitImport::fMULoggingOn() const {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImport_Impl>()->fMULoggingOn();
}

bool ExternalInterfaceFunctionalMockupUnitImport::isFMULoggingOnDefaulted() const {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImport_Impl>()->isFMULoggingOnDefaulted();
}

std::string ExternalInterfaceFunctionalMockupUnitImport::fMUFileName() const {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImport_Impl>()->fMUFileName();
}

bool ExternalInterfaceFunctionalMockupUnitImport::setFMUTimeout(double fMUTimeout) {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImport_Impl>()->setFMUTimeout(fMUTimeout);
}

void ExternalInterfaceFunctionalMockupUnitImport::resetFMUTimeout() {
  getImpl<detail::ExternalInterfaceFunctionalMockupUnitImport_Impl>()->resetFMUTimeout();
}

bool ExternalInterfaceFunctionalMockupUnitImport::setFMULoggingOn(int fMULoggingOn) {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImport_Impl>()->setFMULoggingOn(fMULoggingOn);
}

void ExternalInterfaceFunctionalMockupUnitImport::resetFMULoggingOn() {
  getImpl<detail::ExternalInterfaceFunctionalMockupUnitImport_Impl>()->resetFMULoggingOn();
}

bool ExternalInterfaceFunctionalMockupUnitImport::setFMUFileName(const std::string& fMUName) {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImport_Impl>()->setFMUFileName(fMUName);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double ExternalInterfaceFunctionalMockupUnitImport_Impl::fMUTimeout() const {
  const auto value = getDouble(openstudio::ExternalInterface_FunctionalMockupUnitImportFields::FMUTimeout, true);
  if (value) {
    return *value;
  }
  return 0.0;
}

bool ExternalInterfaceFunctionalMockupUnitImport_Impl::isFMUTimeoutDefaulted() const {
  return !getDouble(openstudio::ExternalInterface_FunctionalMockupUnitImportFields::FMUTimeout, false);
}

int ExternalInterfaceFunctionalMockupUnitImport_Impl::fMULoggingOn() const {
  const auto value = getInt(openstudio::ExternalInterface_FunctionalMockupUnitImportFields::FMULoggingOn, true);
  if (value) {
    return *value;
  }
  return 0;
}

bool ExternalInterfaceFunctionalMockupUnitImport_Impl::isFMULoggingOnDefaulted() const {
  return !getInt(openstudio::ExternalInterface_FunctionalMockupUnitImportFields::FMULoggingOn, false);
}

std::string ExternalInterfaceFunctionalMockupUnitImport_Impl::fMUFileName() const {
  const auto value = getString(openstudio::ExternalInterface_FunctionalMockupUnitImportFields::FMUFileName, true);
  OS_ASSERT(value);
  return *value;
}

bool ExternalInterfaceFunctionalMockupUnitImport_Impl::setFMUTimeout(double fMUTimeout) {
  const bool result = setDouble(openstudio::ExternalInterface_FunctionalMockupUnitImportFields::FMUTimeout, fMUTimeout);
  OS_ASSERT(result);
  return result;
}

void ExternalInterfaceFunctionalMockupUnitImport_Impl::resetFMUTimeout() {
  const bool result = setString(openstudio::ExternalInterface_FunctionalMockupUnitImportFields::FMUTimeout, "");
  OS_ASSERT(result);
}

bool ExternalInterfaceFunctionalMockupUnitImport_Impl::setFMULoggingOn(int fMULoggingOn) {
  const bool result = setInt(openstudio::ExternalInterface_FunctionalMockupUnitImportFields::FMULoggingOn, fMULoggingOn);
  OS_ASSERT(result);
  return result;
}

void ExternalInterfaceFunctionalMockupUnitImport_Impl::resetFMULoggingOn() {
  const bool result = setString(openstudio::ExternalInterface_FunctionalMockupUnitImportFields::FMULoggingOn, "");
  OS_ASSERT(result);
}

bool ExternalInterfaceFunctionalMockupUnitImport_Impl::setFMUFileName(const std::string& fMUName) {
  return setString(openstudio::ExternalInterface_FunctionalMockupUnitImportFields::FMUFileName, fMUName);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
