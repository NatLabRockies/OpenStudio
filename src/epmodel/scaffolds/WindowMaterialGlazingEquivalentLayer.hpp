/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWMATERIALGLAZINGEQUIVALENTLAYER_HPP
#define EPMODEL_WINDOWMATERIALGLAZINGEQUIVALENTLAYER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class WindowMaterialGlazingEquivalentLayer_Impl;
  }

  class EPMODEL_API WindowMaterialGlazingEquivalentLayer : public ModelObject
  {
   public:
    explicit WindowMaterialGlazingEquivalentLayer(const Model& model);

    virtual ~WindowMaterialGlazingEquivalentLayer() override = default;
    WindowMaterialGlazingEquivalentLayer(const WindowMaterialGlazingEquivalentLayer& other) = default;
    WindowMaterialGlazingEquivalentLayer(WindowMaterialGlazingEquivalentLayer&& other) = default;
    WindowMaterialGlazingEquivalentLayer& operator=(const WindowMaterialGlazingEquivalentLayer&) = default;
    WindowMaterialGlazingEquivalentLayer& operator=(WindowMaterialGlazingEquivalentLayer&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> opticalDataTypeValues();

    // Schema Alignment Notes:
    // - API: Equivalent-layer glazing optics (beam/diffuse transmittance & reflectance, diffuse-diffuse auto-calculations,
    //   infrared transmittance/emissivity, and the R-value) map directly to WindowMaterial:Glazing:EquivalentLayer scalar fields.
    // - Field Mapping: OpticalDataType plus the numeric transmittance/reflectance/emissivity/resistance fields mirror the IDD names while
    //   the Window Glass Spectral Data Set Name object-list relationship is intentionally excluded from these scalar helpers.
    // - TODO(parity): Surface the spectral data set relationship once ForwardTranslator exposes equivalent-layer spectral helpers.

    /** @name Scalar field helpers */
    //@{
    std::string opticalDataType() const;
    bool isOpticalDataTypeDefaulted() const;
    bool setOpticalDataType(const std::string& opticalDataType);
    void resetOpticalDataType();

    double frontSideBeamBeamSolarTransmittance() const;
    bool setFrontSideBeamBeamSolarTransmittance(double frontSideBeamBeamSolarTransmittance);

    double backSideBeamBeamSolarTransmittance() const;
    bool setBackSideBeamBeamSolarTransmittance(double backSideBeamBeamSolarTransmittance);

    double frontSideBeamBeamSolarReflectance() const;
    bool setFrontSideBeamBeamSolarReflectance(double frontSideBeamBeamSolarReflectance);

    double backSideBeamBeamSolarReflectance() const;
    bool setBackSideBeamBeamSolarReflectance(double backSideBeamBeamSolarReflectance);

    double frontSideBeamBeamVisibleSolarTransmittance() const;
    bool isFrontSideBeamBeamVisibleSolarTransmittanceDefaulted() const;
    bool setFrontSideBeamBeamVisibleSolarTransmittance(double frontSideBeamBeamVisibleSolarTransmittance);
    void resetFrontSideBeamBeamVisibleSolarTransmittance();

    double backSideBeamBeamVisibleSolarTransmittance() const;
    bool isBackSideBeamBeamVisibleSolarTransmittanceDefaulted() const;
    bool setBackSideBeamBeamVisibleSolarTransmittance(double backSideBeamBeamVisibleSolarTransmittance);
    void resetBackSideBeamBeamVisibleSolarTransmittance();

    double frontSideBeamBeamVisibleSolarReflectance() const;
    bool isFrontSideBeamBeamVisibleSolarReflectanceDefaulted() const;
    bool setFrontSideBeamBeamVisibleSolarReflectance(double frontSideBeamBeamVisibleSolarReflectance);
    void resetFrontSideBeamBeamVisibleSolarReflectance();

    double backSideBeamBeamVisibleSolarReflectance() const;
    bool isBackSideBeamBeamVisibleSolarReflectanceDefaulted() const;
    bool setBackSideBeamBeamVisibleSolarReflectance(double backSideBeamBeamVisibleSolarReflectance);
    void resetBackSideBeamBeamVisibleSolarReflectance();

    double frontSideBeamDiffuseSolarTransmittance() const;
    bool isFrontSideBeamDiffuseSolarTransmittanceDefaulted() const;
    bool setFrontSideBeamDiffuseSolarTransmittance(double frontSideBeamDiffuseSolarTransmittance);
    void resetFrontSideBeamDiffuseSolarTransmittance();

    double backSideBeamDiffuseSolarTransmittance() const;
    bool isBackSideBeamDiffuseSolarTransmittanceDefaulted() const;
    bool setBackSideBeamDiffuseSolarTransmittance(double backSideBeamDiffuseSolarTransmittance);
    void resetBackSideBeamDiffuseSolarTransmittance();

    double frontSideBeamDiffuseSolarReflectance() const;
    bool isFrontSideBeamDiffuseSolarReflectanceDefaulted() const;
    bool setFrontSideBeamDiffuseSolarReflectance(double frontSideBeamDiffuseSolarReflectance);
    void resetFrontSideBeamDiffuseSolarReflectance();

    double backSideBeamDiffuseSolarReflectance() const;
    bool isBackSideBeamDiffuseSolarReflectanceDefaulted() const;
    bool setBackSideBeamDiffuseSolarReflectance(double backSideBeamDiffuseSolarReflectance);
    void resetBackSideBeamDiffuseSolarReflectance();

    double frontSideBeamDiffuseVisibleSolarTransmittance() const;
    bool isFrontSideBeamDiffuseVisibleSolarTransmittanceDefaulted() const;
    bool setFrontSideBeamDiffuseVisibleSolarTransmittance(double frontSideBeamDiffuseVisibleSolarTransmittance);
    void resetFrontSideBeamDiffuseVisibleSolarTransmittance();

    double backSideBeamDiffuseVisibleSolarTransmittance() const;
    bool isBackSideBeamDiffuseVisibleSolarTransmittanceDefaulted() const;
    bool setBackSideBeamDiffuseVisibleSolarTransmittance(double backSideBeamDiffuseVisibleSolarTransmittance);
    void resetBackSideBeamDiffuseVisibleSolarTransmittance();

    double frontSideBeamDiffuseVisibleSolarReflectance() const;
    bool isFrontSideBeamDiffuseVisibleSolarReflectanceDefaulted() const;
    bool setFrontSideBeamDiffuseVisibleSolarReflectance(double frontSideBeamDiffuseVisibleSolarReflectance);
    void resetFrontSideBeamDiffuseVisibleSolarReflectance();

    double backSideBeamDiffuseVisibleSolarReflectance() const;
    bool isBackSideBeamDiffuseVisibleSolarReflectanceDefaulted() const;
    bool setBackSideBeamDiffuseVisibleSolarReflectance(double backSideBeamDiffuseVisibleSolarReflectance);
    void resetBackSideBeamDiffuseVisibleSolarReflectance();

    boost::optional<double> diffuseDiffuseSolarTransmittance() const;
    bool isDiffuseDiffuseSolarTransmittanceDefaulted() const;
    bool isDiffuseDiffuseSolarTransmittanceAutocalculated() const;
    bool setDiffuseDiffuseSolarTransmittance(double diffuseDiffuseSolarTransmittance);
    void resetDiffuseDiffuseSolarTransmittance();
    void autocalculateDiffuseDiffuseSolarTransmittance();

    boost::optional<double> frontSideDiffuseDiffuseSolarReflectance() const;
    bool isFrontSideDiffuseDiffuseSolarReflectanceDefaulted() const;
    bool isFrontSideDiffuseDiffuseSolarReflectanceAutocalculated() const;
    bool setFrontSideDiffuseDiffuseSolarReflectance(double frontSideDiffuseDiffuseSolarReflectance);
    void resetFrontSideDiffuseDiffuseSolarReflectance();
    void autocalculateFrontSideDiffuseDiffuseSolarReflectance();

    boost::optional<double> backSideDiffuseDiffuseSolarReflectance() const;
    bool isBackSideDiffuseDiffuseSolarReflectanceDefaulted() const;
    bool isBackSideDiffuseDiffuseSolarReflectanceAutocalculated() const;
    bool setBackSideDiffuseDiffuseSolarReflectance(double backSideDiffuseDiffuseSolarReflectance);
    void resetBackSideDiffuseDiffuseSolarReflectance();
    void autocalculateBackSideDiffuseDiffuseSolarReflectance();

    boost::optional<double> diffuseDiffuseVisibleSolarTransmittance() const;
    bool isDiffuseDiffuseVisibleSolarTransmittanceDefaulted() const;
    bool isDiffuseDiffuseVisibleSolarTransmittanceAutocalculated() const;
    bool setDiffuseDiffuseVisibleSolarTransmittance(double diffuseDiffuseVisibleSolarTransmittance);
    void resetDiffuseDiffuseVisibleSolarTransmittance();
    void autocalculateDiffuseDiffuseVisibleSolarTransmittance();

    boost::optional<double> frontSideDiffuseDiffuseVisibleSolarReflectance() const;
    bool isFrontSideDiffuseDiffuseVisibleSolarReflectanceDefaulted() const;
    bool isFrontSideDiffuseDiffuseVisibleSolarReflectanceAutocalculated() const;
    bool setFrontSideDiffuseDiffuseVisibleSolarReflectance(double frontSideDiffuseDiffuseVisibleSolarReflectance);
    void resetFrontSideDiffuseDiffuseVisibleSolarReflectance();
    void autocalculateFrontSideDiffuseDiffuseVisibleSolarReflectance();

    boost::optional<double> backSideDiffuseDiffuseVisibleSolarReflectance() const;
    bool isBackSideDiffuseDiffuseVisibleSolarReflectanceDefaulted() const;
    bool isBackSideDiffuseDiffuseVisibleSolarReflectanceAutocalculated() const;
    bool setBackSideDiffuseDiffuseVisibleSolarReflectance(double backSideDiffuseDiffuseVisibleSolarReflectance);
    void resetBackSideDiffuseDiffuseVisibleSolarReflectance();
    void autocalculateBackSideDiffuseDiffuseVisibleSolarReflectance();

    double infraredTransmittance() const;
    bool isInfraredTransmittanceDefaulted() const;
    bool setInfraredTransmittance(double infraredTransmittance);
    void resetInfraredTransmittance();

    double frontSideInfraredEmissivity() const;
    bool isFrontSideInfraredEmissivityDefaulted() const;
    bool setFrontSideInfraredEmissivity(double frontSideInfraredEmissivity);
    void resetFrontSideInfraredEmissivity();

    double backSideInfraredEmissivity() const;
    bool isBackSideInfraredEmissivityDefaulted() const;
    bool setBackSideInfraredEmissivity(double backSideInfraredEmissivity);
    void resetBackSideInfraredEmissivity();

    double thermalResistance() const;
    bool isThermalResistanceDefaulted() const;
    bool setThermalResistance(double thermalResistance);
    void resetThermalResistance();
    //@}

   protected:
    using ImplType = detail::WindowMaterialGlazingEquivalentLayer_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WindowMaterialGlazingEquivalentLayer(std::shared_ptr<detail::WindowMaterialGlazingEquivalentLayer_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
