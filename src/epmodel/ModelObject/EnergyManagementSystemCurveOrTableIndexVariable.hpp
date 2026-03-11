/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENERGYMANAGEMENTSYSTEMCURVEORTABLEINDEXVARIABLE_HPP
#define EPMODEL_ENERGYMANAGEMENTSYSTEMCURVEORTABLEINDEXVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class EnergyManagementSystemCurveOrTableIndexVariable_Impl;
}

class EPMODEL_API EnergyManagementSystemCurveOrTableIndexVariable : public ModelObject
{
 public:
  explicit EnergyManagementSystemCurveOrTableIndexVariable(const Model& model);

  virtual ~EnergyManagementSystemCurveOrTableIndexVariable() override = default;
  EnergyManagementSystemCurveOrTableIndexVariable(const EnergyManagementSystemCurveOrTableIndexVariable& other) = default;
  EnergyManagementSystemCurveOrTableIndexVariable(EnergyManagementSystemCurveOrTableIndexVariable&& other) = default;
  EnergyManagementSystemCurveOrTableIndexVariable& operator=(const EnergyManagementSystemCurveOrTableIndexVariable&) = default;
  EnergyManagementSystemCurveOrTableIndexVariable& operator=(EnergyManagementSystemCurveOrTableIndexVariable&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model::EnergyManagementSystemCurveOrTableIndexVariable class naming.
  // - Field Mapping: EnergyPlus field Curveor Table Object Name is relationship-like and intentionally excluded from scalar accessor scaffold.
  // - ForwardTranslator evidence: ForwardTranslateEnergyManagementSystemCurveOrTableIndexVariable.cpp writes CurveorTableObjectName from modelObject.curveOrTableObject().
  // - TODO(parity): Add relationship APIs incrementally (curveOrTableObject/setCurveOrTableObject) without changing scalar scaffolding conventions.

 protected:
  using ImplType = detail::EnergyManagementSystemCurveOrTableIndexVariable_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit EnergyManagementSystemCurveOrTableIndexVariable(std::shared_ptr<detail::EnergyManagementSystemCurveOrTableIndexVariable_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
