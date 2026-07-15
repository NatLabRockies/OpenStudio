/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORFUELCELL_HPP
#define EPMODEL_GENERATORFUELCELL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject/ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GeneratorFuelCell_Impl;
  }

  class EPMODEL_API GeneratorFuelCell : public ModelObject
  {
   public:
    explicit GeneratorFuelCell(const Model& model);

    virtual ~GeneratorFuelCell() override = default;
    GeneratorFuelCell(const GeneratorFuelCell& other) = default;
    GeneratorFuelCell(GeneratorFuelCell&& other) = default;
    GeneratorFuelCell& operator=(const GeneratorFuelCell&) = default;
    GeneratorFuelCell& operator=(GeneratorFuelCell&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model class naming for counterpart parity.
    // - Field Mapping: Generator:FuelCell fields beyond Name are relationship-like object-list links and are intentionally
    //   excluded from scalar accessors in this scaffold pass.
    // - ForwardTranslator evidence: ForwardTranslateGeneratorFuelCell maps Power/Air/Fuel/Water/AuxHeater/
    //   HeatExchanger/ElectricalStorage/Inverter/StackCooler relationships directly to E+ object references.
    // - TODO(parity): Add preserved relationship APIs incrementally without changing scalar scaffolding conventions.

   protected:
    using ImplType = detail::GeneratorFuelCell_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GeneratorFuelCell(std::shared_ptr<detail::GeneratorFuelCell_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
