/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SPLITTER_HPP
#define EPMODEL_SPLITTER_HPP

#include "HVACComponent/HVACComponent.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {
class Loop_Impl;
class Splitter_Impl;
}

 class EPMODEL_API Splitter : public HVACComponent
 {
  public:
    virtual ~Splitter() override = default;
    Splitter(const Splitter& other) = default;
    Splitter(Splitter&& other) = default;
    Splitter& operator=(const Splitter&) = default;
    Splitter& operator=(Splitter&&) = default;

  // Schema Alignment Notes:
  // - Status: Partial Parity. The canonical branch-oriented splitter API is present, but topology-heavy behavior still depends on the broader loop normalization work.
  // - Canonical Counterpart: openstudio::model::Splitter.
  // - Implemented Parity: Inlet/outlet port queries, outlet-object traversal, branch indexing, branch creation, and branch removal preserve the canonical splitter topology contract.
  // - Field/Storage Mapping: Splitter branch linkage is expressed through EnergyPlus-backed connector topology rather than model-side `Connection` storage.
  // - Evidence: `src/model/Splitter.hpp` defines the canonical branch API surface; the zone-splitter and loop topology wrappers exercise that contract in epmodel.
  // - Remaining Parity Work: Confirm remaining topology semantics and connector-specific behavior as the loop-branch family finishes normalization.
  virtual boost::optional<ModelObject> inletModelObject() const;
  virtual unsigned inletPort() const;
  virtual unsigned outletPort(unsigned branchIndex) const;
  virtual unsigned nextOutletPort() const;
  virtual boost::optional<ModelObject> outletModelObject(unsigned branchIndex) const;
  virtual boost::optional<ModelObject> lastOutletModelObject() const;
  virtual std::vector<ModelObject> outletModelObjects() const;
  virtual unsigned newOutletPortAfterBranch(unsigned branchIndex);
  virtual unsigned branchIndexForOutletModelObject(ModelObject modelObject) const;
  virtual unsigned nextBranchIndex() const;
  virtual void removePortForBranch(unsigned branchIndex);

  protected:
  using ImplType = detail::Splitter_Impl;

  friend class openstudio::epmodel::detail::Loop_Impl;
  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit Splitter(const Model& model);
  Splitter(IddObjectType type, const Model& model);
  explicit Splitter(std::shared_ptr<ImplType> impl);
  virtual bool setOutletModelObject(unsigned branchIndex, const ModelObject& modelObject);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
