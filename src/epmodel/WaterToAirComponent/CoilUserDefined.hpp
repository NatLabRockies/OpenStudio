/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILUSERDEFINED_HPP
#define EPMODEL_COILUSERDEFINED_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CoilUserDefined_Impl;
}

class EPMODEL_API CoilUserDefined : public ModelObject
{
 public:
  explicit CoilUserDefined(const Model& model);

  virtual ~CoilUserDefined() override = default;
  CoilUserDefined(const CoilUserDefined& other) = default;
  CoilUserDefined(CoilUserDefined&& other) = default;
  CoilUserDefined& operator=(const CoilUserDefined&) = default;
  CoilUserDefined& operator=(CoilUserDefined&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model scalar accessor naming/signature for model-counterpart compatibility.
  // - Field Mapping: numberofAirConnections maps directly to E+ Coil:UserDefined Number of Air Connections.
  // - Field Mapping: node names, program/program-calling-manager names, ambient zone, actuator fields, and Plant Connection is Used are excluded
  //   from scalar API generation for this cycle.
  // - ForwardTranslator evidence: ForwardTranslateCoilUserDefined.cpp writes Number of Air Connections from numberofAirConnections().
  // - TODO(parity): Add relationship and non-scalar behavior in later parity milestones.
  int numberofAirConnections() const;

 protected:
  using ImplType = detail::CoilUserDefined_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilUserDefined(std::shared_ptr<detail::CoilUserDefined_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
