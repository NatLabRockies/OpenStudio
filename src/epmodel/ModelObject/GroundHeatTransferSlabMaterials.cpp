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

  bool GroundHeatTransferSlabMaterials::setNMATNumberofmaterials(double nMATNumberofmaterials) {
    return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->setNMATNumberofmaterials(nMATNumberofmaterials);
  }

  double GroundHeatTransferSlabMaterials::aLBEDOSurfaceAlbedoNoSnow() const {
    return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->aLBEDOSurfaceAlbedoNoSnow();
  }

  bool GroundHeatTransferSlabMaterials::isALBEDOSurfaceAlbedoNoSnowDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->isALBEDOSurfaceAlbedoNoSnowDefaulted();
  }

  bool GroundHeatTransferSlabMaterials::setALBEDOSurfaceAlbedoNoSnow(double aLBEDOSurfaceAlbedoNoSnow) {
    return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->setALBEDOSurfaceAlbedoNoSnow(aLBEDOSurfaceAlbedoNoSnow);
  }

  void GroundHeatTransferSlabMaterials::resetALBEDOSurfaceAlbedoNoSnow() {
    getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->resetALBEDOSurfaceAlbedoNoSnow();
  }

  double GroundHeatTransferSlabMaterials::aLBEDOSurfaceAlbedoSnow() const {
    return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->aLBEDOSurfaceAlbedoSnow();
  }

  bool GroundHeatTransferSlabMaterials::isALBEDOSurfaceAlbedoSnowDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->isALBEDOSurfaceAlbedoSnowDefaulted();
  }

  bool GroundHeatTransferSlabMaterials::setALBEDOSurfaceAlbedoSnow(double aLBEDOSurfaceAlbedoSnow) {
    return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->setALBEDOSurfaceAlbedoSnow(aLBEDOSurfaceAlbedoSnow);
  }

  void GroundHeatTransferSlabMaterials::resetALBEDOSurfaceAlbedoSnow() {
    getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->resetALBEDOSurfaceAlbedoSnow();
  }

  double GroundHeatTransferSlabMaterials::ePSLWSurfaceEmissivityNoSnow() const {
    return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->ePSLWSurfaceEmissivityNoSnow();
  }

  bool GroundHeatTransferSlabMaterials::isEPSLWSurfaceEmissivityNoSnowDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->isEPSLWSurfaceEmissivityNoSnowDefaulted();
  }

  bool GroundHeatTransferSlabMaterials::setEPSLWSurfaceEmissivityNoSnow(double ePSLWSurfaceEmissivityNoSnow) {
    return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->setEPSLWSurfaceEmissivityNoSnow(ePSLWSurfaceEmissivityNoSnow);
  }

  void GroundHeatTransferSlabMaterials::resetEPSLWSurfaceEmissivityNoSnow() {
    getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->resetEPSLWSurfaceEmissivityNoSnow();
  }

  double GroundHeatTransferSlabMaterials::ePSLWSurfaceEmissivitySnow() const {
    return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->ePSLWSurfaceEmissivitySnow();
  }

  bool GroundHeatTransferSlabMaterials::isEPSLWSurfaceEmissivitySnowDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->isEPSLWSurfaceEmissivitySnowDefaulted();
  }

  bool GroundHeatTransferSlabMaterials::setEPSLWSurfaceEmissivitySnow(double ePSLWSurfaceEmissivitySnow) {
    return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->setEPSLWSurfaceEmissivitySnow(ePSLWSurfaceEmissivitySnow);
  }

  void GroundHeatTransferSlabMaterials::resetEPSLWSurfaceEmissivitySnow() {
    getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->resetEPSLWSurfaceEmissivitySnow();
  }

  double GroundHeatTransferSlabMaterials::z0SurfaceRoughnessNoSnow() const {
    return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->z0SurfaceRoughnessNoSnow();
  }

  bool GroundHeatTransferSlabMaterials::isZ0SurfaceRoughnessNoSnowDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->isZ0SurfaceRoughnessNoSnowDefaulted();
  }

  bool GroundHeatTransferSlabMaterials::setZ0SurfaceRoughnessNoSnow(double z0SurfaceRoughnessNoSnow) {
    return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->setZ0SurfaceRoughnessNoSnow(z0SurfaceRoughnessNoSnow);
  }

  void GroundHeatTransferSlabMaterials::resetZ0SurfaceRoughnessNoSnow() {
    getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->resetZ0SurfaceRoughnessNoSnow();
  }

  double GroundHeatTransferSlabMaterials::z0SurfaceRoughnessSnow() const {
    return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->z0SurfaceRoughnessSnow();
  }

  bool GroundHeatTransferSlabMaterials::isZ0SurfaceRoughnessSnowDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->isZ0SurfaceRoughnessSnowDefaulted();
  }

  bool GroundHeatTransferSlabMaterials::setZ0SurfaceRoughnessSnow(double z0SurfaceRoughnessSnow) {
    return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->setZ0SurfaceRoughnessSnow(z0SurfaceRoughnessSnow);
  }

  void GroundHeatTransferSlabMaterials::resetZ0SurfaceRoughnessSnow() {
    getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->resetZ0SurfaceRoughnessSnow();
  }

  double GroundHeatTransferSlabMaterials::hINIndoorHConvDownwardFlow() const {
    return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->hINIndoorHConvDownwardFlow();
  }

  bool GroundHeatTransferSlabMaterials::isHINIndoorHConvDownwardFlowDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->isHINIndoorHConvDownwardFlowDefaulted();
  }

  bool GroundHeatTransferSlabMaterials::setHINIndoorHConvDownwardFlow(double hINIndoorHConvDownwardFlow) {
    return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->setHINIndoorHConvDownwardFlow(hINIndoorHConvDownwardFlow);
  }

  void GroundHeatTransferSlabMaterials::resetHINIndoorHConvDownwardFlow() {
    getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->resetHINIndoorHConvDownwardFlow();
  }

  double GroundHeatTransferSlabMaterials::hINIndoorHConvUpward() const {
    return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->hINIndoorHConvUpward();
  }

  bool GroundHeatTransferSlabMaterials::isHINIndoorHConvUpwardDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->isHINIndoorHConvUpwardDefaulted();
  }

  bool GroundHeatTransferSlabMaterials::setHINIndoorHConvUpward(double hINIndoorHConvUpward) {
    return getImpl<detail::GroundHeatTransferSlabMaterials_Impl>()->setHINIndoorHConvUpward(hINIndoorHConvUpward);
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

    bool GroundHeatTransferSlabMaterials_Impl::setNMATNumberofmaterials(double nMATNumberofmaterials) {
      return setDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::NMAT_Numberofmaterials, nMATNumberofmaterials);
    }

    double GroundHeatTransferSlabMaterials_Impl::aLBEDOSurfaceAlbedoNoSnow() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::ALBEDO_SurfaceAlbedo_NoSnow, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabMaterials_Impl::isALBEDOSurfaceAlbedoNoSnowDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_MaterialsFields::ALBEDO_SurfaceAlbedo_NoSnow);
    }

    bool GroundHeatTransferSlabMaterials_Impl::setALBEDOSurfaceAlbedoNoSnow(double aLBEDOSurfaceAlbedoNoSnow) {
      return setDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::ALBEDO_SurfaceAlbedo_NoSnow, aLBEDOSurfaceAlbedoNoSnow);
    }

    void GroundHeatTransferSlabMaterials_Impl::resetALBEDOSurfaceAlbedoNoSnow() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Slab_MaterialsFields::ALBEDO_SurfaceAlbedo_NoSnow, ""));
    }

    double GroundHeatTransferSlabMaterials_Impl::aLBEDOSurfaceAlbedoSnow() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::ALBEDO_SurfaceAlbedo_Snow, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabMaterials_Impl::isALBEDOSurfaceAlbedoSnowDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_MaterialsFields::ALBEDO_SurfaceAlbedo_Snow);
    }

    bool GroundHeatTransferSlabMaterials_Impl::setALBEDOSurfaceAlbedoSnow(double aLBEDOSurfaceAlbedoSnow) {
      return setDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::ALBEDO_SurfaceAlbedo_Snow, aLBEDOSurfaceAlbedoSnow);
    }

    void GroundHeatTransferSlabMaterials_Impl::resetALBEDOSurfaceAlbedoSnow() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Slab_MaterialsFields::ALBEDO_SurfaceAlbedo_Snow, ""));
    }

    double GroundHeatTransferSlabMaterials_Impl::ePSLWSurfaceEmissivityNoSnow() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::EPSLW_SurfaceEmissivity_NoSnow, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabMaterials_Impl::isEPSLWSurfaceEmissivityNoSnowDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_MaterialsFields::EPSLW_SurfaceEmissivity_NoSnow);
    }

    bool GroundHeatTransferSlabMaterials_Impl::setEPSLWSurfaceEmissivityNoSnow(double ePSLWSurfaceEmissivityNoSnow) {
      return setDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::EPSLW_SurfaceEmissivity_NoSnow, ePSLWSurfaceEmissivityNoSnow);
    }

    void GroundHeatTransferSlabMaterials_Impl::resetEPSLWSurfaceEmissivityNoSnow() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Slab_MaterialsFields::EPSLW_SurfaceEmissivity_NoSnow, ""));
    }

    double GroundHeatTransferSlabMaterials_Impl::ePSLWSurfaceEmissivitySnow() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::EPSLW_SurfaceEmissivity_Snow, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabMaterials_Impl::isEPSLWSurfaceEmissivitySnowDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_MaterialsFields::EPSLW_SurfaceEmissivity_Snow);
    }

    bool GroundHeatTransferSlabMaterials_Impl::setEPSLWSurfaceEmissivitySnow(double ePSLWSurfaceEmissivitySnow) {
      return setDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::EPSLW_SurfaceEmissivity_Snow, ePSLWSurfaceEmissivitySnow);
    }

    void GroundHeatTransferSlabMaterials_Impl::resetEPSLWSurfaceEmissivitySnow() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Slab_MaterialsFields::EPSLW_SurfaceEmissivity_Snow, ""));
    }

    double GroundHeatTransferSlabMaterials_Impl::z0SurfaceRoughnessNoSnow() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::Z0_SurfaceRoughness_NoSnow, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabMaterials_Impl::isZ0SurfaceRoughnessNoSnowDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_MaterialsFields::Z0_SurfaceRoughness_NoSnow);
    }

    bool GroundHeatTransferSlabMaterials_Impl::setZ0SurfaceRoughnessNoSnow(double z0SurfaceRoughnessNoSnow) {
      return setDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::Z0_SurfaceRoughness_NoSnow, z0SurfaceRoughnessNoSnow);
    }

    void GroundHeatTransferSlabMaterials_Impl::resetZ0SurfaceRoughnessNoSnow() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Slab_MaterialsFields::Z0_SurfaceRoughness_NoSnow, ""));
    }

    double GroundHeatTransferSlabMaterials_Impl::z0SurfaceRoughnessSnow() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::Z0_SurfaceRoughness_Snow, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabMaterials_Impl::isZ0SurfaceRoughnessSnowDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_MaterialsFields::Z0_SurfaceRoughness_Snow);
    }

    bool GroundHeatTransferSlabMaterials_Impl::setZ0SurfaceRoughnessSnow(double z0SurfaceRoughnessSnow) {
      return setDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::Z0_SurfaceRoughness_Snow, z0SurfaceRoughnessSnow);
    }

    void GroundHeatTransferSlabMaterials_Impl::resetZ0SurfaceRoughnessSnow() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Slab_MaterialsFields::Z0_SurfaceRoughness_Snow, ""));
    }

    double GroundHeatTransferSlabMaterials_Impl::hINIndoorHConvDownwardFlow() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::HIN_IndoorHConv_DownwardFlow, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabMaterials_Impl::isHINIndoorHConvDownwardFlowDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_MaterialsFields::HIN_IndoorHConv_DownwardFlow);
    }

    bool GroundHeatTransferSlabMaterials_Impl::setHINIndoorHConvDownwardFlow(double hINIndoorHConvDownwardFlow) {
      return setDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::HIN_IndoorHConv_DownwardFlow, hINIndoorHConvDownwardFlow);
    }

    void GroundHeatTransferSlabMaterials_Impl::resetHINIndoorHConvDownwardFlow() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Slab_MaterialsFields::HIN_IndoorHConv_DownwardFlow, ""));
    }

    double GroundHeatTransferSlabMaterials_Impl::hINIndoorHConvUpward() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::HIN_IndoorHConv_Upward, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabMaterials_Impl::isHINIndoorHConvUpwardDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_MaterialsFields::HIN_IndoorHConv_Upward);
    }

    bool GroundHeatTransferSlabMaterials_Impl::setHINIndoorHConvUpward(double hINIndoorHConvUpward) {
      return setDouble(openstudio::GroundHeatTransfer_Slab_MaterialsFields::HIN_IndoorHConv_Upward, hINIndoorHConvUpward);
    }

    void GroundHeatTransferSlabMaterials_Impl::resetHINIndoorHConvUpward() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Slab_MaterialsFields::HIN_IndoorHConv_Upward, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
