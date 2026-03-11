/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWMATERIALSHADEEQUIVALENTLAYER_HPP
#define EPMODEL_WINDOWMATERIALSHADEEQUIVALENTLAYER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class WindowMaterialShadeEquivalentLayer_Impl;
  }

  class EPMODEL_API WindowMaterialShadeEquivalentLayer : public ModelObject
  {
   public:
    explicit WindowMaterialShadeEquivalentLayer(const Model& model);

    virtual ~WindowMaterialShadeEquivalentLayer() override = default;
    WindowMaterialShadeEquivalentLayer(const WindowMaterialShadeEquivalentLayer& other) = default;
    WindowMaterialShadeEquivalentLayer(WindowMaterialShadeEquivalentLayer&& other) = default;
    WindowMaterialShadeEquivalentLayer& operator=(const WindowMaterialShadeEquivalentLayer&) = default;
    WindowMaterialShadeEquivalentLayer& operator=(WindowMaterialShadeEquivalentLayer&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: WindowMaterial:Shade:EquivalentLayer scalar optics/thermal fields map directly to these accessors; there is no openstudio::model counterpart so IDD naming is retained.
    // - Field Mapping: Shade beam-beam/diffuse transmittance and reflectance fields, optional visible optics, and shade infrared properties mirror the IDD names while the shared Name reference aligns with WindowEquivalentLayerMaterialNames.

    double shadeBeamBeamSolarTransmittance() const;
    bool isShadeBeamBeamSolarTransmittanceDefaulted() const;

    double frontSideShadeBeamDiffuseSolarTransmittance() const;
    double backSideShadeBeamDiffuseSolarTransmittance() const;
    double frontSideShadeBeamDiffuseSolarReflectance() const;
    double backSideShadeBeamDiffuseSolarReflectance() const;

    boost::optional<double> shadeBeamBeamVisibleTransmittanceAtNormalIncidence() const;
    boost::optional<double> shadeBeamDiffuseVisibleTransmittanceAtNormalIncidence() const;
    boost::optional<double> shadeBeamDiffuseVisibleReflectanceAtNormalIncidence() const;

    double shadeMaterialInfraredTransmittance() const;
    bool isShadeMaterialInfraredTransmittanceDefaulted() const;

    double frontSideShadeMaterialInfraredEmissivity() const;
    bool isFrontSideShadeMaterialInfraredEmissivityDefaulted() const;

    double backSideShadeMaterialInfraredEmissivity() const;
    bool isBackSideShadeMaterialInfraredEmissivityDefaulted() const;

    bool setShadeBeamBeamSolarTransmittance(double shadeBeamBeamSolarTransmittance);
    bool setFrontSideShadeBeamDiffuseSolarTransmittance(double frontSideShadeBeamDiffuseSolarTransmittance);
    bool setBackSideShadeBeamDiffuseSolarTransmittance(double backSideShadeBeamDiffuseSolarTransmittance);
    bool setFrontSideShadeBeamDiffuseSolarReflectance(double frontSideShadeBeamDiffuseSolarReflectance);
    bool setBackSideShadeBeamDiffuseSolarReflectance(double backSideShadeBeamDiffuseSolarReflectance);

    bool setShadeBeamBeamVisibleTransmittanceAtNormalIncidence(double shadeBeamBeamVisibleTransmittanceAtNormalIncidence);
    bool setShadeBeamDiffuseVisibleTransmittanceAtNormalIncidence(double shadeBeamDiffuseVisibleTransmittanceAtNormalIncidence);
    bool setShadeBeamDiffuseVisibleReflectanceAtNormalIncidence(double shadeBeamDiffuseVisibleReflectanceAtNormalIncidence);

    bool setShadeMaterialInfraredTransmittance(double shadeMaterialInfraredTransmittance);
    bool setFrontSideShadeMaterialInfraredEmissivity(double frontSideShadeMaterialInfraredEmissivity);
    bool setBackSideShadeMaterialInfraredEmissivity(double backSideShadeMaterialInfraredEmissivity);

    void resetShadeBeamBeamSolarTransmittance();
    void resetShadeMaterialInfraredTransmittance();
    void resetFrontSideShadeMaterialInfraredEmissivity();
    void resetBackSideShadeMaterialInfraredEmissivity();

   protected:
    using ImplType = detail::WindowMaterialShadeEquivalentLayer_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WindowMaterialShadeEquivalentLayer(std::shared_ptr<detail::WindowMaterialShadeEquivalentLayer_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
