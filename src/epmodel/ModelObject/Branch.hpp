/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_BRANCH_HPP
#define EPMODEL_BRANCH_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"
#include "Node.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  namespace detail {
    class Branch_Impl;
  }

  /** \brief Represents <code>Branch</code>.
   *
   * \par EnergyPlus object
   * Represents \epobject{group-node-branch-management.html#branch,Branch}.
   *
   * \par Important behavior
   * The ordered component and node rows are the saved loop topology; <code>components()</code> resolves those rows to live EPModel objects.
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for <code>Branch</code>; this wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * Relationship-row mutation and higher-level topology conveniences remain owner-managed or unavailable through this wrapper.
   */
  class EPMODEL_API Branch : public ModelObject
  {
   public:
    explicit Branch(const Model& model);

    virtual ~Branch() override = default;
    Branch(const Branch& other) = default;
    Branch(Branch&& other) = default;
    Branch& operator=(const Branch&) = default;
    Branch& operator=(Branch&&) = default;

    std::vector<ModelObject> components() const;
    boost::optional<Node> componentInletNode(unsigned index) const;
    boost::optional<Node> componentOutletNode(unsigned index) const;
    static IddObjectType iddObjectType();

   protected:
    using ImplType = detail::Branch_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit Branch(std::shared_ptr<detail::Branch_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
