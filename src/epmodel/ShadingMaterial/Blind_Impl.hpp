/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_BLIND_IMPL_HPP
#define EPMODEL_BLIND_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API Blind_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~Blind_Impl() override = default;

      std::string slatOrientation() const;
      bool setSlatOrientation(const std::string& slatOrientation);
      void resetSlatOrientation();
      bool isSlatOrientationDefaulted() const;

      double slatWidth() const;
      bool setSlatWidth(double slatWidth);

      double slatSeparation() const;
      bool setSlatSeparation(double slatSeparation);

      double slatThickness() const;
      bool setSlatThickness(double slatThickness);
      bool isSlatThicknessDefaulted() const;
      void resetSlatThickness();

      double slatCurve() const;
      bool setSlatCurve(double slatCurve);
      bool isSlatCurveDefaulted() const;
      void resetSlatCurve();

      double slatAngle() const;
      bool setSlatAngle(double slatAngle);
      bool isSlatAngleDefaulted() const;
      void resetSlatAngle();

      double slatConductivity() const;
      bool setSlatConductivity(double slatConductivity);
      bool isSlatConductivityDefaulted() const;
      void resetSlatConductivity();

      double slatBeamSolarTransmittance() const;
      bool setSlatBeamSolarTransmittance(double slatBeamSolarTransmittance);
      bool isSlatBeamSolarTransmittanceDefaulted() const;
      void resetSlatBeamSolarTransmittance();

      double frontSideSlatBeamSolarReflectance() const;
      bool setFrontSideSlatBeamSolarReflectance(double frontSideSlatBeamSolarReflectance);

      double backSideSlatBeamSolarReflectance() const;
      bool setBackSideSlatBeamSolarReflectance(double backSideSlatBeamSolarReflectance);

      double slatDiffuseSolarTransmittance() const;
      bool setSlatDiffuseSolarTransmittance(double slatDiffuseSolarTransmittance);
      bool isSlatDiffuseSolarTransmittanceDefaulted() const;
      void resetSlatDiffuseSolarTransmittance();

      double frontSideSlatDiffuseSolarReflectance() const;
      bool setFrontSideSlatDiffuseSolarReflectance(double frontSideSlatDiffuseSolarReflectance);

      double backSideSlatDiffuseSolarReflectance() const;
      bool setBackSideSlatDiffuseSolarReflectance(double backSideSlatDiffuseSolarReflectance);

      double slatBeamVisibleTransmittance() const;
      bool setSlatBeamVisibleTransmittance(double slatBeamVisibleTransmittance);

      boost::optional<double> frontSideSlatBeamVisibleReflectance() const;
      bool setFrontSideSlatBeamVisibleReflectance(double frontSideSlatBeamVisibleReflectance);
      void resetFrontSideSlatBeamVisibleReflectance();

      boost::optional<double> backSideSlatBeamVisibleReflectance() const;
      bool setBackSideSlatBeamVisibleReflectance(double backSideSlatBeamVisibleReflectance);
      void resetBackSideSlatBeamVisibleReflectance();

      double slatDiffuseVisibleTransmittance() const;
      bool setSlatDiffuseVisibleTransmittance(double slatDiffuseVisibleTransmittance);
      bool isSlatDiffuseVisibleTransmittanceDefaulted() const;
      void resetSlatDiffuseVisibleTransmittance();

      boost::optional<double> frontSideSlatDiffuseVisibleReflectance() const;
      bool setFrontSideSlatDiffuseVisibleReflectance(double frontSideSlatDiffuseVisibleReflectance);
      void resetFrontSideSlatDiffuseVisibleReflectance();

      boost::optional<double> backSideSlatDiffuseVisibleReflectance() const;
      bool setBackSideSlatDiffuseVisibleReflectance(double backSideSlatDiffuseVisibleReflectance);
      void resetBackSideSlatDiffuseVisibleReflectance();

      double slatInfraredHemisphericalTransmittance() const;
      bool setSlatInfraredHemisphericalTransmittance(double slatInfraredHemisphericalTransmittance);
      bool isSlatInfraredHemisphericalTransmittanceDefaulted() const;
      void resetSlatInfraredHemisphericalTransmittance();

      double frontSideSlatInfraredHemisphericalEmissivity() const;
      bool setFrontSideSlatInfraredHemisphericalEmissivity(double frontSideSlatInfraredHemisphericalEmissivity);
      bool isFrontSideSlatInfraredHemisphericalEmissivityDefaulted() const;
      void resetFrontSideSlatInfraredHemisphericalEmissivity();

      double backSideSlatInfraredHemisphericalEmissivity() const;
      bool setBackSideSlatInfraredHemisphericalEmissivity(double backSideSlatInfraredHemisphericalEmissivity);
      bool isBackSideSlatInfraredHemisphericalEmissivityDefaulted() const;
      void resetBackSideSlatInfraredHemisphericalEmissivity();

      double blindtoGlassDistance() const;
      bool setBlindtoGlassDistance(double blindtoGlassDistance);
      bool isBlindtoGlassDistanceDefaulted() const;
      void resetBlindtoGlassDistance();

      double blindTopOpeningMultiplier() const;
      bool setBlindTopOpeningMultiplier(double blindTopOpeningMultiplier);
      bool isBlindTopOpeningMultiplierDefaulted() const;
      void resetBlindTopOpeningMultiplier();

      double blindBottomOpeningMultiplier() const;
      bool setBlindBottomOpeningMultiplier(double blindBottomOpeningMultiplier);
      bool isBlindBottomOpeningMultiplierDefaulted() const;
      void resetBlindBottomOpeningMultiplier();

      double blindLeftSideOpeningMultiplier() const;
      bool setBlindLeftSideOpeningMultiplier(double blindLeftSideOpeningMultiplier);
      bool isBlindLeftSideOpeningMultiplierDefaulted() const;
      void resetBlindLeftSideOpeningMultiplier();

      double blindRightSideOpeningMultiplier() const;
      bool setBlindRightSideOpeningMultiplier(double blindRightSideOpeningMultiplier);
      bool isBlindRightSideOpeningMultiplierDefaulted() const;
      void resetBlindRightSideOpeningMultiplier();

      double minimumSlatAngle() const;
      bool setMinimumSlatAngle(double minimumSlatAngle);
      bool isMinimumSlatAngleDefaulted() const;
      void resetMinimumSlatAngle();

      double maximumSlatAngle() const;
      bool setMaximumSlatAngle(double maximumSlatAngle);
      bool isMaximumSlatAngleDefaulted() const;
      void resetMaximumSlatAngle();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
