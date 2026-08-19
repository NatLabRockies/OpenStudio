/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENERGYMANAGEMENTSYSTEMPROGRAMCALLINGMANAGER_HPP
#define EPMODEL_ENERGYMANAGEMENTSYSTEMPROGRAMCALLINGMANAGER_HPP

#include "EPModelAPI.hpp"
#include "EnergyManagementSystemProgram.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class EnergyManagementSystemProgram;

  namespace detail {
    class EnergyManagementSystemProgramCallingManager_Impl;
  }

  /** \brief Represents <code>EnergyManagementSystem:ProgramCallingManager</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-energy-management-system-ems.html#energymanagementsystemprogramcallingmanager,EnergyManagementSystem:ProgramCallingManager}
   *
   * \par Important behavior
   * Program names are stored in EnergyPlus extensible rows and preserve their calling order.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::EnergyManagementSystemProgramCallingManager</code>.
   * **Not yet available:** Model typed object-target, program-body, and EMS relationship conveniences are not exposed unless declared by this wrapper.
   *
   * \par Known limitations
   * Typed relationship and extensible-list conveniences not represented by the public declarations are unavailable.
   */
  class EPMODEL_API EnergyManagementSystemProgramCallingManager : public ModelObject
  {
   public:
    explicit EnergyManagementSystemProgramCallingManager(const Model& model);

    virtual ~EnergyManagementSystemProgramCallingManager() override = default;
    EnergyManagementSystemProgramCallingManager(const EnergyManagementSystemProgramCallingManager& other) = default;
    EnergyManagementSystemProgramCallingManager(EnergyManagementSystemProgramCallingManager&& other) = default;
    EnergyManagementSystemProgramCallingManager& operator=(const EnergyManagementSystemProgramCallingManager&) = default;
    EnergyManagementSystemProgramCallingManager& operator=(EnergyManagementSystemProgramCallingManager&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validCallingPointValues();
    std::string callingPoint() const;
    bool setCallingPoint(const std::string& callingPoint);

    std::vector<EnergyManagementSystemProgram> programs() const;
    boost::optional<EnergyManagementSystemProgram> getProgram(unsigned index) const;

    bool eraseProgram(unsigned index);
    void erasePrograms();
    bool addProgram(const EnergyManagementSystemProgram& program);
    bool setProgram(const EnergyManagementSystemProgram& program, unsigned index);
    bool setPrograms(const std::vector<EnergyManagementSystemProgram>& programs);

   protected:
    using ImplType = detail::EnergyManagementSystemProgramCallingManager_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit EnergyManagementSystemProgramCallingManager(std::shared_ptr<detail::EnergyManagementSystemProgramCallingManager_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
