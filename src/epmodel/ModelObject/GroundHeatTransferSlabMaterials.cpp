/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatTransferSlabMaterials.hpp"
#include "GroundHeatTransferSlabMaterials_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GroundHeatTransfer_Slab_Materials_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

GroundHeatTransferSlabMaterials::GroundHeatTransferSlabMaterials(const Model& model)
  : ModelObject(GroundHeatTransferSlabMaterials::iddObjectType(), model) {}

GroundHeatTransferSlabMaterials::GroundHeatTransferSlabMaterials(std::shared_ptr<detail::GroundHeatTransferSlabMaterials_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType GroundHeatTransferSlabMaterials::iddObjectType() {
  return IddObjectType::GroundHeatTransfer_Slab_Materials;
}

double GroundHeatTransferSlabMaterials::nMATNumberofmaterials() const {
  return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->nMATNumberofmaterials();
}

double GroundHeatTransferSlabMaterials::aLBEDOSurfaceAlbedoNoSnow() const {
  return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->aLBEDOSurfaceAlbedoNoSnow();
}

double GroundHeatTransferSlabMaterials::aLBEDOSurfaceAlbedoSnow() const {
  return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->aLBEDOSurfaceAlbedoSnow();
}

double GroundHeatTransferSlabMaterials::ePSLWSurfaceEmissivityNoSnow() const {
  return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->ePSLWSurfaceEmissivityNoSnow();
}

double GroundHeatTransferSlabMaterials::ePSLWSurfaceEmissivitySnow() const {
  return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->ePSLWSurfaceEmissivitySnow();
}

double GroundHeatTransferSlabMaterials::z0SurfaceRoughnessNoSnow() const {
  return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->z0SurfaceRoughnessNoSnow();
}

double GroundHeatTransferSlabMaterials::z0SurfaceRoughnessSnow() const {
  return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->z0SurfaceRoughnessSnow();
}

double GroundHeatTransferSlabMaterials::hINIndoorHConvDownwardFlow() const {
  return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->hINIndoorHConvDownwardFlow();
}

double GroundHeatTransferSlabMaterials::hINIndoorHConvUpward() const {
  return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->hINIndoorHConvUpward();
}

bool GroundHeatTransferSlabMaterials::isALBEDOSurfaceAlbedoNoSnowDefaulted() const {
  return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->isALBEDOSurfaceAlbedoNoSnowDefaulted();
}

bool GroundHeatTransferSlabMaterials::isALBEDOSurfaceAlbedoSnowDefaulted() const {
  return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->isALBEDOSurfaceAlbedoSnowDefaulted();
}

bool GroundHeatTransferSlabMaterials::isEPSLWSurfaceEmissivityNoSnowDefaulted() const {
  return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->isEPSLWSurfaceEmissivityNoSnowDefaulted();
}

bool GroundHeatTransferSlabMaterials::isEPSLWSurfaceEmissivitySnowDefaulted() const {
  return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->isEPSLWSurfaceEmissivitySnowDefaulted();
}

bool GroundHeatTransferSlabMaterials::isZ0SurfaceRoughnessNoSnowDefaulted() const {
  return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->isZ0SurfaceRoughnessNoSnowDefaulted();
}

bool GroundHeatTransferSlabMaterials::isZ0SurfaceRoughnessSnowDefaulted() const {
  return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->isZ0SurfaceRoughnessSnowDefaulted();
}

bool GroundHeatTransferSlabMaterials::isHINIndoorHConvDownwardFlowDefaulted() const {
  return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->isHINIndoorHConvDownwardFlowDefaulted();
}

bool GroundHeatTransferSlabMaterials::isHINIndoorHConvUpwardDefaulted() const {
  return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->isHINIndoorHConvUpwardDefaulted();
}

bool GroundHeatTransferSlabMaterials::setNMATNumberofmaterials(double nMATNumberofmaterials) {
  return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->setNMATNumberofmaterials(nMATNumberofmaterials);
}

bool GroundHeatTransferSlabMaterials::setALBEDOSurfaceAlbedoNoSnow(double aLBEDOSurfaceAlbedoNoSnow) {
  return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->setALBEDOSurfaceAlbedoNoSnow(aLBEDOSurfaceAlbedoNoSnow);
}

bool GroundHeatTransferSlabMaterials::setALBEDOSurfaceAlbedoSnow(double aLBEDOSurfaceAlbedoSnow) {
  return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->setALBEDOSurfaceAlbedoSnow(aLBEDOSurfaceAlbedoSnow);
}

bool GroundHeatTransferSlabMaterials::setEPSLWSurfaceEmissivityNoSnow(double ePSLWSurfaceEmissivityNoSnow) {
  return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->setEPSLWSurfaceEmissivityNoSnow(ePSLWSurfaceEmissivityNoSnow);
}

bool GroundHeatTransferSlabMaterials::setEPSLWSurfaceEmissivitySnow(double ePSLWSurfaceEmissivitySnow) {
  return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->setEPSLWSurfaceEmissivitySnow(ePSLWSurfaceEmissivitySnow);
}

bool GroundHeatTransferSlabMaterials::setZ0SurfaceRoughnessNoSnow(double z0SurfaceRoughnessNoSnow) {
  return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->setZ0SurfaceRoughnessNoSnow(z0SurfaceRoughnessNoSnow);
}

bool GroundHeatTransferSlabMaterials::setZ0SurfaceRoughnessSnow(double z0SurfaceRoughnessSnow) {
  return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->setZ0SurfaceRoughnessSnow(z0SurfaceRoughnessSnow);
}

bool GroundHeatTransferSlabMaterials::setHINIndoorHConvDownwardFlow(double hINIndoorHConvDownwardFlow) {
  return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->setHINIndoorHConvDownwardFlow(hINIndoorHConvDownwardFlow);
}

bool GroundHeatTransferSlabMaterials::setHINIndoorHConvUpward(double hINIndoorHConvUpward) {
  return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->setHINIndoorHConvUpward(hINIndoorHConvUpward);
}

void GroundHeatTransferSlabMaterials::resetALBEDOSurfaceAlbedoNoSnow() {
  getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->resetALBEDOSurfaceAlbedoNoSnow();
}

void GroundHeatTransferSlabMaterials::resetALBEDOSurfaceAlbedoSnow() {
  getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->resetALBEDOSurfaceAlbedoSnow();
}

void GroundHeatTransferSlabMaterials::resetEPSLWSurfaceEmissivityNoSnow() {
  getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->resetEPSLWSurfaceEmissivityNoSnow();
}

void GroundHeatTransferSlabMaterials::resetEPSLWSurfaceEmissivitySnow() {
  getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->resetEPSLWSurfaceEmissivitySnow();
}

void GroundHeatTransferSlabMaterials::resetZ0SurfaceRoughnessNoSnow() {
  getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->resetZ0SurfaceRoughnessNoSnow();
}

void GroundHeatTransferSlabMaterials::resetZ0SurfaceRoughnessSnow() {
  getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->resetZ0SurfaceRoughnessSnow();
}

void GroundHeatTransferSlabMaterials::resetHINIndoorHConvDownwardFlow() {
  getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->resetHINIndoorHConvDownwardFlow();
}

void GroundHeatTransferSlabMaterials::resetHINIndoorHConvUpward() {
  getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->resetHINIndoorHConvUpward();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double GroundHeatTransferSlabMaterials_Impl::nMATNumberofmaterials() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::NMAT_Numberofmaterials, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferSlabMaterials_Impl::aLBEDOSurfaceAlbedoNoSnow() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::ALBEDO_SurfaceAlbedo_NoSnow, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferSlabMaterials_Impl::aLBEDOSurfaceAlbedoSnow() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::ALBEDO_SurfaceAlbedo_Snow, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferSlabMaterials_Impl::ePSLWSurfaceEmissivityNoSnow() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::EPSLW_SurfaceEmissivity_NoSnow, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferSlabMaterials_Impl::ePSLWSurfaceEmissivitySnow() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::EPSLW_SurfaceEmissivity_Snow, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferSlabMaterials_Impl::z0SurfaceRoughnessNoSnow() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::Z0_SurfaceRoughness_NoSnow, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferSlabMaterials_Impl::z0SurfaceRoughnessSnow() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::Z0_SurfaceRoughness_Snow, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferSlabMaterials_Impl::hINIndoorHConvDownwardFlow() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::HIN_IndoorHConv_DownwardFlow, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferSlabMaterials_Impl::hINIndoorHConvUpward() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::HIN_IndoorHConv_Upward, true);
  OS_ASSERT(value);
  return *value;
}

bool GroundHeatTransferSlabMaterials_Impl::isALBEDOSurfaceAlbedoNoSnowDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Slab_MaterialsFields::ALBEDO_SurfaceAlbedo_NoSnow);
}

bool GroundHeatTransferSlabMaterials_Impl::isALBEDOSurfaceAlbedoSnowDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Slab_MaterialsFields::ALBEDO_SurfaceAlbedo_Snow);
}

bool GroundHeatTransferSlabMaterials_Impl::isEPSLWSurfaceEmissivityNoSnowDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Slab_MaterialsFields::EPSLW_SurfaceEmissivity_NoSnow);
}

bool GroundHeatTransferSlabMaterials_Impl::isEPSLWSurfaceEmissivitySnowDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Slab_MaterialsFields::EPSLW_SurfaceEmissivity_Snow);
}

bool GroundHeatTransferSlabMaterials_Impl::isZ0SurfaceRoughnessNoSnowDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Slab_MaterialsFields::Z0_SurfaceRoughness_NoSnow);
}

bool GroundHeatTransferSlabMaterials_Impl::isZ0SurfaceRoughnessSnowDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Slab_MaterialsFields::Z0_SurfaceRoughness_Snow);
}

bool GroundHeatTransferSlabMaterials_Impl::isHINIndoorHConvDownwardFlowDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Slab_MaterialsFields::HIN_IndoorHConv_DownwardFlow);
}

bool GroundHeatTransferSlabMaterials_Impl::isHINIndoorHConvUpwardDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Slab_MaterialsFields::HIN_IndoorHConv_Upward);
}

bool GroundHeatTransferSlabMaterials_Impl::setNMATNumberofmaterials(double nMATNumberofmaterials) {
  return setDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::NMAT_Numberofmaterials, nMATNumberofmaterials);
}

bool GroundHeatTransferSlabMaterials_Impl::setALBEDOSurfaceAlbedoNoSnow(double aLBEDOSurfaceAlbedoNoSnow) {
  return setDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::ALBEDO_SurfaceAlbedo_NoSnow, aLBEDOSurfaceAlbedoNoSnow);
}

bool GroundHeatTransferSlabMaterials_Impl::setALBEDOSurfaceAlbedoSnow(double aLBEDOSurfaceAlbedoSnow) {
  return setDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::ALBEDO_SurfaceAlbedo_Snow, aLBEDOSurfaceAlbedoSnow);
}

bool GroundHeatTransferSlabMaterials_Impl::setEPSLWSurfaceEmissivityNoSnow(double ePSLWSurfaceEmissivityNoSnow) {
  return setDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::EPSLW_SurfaceEmissivity_NoSnow, ePSLWSurfaceEmissivityNoSnow);
}

bool GroundHeatTransferSlabMaterials_Impl::setEPSLWSurfaceEmissivitySnow(double ePSLWSurfaceEmissivitySnow) {
  return setDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::EPSLW_SurfaceEmissivity_Snow, ePSLWSurfaceEmissivitySnow);
}

bool GroundHeatTransferSlabMaterials_Impl::setZ0SurfaceRoughnessNoSnow(double z0SurfaceRoughnessNoSnow) {
  return setDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::Z0_SurfaceRoughness_NoSnow, z0SurfaceRoughnessNoSnow);
}

bool GroundHeatTransferSlabMaterials_Impl::setZ0SurfaceRoughnessSnow(double z0SurfaceRoughnessSnow) {
  return setDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::Z0_SurfaceRoughness_Snow, z0SurfaceRoughnessSnow);
}

bool GroundHeatTransferSlabMaterials_Impl::setHINIndoorHConvDownwardFlow(double hINIndoorHConvDownwardFlow) {
  return setDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::HIN_IndoorHConv_DownwardFlow, hINIndoorHConvDownwardFlow);
}

bool GroundHeatTransferSlabMaterials_Impl::setHINIndoorHConvUpward(double hINIndoorHConvUpward) {
  return setDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::HIN_IndoorHConv_Upward, hINIndoorHConvUpward);
}

void GroundHeatTransferSlabMaterials_Impl::resetALBEDOSurfaceAlbedoNoSnow() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Slab_MaterialsFields::ALBEDO_SurfaceAlbedo_NoSnow, ""));
}

void GroundHeatTransferSlabMaterials_Impl::resetALBEDOSurfaceAlbedoSnow() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Slab_MaterialsFields::ALBEDO_SurfaceAlbedo_Snow, ""));
}

void GroundHeatTransferSlabMaterials_Impl::resetEPSLWSurfaceEmissivityNoSnow() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Slab_MaterialsFields::EPSLW_SurfaceEmissivity_NoSnow, ""));
}

void GroundHeatTransferSlabMaterials_Impl::resetEPSLWSurfaceEmissivitySnow() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Slab_MaterialsFields::EPSLW_SurfaceEmissivity_Snow, ""));
}

void GroundHeatTransferSlabMaterials_Impl::resetZ0SurfaceRoughnessNoSnow() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Slab_MaterialsFields::Z0_SurfaceRoughness_NoSnow, ""));
}

void GroundHeatTransferSlabMaterials_Impl::resetZ0SurfaceRoughnessSnow() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Slab_MaterialsFields::Z0_SurfaceRoughness_Snow, ""));
}

void GroundHeatTransferSlabMaterials_Impl::resetHINIndoorHConvDownwardFlow() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Slab_MaterialsFields::HIN_IndoorHConv_DownwardFlow, ""));
}

void GroundHeatTransferSlabMaterials_Impl::resetHINIndoorHConvUpward() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Slab_MaterialsFields::HIN_IndoorHConv_Upward, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
