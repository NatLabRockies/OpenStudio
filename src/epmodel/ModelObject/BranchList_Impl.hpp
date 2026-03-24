/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_BRANCHLIST_IMPL_HPP
#define EPMODEL_BRANCHLIST_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

class Branch;

namespace detail {
struct LoadContext;

class EPMODEL_API BranchList_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~BranchList_Impl() override = default;

  std::vector<openstudio::epmodel::Branch> branches() const;
  bool insertBranch(unsigned index, const openstudio::epmodel::Branch& branch);
  bool addBranch(const openstudio::epmodel::Branch& branch);
  bool removeBranch(const openstudio::epmodel::Branch& branch);
  void doCanonicalize(LoadContext& context) override;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
