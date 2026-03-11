/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWMATERIALDRAPEEQUIVALENTLAYER_IMPL_HPP
#define EPMODEL_WINDOWMATERIALDRAPEEQUIVALENTLAYER_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API WindowMaterialDrapeEquivalentLayer_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~WindowMaterialDrapeEquivalentLayer_Impl() override = default;

      double drapeBeamBeamSolarTransmittanceAtNormalIncidence() const;
      bool isDrapeBeamBeamSolarTransmittanceAtNormalIncidenceDefaulted() const;

      double frontSideDrapeBeamDiffuseSolarTransmittance() const;
      double backSideDrapeBeamDiffuseSolarTransmittance() const;
      double frontSideDrapeBeamDiffuseSolarReflectance() const;
      double backSideDrapeBeamDiffuseSolarReflectance() const;

      boost::optional<double> drapeBeamBeamVisibleTransmittance() const;
      boost::optional<double> drapeBeamDiffuseVisibleTransmittance() const;
      boost::optional<double> drapeBeamDiffuseVisibleReflectance() const;

      double drapeMaterialInfraredTransmittance() const;
      bool isDrapeMaterialInfraredTransmittanceDefaulted() const;

      double frontSideDrapeMaterialInfraredEmissivity() const;
      bool isFrontSideDrapeMaterialInfraredEmissivityDefaulted() const;

      double backSideDrapeMaterialInfraredEmissivity() const;
      bool isBackSideDrapeMaterialInfraredEmissivityDefaulted() const;

      double widthOfPleatedFabric() const;
      bool isWidthOfPleatedFabricDefaulted() const;

      double lengthOfPleatedFabric() const;
      bool isLengthOfPleatedFabricDefaulted() const;

      bool setDrapeBeamBeamSolarTransmittanceAtNormalIncidence(double drapeBeamBeamSolarTransmittanceAtNormalIncidence);
      bool setFrontSideDrapeBeamDiffuseSolarTransmittance(double frontSideDrapeBeamDiffuseSolarTransmittance);
      bool setBackSideDrapeBeamDiffuseSolarTransmittance(double backSideDrapeBeamDiffuseSolarTransmittance);
      bool setFrontSideDrapeBeamDiffuseSolarReflectance(double frontSideDrapeBeamDiffuseSolarReflectance);
      bool setBackSideDrapeBeamDiffuseSolarReflectance(double backSideDrapeBeamDiffuseSolarReflectance);
      bool setDrapeBeamBeamVisibleTransmittance(double drapeBeamBeamVisibleTransmittance);
      bool setDrapeBeamDiffuseVisibleTransmittance(double drapeBeamDiffuseVisibleTransmittance);
      bool setDrapeBeamDiffuseVisibleReflectance(double drapeBeamDiffuseVisibleReflectance);
      bool setDrapeMaterialInfraredTransmittance(double drapeMaterialInfraredTransmittance);
      bool setFrontSideDrapeMaterialInfraredEmissivity(double frontSideDrapeMaterialInfraredEmissivity);
      bool setBackSideDrapeMaterialInfraredEmissivity(double backSideDrapeMaterialInfraredEmissivity);
      bool setWidthOfPleatedFabric(double widthOfPleatedFabric);
      bool setLengthOfPleatedFabric(double lengthOfPleatedFabric);

      void resetDrapeBeamBeamSolarTransmittanceAtNormalIncidence();
      void resetDrapeBeamBeamVisibleTransmittance();
      void resetDrapeBeamDiffuseVisibleTransmittance();
      void resetDrapeBeamDiffuseVisibleReflectance();
      void resetDrapeMaterialInfraredTransmittance();
      void resetFrontSideDrapeMaterialInfraredEmissivity();
      void resetBackSideDrapeMaterialInfraredEmissivity();
      void resetWidthOfPleatedFabric();
      void resetLengthOfPleatedFabric();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
