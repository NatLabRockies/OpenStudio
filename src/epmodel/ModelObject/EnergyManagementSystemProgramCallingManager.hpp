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

    // Schema Alignment Notes:
    // - API: Preserves the canonical calling-point and program-list surface.
    // - Field Mapping: `callingPoint` -> EnergyPlus `Energy Plus Model Calling Point`.
    // - Field Mapping: `programs` and related mutators use the real EnergyPlus extensible `Program Name` rows through `WorkspaceExtensibleGroup`.
    // - ForwardTranslator evidence: ForwardTranslateEnergyManagementSystemProgramCallingManager.cpp writes the calling point and copies the same
    //   extensible program rows.
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
