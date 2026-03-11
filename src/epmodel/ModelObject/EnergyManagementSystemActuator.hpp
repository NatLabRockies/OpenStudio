/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENERGYMANAGEMENTSYSTEMACTUATOR_HPP
#define EPMODEL_ENERGYMANAGEMENTSYSTEMACTUATOR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class EnergyManagementSystemActuator_Impl;
}

class EPMODEL_API EnergyManagementSystemActuator : public ModelObject
{
 public:
  explicit EnergyManagementSystemActuator(const Model& model);

  virtual ~EnergyManagementSystemActuator() override = default;
  EnergyManagementSystemActuator(const EnergyManagementSystemActuator& other) = default;
  EnergyManagementSystemActuator(EnergyManagementSystemActuator&& other) = default;
  EnergyManagementSystemActuator& operator=(const EnergyManagementSystemActuator&) = default;
  EnergyManagementSystemActuator& operator=(EnergyManagementSystemActuator&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model::EnergyManagementSystemActuator scalar accessor names/signatures.
  // - Field Mapping: actuatedComponentType -> EnergyPlus EnergyManagementSystem:Actuator, Actuated Component Type.
  // - Field Mapping: actuatedComponentControlType -> EnergyPlus EnergyManagementSystem:Actuator, Actuated Component Control Type.
  // - Field Mapping: actuated component identity/zone-or-space targeting remains relationship-like and intentionally excluded from scalar scaffold.
  // - ForwardTranslator evidence: ForwardTranslateEnergyManagementSystemActuator.cpp writes these scalar fields directly.
  // - TODO(parity): Add relationship APIs incrementally without changing these scalar signatures.
  std::string actuatedComponentControlType() const;
  bool setActuatedComponentControlType(const std::string& actuatedComponentControlType);

  std::string actuatedComponentType() const;
  bool setActuatedComponentType(const std::string& actuatedComponentType);

 protected:
  using ImplType = detail::EnergyManagementSystemActuator_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit EnergyManagementSystemActuator(std::shared_ptr<detail::EnergyManagementSystemActuator_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
