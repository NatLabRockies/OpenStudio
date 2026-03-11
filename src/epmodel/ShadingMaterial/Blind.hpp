/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_BLIND_HPP
#define EPMODEL_BLIND_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

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

  class EPMODEL_API Blind : public ModelObject
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

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model Blind scalar names/signatures even though defaults exist so the epmodel facade remains stable.
    // - Field Mapping: Slat geometry and optical scalars map directly to their EnergyPlus WindowMaterial:Blind field counterparts.
    // - Field Mapping: Optional visible/infrared reflectance getters mirror the openstudio::model boost::optional<double> APIs while still delegating to the same IDD strings.
    // - Field Mapping: Debuggable forward translation is provided by ForwardTranslateBlind.cpp, which republishes these fields to EnergyPlus.
    std::string slatOrientation() const;
    bool isSlatOrientationDefaulted() const;

    double slatWidth() const;
    double slatSeparation() const;

    double slatThickness() const;
    bool isSlatThicknessDefaulted() const;

    double slatCurve() const;
    bool isSlatCurveDefaulted() const;

    double slatAngle() const;
    bool isSlatAngleDefaulted() const;

    double slatConductivity() const;
    bool isSlatConductivityDefaulted() const;

    double slatBeamSolarTransmittance() const;
    bool isSlatBeamSolarTransmittanceDefaulted() const;

    double frontSideSlatBeamSolarReflectance() const;
    double backSideSlatBeamSolarReflectance() const;

    double slatDiffuseSolarTransmittance() const;
    bool isSlatDiffuseSolarTransmittanceDefaulted() const;

    double frontSideSlatDiffuseSolarReflectance() const;
    double backSideSlatDiffuseSolarReflectance() const;

    double slatBeamVisibleTransmittance() const;
    boost::optional<double> frontSideSlatBeamVisibleReflectance() const;
    boost::optional<double> backSideSlatBeamVisibleReflectance() const;

    double slatDiffuseVisibleTransmittance() const;
    bool isSlatDiffuseVisibleTransmittanceDefaulted() const;

    boost::optional<double> frontSideSlatDiffuseVisibleReflectance() const;
    boost::optional<double> backSideSlatDiffuseVisibleReflectance() const;

    double slatInfraredHemisphericalTransmittance() const;
    bool isSlatInfraredHemisphericalTransmittanceDefaulted() const;

    double frontSideSlatInfraredHemisphericalEmissivity() const;
    bool isFrontSideSlatInfraredHemisphericalEmissivityDefaulted() const;

    double backSideSlatInfraredHemisphericalEmissivity() const;
    bool isBackSideSlatInfraredHemisphericalEmissivityDefaulted() const;

    double blindtoGlassDistance() const;
    bool isBlindtoGlassDistanceDefaulted() const;

    double blindTopOpeningMultiplier() const;
    bool isBlindTopOpeningMultiplierDefaulted() const;

    double blindBottomOpeningMultiplier() const;
    bool isBlindBottomOpeningMultiplierDefaulted() const;

    double blindLeftSideOpeningMultiplier() const;
    bool isBlindLeftSideOpeningMultiplierDefaulted() const;

    double blindRightSideOpeningMultiplier() const;
    bool isBlindRightSideOpeningMultiplierDefaulted() const;

    double minimumSlatAngle() const;
    bool isMinimumSlatAngleDefaulted() const;

    double maximumSlatAngle() const;
    bool isMaximumSlatAngleDefaulted() const;

    bool setSlatOrientation(const std::string& slatOrientation);
    void resetSlatOrientation();

    bool setSlatWidth(double slatWidth);
    bool setSlatSeparation(double slatSeparation);

    bool setSlatThickness(double slatThickness);
    void resetSlatThickness();

    bool setSlatCurve(double slatCurve);
    void resetSlatCurve();

    bool setSlatAngle(double slatAngle);
    void resetSlatAngle();

    bool setSlatConductivity(double slatConductivity);
    void resetSlatConductivity();

    bool setSlatBeamSolarTransmittance(double slatBeamSolarTransmittance);
    void resetSlatBeamSolarTransmittance();

    bool setFrontSideSlatBeamSolarReflectance(double frontSideSlatBeamSolarReflectance);
    bool setBackSideSlatBeamSolarReflectance(double backSideSlatBeamSolarReflectance);

    bool setSlatDiffuseSolarTransmittance(double slatDiffuseSolarTransmittance);
    void resetSlatDiffuseSolarTransmittance();

    bool setFrontSideSlatDiffuseSolarReflectance(double frontSideSlatDiffuseSolarReflectance);
    bool setBackSideSlatDiffuseSolarReflectance(double backSideSlatDiffuseSolarReflectance);

    bool setSlatBeamVisibleTransmittance(double slatBeamVisibleTransmittance);
    bool setFrontSideSlatBeamVisibleReflectance(double frontSideSlatBeamVisibleReflectance);
    void resetFrontSideSlatBeamVisibleReflectance();

    bool setBackSideSlatBeamVisibleReflectance(double backSideSlatBeamVisibleReflectance);
    void resetBackSideSlatBeamVisibleReflectance();

    bool setSlatDiffuseVisibleTransmittance(double slatDiffuseVisibleTransmittance);
    void resetSlatDiffuseVisibleTransmittance();

    bool setFrontSideSlatDiffuseVisibleReflectance(double frontSideSlatDiffuseVisibleReflectance);
    void resetFrontSideSlatDiffuseVisibleReflectance();

    bool setBackSideSlatDiffuseVisibleReflectance(double backSideSlatDiffuseVisibleReflectance);
    void resetBackSideSlatDiffuseVisibleReflectance();

    bool setSlatInfraredHemisphericalTransmittance(double slatInfraredHemisphericalTransmittance);
    void resetSlatInfraredHemisphericalTransmittance();

    bool setFrontSideSlatInfraredHemisphericalEmissivity(double frontSideSlatInfraredHemisphericalEmissivity);
    void resetFrontSideSlatInfraredHemisphericalEmissivity();

    bool setBackSideSlatInfraredHemisphericalEmissivity(double backSideSlatInfraredHemisphericalEmissivity);
    void resetBackSideSlatInfraredHemisphericalEmissivity();

    bool setBlindtoGlassDistance(double blindtoGlassDistance);
    void resetBlindtoGlassDistance();

    bool setBlindTopOpeningMultiplier(double blindTopOpeningMultiplier);
    void resetBlindTopOpeningMultiplier();

    bool setBlindBottomOpeningMultiplier(double blindBottomOpeningMultiplier);
    void resetBlindBottomOpeningMultiplier();

    bool setBlindLeftSideOpeningMultiplier(double blindLeftSideOpeningMultiplier);
    void resetBlindLeftSideOpeningMultiplier();

    bool setBlindRightSideOpeningMultiplier(double blindRightSideOpeningMultiplier);
    void resetBlindRightSideOpeningMultiplier();

    bool setMinimumSlatAngle(double minimumSlatAngle);
    void resetMinimumSlatAngle();

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
