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

    /** @name Getters */
    //@{
    std::string opticalDataType() const;
    bool isOpticalDataTypeDefaulted() const;

    double frontSideBeamBeamSolarTransmittance() const;
    double backSideBeamBeamSolarTransmittance() const;
    double frontSideBeamBeamSolarReflectance() const;
    double backSideBeamBeamSolarReflectance() const;

    double frontSideBeamBeamVisibleSolarTransmittance() const;
    bool isFrontSideBeamBeamVisibleSolarTransmittanceDefaulted() const;

    double backSideBeamBeamVisibleSolarTransmittance() const;
    bool isBackSideBeamBeamVisibleSolarTransmittanceDefaulted() const;

    double frontSideBeamBeamVisibleSolarReflectance() const;
    bool isFrontSideBeamBeamVisibleSolarReflectanceDefaulted() const;

    double backSideBeamBeamVisibleSolarReflectance() const;
    bool isBackSideBeamBeamVisibleSolarReflectanceDefaulted() const;

    double frontSideBeamDiffuseSolarTransmittance() const;
    bool isFrontSideBeamDiffuseSolarTransmittanceDefaulted() const;

    double backSideBeamDiffuseSolarTransmittance() const;
    bool isBackSideBeamDiffuseSolarTransmittanceDefaulted() const;

    double frontSideBeamDiffuseSolarReflectance() const;
    bool isFrontSideBeamDiffuseSolarReflectanceDefaulted() const;

    double backSideBeamDiffuseSolarReflectance() const;
    bool isBackSideBeamDiffuseSolarReflectanceDefaulted() const;

    double frontSideBeamDiffuseVisibleSolarTransmittance() const;
    bool isFrontSideBeamDiffuseVisibleSolarTransmittanceDefaulted() const;

    double backSideBeamDiffuseVisibleSolarTransmittance() const;
    bool isBackSideBeamDiffuseVisibleSolarTransmittanceDefaulted() const;

    double frontSideBeamDiffuseVisibleSolarReflectance() const;
    bool isFrontSideBeamDiffuseVisibleSolarReflectanceDefaulted() const;

    double backSideBeamDiffuseVisibleSolarReflectance() const;
    bool isBackSideBeamDiffuseVisibleSolarReflectanceDefaulted() const;

    boost::optional<double> diffuseDiffuseSolarTransmittance() const;
    bool isDiffuseDiffuseSolarTransmittanceDefaulted() const;
    bool isDiffuseDiffuseSolarTransmittanceAutocalculated() const;

    boost::optional<double> frontSideDiffuseDiffuseSolarReflectance() const;
    bool isFrontSideDiffuseDiffuseSolarReflectanceDefaulted() const;
    bool isFrontSideDiffuseDiffuseSolarReflectanceAutocalculated() const;

    boost::optional<double> backSideDiffuseDiffuseSolarReflectance() const;
    bool isBackSideDiffuseDiffuseSolarReflectanceDefaulted() const;
    bool isBackSideDiffuseDiffuseSolarReflectanceAutocalculated() const;

    boost::optional<double> diffuseDiffuseVisibleSolarTransmittance() const;
    bool isDiffuseDiffuseVisibleSolarTransmittanceDefaulted() const;
    bool isDiffuseDiffuseVisibleSolarTransmittanceAutocalculated() const;

    boost::optional<double> frontSideDiffuseDiffuseVisibleSolarReflectance() const;
    bool isFrontSideDiffuseDiffuseVisibleSolarReflectanceDefaulted() const;
    bool isFrontSideDiffuseDiffuseVisibleSolarReflectanceAutocalculated() const;

    boost::optional<double> backSideDiffuseDiffuseVisibleSolarReflectance() const;
    bool isBackSideDiffuseDiffuseVisibleSolarReflectanceDefaulted() const;
    bool isBackSideDiffuseDiffuseVisibleSolarReflectanceAutocalculated() const;

    double infraredTransmittance() const;
    bool isInfraredTransmittanceDefaulted() const;

    double frontSideInfraredEmissivity() const;
    bool isFrontSideInfraredEmissivityDefaulted() const;

    double backSideInfraredEmissivity() const;
    bool isBackSideInfraredEmissivityDefaulted() const;

    double thermalResistance() const;
    bool isThermalResistanceDefaulted() const;
    //@}

    /** @name Setters */
    //@{
    bool setOpticalDataType(const std::string& opticalDataType);

    bool setFrontSideBeamBeamSolarTransmittance(double frontSideBeamBeamSolarTransmittance);
    bool setBackSideBeamBeamSolarTransmittance(double backSideBeamBeamSolarTransmittance);
    bool setFrontSideBeamBeamSolarReflectance(double frontSideBeamBeamSolarReflectance);
    bool setBackSideBeamBeamSolarReflectance(double backSideBeamBeamSolarReflectance);

    bool setFrontSideBeamBeamVisibleSolarTransmittance(double frontSideBeamBeamVisibleSolarTransmittance);
    bool setBackSideBeamBeamVisibleSolarTransmittance(double backSideBeamBeamVisibleSolarTransmittance);
    bool setFrontSideBeamBeamVisibleSolarReflectance(double frontSideBeamBeamVisibleSolarReflectance);
    bool setBackSideBeamBeamVisibleSolarReflectance(double backSideBeamBeamVisibleSolarReflectance);

    bool setFrontSideBeamDiffuseSolarTransmittance(double frontSideBeamDiffuseSolarTransmittance);
    bool setBackSideBeamDiffuseSolarTransmittance(double backSideBeamDiffuseSolarTransmittance);
    bool setFrontSideBeamDiffuseSolarReflectance(double frontSideBeamDiffuseSolarReflectance);
    bool setBackSideBeamDiffuseSolarReflectance(double backSideBeamDiffuseSolarReflectance);

    bool setFrontSideBeamDiffuseVisibleSolarTransmittance(double frontSideBeamDiffuseVisibleSolarTransmittance);
    bool setBackSideBeamDiffuseVisibleSolarTransmittance(double backSideBeamDiffuseVisibleSolarTransmittance);
    bool setFrontSideBeamDiffuseVisibleSolarReflectance(double frontSideBeamDiffuseVisibleSolarReflectance);
    bool setBackSideBeamDiffuseVisibleSolarReflectance(double backSideBeamDiffuseVisibleSolarReflectance);

    bool setDiffuseDiffuseSolarTransmittance(double diffuseDiffuseSolarTransmittance);
    bool setFrontSideDiffuseDiffuseSolarReflectance(double frontSideDiffuseDiffuseSolarReflectance);
    bool setBackSideDiffuseDiffuseSolarReflectance(double backSideDiffuseDiffuseSolarReflectance);
    bool setDiffuseDiffuseVisibleSolarTransmittance(double diffuseDiffuseVisibleSolarTransmittance);
    bool setFrontSideDiffuseDiffuseVisibleSolarReflectance(double frontSideDiffuseDiffuseVisibleSolarReflectance);
    bool setBackSideDiffuseDiffuseVisibleSolarReflectance(double backSideDiffuseDiffuseVisibleSolarReflectance);

    bool setInfraredTransmittance(double infraredTransmittance);
    bool setFrontSideInfraredEmissivity(double frontSideInfraredEmissivity);
    bool setBackSideInfraredEmissivity(double backSideInfraredEmissivity);
    bool setThermalResistance(double thermalResistance);

    void resetOpticalDataType();

    void resetFrontSideBeamBeamVisibleSolarTransmittance();
    void resetBackSideBeamBeamVisibleSolarTransmittance();
    void resetFrontSideBeamBeamVisibleSolarReflectance();
    void resetBackSideBeamBeamVisibleSolarReflectance();

    void resetFrontSideBeamDiffuseSolarTransmittance();
    void resetBackSideBeamDiffuseSolarTransmittance();
    void resetFrontSideBeamDiffuseSolarReflectance();
    void resetBackSideBeamDiffuseSolarReflectance();

    void resetFrontSideBeamDiffuseVisibleSolarTransmittance();
    void resetBackSideBeamDiffuseVisibleSolarTransmittance();
    void resetFrontSideBeamDiffuseVisibleSolarReflectance();
    void resetBackSideBeamDiffuseVisibleSolarReflectance();

    void resetDiffuseDiffuseSolarTransmittance();
    void resetFrontSideDiffuseDiffuseSolarReflectance();
    void resetBackSideDiffuseDiffuseSolarReflectance();
    void resetDiffuseDiffuseVisibleSolarTransmittance();
    void resetFrontSideDiffuseDiffuseVisibleSolarReflectance();
    void resetBackSideDiffuseDiffuseVisibleSolarReflectance();

    void resetInfraredTransmittance();
    void resetFrontSideInfraredEmissivity();
    void resetBackSideInfraredEmissivity();
    void resetThermalResistance();

    void autocalculateDiffuseDiffuseSolarTransmittance();
    void autocalculateFrontSideDiffuseDiffuseSolarReflectance();
    void autocalculateBackSideDiffuseDiffuseSolarReflectance();
    void autocalculateDiffuseDiffuseVisibleSolarTransmittance();
    void autocalculateFrontSideDiffuseDiffuseVisibleSolarReflectance();
    void autocalculateBackSideDiffuseDiffuseVisibleSolarReflectance();
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
