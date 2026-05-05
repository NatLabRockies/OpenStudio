/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENERGYMANAGEMENTSYSTEMTRENDVARIABLE_HPP
#define EPMODEL_ENERGYMANAGEMENTSYSTEMTRENDVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class EnergyManagementSystemTrendVariable_Impl;
  }

  class EPMODEL_API EnergyManagementSystemTrendVariable : public ModelObject
  {
   public:
    explicit EnergyManagementSystemTrendVariable(const Model& model, const std::string& eMSVariableName);

    virtual ~EnergyManagementSystemTrendVariable() override = default;
    EnergyManagementSystemTrendVariable(const EnergyManagementSystemTrendVariable& other) = default;
    EnergyManagementSystemTrendVariable(EnergyManagementSystemTrendVariable&& other) = default;
    EnergyManagementSystemTrendVariable& operator=(const EnergyManagementSystemTrendVariable&) = default;
    EnergyManagementSystemTrendVariable& operator=(EnergyManagementSystemTrendVariable&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model::EnergyManagementSystemTrendVariable scalar accessor names/signatures.
    // - Field Mapping: emsVariableName -> EnergyPlus EnergyManagementSystem:TrendVariable, EMS Variable Name.
    // - Field Mapping: numberOfTimestepsToBeLogged -> EnergyPlus EnergyManagementSystem:TrendVariable, Number of Timesteps to be Logged.
    // - ForwardTranslator evidence: ForwardTranslateEnergyManagementSystemTrendVariable.cpp writes these same scalar fields from the preserved APIs.
    // - TODO(parity): Add relationship/object-target overloads (emsVariableObject and typed setEMSVariableName overloads) incrementally without changing scalar signatures.
    std::string emsVariableName() const;
    bool setEMSVariableName(const std::string& eMSVariableName);

    int numberOfTimestepsToBeLogged() const;
    bool setNumberOfTimestepsToBeLogged(int numberofTimestepstobeLogged);

   protected:
    using ImplType = detail::EnergyManagementSystemTrendVariable_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit EnergyManagementSystemTrendVariable(std::shared_ptr<detail::EnergyManagementSystemTrendVariable_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
