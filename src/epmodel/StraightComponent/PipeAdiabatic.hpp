/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PIPEADIABATIC_HPP
#define EPMODEL_PIPEADIABATIC_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class PipeAdiabatic_Impl;
}

class EPMODEL_API PipeAdiabatic : public StraightComponent
{
 public:
  explicit PipeAdiabatic(const Model& model);

  virtual ~PipeAdiabatic() override = default;
  PipeAdiabatic(const PipeAdiabatic& other) = default;
  PipeAdiabatic(PipeAdiabatic&& other) = default;
  PipeAdiabatic& operator=(const PipeAdiabatic&) = default;
  PipeAdiabatic& operator=(PipeAdiabatic&&) = default;

  unsigned inletPort() const;
  unsigned outletPort() const;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - Status: Near Parity. The canonical type-specific `PipeAdiabatic` surface is small and already preserved in epmodel.
  // - Canonical Counterpart: openstudio::model::PipeAdiabatic.
  // - Implemented Parity: `inletPort`, `outletPort`, and the otherwise minimal type shape match the canonical wrapper while inherited straight-component topology behavior carries the usable API.
  // - Field/Storage Mapping: `Pipe:Adiabatic` stores only name and node-link fields, and epmodel keeps those links implicit through inherited topology helpers rather than new pipe-local scalar APIs.
  // - Evidence: `src/model/PipeAdiabatic.hpp` defines the canonical type-specific surface, and `src/energyplus/ForwardTranslator/ForwardTranslatePipeAdiabatic.cpp` maps inherited inlet/outlet topology to EnergyPlus node-name fields.
  // - Remaining Parity Work: Confirm whether any additional type-local relationship convenience beyond inherited `StraightComponent` behavior is needed as broader relationship coverage matures.

 protected:
  using ImplType = detail::PipeAdiabatic_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit PipeAdiabatic(std::shared_ptr<detail::PipeAdiabatic_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
