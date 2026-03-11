/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORTFROMVARIABLE_HPP
#define EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORTFROMVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl;
}

class EPMODEL_API ExternalInterfaceFunctionalMockupUnitImportFromVariable : public ModelObject
{
 public:
  explicit ExternalInterfaceFunctionalMockupUnitImportFromVariable(const Model& model, const std::string& outputVariableIndexKeyName,
                                                                   const std::string& outputVariableName,
                                                                   const std::string& fMUInstanceName, const std::string& fMUVariableName);

  virtual ~ExternalInterfaceFunctionalMockupUnitImportFromVariable() override = default;
  ExternalInterfaceFunctionalMockupUnitImportFromVariable(const ExternalInterfaceFunctionalMockupUnitImportFromVariable& other) = default;
  ExternalInterfaceFunctionalMockupUnitImportFromVariable(ExternalInterfaceFunctionalMockupUnitImportFromVariable&& other) = default;
  ExternalInterfaceFunctionalMockupUnitImportFromVariable& operator=(const ExternalInterfaceFunctionalMockupUnitImportFromVariable&) = default;
  ExternalInterfaceFunctionalMockupUnitImportFromVariable& operator=(ExternalInterfaceFunctionalMockupUnitImportFromVariable&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::ExternalInterfaceFunctionalMockupUnitImportFromVariable scalar accessor names/signatures.
  // - Field Mapping: outputVariableIndexKeyName -> ExternalInterface:FunctionalMockupUnitImport:From:Variable,
  //   Output:Variable Index Key Name.
  // - Field Mapping: outputVariableName -> ExternalInterface:FunctionalMockupUnitImport:From:Variable, Output:Variable Name.
  // - Field Mapping: fMUInstanceName -> ExternalInterface:FunctionalMockupUnitImport:From:Variable, FMU Instance Name.
  // - Field Mapping: fMUVariableName -> ExternalInterface:FunctionalMockupUnitImport:From:Variable, FMU Variable Name.
  // - Field Mapping: fMUFile / setFMUFile are relationship APIs in openstudio::model and excluded from scalar scaffold.
  // - ForwardTranslator evidence: ForwardTranslateExternalInterfaceFunctionalMockupUnitImportFromVariable.cpp writes
  //   FMU File Name from modelObject.fMUFile().fMUFileName().
  // - TODO(parity): Add relationship APIs incrementally without changing preserved scalar signatures.
  std::string outputVariableIndexKeyName() const;
  bool setOutputVariableIndexKeyName(const std::string& outputVariableIndexKeyName);

  std::string outputVariableName() const;
  bool setOutputVariableName(const std::string& outputVariableName);

  std::string fMUInstanceName() const;
  bool setFMUInstanceName(const std::string& fMUInstanceName);

  std::string fMUVariableName() const;
  bool setFMUVariableName(const std::string& fMUVariableName);

 protected:
  using ImplType = detail::ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ExternalInterfaceFunctionalMockupUnitImportFromVariable(
    std::shared_ptr<detail::ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
