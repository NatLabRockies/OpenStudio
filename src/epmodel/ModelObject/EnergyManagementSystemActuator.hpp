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
    explicit EnergyManagementSystemActuator(const ModelObject& actuatedComponent, const std::string& actuatedComponentType,
                                            const std::string& actuatedComponentControlType);

    explicit EnergyManagementSystemActuator(const Model& model);

    virtual ~EnergyManagementSystemActuator() override = default;
    EnergyManagementSystemActuator(const EnergyManagementSystemActuator& other) = default;
    EnergyManagementSystemActuator(EnergyManagementSystemActuator&& other) = default;
    EnergyManagementSystemActuator& operator=(const EnergyManagementSystemActuator&) = default;
    EnergyManagementSystemActuator& operator=(EnergyManagementSystemActuator&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserves the canonical actuator constructor plus the main actuated-component and scalar accessors.
    // - Field Mapping: `actuatedComponent` resolves the real EnergyPlus `Actuated Component Unique Name` field. That field is still string-backed in the
    //   current schema metadata, so epmodel resolves it by exact object name instead of a live object-list reference.
    // - Field Mapping: `actuatedComponentType` -> EnergyPlus `Actuated Component Type`.
    // - Field Mapping: `actuatedComponentControlType` -> EnergyPlus `Actuated Component Control Type`.
    // - Documented Delta: Space-load-specific zone-or-space targeting convenience is still not exposed in epmodel.
    // - ForwardTranslator evidence: ForwardTranslateEnergyManagementSystemActuator.cpp writes these scalar fields directly and uses the
    //   actuated-component relationship as the source of the emitted unique name.
    boost::optional<ModelObject> actuatedComponent() const;
    bool setActuatedComponent(const ModelObject& actuatedComponent);

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
