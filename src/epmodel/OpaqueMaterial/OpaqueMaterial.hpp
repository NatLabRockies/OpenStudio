/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OPAQUEMATERIAL_HPP
#define EPMODEL_OPAQUEMATERIAL_HPP

#include "EPModelAPI.hpp"
#include "Material/Material.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  namespace detail {
    class OpaqueMaterial_Impl;
  }

  /** An OpaqueMaterial is a Material that serves as a base class for all opaque layers in
   *  LayeredConstructions. */
  class EPMODEL_API OpaqueMaterial : public Material
  {
   public:
    virtual ~OpaqueMaterial() override = default;
    OpaqueMaterial(const OpaqueMaterial& other) = default;
    OpaqueMaterial(OpaqueMaterial&& other) = default;
    OpaqueMaterial& operator=(const OpaqueMaterial&) = default;
    OpaqueMaterial& operator=(OpaqueMaterial&&) = default;

    /** The conductivity of the material in W/m*K. */
    double thermalConductivity() const;
    bool setThermalConductivity(double value);

    /** The conductance of the material in W/m^2*K. */
    double thermalConductance() const;
    bool setThermalConductance(double value);

    /** The resistivity of the material in m*K/W. */
    double thermalResistivity() const;
    bool setThermalResistivity(double value);

    /** The resistance of the material in m^2*K/W. */
    double thermalResistance() const;
    bool setThermalResistance(double value);

    /** Thermal absorptance of the material (dimensionless fraction). */
    double thermalAbsorptance() const;
    bool setThermalAbsorptance(double value);

    /** Thermal reflectance of the material (dimensionless fraction). */
    boost::optional<double> thermalReflectance() const;
    bool setThermalReflectance(boost::optional<double> value);

    /** Solar absorptance of the material (dimensionless fraction). */
    double solarAbsorptance() const;
    bool setSolarAbsorptance(boost::optional<double> value);

    /** Solar reflectance of the material (dimensionless fraction). */
    boost::optional<double> solarReflectance() const;
    bool setSolarReflectance(boost::optional<double> value);

    /** Visible absorptance of the material (dimensionless fraction). */
    double visibleAbsorptance() const;
    bool setVisibleAbsorptance(boost::optional<double> value);

    /** Visible reflectance of the material (dimensionless fraction). */
    boost::optional<double> visibleReflectance() const;
    bool setVisibleReflectance(boost::optional<double> value);

    /** Energy it takes to raise the temperature of this material 1 K (J/m^2*K). Equal to
     *  specificHeat() * density() * thickness(). */
    boost::optional<double> heatCapacity() const;

   protected:
    using ImplType = detail::OpaqueMaterial_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    OpaqueMaterial(IddObjectType type, const Model& model);

    explicit OpaqueMaterial(std::shared_ptr<detail::OpaqueMaterial_Impl> impl);

   private:
    REGISTER_LOGGER("openstudio.epmodel.OpaqueMaterial");
  };

  using OptionalOpaqueMaterial = boost::optional<OpaqueMaterial>;
  using OpaqueMaterialVector = std::vector<OpaqueMaterial>;

}  // namespace epmodel
}  // namespace openstudio

#endif
