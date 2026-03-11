/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatTransferSlabMatlProps.hpp"
#include "GroundHeatTransferSlabMatlProps_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GroundHeatTransfer_Slab_MatlProps_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

GroundHeatTransferSlabMatlProps::GroundHeatTransferSlabMatlProps(const Model& model)
  : ModelObject(GroundHeatTransferSlabMatlProps::iddObjectType(), model) {}

GroundHeatTransferSlabMatlProps::GroundHeatTransferSlabMatlProps(std::shared_ptr<detail::GroundHeatTransferSlabMatlProps_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType GroundHeatTransferSlabMatlProps::iddObjectType() {
  return IddObjectType::GroundHeatTransfer_Slab_MatlProps;
}

double GroundHeatTransferSlabMatlProps::rHOSlabMaterialdensity() const {
  return getImpl<detail::GroundHeatTransferSlabMatlProps_Impl>()->rHOSlabMaterialdensity();
}

double GroundHeatTransferSlabMatlProps::rHOSoilDensity() const {
  return getImpl<detail::GroundHeatTransferSlabMatlProps_Impl>()->rHOSoilDensity();
}

double GroundHeatTransferSlabMatlProps::cPSlabCP() const {
  return getImpl<detail::GroundHeatTransferSlabMatlProps_Impl>()->cPSlabCP();
}

double GroundHeatTransferSlabMatlProps::cPSoilCP() const {
  return getImpl<detail::GroundHeatTransferSlabMatlProps_Impl>()->cPSoilCP();
}

double GroundHeatTransferSlabMatlProps::tCONSlabk() const {
  return getImpl<detail::GroundHeatTransferSlabMatlProps_Impl>()->tCONSlabk();
}

double GroundHeatTransferSlabMatlProps::tCONSoilk() const {
  return getImpl<detail::GroundHeatTransferSlabMatlProps_Impl>()->tCONSoilk();
}

bool GroundHeatTransferSlabMatlProps::isRHOSlabMaterialdensityDefaulted() const {
  return getImpl<detail::GroundHeatTransferSlabMatlProps_Impl>()->isRHOSlabMaterialdensityDefaulted();
}

bool GroundHeatTransferSlabMatlProps::isRHOSoilDensityDefaulted() const {
  return getImpl<detail::GroundHeatTransferSlabMatlProps_Impl>()->isRHOSoilDensityDefaulted();
}

bool GroundHeatTransferSlabMatlProps::isCPSlabCPDefaulted() const {
  return getImpl<detail::GroundHeatTransferSlabMatlProps_Impl>()->isCPSlabCPDefaulted();
}

bool GroundHeatTransferSlabMatlProps::isCPSoilCPDefaulted() const {
  return getImpl<detail::GroundHeatTransferSlabMatlProps_Impl>()->isCPSoilCPDefaulted();
}

bool GroundHeatTransferSlabMatlProps::isTCONSlabkDefaulted() const {
  return getImpl<detail::GroundHeatTransferSlabMatlProps_Impl>()->isTCONSlabkDefaulted();
}

bool GroundHeatTransferSlabMatlProps::isTCONSoilkDefaulted() const {
  return getImpl<detail::GroundHeatTransferSlabMatlProps_Impl>()->isTCONSoilkDefaulted();
}

bool GroundHeatTransferSlabMatlProps::setRHOSlabMaterialdensity(double rHOSlabMaterialdensity) {
  return getImpl<detail::GroundHeatTransferSlabMatlProps_Impl>()->setRHOSlabMaterialdensity(rHOSlabMaterialdensity);
}

bool GroundHeatTransferSlabMatlProps::setRHOSoilDensity(double rHOSoilDensity) {
  return getImpl<detail::GroundHeatTransferSlabMatlProps_Impl>()->setRHOSoilDensity(rHOSoilDensity);
}

bool GroundHeatTransferSlabMatlProps::setCPSlabCP(double cPSlabCP) {
  return getImpl<detail::GroundHeatTransferSlabMatlProps_Impl>()->setCPSlabCP(cPSlabCP);
}

bool GroundHeatTransferSlabMatlProps::setCPSoilCP(double cPSoilCP) {
  return getImpl<detail::GroundHeatTransferSlabMatlProps_Impl>()->setCPSoilCP(cPSoilCP);
}

bool GroundHeatTransferSlabMatlProps::setTCONSlabk(double tCONSlabk) {
  return getImpl<detail::GroundHeatTransferSlabMatlProps_Impl>()->setTCONSlabk(tCONSlabk);
}

bool GroundHeatTransferSlabMatlProps::setTCONSoilk(double tCONSoilk) {
  return getImpl<detail::GroundHeatTransferSlabMatlProps_Impl>()->setTCONSoilk(tCONSoilk);
}

void GroundHeatTransferSlabMatlProps::resetRHOSlabMaterialdensity() {
  getImpl<detail::GroundHeatTransferSlabMatlProps_Impl>()->resetRHOSlabMaterialdensity();
}

void GroundHeatTransferSlabMatlProps::resetRHOSoilDensity() {
  getImpl<detail::GroundHeatTransferSlabMatlProps_Impl>()->resetRHOSoilDensity();
}

void GroundHeatTransferSlabMatlProps::resetCPSlabCP() {
  getImpl<detail::GroundHeatTransferSlabMatlProps_Impl>()->resetCPSlabCP();
}

void GroundHeatTransferSlabMatlProps::resetCPSoilCP() {
  getImpl<detail::GroundHeatTransferSlabMatlProps_Impl>()->resetCPSoilCP();
}

void GroundHeatTransferSlabMatlProps::resetTCONSlabk() {
  getImpl<detail::GroundHeatTransferSlabMatlProps_Impl>()->resetTCONSlabk();
}

void GroundHeatTransferSlabMatlProps::resetTCONSoilk() {
  getImpl<detail::GroundHeatTransferSlabMatlProps_Impl>()->resetTCONSoilk();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double GroundHeatTransferSlabMatlProps_Impl::rHOSlabMaterialdensity() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_MatlPropsFields::RHO_SlabMaterialdensity, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferSlabMatlProps_Impl::rHOSoilDensity() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_MatlPropsFields::RHO_SoilDensity, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferSlabMatlProps_Impl::cPSlabCP() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_MatlPropsFields::CP_SlabCP, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferSlabMatlProps_Impl::cPSoilCP() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_MatlPropsFields::CP_SoilCP, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferSlabMatlProps_Impl::tCONSlabk() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_MatlPropsFields::TCON_Slabk, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferSlabMatlProps_Impl::tCONSoilk() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_MatlPropsFields::TCON_Soilk, true);
  OS_ASSERT(value);
  return *value;
}

bool GroundHeatTransferSlabMatlProps_Impl::isRHOSlabMaterialdensityDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Slab_MatlPropsFields::RHO_SlabMaterialdensity);
}

bool GroundHeatTransferSlabMatlProps_Impl::isRHOSoilDensityDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Slab_MatlPropsFields::RHO_SoilDensity);
}

bool GroundHeatTransferSlabMatlProps_Impl::isCPSlabCPDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Slab_MatlPropsFields::CP_SlabCP);
}

bool GroundHeatTransferSlabMatlProps_Impl::isCPSoilCPDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Slab_MatlPropsFields::CP_SoilCP);
}

bool GroundHeatTransferSlabMatlProps_Impl::isTCONSlabkDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Slab_MatlPropsFields::TCON_Slabk);
}

bool GroundHeatTransferSlabMatlProps_Impl::isTCONSoilkDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Slab_MatlPropsFields::TCON_Soilk);
}

bool GroundHeatTransferSlabMatlProps_Impl::setRHOSlabMaterialdensity(double rHOSlabMaterialdensity) {
  return setDouble(openstudio::GroundHeatTransfer_Slab_MatlPropsFields::RHO_SlabMaterialdensity, rHOSlabMaterialdensity);
}

bool GroundHeatTransferSlabMatlProps_Impl::setRHOSoilDensity(double rHOSoilDensity) {
  return setDouble(openstudio::GroundHeatTransfer_Slab_MatlPropsFields::RHO_SoilDensity, rHOSoilDensity);
}

bool GroundHeatTransferSlabMatlProps_Impl::setCPSlabCP(double cPSlabCP) {
  return setDouble(openstudio::GroundHeatTransfer_Slab_MatlPropsFields::CP_SlabCP, cPSlabCP);
}

bool GroundHeatTransferSlabMatlProps_Impl::setCPSoilCP(double cPSoilCP) {
  return setDouble(openstudio::GroundHeatTransfer_Slab_MatlPropsFields::CP_SoilCP, cPSoilCP);
}

bool GroundHeatTransferSlabMatlProps_Impl::setTCONSlabk(double tCONSlabk) {
  return setDouble(openstudio::GroundHeatTransfer_Slab_MatlPropsFields::TCON_Slabk, tCONSlabk);
}

bool GroundHeatTransferSlabMatlProps_Impl::setTCONSoilk(double tCONSoilk) {
  return setDouble(openstudio::GroundHeatTransfer_Slab_MatlPropsFields::TCON_Soilk, tCONSoilk);
}

void GroundHeatTransferSlabMatlProps_Impl::resetRHOSlabMaterialdensity() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Slab_MatlPropsFields::RHO_SlabMaterialdensity, ""));
}

void GroundHeatTransferSlabMatlProps_Impl::resetRHOSoilDensity() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Slab_MatlPropsFields::RHO_SoilDensity, ""));
}

void GroundHeatTransferSlabMatlProps_Impl::resetCPSlabCP() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Slab_MatlPropsFields::CP_SlabCP, ""));
}

void GroundHeatTransferSlabMatlProps_Impl::resetCPSoilCP() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Slab_MatlPropsFields::CP_SoilCP, ""));
}

void GroundHeatTransferSlabMatlProps_Impl::resetTCONSlabk() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Slab_MatlPropsFields::TCON_Slabk, ""));
}

void GroundHeatTransferSlabMatlProps_Impl::resetTCONSoilk() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Slab_MatlPropsFields::TCON_Soilk, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
