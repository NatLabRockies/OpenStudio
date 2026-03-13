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

    // Screen Beam-Beam Solar Transmittance
    boost::optional<double> screenBeamBeamSolarTransmittance() const;
    bool isScreenBeamBeamSolarTransmittanceDefaulted() const;
    bool isScreenBeamBeamSolarTransmittanceAutocalculated() const;
    bool setScreenBeamBeamSolarTransmittance(double screenBeamBeamSolarTransmittance);
    void resetScreenBeamBeamSolarTransmittance();
    void autocalculateScreenBeamBeamSolarTransmittance();

    // Screen Beam-Diffuse Solar Transmittance
    double screenBeamDiffuseSolarTransmittance() const;
    bool setScreenBeamDiffuseSolarTransmittance(double screenBeamDiffuseSolarTransmittance);

    // Screen Beam-Diffuse Solar Reflectance
    double screenBeamDiffuseSolarReflectance() const;
    bool setScreenBeamDiffuseSolarReflectance(double screenBeamDiffuseSolarReflectance);

    // Screen Beam-Beam Visible Solar Transmittance
    double screenBeamBeamVisibleSolarTransmittance() const;
    bool setScreenBeamBeamVisibleSolarTransmittance(double screenBeamBeamVisibleSolarTransmittance);

    // Screen Beam-Diffuse Visible Solar Transmittance
    double screenBeamDiffuseVisibleSolarTransmittance() const;
    bool setScreenBeamDiffuseVisibleSolarTransmittance(double screenBeamDiffuseVisibleSolarTransmittance);

    // Screen Beam-Diffuse Visible Solar Reflectance
    double screenBeamDiffuseVisibleSolarReflectance() const;
    bool setScreenBeamDiffuseVisibleSolarReflectance(double screenBeamDiffuseVisibleSolarReflectance);

    // Screen Infrared Transmittance
    double screenInfraredTransmittance() const;
    bool isScreenInfraredTransmittanceDefaulted() const;
    bool setScreenInfraredTransmittance(double screenInfraredTransmittance);
    void resetScreenInfraredTransmittance();

    // Screen Infrared Emissivity
    double screenInfraredEmissivity() const;
    bool isScreenInfraredEmissivityDefaulted() const;
    bool setScreenInfraredEmissivity(double screenInfraredEmissivity);
    void resetScreenInfraredEmissivity();

    // Screen Wire Spacing
    double screenWireSpacing() const;
    bool isScreenWireSpacingDefaulted() const;
    bool setScreenWireSpacing(double screenWireSpacing);
    void resetScreenWireSpacing();

    // Screen Wire Diameter
    double screenWireDiameter() const;
    bool isScreenWireDiameterDefaulted() const;
    bool setScreenWireDiameter(double screenWireDiameter);
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
