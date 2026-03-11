/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MASSLESSOPAQUEMATERIAL_HPP
#define EPMODEL_MASSLESSOPAQUEMATERIAL_HPP

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
class MasslessOpaqueMaterial_Impl;
}

class EPMODEL_API MasslessOpaqueMaterial : public ModelObject
{
 public:
  explicit MasslessOpaqueMaterial(const Model& model, const std::string& roughness = "Smooth", double thermalResistance = 0.1);

  virtual ~MasslessOpaqueMaterial() override = default;
  MasslessOpaqueMaterial(const MasslessOpaqueMaterial& other) = default;
  MasslessOpaqueMaterial(MasslessOpaqueMaterial&& other) = default;
  MasslessOpaqueMaterial& operator=(const MasslessOpaqueMaterial&) = default;
  MasslessOpaqueMaterial& operator=(MasslessOpaqueMaterial&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> roughnessValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model::MasslessOpaqueMaterial scalar accessor names/signatures.
  // - Field Mapping: roughness, thermalResistance, and thermal/solar/visible absorptance APIs map directly to E+ Material:NoMass fields.
  // - ForwardTranslator evidence: ForwardTranslateMasslessOpaqueMaterial.cpp writes these scalar APIs directly to Material:NoMass fields.
  // - Field Mapping: material-property child-object relationships are intentionally excluded from this scalar-only scaffold pass.
  // - TODO(parity): Add non-scalar material-property relationship APIs in a dedicated parity pass.
  std::string roughness() const;
  double thermalResistance() const;

  boost::optional<double> thermalAbsorptance() const;
  bool isThermalAbsorptanceDefaulted() const;

  boost::optional<double> solarAbsorptance() const;
  bool isSolarAbsorptanceDefaulted() const;

  boost::optional<double> visibleAbsorptance() const;
  bool isVisibleAbsorptanceDefaulted() const;

  bool setRoughness(const std::string& roughness);
  bool setThermalResistance(double thermalResistance);

  bool setThermalAbsorptance(double thermalAbsorptance);
  void resetThermalAbsorptance();

  bool setSolarAbsorptance(double solarAbsorptance);
  void resetSolarAbsorptance();

  bool setVisibleAbsorptance(double visibleAbsorptance);
  void resetVisibleAbsorptance();

 protected:
  using ImplType = detail::MasslessOpaqueMaterial_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit MasslessOpaqueMaterial(std::shared_ptr<detail::MasslessOpaqueMaterial_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
