/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_BLIND_HPP
#define EPMODEL_BLIND_HPP

#include "EPModelAPI.hpp"
#include "ShadingMaterial/ShadingMaterial.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class Blind_Impl;
  }

  /** \brief Represents a slatted blind shading material.
   *
   * \par EnergyPlus object
   * \epobject{group-surface-construction-elements.html#windowmaterialblind,WindowMaterial:Blind}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::Blind</code>. EPModel exposes the same slat,
   * optical, and opening-factor fields and additionally exposes the
   * <code>slatCurve()</code> getter/setter/resetter for the EnergyPlus slat
   * curve field.
   *
   * \par Known limitations
   * No separate blind-control relationship is managed by this material wrapper.
   */
  class EPMODEL_API Blind : public ShadingMaterial
  {
   public:
    explicit Blind(const Model& model);

    virtual ~Blind() override = default;
    Blind(const Blind& other) = default;
    Blind(Blind&& other) = default;
    Blind& operator=(const Blind&) = default;
    Blind& operator=(Blind&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> slatOrientationValues();

    std::string slatOrientation() const;
    bool isSlatOrientationDefaulted() const;
    bool setSlatOrientation(const std::string& slatOrientation);
    void resetSlatOrientation();

    double slatWidth() const;
    bool setSlatWidth(double slatWidth);

    double slatSeparation() const;
    bool setSlatSeparation(double slatSeparation);

    double slatThickness() const;
    bool isSlatThicknessDefaulted() const;
    bool setSlatThickness(double slatThickness);
    void resetSlatThickness();

    double slatCurve() const;
    bool isSlatCurveDefaulted() const;
    bool setSlatCurve(double slatCurve);
    void resetSlatCurve();

    double slatAngle() const;
    bool isSlatAngleDefaulted() const;
    bool setSlatAngle(double slatAngle);
    void resetSlatAngle();

    double slatConductivity() const;
    bool isSlatConductivityDefaulted() const;
    bool setSlatConductivity(double slatConductivity);
    void resetSlatConductivity();

    double slatBeamSolarTransmittance() const;
    bool isSlatBeamSolarTransmittanceDefaulted() const;
    bool setSlatBeamSolarTransmittance(double slatBeamSolarTransmittance);
    void resetSlatBeamSolarTransmittance();

    double frontSideSlatBeamSolarReflectance() const;
    bool setFrontSideSlatBeamSolarReflectance(double frontSideSlatBeamSolarReflectance);

    double backSideSlatBeamSolarReflectance() const;
    bool setBackSideSlatBeamSolarReflectance(double backSideSlatBeamSolarReflectance);

    double slatDiffuseSolarTransmittance() const;
    bool isSlatDiffuseSolarTransmittanceDefaulted() const;
    bool setSlatDiffuseSolarTransmittance(double slatDiffuseSolarTransmittance);
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
    bool isSlatDiffuseVisibleTransmittanceDefaulted() const;
    bool setSlatDiffuseVisibleTransmittance(double slatDiffuseVisibleTransmittance);
    void resetSlatDiffuseVisibleTransmittance();

    boost::optional<double> frontSideSlatDiffuseVisibleReflectance() const;
    bool setFrontSideSlatDiffuseVisibleReflectance(double frontSideSlatDiffuseVisibleReflectance);
    void resetFrontSideSlatDiffuseVisibleReflectance();

    boost::optional<double> backSideSlatDiffuseVisibleReflectance() const;
    bool setBackSideSlatDiffuseVisibleReflectance(double backSideSlatDiffuseVisibleReflectance);
    void resetBackSideSlatDiffuseVisibleReflectance();

    double slatInfraredHemisphericalTransmittance() const;
    bool isSlatInfraredHemisphericalTransmittanceDefaulted() const;
    bool setSlatInfraredHemisphericalTransmittance(double slatInfraredHemisphericalTransmittance);
    void resetSlatInfraredHemisphericalTransmittance();

    double frontSideSlatInfraredHemisphericalEmissivity() const;
    bool isFrontSideSlatInfraredHemisphericalEmissivityDefaulted() const;
    bool setFrontSideSlatInfraredHemisphericalEmissivity(double frontSideSlatInfraredHemisphericalEmissivity);
    void resetFrontSideSlatInfraredHemisphericalEmissivity();

    double backSideSlatInfraredHemisphericalEmissivity() const;
    bool isBackSideSlatInfraredHemisphericalEmissivityDefaulted() const;
    bool setBackSideSlatInfraredHemisphericalEmissivity(double backSideSlatInfraredHemisphericalEmissivity);
    void resetBackSideSlatInfraredHemisphericalEmissivity();

    double blindtoGlassDistance() const;
    bool isBlindtoGlassDistanceDefaulted() const;
    bool setBlindtoGlassDistance(double blindtoGlassDistance);
    void resetBlindtoGlassDistance();

    double blindTopOpeningMultiplier() const;
    bool isBlindTopOpeningMultiplierDefaulted() const;
    bool setBlindTopOpeningMultiplier(double blindTopOpeningMultiplier);
    void resetBlindTopOpeningMultiplier();

    double blindBottomOpeningMultiplier() const;
    bool isBlindBottomOpeningMultiplierDefaulted() const;
    bool setBlindBottomOpeningMultiplier(double blindBottomOpeningMultiplier);
    void resetBlindBottomOpeningMultiplier();

    double blindLeftSideOpeningMultiplier() const;
    bool isBlindLeftSideOpeningMultiplierDefaulted() const;
    bool setBlindLeftSideOpeningMultiplier(double blindLeftSideOpeningMultiplier);
    void resetBlindLeftSideOpeningMultiplier();

    double blindRightSideOpeningMultiplier() const;
    bool isBlindRightSideOpeningMultiplierDefaulted() const;
    bool setBlindRightSideOpeningMultiplier(double blindRightSideOpeningMultiplier);
    void resetBlindRightSideOpeningMultiplier();

    double minimumSlatAngle() const;
    bool isMinimumSlatAngleDefaulted() const;
    bool setMinimumSlatAngle(double minimumSlatAngle);
    void resetMinimumSlatAngle();

    double maximumSlatAngle() const;
    bool isMaximumSlatAngleDefaulted() const;
    bool setMaximumSlatAngle(double maximumSlatAngle);
    void resetMaximumSlatAngle();

   protected:
    using ImplType = detail::Blind_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit Blind(std::shared_ptr<detail::Blind_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
