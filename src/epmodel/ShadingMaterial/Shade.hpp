/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_SHADE_HPP
#define EPMODEL_SHADE_HPP

#include "EPModelAPI.hpp"
#include "ShadingMaterial/ShadingMaterial.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class Shade_Impl;
  }

  class EPMODEL_API Shade : public ShadingMaterial
  {
   public:
    explicit Shade(const Model& model);

    virtual ~Shade() override = default;
    Shade(const Shade& other) = default;
    Shade(Shade&& other) = default;
    Shade& operator=(const Shade&) = default;
    Shade& operator=(Shade&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Mirror openstudio::model::Shade scalar accessors (thermals and optical coefficients) so the epmodel facade stays
    //         compatible with the existing public surface/shading material API.
    // - Field Mapping: Each accessor reads/writes the EnergyPlus WindowMaterial:Shade fields consumed by
    //         energyplus::ForwardTranslator::translateShade (ForwardTranslator/ForwardTranslateShade.cpp).
    // - TODO(parity): Keep the derived absorptance/thermal helpers aligned with the model counterpart as the field semantics evolve.
    double thermalConductivity() const;
    bool setThermalConductivity(double value);

    double thermalConductance() const;
    bool setThermalConductance(double value);

    double thermalResistivity() const;
    bool setThermalResistivity(double value);

    double thermalResistance() const;
    bool setThermalResistance(double value);

    double solarTransmittance() const;
    bool setSolarTransmittance(double solarTransmittance);

    double solarReflectance() const;
    bool setSolarReflectance(double solarReflectance);

    double visibleTransmittance() const;
    bool setVisibleTransmittance(double visibleTransmittance);

    double visibleReflectance() const;
    bool setVisibleReflectance(double visibleReflectance);

    double thermalHemisphericalEmissivity() const;
    bool setThermalHemisphericalEmissivity(double thermalHemisphericalEmissivity);

    double thermalTransmittance() const;
    bool setThermalTransmittance(double thermalTransmittance);

    double solarAbsorptance() const;

    double visibleAbsorptance() const;

    double thickness() const;
    bool setThickness(double thickness);

    double conductivity() const;
    bool setConductivity(double conductivity);

    double shadetoGlassDistance() const;
    bool isShadetoGlassDistanceDefaulted() const;
    bool setShadetoGlassDistance(double shadetoGlassDistance);
    void resetShadetoGlassDistance();

    double topOpeningMultiplier() const;
    bool isTopOpeningMultiplierDefaulted() const;
    bool setTopOpeningMultiplier(double topOpeningMultiplier);
    void resetTopOpeningMultiplier();

    double bottomOpeningMultiplier() const;
    bool isBottomOpeningMultiplierDefaulted() const;
    bool setBottomOpeningMultiplier(double bottomOpeningMultiplier);
    void resetBottomOpeningMultiplier();

    double leftSideOpeningMultiplier() const;
    bool isLeftSideOpeningMultiplierDefaulted() const;
    bool setLeftSideOpeningMultiplier(double leftSideOpeningMultiplier);
    void resetLeftSideOpeningMultiplier();

    double rightSideOpeningMultiplier() const;
    bool isRightSideOpeningMultiplierDefaulted() const;
    bool setRightSideOpeningMultiplier(double rightSideOpeningMultiplier);
    void resetRightSideOpeningMultiplier();

    double airflowPermeability() const;
    bool isAirflowPermeabilityDefaulted() const;
    bool setAirflowPermeability(double airflowPermeability);
    void resetAirflowPermeability();

   protected:
    using ImplType = detail::Shade_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class detail::Shade_Impl;

    explicit Shade(std::shared_ptr<detail::Shade_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
