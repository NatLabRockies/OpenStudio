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

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model::EnergyManagementSystemProgram class naming.
    // - Field Mapping: EnergyPlus Program Line is an extensible/non-scalar field and intentionally excluded from simple scalar accessor scaffold.
    // - ForwardTranslator evidence: ForwardTranslateEnergyManagementSystemProgram.cpp maps OS extensible ProgramLine entries to E+ extensible ProgramLine entries.
    // - TODO(parity): Add non-scalar body/lines/referencedObjects APIs incrementally without changing scalar scaffolding conventions.

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
