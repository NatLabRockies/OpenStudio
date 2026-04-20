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
      bool setDrapeBeamBeamSolarTransmittanceAtNormalIncidence(double drapeBeamBeamSolarTransmittanceAtNormalIncidence);
      void resetDrapeBeamBeamSolarTransmittanceAtNormalIncidence();

      double frontSideDrapeBeamDiffuseSolarTransmittance() const;
      bool setFrontSideDrapeBeamDiffuseSolarTransmittance(double frontSideDrapeBeamDiffuseSolarTransmittance);

      double backSideDrapeBeamDiffuseSolarTransmittance() const;
      bool setBackSideDrapeBeamDiffuseSolarTransmittance(double backSideDrapeBeamDiffuseSolarTransmittance);

      double frontSideDrapeBeamDiffuseSolarReflectance() const;
      bool setFrontSideDrapeBeamDiffuseSolarReflectance(double frontSideDrapeBeamDiffuseSolarReflectance);

      double backSideDrapeBeamDiffuseSolarReflectance() const;
      bool setBackSideDrapeBeamDiffuseSolarReflectance(double backSideDrapeBeamDiffuseSolarReflectance);

      boost::optional<double> drapeBeamBeamVisibleTransmittance() const;
      bool setDrapeBeamBeamVisibleTransmittance(double drapeBeamBeamVisibleTransmittance);
      void resetDrapeBeamBeamVisibleTransmittance();

      boost::optional<double> drapeBeamDiffuseVisibleTransmittance() const;
      bool setDrapeBeamDiffuseVisibleTransmittance(double drapeBeamDiffuseVisibleTransmittance);
      void resetDrapeBeamDiffuseVisibleTransmittance();

      boost::optional<double> drapeBeamDiffuseVisibleReflectance() const;
      bool setDrapeBeamDiffuseVisibleReflectance(double drapeBeamDiffuseVisibleReflectance);
      void resetDrapeBeamDiffuseVisibleReflectance();

      double drapeMaterialInfraredTransmittance() const;
      bool isDrapeMaterialInfraredTransmittanceDefaulted() const;
      bool setDrapeMaterialInfraredTransmittance(double drapeMaterialInfraredTransmittance);
      void resetDrapeMaterialInfraredTransmittance();

      double frontSideDrapeMaterialInfraredEmissivity() const;
      bool isFrontSideDrapeMaterialInfraredEmissivityDefaulted() const;
      bool setFrontSideDrapeMaterialInfraredEmissivity(double frontSideDrapeMaterialInfraredEmissivity);
      void resetFrontSideDrapeMaterialInfraredEmissivity();

      double backSideDrapeMaterialInfraredEmissivity() const;
      bool isBackSideDrapeMaterialInfraredEmissivityDefaulted() const;
      bool setBackSideDrapeMaterialInfraredEmissivity(double backSideDrapeMaterialInfraredEmissivity);
      void resetBackSideDrapeMaterialInfraredEmissivity();

      double widthOfPleatedFabric() const;
      bool isWidthOfPleatedFabricDefaulted() const;
      bool setWidthOfPleatedFabric(double widthOfPleatedFabric);
      void resetWidthOfPleatedFabric();

      double lengthOfPleatedFabric() const;
      bool isLengthOfPleatedFabricDefaulted() const;
      bool setLengthOfPleatedFabric(double lengthOfPleatedFabric);
      void resetLengthOfPleatedFabric();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
