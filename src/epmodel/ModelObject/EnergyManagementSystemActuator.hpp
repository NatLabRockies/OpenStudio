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

  /** \brief Represents <code>EnergyManagementSystem:Actuator</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-energy-management-system-ems.html#energymanagementsystemactuator,EnergyManagementSystem:Actuator}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::EnergyManagementSystemActuator</code>.
   * **Not yet available:** Model typed object-target, program-body, and EMS relationship conveniences are not exposed unless declared by this wrapper.
   *
   * \par Known limitations
   * Typed relationship and extensible-list conveniences not represented by the public declarations are unavailable.
   */
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
