/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONNECTORMIXER_HPP
#define EPMODEL_CONNECTORMIXER_HPP

#include "EPModelAPI.hpp"
#include "Mixer.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
  class ConnectorMixer_Impl;
}

class EPMODEL_API ConnectorMixer : public Mixer
{
 public:
  explicit ConnectorMixer(const Model& model);

  virtual ~ConnectorMixer() override = default;
  ConnectorMixer(const ConnectorMixer& other) = default;
  ConnectorMixer(ConnectorMixer&& other) = default;
  ConnectorMixer& operator=(const ConnectorMixer&) = default;
  ConnectorMixer& operator=(ConnectorMixer&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - Status: Partial Parity. The connector-specific branch-port surface is present, but broader connector/topology behavior still relies on loop-level normalization.
  // - Canonical Counterpart: openstudio::model::ConnectorMixer.
  // - Implemented Parity: Connector-specific inlet/outlet port traversal, branch indexing, outlet lookup, and branch removal APIs preserve the canonical connector-mixer topology contract.
  // - Field/Storage Mapping: Public behavior is organized around EnergyPlus `Connector:Mixer` branch topology rather than OpenStudio connection storage.
  // - Evidence: `src/model/ConnectorMixer.hpp` and the loop topology family establish the canonical connector-specific branch API this wrapper is preserving.
  // - Remaining Parity Work: Confirm any remaining connector-specific loop-integration semantics once the topology family normalization pass is complete.
  unsigned outletPort() const override;
  unsigned inletPort(unsigned branchIndex) const override;
  unsigned nextInletPort() const override;
  boost::optional<ModelObject> outletModelObject() const override;
  std::vector<ModelObject> inletModelObjects() const override;
  unsigned nextBranchIndex() const override;
  void removePortForBranch(unsigned branchIndex) override;
  bool setInletModelObject(unsigned branchIndex, const ModelObject& modelObject) override;

 protected:
  using ImplType = detail::ConnectorMixer_Impl;

  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;
  friend class openstudio::epmodel::Model;

  explicit ConnectorMixer(std::shared_ptr<detail::ConnectorMixer_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
