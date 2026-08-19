/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_NODELIST_HPP
#define EPMODEL_NODELIST_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"
#include "Node.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class NodeList_Impl;
  }

  /** \brief NodeList.
   *
   * \par EnergyPlus object
   * \epobject{group-node-branch-management.html#nodelist,NodeList}.
   *
   * \par OpenStudio Model API
   * There is no corresponding <code>openstudio::model</code> class; this wrapper reads the node targets, but node-list mutation is not exposed.
   *
   * \par Known limitations
   * There is no corresponding <code>openstudio::model</code> class; this wrapper reads the node targets, but node-list mutation is not exposed.
   */
  class EPMODEL_API NodeList : public ModelObject
  {
   public:
    explicit NodeList(const Model& model);

    virtual ~NodeList() override = default;
    NodeList(const NodeList& other) = default;
    NodeList(NodeList&& other) = default;
    NodeList& operator=(const NodeList&) = default;
    NodeList& operator=(NodeList&&) = default;

    std::vector<Node> nodes() const;

    static IddObjectType iddObjectType();

   protected:
    using ImplType = detail::NodeList_Impl;

    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class Model;

    explicit NodeList(std::shared_ptr<detail::NodeList_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
