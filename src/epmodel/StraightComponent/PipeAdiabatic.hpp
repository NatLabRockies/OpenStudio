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
  // - API: Preserve openstudio::model::PipeAdiabatic API shape, including inletPort()/outletPort().
  // - Field Mapping: Pipe:Adiabatic has only Name + node-link fields; node-link fields are relationship-like and excluded from scalar pass.
  // - ForwardTranslator evidence: ForwardTranslatePipeAdiabatic.cpp maps inletModelObject()/outletModelObject() to Inlet/Outlet Node Name.
  // - TODO(parity): Add dedicated relationship/node-link APIs without changing preserved names/signatures.

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
