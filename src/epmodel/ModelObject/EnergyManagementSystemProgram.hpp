/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENERGYMANAGEMENTSYSTEMPROGRAM_HPP
#define EPMODEL_ENERGYMANAGEMENTSYSTEMPROGRAM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class EnergyManagementSystemProgram_Impl;
  }

  /** \brief Represents <code>EnergyManagementSystem:Program</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-energy-management-system-ems.html#energymanagementsystemprogram,EnergyManagementSystem:Program}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::EnergyManagementSystemProgram</code>.
   * **Not yet available:** Model typed object-target, program-body, and EMS relationship conveniences are not exposed unless declared by this wrapper.
   *
   * \par Known limitations
   * Typed relationship and extensible-list conveniences not represented by the public declarations are unavailable.
   */
  class EPMODEL_API EnergyManagementSystemProgram : public ModelObject
  {
   public:
    explicit EnergyManagementSystemProgram(const Model& model);

    virtual ~EnergyManagementSystemProgram() override = default;
    EnergyManagementSystemProgram(const EnergyManagementSystemProgram& other) = default;
    EnergyManagementSystemProgram(EnergyManagementSystemProgram&& other) = default;
    EnergyManagementSystemProgram& operator=(const EnergyManagementSystemProgram&) = default;
    EnergyManagementSystemProgram& operator=(EnergyManagementSystemProgram&&) = default;

    static IddObjectType iddObjectType();
   protected:
    using ImplType = detail::EnergyManagementSystemProgram_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit EnergyManagementSystemProgram(std::shared_ptr<detail::EnergyManagementSystemProgram_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
