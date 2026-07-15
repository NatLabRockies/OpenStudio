/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORTTOACTUATOR_HPP
#define EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORTTOACTUATOR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl;
  }

  class EPMODEL_API ExternalInterfaceFunctionalMockupUnitImportToActuator : public ModelObject
  {
   public:
    explicit ExternalInterfaceFunctionalMockupUnitImportToActuator(const Model& model);

    virtual ~ExternalInterfaceFunctionalMockupUnitImportToActuator() override = default;
    ExternalInterfaceFunctionalMockupUnitImportToActuator(const ExternalInterfaceFunctionalMockupUnitImportToActuator& other) = default;
    ExternalInterfaceFunctionalMockupUnitImportToActuator(ExternalInterfaceFunctionalMockupUnitImportToActuator&& other) = default;
    ExternalInterfaceFunctionalMockupUnitImportToActuator& operator=(const ExternalInterfaceFunctionalMockupUnitImportToActuator&) = default;
    ExternalInterfaceFunctionalMockupUnitImportToActuator& operator=(ExternalInterfaceFunctionalMockupUnitImportToActuator&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::ExternalInterfaceFunctionalMockupUnitImportToActuator scalar accessor names/signatures.
    // - Field Mapping: actuatedComponentType -> ExternalInterface:FunctionalMockupUnitImport:To:Actuator, Actuated Component Type.
    // - Field Mapping: actuatedComponentControlType -> ExternalInterface:FunctionalMockupUnitImport:To:Actuator, Actuated Component Control Type.
    // - Field Mapping: fMUInstanceName -> ExternalInterface:FunctionalMockupUnitImport:To:Actuator, FMU Instance Name.
    // - Field Mapping: fMUVariableName -> ExternalInterface:FunctionalMockupUnitImport:To:Actuator, FMU Variable Name.
    // - Field Mapping: initialValue -> ExternalInterface:FunctionalMockupUnitImport:To:Actuator, Initial Value.
    // - Field Mapping: actuatedComponentUnique / fMUFile are relationship APIs and excluded from scalar scaffold.
    // - ForwardTranslator evidence: ForwardTranslateExternalInterfaceFunctionalMockupUnitImportToActuator.cpp writes these scalar fields directly.
    // - TODO(parity): Add relationship APIs incrementally without changing preserved scalar signatures.
    std::string actuatedComponentType() const;
    bool setActuatedComponentType(const std::string& actuatedComponentType);

    std::string actuatedComponentControlType() const;
    bool setActuatedComponentControlType(const std::string& actuatedComponentControlType);

    std::string fMUInstanceName() const;
    bool setFMUInstanceName(const std::string& fMUInstanceName);

    std::string fMUVariableName() const;
    bool setFMUVariableName(const std::string& fMUVariableName);

    double initialValue() const;
    bool setInitialValue(double initialValue);

   protected:
    using ImplType = detail::ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ExternalInterfaceFunctionalMockupUnitImportToActuator(
      std::shared_ptr<detail::ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
