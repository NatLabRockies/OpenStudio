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
      bool setNMATNumberofmaterials(double nMATNumberofmaterials);

      double aLBEDOSurfaceAlbedoNoSnow() const;
      bool isALBEDOSurfaceAlbedoNoSnowDefaulted() const;
      bool setALBEDOSurfaceAlbedoNoSnow(double aLBEDOSurfaceAlbedoNoSnow);
      void resetALBEDOSurfaceAlbedoNoSnow();

      double aLBEDOSurfaceAlbedoSnow() const;
      bool isALBEDOSurfaceAlbedoSnowDefaulted() const;
      bool setALBEDOSurfaceAlbedoSnow(double aLBEDOSurfaceAlbedoSnow);
      void resetALBEDOSurfaceAlbedoSnow();

      double ePSLWSurfaceEmissivityNoSnow() const;
      bool isEPSLWSurfaceEmissivityNoSnowDefaulted() const;
      bool setEPSLWSurfaceEmissivityNoSnow(double ePSLWSurfaceEmissivityNoSnow);
      void resetEPSLWSurfaceEmissivityNoSnow();

      double ePSLWSurfaceEmissivitySnow() const;
      bool isEPSLWSurfaceEmissivitySnowDefaulted() const;
      bool setEPSLWSurfaceEmissivitySnow(double ePSLWSurfaceEmissivitySnow);
      void resetEPSLWSurfaceEmissivitySnow();

      double z0SurfaceRoughnessNoSnow() const;
      bool isZ0SurfaceRoughnessNoSnowDefaulted() const;
      bool setZ0SurfaceRoughnessNoSnow(double z0SurfaceRoughnessNoSnow);
      void resetZ0SurfaceRoughnessNoSnow();

      double z0SurfaceRoughnessSnow() const;
      bool isZ0SurfaceRoughnessSnowDefaulted() const;
      bool setZ0SurfaceRoughnessSnow(double z0SurfaceRoughnessSnow);
      void resetZ0SurfaceRoughnessSnow();

      double hINIndoorHConvDownwardFlow() const;
      bool isHINIndoorHConvDownwardFlowDefaulted() const;
      bool setHINIndoorHConvDownwardFlow(double hINIndoorHConvDownwardFlow);
      void resetHINIndoorHConvDownwardFlow();

      double hINIndoorHConvUpward() const;
      bool isHINIndoorHConvUpwardDefaulted() const;
      bool setHINIndoorHConvUpward(double hINIndoorHConvUpward);
      void resetHINIndoorHConvUpward();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
