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

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model::EnergyManagementSystemGlobalVariable class name and constructor signature.
    // - Field Mapping: constructor variableName maps to EnergyPlus EnergyManagementSystem:GlobalVariable extensible field Erl Variable Name.
    // - ForwardTranslator evidence: ForwardTranslateEnergyManagementSystemGlobalVariable.cpp writes modelObject.name() into ErlVariableName extensible entries.
    // - API Drift: openstudio::model::exportToBCVTB APIs are OS-schema-only and have no scalar field on EnergyPlus EnergyManagementSystem:GlobalVariable.
    // - TODO(parity): If/when Output:EnergyManagementSystem parity is added, evaluate cross-object mapping for export controls.

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
