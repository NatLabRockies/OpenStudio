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

    /** @name Getters */
    //@{
    double drapeBeamBeamSolarTransmittanceAtNormalIncidence() const;
    bool isDrapeBeamBeamSolarTransmittanceAtNormalIncidenceDefaulted() const;

    double frontSideDrapeBeamDiffuseSolarTransmittance() const;
    double backSideDrapeBeamDiffuseSolarTransmittance() const;
    double frontSideDrapeBeamDiffuseSolarReflectance() const;
    double backSideDrapeBeamDiffuseSolarReflectance() const;

    boost::optional<double> drapeBeamBeamVisibleTransmittance() const;
    boost::optional<double> drapeBeamDiffuseVisibleTransmittance() const;
    boost::optional<double> drapeBeamDiffuseVisibleReflectance() const;

    double drapeMaterialInfraredTransmittance() const;
    bool isDrapeMaterialInfraredTransmittanceDefaulted() const;

    double frontSideDrapeMaterialInfraredEmissivity() const;
    bool isFrontSideDrapeMaterialInfraredEmissivityDefaulted() const;

    double backSideDrapeMaterialInfraredEmissivity() const;
    bool isBackSideDrapeMaterialInfraredEmissivityDefaulted() const;

    double widthOfPleatedFabric() const;
    bool isWidthOfPleatedFabricDefaulted() const;

    double lengthOfPleatedFabric() const;
    bool isLengthOfPleatedFabricDefaulted() const;
    //@}

    /** @name Setters */
    //@{
    bool setDrapeBeamBeamSolarTransmittanceAtNormalIncidence(double drapeBeamBeamSolarTransmittanceAtNormalIncidence);
    bool setFrontSideDrapeBeamDiffuseSolarTransmittance(double frontSideDrapeBeamDiffuseSolarTransmittance);
    bool setBackSideDrapeBeamDiffuseSolarTransmittance(double backSideDrapeBeamDiffuseSolarTransmittance);
    bool setFrontSideDrapeBeamDiffuseSolarReflectance(double frontSideDrapeBeamDiffuseSolarReflectance);
    bool setBackSideDrapeBeamDiffuseSolarReflectance(double backSideDrapeBeamDiffuseSolarReflectance);
    bool setDrapeBeamBeamVisibleTransmittance(double drapeBeamBeamVisibleTransmittance);
    bool setDrapeBeamDiffuseVisibleTransmittance(double drapeBeamDiffuseVisibleTransmittance);
    bool setDrapeBeamDiffuseVisibleReflectance(double drapeBeamDiffuseVisibleReflectance);
    bool setDrapeMaterialInfraredTransmittance(double drapeMaterialInfraredTransmittance);
    bool setFrontSideDrapeMaterialInfraredEmissivity(double frontSideDrapeMaterialInfraredEmissivity);
    bool setBackSideDrapeMaterialInfraredEmissivity(double backSideDrapeMaterialInfraredEmissivity);
    bool setWidthOfPleatedFabric(double widthOfPleatedFabric);
    bool setLengthOfPleatedFabric(double lengthOfPleatedFabric);

    void resetDrapeBeamBeamSolarTransmittanceAtNormalIncidence();
    void resetDrapeBeamBeamVisibleTransmittance();
    void resetDrapeBeamDiffuseVisibleTransmittance();
    void resetDrapeBeamDiffuseVisibleReflectance();
    void resetDrapeMaterialInfraredTransmittance();
    void resetFrontSideDrapeMaterialInfraredEmissivity();
    void resetBackSideDrapeMaterialInfraredEmissivity();
    void resetWidthOfPleatedFabric();
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
