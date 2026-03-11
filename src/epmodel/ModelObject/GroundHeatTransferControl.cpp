/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatTransferControl.hpp"
#include "GroundHeatTransferControl_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GroundHeatTransfer_Control_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

GroundHeatTransferControl::GroundHeatTransferControl(const Model& model) : ModelObject(GroundHeatTransferControl::iddObjectType(), model) {}

GroundHeatTransferControl::GroundHeatTransferControl(std::shared_ptr<detail::GroundHeatTransferControl_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType GroundHeatTransferControl::iddObjectType() {
  return IddObjectType::GroundHeatTransfer_Control;
}

bool GroundHeatTransferControl::runBasementPreprocessor() const {
  return getImpl<detail::GroundHeatTransferControl_Impl>()->runBasementPreprocessor();
}

bool GroundHeatTransferControl::isRunBasementPreprocessorDefaulted() const {
  return getImpl<detail::GroundHeatTransferControl_Impl>()->isRunBasementPreprocessorDefaulted();
}

bool GroundHeatTransferControl::setRunBasementPreprocessor(bool runBasementPreprocessor) {
  return getImpl<detail::GroundHeatTransferControl_Impl>()->setRunBasementPreprocessor(runBasementPreprocessor);
}

void GroundHeatTransferControl::resetRunBasementPreprocessor() {
  getImpl<detail::GroundHeatTransferControl_Impl>()->resetRunBasementPreprocessor();
}

bool GroundHeatTransferControl::runSlabPreprocessor() const {
  return getImpl<detail::GroundHeatTransferControl_Impl>()->runSlabPreprocessor();
}

bool GroundHeatTransferControl::isRunSlabPreprocessorDefaulted() const {
  return getImpl<detail::GroundHeatTransferControl_Impl>()->isRunSlabPreprocessorDefaulted();
}

bool GroundHeatTransferControl::setRunSlabPreprocessor(bool runSlabPreprocessor) {
  return getImpl<detail::GroundHeatTransferControl_Impl>()->setRunSlabPreprocessor(runSlabPreprocessor);
}

void GroundHeatTransferControl::resetRunSlabPreprocessor() {
  getImpl<detail::GroundHeatTransferControl_Impl>()->resetRunSlabPreprocessor();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

bool GroundHeatTransferControl_Impl::runBasementPreprocessor() const {
  const auto value = getString(openstudio::GroundHeatTransfer_ControlFields::RunBasementPreprocessor, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool GroundHeatTransferControl_Impl::isRunBasementPreprocessorDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_ControlFields::RunBasementPreprocessor);
}

bool GroundHeatTransferControl_Impl::setRunBasementPreprocessor(bool runBasementPreprocessor) {
  const bool result = setString(openstudio::GroundHeatTransfer_ControlFields::RunBasementPreprocessor,
                                runBasementPreprocessor ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

void GroundHeatTransferControl_Impl::resetRunBasementPreprocessor() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_ControlFields::RunBasementPreprocessor, ""));
}

bool GroundHeatTransferControl_Impl::runSlabPreprocessor() const {
  const auto value = getString(openstudio::GroundHeatTransfer_ControlFields::RunSlabPreprocessor, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool GroundHeatTransferControl_Impl::isRunSlabPreprocessorDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_ControlFields::RunSlabPreprocessor);
}

bool GroundHeatTransferControl_Impl::setRunSlabPreprocessor(bool runSlabPreprocessor) {
  const bool result = setString(openstudio::GroundHeatTransfer_ControlFields::RunSlabPreprocessor, runSlabPreprocessor ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

void GroundHeatTransferControl_Impl::resetRunSlabPreprocessor() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_ControlFields::RunSlabPreprocessor, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
