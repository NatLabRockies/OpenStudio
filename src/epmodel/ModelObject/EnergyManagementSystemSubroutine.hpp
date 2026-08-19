/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENERGYMANAGEMENTSYSTEMSUBROUTINE_HPP
#define EPMODEL_ENERGYMANAGEMENTSYSTEMSUBROUTINE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class EnergyManagementSystemSubroutine_Impl;
  }

  /** \brief Represents <code>EnergyManagementSystem:Subroutine</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-energy-management-system-ems.html#energymanagementsystemsubroutine,EnergyManagementSystem:Subroutine}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::EnergyManagementSystemSubroutine</code>.
   * **Not yet available:** Model typed object-target, program-body, and EMS relationship conveniences are not exposed unless declared by this wrapper.
   *
   * \par Known limitations
   * Typed relationship and extensible-list conveniences not represented by the public declarations are unavailable.
   */
  class EPMODEL_API EnergyManagementSystemSubroutine : public ModelObject
  {
   public:
    explicit EnergyManagementSystemSubroutine(const Model& model);

    virtual ~EnergyManagementSystemSubroutine() override = default;
    EnergyManagementSystemSubroutine(const EnergyManagementSystemSubroutine& other) = default;
    EnergyManagementSystemSubroutine(EnergyManagementSystemSubroutine&& other) = default;
    EnergyManagementSystemSubroutine& operator=(const EnergyManagementSystemSubroutine&) = default;
    EnergyManagementSystemSubroutine& operator=(EnergyManagementSystemSubroutine&&) = default;

    static IddObjectType iddObjectType();
   protected:
    using ImplType = detail::EnergyManagementSystemSubroutine_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit EnergyManagementSystemSubroutine(std::shared_ptr<detail::EnergyManagementSystemSubroutine_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
