/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_SHADE_HPP
#define EPMODEL_SHADE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class Shade_Impl;
  }

  class EPMODEL_API Shade : public ModelObject
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
    double thermalConductance() const;
    double thermalResistivity() const;
    double thermalResistance() const;

    double solarTransmittance() const;
    double solarReflectance() const;
    double visibleTransmittance() const;
    double visibleReflectance() const;
    double thermalHemisphericalEmissivity() const;
    double thermalTransmittance() const;
    double solarAbsorptance() const;
    double visibleAbsorptance() const;

    double thickness() const;
    double conductivity() const;

    double shadetoGlassDistance() const;
    bool isShadetoGlassDistanceDefaulted() const;

    double topOpeningMultiplier() const;
    bool isTopOpeningMultiplierDefaulted() const;

    double bottomOpeningMultiplier() const;
    bool isBottomOpeningMultiplierDefaulted() const;

    double leftSideOpeningMultiplier() const;
    bool isLeftSideOpeningMultiplierDefaulted() const;

    double rightSideOpeningMultiplier() const;
    bool isRightSideOpeningMultiplierDefaulted() const;

    double airflowPermeability() const;
    bool isAirflowPermeabilityDefaulted() const;

    bool setThermalConductivity(double value);
    bool setThermalConductance(double value);
    bool setThermalResistivity(double value);
    bool setThermalResistance(double value);

    bool setThermalTransmittance(double thermalTransmittance);
    bool setSolarTransmittance(double solarTransmittance);
    bool setSolarReflectance(double solarReflectance);
    bool setVisibleTransmittance(double visibleTransmittance);
    bool setVisibleReflectance(double visibleReflectance);
    bool setThermalHemisphericalEmissivity(double thermalHemisphericalEmissivity);
    bool setThickness(double thickness);
    bool setConductivity(double conductivity);

    bool setShadetoGlassDistance(double shadetoGlassDistance);
    void resetShadetoGlassDistance();

    bool setTopOpeningMultiplier(double topOpeningMultiplier);
    void resetTopOpeningMultiplier();

    bool setBottomOpeningMultiplier(double bottomOpeningMultiplier);
    void resetBottomOpeningMultiplier();

    bool setLeftSideOpeningMultiplier(double leftSideOpeningMultiplier);
    void resetLeftSideOpeningMultiplier();

    bool setRightSideOpeningMultiplier(double rightSideOpeningMultiplier);
    void resetRightSideOpeningMultiplier();

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
