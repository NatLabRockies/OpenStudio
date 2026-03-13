/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWMATERIALDRAPEEQUIVALENTLAYER_HPP
#define EPMODEL_WINDOWMATERIALDRAPEEQUIVALENTLAYER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class WindowMaterialDrapeEquivalentLayer_Impl;
  }

  class EPMODEL_API WindowMaterialDrapeEquivalentLayer : public ModelObject
  {
   public:
    explicit WindowMaterialDrapeEquivalentLayer(const Model& model);

    virtual ~WindowMaterialDrapeEquivalentLayer() override = default;
    WindowMaterialDrapeEquivalentLayer(const WindowMaterialDrapeEquivalentLayer& other) = default;
    WindowMaterialDrapeEquivalentLayer(WindowMaterialDrapeEquivalentLayer&& other) = default;
    WindowMaterialDrapeEquivalentLayer& operator=(const WindowMaterialDrapeEquivalentLayer&) = default;
    WindowMaterialDrapeEquivalentLayer& operator=(WindowMaterialDrapeEquivalentLayer&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: IDD-derived WindowMaterial:Drape:EquivalentLayer scalar optics and thermal properties feed these accessors directly.
    // - Field Mapping: WindowMaterial:Drape:EquivalentLayer beam/diffuse/visible/infrared fields map to these getters/setters while the Name field remains on ModelObject.
    // - TODO(parity): Extend relationship helpers once ForwardTranslator coverage for equivalent-layer drapes is available in epmodel.

    /** @name Field Accessors */
    //@{
    double drapeBeamBeamSolarTransmittanceAtNormalIncidence() const;
    bool isDrapeBeamBeamSolarTransmittanceAtNormalIncidenceDefaulted() const;
    bool setDrapeBeamBeamSolarTransmittanceAtNormalIncidence(double drapeBeamBeamSolarTransmittanceAtNormalIncidence);
    void resetDrapeBeamBeamSolarTransmittanceAtNormalIncidence();

    double frontSideDrapeBeamDiffuseSolarTransmittance() const;
    bool setFrontSideDrapeBeamDiffuseSolarTransmittance(double frontSideDrapeBeamDiffuseSolarTransmittance);

    double backSideDrapeBeamDiffuseSolarTransmittance() const;
    bool setBackSideDrapeBeamDiffuseSolarTransmittance(double backSideDrapeBeamDiffuseSolarTransmittance);

    double frontSideDrapeBeamDiffuseSolarReflectance() const;
    bool setFrontSideDrapeBeamDiffuseSolarReflectance(double frontSideDrapeBeamDiffuseSolarReflectance);

    double backSideDrapeBeamDiffuseSolarReflectance() const;
    bool setBackSideDrapeBeamDiffuseSolarReflectance(double backSideDrapeBeamDiffuseSolarReflectance);

    boost::optional<double> drapeBeamBeamVisibleTransmittance() const;
    bool setDrapeBeamBeamVisibleTransmittance(double drapeBeamBeamVisibleTransmittance);
    void resetDrapeBeamBeamVisibleTransmittance();

    boost::optional<double> drapeBeamDiffuseVisibleTransmittance() const;
    bool setDrapeBeamDiffuseVisibleTransmittance(double drapeBeamDiffuseVisibleTransmittance);
    void resetDrapeBeamDiffuseVisibleTransmittance();

    boost::optional<double> drapeBeamDiffuseVisibleReflectance() const;
    bool setDrapeBeamDiffuseVisibleReflectance(double drapeBeamDiffuseVisibleReflectance);
    void resetDrapeBeamDiffuseVisibleReflectance();

    double drapeMaterialInfraredTransmittance() const;
    bool isDrapeMaterialInfraredTransmittanceDefaulted() const;
    bool setDrapeMaterialInfraredTransmittance(double drapeMaterialInfraredTransmittance);
    void resetDrapeMaterialInfraredTransmittance();

    double frontSideDrapeMaterialInfraredEmissivity() const;
    bool isFrontSideDrapeMaterialInfraredEmissivityDefaulted() const;
    bool setFrontSideDrapeMaterialInfraredEmissivity(double frontSideDrapeMaterialInfraredEmissivity);
    void resetFrontSideDrapeMaterialInfraredEmissivity();

    double backSideDrapeMaterialInfraredEmissivity() const;
    bool isBackSideDrapeMaterialInfraredEmissivityDefaulted() const;
    bool setBackSideDrapeMaterialInfraredEmissivity(double backSideDrapeMaterialInfraredEmissivity);
    void resetBackSideDrapeMaterialInfraredEmissivity();

    double widthOfPleatedFabric() const;
    bool isWidthOfPleatedFabricDefaulted() const;
    bool setWidthOfPleatedFabric(double widthOfPleatedFabric);
    void resetWidthOfPleatedFabric();

    double lengthOfPleatedFabric() const;
    bool isLengthOfPleatedFabricDefaulted() const;
    bool setLengthOfPleatedFabric(double lengthOfPleatedFabric);
    void resetLengthOfPleatedFabric();
    //@}

   protected:
    using ImplType = detail::WindowMaterialDrapeEquivalentLayer_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WindowMaterialDrapeEquivalentLayer(std::shared_ptr<detail::WindowMaterialDrapeEquivalentLayer_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
