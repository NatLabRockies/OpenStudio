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

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model::EnergyManagementSystemConstructionIndexVariable class naming.
    // - Field Mapping: EnergyPlus field Construction Object Name is relationship-like and intentionally excluded from scalar accessor scaffold.
    // - ForwardTranslator evidence: ForwardTranslateEnergyManagementSystemConstructionIndexVariable.cpp writes ConstructionObjectName from modelObject.constructionObject().
    // - TODO(parity): Add relationship APIs incrementally (constructionObject/setConstructionObject) without changing scalar scaffolding conventions.

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
