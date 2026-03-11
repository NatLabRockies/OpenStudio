/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MATERIALPROPERTYPHASECHANGE_HPP
#define EPMODEL_MATERIALPROPERTYPHASECHANGE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class MaterialPropertyPhaseChange_Impl;
}

/** MaterialPropertyPhaseChange is a ModelObject that wraps the EnergyPlus IDD object
 * 'MaterialProperty:PhaseChange'. */
class EPMODEL_API MaterialPropertyPhaseChange : public ModelObject
{
 public:
  explicit MaterialPropertyPhaseChange(const Model& model);

  virtual ~MaterialPropertyPhaseChange() override = default;
  MaterialPropertyPhaseChange(const MaterialPropertyPhaseChange& other) = default;
  MaterialPropertyPhaseChange(MaterialPropertyPhaseChange&& other) = default;
  MaterialPropertyPhaseChange& operator=(const MaterialPropertyPhaseChange&) = default;
  MaterialPropertyPhaseChange& operator=(MaterialPropertyPhaseChange&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model::MaterialPropertyPhaseChange scalar accessor names/signatures.
  // - Field Mapping: temperatureCoefficientforThermalConductivity maps to E+ field Temperature Coefficient for Thermal Conductivity.
  // - ForwardTranslator evidence: ForwardTranslateMaterialPropertyPhaseChange.cpp writes
  //   modelObject.temperatureCoefficientforThermalConductivity() to MaterialProperty:PhaseChange
  //   Temperature Coefficient for Thermal Conductivity.
  // - Exclusions: material/materialName relationship and extensible temperature-enthalpy APIs are intentionally excluded in this scalar-only pass.
  // - TODO(parity): Add material relationship and extensible Temperature/Enthalpy APIs in a dedicated relationship/extensible parity pass.
  double temperatureCoefficientforThermalConductivity() const;
  bool isTemperatureCoefficientforThermalConductivityDefaulted() const;

  bool setTemperatureCoefficientforThermalConductivity(double temperatureCoefficientforThermalConductivity);
  void resetTemperatureCoefficientforThermalConductivity();

 protected:
  using ImplType = detail::MaterialPropertyPhaseChange_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit MaterialPropertyPhaseChange(std::shared_ptr<detail::MaterialPropertyPhaseChange_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
