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
    bool setShadeBeamBeamSolarTransmittance(double shadeBeamBeamSolarTransmittance);
    void resetShadeBeamBeamSolarTransmittance();

    double frontSideShadeBeamDiffuseSolarTransmittance() const;
    bool setFrontSideShadeBeamDiffuseSolarTransmittance(double frontSideShadeBeamDiffuseSolarTransmittance);

    double backSideShadeBeamDiffuseSolarTransmittance() const;
    bool setBackSideShadeBeamDiffuseSolarTransmittance(double backSideShadeBeamDiffuseSolarTransmittance);

    double frontSideShadeBeamDiffuseSolarReflectance() const;
    bool setFrontSideShadeBeamDiffuseSolarReflectance(double frontSideShadeBeamDiffuseSolarReflectance);

    double backSideShadeBeamDiffuseSolarReflectance() const;
    bool setBackSideShadeBeamDiffuseSolarReflectance(double backSideShadeBeamDiffuseSolarReflectance);

    boost::optional<double> shadeBeamBeamVisibleTransmittanceAtNormalIncidence() const;
    bool setShadeBeamBeamVisibleTransmittanceAtNormalIncidence(double shadeBeamBeamVisibleTransmittanceAtNormalIncidence);

    boost::optional<double> shadeBeamDiffuseVisibleTransmittanceAtNormalIncidence() const;
    bool setShadeBeamDiffuseVisibleTransmittanceAtNormalIncidence(double shadeBeamDiffuseVisibleTransmittanceAtNormalIncidence);

    boost::optional<double> shadeBeamDiffuseVisibleReflectanceAtNormalIncidence() const;
    bool setShadeBeamDiffuseVisibleReflectanceAtNormalIncidence(double shadeBeamDiffuseVisibleReflectanceAtNormalIncidence);

    double shadeMaterialInfraredTransmittance() const;
    bool isShadeMaterialInfraredTransmittanceDefaulted() const;
    bool setShadeMaterialInfraredTransmittance(double shadeMaterialInfraredTransmittance);
    void resetShadeMaterialInfraredTransmittance();

    double frontSideShadeMaterialInfraredEmissivity() const;
    bool isFrontSideShadeMaterialInfraredEmissivityDefaulted() const;
    bool setFrontSideShadeMaterialInfraredEmissivity(double frontSideShadeMaterialInfraredEmissivity);
    void resetFrontSideShadeMaterialInfraredEmissivity();

    double backSideShadeMaterialInfraredEmissivity() const;
    bool isBackSideShadeMaterialInfraredEmissivityDefaulted() const;
    bool setBackSideShadeMaterialInfraredEmissivity(double backSideShadeMaterialInfraredEmissivity);
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
