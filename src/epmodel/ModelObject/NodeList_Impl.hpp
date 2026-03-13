/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_NODELIST_IMPL_HPP
#define EPMODEL_NODELIST_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <cstddef>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

class Node;
class ModelObject;
class NodeList;

namespace detail {
struct LoadContext;

class EPMODEL_API NodeList_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~NodeList_Impl() override = default;

  static openstudio::epmodel::NodeList ensureAttachedNodeList(LoadContext& context, openstudio::epmodel::ModelObject& owner, unsigned fieldIndex,
                                                              const std::string& listSuffix, const std::string& nodeSuffix,
                                                              std::size_t expectedMaxNodes = 2u);
  std::vector<openstudio::epmodel::Node> nodes() const;
  bool addNode(const openstudio::epmodel::Node& node);
  bool removeNode(const openstudio::epmodel::Node& node);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
