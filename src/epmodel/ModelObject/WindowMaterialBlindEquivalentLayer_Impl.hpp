/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWMATERIALBLINDEQUIVALENTLAYER_IMPL_HPP
#define EPMODEL_WINDOWMATERIALBLINDEQUIVALENTLAYER_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API WindowMaterialBlindEquivalentLayer_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~WindowMaterialBlindEquivalentLayer_Impl() override = default;

      std::string slatOrientation() const;
      bool isSlatOrientationDefaulted() const;

      double slatWidth() const;
      double slatSeparation() const;

      double slatCrown() const;
      bool isSlatCrownDefaulted() const;

      double slatAngle() const;
      bool isSlatAngleDefaulted() const;

      double frontSideSlatBeamDiffuseSolarTransmittance() const;
      bool isFrontSideSlatBeamDiffuseSolarTransmittanceDefaulted() const;

      double backSideSlatBeamDiffuseSolarTransmittance() const;
      bool isBackSideSlatBeamDiffuseSolarTransmittanceDefaulted() const;

      double frontSideSlatBeamDiffuseSolarReflectance() const;
      double backSideSlatBeamDiffuseSolarReflectance() const;

      double frontSideSlatBeamDiffuseVisibleTransmittance() const;
      bool isFrontSideSlatBeamDiffuseVisibleTransmittanceDefaulted() const;

      double backSideSlatBeamDiffuseVisibleTransmittance() const;
      bool isBackSideSlatBeamDiffuseVisibleTransmittanceDefaulted() const;

      boost::optional<double> frontSideSlatBeamDiffuseVisibleReflectance() const;
      boost::optional<double> backSideSlatBeamDiffuseVisibleReflectance() const;

      double slatDiffuseDiffuseSolarTransmittance() const;
      bool isSlatDiffuseDiffuseSolarTransmittanceDefaulted() const;

      double frontSideSlatDiffuseDiffuseSolarReflectance() const;
      double backSideSlatDiffuseDiffuseSolarReflectance() const;

      boost::optional<double> slatDiffuseDiffuseVisibleTransmittance() const;
      boost::optional<double> frontSideSlatDiffuseDiffuseVisibleReflectance() const;
      boost::optional<double> backSideSlatDiffuseDiffuseVisibleReflectance() const;

      double slatInfraredTransmittance() const;
      bool isSlatInfraredTransmittanceDefaulted() const;

      double frontSideSlatInfraredEmissivity() const;
      bool isFrontSideSlatInfraredEmissivityDefaulted() const;

      double backSideSlatInfraredEmissivity() const;
      bool isBackSideSlatInfraredEmissivityDefaulted() const;

      std::string slatAngleControl() const;
      bool isSlatAngleControlDefaulted() const;

      bool setSlatOrientation(const std::string& slatOrientation);
      bool setSlatWidth(double slatWidth);
      bool setSlatSeparation(double slatSeparation);
      bool setSlatCrown(double slatCrown);
      bool setSlatAngle(double slatAngle);
      bool setFrontSideSlatBeamDiffuseSolarTransmittance(double frontSideSlatBeamDiffuseSolarTransmittance);
      bool setBackSideSlatBeamDiffuseSolarTransmittance(double backSideSlatBeamDiffuseSolarTransmittance);
      bool setFrontSideSlatBeamDiffuseSolarReflectance(double frontSideSlatBeamDiffuseSolarReflectance);
      bool setBackSideSlatBeamDiffuseSolarReflectance(double backSideSlatBeamDiffuseSolarReflectance);
      bool setFrontSideSlatBeamDiffuseVisibleTransmittance(double frontSideSlatBeamDiffuseVisibleTransmittance);
      bool setBackSideSlatBeamDiffuseVisibleTransmittance(double backSideSlatBeamDiffuseVisibleTransmittance);
      bool setFrontSideSlatBeamDiffuseVisibleReflectance(double frontSideSlatBeamDiffuseVisibleReflectance);
      bool setBackSideSlatBeamDiffuseVisibleReflectance(double backSideSlatBeamDiffuseVisibleReflectance);
      bool setSlatDiffuseDiffuseSolarTransmittance(double slatDiffuseDiffuseSolarTransmittance);
      bool setFrontSideSlatDiffuseDiffuseSolarReflectance(double frontSideSlatDiffuseDiffuseSolarReflectance);
      bool setBackSideSlatDiffuseDiffuseSolarReflectance(double backSideSlatDiffuseDiffuseSolarReflectance);
      bool setSlatDiffuseDiffuseVisibleTransmittance(double slatDiffuseDiffuseVisibleTransmittance);
      bool setFrontSideSlatDiffuseDiffuseVisibleReflectance(double frontSideSlatDiffuseDiffuseVisibleReflectance);
      bool setBackSideSlatDiffuseDiffuseVisibleReflectance(double backSideSlatDiffuseDiffuseVisibleReflectance);
      bool setSlatInfraredTransmittance(double slatInfraredTransmittance);
      bool setFrontSideSlatInfraredEmissivity(double frontSideSlatInfraredEmissivity);
      bool setBackSideSlatInfraredEmissivity(double backSideSlatInfraredEmissivity);
      bool setSlatAngleControl(const std::string& slatAngleControl);

      void resetSlatOrientation();
      void resetSlatCrown();
      void resetSlatAngle();
      void resetFrontSideSlatBeamDiffuseSolarTransmittance();
      void resetBackSideSlatBeamDiffuseSolarTransmittance();
      void resetFrontSideSlatBeamDiffuseVisibleTransmittance();
      void resetBackSideSlatBeamDiffuseVisibleTransmittance();
      void resetFrontSideSlatBeamDiffuseVisibleReflectance();
      void resetBackSideSlatBeamDiffuseVisibleReflectance();
      void resetSlatDiffuseDiffuseSolarTransmittance();
      void resetSlatDiffuseDiffuseVisibleTransmittance();
      void resetFrontSideSlatDiffuseDiffuseVisibleReflectance();
      void resetBackSideSlatDiffuseDiffuseVisibleReflectance();
      void resetSlatInfraredTransmittance();
      void resetFrontSideSlatInfraredEmissivity();
      void resetBackSideSlatInfraredEmissivity();
      void resetSlatAngleControl();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
