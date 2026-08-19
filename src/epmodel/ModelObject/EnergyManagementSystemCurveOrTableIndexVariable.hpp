/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENERGYMANAGEMENTSYSTEMCURVEORTABLEINDEXVARIABLE_HPP
#define EPMODEL_ENERGYMANAGEMENTSYSTEMCURVEORTABLEINDEXVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class EnergyManagementSystemCurveOrTableIndexVariable_Impl;
  }

  /** \brief Represents <code>EnergyManagementSystem:CurveOrTableIndexVariable</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-energy-management-system-ems.html#energymanagementsystemcurveortableindexvariable,EnergyManagementSystem:CurveOrTableIndexVariable}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::EnergyManagementSystemCurveOrTableIndexVariable</code>.
   * **Not yet available:** Model typed object-target, program-body, and EMS relationship conveniences are not exposed unless declared by this wrapper.
   *
   * \par Known limitations
   * Typed relationship and extensible-list conveniences not represented by the public declarations are unavailable.
   */
  class EPMODEL_API EnergyManagementSystemCurveOrTableIndexVariable : public ModelObject
  {
   public:
    explicit EnergyManagementSystemCurveOrTableIndexVariable(const Model& model);

    virtual ~EnergyManagementSystemCurveOrTableIndexVariable() override = default;
    EnergyManagementSystemCurveOrTableIndexVariable(const EnergyManagementSystemCurveOrTableIndexVariable& other) = default;
    EnergyManagementSystemCurveOrTableIndexVariable(EnergyManagementSystemCurveOrTableIndexVariable&& other) = default;
    EnergyManagementSystemCurveOrTableIndexVariable& operator=(const EnergyManagementSystemCurveOrTableIndexVariable&) = default;
    EnergyManagementSystemCurveOrTableIndexVariable& operator=(EnergyManagementSystemCurveOrTableIndexVariable&&) = default;

    static IddObjectType iddObjectType();
   protected:
    using ImplType = detail::EnergyManagementSystemCurveOrTableIndexVariable_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit EnergyManagementSystemCurveOrTableIndexVariable(std::shared_ptr<detail::EnergyManagementSystemCurveOrTableIndexVariable_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
