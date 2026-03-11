/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWMATERIALCOMPLEXSHADE_IMPL_HPP
#define EPMODEL_WINDOWMATERIALCOMPLEXSHADE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API WindowMaterialComplexShade_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~WindowMaterialComplexShade_Impl() override = default;

      std::string layerType() const;
      bool isLayerTypeDefaulted() const;

      double thickness() const;
      bool isThicknessDefaulted() const;

      double conductivity() const;
      bool isConductivityDefaulted() const;

      double irTransmittance() const;
      bool isIrTransmittanceDefaulted() const;

      double frontEmissivity() const;
      bool isFrontEmissivityDefaulted() const;

      double backEmissivity() const;
      bool isBackEmissivityDefaulted() const;

      double topOpeningMultiplier() const;
      bool isTopOpeningMultiplierDefaulted() const;

      double bottomOpeningMultiplier() const;
      bool isBottomOpeningMultiplierDefaulted() const;

      double leftSideOpeningMultiplier() const;
      bool isLeftSideOpeningMultiplierDefaulted() const;

      double rightSideOpeningMultiplier() const;
      bool isRightSideOpeningMultiplierDefaulted() const;

      double frontOpeningMultiplier() const;
      bool isFrontOpeningMultiplierDefaulted() const;

      double slatWidth() const;
      bool isSlatWidthDefaulted() const;

      double slatSpacing() const;
      bool isSlatSpacingDefaulted() const;

      double slatThickness() const;
      bool isSlatThicknessDefaulted() const;

      double slatAngle() const;
      bool isSlatAngleDefaulted() const;

      double slatConductivity() const;
      bool isSlatConductivityDefaulted() const;

      double slatCurve() const;
      bool isSlatCurveDefaulted() const;

      bool setLayerType(const std::string& layerType);
      bool setThickness(double thickness);
      bool setConductivity(double conductivity);
      bool setIrTransmittance(double irTransmittance);
      bool setFrontEmissivity(double frontEmissivity);
      bool setBackEmissivity(double backEmissivity);
      bool setTopOpeningMultiplier(double topOpeningMultiplier);
      bool setBottomOpeningMultiplier(double bottomOpeningMultiplier);
      bool setLeftSideOpeningMultiplier(double leftSideOpeningMultiplier);
      bool setRightSideOpeningMultiplier(double rightSideOpeningMultiplier);
      bool setFrontOpeningMultiplier(double frontOpeningMultiplier);
      bool setSlatWidth(double slatWidth);
      bool setSlatSpacing(double slatSpacing);
      bool setSlatThickness(double slatThickness);
      bool setSlatAngle(double slatAngle);
      bool setSlatConductivity(double slatConductivity);
      bool setSlatCurve(double slatCurve);

      void resetLayerType();
      void resetThickness();
      void resetConductivity();
      void resetIrTransmittance();
      void resetFrontEmissivity();
      void resetBackEmissivity();
      void resetTopOpeningMultiplier();
      void resetBottomOpeningMultiplier();
      void resetLeftSideOpeningMultiplier();
      void resetRightSideOpeningMultiplier();
      void resetFrontOpeningMultiplier();
      void resetSlatWidth();
      void resetSlatSpacing();
      void resetSlatThickness();
      void resetSlatAngle();
      void resetSlatConductivity();
      void resetSlatCurve();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
