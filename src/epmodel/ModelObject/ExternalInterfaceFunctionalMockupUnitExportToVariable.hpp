/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITEXPORTTOVARIABLE_HPP
#define EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITEXPORTTOVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ExternalInterfaceFunctionalMockupUnitExportToVariable_Impl;
  }

  class EPMODEL_API ExternalInterfaceFunctionalMockupUnitExportToVariable : public ModelObject
  {
   public:
    explicit ExternalInterfaceFunctionalMockupUnitExportToVariable(const Model& model, const std::string& fMUVariableName, double initialValue);

    virtual ~ExternalInterfaceFunctionalMockupUnitExportToVariable() override = default;
    ExternalInterfaceFunctionalMockupUnitExportToVariable(const ExternalInterfaceFunctionalMockupUnitExportToVariable& other) = default;
    ExternalInterfaceFunctionalMockupUnitExportToVariable(ExternalInterfaceFunctionalMockupUnitExportToVariable&& other) = default;
    ExternalInterfaceFunctionalMockupUnitExportToVariable& operator=(const ExternalInterfaceFunctionalMockupUnitExportToVariable&) = default;
    ExternalInterfaceFunctionalMockupUnitExportToVariable& operator=(ExternalInterfaceFunctionalMockupUnitExportToVariable&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::ExternalInterfaceFunctionalMockupUnitExportToVariable scalar accessor names/signatures.
    // - Field Mapping: fMUVariableName -> ExternalInterface:FunctionalMockupUnitExport:To:Variable, FMU Variable Name.
    // - Field Mapping: initialValue -> ExternalInterface:FunctionalMockupUnitExport:To:Variable, Initial Value.
    // - ForwardTranslator evidence: ForwardTranslateExternalInterfaceFunctionalMockupUnitExportToVariable.cpp writes FMU Variable Name and
    //   Initial Value directly from these APIs.
    // - TODO(parity): Revisit only if upstream model API changes for FMU export parity milestones.
    std::string fMUVariableName() const;
    bool setFMUVariableName(const std::string& fMUVariableName);

    double initialValue() const;
    bool setInitialValue(double initialValue);

   protected:
    using ImplType = detail::ExternalInterfaceFunctionalMockupUnitExportToVariable_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ExternalInterfaceFunctionalMockupUnitExportToVariable(
      std::shared_ptr<detail::ExternalInterfaceFunctionalMockupUnitExportToVariable_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
