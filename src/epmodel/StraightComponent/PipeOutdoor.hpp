/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PIPEOUTDOOR_HPP
#define EPMODEL_PIPEOUTDOOR_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class PipeOutdoor_Impl;
}

class EPMODEL_API PipeOutdoor : public StraightComponent
{
 public:
  explicit PipeOutdoor(const Model& model);

  virtual ~PipeOutdoor() override = default;
  PipeOutdoor(const PipeOutdoor& other) = default;
  PipeOutdoor(PipeOutdoor&& other) = default;
  PipeOutdoor& operator=(const PipeOutdoor&) = default;
  PipeOutdoor& operator=(PipeOutdoor&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::PipeOutdoor scalar accessor names/signatures for counterpart parity.
  // - Field Mapping: pipeInsideDiameter and pipeLength map directly to E+ Pipe:Outdoor fields.
  // - ForwardTranslator evidence: ForwardTranslatePipeOutdoor.cpp writes these scalar APIs directly to matching E+ fields.
  // - Field Mapping: Construction, ambient outdoor-air node, and fluid node names are relationship-like and excluded from this scalar pass.
  // - TODO(parity): Add excluded relationship APIs without changing preserved scalar signatures.
  double pipeInsideDiameter() const;
  bool setPipeInsideDiameter(double pipeInsideDiameter);

  double pipeLength() const;
  bool setPipeLength(double pipeLength);

 protected:
  using ImplType = detail::PipeOutdoor_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit PipeOutdoor(std::shared_ptr<detail::PipeOutdoor_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
