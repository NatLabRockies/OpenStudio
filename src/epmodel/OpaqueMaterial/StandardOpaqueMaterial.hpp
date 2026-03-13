/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_STANDARDOPAQUEMATERIAL_HPP
#define EPMODEL_STANDARDOPAQUEMATERIAL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

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

  class EPMODEL_API StandardOpaqueMaterial : public ModelObject
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

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model::StandardOpaqueMaterial scalar accessor names/signatures.
    // - Field Mapping: roughness/thickness/conductivity/density/specificHeat and thermal/solar/visible absorptance APIs map directly to E+ Material fields.
    // - Field Mapping: thermalConductivity aliases Conductivity and thermalConductance/resistivity/resistance are derived scalar transforms over mapped fields.
    // - ForwardTranslator evidence: ForwardTranslateStandardOpaqueMaterial.cpp translates these scalar APIs directly to EnergyPlus Material fields.
    // - Field Mapping: material-property child object relationships (phase change/EMPD) are intentionally excluded from this scalar-only scaffold pass.
    // - TODO(parity): Add non-scalar material-property relationship APIs in a dedicated parity pass.
    double thermalConductivity() const;
    bool setThermalConductivity(double value);

    double thermalConductance() const;
    bool setThermalConductance(double value);

    double thermalResistivity() const;
    bool setThermalResistivity(double value);

    double thermalResistance() const;
    bool setThermalResistance(double value);

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
