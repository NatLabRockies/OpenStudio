/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEACTUATOR_HPP
#define EPMODEL_EXTERNALINTERFACEACTUATOR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ExternalInterfaceActuator_Impl;
}

class EPMODEL_API ExternalInterfaceActuator : public ModelObject
{
 public:
  explicit ExternalInterfaceActuator(const Model& model);

  virtual ~ExternalInterfaceActuator() override = default;
  ExternalInterfaceActuator(const ExternalInterfaceActuator& other) = default;
  ExternalInterfaceActuator(ExternalInterfaceActuator&& other) = default;
  ExternalInterfaceActuator& operator=(const ExternalInterfaceActuator&) = default;
  ExternalInterfaceActuator& operator=(ExternalInterfaceActuator&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::ExternalInterfaceActuator scalar accessor names/signatures where mappable to E+.
  // - Field Mapping: actuatedComponentType -> ExternalInterface:Actuator, Actuated Component Type.
  // - Field Mapping: actuatedComponentControlType -> ExternalInterface:Actuator, Actuated Component Control Type.
  // - Field Mapping: optionalInitialValue -> ExternalInterface:Actuator, Optional Initial Value.
  // - Field Mapping: actuatedComponentUnique is relationship-like (object target) and excluded from scalar scaffold.
  // - Field Mapping: exportToBCVTB / isExportToBCVTBDefaulted / setExportToBCVTB / resetExportToBCVTB are OS-only
  //   fields (OS:ExternalInterface:Actuator) and not present in ExternalInterface:Actuator; ForwardTranslator evidence
  //   confirms no EnergyPlus mapping for these APIs.
  // - TODO(parity): Add relationship APIs incrementally without changing preserved scalar signatures.
  std::string actuatedComponentControlType() const;
  bool setActuatedComponentControlType(const std::string& actuatedComponentControlType);

  std::string actuatedComponentType() const;
  bool setActuatedComponentType(const std::string& actuatedComponentType);

  boost::optional<double> optionalInitialValue() const;
  bool setOptionalInitialValue(double optionalInitialValue);
  void resetOptionalInitialValue();

 protected:
  using ImplType = detail::ExternalInterfaceActuator_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ExternalInterfaceActuator(std::shared_ptr<detail::ExternalInterfaceActuator_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
