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

  /** \brief Represents <code>BranchList</code>.
   *
   * \par EnergyPlus object
   * Represents \epobject{group-node-branch-management.html#branchlist,BranchList}.
   *
   * \par Important behavior
   * The extensible branch-name rows preserve loop ordering and are resolved by <code>branches()</code>.
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for <code>BranchList</code>; this wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * Relationship-row mutation and higher-level topology conveniences remain owner-managed or unavailable through this wrapper.
   */
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

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit BranchList(std::shared_ptr<detail::BranchList_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
