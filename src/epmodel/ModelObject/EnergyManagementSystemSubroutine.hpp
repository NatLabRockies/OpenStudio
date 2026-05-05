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

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model::EnergyManagementSystemSubroutine class naming.
    // - Field Mapping: EnergyPlus Subroutine Program Line is an extensible/non-scalar field and intentionally excluded from simple scalar accessor scaffold.
    // - ForwardTranslator evidence: ForwardTranslateEnergyManagementSystemSubroutine.cpp copies OS extensible ProgramLine entries to E+ extensible ProgramLine entries.
    // - TODO(parity): Add non-scalar body/lines/referencedObjects APIs incrementally without changing scalar scaffolding conventions.

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
