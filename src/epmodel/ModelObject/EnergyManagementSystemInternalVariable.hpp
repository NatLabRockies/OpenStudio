/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENERGYMANAGEMENTSYSTEMINTERNALVARIABLE_HPP
#define EPMODEL_ENERGYMANAGEMENTSYSTEMINTERNALVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class EnergyManagementSystemInternalVariable_Impl;
}

class EPMODEL_API EnergyManagementSystemInternalVariable : public ModelObject
{
 public:
  explicit EnergyManagementSystemInternalVariable(const Model& model, const std::string& internalDataType);

  virtual ~EnergyManagementSystemInternalVariable() override = default;
  EnergyManagementSystemInternalVariable(const EnergyManagementSystemInternalVariable& other) = default;
  EnergyManagementSystemInternalVariable(EnergyManagementSystemInternalVariable&& other) = default;
  EnergyManagementSystemInternalVariable& operator=(const EnergyManagementSystemInternalVariable&) = default;
  EnergyManagementSystemInternalVariable& operator=(EnergyManagementSystemInternalVariable&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model::EnergyManagementSystemInternalVariable class and scalar accessor names/signatures.
  // - Field Mapping: internalDataIndexKeyName -> EnergyPlus EnergyManagementSystem:InternalVariable, Internal Data Index Key Name.
  // - Field Mapping: internalDataType -> EnergyPlus EnergyManagementSystem:InternalVariable, Internal Data Type.
  // - ForwardTranslator evidence: ForwardTranslateEnergyManagementSystemInternalVariable.cpp writes InternalDataIndexKeyName and InternalDataType from these APIs.
  // - TODO(parity): Add relationship-aware UID substitution behavior (if needed) without changing these scalar API signatures.
  std::string internalDataIndexKeyName() const;
  bool setInternalDataIndexKeyName(const std::string& internalDataIndexKeyName);
  void resetInternalDataIndexKeyName();

  std::string internalDataType() const;
  bool setInternalDataType(const std::string& internalDataType);

 protected:
  using ImplType = detail::EnergyManagementSystemInternalVariable_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit EnergyManagementSystemInternalVariable(std::shared_ptr<detail::EnergyManagementSystemInternalVariable_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
