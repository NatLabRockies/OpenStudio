/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWMATERIALSHADEEQUIVALENTLAYER_IMPL_HPP
#define EPMODEL_WINDOWMATERIALSHADEEQUIVALENTLAYER_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API WindowMaterialShadeEquivalentLayer_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~WindowMaterialShadeEquivalentLayer_Impl() override = default;

      double shadeBeamBeamSolarTransmittance() const;
      bool isShadeBeamBeamSolarTransmittanceDefaulted() const;
      bool setShadeBeamBeamSolarTransmittance(double shadeBeamBeamSolarTransmittance);
      void resetShadeBeamBeamSolarTransmittance();

      double frontSideShadeBeamDiffuseSolarTransmittance() const;
      bool setFrontSideShadeBeamDiffuseSolarTransmittance(double frontSideShadeBeamDiffuseSolarTransmittance);
      double backSideShadeBeamDiffuseSolarTransmittance() const;
      bool setBackSideShadeBeamDiffuseSolarTransmittance(double backSideShadeBeamDiffuseSolarTransmittance);
      double frontSideShadeBeamDiffuseSolarReflectance() const;
      bool setFrontSideShadeBeamDiffuseSolarReflectance(double frontSideShadeBeamDiffuseSolarReflectance);
      double backSideShadeBeamDiffuseSolarReflectance() const;
      bool setBackSideShadeBeamDiffuseSolarReflectance(double backSideShadeBeamDiffuseSolarReflectance);

      boost::optional<double> shadeBeamBeamVisibleTransmittanceAtNormalIncidence() const;
      bool setShadeBeamBeamVisibleTransmittanceAtNormalIncidence(double shadeBeamBeamVisibleTransmittanceAtNormalIncidence);
      boost::optional<double> shadeBeamDiffuseVisibleTransmittanceAtNormalIncidence() const;
      bool setShadeBeamDiffuseVisibleTransmittanceAtNormalIncidence(double shadeBeamDiffuseVisibleTransmittanceAtNormalIncidence);
      boost::optional<double> shadeBeamDiffuseVisibleReflectanceAtNormalIncidence() const;
      bool setShadeBeamDiffuseVisibleReflectanceAtNormalIncidence(double shadeBeamDiffuseVisibleReflectanceAtNormalIncidence);

      double shadeMaterialInfraredTransmittance() const;
      bool isShadeMaterialInfraredTransmittanceDefaulted() const;
      bool setShadeMaterialInfraredTransmittance(double shadeMaterialInfraredTransmittance);
      void resetShadeMaterialInfraredTransmittance();

      double frontSideShadeMaterialInfraredEmissivity() const;
      bool isFrontSideShadeMaterialInfraredEmissivityDefaulted() const;
      bool setFrontSideShadeMaterialInfraredEmissivity(double frontSideShadeMaterialInfraredEmissivity);
      void resetFrontSideShadeMaterialInfraredEmissivity();

      double backSideShadeMaterialInfraredEmissivity() const;
      bool isBackSideShadeMaterialInfraredEmissivityDefaulted() const;
      bool setBackSideShadeMaterialInfraredEmissivity(double backSideShadeMaterialInfraredEmissivity);
      void resetBackSideShadeMaterialInfraredEmissivity();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
