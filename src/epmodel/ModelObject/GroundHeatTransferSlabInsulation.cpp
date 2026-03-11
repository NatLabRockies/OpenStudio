/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatTransferSlabInsulation.hpp"
#include "GroundHeatTransferSlabInsulation_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GroundHeatTransfer_Slab_Insulation_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

GroundHeatTransferSlabInsulation::GroundHeatTransferSlabInsulation(const Model& model)
  : ModelObject(GroundHeatTransferSlabInsulation::iddObjectType(), model) {}

GroundHeatTransferSlabInsulation::GroundHeatTransferSlabInsulation(std::shared_ptr<detail::GroundHeatTransferSlabInsulation_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType GroundHeatTransferSlabInsulation::iddObjectType() {
  return IddObjectType::GroundHeatTransfer_Slab_Insulation;
}

std::vector<std::string> GroundHeatTransferSlabInsulation::iVINSFlagIsthereverticalinsulationValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::GroundHeatTransfer_Slab_InsulationFields::IVINS_Flag_Isthereverticalinsulation);
}

double GroundHeatTransferSlabInsulation::rINSRvalueofunderslabinsulation() const {
  return getImpl<detail::GroundHeatTransferSlabInsulation_Impl>()->rINSRvalueofunderslabinsulation();
}

double GroundHeatTransferSlabInsulation::dINSWidthofstripofunderslabinsulation() const {
  return getImpl<detail::GroundHeatTransferSlabInsulation_Impl>()->dINSWidthofstripofunderslabinsulation();
}

double GroundHeatTransferSlabInsulation::rVINSRvalueofverticalinsulation() const {
  return getImpl<detail::GroundHeatTransferSlabInsulation_Impl>()->rVINSRvalueofverticalinsulation();
}

double GroundHeatTransferSlabInsulation::zVINSDepthofverticalinsulation() const {
  return getImpl<detail::GroundHeatTransferSlabInsulation_Impl>()->zVINSDepthofverticalinsulation();
}

std::string GroundHeatTransferSlabInsulation::iVINSFlagIsthereverticalinsulation() const {
  return getImpl<detail::GroundHeatTransferSlabInsulation_Impl>()->iVINSFlagIsthereverticalinsulation();
}

bool GroundHeatTransferSlabInsulation::isRINSRvalueofunderslabinsulationDefaulted() const {
  return getImpl<detail::GroundHeatTransferSlabInsulation_Impl>()->isRINSRvalueofunderslabinsulationDefaulted();
}

bool GroundHeatTransferSlabInsulation::isDINSWidthofstripofunderslabinsulationDefaulted() const {
  return getImpl<detail::GroundHeatTransferSlabInsulation_Impl>()->isDINSWidthofstripofunderslabinsulationDefaulted();
}

bool GroundHeatTransferSlabInsulation::isRVINSRvalueofverticalinsulationDefaulted() const {
  return getImpl<detail::GroundHeatTransferSlabInsulation_Impl>()->isRVINSRvalueofverticalinsulationDefaulted();
}

bool GroundHeatTransferSlabInsulation::isZVINSDepthofverticalinsulationDefaulted() const {
  return getImpl<detail::GroundHeatTransferSlabInsulation_Impl>()->isZVINSDepthofverticalinsulationDefaulted();
}

bool GroundHeatTransferSlabInsulation::isIVINSFlagIsthereverticalinsulationDefaulted() const {
  return getImpl<detail::GroundHeatTransferSlabInsulation_Impl>()->isIVINSFlagIsthereverticalinsulationDefaulted();
}

bool GroundHeatTransferSlabInsulation::setRINSRvalueofunderslabinsulation(double rINSRvalueofunderslabinsulation) {
  return getImpl<detail::GroundHeatTransferSlabInsulation_Impl>()->setRINSRvalueofunderslabinsulation(rINSRvalueofunderslabinsulation);
}

bool GroundHeatTransferSlabInsulation::setDINSWidthofstripofunderslabinsulation(double dINSWidthofstripofunderslabinsulation) {
  return getImpl<detail::GroundHeatTransferSlabInsulation_Impl>()->setDINSWidthofstripofunderslabinsulation(
    dINSWidthofstripofunderslabinsulation);
}

bool GroundHeatTransferSlabInsulation::setRVINSRvalueofverticalinsulation(double rVINSRvalueofverticalinsulation) {
  return getImpl<detail::GroundHeatTransferSlabInsulation_Impl>()->setRVINSRvalueofverticalinsulation(rVINSRvalueofverticalinsulation);
}

bool GroundHeatTransferSlabInsulation::setZVINSDepthofverticalinsulation(double zVINSDepthofverticalinsulation) {
  return getImpl<detail::GroundHeatTransferSlabInsulation_Impl>()->setZVINSDepthofverticalinsulation(zVINSDepthofverticalinsulation);
}

bool GroundHeatTransferSlabInsulation::setIVINSFlagIsthereverticalinsulation(const std::string& iVINSFlagIsthereverticalinsulation) {
  return getImpl<detail::GroundHeatTransferSlabInsulation_Impl>()->setIVINSFlagIsthereverticalinsulation(
    iVINSFlagIsthereverticalinsulation);
}

void GroundHeatTransferSlabInsulation::resetRINSRvalueofunderslabinsulation() {
  getImpl<detail::GroundHeatTransferSlabInsulation_Impl>()->resetRINSRvalueofunderslabinsulation();
}

void GroundHeatTransferSlabInsulation::resetDINSWidthofstripofunderslabinsulation() {
  getImpl<detail::GroundHeatTransferSlabInsulation_Impl>()->resetDINSWidthofstripofunderslabinsulation();
}

void GroundHeatTransferSlabInsulation::resetRVINSRvalueofverticalinsulation() {
  getImpl<detail::GroundHeatTransferSlabInsulation_Impl>()->resetRVINSRvalueofverticalinsulation();
}

void GroundHeatTransferSlabInsulation::resetZVINSDepthofverticalinsulation() {
  getImpl<detail::GroundHeatTransferSlabInsulation_Impl>()->resetZVINSDepthofverticalinsulation();
}

void GroundHeatTransferSlabInsulation::resetIVINSFlagIsthereverticalinsulation() {
  getImpl<detail::GroundHeatTransferSlabInsulation_Impl>()->resetIVINSFlagIsthereverticalinsulation();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double GroundHeatTransferSlabInsulation_Impl::rINSRvalueofunderslabinsulation() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_InsulationFields::RINS_Rvalueofunderslabinsulation, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferSlabInsulation_Impl::dINSWidthofstripofunderslabinsulation() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_InsulationFields::DINS_Widthofstripofunderslabinsulation, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferSlabInsulation_Impl::rVINSRvalueofverticalinsulation() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_InsulationFields::RVINS_Rvalueofverticalinsulation, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferSlabInsulation_Impl::zVINSDepthofverticalinsulation() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_InsulationFields::ZVINS_Depthofverticalinsulation, true);
  OS_ASSERT(value);
  return *value;
}

std::string GroundHeatTransferSlabInsulation_Impl::iVINSFlagIsthereverticalinsulation() const {
  const auto value = getString(openstudio::GroundHeatTransfer_Slab_InsulationFields::IVINS_Flag_Isthereverticalinsulation, true);
  OS_ASSERT(value);
  return *value;
}

bool GroundHeatTransferSlabInsulation_Impl::isRINSRvalueofunderslabinsulationDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Slab_InsulationFields::RINS_Rvalueofunderslabinsulation);
}

bool GroundHeatTransferSlabInsulation_Impl::isDINSWidthofstripofunderslabinsulationDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Slab_InsulationFields::DINS_Widthofstripofunderslabinsulation);
}

bool GroundHeatTransferSlabInsulation_Impl::isRVINSRvalueofverticalinsulationDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Slab_InsulationFields::RVINS_Rvalueofverticalinsulation);
}

bool GroundHeatTransferSlabInsulation_Impl::isZVINSDepthofverticalinsulationDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Slab_InsulationFields::ZVINS_Depthofverticalinsulation);
}

bool GroundHeatTransferSlabInsulation_Impl::isIVINSFlagIsthereverticalinsulationDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Slab_InsulationFields::IVINS_Flag_Isthereverticalinsulation);
}

bool GroundHeatTransferSlabInsulation_Impl::setRINSRvalueofunderslabinsulation(double rINSRvalueofunderslabinsulation) {
  const bool result =
    setDouble(openstudio::GroundHeatTransfer_Slab_InsulationFields::RINS_Rvalueofunderslabinsulation, rINSRvalueofunderslabinsulation);
  OS_ASSERT(result);
  return result;
}

bool GroundHeatTransferSlabInsulation_Impl::setDINSWidthofstripofunderslabinsulation(double dINSWidthofstripofunderslabinsulation) {
  const bool result = setDouble(openstudio::GroundHeatTransfer_Slab_InsulationFields::DINS_Widthofstripofunderslabinsulation,
                                dINSWidthofstripofunderslabinsulation);
  OS_ASSERT(result);
  return result;
}

bool GroundHeatTransferSlabInsulation_Impl::setRVINSRvalueofverticalinsulation(double rVINSRvalueofverticalinsulation) {
  const bool result =
    setDouble(openstudio::GroundHeatTransfer_Slab_InsulationFields::RVINS_Rvalueofverticalinsulation, rVINSRvalueofverticalinsulation);
  OS_ASSERT(result);
  return result;
}

bool GroundHeatTransferSlabInsulation_Impl::setZVINSDepthofverticalinsulation(double zVINSDepthofverticalinsulation) {
  const bool result =
    setDouble(openstudio::GroundHeatTransfer_Slab_InsulationFields::ZVINS_Depthofverticalinsulation, zVINSDepthofverticalinsulation);
  OS_ASSERT(result);
  return result;
}

bool GroundHeatTransferSlabInsulation_Impl::setIVINSFlagIsthereverticalinsulation(const std::string& iVINSFlagIsthereverticalinsulation) {
  return setString(openstudio::GroundHeatTransfer_Slab_InsulationFields::IVINS_Flag_Isthereverticalinsulation,
                   iVINSFlagIsthereverticalinsulation);
}

void GroundHeatTransferSlabInsulation_Impl::resetRINSRvalueofunderslabinsulation() {
  const bool result = setString(openstudio::GroundHeatTransfer_Slab_InsulationFields::RINS_Rvalueofunderslabinsulation, "");
  OS_ASSERT(result);
}

void GroundHeatTransferSlabInsulation_Impl::resetDINSWidthofstripofunderslabinsulation() {
  const bool result = setString(openstudio::GroundHeatTransfer_Slab_InsulationFields::DINS_Widthofstripofunderslabinsulation, "");
  OS_ASSERT(result);
}

void GroundHeatTransferSlabInsulation_Impl::resetRVINSRvalueofverticalinsulation() {
  const bool result = setString(openstudio::GroundHeatTransfer_Slab_InsulationFields::RVINS_Rvalueofverticalinsulation, "");
  OS_ASSERT(result);
}

void GroundHeatTransferSlabInsulation_Impl::resetZVINSDepthofverticalinsulation() {
  const bool result = setString(openstudio::GroundHeatTransfer_Slab_InsulationFields::ZVINS_Depthofverticalinsulation, "");
  OS_ASSERT(result);
}

void GroundHeatTransferSlabInsulation_Impl::resetIVINSFlagIsthereverticalinsulation() {
  const bool result = setString(openstudio::GroundHeatTransfer_Slab_InsulationFields::IVINS_Flag_Isthereverticalinsulation, "");
  OS_ASSERT(result);
}

std::vector<std::string> GroundHeatTransferSlabInsulation_Impl::iVINSFlagIsthereverticalinsulationValues() const {
  return openstudio::epmodel::GroundHeatTransferSlabInsulation::iVINSFlagIsthereverticalinsulationValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
