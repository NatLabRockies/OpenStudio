/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORTTOVARIABLE_HPP
#define EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORTTOVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl;
  }

  class EPMODEL_API ExternalInterfaceFunctionalMockupUnitImportToVariable : public ModelObject
  {
   public:
    explicit ExternalInterfaceFunctionalMockupUnitImportToVariable(const Model& model);

    virtual ~ExternalInterfaceFunctionalMockupUnitImportToVariable() override = default;
    ExternalInterfaceFunctionalMockupUnitImportToVariable(const ExternalInterfaceFunctionalMockupUnitImportToVariable& other) = default;
    ExternalInterfaceFunctionalMockupUnitImportToVariable(ExternalInterfaceFunctionalMockupUnitImportToVariable&& other) = default;
    ExternalInterfaceFunctionalMockupUnitImportToVariable& operator=(const ExternalInterfaceFunctionalMockupUnitImportToVariable&) = default;
    ExternalInterfaceFunctionalMockupUnitImportToVariable& operator=(ExternalInterfaceFunctionalMockupUnitImportToVariable&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::ExternalInterfaceFunctionalMockupUnitImportToVariable scalar accessor names/signatures.
    // - Field Mapping: fMUInstanceName -> ExternalInterface:FunctionalMockupUnitImport:To:Variable, FMU Instance Name.
    // - Field Mapping: fMUVariableName -> ExternalInterface:FunctionalMockupUnitImport:To:Variable, FMU Variable Name.
    // - Field Mapping: initialValue -> ExternalInterface:FunctionalMockupUnitImport:To:Variable, Initial Value.
    // - Field Mapping: fMUFile / setFMUFile are relationship APIs and excluded from scalar scaffold.
    // - ForwardTranslator evidence: ForwardTranslateExternalInterfaceFunctionalMockupUnitImportToVariable.cpp writes these scalar fields directly.
    // - TODO(parity): Add relationship APIs incrementally without changing preserved scalar signatures.
    std::string fMUInstanceName() const;
    bool setFMUInstanceName(const std::string& fMUInstanceName);

    std::string fMUVariableName() const;
    bool setFMUVariableName(const std::string& fMUVariableName);

    double initialValue() const;
    bool setInitialValue(double initialValue);

   protected:
    using ImplType = detail::ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ExternalInterfaceFunctionalMockupUnitImportToVariable(
      std::shared_ptr<detail::ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
