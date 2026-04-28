/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWMATERIALBLINDEQUIVALENTLAYER_HPP
#define EPMODEL_WINDOWMATERIALBLINDEQUIVALENTLAYER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class WindowMaterialBlindEquivalentLayer_Impl;
  }

  class EPMODEL_API WindowMaterialBlindEquivalentLayer : public ModelObject
  {
   public:
    explicit WindowMaterialBlindEquivalentLayer(const Model& model);

    virtual ~WindowMaterialBlindEquivalentLayer() override = default;
    WindowMaterialBlindEquivalentLayer(const WindowMaterialBlindEquivalentLayer& other) = default;
    WindowMaterialBlindEquivalentLayer(WindowMaterialBlindEquivalentLayer&& other) = default;
    WindowMaterialBlindEquivalentLayer& operator=(const WindowMaterialBlindEquivalentLayer&) = default;
    WindowMaterialBlindEquivalentLayer& operator=(WindowMaterialBlindEquivalentLayer&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> slatOrientationValues();
    static std::vector<std::string> slatAngleControlValues();

    // Schema Alignment Notes:
    // - API: IDD-derived WindowMaterial:Blind:EquivalentLayer scalar optics and thermal properties map directly to these fields.
    // - Field Mapping: Required spacing/reflectance scalars stay as strict getters, optional fields expose boost::optional and reset helpers.
    // - Field Mapping: Name and WindowEquivalentLayerMaterialNames references remain exposed through the ModelObject base API.
    // - TODO(parity): Add relationship helpers once translator coverage of WindowEquivalentLayer relationships reaches epmodel.

    /** @name Scalar Accessors */
    //@{
    std::string slatOrientation() const;
    bool isSlatOrientationDefaulted() const;
    bool setSlatOrientation(const std::string& slatOrientation);
    void resetSlatOrientation();

    double slatWidth() const;
    bool setSlatWidth(double slatWidth);

    double slatSeparation() const;
    bool setSlatSeparation(double slatSeparation);

    double slatCrown() const;
    bool isSlatCrownDefaulted() const;
    bool setSlatCrown(double slatCrown);
    void resetSlatCrown();

    double slatAngle() const;
    bool isSlatAngleDefaulted() const;
    bool setSlatAngle(double slatAngle);
    void resetSlatAngle();

    double frontSideSlatBeamDiffuseSolarTransmittance() const;
    bool isFrontSideSlatBeamDiffuseSolarTransmittanceDefaulted() const;
    bool setFrontSideSlatBeamDiffuseSolarTransmittance(double frontSideSlatBeamDiffuseSolarTransmittance);
    void resetFrontSideSlatBeamDiffuseSolarTransmittance();

    double backSideSlatBeamDiffuseSolarTransmittance() const;
    bool isBackSideSlatBeamDiffuseSolarTransmittanceDefaulted() const;
    bool setBackSideSlatBeamDiffuseSolarTransmittance(double backSideSlatBeamDiffuseSolarTransmittance);
    void resetBackSideSlatBeamDiffuseSolarTransmittance();

    double frontSideSlatBeamDiffuseSolarReflectance() const;
    bool setFrontSideSlatBeamDiffuseSolarReflectance(double frontSideSlatBeamDiffuseSolarReflectance);

    double backSideSlatBeamDiffuseSolarReflectance() const;
    bool setBackSideSlatBeamDiffuseSolarReflectance(double backSideSlatBeamDiffuseSolarReflectance);

    double frontSideSlatBeamDiffuseVisibleTransmittance() const;
    bool isFrontSideSlatBeamDiffuseVisibleTransmittanceDefaulted() const;
    bool setFrontSideSlatBeamDiffuseVisibleTransmittance(double frontSideSlatBeamDiffuseVisibleTransmittance);
    void resetFrontSideSlatBeamDiffuseVisibleTransmittance();

    double backSideSlatBeamDiffuseVisibleTransmittance() const;
    bool isBackSideSlatBeamDiffuseVisibleTransmittanceDefaulted() const;
    bool setBackSideSlatBeamDiffuseVisibleTransmittance(double backSideSlatBeamDiffuseVisibleTransmittance);
    void resetBackSideSlatBeamDiffuseVisibleTransmittance();

    boost::optional<double> frontSideSlatBeamDiffuseVisibleReflectance() const;
    bool setFrontSideSlatBeamDiffuseVisibleReflectance(double frontSideSlatBeamDiffuseVisibleReflectance);
    void resetFrontSideSlatBeamDiffuseVisibleReflectance();

    boost::optional<double> backSideSlatBeamDiffuseVisibleReflectance() const;
    bool setBackSideSlatBeamDiffuseVisibleReflectance(double backSideSlatBeamDiffuseVisibleReflectance);
    void resetBackSideSlatBeamDiffuseVisibleReflectance();

    double slatDiffuseDiffuseSolarTransmittance() const;
    bool isSlatDiffuseDiffuseSolarTransmittanceDefaulted() const;
    bool setSlatDiffuseDiffuseSolarTransmittance(double slatDiffuseDiffuseSolarTransmittance);
    void resetSlatDiffuseDiffuseSolarTransmittance();

    double frontSideSlatDiffuseDiffuseSolarReflectance() const;
    bool setFrontSideSlatDiffuseDiffuseSolarReflectance(double frontSideSlatDiffuseDiffuseSolarReflectance);

    double backSideSlatDiffuseDiffuseSolarReflectance() const;
    bool setBackSideSlatDiffuseDiffuseSolarReflectance(double backSideSlatDiffuseDiffuseSolarReflectance);

    boost::optional<double> slatDiffuseDiffuseVisibleTransmittance() const;
    bool setSlatDiffuseDiffuseVisibleTransmittance(double slatDiffuseDiffuseVisibleTransmittance);
    void resetSlatDiffuseDiffuseVisibleTransmittance();

    boost::optional<double> frontSideSlatDiffuseDiffuseVisibleReflectance() const;
    bool setFrontSideSlatDiffuseDiffuseVisibleReflectance(double frontSideSlatDiffuseDiffuseVisibleReflectance);
    void resetFrontSideSlatDiffuseDiffuseVisibleReflectance();

    boost::optional<double> backSideSlatDiffuseDiffuseVisibleReflectance() const;
    bool setBackSideSlatDiffuseDiffuseVisibleReflectance(double backSideSlatDiffuseDiffuseVisibleReflectance);
    void resetBackSideSlatDiffuseDiffuseVisibleReflectance();

    double slatInfraredTransmittance() const;
    bool isSlatInfraredTransmittanceDefaulted() const;
    bool setSlatInfraredTransmittance(double slatInfraredTransmittance);
    void resetSlatInfraredTransmittance();

    double frontSideSlatInfraredEmissivity() const;
    bool isFrontSideSlatInfraredEmissivityDefaulted() const;
    bool setFrontSideSlatInfraredEmissivity(double frontSideSlatInfraredEmissivity);
    void resetFrontSideSlatInfraredEmissivity();

    double backSideSlatInfraredEmissivity() const;
    bool isBackSideSlatInfraredEmissivityDefaulted() const;
    bool setBackSideSlatInfraredEmissivity(double backSideSlatInfraredEmissivity);
    void resetBackSideSlatInfraredEmissivity();

    std::string slatAngleControl() const;
    bool isSlatAngleControlDefaulted() const;
    bool setSlatAngleControl(const std::string& slatAngleControl);
    void resetSlatAngleControl();
    //@}

   protected:
    using ImplType = detail::WindowMaterialBlindEquivalentLayer_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WindowMaterialBlindEquivalentLayer(std::shared_ptr<detail::WindowMaterialBlindEquivalentLayer_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
