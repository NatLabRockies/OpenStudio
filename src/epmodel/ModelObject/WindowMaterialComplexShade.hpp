/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWMATERIALCOMPLEXSHADE_HPP
#define EPMODEL_WINDOWMATERIALCOMPLEXSHADE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class WindowMaterialComplexShade_Impl;
  }

  class EPMODEL_API WindowMaterialComplexShade : public ModelObject
  {
   public:
    explicit WindowMaterialComplexShade(const Model& model);

    virtual ~WindowMaterialComplexShade() override = default;
    WindowMaterialComplexShade(const WindowMaterialComplexShade& other) = default;
    WindowMaterialComplexShade(WindowMaterialComplexShade&& other) = default;
    WindowMaterialComplexShade& operator=(const WindowMaterialComplexShade&) = default;
    WindowMaterialComplexShade& operator=(WindowMaterialComplexShade&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> layerTypeValues();

    // Schema Alignment Notes:
    // - API/Field Mapping: WindowMaterialComplexShade exposes the scalar optics and thermal properties defined by WindowMaterial:ComplexShade via WindowMaterial_ComplexShadeFields.
    // - API/Field Mapping: Layer type and numeric thermophysical scalars follow the EnergyPlus defaults to mirror translator evidence once available.
    // - TODO(parity): Wire ForwardTranslator evidence to confirm these mappings once the translator has coverage.

    /** @name Layer type */
    //@{
    std::string layerType() const;
    bool isLayerTypeDefaulted() const;
    bool setLayerType(const std::string& layerType);
    void resetLayerType();
    //@}

    /** @name Thickness */
    //@{
    double thickness() const;
    bool isThicknessDefaulted() const;
    bool setThickness(double thickness);
    void resetThickness();
    //@}

    /** @name Conductivity */
    //@{
    double conductivity() const;
    bool isConductivityDefaulted() const;
    bool setConductivity(double conductivity);
    void resetConductivity();
    //@}

    /** @name IR transmittance */
    //@{
    double irTransmittance() const;
    bool isIrTransmittanceDefaulted() const;
    bool setIrTransmittance(double irTransmittance);
    void resetIrTransmittance();
    //@}

    /** @name Front emissivity */
    //@{
    double frontEmissivity() const;
    bool isFrontEmissivityDefaulted() const;
    bool setFrontEmissivity(double frontEmissivity);
    void resetFrontEmissivity();
    //@}

    /** @name Back emissivity */
    //@{
    double backEmissivity() const;
    bool isBackEmissivityDefaulted() const;
    bool setBackEmissivity(double backEmissivity);
    void resetBackEmissivity();
    //@}

    /** @name Top opening multiplier */
    //@{
    double topOpeningMultiplier() const;
    bool isTopOpeningMultiplierDefaulted() const;
    bool setTopOpeningMultiplier(double topOpeningMultiplier);
    void resetTopOpeningMultiplier();
    //@}

    /** @name Bottom opening multiplier */
    //@{
    double bottomOpeningMultiplier() const;
    bool isBottomOpeningMultiplierDefaulted() const;
    bool setBottomOpeningMultiplier(double bottomOpeningMultiplier);
    void resetBottomOpeningMultiplier();
    //@}

    /** @name Left side opening multiplier */
    //@{
    double leftSideOpeningMultiplier() const;
    bool isLeftSideOpeningMultiplierDefaulted() const;
    bool setLeftSideOpeningMultiplier(double leftSideOpeningMultiplier);
    void resetLeftSideOpeningMultiplier();
    //@}

    /** @name Right side opening multiplier */
    //@{
    double rightSideOpeningMultiplier() const;
    bool isRightSideOpeningMultiplierDefaulted() const;
    bool setRightSideOpeningMultiplier(double rightSideOpeningMultiplier);
    void resetRightSideOpeningMultiplier();
    //@}

    /** @name Front opening multiplier */
    //@{
    double frontOpeningMultiplier() const;
    bool isFrontOpeningMultiplierDefaulted() const;
    bool setFrontOpeningMultiplier(double frontOpeningMultiplier);
    void resetFrontOpeningMultiplier();
    //@}

    /** @name Slat width */
    //@{
    double slatWidth() const;
    bool isSlatWidthDefaulted() const;
    bool setSlatWidth(double slatWidth);
    void resetSlatWidth();
    //@}

    /** @name Slat spacing */
    //@{
    double slatSpacing() const;
    bool isSlatSpacingDefaulted() const;
    bool setSlatSpacing(double slatSpacing);
    void resetSlatSpacing();
    //@}

    /** @name Slat thickness */
    //@{
    double slatThickness() const;
    bool isSlatThicknessDefaulted() const;
    bool setSlatThickness(double slatThickness);
    void resetSlatThickness();
    //@}

    /** @name Slat angle */
    //@{
    double slatAngle() const;
    bool isSlatAngleDefaulted() const;
    bool setSlatAngle(double slatAngle);
    void resetSlatAngle();
    //@}

    /** @name Slat conductivity */
    //@{
    double slatConductivity() const;
    bool isSlatConductivityDefaulted() const;
    bool setSlatConductivity(double slatConductivity);
    void resetSlatConductivity();
    //@}

    /** @name Slat curve */
    //@{
    double slatCurve() const;
    bool isSlatCurveDefaulted() const;
    bool setSlatCurve(double slatCurve);
    void resetSlatCurve();
    //@}

   protected:
    using ImplType = detail::WindowMaterialComplexShade_Impl;

    friend class Model;
    friend class detail::WindowMaterialComplexShade_Impl;

    explicit WindowMaterialComplexShade(std::shared_ptr<detail::WindowMaterialComplexShade_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
