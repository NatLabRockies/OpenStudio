/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERSLABMATERIALS_HPP
#define EPMODEL_GROUNDHEATTRANSFERSLABMATERIALS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class GroundHeatTransferSlabMaterials_Impl;
}

class EPMODEL_API GroundHeatTransferSlabMaterials : public ModelObject
{
 public:
  explicit GroundHeatTransferSlabMaterials(const Model& model);

  virtual ~GroundHeatTransferSlabMaterials() override = default;
  GroundHeatTransferSlabMaterials(const GroundHeatTransferSlabMaterials& other) = default;
  GroundHeatTransferSlabMaterials(GroundHeatTransferSlabMaterials&& other) = default;
  GroundHeatTransferSlabMaterials& operator=(const GroundHeatTransferSlabMaterials&) = default;
  GroundHeatTransferSlabMaterials& operator=(GroundHeatTransferSlabMaterials&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to GroundHeatTransfer:Slab:Materials N1-N9 fields.
  // - TODO(parity): Add relationship APIs incrementally if future schema revisions introduce link fields.
  double nMATNumberofmaterials() const;
  double aLBEDOSurfaceAlbedoNoSnow() const;
  double aLBEDOSurfaceAlbedoSnow() const;
  double ePSLWSurfaceEmissivityNoSnow() const;
  double ePSLWSurfaceEmissivitySnow() const;
  double z0SurfaceRoughnessNoSnow() const;
  double z0SurfaceRoughnessSnow() const;
  double hINIndoorHConvDownwardFlow() const;
  double hINIndoorHConvUpward() const;

  bool isALBEDOSurfaceAlbedoNoSnowDefaulted() const;
  bool isALBEDOSurfaceAlbedoSnowDefaulted() const;
  bool isEPSLWSurfaceEmissivityNoSnowDefaulted() const;
  bool isEPSLWSurfaceEmissivitySnowDefaulted() const;
  bool isZ0SurfaceRoughnessNoSnowDefaulted() const;
  bool isZ0SurfaceRoughnessSnowDefaulted() const;
  bool isHINIndoorHConvDownwardFlowDefaulted() const;
  bool isHINIndoorHConvUpwardDefaulted() const;

  bool setNMATNumberofmaterials(double nMATNumberofmaterials);
  bool setALBEDOSurfaceAlbedoNoSnow(double aLBEDOSurfaceAlbedoNoSnow);
  bool setALBEDOSurfaceAlbedoSnow(double aLBEDOSurfaceAlbedoSnow);
  bool setEPSLWSurfaceEmissivityNoSnow(double ePSLWSurfaceEmissivityNoSnow);
  bool setEPSLWSurfaceEmissivitySnow(double ePSLWSurfaceEmissivitySnow);
  bool setZ0SurfaceRoughnessNoSnow(double z0SurfaceRoughnessNoSnow);
  bool setZ0SurfaceRoughnessSnow(double z0SurfaceRoughnessSnow);
  bool setHINIndoorHConvDownwardFlow(double hINIndoorHConvDownwardFlow);
  bool setHINIndoorHConvUpward(double hINIndoorHConvUpward);

  void resetALBEDOSurfaceAlbedoNoSnow();
  void resetALBEDOSurfaceAlbedoSnow();
  void resetEPSLWSurfaceEmissivityNoSnow();
  void resetEPSLWSurfaceEmissivitySnow();
  void resetZ0SurfaceRoughnessNoSnow();
  void resetZ0SurfaceRoughnessSnow();
  void resetHINIndoorHConvDownwardFlow();
  void resetHINIndoorHConvUpward();

 protected:
  using ImplType = detail::GroundHeatTransferSlabMaterials_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit GroundHeatTransferSlabMaterials(std::shared_ptr<detail::GroundHeatTransferSlabMaterials_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
