/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_BRANCHLIST_HPP
#define EPMODEL_BRANCHLIST_HPP

#include "EPModelAPI.hpp"
#include "Branch.hpp"
#include "ModelObject.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <vector>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
  class BranchList_Impl;
}

class EPMODEL_API BranchList : public ModelObject
{
 public:
  explicit BranchList(const Model& model);

  virtual ~BranchList() override = default;
  BranchList(const BranchList& other) = default;
  BranchList(BranchList&& other) = default;
  BranchList& operator=(const BranchList&) = default;
  BranchList& operator=(BranchList&&) = default;

  std::vector<Branch> branches() const;

 static IddObjectType iddObjectType();

 protected:
  using ImplType = detail::BranchList_Impl;

  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit BranchList(std::shared_ptr<detail::BranchList_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
