/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENERGYMANAGEMENTSYSTEMPROGRAMCALLINGMANAGER_HPP
#define EPMODEL_ENERGYMANAGEMENTSYSTEMPROGRAMCALLINGMANAGER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

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
  // - API: Preserves openstudio::model::EnergyManagementSystemProgramCallingManager class and scalar accessor naming/signatures.
  // - Field Mapping: callingPoint -> EnergyPlus EnergyManagementSystem:ProgramCallingManager, EnergyPlus Model Calling Point.
  // - Field Mapping: program list APIs (programs/getProgram/addProgram/setProgram/erasePrograms/setPrograms) are extensible relationship-like and excluded from scalar scaffold.
  // - ForwardTranslator evidence: ForwardTranslateEnergyManagementSystemProgramCallingManager.cpp writes EnergyPlusModelCallingPoint and copies extensible ProgramName groups.
  // - TODO(parity): Add program extensible relationship APIs incrementally without changing these scalar signatures.
  std::string callingPoint() const;
  bool setCallingPoint(const std::string& callingPoint);

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
