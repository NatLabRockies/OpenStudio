/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENERGYMANAGEMENTSYSTEMCONSTRUCTIONINDEXVARIABLE_HPP
#define EPMODEL_ENERGYMANAGEMENTSYSTEMCONSTRUCTIONINDEXVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class EnergyManagementSystemConstructionIndexVariable_Impl;
  }

  /** \brief Represents <code>EnergyManagementSystem:ConstructionIndexVariable</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-energy-management-system-ems.html#energymanagementsystemconstructionindexvariable,EnergyManagementSystem:ConstructionIndexVariable}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::EnergyManagementSystemConstructionIndexVariable</code>.
   * **Not yet available:** Model typed object-target, program-body, and EMS relationship conveniences are not exposed unless declared by this wrapper.
   *
   * \par Known limitations
   * Typed relationship and extensible-list conveniences not represented by the public declarations are unavailable.
   */
  class EPMODEL_API EnergyManagementSystemConstructionIndexVariable : public ModelObject
  {
   public:
    explicit EnergyManagementSystemConstructionIndexVariable(const Model& model);

    virtual ~EnergyManagementSystemConstructionIndexVariable() override = default;
    EnergyManagementSystemConstructionIndexVariable(const EnergyManagementSystemConstructionIndexVariable& other) = default;
    EnergyManagementSystemConstructionIndexVariable(EnergyManagementSystemConstructionIndexVariable&& other) = default;
    EnergyManagementSystemConstructionIndexVariable& operator=(const EnergyManagementSystemConstructionIndexVariable&) = default;
    EnergyManagementSystemConstructionIndexVariable& operator=(EnergyManagementSystemConstructionIndexVariable&&) = default;

    static IddObjectType iddObjectType();
   protected:
    using ImplType = detail::EnergyManagementSystemConstructionIndexVariable_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit EnergyManagementSystemConstructionIndexVariable(std::shared_ptr<detail::EnergyManagementSystemConstructionIndexVariable_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
