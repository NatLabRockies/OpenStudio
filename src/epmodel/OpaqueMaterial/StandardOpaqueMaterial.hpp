/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_STANDARDOPAQUEMATERIAL_HPP
#define EPMODEL_STANDARDOPAQUEMATERIAL_HPP

#include "EPModelAPI.hpp"
#include "OpaqueMaterial/OpaqueMaterial.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class StandardOpaqueMaterial_Impl;
  }

  /** \brief Represents a conventional opaque material layer.
   *
   * \par EnergyPlus object
   * \epobject{group-surface-construction-elements.html#material,Material}.
   *
   * \par Important behavior
   * Thermal conductance, resistivity, resistance, and heat capacity are derived
   * from the persisted conductivity, density, specific heat, and thickness
   * fields. They are not independent EnergyPlus fields.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::StandardOpaqueMaterial</code>. The scalar thermal
   * and optical methods have the same public meaning. Model's phase-change and
   * EMPD material-property relationships are not available.
   *
   * \par Known limitations
   * Only the direct <code>Material</code> scalar fields are exposed; material
   * property child objects cannot be assigned here.
   */
  class EPMODEL_API StandardOpaqueMaterial : public OpaqueMaterial
  {
   public:
    explicit StandardOpaqueMaterial(const Model& model, const std::string& roughness = "Smooth", double thickness = 0.1, double conductivity = 0.1,
                                    double density = 0.1, double specificHeat = 1400.0);

    virtual ~StandardOpaqueMaterial() override = default;
    StandardOpaqueMaterial(const StandardOpaqueMaterial& other) = default;
    StandardOpaqueMaterial(StandardOpaqueMaterial&& other) = default;
    StandardOpaqueMaterial& operator=(const StandardOpaqueMaterial&) = default;
    StandardOpaqueMaterial& operator=(StandardOpaqueMaterial&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> roughnessValues();

    double thermalConductivity() const;
    bool setThermalConductivity(double value);

    double thermalConductance() const;
    bool setThermalConductance(double value);

    double thermalResistivity() const;
    bool setThermalResistivity(double value);

    boost::optional<double> thermalReflectance() const;
    bool setThermalReflectance(boost::optional<double> value);

    boost::optional<double> solarReflectance() const;
    bool setSolarReflectance(boost::optional<double> value);

    boost::optional<double> visibleReflectance() const;
    bool setVisibleReflectance(boost::optional<double> value);

    std::string roughness() const;
    bool setRoughness(const std::string& roughness);

    double thickness() const;
    bool setThickness(double thickness);

    double conductivity() const;
    bool setConductivity(double conductivity);

    double density() const;
    bool setDensity(double density);

    double specificHeat() const;
    bool setSpecificHeat(double specificHeat);

    double thermalAbsorptance() const;
    bool isThermalAbsorptanceDefaulted() const;
    bool setThermalAbsorptance(boost::optional<double> value);
    bool setThermalAbsorptance(double thermalAbsorptance);
    void resetThermalAbsorptance();

    double solarAbsorptance() const;
    bool isSolarAbsorptanceDefaulted() const;
    bool setSolarAbsorptance(boost::optional<double> value);
    bool setSolarAbsorptance(double solarAbsorptance);
    void resetSolarAbsorptance();

    double visibleAbsorptance() const;
    bool isVisibleAbsorptanceDefaulted() const;
    bool setVisibleAbsorptance(boost::optional<double> value);
    bool setVisibleAbsorptance(double visibleAbsorptance);
    void resetVisibleAbsorptance();

    boost::optional<double> heatCapacity() const;

   protected:
    using ImplType = detail::StandardOpaqueMaterial_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit StandardOpaqueMaterial(std::shared_ptr<detail::StandardOpaqueMaterial_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
