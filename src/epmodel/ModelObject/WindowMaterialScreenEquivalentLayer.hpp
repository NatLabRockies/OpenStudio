/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWMATERIALSCREENEQUIVALENTLAYER_HPP
#define EPMODEL_WINDOWMATERIALSCREENEQUIVALENTLAYER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class WindowMaterialScreenEquivalentLayer_Impl;
  }

  class EPMODEL_API WindowMaterialScreenEquivalentLayer : public ModelObject
  {
   public:
    explicit WindowMaterialScreenEquivalentLayer(const Model& model);

    virtual ~WindowMaterialScreenEquivalentLayer() override = default;
    WindowMaterialScreenEquivalentLayer(const WindowMaterialScreenEquivalentLayer& other) = default;
    WindowMaterialScreenEquivalentLayer(WindowMaterialScreenEquivalentLayer&& other) = default;
    WindowMaterialScreenEquivalentLayer& operator=(const WindowMaterialScreenEquivalentLayer&) = default;
    WindowMaterialScreenEquivalentLayer& operator=(WindowMaterialScreenEquivalentLayer&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Equivalent-layer screen optics (beam/diffuse transmittance and reflectance, infrared transmittance/emissivity,
    //   and wire geometry) map directly to WindowMaterial:Screen:EquivalentLayer scalar fields.
    // - Field Mapping: The Screen Beam-Beam Solar Transmittance field is autocalculatable while the remaining optics and
    //   geometry scalars mirror the IDD naming; Name implicitly aligns with WindowEquivalentLayerMaterialNames.

    boost::optional<double> screenBeamBeamSolarTransmittance() const;
    bool isScreenBeamBeamSolarTransmittanceDefaulted() const;
    bool isScreenBeamBeamSolarTransmittanceAutocalculated() const;

    double screenBeamDiffuseSolarTransmittance() const;
    double screenBeamDiffuseSolarReflectance() const;
    double screenBeamBeamVisibleSolarTransmittance() const;
    double screenBeamDiffuseVisibleSolarTransmittance() const;
    double screenBeamDiffuseVisibleSolarReflectance() const;

    double screenInfraredTransmittance() const;
    bool isScreenInfraredTransmittanceDefaulted() const;

    double screenInfraredEmissivity() const;
    bool isScreenInfraredEmissivityDefaulted() const;

    double screenWireSpacing() const;
    bool isScreenWireSpacingDefaulted() const;

    double screenWireDiameter() const;
    bool isScreenWireDiameterDefaulted() const;

    bool setScreenBeamBeamSolarTransmittance(double screenBeamBeamSolarTransmittance);
    bool setScreenBeamDiffuseSolarTransmittance(double screenBeamDiffuseSolarTransmittance);
    bool setScreenBeamDiffuseSolarReflectance(double screenBeamDiffuseSolarReflectance);
    bool setScreenBeamBeamVisibleSolarTransmittance(double screenBeamBeamVisibleSolarTransmittance);
    bool setScreenBeamDiffuseVisibleSolarTransmittance(double screenBeamDiffuseVisibleSolarTransmittance);
    bool setScreenBeamDiffuseVisibleSolarReflectance(double screenBeamDiffuseVisibleSolarReflectance);

    bool setScreenInfraredTransmittance(double screenInfraredTransmittance);
    bool setScreenInfraredEmissivity(double screenInfraredEmissivity);
    bool setScreenWireSpacing(double screenWireSpacing);
    bool setScreenWireDiameter(double screenWireDiameter);

    void resetScreenBeamBeamSolarTransmittance();
    void autocalculateScreenBeamBeamSolarTransmittance();

    void resetScreenInfraredTransmittance();
    void resetScreenInfraredEmissivity();
    void resetScreenWireSpacing();
    void resetScreenWireDiameter();

   protected:
    using ImplType = detail::WindowMaterialScreenEquivalentLayer_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WindowMaterialScreenEquivalentLayer(std::shared_ptr<detail::WindowMaterialScreenEquivalentLayer_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
