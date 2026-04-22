/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MIXER_HPP
#define EPMODEL_MIXER_HPP

#include "HVACComponent/HVACComponent.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {
class Loop_Impl;
class Mixer_Impl;
}

 class EPMODEL_API Mixer : public HVACComponent
 {
  public:
    virtual ~Mixer() override = default;
    Mixer(const Mixer& other) = default;
    Mixer(Mixer&& other) = default;
    Mixer& operator=(const Mixer&) = default;
    Mixer& operator=(Mixer&&) = default;

  // Schema Alignment Notes:
  // - Status: Partial Parity. The canonical branch-oriented mixer API is present, but topology-heavy behavior still depends on the broader loop normalization work.
  // - Canonical Counterpart: openstudio::model::Mixer.
  // - Implemented Parity: Outlet/inlet port queries, inlet-object traversal, branch indexing, branch creation, and branch removal preserve the canonical mixer topology contract.
  // - Field/Storage Mapping: Mixer branch linkage is expressed through EnergyPlus-backed connector topology rather than model-side `Connection` storage.
  // - Evidence: `src/model/Mixer.hpp` defines the canonical branch API surface; the zone-mixer and loop topology wrappers exercise that contract in epmodel.
  // - Remaining Parity Work: Confirm remaining topology semantics and connector-specific behavior as the loop-branch family finishes normalization.
  virtual boost::optional<ModelObject> outletModelObject() const;
  virtual bool setOutletModelObject(const ModelObject& modelObject);
  virtual unsigned outletPort() const;
  virtual unsigned inletPort(unsigned branchIndex) const;
  virtual unsigned nextInletPort() const;
  virtual boost::optional<ModelObject> inletModelObject(unsigned branchIndex) const;
  virtual boost::optional<ModelObject> lastInletModelObject() const;
  virtual std::vector<ModelObject> inletModelObjects() const;
  virtual unsigned newInletPortAfterBranch(unsigned branchIndex);
  virtual unsigned branchIndexForInletModelObject(const ModelObject& modelObject) const;
  virtual unsigned nextBranchIndex() const;
  virtual void removePortForBranch(unsigned branchIndex);
  virtual bool setInletModelObject(unsigned branchIndex, const ModelObject& modelObject);

  protected:
  using ImplType = detail::Mixer_Impl;

  friend class openstudio::epmodel::detail::Loop_Impl;
  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit Mixer(const Model& model);
  Mixer(IddObjectType type, const Model& model);
  explicit Mixer(std::shared_ptr<ImplType> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
