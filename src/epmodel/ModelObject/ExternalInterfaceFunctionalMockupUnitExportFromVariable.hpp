/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITEXPORTFROMVARIABLE_HPP
#define EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITEXPORTFROMVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ExternalInterfaceFunctionalMockupUnitExportFromVariable_Impl;
}

class EPMODEL_API ExternalInterfaceFunctionalMockupUnitExportFromVariable : public ModelObject
{
 public:
  explicit ExternalInterfaceFunctionalMockupUnitExportFromVariable(const Model& model, const std::string& outputVariableIndexKeyName,
                                                                   const std::string& outputVariableName, const std::string& fMUVariableName);

  virtual ~ExternalInterfaceFunctionalMockupUnitExportFromVariable() override = default;
  ExternalInterfaceFunctionalMockupUnitExportFromVariable(const ExternalInterfaceFunctionalMockupUnitExportFromVariable& other) = default;
  ExternalInterfaceFunctionalMockupUnitExportFromVariable(ExternalInterfaceFunctionalMockupUnitExportFromVariable&& other) = default;
  ExternalInterfaceFunctionalMockupUnitExportFromVariable& operator=(const ExternalInterfaceFunctionalMockupUnitExportFromVariable&) = default;
  ExternalInterfaceFunctionalMockupUnitExportFromVariable& operator=(ExternalInterfaceFunctionalMockupUnitExportFromVariable&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::ExternalInterfaceFunctionalMockupUnitExportFromVariable scalar accessor names/signatures.
  // - Field Mapping: outputVariableIndexKeyName -> ExternalInterface:FunctionalMockupUnitExport:From:Variable,
  //   Output Variable Index Key Name.
  // - Field Mapping: outputVariableName -> ExternalInterface:FunctionalMockupUnitExport:From:Variable, Output Variable Name.
  // - Field Mapping: fMUVariableName -> ExternalInterface:FunctionalMockupUnitExport:From:Variable, FMU Variable Name.
  // - TODO(parity): Revisit only if upstream model API changes for FMU export parity milestones.
  std::string outputVariableIndexKeyName() const;
  bool setOutputVariableIndexKeyName(const std::string& outputVariableIndexKeyName);

  std::string outputVariableName() const;
  bool setOutputVariableName(const std::string& outputVariableName);

  std::string fMUVariableName() const;
  bool setFMUVariableName(const std::string& fMUVariableName);

 protected:
  using ImplType = detail::ExternalInterfaceFunctionalMockupUnitExportFromVariable_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ExternalInterfaceFunctionalMockupUnitExportFromVariable(
    std::shared_ptr<detail::ExternalInterfaceFunctionalMockupUnitExportFromVariable_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
