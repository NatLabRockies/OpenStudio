/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONNECTORSPLITTER_IMPL_HPP
#define EPMODEL_CONNECTORSPLITTER_IMPL_HPP

#include "HVACComponent/Splitter_Impl.hpp"

namespace openstudio {
namespace epmodel {
class Branch;
namespace detail {

class EPMODEL_API ConnectorSplitter_Impl : public Splitter_Impl
{
 public:
  using Splitter_Impl::Splitter_Impl;
  virtual ~ConnectorSplitter_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort(unsigned branchIndex) const override;
  boost::optional<openstudio::epmodel::ModelObject> inletModelObject() const override;
  std::vector<openstudio::epmodel::ModelObject> outletModelObjects() const override;
  unsigned nextBranchIndex() const override;
  void removePortForBranch(unsigned branchIndex) override;
  bool setOutletModelObject(unsigned branchIndex, const openstudio::epmodel::ModelObject& modelObject) override;

  boost::optional<openstudio::epmodel::Branch> inletBranch() const;
  bool setInletBranch(const openstudio::epmodel::Branch& branch);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
