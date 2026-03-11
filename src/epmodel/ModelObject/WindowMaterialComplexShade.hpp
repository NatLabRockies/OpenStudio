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

    /** @name Getters */
    //@{
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
    //@}

    /** @name Setters */
    //@{
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
