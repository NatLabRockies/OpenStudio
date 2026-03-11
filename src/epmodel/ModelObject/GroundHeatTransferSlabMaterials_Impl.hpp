/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERSLABMATERIALS_IMPL_HPP
#define EPMODEL_GROUNDHEATTRANSFERSLABMATERIALS_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API GroundHeatTransferSlabMaterials_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~GroundHeatTransferSlabMaterials_Impl() override = default;

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
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
