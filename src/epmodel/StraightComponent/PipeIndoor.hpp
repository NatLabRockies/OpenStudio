/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PIPEINDOOR_HPP
#define EPMODEL_PIPEINDOOR_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class PipeIndoor_Impl;
}

class EPMODEL_API PipeIndoor : public StraightComponent
{
 public:
  explicit PipeIndoor(const Model& model);

  virtual ~PipeIndoor() override = default;
  PipeIndoor(const PipeIndoor& other) = default;
  PipeIndoor(PipeIndoor&& other) = default;
  PipeIndoor& operator=(const PipeIndoor&) = default;
  PipeIndoor& operator=(PipeIndoor&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> environmentTypeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::PipeIndoor scalar accessor names/signatures for counterpart parity.
  // - Field Mapping: environmentType, pipeInsideDiameter, and pipeLength map directly to E+ Pipe:Indoor fields.
  // - ForwardTranslator evidence: ForwardTranslatePipeIndoor.cpp writes these scalar APIs directly to matching E+ fields.
  // - Field Mapping: Construction, ambient zone/schedule links, and node names are relationship-like and excluded from this scalar pass.
  // - TODO(parity): Add excluded relationship APIs without changing preserved scalar signatures.
  std::string environmentType() const;
  bool setEnvironmentType(const std::string& environmentType);

  double pipeInsideDiameter() const;
  bool setPipeInsideDiameter(double pipeInsideDiameter);

  double pipeLength() const;
  bool setPipeLength(double pipeLength);

 protected:
  using ImplType = detail::PipeIndoor_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit PipeIndoor(std::shared_ptr<detail::PipeIndoor_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
