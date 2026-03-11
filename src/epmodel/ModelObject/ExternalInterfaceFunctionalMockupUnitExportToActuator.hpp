/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITEXPORTTOACTUATOR_HPP
#define EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITEXPORTTOACTUATOR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl;
}

class EPMODEL_API ExternalInterfaceFunctionalMockupUnitExportToActuator : public ModelObject
{
 public:
  explicit ExternalInterfaceFunctionalMockupUnitExportToActuator(const Model& model);

  virtual ~ExternalInterfaceFunctionalMockupUnitExportToActuator() override = default;
  ExternalInterfaceFunctionalMockupUnitExportToActuator(const ExternalInterfaceFunctionalMockupUnitExportToActuator& other) = default;
  ExternalInterfaceFunctionalMockupUnitExportToActuator(ExternalInterfaceFunctionalMockupUnitExportToActuator&& other) = default;
  ExternalInterfaceFunctionalMockupUnitExportToActuator& operator=(const ExternalInterfaceFunctionalMockupUnitExportToActuator&) = default;
  ExternalInterfaceFunctionalMockupUnitExportToActuator& operator=(ExternalInterfaceFunctionalMockupUnitExportToActuator&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::ExternalInterfaceFunctionalMockupUnitExportToActuator scalar accessor names/signatures.
  // - Field Mapping: actuatedComponentType -> ExternalInterface:FunctionalMockupUnitExport:To:Actuator, Actuated Component Type.
  // - Field Mapping: actuatedComponentControlType -> ExternalInterface:FunctionalMockupUnitExport:To:Actuator, Actuated Component Control Type.
  // - Field Mapping: fMUVariableName -> ExternalInterface:FunctionalMockupUnitExport:To:Actuator, FMU Variable Name.
  // - Field Mapping: initialValue -> ExternalInterface:FunctionalMockupUnitExport:To:Actuator, Initial Value.
  // - Field Mapping: actuatedComponentUnique is relationship-like (object target) and excluded from scalar scaffold.
  // - ForwardTranslator evidence: ForwardTranslateExternalInterfaceFunctionalMockupUnitExportToActuator.cpp writes these scalar fields directly.
  // - TODO(parity): Add relationship APIs incrementally without changing preserved scalar signatures.
  std::string actuatedComponentType() const;
  bool setActuatedComponentType(const std::string& actuatedComponentType);

  std::string actuatedComponentControlType() const;
  bool setActuatedComponentControlType(const std::string& actuatedComponentControlType);

  std::string fMUVariableName() const;
  bool setFMUVariableName(const std::string& fMUVariableName);

  boost::optional<double> initialValue() const;
  bool setInitialValue(double initialValue);

 protected:
  using ImplType = detail::ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ExternalInterfaceFunctionalMockupUnitExportToActuator(
    std::shared_ptr<detail::ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
