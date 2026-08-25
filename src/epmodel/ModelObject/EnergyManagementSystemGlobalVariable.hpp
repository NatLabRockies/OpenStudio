/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENERGYMANAGEMENTSYSTEMGLOBALVARIABLE_HPP
#define EPMODEL_ENERGYMANAGEMENTSYSTEMGLOBALVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class EnergyManagementSystemGlobalVariable_Impl;
  }

  /** \brief Represents <code>EnergyManagementSystem:GlobalVariable</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-energy-management-system-ems.html#energymanagementsystemglobalvariable,EnergyManagementSystem:GlobalVariable}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::EnergyManagementSystemGlobalVariable</code>.
   * **Not yet available:** Model typed object-target, program-body, and EMS relationship conveniences are not exposed unless declared by this wrapper.
   *
   * \par Known limitations
   * Typed relationship and extensible-list conveniences not represented by the public declarations are unavailable.
   */
  class EPMODEL_API EnergyManagementSystemGlobalVariable : public ModelObject
  {
   public:
    explicit EnergyManagementSystemGlobalVariable(const Model& model, const std::string& variableName);

    virtual ~EnergyManagementSystemGlobalVariable() override = default;
    EnergyManagementSystemGlobalVariable(const EnergyManagementSystemGlobalVariable& other) = default;
    EnergyManagementSystemGlobalVariable(EnergyManagementSystemGlobalVariable&& other) = default;
    EnergyManagementSystemGlobalVariable& operator=(const EnergyManagementSystemGlobalVariable&) = default;
    EnergyManagementSystemGlobalVariable& operator=(EnergyManagementSystemGlobalVariable&&) = default;

    static IddObjectType iddObjectType();
   protected:
    using ImplType = detail::EnergyManagementSystemGlobalVariable_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit EnergyManagementSystemGlobalVariable(std::shared_ptr<detail::EnergyManagementSystemGlobalVariable_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
