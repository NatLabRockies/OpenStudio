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
  explicit StandardOpaqueMaterial(const Model& model, const std::string& roughness = "Smooth", double thickness = 0.1,
                                  double conductivity = 0.1, double density = 0.1, double specificHeat = 1400.0);

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
  double thermalConductance() const;
  double thermalResistivity() const;
  double thermalResistance() const;

  boost::optional<double> thermalReflectance() const;
  boost::optional<double> solarReflectance() const;
  boost::optional<double> visibleReflectance() const;

  std::string roughness() const;
  double thickness() const;
  double conductivity() const;
  double density() const;
  double specificHeat() const;

  double thermalAbsorptance() const;
  bool isThermalAbsorptanceDefaulted() const;

  double solarAbsorptance() const;
  bool isSolarAbsorptanceDefaulted() const;

  double visibleAbsorptance() const;
  bool isVisibleAbsorptanceDefaulted() const;

  bool setThermalConductivity(double value);
  bool setThermalConductance(double value);
  bool setThermalResistivity(double value);
  bool setThermalResistance(double value);

  bool setThermalAbsorptance(boost::optional<double> value);
  bool setThermalReflectance(boost::optional<double> value);

  bool setSolarAbsorptance(boost::optional<double> value);
  bool setSolarReflectance(boost::optional<double> value);

  bool setVisibleAbsorptance(boost::optional<double> value);
  bool setVisibleReflectance(boost::optional<double> value);

  bool setRoughness(const std::string& roughness);
  bool setThickness(double thickness);
  bool setConductivity(double conductivity);
  bool setDensity(double density);
  bool setSpecificHeat(double specificHeat);

  bool setThermalAbsorptance(double thermalAbsorptance);
  void resetThermalAbsorptance();

  bool setSolarAbsorptance(double solarAbsorptance);
  void resetSolarAbsorptance();

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
