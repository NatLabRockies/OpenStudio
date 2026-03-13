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
      bool setLayerType(const std::string& layerType);
      void resetLayerType();

      double thickness() const;
      bool isThicknessDefaulted() const;
      bool setThickness(double thickness);
      void resetThickness();

      double conductivity() const;
      bool isConductivityDefaulted() const;
      bool setConductivity(double conductivity);
      void resetConductivity();

      double irTransmittance() const;
      bool isIrTransmittanceDefaulted() const;
      bool setIrTransmittance(double irTransmittance);
      void resetIrTransmittance();

      double frontEmissivity() const;
      bool isFrontEmissivityDefaulted() const;
      bool setFrontEmissivity(double frontEmissivity);
      void resetFrontEmissivity();

      double backEmissivity() const;
      bool isBackEmissivityDefaulted() const;
      bool setBackEmissivity(double backEmissivity);
      void resetBackEmissivity();

      double topOpeningMultiplier() const;
      bool isTopOpeningMultiplierDefaulted() const;
      bool setTopOpeningMultiplier(double topOpeningMultiplier);
      void resetTopOpeningMultiplier();

      double bottomOpeningMultiplier() const;
      bool isBottomOpeningMultiplierDefaulted() const;
      bool setBottomOpeningMultiplier(double bottomOpeningMultiplier);
      void resetBottomOpeningMultiplier();

      double leftSideOpeningMultiplier() const;
      bool isLeftSideOpeningMultiplierDefaulted() const;
      bool setLeftSideOpeningMultiplier(double leftSideOpeningMultiplier);
      void resetLeftSideOpeningMultiplier();

      double rightSideOpeningMultiplier() const;
      bool isRightSideOpeningMultiplierDefaulted() const;
      bool setRightSideOpeningMultiplier(double rightSideOpeningMultiplier);
      void resetRightSideOpeningMultiplier();

      double frontOpeningMultiplier() const;
      bool isFrontOpeningMultiplierDefaulted() const;
      bool setFrontOpeningMultiplier(double frontOpeningMultiplier);
      void resetFrontOpeningMultiplier();

      double slatWidth() const;
      bool isSlatWidthDefaulted() const;
      bool setSlatWidth(double slatWidth);
      void resetSlatWidth();

      double slatSpacing() const;
      bool isSlatSpacingDefaulted() const;
      bool setSlatSpacing(double slatSpacing);
      void resetSlatSpacing();

      double slatThickness() const;
      bool isSlatThicknessDefaulted() const;
      bool setSlatThickness(double slatThickness);
      void resetSlatThickness();

      double slatAngle() const;
      bool isSlatAngleDefaulted() const;
      bool setSlatAngle(double slatAngle);
      void resetSlatAngle();

      double slatConductivity() const;
      bool isSlatConductivityDefaulted() const;
      bool setSlatConductivity(double slatConductivity);
      void resetSlatConductivity();

      double slatCurve() const;
      bool isSlatCurveDefaulted() const;
      bool setSlatCurve(double slatCurve);
      void resetSlatCurve();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
